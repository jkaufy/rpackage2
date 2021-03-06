test_that("BINSEG output vector has reasonable size/values", {
  library(data.table)
  data(neuroblastoma, package="neuroblastoma")
  proifle_id <- "4"
  chromosome_num <- "2"
  nb.dt <- data.table(neuroblastoma$profiles)
  data.dt <- nb.dt[nb.dt$profile.id == proifle_id & nb.dt$chromosome == chromosome_num,]
  num_segs <- 20
  my.binseg.result <- BINSEG(data.dt, num_segs)
  expect_equal(length(my.binseg.result), num_segs)
})
