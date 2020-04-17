
<img src="fstcore.png" align="right" height="196" width="196" />

[![Linux/OSX Build
Status](https://travis-ci.org/fstpackage/fstcore.svg?branch=develop)](https://travis-ci.org/fstpackage/fstcore)
[![Windows Build](https://ci.appveyor.com/api/projects/status/alg12npmm08564v6?svg=true)](https://ci.appveyor.com/project/fstpackage/fstcore)
[![License: AGPL
v3](https://img.shields.io/badge/License-AGPL%20v3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)
[![CRAN\_Status\_Badge](http://www.r-pkg.org/badges/version/fstcore)](https://cran.r-project.org/package=fstcore)
[![codecov](https://codecov.io/gh/fstpackage/fstcore/branch/develop/graph/badge.svg)](https://codecov.io/gh/fstpackage/fstcore)
[![downloads](http://cranlogs.r-pkg.org/badges/fstcore)](http://cran.rstudio.com/web/packages/fstcore/index.html)
[![total\_downloads](https://cranlogs.r-pkg.org/badges/grand-total/fstcore)](http://cran.rstudio.com/web/packages/fstcore/index.html)


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

Please refer to http://www.fstpackage.org/fst to get an introduction to using the `fst` package.


## Contact

Questions, ideas and issues can be best reported in the [fst package repository](https://github.com/fstpackage/fst).
