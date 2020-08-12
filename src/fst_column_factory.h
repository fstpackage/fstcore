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


#ifndef COLUMN_FACTORY_H
#define COLUMN_FACTORY_H

#include <iostream>
#include <vector>

#include <Rcpp.h>

#include <interface/icolumnfactory.h>
#include <interface/ifstcolumn.h>
#include <interface/ifsttable.h>

#include <fst_column.h>
#include <fst_blockrunner_char.h>


class ColumnFactory : public IColumnFactory
{
public:
  ~ColumnFactory() {};

  IFactorColumn* CreateFactorColumn(uint64_t nrOfRows, uint64_t nrOfLevels, FstColumnAttribute columnAttribute)
  {
    return new FactorColumn(nrOfRows, nrOfLevels, columnAttribute);
  }

  ILogicalColumn* CreateLogicalColumn(uint64_t nrOfRows, FstColumnAttribute columnAttribute)
  {
    return new LogicalColumn(nrOfRows);
  }

  IDoubleColumn* CreateDoubleColumn(uint64_t nrOfRows, FstColumnAttribute columnAttribute, short int scale)
  {
    return new DoubleColumn(nrOfRows, columnAttribute, scale);
  }

  IIntegerColumn* CreateIntegerColumn(uint64_t nrOfRows, FstColumnAttribute columnAttribute, short int scale)
  {
    return new IntegerColumn(nrOfRows, columnAttribute, scale);
  }

  IByteColumn* CreateByteColumn(uint64_t nrOfRows, FstColumnAttribute columnAttribute)
  {
    return new ByteColumn(nrOfRows);
  }

  IInt64Column* CreateInt64Column(uint64_t nrOfRows, FstColumnAttribute columnAttribute, short int scale)
  {
    return new Int64Column(nrOfRows, columnAttribute, scale);
  }

  IStringColumn* CreateStringColumn(uint64_t nrOfRows, FstColumnAttribute columnAttribute)
  {
    return new BlockReaderChar();
  }

  IStringArray* CreateStringArray()
  {
    return new StringArray();
  }
};


#endif  // COLUMN_FACTORY_H

