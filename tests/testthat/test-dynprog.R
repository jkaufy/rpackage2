test_that("Dyanmic Programming output vector has reasonable size/values", {
  destfile <- "data-for-LOPART-signals.csv.gz"
  file.url = paste0(
    "https://raw.githubusercontent.com/tdhock/LOPART-paper/master/",
    destfile)
  
  if(!file.exists(destfile)){
    download.file(file.url, destfile)
  }
  library(data.table)
  zip.dt <- data.table::fread(destfile)
  sequence_id <- 20167.22
  selected.dt <- zip.dt[sequenceID == sequence_id,]
  logratio <- as.numeric(selected.dt[["logratio"]])
  
  max_segments <- 3
  dynprog_result <-rpackage2::dynprog_interface(logratio, max_segments)
  expect_equal(ncol(dynprog_result), max_segments)
  expect_equal(nrow(dynprog_result), nrow(selected.dt))
})
