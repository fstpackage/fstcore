
# write and read cycle
store_retrieve <- function(path, table, compression = 50L, uniform_encoding = TRUE) {

  # store
  msg <- fstcore:::fststore(path, table, compression, uniform_encoding)

  if ("fst_error" %in% class(msg)) {
    stop(msg)
  }

  # retrieve
  fstcore:::fstretrieve(path, NULL, 1L, NULL)
}
