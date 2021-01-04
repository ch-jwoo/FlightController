//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl_data.cpp
//
// Code generated for Simulink model 'positionControl'.
//
// Model version                  : 1.20
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Wed Oct  7 21:39:34 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "positionControl.h"
#include "positionControl_private.h"

// Block parameters (default storage)
positionControlModelClass::P_positionControl_T positionControlModelClass::
  positionControl_P = {
  // Variable: vel_Horizon_Max
  //  Referenced by:
  //    '<S34>/DeadZone'
  //    '<S48>/Saturation'
  //    '<S178>/DeadZone'
  //    '<S192>/Saturation'

  3.0,

  // Variable: vel_climbMax
  //  Referenced by:
  //    '<S274>/DeadZone'
  //    '<S288>/Saturation'

  1.0,

  // Variable: vel_descentMax
  //  Referenced by:
  //    '<S274>/DeadZone'
  //    '<S288>/Saturation'

  1.0,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S36>/Filter'

  0.0,

  // Mask Parameter: PIDController4_InitialCondition
  //  Referenced by: '<S180>/Filter'

  0.0,

  // Mask Parameter: PIDController5_InitialCondition
  //  Referenced by: '<S228>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S84>/Filter'

  0.0,

  // Mask Parameter: ZPostoVel_InitialConditionForFi
  //  Referenced by: '<S276>/Filter'

  0.0,

  // Mask Parameter: PIDController3_InitialCondition
  //  Referenced by: '<S132>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_c
  //  Referenced by: '<S41>/Integrator'

  0.0,

  // Mask Parameter: PIDController4_InitialConditi_i
  //  Referenced by: '<S185>/Integrator'

  0.0,

  // Mask Parameter: PIDController5_InitialConditi_c
  //  Referenced by: '<S233>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_a
  //  Referenced by: '<S89>/Integrator'

  0.0,

  // Mask Parameter: ZPostoVel_InitialConditionForIn
  //  Referenced by: '<S281>/Integrator'

  0.0,

  // Mask Parameter: PIDController3_InitialConditi_d
  //  Referenced by: '<S137>/Integrator'

  0.0,

  // Mask Parameter: PIDController5_LowerSaturationL
  //  Referenced by:
  //    '<S226>/DeadZone'
  //    '<S240>/Saturation'

  -1.0,

  // Mask Parameter: PIDController1_LowerSaturationL
  //  Referenced by:
  //    '<S82>/DeadZone'
  //    '<S96>/Saturation'

  -1.0,

  // Mask Parameter: PIDController3_LowerSaturationL
  //  Referenced by:
  //    '<S130>/DeadZone'
  //    '<S144>/Saturation'

  -0.1,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S44>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController4_N
  //  Referenced by: '<S188>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController5_N
  //  Referenced by: '<S236>/Filter Coefficient'

  5.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S92>/Filter Coefficient'

  5.0,

  // Mask Parameter: ZPostoVel_N
  //  Referenced by: '<S284>/Filter Coefficient'

  5.0,

  // Mask Parameter: PIDController3_N
  //  Referenced by: '<S140>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController5_UpperSaturationL
  //  Referenced by:
  //    '<S226>/DeadZone'
  //    '<S240>/Saturation'

  1.0,

  // Mask Parameter: PIDController1_UpperSaturationL
  //  Referenced by:
  //    '<S82>/DeadZone'
  //    '<S96>/Saturation'

  1.0,

  // Mask Parameter: PIDController3_UpperSaturationL
  //  Referenced by:
  //    '<S130>/DeadZone'
  //    '<S144>/Saturation'

  0.5,

  // Expression: 0
  //  Referenced by: '<S34>/Constant1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S82>/Constant1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S178>/Constant1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S226>/Constant1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S130>/Constant1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S274>/Constant1'

  0.0,

  // Expression: -1
  //  Referenced by: '<S9>/Gain'

  -1.0,

  // Computed Parameter: Integrator_gainval
  //  Referenced by: '<S41>/Integrator'

  0.01,

  // Computed Parameter: Filter_gainval
  //  Referenced by: '<S36>/Filter'

  0.01,

  // Computed Parameter: Integrator_gainval_l
  //  Referenced by: '<S185>/Integrator'

  0.01,

  // Computed Parameter: Filter_gainval_l
  //  Referenced by: '<S180>/Filter'

  0.01,

  // Computed Parameter: Integrator_gainval_k
  //  Referenced by: '<S233>/Integrator'

  0.01,

  // Computed Parameter: Filter_gainval_i
  //  Referenced by: '<S228>/Filter'

  0.01,

  // Computed Parameter: Integrator_gainval_lc
  //  Referenced by: '<S89>/Integrator'

  0.01,

  // Computed Parameter: Filter_gainval_l5
  //  Referenced by: '<S84>/Filter'

  0.01,

  // Expression: -1
  //  Referenced by: '<S1>/Gain1'

  -1.0,

  // Expression: -1
  //  Referenced by: '<S1>/Gain2'

  -1.0,

  // Computed Parameter: Integrator_gainval_j
  //  Referenced by: '<S281>/Integrator'

  0.01,

  // Computed Parameter: Filter_gainval_c
  //  Referenced by: '<S276>/Filter'

  0.01,

  // Expression: -1
  //  Referenced by: '<S1>/Gain3'

  -1.0,

  // Computed Parameter: Integrator_gainval_a
  //  Referenced by: '<S137>/Integrator'

  0.01,

  // Computed Parameter: Filter_gainval_g
  //  Referenced by: '<S132>/Filter'

  0.01,

  // Expression: 1
  //  Referenced by: '<S1>/Saturation'

  1.0,

  // Expression: 0
  //  Referenced by: '<S1>/Saturation'

  0.0,

  // Expression: 0
  //  Referenced by: '<S34>/ZeroGain'

  0.0,

  // Expression: 0
  //  Referenced by: '<S82>/ZeroGain'

  0.0,

  // Expression: 0
  //  Referenced by: '<S178>/ZeroGain'

  0.0,

  // Expression: 0
  //  Referenced by: '<S226>/ZeroGain'

  0.0,

  // Expression: 0
  //  Referenced by: '<S130>/ZeroGain'

  0.0,

  // Expression: 0
  //  Referenced by: '<S274>/ZeroGain'

  0.0
};

//
// File trailer for generated code.
//
// [EOF]
//
