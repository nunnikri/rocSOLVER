/* ************************************************************************
 * Copyright (c) 2020-2022 Advanced Micro Devices, Inc.
 * ************************************************************************ */

#pragma once

#include "clientcommon.hpp"
#include "lapack_host_reference.hpp"
#include "norm.hpp"
#include "rocsolver.hpp"
#include "rocsolver_arguments.hpp"
#include "rocsolver_test.hpp"

template <typename T>
void larfg_checkBadArgs(const rocblas_handle handle,
                        const rocblas_int n,
                        T da,
                        T dx,
                        const rocblas_int inc,
                        T dt)
{
    // handle
    EXPECT_ROCBLAS_STATUS(rocsolver_larfg(nullptr, n, da, dx, inc, dt),
                          rocblas_status_invalid_handle);

    // values
    // N/A

    // pointers
    EXPECT_ROCBLAS_STATUS(rocsolver_larfg(handle, n, (T) nullptr, dx, inc, dt),
                          rocblas_status_invalid_pointer);
    EXPECT_ROCBLAS_STATUS(rocsolver_larfg(handle, n, da, (T) nullptr, inc, dt),
                          rocblas_status_invalid_pointer);
    EXPECT_ROCBLAS_STATUS(rocsolver_larfg(handle, n, da, dx, inc, (T) nullptr),
                          rocblas_status_invalid_pointer);

    // quick return with invalid pointers
    EXPECT_ROCBLAS_STATUS(rocsolver_larfg(handle, 0, (T) nullptr, (T) nullptr, inc, (T) nullptr),
                          rocblas_status_success);
}

template <typename T>
void testing_larfg_bad_arg()
{
    // safe arguments
    rocblas_local_handle handle;
    rocblas_int n = 2;
    rocblas_int inc = 1;

    // memory allocation
    device_strided_batch_vector<T> da(1, 1, 1, 1);
    device_strided_batch_vector<T> dx(1, 1, 1, 1);
    device_strided_batch_vector<T> dt(1, 1, 1, 1);
    CHECK_HIP_ERROR(da.memcheck());
    CHECK_HIP_ERROR(dx.memcheck());
    CHECK_HIP_ERROR(dt.memcheck());

    // check bad arguments
    larfg_checkBadArgs(handle, n, da.data(), dx.data(), inc, dt.data());
}

template <bool CPU, bool GPU, typename T, typename Td, typename Th>
void larfg_initData(const rocblas_handle handle,
                    const rocblas_int n,
                    Td& da,
                    Td& dx,
                    const rocblas_int inc,
                    Td& dt,
                    Th& ha,
                    Th& hx,
                    Th& ht)
{
    if(CPU)
    {
        rocblas_init<T>(ha, true);
        rocblas_init<T>(hx, true);
    }

    if(GPU)
    {
        // copy data from CPU to device
        CHECK_HIP_ERROR(da.transfer_from(ha));
        CHECK_HIP_ERROR(dx.transfer_from(hx));
    }
}

template <typename T, typename Td, typename Th>
void larfg_getError(const rocblas_handle handle,
                    const rocblas_int n,
                    Td& da,
                    Td& dx,
                    const rocblas_int inc,
                    Td& dt,
                    Th& ha,
                    Th& hx,
                    Th& hxr,
                    Th& ht,
                    double* max_err)
{
    // initialize data
    larfg_initData<true, true, T>(handle, n, da, dx, inc, dt, ha, hx, ht);

    // execute computations
    // GPU lapack
    CHECK_ROCBLAS_ERROR(rocsolver_larfg(handle, n, da.data(), dx.data(), inc, dt.data()));
    CHECK_HIP_ERROR(hxr.transfer_from(dx));

    // CPU lapack
    cblas_larfg<T>(n, ha[0], hx[0], inc, ht[0]);

    // error is ||hx - hxr|| (not necessary to check tau, for now)
    // (THIS DOES NOT ACCOUNT FOR NUMERICAL REPRODUCIBILITY ISSUES.
    // IT MIGHT BE REVISITED IN THE FUTURE)
    // using norm-1 which is infinity norm for this data setup
    *max_err = norm_error('O', 1, n - 1, inc, hx[0], hxr[0]);
}

template <typename T, typename Td, typename Th>
void larfg_getPerfData(const rocblas_handle handle,
                       const rocblas_int n,
                       Td& da,
                       Td& dx,
                       const rocblas_int inc,
                       Td& dt,
                       Th& ha,
                       Th& hx,
                       Th& ht,
                       double* gpu_time_used,
                       double* cpu_time_used,
                       const rocblas_int hot_calls,
                       const int profile,
                       const bool profile_kernels,
                       const bool perf)
{
    if(!perf)
    {
        larfg_initData<true, false, T>(handle, n, da, dx, inc, dt, ha, hx, ht);

        // cpu-lapack performance (only if not in perf mode)
        *cpu_time_used = get_time_us_no_sync();
        cblas_larfg<T>(n, ha[0], hx[0], inc, ht[0]);
        *cpu_time_used = get_time_us_no_sync() - *cpu_time_used;
    }

    larfg_initData<true, false, T>(handle, n, da, dx, inc, dt, ha, hx, ht);

    // cold calls
    for(int iter = 0; iter < 2; iter++)
    {
        larfg_initData<false, true, T>(handle, n, da, dx, inc, dt, ha, hx, ht);

        CHECK_ROCBLAS_ERROR(rocsolver_larfg(handle, n, da.data(), dx.data(), inc, dt.data()));
    }

    // gpu-lapack performance
    hipStream_t stream;
    CHECK_ROCBLAS_ERROR(rocblas_get_stream(handle, &stream));
    double start;

    if(profile > 0)
    {
        if(profile_kernels)
            rocsolver_log_set_layer_mode(rocblas_layer_mode_log_profile
                                         | rocblas_layer_mode_ex_log_kernel);
        else
            rocsolver_log_set_layer_mode(rocblas_layer_mode_log_profile);
        rocsolver_log_set_max_levels(profile);
    }

    for(int iter = 0; iter < hot_calls; iter++)
    {
        larfg_initData<false, true, T>(handle, n, da, dx, inc, dt, ha, hx, ht);

        start = get_time_us_sync(stream);
        rocsolver_larfg(handle, n, da.data(), dx.data(), inc, dt.data());
        *gpu_time_used += get_time_us_sync(stream) - start;
    }
    *gpu_time_used /= hot_calls;
}

