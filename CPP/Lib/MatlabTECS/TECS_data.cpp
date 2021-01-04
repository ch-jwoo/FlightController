//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TECS_data.cpp
//
// Code generated for Simulink model 'TECS'.
//
// Model version                  : 1.30
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Thu Oct 15 15:30:38 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "TECS.h"
#include "TECS_private.h"

// Block parameters (default storage)
fw_TECSModelClass::P_TECS_T fw_TECSModelClass::TECS_P = {
  // Mask Parameter: DiscretePIDController_I
  //  Referenced by: '<S34>/Integral Gain'

  0.1,

  // Mask Parameter: DiscretePIDController_I_l
  //  Referenced by: '<S83>/Integral Gain'

  0.1,

  // Mask Parameter: DiscretePIDController_InitialCo
  //  Referenced by: '<S86>/Integrator'

  0.0,

  // Mask Parameter: DiscretePIDController_Initial_f
  //  Referenced by: '<S37>/Integrator'

  0.0,

  // Mask Parameter: DiscretePIDController_LowerSatu
  //  Referenced by:
  //    '<S79>/DeadZone'
  //    '<S93>/Saturation'

  -0.3,

  // Mask Parameter: DiscretePIDController_LowerSa_p
  //  Referenced by:
  //    '<S30>/DeadZone'
  //    '<S44>/Saturation'

  -0.3,

  // Mask Parameter: DiscretePIDController_UpperSatu
  //  Referenced by:
  //    '<S79>/DeadZone'
  //    '<S93>/Saturation'

  0.3,

  // Mask Parameter: DiscretePIDController_UpperSa_f
  //  Referenced by:
  //    '<S30>/DeadZone'
  //    '<S44>/Saturation'

  0.3,

  // Expression: 0
  //  Referenced by: '<S30>/Constant1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S79>/Constant1'

  0.0,

  // Computed Parameter: Integrator_gainval
  //  Referenced by: '<S86>/Integrator'

  0.01,

  // Expression: ACCEL_ONE_G
  //  Referenced by: '<S1>/ACCEL_ONE_G'

  9.8,

  // Expression: ACCEL_ONE_G
  //  Referenced by: '<S1>/ACCEL_ONE_G2'

  9.8,

  // Expression: 1/2
  //  Referenced by: '<S1>/Gain'

  0.5,

  // Expression: 1/2
  //  Referenced by: '<S1>/Gain1'

  0.5,

  // Expression: FW_T_HRATE_P
  //  Referenced by: '<S1>/FW_T_HRATE_P'

  0.05,

  // Expression: ACCEL_ONE_G
  //  Referenced by: '<S1>/ACCEL_ONE_G1'

  9.8,

  // Expression: FW_T_SRATE_P
  //  Referenced by: '<S1>/FW_T_SRATE_P'

  0.1,

  // Expression: ACCEL_ONE_G
  //  Referenced by: '<S1>/ACCEL_ONE_G3'

  9.8,

  // Expression: FW_T_THR_DAMP
  //  Referenced by: '<S4>/FW_T_THR_DAMP'

  0.7,

  // Expression: STE_to_throttle
  //  Referenced by: '<S4>/STE_to_throttle'

  0.005,

  // Expression: FW_T_PRE_GAIN
  //  Referenced by: '<S4>/FW_T_PRE_GAIN'

  0.002,

  // Expression: FW_THR_CRUISE
  //  Referenced by: '<S4>/FW_THR_CRUISE'

  0.5,

  // Expression: 1
  //  Referenced by: '<S4>/Saturation'

  1.0,

  // Expression: 0
  //  Referenced by: '<S4>/Saturation'

  0.0,

  // Expression: 1
  //  Referenced by: '<S4>/Saturation1'

  1.0,

  // Expression: 0
  //  Referenced by: '<S4>/Saturation1'

  0.0,

  // Computed Parameter: Integrator_gainval_m
  //  Referenced by: '<S37>/Integrator'

  0.01,

  // Expression: FW_T_SPDWEIGHT
  //  Referenced by: '<S3>/FW_T_SPDWEIGHT'

  1.0,

  // Expression: FW_T_PITCH_DAMP
  //  Referenced by: '<S3>/STE_T_INTEG_GAIN1'

  0.5,

  // Expression: FW_T_P_TIME_CONST
  //  Referenced by: '<S3>/FW_T_P_TIME_CONST_'

  0.1,

  // Expression: FW_T_P_TIME_CONST
  //  Referenced by: '<S3>/FW_T_P_TIME_CONST'

  5.0,

  // Expression: ACCEL_ONE_G
  //  Referenced by: '<S3>/ACCEL_ONE_G'

  9.8,

  // Expression: 1
  //  Referenced by: '<S3>/Saturation'

  1.0,

  // Expression: -1
  //  Referenced by: '<S3>/Saturation'

  -1.0,

  // Expression: 0
  //  Referenced by: '<S30>/ZeroGain'

  0.0,

  // Expression: 0
  //  Referenced by: '<S79>/ZeroGain'

  0.0
};

//
// File trailer for generated code.
//
// [EOF]
//
