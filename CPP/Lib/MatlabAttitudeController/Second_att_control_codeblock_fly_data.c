/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Second_att_control_codeblock_fly_data.c
 *
 * Code generated for Simulink model 'Second_att_control_codeblock_fly'.
 *
 * Model version                  : 1.29
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Sun Aug  9 19:55:33 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "../MatlabAttitudeController/Second_att_control_codeblock_fly.h"
#include "../MatlabAttitudeController/Second_att_control_codeblock_fly_private.h"

/* Block parameters (default storage) */
P_Second_att_control_codebloc_T Second_att_control_codeblock__P = {
  /* Mask Parameter: DiscreteDerivative_ICPrevScaled
   * Referenced by: '<S8>/UD'
   */
  0.0F,

  /* Mask Parameter: DiscreteDerivative1_ICPrevScale
   * Referenced by: '<S9>/UD'
   */
  0.0F,

  /* Mask Parameter: DiscretePIDController_InitialCo
   * Referenced by: '<S42>/Integrator'
   */
  0.0F,

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

  /* Computed Parameter: DiscreteTimeIntegrator_gainval
   * Referenced by: '<S5>/Discrete-Time Integrator'
   */
  0.005F,

  /* Computed Parameter: DiscreteTimeIntegrator_IC
   * Referenced by: '<S5>/Discrete-Time Integrator'
   */
  0.0F,

  /* Computed Parameter: DiscreteTimeIntegrator_gainva_l
   * Referenced by: '<S6>/Discrete-Time Integrator'
   */
  0.005F,

  /* Computed Parameter: DiscreteTimeIntegrator_IC_k
   * Referenced by: '<S6>/Discrete-Time Integrator'
   */
  0.0F,

  /* Computed Parameter: TSamp_WtEt
   * Referenced by: '<S8>/TSamp'
   */
  200.0F,

  /* Computed Parameter: Saturation_UpperSat
   * Referenced by: '<S6>/Saturation'
   */
  8.0F,

  /* Computed Parameter: Saturation_LowerSat
   * Referenced by: '<S6>/Saturation'
   */
  -8.0F,

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S6>/Gain'
   */
  0.125F,

  /* Computed Parameter: DiscreteTimeIntegrator1_gainval
   * Referenced by: '<S5>/Discrete-Time Integrator1'
   */
  0.005F,

  /* Computed Parameter: DiscreteTimeIntegrator1_IC
   * Referenced by: '<S5>/Discrete-Time Integrator1'
   */
  0.0F,

  /* Computed Parameter: DiscreteTimeIntegrator1_gainv_k
   * Referenced by: '<S6>/Discrete-Time Integrator1'
   */
  0.005F,

  /* Computed Parameter: DiscreteTimeIntegrator1_IC_j
   * Referenced by: '<S6>/Discrete-Time Integrator1'
   */
  0.0F,

  /* Computed Parameter: TSamp_WtEt_l
   * Referenced by: '<S9>/TSamp'
   */
  200.0F,

  /* Computed Parameter: Saturation1_UpperSat
   * Referenced by: '<S6>/Saturation1'
   */
  8.0F,

  /* Computed Parameter: Saturation1_LowerSat
   * Referenced by: '<S6>/Saturation1'
   */
  -8.0F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<S6>/Gain1'
   */
  0.125F,

  /* Computed Parameter: Saturation7_UpperSat
   * Referenced by: '<S3>/Saturation7'
   */
  1.0F,

  /* Computed Parameter: Saturation7_LowerSat
   * Referenced by: '<S3>/Saturation7'
   */
  -1.0F,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S42>/Integrator'
   */
  0.005F,

  /* Computed Parameter: Saturation10_UpperSat
   * Referenced by: '<S3>/Saturation10'
   */
  1.0F,

  /* Computed Parameter: Saturation10_LowerSat
   * Referenced by: '<S3>/Saturation10'
   */
  0.0F,

  /* Computed Parameter: Delay_InitialCondition
   * Referenced by: '<S6>/Delay'
   */
  0.0F,

  /* Computed Parameter: antiWU_Gain_Gain
   * Referenced by: '<S6>/antiWU_Gain'
   */
  0.005F,

  /* Computed Parameter: Delay1_InitialCondition
   * Referenced by: '<S6>/Delay1'
   */
  0.0F,

  /* Computed Parameter: antiWU_Gain1_Gain
   * Referenced by: '<S6>/antiWU_Gain1'
   */
  0.005F,

  /* Computed Parameter: Saturation_UpperSat_d
   * Referenced by: '<S1>/Saturation'
   */
  2000U,

  /* Computed Parameter: Saturation_LowerSat_i
   * Referenced by: '<S1>/Saturation'
   */
  1000U,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S1>/Constant'
   */
  990U,

  /* Computed Parameter: Switch_Threshold
   * Referenced by: '<S1>/Switch'
   */
  1500U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
