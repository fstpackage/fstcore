
## Submission

This release addresses build problems experienced by users with older compilers where assembler code in the
bundled ZSTD library is not compiled correctly. To avoid this problem on later releases, additional platforms
have been added to the test environment.

## Test environments 

* macOS 12.6.9 using R 4.3.2 and bundled ZSTD and LZ4 libs on github build infrastructure
* macOS 12.6.9 using R 4.3.2 and system ZSTD and LZ4 libs on github build infrastructure
* macOS 11.7.10 using R 4.3.2 and bundled ZSTD and LZ4 libs on github build infrastructure
* Ubuntu 20.04.5 LTS using R 3.6.3 with forced use of the bundled LZ4 and ZSTD libraries
* Microsoft Windows Server 2022 Datacenter using R dev (2023-11-28 r85645) on github build infrastructure
* Microsoft Windows Server 2022 Datacenter using R 4.2.3 on github build infrastructure
* Microsoft Windows Server 2022 Datacenter using R 3.6.3 on github build infrastructure
* Ubuntu 22.04.3 LTS using R dev (2023-11-27 r85642) on github build infrastructure
* Ubuntu 22.04.3 LTS using R dev (2023-11-27 r85642) with missing LZ4 and ZSTD libs on github build infrastructure
* Ubuntu 22.04.3 LTS using R 4.3.2 on github build infrastructure
* Ubuntu 20.04.5 LTS using R 3.6.3 on github build infrastructure
* Ubuntu 20.04.5 LTS using R 3.6.3 with forced use of the bundled LZ4 and ZSTD libraries
* Local Ubuntu with instrumented image using clang-10
* Windows 11 local R 4.3.2
* Rhub (all available systems)

## R CMD check results

There are no errors or warnings.

## revdepcheck results

We checked 2 reverse dependencies, comparing R CMD check results across CRAN and dev versions of this package.

 * We saw 0 new problems
 * We failed to check 0 packages
