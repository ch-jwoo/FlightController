//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TECS_data.cpp
//
// Code generated for Simulink model 'TECS'.
//
// Model version                  : 1.27
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Sun Sep 27 14:33:42 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include <MatlabTECS/TECS.h>
#include <MatlabTECS/TECS_private.h>


// Block parameters (default storage)
fw_TECSModelClass::P_TECS_T fw_TECSModelClass::TECS_P = {
  // Mask Parameter: FW_T_INTEGRAL_GAIN_I
  //  Referenced by: '<S133>/Integral Gain'

  0.1,

  // Mask Parameter: FW_T_INTEGRAL_GAIN_InitialCondi
  //  Referenced by: '<S136>/Integrator'

  0.0,

  // Mask Parameter: STE_to_throttle_LowerSaturation
  //  Referenced by: '<S338>/Saturation'

  0.0,

  // Mask Parameter: FW_T_HRATE_P_P
  //  Referenced by: '<S41>/Proportional Gain'

  0.05,

  // Mask Parameter: FW_T_SRATE_P_P
  //  Referenced by: '<S89>/Proportional Gain'

  0.02,

  // Mask Parameter: FW_T_PITCH_DAMP_P
  //  Referenced by: '<S189>/Proportional Gain'

  0.0,

  // Mask Parameter: FW_T_THR_DAMP_P
  //  Referenced by: '<S288>/Proportional Gain'

  0.5,

  // Mask Parameter: FW_T_INTEG_GAIN_P
  //  Referenced by: '<S240>/Proportional Gain'

  0.1,

  // Mask Parameter: STE_to_throttle_P
  //  Referenced by: '<S336>/Proportional Gain'

  0.002,

  // Mask Parameter: STE_to_throttle_UpperSaturation
  //  Referenced by: '<S338>/Saturation'

  1.0,

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

  // Expression: FW_T_HRATE_FF
  //  Referenced by: '<S1>/FW_T_HRATE_FF'

  0.0,

  // Expression: ACCEL_ONE_G
  //  Referenced by: '<S1>/ACCEL_ONE_G1'

  9.8,

  // Expression: ACCEL_ONE_G
  //  Referenced by: '<S1>/ACCEL_ONE_G3'

  9.8,

  // Expression: FW_T_SPDWEIGHT
  //  Referenced by: '<S101>/FW_T_SPDWEIGHT'

  1.0,

  // Computed Parameter: Integrator_gainval
  //  Referenced by: '<S136>/Integrator'

  0.2,

  // Expression: FW_T_TIME_CONST
  //  Referenced by: '<S101>/FW_T_TIME_CONST_'

  5.0,

  // Expression: FW_T_TIME_CONST
  //  Referenced by: '<S101>/FW_T_TIME_CONST'

  5.0,

  // Expression: ACCEL_ONE_G
  //  Referenced by: '<S101>/ACCEL_ONE_G'

  9.8,

  // Expression: 1
  //  Referenced by: '<S101>/Saturation'

  1.0,

  // Expression: -1
  //  Referenced by: '<S101>/Saturation'

  -1.0,

  // Expression: FW_T_PRE_GAIN
  //  Referenced by: '<S102>/FW_T_PRE_GAIN'

  0.002,

  // Expression: FW_THR_CRUISE
  //  Referenced by: '<S102>/FW_THR_CRUISE'

  0.5,

  // Expression: 1
  //  Referenced by: '<S102>/Saturation'

  1.0,

  // Expression: 0
  //  Referenced by: '<S102>/Saturation'

  0.0,

  // Expression: 1
  //  Referenced by: '<S102>/Saturation1'

  1.0,

  // Expression: 0
  //  Referenced by: '<S102>/Saturation1'

  0.0
};

//
// File trailer for generated code.
//
// [EOF]
//
