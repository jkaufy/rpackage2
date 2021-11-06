#define ERROR_N_DATA_MUST_BE_POSITIVE 1
#define ERROR_MAX_SEGMENTS_MUST_BE_POSITIVE 2

int cumSum
(const int N_data,
 const double *data_ptr,
 // inputs above, outputs below
 double *cum_vec
 );

int loss
(const int length,
 const double *n_vec,
 const double *sum_vec,
 // inputs above, outputs below
 double *result_vec
 );


int dynprog
( const int N_data,
  const int max_segments,
  double *poss_end_ptr,
  double *last_loss_ptr,
  double *sum_seg_ptr,
  double *cum_ptr,
  //inputs above, outputs below.
  double *loss_ptr
  );


