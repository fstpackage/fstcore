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


#ifndef FSTCOMPRESS_H
#define FSTCOMPRESS_H

// [[Rcpp::interfaces(cpp)]]

#include <Rcpp.h>


// [[Rcpp::export(rng = false)]]
SEXP fsthasher(SEXP rawVec, SEXP seed, SEXP blockHash);


// [[Rcpp::export(rng = false)]]
SEXP fstcomp(SEXP rawVec, SEXP compressor, SEXP compression, SEXP hash);


// [[Rcpp::export(rng = false)]]
SEXP fstdecomp(SEXP rawVec);


#endif  // FASTSTORE_H
