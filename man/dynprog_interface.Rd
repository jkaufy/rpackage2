\name{dynprog_interface}
\docType{package}
\title{
  Dynamic Progamming Algorithm
}
\alias{
  dynprog_interface
}
\description{
  Computes Dynamic Programming on a numeric vector up to max segements
}
\usage{
dynprog_interface(data_mat, clusters)
}
\arguments{
\item{data_vec}{A numeric data vector size (n)}

\item{max_segments}{The maximum number of segments}
}
\value{
  Returns the Loss Matrix as a numeric matrix with the columns as the
  max segments 
}
\examples{
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
}