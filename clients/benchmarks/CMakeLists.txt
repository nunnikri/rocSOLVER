# ########################################################################
# Copyright (c) 2016-2021 Advanced Micro Devices, Inc.
# ########################################################################

add_executable(rocsolver-bench client.cpp)

add_armor_flags(rocsolver-bench "${ARMOR_LEVEL}")

target_link_libraries(rocsolver-bench PRIVATE
  cblas
  lapack
  blas
  Threads::Threads
  hip::device
  rocsolver-common
  clients-common
  roc::rocsolver
)

# Turn on f16c intrinsics
target_compile_options(rocsolver-bench PRIVATE -mf16c)
target_compile_definitions(rocsolver-bench PRIVATE
  ROCM_USE_FLOAT16
  ROCSOLVER_CLIENTS_BENCH
)

rocm_install(TARGETS rocsolver-bench COMPONENT benchmarks)
