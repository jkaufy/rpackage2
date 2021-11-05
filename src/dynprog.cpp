#include "dynprog.h"
#include <math.h>
#include <stdio.h>

int dynprog
(const int N_data,
 const int N_centers,
 const int N_features,
 const double *data_ptr,
 double *centers_ptr,
 double *mean_ptr,
 double *tot_cluster_ptr,
 //inputs above, outputs below.
 int *cluster_ptr,
 double *error
 ){
  if(N_data < 1){
    return ERROR_N_DATA_MUST_BE_POSITIVE;
  }
  
  if(N_centers < 1){
    return ERROR_N_CENTERS_MUST_BE_POSITIVE;
  }
  bool change = true;
  int old_cluster = 0;
  
  while(change){
    change = false;
    *error = 0; 
    
    for(int data_i=0; data_i<N_data; data_i++){
      double min_error = INFINITY;
      old_cluster = cluster_ptr[data_i];
      for(int center_i=0;center_i<N_centers; center_i++){
        double error = 0;
        for(int feature_i=0;feature_i<N_features; feature_i++){
          double data_value = data_ptr[feature_i*N_data + data_i];
          double center_value = centers_ptr[feature_i*N_centers + center_i];
          double diff = data_value - center_value;
          error += diff * diff;
        }
        if(error < min_error){
          min_error = error;
          cluster_ptr[data_i] = center_i+1;
        }
      }
      
      if(old_cluster != cluster_ptr[data_i])
      {
        change = true;
      }
      *error += min_error;
    }
    
    for(int data_i=0; data_i<N_data; data_i++){
      for(int feature_i=0;feature_i<N_features; feature_i++){
        double data_value = data_ptr[feature_i*N_data + data_i];
        mean_ptr[feature_i*N_centers + (cluster_ptr[data_i]-1)] += data_value;
      }
      tot_cluster_ptr[cluster_ptr[data_i]-1] += 1;
    }
    
    for(int center_i=0;center_i<N_centers; center_i++){
      for(int feature_i=0;feature_i<N_features; feature_i++){
        double new_center_value = mean_ptr[feature_i*N_centers + center_i] / 
          tot_cluster_ptr[center_i];
        centers_ptr[feature_i*N_centers + center_i] = new_center_value;
      }
    }
  }
  
  return 0;//SUCCESS
}