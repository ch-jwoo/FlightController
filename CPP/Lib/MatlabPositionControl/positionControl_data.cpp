//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl_data.cpp
//
// Code generated for Simulink model 'positionControl'.
//
// Model version                  : 1.10
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Sun Aug 23 20:26:15 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include <MatlabPositionControl/positionControl.h>
#include <MatlabPositionControl/positionControl_private.h>

// Block parameters (default storage)
positionControlModelClass::P_positionControl_T positionControlModelClass::
  positionControl_P = {
  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S35>/Filter'

  0.0,

  // Mask Parameter: PIDController4_InitialCondition
  //  Referenced by: '<S179>/Filter'

  0.0,

  // Mask Parameter: PIDController5_InitialCondition
  //  Referenced by: '<S227>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S83>/Filter'

  0.0,

  // Mask Parameter: ZPostoVel_InitialConditionForFi
  //  Referenced by: '<S275>/Filter'

  0.0,

  // Mask Parameter: PIDController3_InitialCondition
  //  Referenced by: '<S131>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_c
  //  Referenced by: '<S40>/Integrator'

  0.0,

  // Mask Parameter: PIDController4_InitialConditi_i
  //  Referenced by: '<S184>/Integrator'

  0.0,

  // Mask Parameter: PIDController5_InitialConditi_c
  //  Referenced by: '<S232>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_a
  //  Referenced by: '<S88>/Integrator'

  0.0,

  // Mask Parameter: ZPostoVel_InitialConditionForIn
  //  Referenced by: '<S280>/Integrator'

  0.0,

  // Mask Parameter: PIDController3_InitialConditi_d
  //  Referenced by: '<S136>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_Kb
  //  Referenced by: '<S81>/Kb'

  0.01,

  // Mask Parameter: PIDController5_Kb
  //  Referenced by: '<S225>/Kb'

  0.01,

  // Mask Parameter: PIDController_LowerSaturationLi
  //  Referenced by: '<S47>/Saturation'

  -20.0,

  // Mask Parameter: PIDController4_LowerSaturationL
  //  Referenced by: '<S191>/Saturation'

  -20.0,

  // Mask Parameter: PIDController5_LowerSaturationL
  //  Referenced by: '<S239>/Saturation'

  -1.0,

  // Mask Parameter: PIDController1_LowerSaturationL
  //  Referenced by: '<S95>/Saturation'

  -1.0,

  // Mask Parameter: PIDController3_LowerSaturationL
  //  Referenced by:
  //    '<S129>/DeadZone'
  //    '<S143>/Saturation'

  -0.5,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S43>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController4_N
  //  Referenced by: '<S187>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController5_N
  //  Referenced by: '<S235>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S91>/Filter Coefficient'

  10.0,

  // Mask Parameter: ZPostoVel_N
  //  Referenced by: '<S283>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController3_N
  //  Referenced by: '<S139>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController_UpperSaturationLi
  //  Referenced by: '<S47>/Saturation'

  20.0,

  // Mask Parameter: PIDController4_UpperSaturationL
  //  Referenced by: '<S191>/Saturation'

  20.0,

  // Mask Parameter: PIDController5_UpperSaturationL
  //  Referenced by: '<S239>/Saturation'

  1.0,

  // Mask Parameter: PIDController1_UpperSaturationL
  //  Referenced by: '<S95>/Saturation'

  1.0,

  // Mask Parameter: PIDController3_UpperSaturationL
  //  Referenced by:
  //    '<S129>/DeadZone'
  //    '<S143>/Saturation'

  0.5,

  // Expression: 0
  //  Referenced by: '<S129>/Constant1'

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
  //  Referenced by: '<S184>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_l
  //  Referenced by: '<S179>/Filter'

  0.02,

  // Computed Parameter: Integrator_gainval_k
  //  Referenced by: '<S232>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_i
  //  Referenced by: '<S227>/Filter'

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

  // Expression: -1
  //  Referenced by: '<S1>/Gain2'

  -1.0,

  // Computed Parameter: Integrator_gainval_j
  //  Referenced by: '<S280>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_c
  //  Referenced by: '<S275>/Filter'

  0.02,

  // Expression: -1
  //  Referenced by: '<S1>/Gain3'

  -1.0,

  // Computed Parameter: Integrator_gainval_a
  //  Referenced by: '<S136>/Integrator'

  0.02,

  // Computed Parameter: Filter_gainval_g
  //  Referenced by: '<S131>/Filter'

  0.02,

  // Expression: 0
  //  Referenced by: '<S129>/ZeroGain'

  0.0
};

//
// File trailer for generated code.
//
// [EOF]
//
