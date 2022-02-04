
## Submission

This submission of fstcore (v0.9.8) addresses linking problems occurring on ARM OSX systems due to incorrect
configuration of Makevars as pointed out by Prof. Ripley.

In addition, the ZSTD library has been updated to version 1.5.2 and the LZ4 library has been updated to version 1.9.3.

## Test environments 

* macOS 11.6.2 20G314 using R 4.1.2 on github build infrastructure
* Ubuntu 20.04.3 LTS using R version 4.0.5 on github build infrastructure
* Ubuntu 20.04.3 LTS using R 4.1.2 on github build infrastructure
* Ubuntu 20.04.3 LTS using R dev (2022-01-30 r81596) on github build infrastructure
* Microsoft Windows Server 2019 10.0.17763 Datacenter using R 4.1.2 on github build infrastructure
* Ubuntu 18.04 locally using clang-10.0
* Docker with the rocker/r-devel-ubsan-clang instrumented image
* Local Ubuntu with instrumented image using clang-10
* Windows 10 local R 3.6.3
* Singularity-container package for running rchk on Ubuntu 18.04
* Valgrind on Ubuntu 18.04
* Rhub (all available systems)

## R CMD check results

There are no errors or warnings.

## revdepcheck results

We checked 1 reverse dependencies, comparing R CMD check results across CRAN and dev versions of this package.

 * We saw 0 new problems
 * We failed to check 0 packages
