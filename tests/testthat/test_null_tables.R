
require(testthat)

context("NULL tables")


source("fst_helpers.R")


# temp data folder
if (dir.exists("data")) {
  unlink("data", recursive = TRUE, force = TRUE)
}

dir.create("data")


test_that("zero-row table", {

  zero_rows <- data.frame(X = integer(0), Y = character(0))

  # store and retrieve
  res <- store_retrieve("data/1.fst", zero_rows, 50L, TRUE)

  expect_equal(length(res$resTable$X), 0)
  expect_equal(length(res$resTable$Y), 0)
})
