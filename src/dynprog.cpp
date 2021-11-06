#include "dynprog.h"
#include <math.h>
#include <stdio.h>
#include <limits>

int cumSum
  (const int N_data,
   const double *data_ptr,
   // inputs above, outputs below
   double *cum_vec
  ){
  
  if(N_data < 1){
    return ERROR_N_DATA_MUST_BE_POSITIVE;
  }
  
  for (int index = 0; index < N_data; index++){
    if (index == 0){
      cum_vec[index] = data_ptr[index];
    }else {
      cum_vec[index] = data_ptr[index]+cum_vec[index-1];
    }
  }
  
  return 0; // success
}

int loss
  (const int length,
   const double *n_vec,
   const double *sum_vec,
   // inputs above, outputs below
   double *result_vec
  ){
  
  for (int index = 0; index < length; index++){
    result_vec[index] = -(sum_vec[index]*sum_vec[index])/n_vec[index];
  }
  
  return 0; // success
}

int dynprog
  ( const int N_data,
    const int max_segments,
    double *poss_end_ptr,
    double *last_loss_ptr,
    double *sum_seg_ptr,
    double *cum_ptr,
    //inputs above, outputs below.
    double *loss_ptr
  ){
  
  if(max_segments < 1){
    return ERROR_MAX_SEGMENTS_MUST_BE_POSITIVE;
  }
  
  int length;
  double total_loss = 0;
  double min_loss;
  for (int N_segs = 1; N_segs < max_segments; N_segs++){
    for (int up_to_t = N_segs; up_to_t < N_data; up_to_t++){
      
      min_loss = std::numeric_limits<double>::infinity();
      length = 0;
      
      for (int index = N_segs-1; index < up_to_t; index++){
        sum_seg_ptr[index] = cum_ptr[up_to_t]-cum_ptr[index];
        poss_end_ptr[index] = up_to_t - index;
        length ++;
      }
      
      loss (length+1, poss_end_ptr, sum_seg_ptr, last_loss_ptr);
      
      for (int i = N_segs-1; i < up_to_t; i++ )
      {
        
        total_loss = loss_ptr[(N_segs-1)*N_data + i] + last_loss_ptr[i];
        //printf("TOTx: %f Next: ", last_loss_ptr[i]);
        
        if(total_loss < min_loss){
          min_loss = total_loss;
        }
      }
      loss_ptr[N_segs*N_data + up_to_t] = min_loss;
      
    }
  }
  return 0;//SUCCESS
}



