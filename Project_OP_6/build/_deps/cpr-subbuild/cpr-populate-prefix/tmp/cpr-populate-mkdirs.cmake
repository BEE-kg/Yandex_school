# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/build/_deps/cpr-src")
  file(MAKE_DIRECTORY "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/build/_deps/cpr-src")
endif()
file(MAKE_DIRECTORY
  "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/build/_deps/cpr-build"
  "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/build/_deps/cpr-subbuild/cpr-populate-prefix"
  "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/build/_deps/cpr-subbuild/cpr-populate-prefix/tmp"
  "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/build/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp"
  "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/build/_deps/cpr-subbuild/cpr-populate-prefix/src"
  "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/build/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/build/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Study/OP/Project_OP_6/labwork6-BEE-kg/build/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
