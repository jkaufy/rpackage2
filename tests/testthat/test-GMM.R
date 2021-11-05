test_that("GMM output vector has reasonable size/values", {
  data.mat <- as.matrix(iris[, c("Petal.Length", "Petal.Width")])
  K <- 3
  GMM.result <- GMM( data.mat, K )
  expect_equal( is.numeric(GMM.result[['loglik']]), TRUE )
})