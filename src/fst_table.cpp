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

#include <interface/ifsttable.h>
#include <interface/istringwriter.h>
#include <interface/fstdefines.h>

#include <fst_blockrunner_char.h>
#include <fst_column.h>
#include <fst_table.h>

using namespace Rcpp;


FstTable::FstTable(SEXP &table, int uniformEncoding, SEXP r_container)
{
  this->r_container = r_container;
  this->rTable = &table;
  this->nrOfCols = 0;
  this->uniformEncoding = uniformEncoding;
}


uint32_t FstTable::NrOfColumns()
{
  if (nrOfCols == 0)
  {
    nrOfCols = Rf_length(*rTable);
  }

  return nrOfCols;
}


uint64_t FstTable::NrOfRows()
{
  if (nrOfCols == 0)  // table has zero columns
  {
    nrOfCols = Rf_length(*rTable);

    if (nrOfCols == 0) return 0;  // table has zero columns and rows
  }

  SEXP colVec = VECTOR_ELT(*rTable, 0);  // retrieve column vector
  return XLENGTH(colVec);
}


FstColumnType FstTable::ColumnType(uint32_t colNr, FstColumnAttribute &columnAttribute, short int &scale,
  std::string &annotation, bool &hasAnnotation)
{
  SEXP colVec = VECTOR_ELT(*rTable, colNr);  // retrieve column vector
  hasAnnotation = false;

  switch (TYPEOF(colVec))
  {
    case STRSXP:
      columnAttribute = FstColumnAttribute::CHARACTER_BASE;
      return FstColumnType::CHARACTER;

    case INTSXP:
      if (Rf_inherits(colVec, "difftime"))
      {
        columnAttribute = FstColumnAttribute::INT_32_TIMEINTERVAL_SECONDS;

        // Convert units
        SEXP units = Rf_getAttrib(colVec, Rf_install("units"));
        std::string unit = std::string(CHAR(STRING_ELT(units, 0)));

        if (unit == "secs")
        {
          scale = FstTimeScale::SECONDS;
        }
        else if (unit == "mins")
        {
          scale = FstTimeScale::MINUTES;
        }
        else if (unit == "hours")
        {
          scale = FstTimeScale::HOURS;
        }
        else if (unit == "days")
        {
          scale = FstTimeScale::DAYS;
        }
        else
        {
          Rf_warning("Unknown time unit, defaulting to seconds");
          scale = FstTimeScale::SECONDS;
        }

        return FstColumnType::INT_32;
      }

      if (Rf_isFactor(colVec))  // factor
      {
        if (Rf_inherits(colVec, "ordered"))
        {
          columnAttribute = FstColumnAttribute::FACTOR_ORDERED;
          return FstColumnType::FACTOR;
        }

        columnAttribute = FstColumnAttribute::FACTOR_BASE;
        return FstColumnType::FACTOR;
      }

      if (Rf_inherits(colVec, "Date"))
      {
        columnAttribute = FstColumnAttribute::INT_32_DATE_DAYS;
        return FstColumnType::INT_32;
      }

      if (Rf_inherits(colVec, "ITime"))
      {
        columnAttribute = FstColumnAttribute::INT_32_TIME_OF_DAY_SECONDS;
        scale = FstTimeScale::SECONDS;
        return FstColumnType::INT_32;
      }

      if (Rf_inherits(colVec, "POSIXct"))
      {
        hasAnnotation = false;
        columnAttribute = FstColumnAttribute::INT_32_TIMESTAMP_SECONDS;

        SEXP tzoneR = Rf_getAttrib(colVec, Rf_install("tzone"));

        if (!Rf_isNull(tzoneR))
        {
          hasAnnotation = true;
          annotation += Rf_translateCharUTF8(STRING_ELT(tzoneR, 0));
        }

        return FstColumnType::INT_32;
      }

      columnAttribute = FstColumnAttribute::INT_32_BASE;
      return FstColumnType::INT_32;

    case REALSXP:
      if (Rf_inherits(colVec, "ITime"))
      {
        columnAttribute = FstColumnAttribute::DOUBLE_64_TIME_OF_DAY_SECONDS;
        scale = FstTimeScale::SECONDS;
        return FstColumnType::DOUBLE_64;
      }

      if (Rf_inherits(colVec, "difftime"))
      {
        columnAttribute = FstColumnAttribute::DOUBLE_64_TIMEINTERVAL_SECONDS;

        // Convert units
        SEXP units = Rf_getAttrib(colVec, Rf_install("units"));
        std::string unit = std::string(CHAR(STRING_ELT(units, 0)));

        if (unit == "secs")
        {
          scale = FstTimeScale::SECONDS;
        }
        else if (unit == "mins")
        {
          scale = FstTimeScale::MINUTES;
        }
        else if (unit == "hours")
        {
          scale = FstTimeScale::HOURS;
        }
        else if (unit == "days")
        {
          scale = FstTimeScale::DAYS;
        }
        else
        {
          Rf_warning("Unknown time unit, defaulting to seconds");
          scale = FstTimeScale::SECONDS;
        }

        return FstColumnType::DOUBLE_64;
      }

      if (Rf_inherits(colVec, "Date"))
      {
        columnAttribute = FstColumnAttribute::DOUBLE_64_DATE_DAYS;
        return FstColumnType::DOUBLE_64;
      }

      if (Rf_inherits(colVec, "POSIXct"))
      {
        hasAnnotation = false;
        columnAttribute = FstColumnAttribute::DOUBLE_64_TIMESTAMP_SECONDS;

        SEXP tzoneR = Rf_getAttrib(colVec, Rf_install("tzone"));

        if (!Rf_isNull(tzoneR))
        {
          hasAnnotation = true;
          annotation += Rf_translateCharUTF8(STRING_ELT(tzoneR, 0));
        }

        return FstColumnType::DOUBLE_64;
      }

      if (Rf_inherits(colVec, "nanotime"))
      {
        columnAttribute = FstColumnAttribute::INT_64_TIME_SECONDS;

        scale = FstTimeScale::NANOSECONDS;  // set scale to nanoseconds

        return FstColumnType::INT_64;
      }

      if (Rf_inherits(colVec, "integer64"))
      {
        columnAttribute = FstColumnAttribute::INT_64_BASE;
        return FstColumnType::INT_64;
      }

      columnAttribute = FstColumnAttribute::DOUBLE_64_BASE;
      return FstColumnType::DOUBLE_64;

    case LGLSXP:
      columnAttribute = FstColumnAttribute::BOOL_2_BASE;
      return FstColumnType::BOOL_2;

    case RAWSXP:
      columnAttribute = FstColumnAttribute::BYTE_BASE;
      return FstColumnType::BYTE;

    default:
      columnAttribute = FstColumnAttribute::NONE;
      return FstColumnType::UNKNOWN;
  }
}


