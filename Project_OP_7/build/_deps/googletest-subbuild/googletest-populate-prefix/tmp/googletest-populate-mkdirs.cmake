# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Study/OP/Project_OP_7/labwork7-BEE-kg/build/_deps/googletest-src")
  file(MAKE_DIRECTORY "C:/Study/OP/Project_OP_7/labwork7-BEE-kg/build/_deps/googletest-src")
endif()
file(MAKE_DIRECTORY
  "C:/Study/OP/Project_OP_7/labwork7-BEE-kg/build/_deps/googletest-build"
  "C:/Study/OP/Project_OP_7/labwork7-BEE-kg/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "C:/Study/OP/Project_OP_7/labwork7-BEE-kg/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "C:/Study/OP/Project_OP_7/labwork7-BEE-kg/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "C:/Study/OP/Project_OP_7/labwork7-BEE-kg/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "C:/Study/OP/Project_OP_7/labwork7-BEE-kg/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Study/OP/Project_OP_7/labwork7-BEE-kg/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Study/OP/Project_OP_7/labwork7-BEE-kg/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
