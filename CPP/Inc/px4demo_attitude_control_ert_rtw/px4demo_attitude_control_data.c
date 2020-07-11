/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: px4demo_attitude_control_data.c
 *
 * Code generated for Simulink model 'px4demo_attitude_control'.
 *
 * Model version                  : 1.25
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Sat Jul 11 16:13:56 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "px4demo_attitude_control.h"
#include "px4demo_attitude_control_private.h"

/* Block parameters (default storage) */
P_px4demo_attitude_control_T px4demo_attitude_control_P = {
  /* Variable: KiPitchAttitude
   * Referenced by: '<S39>/Integral Gain'
   */
  0.046025265F,

  /* Variable: KiPitchRate
   * Referenced by: '<S87>/Integral Gain'
   */
  0.383615583F,

  /* Variable: KiRollAttitude
   * Referenced by: '<S135>/Integral Gain'
   */
  0.046025265F,

  /* Variable: KiRollRate
   * Referenced by: '<S183>/Integral Gain'
   */
  0.383615583F,

  /* Variable: KiYawRate
   * Referenced by: '<S231>/Integral Gain'
   */
  0.383615583F,

  /* Variable: KpPitchAttitude
   * Referenced by: '<S47>/Proportional Gain'
   */
  0.52511555F,

  /* Variable: KpPitchRate
   * Referenced by: '<S95>/Proportional Gain'
   */
  1.09611535F,

  /* Variable: KpRollAttitude
   * Referenced by: '<S143>/Proportional Gain'
   */
  0.52511555F,

  /* Variable: KpRollRate
   * Referenced by: '<S191>/Proportional Gain'
   */
  1.09611535F,

  /* Variable: KpYawRate
   * Referenced by: '<S239>/Proportional Gain'
   */
  1.09611535F,

  /* Mask Parameter: yaw_rate_InitialConditionForIntegrator
   * Referenced by: '<S234>/Integrator'
   */
  0.0,

  /* Mask Parameter: yaw_rate_Kb
   * Referenced by: '<S227>/Kb'
   */
  1.0,

  /* Mask Parameter: yaw_rate_LowerSaturationLimit
   * Referenced by: '<S241>/Saturation'
   */
  -1.0,

  /* Mask Parameter: yaw_rate_UpperSaturationLimit
   * Referenced by: '<S241>/Saturation'
   */
  1.0,

  /* Mask Parameter: roll_attitude_InitialConditionForIntegrator
   * Referenced by: '<S138>/Integrator'
   */
  0.0F,

  /* Mask Parameter: roll_rate_InitialConditionForIntegrator
   * Referenced by: '<S186>/Integrator'
   */
  0.0F,

  /* Mask Parameter: pitch_attitude_InitialConditionForIntegrator
   * Referenced by: '<S42>/Integrator'
   */
  0.0F,

  /* Mask Parameter: pitch_rate_InitialConditionForIntegrator
   * Referenced by: '<S90>/Integrator'
   */
  0.0F,

  /* Mask Parameter: pitch_rate_Kb
   * Referenced by: '<S83>/Kb'
   */
  1.0F,

  /* Mask Parameter: pitch_attitude_Kb
   * Referenced by: '<S35>/Kb'
   */
  1.0F,

  /* Mask Parameter: roll_rate_Kb
   * Referenced by: '<S179>/Kb'
   */
  1.0F,

  /* Mask Parameter: roll_attitude_Kb
   * Referenced by: '<S131>/Kb'
   */
  1.0F,

  /* Mask Parameter: roll_attitude_LowerSaturationLimit
   * Referenced by: '<S145>/Saturation'
   */
  -1.0F,

  /* Mask Parameter: roll_rate_LowerSaturationLimit
   * Referenced by: '<S193>/Saturation'
   */
  -1.0F,

  /* Mask Parameter: pitch_attitude_LowerSaturationLimit
   * Referenced by: '<S49>/Saturation'
   */
  -1.0F,

  /* Mask Parameter: pitch_rate_LowerSaturationLimit
   * Referenced by: '<S97>/Saturation'
   */
  -1.0F,

  /* Mask Parameter: roll_attitude_UpperSaturationLimit
   * Referenced by: '<S145>/Saturation'
   */
  1.0F,

  /* Mask Parameter: roll_rate_UpperSaturationLimit
   * Referenced by: '<S193>/Saturation'
   */
  1.0F,

  /* Mask Parameter: pitch_attitude_UpperSaturationLimit
   * Referenced by: '<S49>/Saturation'
   */
  1.0F,

  /* Mask Parameter: pitch_rate_UpperSaturationLimit
   * Referenced by: '<S97>/Saturation'
   */
  1.0F,

  /* Mask Parameter: CompareToConstant3_const
   * Referenced by: '<S5>/Constant'
   */
  1500U,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S234>/Integrator'
   */
  0.004,

  /* Computed Parameter: urads_max_Gain
   * Referenced by: '<S2>/1 // rads_max'
   */
  0.333333343F,

  /* Computed Parameter: urad_max_Gain
   * Referenced by: '<S2>/1 // rad_max'
   */
  1.0F,

  /* Computed Parameter: Saturation9_UpperSat
   * Referenced by: '<S3>/Saturation9'
   */
  1.0F,

  /* Computed Parameter: Saturation9_LowerSat
   * Referenced by: '<S3>/Saturation9'
   */
  -1.0F,

  /* Computed Parameter: Saturation8_UpperSat
   * Referenced by: '<S3>/Saturation8'
   */
  1.0F,

  /* Computed Parameter: Saturation8_LowerSat
   * Referenced by: '<S3>/Saturation8'
   */
  -1.0F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<S3>/Gain2'
   */
  { 1.0F, -1.0F },

  /* Computed Parameter: Integrator_gainval_i
   * Referenced by: '<S138>/Integrator'
   */
  0.004F,

  /* Computed Parameter: Integrator_gainval_h
   * Referenced by: '<S186>/Integrator'
   */
  0.004F,

  /* Computed Parameter: Integrator_gainval_d
   * Referenced by: '<S42>/Integrator'
   */
  0.004F,

  /* Computed Parameter: Integrator_gainval_dp
   * Referenced by: '<S90>/Integrator'
   */
  0.004F,

  /* Computed Parameter: urads_max_yaw_Gain
   * Referenced by: '<S2>/1 // rads_max_yaw'
   */
  0.25F,

  /* Computed Parameter: Saturation7_UpperSat
   * Referenced by: '<S3>/Saturation7'
   */
  1.0F,

  /* Computed Parameter: Saturation7_LowerSat
   * Referenced by: '<S3>/Saturation7'
   */
  -1.0F,

  /* Computed Parameter: Saturation10_UpperSat
   * Referenced by: '<S3>/Saturation10'
   */
  1.0F,

  /* Computed Parameter: Saturation10_LowerSat
   * Referenced by: '<S3>/Saturation10'
   */
  0.0F,

  /* Computed Parameter: Output_Limits1_UpperSat
   * Referenced by: '<Root>/Output_Limits1'
   */
  2000U,

  /* Computed Parameter: Output_Limits1_LowerSat
   * Referenced by: '<Root>/Output_Limits1'
   */
  1000U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