int* FstTable::GetLogicalWriter(uint32_t colNr)
{
  cols = VECTOR_ELT(*rTable, colNr);  // retrieve column vector
  return LOGICAL(cols);
}


long long* FstTable::GetInt64Writer(uint32_t colNr)
{
  cols = VECTOR_ELT(*rTable, colNr);  // retrieve column vector (no copy?)

  // Convert doubles to long integer type
  return (long long*) (REAL(cols));
}


int* FstTable::GetIntWriter(uint32_t colNr)
{
  cols = VECTOR_ELT(*rTable, colNr);  // retrieve column vector
  return INTEGER(cols);
}


char* FstTable::GetByteWriter(uint32_t colNr)
{
  cols = VECTOR_ELT(*rTable, colNr);  // retrieve column vector
  return (char*) RAW(cols);
}


double* FstTable::GetDoubleWriter(uint32_t colNr)
{
  cols = VECTOR_ELT(*rTable, colNr);  // retrieve column vector
  return REAL(cols);
}


IByteBlockColumn* FstTable::GetByteBlockWriter(uint32_t col_nr){
  return nullptr;
}


IStringWriter* FstTable::GetStringWriter(uint32_t colNr)
{
  cols = VECTOR_ELT(*rTable, colNr);  // retrieve column vector

  // Assuming that nrOfRows is already set
  uint32_t nrOfVectorRows = LENGTH(cols);

  return new BlockWriterChar(cols, nrOfVectorRows, MAX_CHAR_STACK_SIZE, uniformEncoding);
}


