
## Submission

This release addresses build problems using the g++ 15 compiler where the <cstdint> header is reported missing.
Also, the bundled LZ4 and ZSTD libraries have been updated to the latest versions.

## R CMD check results

There are no errors or warnings.

## revdepcheck results

We checked 2 reverse dependencies, comparing R CMD check results across CRAN and dev versions of this package.

 * We saw 0 new problems
 * We failed to check 0 packages

## Test environments 

* Debian unstable using gcc-snapshot 15.0.0 20241220 (experimental)
* macOS 14.7.2 23H311 using R 4.4.2 and bundled ZSTD and LZ4 libs on github build infrastructure
* macOS 14.7.2 23H311 using R 4.4.2 and system ZSTD and LZ4 libs on github build infrastructure
* macOS 11.7.10 using R 4.4.2 and bundled ZSTD and LZ4 libs
* Microsoft Windows Server 2022 10.0.20348 Datacenter using R 4.4.2
* Microsoft Windows Server 2022 10.0.20348 Datacenter using R Under development (unstable) (2025-02-06 r87702 ucrt)
* Microsoft Windows Server 2022 Datacenter using R version 3.6.3 (2020-02-29)
* Ubuntu 24.04.1 LTS using R 3.6.3 with forced use of the bundled LZ4 and ZSTD libraries
* Ubuntu 24.04.1 LTS using R Under development (unstable) (2025-02-03 r87683)
* Ubuntu 24.04.1 LTS using R Under development (unstable) (2025-02-03 r87683) with missing LZ4 and ZSTD libs
* Ubuntu 20.04.6 LTS using R version 4.0.5 (2021-03-31)
* Ubuntu 20.04.6 LTS using R version 4.0.5 (2021-03-31) with forced use of the bundled LZ4 and ZSTD libraries
* Windows 11 local R 4.4.2
* All container images provided through Rhub (including valgrind, clang20, clang ubsan/asan)
