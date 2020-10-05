/*
  fstcore - R bindings to the fstlib library

  Copyright (C) 2017-present, Mark AJ Klik

  This file is part of the fstcore R package.

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this file,
  You can obtain one at https://mozilla.org/MPL/2.0/.

  https://www.mozilla.org/en-US/MPL/2.0/FAQ/

  You can contact the author at:
  - fstcore R package source repository : https://github.com/fstpackage/fstcore
*/


#ifndef FASTSTORE_H
#define FASTSTORE_H

// [[Rcpp::interfaces(r, cpp)]]

#include <Rcpp.h>


// [[Rcpp::export(rng = false)]]
int fstlib_version();


// [[Rcpp::export(rng = false)]]
SEXP fststore(Rcpp::String fileName, SEXP table, SEXP compression, SEXP uniformEncoding);


// [[Rcpp::export(rng = false)]]
SEXP fstmetadata(Rcpp::String fileName);


// [[Rcpp::export(rng = false)]]
SEXP fstretrieve(Rcpp::String fileName, SEXP columnSelection, SEXP startRow, SEXP endRow);


#endif  // FASTSTORE_H
