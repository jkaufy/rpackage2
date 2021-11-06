#include <Rcpp.h>
#include "dynprog.h"
using namespace Rcpp;

// [[Rcpp::export]]
NumericMatrix dynprog_interface
(NumericVector data_vec, int max_segments) {
  int N_data = data_vec.length();
  
  NumericVector data_i(N_data);
  NumericVector cum_vec(N_data);
  NumericVector last_loss(N_data);
  NumericVector possible_end(N_data);
  NumericVector sum_segs(N_data);
  
  NumericMatrix loss_mat(N_data, max_segments);
  
  std::fill( loss_mat.begin(), loss_mat.end(), NumericVector::get_na());
  
  double *data_i_ptr = &data_i[0];
  double *data_ptr = &data_vec[0];
  double *loss_ptr = &loss_mat[0];
  double *cum_ptr = &cum_vec[0];
  double *last_loss_ptr = &last_loss[0];
  double *sum_seg_ptr = &sum_segs[0];
  double *poss_end_ptr = &possible_end[0];
  
  for (int index = 0; index < N_data; index++){
    data_i_ptr[index] = index+1;
  }
  
  int status = cumSum
    ( N_data,
      data_ptr,
      // inputs above, outputs below
      cum_ptr
    );
  
  if(status == ERROR_N_DATA_MUST_BE_POSITIVE){
    Rcpp::stop("N_data must be postiive");
  }
  
  status = loss
    ( N_data,
      data_i_ptr,
      cum_ptr,
        // inputs above, outputs below
      last_loss_ptr
    );
  
  loss_mat(_, 0 ) = last_loss;

  status = dynprog
    ( N_data,
     max_segments,
     poss_end_ptr,
     last_loss_ptr,
     sum_seg_ptr,
     cum_ptr,
     //inputs above, outputs below.
     loss_ptr
    );
  
  List dynprog_result = List::create(Named("loss") = loss_mat);
  
  if(status == ERROR_MAX_SEGMENTS_MUST_BE_POSITIVE){
    Rcpp::stop("N_centers must be postiive");
  }
  
  return loss_mat;
}