//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl_data.cpp
//
// Code generated for Simulink model 'positionControl'.
//
// Model version                  : 1.7
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Wed Aug 19 08:09:50 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "positionControl.h"
#include "positionControl_private.h"

// Block parameters (default storage)
P_positionControl_T positionControlModelClass::positionControl_P = {
  // Variable: pos_y_D
  //  Referenced by: '<S226>/Derivative Gain'

  0.0,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S35>/Filter'

  0.0,

  // Mask Parameter: PIDController4_InitialCondition
  //  Referenced by: '<S227>/Filter'

  0.0,

  // Mask Parameter: PIDController5_InitialCondition
  //  Referenced by: '<S275>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S83>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S131>/Filter'

  0.0,

  // Mask Parameter: PIDController3_InitialCondition
  //  Referenced by: '<S179>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_c
  //  Referenced by: '<S40>/Integrator'

  0.0,

  // Mask Parameter: PIDController4_InitialConditi_i
  //  Referenced by: '<S232>/Integrator'

  0.0,

  // Mask Parameter: PIDController5_InitialConditi_c
  //  Referenced by: '<S280>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_a
  //  Referenced by: '<S88>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_n
  //  Referenced by: '<S136>/Integrator'

  0.0,

  // Mask Parameter: PIDController3_InitialConditi_d
  //  Referenced by: '<S184>/Integrator'

  0.0,

  // Mask Parameter: PIDController_LowerSaturationLi
  //  Referenced by: '<S47>/Saturation'

  -20.0,

  // Mask Parameter: PIDController4_LowerSaturationL
  //  Referenced by: '<S239>/Saturation'

  -20.0,

  // Mask Parameter: PIDController5_LowerSaturationL
  //  Referenced by:
  //    '<S273>/DeadZone'
  //    '<S287>/Saturation'

  -1.0,

  // Mask Parameter: PIDController1_LowerSaturationL
  //  Referenced by:
  //    '<S81>/DeadZone'
  //    '<S95>/Saturation'

  -1.0,

  // Mask Parameter: PIDController2_LowerSaturationL
  //  Referenced by: '<S143>/Saturation'

  -10.0,

  // Mask Parameter: PIDController3_LowerSaturationL
  //  Referenced by:
  //    '<S177>/DeadZone'
  //    '<S191>/Saturation'

  0.0,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S43>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController4_N
  //  Referenced by: '<S235>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController5_N
  //  Referenced by: '<S283>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S91>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController2_N
  //  Referenced by: '<S139>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController3_N
  //  Referenced by: '<S187>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController_UpperSaturationLi
  //  Referenced by: '<S47>/Saturation'

  20.0,

  // Mask Parameter: PIDController4_UpperSaturationL
  //  Referenced by: '<S239>/Saturation'

  20.0,

  // Mask Parameter: PIDController5_UpperSaturationL
  //  Referenced by:
  //    '<S273>/DeadZone'
  //    '<S287>/Saturation'

  1.0,

  // Mask Parameter: PIDController1_UpperSaturationL
  //  Referenced by:
  //    '<S81>/DeadZone'
  //    '<S95>/Saturation'

  1.0,

  // Mask Parameter: PIDController2_UpperSaturationL
  //  Referenced by: '<S143>/Saturation'

  10.0,

  // Mask Parameter: PIDController3_UpperSaturationL
  //  Referenced by:
  //    '<S177>/DeadZone'
  //    '<S191>/Saturation'

  1.0,

  // Expression: 0
  //  Referenced by: '<S81>/Constant1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S273>/Constant1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S177>/Constant1'

  0.0,

  // Expression: -1
  //  Referenced by: '<S8>/Gain'

  -1.0,

  // Computed Parameter: Integrator_gainval
  //  Referenced by: '<S40>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval
  //  Referenced by: '<S35>/Filter'

  0.02,

  // Computed Parameter: Integrator_gainval_l
  //  Referenced by: '<S232>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_l
  //  Referenced by: '<S227>/Filter'

  0.02,

  // Computed Parameter: Integrator_gainval_k
  //  Referenced by: '<S280>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_i
  //  Referenced by: '<S275>/Filter'

  0.02,

  // Expression: -1
  //  Referenced by: '<S1>/Gain1'

  -1.0,

  // Computed Parameter: Integrator_gainval_lc
  //  Referenced by: '<S88>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_l5
  //  Referenced by: '<S83>/Filter'

  0.02,

  // Computed Parameter: Integrator_gainval_o
  //  Referenced by: '<S136>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_f
  //  Referenced by: '<S131>/Filter'

  0.02,

  // Computed Parameter: Integrator_gainval_a
  //  Referenced by: '<S184>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_g
  //  Referenced by: '<S179>/Filter'

  0.02,

  // Expression: 0
  //  Referenced by: '<S81>/ZeroGain'

  0.0,

  // Expression: 0
  //  Referenced by: '<S273>/ZeroGain'

  0.0,

  // Expression: 0
  //  Referenced by: '<S177>/ZeroGain'

  0.0
};

//
// File trailer for generated code.
//
// [EOF]
//
