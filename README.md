
<img src="man/figures/fstcore.png" align="right" height="196" width="196" />

<!-- badges: start -->
  [![CRAN status](https://cranchecks.info/badges/flavor/release/fstcore/)](https://cran.r-project.org/web/checks/check_results_fstcore.html)
  [![CRAN\_Status\_Badge](https://www.r-pkg.org/badges/version/fstcore)](https://cran.r-project.org/package=fstcore)
  [![downloads](https://cranlogs.r-pkg.org/badges/fstcore)](https://cran.r-project.org/package=fstcore)
  [![total\_downloads](https://cranlogs.r-pkg.org/badges/grand-total/fstcore)](https://cran.r-project.org/package=fstcore)

  [![Build Status](https://github.com/fstpackage/fstcore/actions/workflows/R-CMD-check.yaml/badge.svg?branch=develop)](https://github.com/fstpackage/fstcore/actions/workflows/R-CMD-check.yaml)
  [![codecov](https://codecov.io/gh/fstpackage/fstcore/branch/develop/graph/badge.svg)](https://app.codecov.io/gh/fstpackage/fstcore)
<!-- badges: end -->

[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://opensource.org/licenses/MPL-2.0/)


## Overview

R package `fstcore` contains R bindings to the C++ `fstlib` library which allows interfacing with _fst_ files.
It also contains the `LZ4` and `ZSTD` sources used for compression. `fstcore` exists as a package separate from the
`fst` package to facilitate independent updates to the `fstlib`, `LZ4` and `ZSTD` libraries and is used as a
backend to `fst`.


## Installation

Package `fstcore` is automatically installed as a dependency when you install the `fst` package from CRAN.
If you need to install it directly, you can use:

``` r
install.packages("fstcore")
```

You can also use the development version from GitHub:

``` r
# install.packages("devtools")
devtools::install_github("fstpackage/fstcore", ref = "develop")
```

## Basic usage

Please refer to https://www.fstpackage.org/fst to get an introduction to using the `fst` package.


## Contact

Questions, ideas and issues can be reported in the [fst package repository](https://github.com/fstpackage/fst).
