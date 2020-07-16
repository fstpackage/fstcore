
# write and read cycle
store_retrieve <- function(path, table, compression = 50L, uniform_encoding = TRUE) {

  # store
  fstcore:::fststore(path, table, compression, uniform_encoding)

  # retrieve
  fstcore:::fstretrieve(path, NULL, 1L, NULL)
}
