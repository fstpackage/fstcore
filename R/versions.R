#  fstcore - R bindings to the fstlib library
#
#  Copyright (C) 2017-present, Mark AJ Klik
#
#  This file is part of the fstcore R package.
#
#  This Source Code Form is subject to the terms of the Mozilla Public
#  License, v. 2.0. If a copy of the MPL was not distributed with this file,
#  You can obtain one at https://mozilla.org/MPL/2.0/.
#
#  https://www.mozilla.org/en-US/MPL/2.0/FAQ/
#
#  You can contact the author at:
#  - fstcore R package source repository : https://github.com/fstpackage/fstcore


#' Display versioning information of fstcore library dependencies
#'
#' @return a list with library versions
#' @export
lib_versions <- function() {
  library_versions()
}
