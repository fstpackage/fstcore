
## Submission


This submission of fstcore (v0.9.14) addresses build problems on systems using gcc 13 due to missing <cstdint>
includes. With thanks to Prof. Ripley for identifying the problem and offering pointers to the solution.


## Test environments 

* MacOS 11.6.2 20G314 using R 4.1.3 on github build infrastructure
* Ubuntu 20.04.3 LTS using R 4.0.5 on github build infrastructure
* Ubuntu 20.04.3 LTS using R 4.1.3 on github build infrastructure
* Ubuntu 20.04.3 LTS using R dev (2022-01-30 r81596) on github build infrastructure
* Microsoft Windows Server 2019 10.0.17763 Datacenter using R4.1.3 on github build infrastructure
* Ubuntu 18.04 locally using clang-10.0
* Docker with the rocker/r-devel-ubsan-clang instrumented image
* Local Ubuntu with instrumented image using clang-10
* Windows 11 local R 3.6.3
* Windows 11 local R 4.1.3
* Windows 11 local R 4.2.2
* Singularity-container package for running rchk on Ubuntu 18.04
* Valgrind on Ubuntu 18.04
* Rhub (all available systems)

## R CMD check results

There are no errors or warnings.

## revdepcheck results

We checked 2 reverse dependencies, comparing R CMD check results across CRAN and dev versions of this package.

 * We saw 0 new problems
 * We failed to check 0 packages
