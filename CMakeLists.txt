cmake_minimum_required(VERSION 2.8.3)
project(benford)

if(UNIX)
  include_directories(/usr/include/mysql)
endif()

add_library(benford SHARED common.c chisq.c mstar.c max.c)
set_target_properties(benford PROPERTIES OUTPUT_NAME "benford" PREFIX "")

if(UNIX)
  set_target_properties(benford PROPERTIES COMPILE_FLAGS "-std=c99")
endif()
