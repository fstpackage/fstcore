
## Submission

This submission of fstcore (v0.9.14) addresses build problems on systems using gcc 13 due to missing <cstdint>
includes. With thanks to Prof. Ripley for identifying the problem and offering pointers to the solution.

## Test environments 

* macOS 12.6.2 using R 4.2.2 and bundled ZSTD and LZ4 libs on github build infrastructure
* macOS 12.6.2 using R 4.2.2 and system ZSTD and LZ4 libs on github build infrastructure
* Microsoft Windows Server 2022 Datacenter using R 4.2.2 on github build infrastructure
* Microsoft Windows Server 2022 Datacenter using R 4.1.3 on github build infrastructure

* Ubuntu 20.04.5 LTS using R 4.0.5 on github build infrastructure
* Ubuntu 20.04.5 LTS using R 4.1.3 on github build infrastructure
* Ubuntu 20.04.5 LTS using R dev (2023-01-10 r83596) on github build infrastructure
* Ubuntu 20.04.5 LTS using R dev (2023-01-10 r83596) with missing LZ4 and ZSTD libs on github build infrastructure
* Ubuntu 20.04.5 LTS using R 4.2.2 on github build infrastructure
* Ubuntu 18.04.6 LTS using R 3.5.3 on github build infrastructure
* Local Ubuntu with instrumented image using clang-10
* Windows 11 local R 3.6.3
* Windows 11 local R 4.1.3
* Windows 11 local R 4.2.2
* Rhub (all available systems)

## R CMD check results

There are no errors or warnings.

## revdepcheck results

We checked 2 reverse dependencies, comparing R CMD check results across CRAN and dev versions of this package.

 * We saw 0 new problems
 * We failed to check 0 packages
