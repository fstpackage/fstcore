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


#include <Rcpp.h>

#include <interface/openmphelper.h>

#ifdef _OPENMP
#include <pthread.h>
#endif


static int fst_threads_at_fork = 1;
static bool restore_threads_after_fork = true;
static bool forked = false;


SEXP getnrofthreads()
{
  return Rf_ScalarInteger(GetFstThreads());
}


int setnrofthreads(SEXP nrOfThreads)
{
  SEXP intVal = Rf_coerceVector(nrOfThreads, INTSXP);

  if (!Rf_isInteger(intVal) || Rf_length(intVal) != 1 || INTEGER(intVal)[0] < 0)
  {
    // catches NA too since NA is -ve
    Rcpp::stop("Argument to threads_fst must be a single integer >= 0, default 0 is recommended to use all cores");
  }

  return ThreadsFst(*INTEGER(intVal));
}


void restore_after_fork(bool restore)
{
  restore_threads_after_fork = restore;
}

// Folowing code was adopted from package data.table:
// TODO: implement in fstcore to guard against forking issues with OpenMP

void when_fork()
{
  // use call to fstlib that does not call any OpenMP library functions internally
  fst_threads_at_fork = GetThreads();
  forked = true;

  SetThreads(1);
}


void when_unfork()
{
  // use call to fstlib that does not call any OpenMP library functions internally
  if (restore_threads_after_fork)
  {
    SetThreads(fst_threads_at_fork);
  }
  
  forked = false;
}


bool is_forked()
{
  return forked;
}


int avoid_openmp_hang_within_fork(DllInfo *dll)
{
  // Called once on loading package
#ifdef _OPENMP
  return pthread_atfork(&when_fork, &when_unfork, NULL);
#endif

  return 0;
}


SEXP hasopenmp()
{
  return Rf_ScalarLogical(HasOpenMP());
}

