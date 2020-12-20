
## Submission

With version 0.9.6, the license of fstcore changes from AGPL version 3 to MPL version 2.

* ZSTD has been updated to version 1.4.5
* fstlib has been updated to version 0.1.6

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

## revdepcheck results

We checked 1 reverse dependencies, comparing R CMD check results across CRAN and dev versions of this package.

 * We saw 0 new problems
 * We failed to check 0 packages
