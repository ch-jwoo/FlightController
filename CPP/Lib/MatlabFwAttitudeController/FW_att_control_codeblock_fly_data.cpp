//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: FW_att_control_codeblock_fly_data.cpp
//
// Code generated for Simulink model 'FW_att_control_codeblock_fly'.
//
// Model version                  : 1.52
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Fri Oct  2 16:09:59 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include <MatlabFwAttitudeController/FW_att_control_codeblock_fly.h>
#include <MatlabFwAttitudeController/FW_att_control_codeblock_fly_private.h>

// Block parameters (default storage)
FW_px4_AlgorithmModelClass::P_FW_att_control_codeblock_fl_T FW_px4_AlgorithmModelClass::
  FW_att_control_codeblock_fly_P = {
  // Variable: FW_Angle_rate_pitch_kI
  //  Referenced by: '<S4>/I_pr1'

  1.0F,

  // Variable: FW_Angle_rate_pitch_kP
  //  Referenced by: '<S4>/P_pr1'

  4.0F,

  // Variable: FW_Angle_rate_roll_PI_kI
  //  Referenced by: '<S4>/I_pr'

  1.0F,

  // Variable: FW_Angle_rate_roll_PI_kP
  //  Referenced by: '<S4>/P_pr'

  4.0F,

  // Variable: FW_Max_angle_coef
  //  Referenced by: '<S1>/FW_Max_angle_coef'

  0.5F,

  // Variable: FW_Yaw_angel_rate_P
  //  Referenced by: '<S6>/Gain'

  2.0F,

  // Variable: FW_kD_Pitch_rate_PID
  //  Referenced by: '<S5>/D_pr1'

  0.0F,

  // Variable: FW_kD_Roll_rate_PID
  //  Referenced by: '<S5>/D_pr'

  0.0F,

  // Variable: FW_kI_Pitch_rate_PID
  //  Referenced by: '<S5>/I_pr1'

  0.03F,

  // Variable: FW_kI_Roll_rate_PID
  //  Referenced by: '<S5>/I_pr'

  0.03F,

  // Variable: FW_kI_Yaw_rate_PID
  //  Referenced by: '<S38>/Integral Gain'

  0.2F,

  // Variable: FW_kP_Pitch_rate_PID
  //  Referenced by: '<S5>/P_pr1'

  0.3F,

  // Variable: FW_kP_Roll_rate_PID
  //  Referenced by: '<S5>/P_pr'

  0.3F,

  // Variable: FW_kP_Yaw_rate_PID
  //  Referenced by: '<S46>/Proportional Gain'

  0.3F,

  // Mask Parameter: DiscreteDerivative_ICPrevScaled
  //  Referenced by: '<S7>/UD'

  0.0F,

  // Mask Parameter: DiscreteDerivative1_ICPrevScale
  //  Referenced by: '<S8>/UD'

  0.0F,

  // Mask Parameter: DiscretePIDController_InitialCo
  //  Referenced by: '<S41>/Integrator'

  0.0F,

  // Computed Parameter: roll_dircection_Gain
  //  Referenced by: '<Root>/roll_dircection'

  1.0F,

  // Computed Parameter: pitch_direction_Gain
  //  Referenced by: '<Root>/pitch_direction'

  1.0F,

  // Computed Parameter: DiscreteTimeIntegrator_gainval
  //  Referenced by: '<S4>/Discrete-Time Integrator'

  0.005F,

  // Computed Parameter: DiscreteTimeIntegrator_IC
  //  Referenced by: '<S4>/Discrete-Time Integrator'

  0.0F,

  // Computed Parameter: DiscreteTimeIntegrator_gainva_l
  //  Referenced by: '<S5>/Discrete-Time Integrator'

  0.005F,

  // Computed Parameter: DiscreteTimeIntegrator_IC_k
  //  Referenced by: '<S5>/Discrete-Time Integrator'

  0.0F,

  // Computed Parameter: TSamp_WtEt
  //  Referenced by: '<S7>/TSamp'

  200.0F,

  // Computed Parameter: Roll_rate_UpperSat
  //  Referenced by: '<S5>/Roll_rate'

  1.0F,

  // Computed Parameter: Roll_rate_LowerSat
  //  Referenced by: '<S5>/Roll_rate'

  -1.0F,

  // Computed Parameter: DiscreteTimeIntegrator1_gainval
  //  Referenced by: '<S4>/Discrete-Time Integrator1'

  0.005F,

  // Computed Parameter: DiscreteTimeIntegrator1_IC
  //  Referenced by: '<S4>/Discrete-Time Integrator1'

  0.0F,

  // Computed Parameter: DiscreteTimeIntegrator1_gainv_k
  //  Referenced by: '<S5>/Discrete-Time Integrator1'

  0.005F,

  // Computed Parameter: DiscreteTimeIntegrator1_IC_j
  //  Referenced by: '<S5>/Discrete-Time Integrator1'

  0.0F,

  // Computed Parameter: TSamp_WtEt_l
  //  Referenced by: '<S8>/TSamp'

  200.0F,

  // Computed Parameter: Pitch_rate_UpperSat
  //  Referenced by: '<S5>/Pitch_rate'

  1.0F,

  // Computed Parameter: Pitch_rate_LowerSat
  //  Referenced by: '<S5>/Pitch_rate'

  -1.0F,

  // Computed Parameter: Integrator_gainval
  //  Referenced by: '<S41>/Integrator'

  0.005F,

  // Computed Parameter: Delay_InitialCondition
  //  Referenced by: '<S5>/Delay'

  0.0F,

  // Computed Parameter: antiWU_Gain_Gain
  //  Referenced by: '<S5>/antiWU_Gain'

  0.005F,

  // Computed Parameter: Delay1_InitialCondition
  //  Referenced by: '<S5>/Delay1'

  0.0F,

  // Computed Parameter: antiWU_Gain1_Gain
  //  Referenced by: '<S5>/antiWU_Gain1'

  0.005F,

  // Computed Parameter: Saturation_UpperSat
  //  Referenced by: '<S1>/Saturation'

  2000U,

  // Computed Parameter: Saturation_LowerSat
  //  Referenced by: '<S1>/Saturation'

  1000U
};

//
// File trailer for generated code.
//
// [EOF]
//
