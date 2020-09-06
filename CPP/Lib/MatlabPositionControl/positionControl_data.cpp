//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl_data.cpp
//
// Code generated for Simulink model 'positionControl'.
//
// Model version                  : 1.16
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Fri Sep  4 20:36:03 2020
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
  // Variable: vel_Horizon_Max
  //  Referenced by:
  //    '<S47>/Saturation'
  //    '<S193>/Saturation'

  2.0,

  // Variable: vel_climbMax
  //  Referenced by:
  //    '<S275>/DeadZone'
  //    '<S289>/Saturation'

  1.0,

  // Variable: vel_descentMax
  //  Referenced by:
  //    '<S275>/DeadZone'
  //    '<S289>/Saturation'

  1.0,

  // Mask Parameter: PIDController3_DifferentiatorIC
  //  Referenced by: '<S131>/UD'

  0.0,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S35>/Filter'

  0.0,

  // Mask Parameter: PIDController4_InitialCondition
  //  Referenced by: '<S181>/Filter'

  0.0,

  // Mask Parameter: PIDController5_InitialCondition
  //  Referenced by: '<S229>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S83>/Filter'

  0.0,

  // Mask Parameter: ZPostoVel_InitialConditionForFi
  //  Referenced by: '<S277>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_c
  //  Referenced by: '<S40>/Integrator'

  0.0,

  // Mask Parameter: PIDController4_InitialConditi_i
  //  Referenced by: '<S186>/Integrator'

  0.0,

  // Mask Parameter: PIDController5_InitialConditi_c
  //  Referenced by: '<S234>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_a
  //  Referenced by: '<S88>/Integrator'

  0.0,

  // Mask Parameter: ZPostoVel_InitialConditionForIn
  //  Referenced by: '<S282>/Integrator'

  0.0,

  // Mask Parameter: PIDController3_InitialCondition
  //  Referenced by: '<S138>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_Kb
  //  Referenced by: '<S81>/Kb'

  0.01,

  // Mask Parameter: PIDController5_Kb
  //  Referenced by: '<S227>/Kb'

  0.01,

  // Mask Parameter: PIDController5_LowerSaturationL
  //  Referenced by: '<S241>/Saturation'

  -1.0,

  // Mask Parameter: PIDController1_LowerSaturationL
  //  Referenced by: '<S95>/Saturation'

  -1.0,

  // Mask Parameter: PIDController3_LowerSaturationL
  //  Referenced by:
  //    '<S129>/DeadZone'
  //    '<S145>/Saturation'

  -0.1,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S43>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController4_N
  //  Referenced by: '<S189>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController5_N
  //  Referenced by: '<S237>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S91>/Filter Coefficient'

  10.0,

  // Mask Parameter: ZPostoVel_N
  //  Referenced by: '<S285>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController5_UpperSaturationL
  //  Referenced by: '<S241>/Saturation'

  1.0,

  // Mask Parameter: PIDController1_UpperSaturationL
  //  Referenced by: '<S95>/Saturation'

  1.0,

  // Mask Parameter: PIDController3_UpperSaturationL
  //  Referenced by:
  //    '<S129>/DeadZone'
  //    '<S145>/Saturation'

  0.5,

  // Expression: 0
  //  Referenced by: '<S129>/Constant1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S275>/Constant1'

  0.0,

  // Expression: -1
  //  Referenced by: '<S8>/Gain'

  -1.0,

  // Computed Parameter: Integrator_gainval
  //  Referenced by: '<S40>/Integrator'

  0.01,

  // Computed Parameter: Filter_gainval
  //  Referenced by: '<S35>/Filter'

  0.01,

  // Computed Parameter: Integrator_gainval_l
  //  Referenced by: '<S186>/Integrator'

  0.01,

  // Computed Parameter: Filter_gainval_l
  //  Referenced by: '<S181>/Filter'

  0.01,

  // Computed Parameter: Integrator_gainval_k
  //  Referenced by: '<S234>/Integrator'

  0.01,

  // Computed Parameter: Filter_gainval_i
  //  Referenced by: '<S229>/Filter'

  0.01,

  // Computed Parameter: Integrator_gainval_lc
  //  Referenced by: '<S88>/Integrator'

  0.01,

  // Computed Parameter: Filter_gainval_l5
  //  Referenced by: '<S83>/Filter'

  0.01,

  // Expression: -1
  //  Referenced by: '<S1>/Gain1'

  -1.0,

  // Expression: -1
  //  Referenced by: '<S1>/Gain2'

  -1.0,

  // Computed Parameter: Integrator_gainval_j
  //  Referenced by: '<S282>/Integrator'

  0.01,

  // Computed Parameter: Filter_gainval_c
  //  Referenced by: '<S277>/Filter'

  0.01,

  // Expression: -1
  //  Referenced by: '<S1>/Gain3'

  -1.0,

  // Computed Parameter: Integrator_gainval_a
  //  Referenced by: '<S138>/Integrator'

  0.01,

  // Computed Parameter: Tsamp_WtEt
  //  Referenced by: '<S133>/Tsamp'

  100.0,

  // Expression: 1
  //  Referenced by: '<S1>/Saturation'

  1.0,

  // Expression: 0
  //  Referenced by: '<S1>/Saturation'

  0.0,

  // Expression: 0
  //  Referenced by: '<S129>/ZeroGain'

  0.0,

  // Expression: 0
  //  Referenced by: '<S275>/ZeroGain'

  0.0
};

//
// File trailer for generated code.
//
// [EOF]
//
