#include "kalman_filter.h"

void KalmanFilter_Init(KalmanFilter_InitTypeDef *KF_Struct, float mea_e, float est_e, float q)
{
	KF_Struct->_err_measure=mea_e;
  KF_Struct->_err_estimate=est_e;
  KF_Struct->_q = q;
	
	KF_Struct->_current_estimate = 0;
	KF_Struct->_last_estimate = 0;
	KF_Struct->_kalman_gain = 0;
}

float KalmanFilter_Update(KalmanFilter_InitTypeDef *KF_Struct, float mea)
{
	KF_Struct->_kalman_gain = KF_Struct->_err_estimate/(KF_Struct->_err_estimate + KF_Struct->_err_measure);
  KF_Struct->_current_estimate = KF_Struct->_last_estimate + KF_Struct->_kalman_gain * (mea - KF_Struct->_last_estimate);
  KF_Struct->_err_estimate =  (1.0 - KF_Struct->_kalman_gain)*KF_Struct->_err_estimate + abs(KF_Struct->_last_estimate-KF_Struct->_current_estimate)*KF_Struct->_q;
  KF_Struct->_last_estimate = KF_Struct->_current_estimate;

  return KF_Struct->_current_estimate;
}
