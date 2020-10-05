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


#ifndef OPEN_MP_H
#define OPEN_MP_H

// [[Rcpp::interfaces(r, cpp)]]

#include <Rcpp.h>


// [[Rcpp::export(rng = false)]]
SEXP getnrofthreads();


// [[Rcpp::export(rng = false)]]
int setnrofthreads(SEXP nrOfThreads);


// [[Rcpp::export(rng = false)]]
SEXP hasopenmp();


// [[Rcpp::export(rng = false)]]
void restore_after_fork(bool restore);


// [[Rcpp::export(rng = false)]]
bool is_forked();


// [[Rcpp::init]]
int avoid_openmp_hang_within_fork(DllInfo *dll);


#endif  // OPEN_MP_H
