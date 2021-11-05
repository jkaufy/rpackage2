#include <Rcpp.h>
#include "dynprog.h"
using namespace Rcpp;

// [[Rcpp::export]]
List dynprog_interface
(NumericMatrix data_mat, int clusters) {
  int N_data = data_mat.nrow();
  int N_features = data_mat.ncol();
  NumericMatrix centers_mat(clusters, N_features);
  NumericMatrix mean_clusters(clusters,N_features);
  NumericVector cluster_totals(clusters);
  
  
  if(N_features != data_mat.ncol()){
    Rcpp::stop("number of columns in data and centers should be the same");
  }
  for(int cluster_i = 0; cluster_i < clusters ; cluster_i++){
    int random_integer = rand() % N_data;
    centers_mat( cluster_i , _ ) = data_mat( random_integer , _ );
  }
  double error = 0;
  double *data_ptr = &data_mat[0];
  double *tot_cluster_ptr = &cluster_totals[0];
  double *centers_ptr = &centers_mat[0];
  double *mean_ptr = &mean_clusters[0];
  double *error_ptr = NULL;
  error_ptr = &error;
  IntegerVector cluster_vec(N_data);
  int *cluster_ptr = &cluster_vec[0];
  int status = dynprog
    (N_data,
     clusters,
     N_features,
     data_ptr,
     centers_ptr,
     mean_ptr,
     tot_cluster_ptr,
     //inputs above, outputs below.
     cluster_ptr,
     error_ptr);
  
  List kmeans_result = List::create(Named("cluster_ids") = cluster_vec);
  if(status == ERROR_N_DATA_MUST_BE_POSITIVE){
    Rcpp::stop("N_data must be postiive");
  }
  if(status == ERROR_N_CENTERS_MUST_BE_POSITIVE){
    Rcpp::stop("N_centers must be postiive");
  }
  return Rcpp::List::create(Rcpp::Named("cluster_id") = cluster_vec,
                            Rcpp::Named("tot.withinss") = error);
}