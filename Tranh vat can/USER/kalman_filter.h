#ifndef __kalman_filter__
#define __kalman_filter__

#ifdef __cplusplus
extern "C" {
#endif

#include "math.h"
typedef struct
{
    float _current_estimate;
    float _last_estimate;
    float _err_measure;
    float _err_estimate;
    float _q;
    float _kalman_gain;
	
}KalmanFilter_InitTypeDef;
	
void KalmanFilter_Init(KalmanFilter_InitTypeDef *KF_Struct, float mea_e, float est_e, float q);
float KalmanFilter_Update(KalmanFilter_InitTypeDef *KF_Struct, float mea);


#ifdef __cplusplus
}
#endif
#endif
