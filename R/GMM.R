#' Perform Gaussian Mixture Model on a data matrix.
#'
#' This function computes the negative log likely on a data matrix using the
#' Gaussian Mixture Model
#'
#' @param data.mat A numeric data matrix (nxp)
#' @param K The number of clusters
#'
#' @return A numeric value of log.likely error
#'
#' @export
#'
#' @examples
#' data.mat <- as.matrix(iris[, c("Petal.Length", "Petal.Width")])
#' K <- 3
#' log.likely <- GMM(data.mat, K)
#' 

GMM <- function(data.mat, K)
{
  rand.mat <- matrix(runif(nrow(data.mat)*K), nrow=nrow(data.mat), ncol=K)
  prob.mat <- rand.mat/rowSums(rand.mat)
  old.log.likely <- 0 
  new.log.likely <- 1
  round.decimal <- 3
  
  while(round(old.log.likely, digits = round.decimal) != 
        round(new.log.likely, digits = round.decimal))
  {
    old.log.likely = new.log.likely
    
    
    cluster.param.list <- list()
    for (cluster in 1:K)
    {
      prob.vec <- prob.mat[, cluster]
      mean.vec <- colSums(data.mat * prob.vec)/sum(prob.vec)
      mean.mat <- matrix(mean.vec, nrow(data.mat), ncol(data.mat), byrow = TRUE)
      diff.mat <- data.mat - mean.mat
      constrained.cov.mat <- diag(colSums(diff.mat^2*prob.vec) / sum(prob.vec))
      this.cluster.params <- list(
        prior.weight = mean(prob.vec),
        mean.vec = mean.vec,
        cov.mat = constrained.cov.mat)
      cluster.param.list[[cluster]] <- this.cluster.params
    }
    
    density.mat <- matrix(NA, nrow(data.mat), K)
    for(cluster in 1:K){
      params <- cluster.param.list[[cluster]]
      density.mat[,cluster] <- mvtnorm::dmvnorm(
        data.mat, params$mean.vec, params$cov.mat
      )
    }
    
    total.density.vec <- rowSums(density.mat)
    new.log.likely <- sum(log(total.density.vec))
    prob.mat <- density.mat/total.density.vec
  }
  
  return(list(
    loglik = new.log.likely))
  
}