template <typename T>
void testing_larfg(Arguments& argus)
{
    // get arguments
    rocblas_local_handle handle;
    rocblas_int n = argus.get<rocblas_int>("n");
    rocblas_int inc = argus.get<rocblas_int>("incx");

    rocblas_int hot_calls = argus.iters;

    // check non-supported values
    // N/A

    // determine sizes
    // size_x could be zero in test cases that are not quick-return or invalid
    // cases setting it to one to avoid possible memory access errors in the rest
    // of the unit test
    size_t size_x = n > 1 ? size_t(n - 1) : 1;
    size_t stx = size_x * inc;
    double max_error = 0, gpu_time_used = 0, cpu_time_used = 0;

    size_t size_xr = (argus.unit_check || argus.norm_check) ? size_x : 0;
    size_t stxr = (argus.unit_check || argus.norm_check) ? stx : 0;

    // check invalid sizes
    bool invalid_size = (n < 0 || inc < 1);
    if(invalid_size)
    {
        EXPECT_ROCBLAS_STATUS(rocsolver_larfg(handle, n, (T*)nullptr, (T*)nullptr, inc, (T*)nullptr),
                              rocblas_status_invalid_size);

        if(argus.timing)
            rocsolver_bench_inform(inform_invalid_size);

        return;
    }

    // memory size query is necessary
    if(argus.mem_query || !USE_ROCBLAS_REALLOC_ON_DEMAND)
    {
        CHECK_ROCBLAS_ERROR(rocblas_start_device_memory_size_query(handle));
        CHECK_ALLOC_QUERY(rocsolver_larfg(handle, n, (T*)nullptr, (T*)nullptr, inc, (T*)nullptr));

        size_t size;
        CHECK_ROCBLAS_ERROR(rocblas_stop_device_memory_size_query(handle, &size));
        if(argus.mem_query)
        {
            rocsolver_bench_inform(inform_mem_query, size);
            return;
        }

        CHECK_ROCBLAS_ERROR(rocblas_set_device_memory_size(handle, size));
    }

    // memory allocations
    host_strided_batch_vector<T> hx(size_x, inc, stx, 1);
    host_strided_batch_vector<T> hxr(size_xr, inc, stxr, 1);
    host_strided_batch_vector<T> ha(1, 1, 1, 1);
    host_strided_batch_vector<T> ht(1, 1, 1, 1);
    device_strided_batch_vector<T> dx(size_x, inc, stx, 1);
    device_strided_batch_vector<T> da(1, 1, 1, 1);
    device_strided_batch_vector<T> dt(1, 1, 1, 1);
    CHECK_HIP_ERROR(da.memcheck());
    if(size_x)
        CHECK_HIP_ERROR(dx.memcheck());
    CHECK_HIP_ERROR(dt.memcheck());

    // check quick return
    if(n == 0)
    {
        EXPECT_ROCBLAS_STATUS(rocsolver_larfg(handle, n, da.data(), dx.data(), inc, dt.data()),
                              rocblas_status_success);

        if(argus.timing)
            rocsolver_bench_inform(inform_quick_return);

        return;
    }

    // check computations
    if(argus.unit_check || argus.norm_check)
        larfg_getError<T>(handle, n, da, dx, inc, dt, ha, hx, hxr, ht, &max_error);

    // collect performance data
    if(argus.timing)
        larfg_getPerfData<T>(handle, n, da, dx, inc, dt, ha, hx, ht, &gpu_time_used, &cpu_time_used,
                             hot_calls, argus.profile, argus.profile_kernels, argus.perf);

    // validate results for rocsolver-test
    // using n * machine_precision as tolerance
    if(argus.unit_check)
        ROCSOLVER_TEST_CHECK(T, max_error, n);

    // output results for rocsolver-bench
    if(argus.timing)
    {
        if(!argus.perf)
        {
            rocsolver_bench_header("Arguments:");
            rocsolver_bench_output("n", "inc");
            rocsolver_bench_output(n, inc);

            rocsolver_bench_header("Results:");
            if(argus.norm_check)
            {
                rocsolver_bench_output("cpu_time_us", "gpu_time_us", "error");
                rocsolver_bench_output(cpu_time_used, gpu_time_used, max_error);
            }
            else
            {
                rocsolver_bench_output("cpu_time_us", "gpu_time_us");
                rocsolver_bench_output(cpu_time_used, gpu_time_used);
            }
            rocsolver_bench_endl();
        }
        else
        {
            if(argus.norm_check)
                rocsolver_bench_output(gpu_time_used, max_error);
            else
                rocsolver_bench_output(gpu_time_used);
        }
    }

    // ensure all arguments were consumed
    argus.validate_consumed();
}
