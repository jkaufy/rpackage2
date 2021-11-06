# rpackage
## Installation:

You can install this R package by using the command:
```
remotes::install_github(“jkaufy/rpackage2”)
```
## Usage:

Example for Dynamic Programming:

```
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
```

Example for Binary Segmentation:
```
data(neuroblastoma, package="neuroblastoma")
library(data.table)
proifle_id <- "4"
chromosome_num <- "2"
nb.dt <- data.table(neuroblastoma$profiles)
data.dt <- nb.dt[profile.id==proifle_id & chromosome==chromosome_num]
num_segs <- 20
my.binseg.result <- BINSEG(data.dt, num_segs)
```