IStringWriter* FstTable::GetLevelWriter(uint32_t colNr)
{
  cols = VECTOR_ELT(*rTable, colNr);  // retrieve column vector

  SEXP levels_str = PROTECT(Rf_mkString("levels"));
  cols = PROTECT(Rf_getAttrib(cols, levels_str));
  uint32_t nrOfFactorLevels = LENGTH(cols);

  IStringWriter* str_writer = new BlockWriterChar(cols, nrOfFactorLevels,
    MAX_CHAR_STACK_SIZE, uniformEncoding);

  UNPROTECT(2);

  return str_writer;
}


IStringWriter* FstTable::GetColNameWriter()
{
  cols = Rf_getAttrib(*rTable, R_NamesSymbol);

  // Assuming that nrOfCols is already set
  return new BlockWriterChar(cols, nrOfCols, MAX_CHAR_STACK_SIZE, uniformEncoding);
}


inline uint32_t FindKey(StringVector colNameList, String item)
{
  int index = -1;
  int found = 0;
  for (Rcpp::StringVector::iterator it = colNameList.begin(); it != colNameList.end(); ++it)
  {
    if (*it == item)
    {
      index = found;
      break;
    }
    ++found;
  }

  return index;
}


uint32_t FstTable::NrOfKeys()
{
  SEXP sorted_str = PROTECT(Rf_mkString("sorted"));
  SEXP keyNames = PROTECT(Rf_getAttrib(*rTable, sorted_str));

  if (Rf_isNull(keyNames)) {
    UNPROTECT(2);
    return 0;
  }

  uint32_t length = LENGTH(keyNames);

  UNPROTECT(2);

  return length;
}


void FstTable::GetKeyColumns(int* keyColPos)
{
  SEXP sorted_str = PROTECT(Rf_mkString("sorted"));
  SEXP keyNames = PROTECT(Rf_getAttrib(*rTable, sorted_str));

  if (Rf_isNull(keyNames)) {
    UNPROTECT(2);
    return;
  }

  int keyLength = LENGTH(keyNames);

  // Find key column index numbers, if any
  StringVector keyList(keyNames);
  SEXP colNames = PROTECT(Rf_getAttrib(*rTable, R_NamesSymbol));

  for (int colSel = 0; colSel < keyLength; ++colSel)
  {
    keyColPos[colSel] = FindKey(colNames, keyList[colSel]);
  }

  UNPROTECT(3);  // keyNames
}


//  FstTableReader implementation

void FstTable::InitTable(uint32_t nrOfCols, uint64_t nrOfRows)
{
  this->nrOfCols = nrOfCols;
  this->nrOfRows = nrOfRows;

  SEXP resTable = Rf_allocVector(VECSXP, nrOfCols);

  // this PROTECT's the new vector
  SET_VECTOR_ELT(this->r_container, 0, resTable);
}


void FstTable::SetStringColumn(IStringColumn* stringColumn, int colNr)
{
  BlockReaderChar* sColumn = (BlockReaderChar*) stringColumn;

  // retrieve from memory-safe r container
  SEXP resTable = VECTOR_ELT(this->r_container, 0);
  SET_VECTOR_ELT(resTable, colNr, sColumn->StrVector());
}


void FstTable::SetLogicalColumn(ILogicalColumn* logicalColumn, int colNr)
{
  LogicalColumn* lColumn = (LogicalColumn*) logicalColumn;

  // retrieve from memory-safe r container
  SEXP resTable = VECTOR_ELT(this->r_container, 0);
  SET_VECTOR_ELT(resTable, colNr, lColumn->boolVec);
}


