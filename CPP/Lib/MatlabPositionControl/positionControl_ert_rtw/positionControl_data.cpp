//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl_data.cpp
//
// Code generated for Simulink model 'positionControl'.
//
// Model version                  : 1.8
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Fri Aug 21 23:47:28 2020
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
  // Variable: pos_y_D
  //  Referenced by: '<S177>/Derivative Gain'

  0.252,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S34>/Filter'

  0.0,

  // Mask Parameter: PIDController4_InitialCondition
  //  Referenced by: '<S178>/Filter'

  0.0,

  // Mask Parameter: PIDController5_InitialCondition
  //  Referenced by: '<S226>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S82>/Filter'

  0.0,

  // Mask Parameter: PIDController3_InitialCondition
  //  Referenced by: '<S130>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_c
  //  Referenced by: '<S39>/Integrator'

  0.0,

  // Mask Parameter: PIDController4_InitialConditi_i
  //  Referenced by: '<S183>/Integrator'

  0.0,

  // Mask Parameter: PIDController5_InitialConditi_c
  //  Referenced by: '<S231>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_a
  //  Referenced by: '<S87>/Integrator'

  0.0,

  // Mask Parameter: PIDController3_InitialConditi_d
  //  Referenced by: '<S135>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_Kb
  //  Referenced by: '<S80>/Kb'

  0.01,

  // Mask Parameter: PIDController5_Kb
  //  Referenced by: '<S224>/Kb'

  0.01,

  // Mask Parameter: PIDController_LowerSaturationLi
  //  Referenced by: '<S46>/Saturation'

  -20.0,

  // Mask Parameter: PIDController4_LowerSaturationL
  //  Referenced by: '<S190>/Saturation'

  -20.0,

  // Mask Parameter: PIDController5_LowerSaturationL
  //  Referenced by: '<S238>/Saturation'

  -1.0,

  // Mask Parameter: PIDController1_LowerSaturationL
  //  Referenced by: '<S94>/Saturation'

  -1.0,

  // Mask Parameter: PIDController3_LowerSaturationL
  //  Referenced by:
  //    '<S128>/DeadZone'
  //    '<S142>/Saturation'

  0.0,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S42>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController4_N
  //  Referenced by: '<S186>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController5_N
  //  Referenced by: '<S234>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S90>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController3_N
  //  Referenced by: '<S138>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController_UpperSaturationLi
  //  Referenced by: '<S46>/Saturation'

  20.0,

  // Mask Parameter: PIDController4_UpperSaturationL
  //  Referenced by: '<S190>/Saturation'

  20.0,

  // Mask Parameter: PIDController5_UpperSaturationL
  //  Referenced by: '<S238>/Saturation'

  1.0,

  // Mask Parameter: PIDController1_UpperSaturationL
  //  Referenced by: '<S94>/Saturation'

  1.0,

  // Mask Parameter: PIDController3_UpperSaturationL
  //  Referenced by:
  //    '<S128>/DeadZone'
  //    '<S142>/Saturation'

  1.0,

  // Expression: 0
  //  Referenced by: '<S128>/Constant1'

  0.0,

  // Expression: -1
  //  Referenced by: '<S7>/Gain'

  -1.0,

  // Computed Parameter: Integrator_gainval
  //  Referenced by: '<S39>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval
  //  Referenced by: '<S34>/Filter'

  0.02,

  // Computed Parameter: Integrator_gainval_l
  //  Referenced by: '<S183>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_l
  //  Referenced by: '<S178>/Filter'

  0.02,

  // Computed Parameter: Integrator_gainval_k
  //  Referenced by: '<S231>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_i
  //  Referenced by: '<S226>/Filter'

  0.02,

  // Expression: -1
  //  Referenced by: '<S1>/Gain1'

  -1.0,

  // Computed Parameter: Integrator_gainval_lc
  //  Referenced by: '<S87>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_l5
  //  Referenced by: '<S82>/Filter'

  0.02,

  // Expression: -1
  //  Referenced by: '<S1>/Gain2'

  -1.0,

  // Computed Parameter: Integrator_gainval_a
  //  Referenced by: '<S135>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_g
  //  Referenced by: '<S130>/Filter'

  0.02,

  // Expression: 0
  //  Referenced by: '<S128>/ZeroGain'

  0.0
};

//
// File trailer for generated code.
//
// [EOF]
//
