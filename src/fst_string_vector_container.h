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


#ifndef STRING_VECTOR_CONTAINER_H
#define STRING_VECTOR_CONTAINER_H


#include <stdexcept>
#include <memory>

#include <Rcpp.h>

#include <interface/fstdefines.h>


// Class is meant for smaller character vectors that need protection from garbage collection

class StringVectorContainer : public IStringColumn
{
  SEXP container;  // make sure the contained object is PROTECTED
  std::unique_ptr<BlockReaderChar> str_vector_p;

public:
  StringVectorContainer(SEXP container_list)
  {
    container = container_list;
  }

  ~StringVectorContainer(){}

  void AllocateVec(uint64_t vecLength)
  {
    str_vector_p = std::unique_ptr<BlockReaderChar>(new BlockReaderChar());  // unprotected SEXP
    BlockReaderChar* block_reader = str_vector_p.get();

    // allocate
    block_reader->AllocateVec(vecLength);

    // make sure vector is protected
    SEXP str_vec = block_reader->StrVector();
    SET_VECTOR_ELT(container, 0, str_vec);
  }

  StringEncoding GetEncoding()
  {
    return str_vector_p.get()->GetEncoding();
  }

  void SetEncoding(StringEncoding fst_string_encoding)
  {
    str_vector_p.get()->SetEncoding(fst_string_encoding);
  }

  void BufferToVec(uint64_t nrOfElements, uint64_t startElem, uint64_t endElem,
    uint64_t vecOffset, unsigned int* sizeMeta, char* buf)
  {
    str_vector_p.get()->BufferToVec(nrOfElements, startElem, endElem, vecOffset, sizeMeta, buf);
  }

  const char* GetElement(uint64_t elementNr)
  {
    return str_vector_p.get()->GetElement(elementNr);
  }

  SEXP StrVector()
  {
    return VECTOR_ELT(container, 0);
  }
};


#endif  // STRING_VECTOR_CONTAINER_H
