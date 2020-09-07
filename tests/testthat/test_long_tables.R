
require(testthat)

context("long tables")

source("fst_helpers.R")


# temp data folder
if (dir.exists("data")) {
  unlink("data", recursive = TRUE, force = TRUE)
}

dir.create("data")


test_that("long table", {

  skip_on_cran()  # this test requires > 2 GB RAM

  # manually create a data frame
  df <- structure(
    list(
      X = rep(as.raw(1L), 2^31 + 1)
    ),
    class = "data.frame"
  )

  # test for long vec
  expect_equal(length(df$X), 2^31)

  # write to disk
  fstcore:::fststore("data/1.fst", df, 50L, TRUE)

  # result table contains a long vec
  y <- fstcore:::fstretrieve("data/1.fst", NULL, 1, NULL)
  expect_equal(length(y$resTable$X), 2^31 + 1)

  # custom row selection
  y <- fstcore:::fstretrieve("data/1.fst", NULL, 1, 2^31 + 1)
  expect_equal(length(y$resTable$X), 2^31 + 1)
})
