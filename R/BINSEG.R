#' Performs Binary Segmentation on a data matrix containing a log-ratio
#' numeric vector.
#'
#' This function computes TODO
#'
#' @param data.dt A numeric data matrix (nxp) containing a log-ratio numeric Vector
#' @param num_segments The number of clusters
#'
#' @return TODO
#'
#' @export
#'
#' @examples
#' TODO
#'

BINSEG <- function (data.dt, num_segments)
{
  square_loss <- c()
  data.dt[, data.i := 1:.N]
  data.dt[, cum.data := cumsum(logratio)]
  data.dt[, .(logratio, cum.data)]
  possible.dt <- data.table(
    first_seg_end = seq(1, nrow(data.dt)-1))
  possible.dt[, first_seg_mean := {
    data.dt$cum.data[first_seg_end]/first_seg_end
  }]
  ## Loss = sum of squares - sum^2/n.
  loss <- function(cum.sum.vec, cum.square.vec, N.data.vec){
    cum.square.vec-cum.sum.vec^2/N.data.vec
  }
  data.dt[, cum.square := cumsum(logratio^2)]
  possible.dt[, first_seg_loss := {
    data.dt[
      first_seg_end,
      loss(cum.data, cum.square, first_seg_end)
    ]  
  }]
  possible.dt[, cum.data.after := {
    data.dt[.N, cum.data]-data.dt[first_seg_end, cum.data]
  }]
  possible.dt[, cum.square.after := {
    data.dt[.N, cum.square]-
      data.dt[first_seg_end, cum.square]
  }]
  possible.dt[, N.data.after := nrow(data.dt)-first_seg_end]
  possible.dt[, second_seg_loss := {
    loss(cum.data.after, cum.square.after, N.data.after)
  }]
  possible.dt[, total_loss := {
    first_seg_loss + second_seg_loss
  }]
  all.new.possible.dt <- data.table(
    first_seg_end = seq(1, nrow(data.dt)-1))
  
  square_loss <- c(square_loss, possible.dt[which.min(total_loss)]$total_loss)
  new.segs <- possible.dt[which.min(total_loss), rbind(
    data.table(start=1, end=first_seg_end),
    data.table(start=first_seg_end+1, end=nrow(data.dt)))]
  
  for (segments in 2:num_segments)
  {
    old_loss <- square_loss[segments-1]
    all.new.possible.dt <-  data.table()
    for(seg.i in 1:nrow(new.segs)){
      one.seg <- new.segs[seg.i]
      new.possible.dt <- one.seg[, data.table(
        first_seg_end=seq(start, end-1))]
      
      new.possible.dt[, first_seg_loss := 
                        data.dt[
                          first_seg_end,
                          loss(cum.data, cum.square, first_seg_end)
                        ]
      ]
      new.possible.dt[, cum.data.after := {
        data.dt[.N, cum.data]-data.dt[first_seg_end, cum.data]
      }]
      new.possible.dt[, cum.square.after := {
        data.dt[.N, cum.square]-
          data.dt[first_seg_end, cum.square]
      }]
      new.possible.dt[, N.data.after := nrow(data.dt)-first_seg_end]
      
      new.possible.dt[, second_seg_loss := 
                        loss(cum.data.after, cum.square.after, N.data.after)
      ]
      new.possible.dt[, split_loss := {
        first_seg_loss+second_seg_loss
      }]
      new.possible.dt[, no_split_loss := old_loss]
      new.possible.dt[, loss_decrease := no_split_loss-split_loss]
      all.new.possible.dt <- rbind(all.new.possible.dt,new.possible.dt)
    }
    
    for (seg.i in 1:nrow(new.segs))
    {
      if(all.new.possible.dt[which.min(total_loss)]$first_seg_end < seg.i$end)
      {
        new.segs <- all.new.possible.dt[which.min(total_loss), rbind(
          segs.i,
          data.table(start=first_seg_end+1, end=seg.i$end))]
        seg.i$end <- all.new.possible.dt[which.min(total_loss)]$first_seg_end
      }
    }
    sqaure_loss <- c(sqaure_loss, 
                     all.new.possible.dt[which.min(total_loss)]$total_loss)
  }
  
  segments <- 1:num_segments
  return_table<- cbind(segements,sqaure_loss)
  return(return_table)
}
