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


#ifndef BLOCKRUNNER_CHAR_H
#define BLOCKRUNNER_CHAR_H


#include <stdexcept>
#include <memory>

#include <Rcpp.h>

#include <interface/fstdefines.h>


class BlockWriterChar : public IStringWriter
{
  SEXP* strVec;
  unsigned int stackBufSize;
  unsigned int heapBufSize;
  int uniformEncoding;

  std::unique_ptr<char[]> heapBuf;

  // Buffers for blockRunner (make these local !!!!)
  unsigned int naInts_buf[1 + BLOCKSIZE_CHAR / 32];  // we have 32 NA bits per integer
  unsigned int strSizes_buf[BLOCKSIZE_CHAR];  // we have 32 NA bits per integer
  char buf[MAX_CHAR_STACK_SIZE];

  public:
    BlockWriterChar(SEXP &strVec, uint64_t vecLength, unsigned int stackBufSize, int uniformEncoding);

    ~BlockWriterChar();

    StringEncoding Encoding()
    {
      // Get first non-NA element and set encoding accordingly
      // This is expensive for vectors with lots of NA's at the start
      cetype_t encoding = cetype_t::CE_NATIVE;  // default
      unsigned int pos;
      for (pos = 0; pos < this->vecLength; pos++)
      {
        SEXP strElem = STRING_ELT(*strVec, pos);
        if (strElem != NA_STRING)  // set NA bit
        {
          encoding = Rf_getCharCE(strElem);
          break;
        }
      }

      // check remaining vector for elements with different encoding
      if (!uniformEncoding)
      {
        for (; pos < this->vecLength; pos++)
        {
          SEXP strElem = STRING_ELT(*strVec, pos);
          if (strElem != NA_STRING)  // set NA bit
          {
            cetype_t nextEncoding = Rf_getCharCE(strElem);
            if (nextEncoding != encoding)
            {
              throw(std::runtime_error("Character vectors with mixed encodings are currently not supported"));
            }
          }
        }
      }

      switch (encoding)
      {
        case cetype_t::CE_LATIN1:
          return StringEncoding::LATIN1;

        case cetype_t::CE_UTF8:
          return StringEncoding::UTF8;

        default:
          return StringEncoding::NATIVE;
      }
    }

    void SetBuffersFromVec(uint64_t startCount, uint64_t endCount);
};


class BlockReaderChar : public IStringColumn
{
  SEXP strVec;
  // bool isProtected;
  cetype_t strEncoding;
  StringEncoding string_encoding = StringEncoding::NATIVE;

public:
  BlockReaderChar()
  {
    // isProtected = false;
  }

  ~BlockReaderChar(){}

  // make sure strVec is PROTECTED after creation
  void AllocateVec(uint64_t vecLength);

  StringEncoding GetEncoding()
  {
    return string_encoding;
  }

  void SetEncoding(StringEncoding fst_string_encoding)
  {
    string_encoding = fst_string_encoding;

    switch (fst_string_encoding)
    {
      case StringEncoding::LATIN1:
      {
        strEncoding = cetype_t::CE_LATIN1;
        break;
      }

      case StringEncoding::UTF8:
      {
        strEncoding = cetype_t::CE_UTF8;
        break;
      }

      default:  // native or unknown encoding
        strEncoding = cetype_t::CE_NATIVE;
        break;
    }
  }

  void BufferToVec(uint64_t nrOfElements, uint64_t startElem, uint64_t endElem,
    uint64_t vecOffset, unsigned int* sizeMeta, char* buf);

  const char* GetElement(uint64_t elementNr)
  {
    return CHAR(STRING_ELT(strVec, elementNr));
  }

  SEXP StrVector() { return strVec; }
};



#endif  // BLOCKRUNNER_CHAR_H