void FstTable::SetInt64Column(IInt64Column* int64Column, int colNr)
{
  Int64Column* i64Column = (Int64Column*) int64Column;

  // retrieve from memory-safe r container
  SEXP resTable = VECTOR_ELT(this->r_container, 0);
  SET_VECTOR_ELT(resTable, colNr, i64Column->int64Vec);
}


void FstTable::SetDoubleColumn(IDoubleColumn* doubleColumn, int colNr)
{
  DoubleColumn* dColumn = (DoubleColumn*) doubleColumn;

  // retrieve from memory-safe r container
  SEXP resTable = VECTOR_ELT(this->r_container, 0);
  SET_VECTOR_ELT(resTable, colNr, dColumn->colVec);
}


IByteBlockColumn* FstTable::add_byte_block_column(unsigned col_nr)
{
  // to be implemented
  return nullptr;
}


void FstTable::SetIntegerColumn(IIntegerColumn* integerColumn, int colNr)
{
  IntegerColumn* iColumn = (IntegerColumn*) integerColumn;

  // retrieve from memory-safe r container
  SEXP resTable = VECTOR_ELT(this->r_container, 0);
  SET_VECTOR_ELT(resTable, colNr, iColumn->colVec);
}


void FstTable::SetByteColumn(IByteColumn* byteColumn, int colNr)
{
  ByteColumn* bColumn = (ByteColumn*) byteColumn;

  // retrieve from memory-safe r container
  SEXP resTable = VECTOR_ELT(this->r_container, 0);
  SET_VECTOR_ELT(resTable, colNr, bColumn->colVec);
}


void FstTable::SetFactorColumn(IFactorColumn* factorColumn, int colNr)
{
  FactorColumn* factColumn = (FactorColumn*) factorColumn;
  //
  // SEXP level_str = PROTECT(Rf_mkString("levels"));
  // Rf_setAttrib(factColumn->intVec, level_str, factColumn->blockReaderStrVecP->StrVector());
  // UNPROTECT(1); // level_str
  //
  // if (factColumn->Attribute() == FstColumnAttribute::FACTOR_ORDERED)  // ordered factor
  // {
  //   SEXP classes;
  //   PROTECT(classes = Rf_allocVector(STRSXP, 2));
  //   SET_STRING_ELT(classes, 0, Rf_mkChar("ordered"));
  //   SET_STRING_ELT(classes, 1, Rf_mkChar("factor"));
  //   Rf_setAttrib(factColumn->intVec, Rf_mkString("class"), classes);
  //   UNPROTECT(1);
  // }
  // else  // unordered factor
  // {
  //   SEXP factor_str = PROTECT(Rf_mkString("factor"));
  //   Rf_setAttrib(factColumn->intVec, Rf_mkString("class"), factor_str);
  //   UNPROTECT(1);
  // }

  // retrieve from memory-safe r container
  SEXP resTable = VECTOR_ELT(this->r_container, 0);
  SET_VECTOR_ELT(resTable, colNr, factColumn->intVec);
}


void FstTable::SetColNames(IStringArray* col_names)
{
  StringArray* colNames = (StringArray*) col_names;  // upcast
  SEXP colNameVec = PROTECT(colNames->StrVector());

  // retrieve from memory-safe r container
  SEXP resTable = VECTOR_ELT(this->r_container, 0);
  Rf_setAttrib(resTable, R_NamesSymbol, colNameVec);
  UNPROTECT(1);  // colNameVec
}


SEXP FstTable::GetColNames()
{
  // retrieve from memory-safe r container
  SEXP resTable = VECTOR_ELT(this->r_container, 0);

  return Rf_getAttrib(resTable, R_NamesSymbol);
}


void FstTable::SetKeyColumns(int* keyColPos, uint32_t nrOfKeys)
{

}
