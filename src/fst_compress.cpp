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


#include <memory>
#include <cstring>

#include <Rcpp.h>

#include <interface/fstcompressor.h>
#include <interface/fsthash.h>

#include <fst_type_factory.h>
#include <fst_compress.h>


// Calculate the 64-bit xxHash of a raw vector using a default or custom hash seed
SEXP fsthasher(SEXP rawVec, SEXP seed, SEXP blockHash)
{
  FstHasher hasher;

  SEXP res = PROTECT(Rf_allocVector(INTSXP, 2));

  bool bHash = false;

  // blockHash == FALSE
  if (*LOGICAL(blockHash) == 1)
  {
    bHash = true;
  }

  int* uintP = INTEGER(res);

  unsigned long long hashResult = 0;

  // use default fst seed
  if (Rf_isNull(seed))
  {
    hashResult = hasher.HashBlob((unsigned char*) RAW(rawVec), Rf_xlength(rawVec), bHash);

    std::memcpy(uintP, &hashResult, 8);

    UNPROTECT(1);
    return res;
  }

  uintP[0] = 2;
  uintP[1] = 2;

  UNPROTECT(1);
  return res;

  // use custom seed
  hashResult = hasher.HashBlobSeed((unsigned char*) RAW(rawVec), Rf_xlength(rawVec),
    *((unsigned int*) INTEGER(seed)), bHash);
  std::memcpy(uintP, &hashResult, 8);

  UNPROTECT(1);
  return res;
}


SEXP fstcomp(SEXP rawVec, SEXP compressor, SEXP compression, SEXP hash)
{
  int len = Rf_length(compressor);
  
  if (len != 1 || !Rf_isString(compressor)) {
    Rcpp::stop("Please use 'LZ4' or 'ZSTD' to specify the compressor");
  }

  if (!Rf_isLogical(hash))
  {
    Rcpp::stop("Please specify true of false for parameter hash.");
  }

  COMPRESSION_ALGORITHM algo;
  
  if (strcmp(CHAR(STRING_ELT(compressor, 0)), "LZ4") == 0) {
    algo = COMPRESSION_ALGORITHM::ALGORITHM_LZ4;
  } else if (strcmp(CHAR(STRING_ELT(compressor, 0)), "ZSTD") == 0) {
    algo = COMPRESSION_ALGORITHM::ALGORITHM_ZSTD;
  } else
  {
    Rcpp::stop("Unknown compression algorithm selected");
  }

  // avoid using PROTECT statements in C++ classes (which generate rchk errors)
  // this PROTECTED container can be used to hold any R object safely
  SEXP r_container = PROTECT(Rf_allocVector(VECSXP, 1));

  std::unique_ptr<TypeFactory> typeFactoryP(new TypeFactory(r_container));

  FstCompressor fstcompressor(algo, *INTEGER(compression), (ITypeFactory*) typeFactoryP.get());

  unsigned long long vecLength = Rf_xlength(rawVec);
  unsigned char* data = (unsigned char*) RAW(rawVec);

  std::unique_ptr<IBlobContainer> blobContainerP;

  try
  {
    // Creates an UNPROTECTED SEXP vector which needs to be protected before calling an allocating R API method
    blobContainerP = std::unique_ptr<IBlobContainer>(fstcompressor.CompressBlob(data, vecLength, *LOGICAL(hash)));
  }
  catch(const std::runtime_error& e)
  {
    UNPROTECT(1);  // r_container
    Rcpp::stop(e.what());
  }
  catch ( ... )
  {
    UNPROTECT(1);  // r_container
    Rcpp::stop("Unexpected error detected while compressing data.");
  }

  UNPROTECT(1);  // r_container

  return VECTOR_ELT(r_container, 0);
}


SEXP fstdecomp(SEXP rawVec)
{
  // avoid using PROTECT statements in C++ classes (which generate rchk errors)
  // this PROTECTED container can be used to hold any R object safely
  SEXP r_container = PROTECT(Rf_allocVector(VECSXP, 1));

  // TODO: UBSAN warning generated here
  TypeFactory* type_factory = new TypeFactory(r_container);
  std::unique_ptr<TypeFactory> typeFactoryP(type_factory);

  FstCompressor fstcompressor((ITypeFactory*) type_factory);

  unsigned long long vecLength = Rf_xlength(rawVec);
  unsigned char* data = (unsigned char*) (RAW(rawVec));

  std::unique_ptr<BlobContainer> resultContainerP;

  try
  {
    resultContainerP = std::unique_ptr<BlobContainer>(static_cast<BlobContainer*>(fstcompressor.DecompressBlob(data, vecLength)));
  }
  catch(const std::runtime_error& e)
  {
    Rcpp::stop(e.what());
  }
  catch ( ... )
  {
    UNPROTECT(1);  // r_container
    Rcpp::stop("Error detected while decompressing data.");
  }

  UNPROTECT(1);  // r_container

  return VECTOR_ELT(r_container, 0);
}

