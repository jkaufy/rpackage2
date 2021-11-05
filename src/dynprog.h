#define ERROR_N_DATA_MUST_BE_POSITIVE 1
#define ERROR_N_CENTERS_MUST_BE_POSITIVE 2
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
 );