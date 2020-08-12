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


#ifndef FST_TABLE_H
#define FST_TABLE_H

#include <iostream>
#include <vector>

#include <Rcpp.h>

#include <interface/fstdefines.h>
#include <interface/istringwriter.h>
#include <interface/ifsttable.h>


/**
  Interface to a fst table. A fst table is a temporary wrapper around an array of columnar data buffers.
  The table only exists to facilitate serialization and deserialization of data.
*/
class FstTable : public IFstTable
{
  // References to R objects
  SEXP* rTable;  // reference to R table structure (e.g. data.frame or data.table)
  SEXP cols;  // reference to working column

  // container for r objects, must be a VECSXP of length >= 1
  SEXP r_container;

  // Table metadata
  unsigned int nrOfCols;
  unsigned long long nrOfRows;
  int uniformEncoding;


  public:
    // use r_container for res_table
    // SEXP resTable;

    FstTable(SEXP r_container)
    {
      this->r_container = r_container;
    }

    FstTable(SEXP &table, int uniformEncoding, SEXP r_container);

    ~FstTable() {}

    SEXP ResTable() { return VECTOR_ELT(r_container, 0); }

    void InitTable(unsigned int nrOfCols, unsigned long long nrOfRows);

    void SetStringColumn(IStringColumn* stringColumn, int colNr);

    void SetLogicalColumn(ILogicalColumn* logicalColumn, int colNr);

    void SetIntegerColumn(IIntegerColumn* integerColumn, int colNr);

    // void SetIntegerColumn(IIntegerColumn* integerColumn, int colNr, std::string &annotation);

    void SetByteColumn(IByteColumn* byteColumn, int colNr);

    void SetInt64Column(IInt64Column* int64Column, int colNr);

  	void SetDoubleColumn(IDoubleColumn * doubleColumn, int colNr);

  	IByteBlockColumn* add_byte_block_column(unsigned col_nr);

  	void SetFactorColumn(IFactorColumn* factorColumn, int colNr);

    void SetColNames();

    void SetKeyColumns(int* keyColPos, unsigned int nrOfKeys);

    FstColumnType ColumnType(unsigned int colNr, FstColumnAttribute &columnAttribute, short int &scale,
      std::string &annotation, bool &hasAnnotation);

    IStringWriter* GetStringWriter(unsigned int colNr);

    int* GetLogicalWriter(unsigned int colNr);

    int* GetIntWriter(unsigned int colNr);

    char* GetByteWriter(unsigned int colNr);

    long long* GetInt64Writer(unsigned int colNr);

    double* GetDoubleWriter(unsigned int colNr);

    IByteBlockColumn* GetByteBlockWriter(unsigned int col_nr);

    IStringWriter* GetLevelWriter(unsigned int colNr);

    IStringWriter* GetColNameWriter();

    void GetKeyColumns(int* keyColPos);

    unsigned int NrOfKeys();

    unsigned int NrOfColumns();

    void SetColNames(IStringArray* col_names);

    SEXP GetColNames();

    unsigned long long NrOfRows();
};


#endif  // FST_TABLE_H
