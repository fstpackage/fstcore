

# fstcore 0.9.17 (in development)


# fstcore 0.9.16 (2023-11-29)

This release addresses build problems on systems using clang version 16 or above due to the use of string literals
in RcppExports.cpp. With thanks to CRAN for identifying the problem and Prof. Eddelbuettel for providing a fix in
the Rcpp package.

## Library updates

* `ZSTD` has been updated to version 1.5.5


# fstcore 0.9.14 (2023-01-12)

This release addresses build problems on systems using gcc 13 due to missing <cstdint> includes. With thanks to
Prof. Ripley for identifying the problem and offering pointers to the solution.

## Library updates

* `LZ4` has been updated to version 1.9.4


# fstcore 0.9.12 (2022-03-23)

This release adds a fallback mechanism for systems that fail the configure script. When systems packages LZ4 or
ZSTD are missing and configuration fails, the bundled code is used to build the package.


# fstcore 0.9.10 (2022-03-21)

This release adds a configure script to the package that checks for the availability of system packages lz4, zstd and
xxhash. When available, these system packages are used instead of compiling code directly from the package sources.


# fstcore 0.9.8 (2022-02-04)

This release addresses linking problems occurring on ARM OSX systems due to incorrect configuration of Makevars.
With thanks to Prof. Ripley for identifying the problem and offering pointers for the solution.

## Library updates

* `ZSTD` has been updated to version 1.5.2
* `LZ4` has been updated to version 1.9.3


# fstcore 0.9.6 (2021-01-05)

With version 0.9.6, the license of `fstcore` changes from AGPL version 3 to MPL version 2. This allows for less
restrictive use of the `fstcore` package. In particular, closed-source (commercial) solutions can now use `fstcore`
(call it's API), as was impossible under AGPL (under AGPL, products can only use `fstcore` if they make the products
source code available under AGPL or more restrictive license).

## Library updates

* `ZSTD` has been updated to version 1.4.5
* `fstlib` has been updated to version 0.1.6

## Enhancements

* Numeric values can now be used to select a row range, including values larger than 2^31 to select a subset from
long vector columns (thanks @dipterix for reporting)
* The random seed is not initialized anymore when `fstcore` is loaded (see [fst#251](https://github.com/fstpackage/fst/issues/251), thanks @mlell for investigating and @riccardoporreca for providing the solution)


# fstcore 0.9.4 (2020-05-04)

R package `fstcore`contains the R bindings to the C++ fstlib library needed to interface with _fst_ files as well as
the LZ4 and ZSTD sources. It was developed as a package separate from the fst package to facilitate independent
updates to the fstlib, LZ4 and ZSTD libraries.
