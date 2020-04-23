
## Resubmission

In this resubmission of package fstcore, I've corrected quotes in the Title and Description fields and added some
executable examples in the documentation. Also, Yuta Mori was added as copyright holder for the libdivsufsort-lite
code bundled with ZSTD.

## Submission

This is the first submission of package fstcore. This package contains the R bindings to the fstlib library and the
sources of the LZ4 and ZSTD compression libraries. The C++ code in this package is an almost exact duplicate of the
C++ code that is contained in v0.9.2 of the fst package. The rational for moving the core C++ binding of the fst
package into a separate package is better maintainability.  With this split, the C++ components can be updated
independently from the fst package.


## Test environments 

* OSX on travis-ci (version 10.13.6)
* Ubuntu Ubuntu 16.04.6 LTS on travis-ci
* Ubuntu 19.10 locally
* Ubuntu 19.10 locally using clang-6
* Docker with the rocker/r-devel-ubsan-clang instrumented image
* Local Ubuntu with instrumented image using clang-10
* Windows 10 local R 3.6.4
* Windows 10 local R-dev 4.0.0 pre-release (r77640)
* Windows Server 2012 R2 x64 (build 9600) on AppVeyor (R 3.6.3)
* Valgrind on Ubuntu 19.10
* Rhub (all available systems)

## R CMD check results

There are no errors or warnings.

## Downstream dependencies

There are currently no downstream dependencies.
