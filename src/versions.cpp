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


#include <cstring>
#include <Rcpp.h>

#include <zstd.h>
#include <lz4.h>
#include <interface/fstdefines.h>

using namespace Rcpp;

// [[Rcpp::export]]
SEXP library_versions()
{
  List retList = List::create(
    _["zstd"] = std::to_string(ZSTD_VERSION_MAJOR) + "." + std::to_string(ZSTD_VERSION_MINOR) + "." +
      std::to_string(ZSTD_VERSION_RELEASE),
    _["lz4"]  = std::to_string(LZ4_VERSION_MAJOR) + "." + std::to_string(LZ4_VERSION_MINOR) + "." +
      std::to_string(LZ4_VERSION_RELEASE),
    _["fstlib"]  = std::to_string(FST_VERSION_MAJOR) + "." + std::to_string(FST_VERSION_MINOR) + "." +
      std::to_string(FST_VERSION_RELEASE)
  );

  return retList;
}
