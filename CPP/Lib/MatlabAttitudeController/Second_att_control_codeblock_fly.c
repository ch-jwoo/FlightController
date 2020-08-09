/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Second_att_control_codeblock_fly.c
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

/* Exported block parameters */
real32_T Angle_rate_pitch_kI = 1.0F;   /* Variable: Angle_rate_pitch_kI
                                        * Referenced by: '<S5>/I_pr1'
                                        */
real32_T Angle_rate_pitch_kP = 4.0F;   /* Variable: Angle_rate_pitch_kP
                                        * Referenced by: '<S5>/P_pr1'
                                        */
real32_T Angle_rate_roll_PI_kI = 1.0F; /* Variable: Angle_rate_roll_PI_kI
                                        * Referenced by: '<S5>/I_pr'
                                        */
real32_T Angle_rate_roll_PI_kP = 4.0F; /* Variable: Angle_rate_roll_PI_kP
                                        * Referenced by: '<S5>/P_pr'
                                        */
real32_T Yaw_angel_rate_P = 2.0F;      /* Variable: Yaw_angel_rate_P
                                        * Referenced by: '<S7>/Gain'
                                        */
real32_T kD_Pitch_rate_PID = 0.03F;    /* Variable: kD_Pitch_rate_PID
                                        * Referenced by: '<S6>/D_pr1'
                                        */
real32_T kD_Roll_rate_PID = 0.03F;     /* Variable: kD_Roll_rate_PID
                                        * Referenced by: '<S6>/D_pr'
                                        */
real32_T kI_Pitch_rate_PID = 0.3F;     /* Variable: kI_Pitch_rate_PID
                                        * Referenced by: '<S6>/I_pr1'
                                        */
real32_T kI_Roll_rate_PID = 0.3F;      /* Variable: kI_Roll_rate_PID
                                        * Referenced by: '<S6>/I_pr'
                                        */
real32_T kI_Yaw_rate_PID = 0.0F;       /* Variable: kI_Yaw_rate_PID
                                        * Referenced by: '<S39>/Integral Gain'
                                        */
real32_T kP_Pitch_rate_PID = 3.0F;     /* Variable: kP_Pitch_rate_PID
                                        * Referenced by: '<S6>/P_pr1'
                                        */
real32_T kP_Roll_rate_PID = 3.0F;      /* Variable: kP_Roll_rate_PID
                                        * Referenced by: '<S6>/P_pr'
                                        */
real32_T kP_Yaw_rate_PID = 0.0F;       /* Variable: kP_Yaw_rate_PID
                                        * Referenced by: '<S47>/Proportional Gain'
                                        */

/* Exported data definition */

/* Const memory section */
/* Definition for custom storage class: Const */
const real32_T Max_angle_coef = 0.5F;  /* Referenced by: '<S3>/Gain' */

/* Block signals (default storage) */
B_Second_att_control_codebloc_T Second_att_control_codeblock__B;

/* Block states (default storage) */
DW_Second_att_control_codeblo_T Second_att_control_codeblock_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Second_att_control_codeb_T Second_att_control_codeblock__U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Second_att_control_codeb_T Second_att_control_codeblock__Y;
real32_T rt_roundf_snf(real32_T u)
{
  real32_T y;
  if ((real32_T)fabs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (real32_T)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = (real32_T)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void Second_att_control_codeblock_fly_step(void)
{
  int32_T i;
  uint32_T tmp;
  uint16_T y;
  real32_T u0;
  real32_T u1;
  real32_T u2;

  /* DataTypeConversion: '<S3>/Data Type Conversion' incorporates:
   *  Inport: '<Root>/set_roll'
   */
  Second_att_control_codeblock__B.DataTypeConversion =
    Second_att_control_codeblock__U.set_roll;

  /* Fcn: '<S3>/Fcn2' */
  Second_att_control_codeblock__B.Fcn2 =
    (Second_att_control_codeblock__B.DataTypeConversion - 1500.0F) / 500.0F;

  /* Saturate: '<S3>/Saturation9' */
  u0 = Second_att_control_codeblock__B.Fcn2;
  u1 = Second_att_control_codeblock__P.Saturation9_LowerSat;
  u2 = Second_att_control_codeblock__P.Saturation9_UpperSat;
  if (u0 > u2) {
    Second_att_control_codeblock__B.Saturation9 = u2;
  } else if (u0 < u1) {
    Second_att_control_codeblock__B.Saturation9 = u1;
  } else {
    Second_att_control_codeblock__B.Saturation9 = u0;
  }

  /* End of Saturate: '<S3>/Saturation9' */

  /* DataTypeConversion: '<S3>/Data Type Conversion1' incorporates:
   *  Inport: '<Root>/set_pitch'
   */
  Second_att_control_codeblock__B.DataTypeConversion1 =
    Second_att_control_codeblock__U.set_pitch;

  /* Fcn: '<S3>/Fcn5' */
  Second_att_control_codeblock__B.Fcn5 =
    (Second_att_control_codeblock__B.DataTypeConversion1 - 1500.0F) / 500.0F;

  /* Saturate: '<S3>/Saturation8' */
  u0 = Second_att_control_codeblock__B.Fcn5;
  u1 = Second_att_control_codeblock__P.Saturation8_LowerSat;
  u2 = Second_att_control_codeblock__P.Saturation8_UpperSat;
  if (u0 > u2) {
    Second_att_control_codeblock__B.Saturation8 = u2;
  } else if (u0 < u1) {
    Second_att_control_codeblock__B.Saturation8 = u1;
  } else {
    Second_att_control_codeblock__B.Saturation8 = u0;
  }

  /* End of Saturate: '<S3>/Saturation8' */

  /* Gain: '<S3>/Gain2' */
  Second_att_control_codeblock__B.Gain2[0] =
    Second_att_control_codeblock__P.Gain2_Gain[0] *
    Second_att_control_codeblock__B.Saturation9;
  Second_att_control_codeblock__B.Gain2[1] =
    Second_att_control_codeblock__P.Gain2_Gain[1] *
    Second_att_control_codeblock__B.Saturation8;

  /* Gain: '<S3>/Gain' */
  Second_att_control_codeblock__B.Gain[0] = Max_angle_coef *
    Second_att_control_codeblock__B.Gain2[0];
  Second_att_control_codeblock__B.Gain[1] = Max_angle_coef *
    Second_att_control_codeblock__B.Gain2[1];

  /* Sum: '<S5>/Sum' incorporates:
   *  Inport: '<Root>/Roll'
   */
  Second_att_control_codeblock__B.pitchrollerror =
    Second_att_control_codeblock__B.Gain[0] -
    Second_att_control_codeblock__U.Roll;

  /* Gain: '<S5>/P_pr' */
  Second_att_control_codeblock__B.P_pr = Angle_rate_roll_PI_kP *
    Second_att_control_codeblock__B.pitchrollerror;

  /* DiscreteIntegrator: '<S5>/Discrete-Time Integrator' */
  Second_att_control_codeblock__B.DiscreteTimeIntegrator =
    Second_att_control_codeblock_DW.DiscreteTimeIntegrator_DSTATE;

  /* Gain: '<S5>/I_pr' */
  Second_att_control_codeblock__B.I_pr = Angle_rate_roll_PI_kI *
    Second_att_control_codeblock__B.DiscreteTimeIntegrator;

  /* Sum: '<S5>/Sum16' */
  Second_att_control_codeblock__B.P_pr_m = Second_att_control_codeblock__B.P_pr
    + Second_att_control_codeblock__B.I_pr;

  /* Sum: '<S6>/Sum' incorporates:
   *  Inport: '<Root>/p'
   */
  Second_att_control_codeblock__B.pitchrollerror_b =
    Second_att_control_codeblock__B.P_pr_m - Second_att_control_codeblock__U.p;

  /* Gain: '<S6>/P_pr' */
  Second_att_control_codeblock__B.P_pr_b = kP_Roll_rate_PID *
    Second_att_control_codeblock__B.pitchrollerror_b;

  /* DiscreteIntegrator: '<S6>/Discrete-Time Integrator' */
  Second_att_control_codeblock__B.DiscreteTimeIntegrator_h =
    Second_att_control_codeblock_DW.DiscreteTimeIntegrator_DSTATE_k;

  /* Gain: '<S6>/I_pr' */
  Second_att_control_codeblock__B.I_pr_d = kI_Roll_rate_PID *
    Second_att_control_codeblock__B.DiscreteTimeIntegrator_h;

  /* SampleTimeMath: '<S8>/TSamp'
   *
   * About '<S8>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  Second_att_control_codeblock__B.TSamp =
    Second_att_control_codeblock__B.pitchrollerror_b *
    Second_att_control_codeblock__P.TSamp_WtEt;

  /* UnitDelay: '<S8>/UD'
   *
   * Block description for '<S8>/UD':
   *
   *  Store in Global RAM
   */
  Second_att_control_codeblock__B.Uk1 =
    Second_att_control_codeblock_DW.UD_DSTATE;

  /* Sum: '<S8>/Diff'
   *
   * Block description for '<S8>/Diff':
   *
   *  Add in CPU
   */
  Second_att_control_codeblock__B.Diff = Second_att_control_codeblock__B.TSamp -
    Second_att_control_codeblock__B.Uk1;

  /* Gain: '<S6>/D_pr' */
  Second_att_control_codeblock__B.D_pr = kD_Roll_rate_PID *
    Second_att_control_codeblock__B.Diff;

  /* Sum: '<S6>/Sum16' */
  Second_att_control_codeblock__B.P_pr_d =
    (Second_att_control_codeblock__B.P_pr_b +
     Second_att_control_codeblock__B.I_pr_d) +
    Second_att_control_codeblock__B.D_pr;

  /* Saturate: '<S6>/Saturation' */
  u0 = Second_att_control_codeblock__B.P_pr_d;
  u1 = Second_att_control_codeblock__P.Saturation_LowerSat;
  u2 = Second_att_control_codeblock__P.Saturation_UpperSat;
  if (u0 > u2) {
    Second_att_control_codeblock__B.Saturation = u2;
  } else if (u0 < u1) {
    Second_att_control_codeblock__B.Saturation = u1;
  } else {
    Second_att_control_codeblock__B.Saturation = u0;
  }

  /* End of Saturate: '<S6>/Saturation' */

  /* Gain: '<S6>/Gain' */
  Second_att_control_codeblock__B.Gain_p =
    Second_att_control_codeblock__P.Gain_Gain *
    Second_att_control_codeblock__B.Saturation;

  /* Sum: '<S5>/Sum2' incorporates:
   *  Inport: '<Root>/Pitch'
   */
  Second_att_control_codeblock__B.pitchrollerror_m =
    Second_att_control_codeblock__B.Gain[1] -
    Second_att_control_codeblock__U.Pitch;

  /* Gain: '<S5>/P_pr1' */
  Second_att_control_codeblock__B.P_pr1 = Angle_rate_pitch_kP *
    Second_att_control_codeblock__B.pitchrollerror_m;

  /* DiscreteIntegrator: '<S5>/Discrete-Time Integrator1' */
  Second_att_control_codeblock__B.DiscreteTimeIntegrator1 =
    Second_att_control_codeblock_DW.DiscreteTimeIntegrator1_DSTATE;

  /* Gain: '<S5>/I_pr1' */
  Second_att_control_codeblock__B.I_pr1 = Angle_rate_pitch_kI *
    Second_att_control_codeblock__B.DiscreteTimeIntegrator1;

  /* Sum: '<S5>/Sum1' */
  Second_att_control_codeblock__B.P_pr_o = Second_att_control_codeblock__B.P_pr1
    + Second_att_control_codeblock__B.I_pr1;

  /* Sum: '<S6>/Sum1' incorporates:
   *  Inport: '<Root>/q'
   */
  Second_att_control_codeblock__B.pitchrollerror_i =
    Second_att_control_codeblock__B.P_pr_o - Second_att_control_codeblock__U.q;

  /* Gain: '<S6>/P_pr1' */
  Second_att_control_codeblock__B.P_pr1_p = kP_Pitch_rate_PID *
    Second_att_control_codeblock__B.pitchrollerror_i;

  /* DiscreteIntegrator: '<S6>/Discrete-Time Integrator1' */
  Second_att_control_codeblock__B.DiscreteTimeIntegrator1_p =
    Second_att_control_codeblock_DW.DiscreteTimeIntegrator1_DSTAT_d;

  /* Gain: '<S6>/I_pr1' */
  Second_att_control_codeblock__B.I_pr1_j = kI_Pitch_rate_PID *
    Second_att_control_codeblock__B.DiscreteTimeIntegrator1_p;

  /* SampleTimeMath: '<S9>/TSamp'
   *
   * About '<S9>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  Second_att_control_codeblock__B.TSamp_h =
    Second_att_control_codeblock__B.pitchrollerror_i *
    Second_att_control_codeblock__P.TSamp_WtEt_l;

  /* UnitDelay: '<S9>/UD'
   *
   * Block description for '<S9>/UD':
   *
   *  Store in Global RAM
   */
  Second_att_control_codeblock__B.Uk1_i =
    Second_att_control_codeblock_DW.UD_DSTATE_e;

  /* Sum: '<S9>/Diff'
   *
   * Block description for '<S9>/Diff':
   *
   *  Add in CPU
   */
  Second_att_control_codeblock__B.Diff_l =
    Second_att_control_codeblock__B.TSamp_h -
    Second_att_control_codeblock__B.Uk1_i;

  /* Gain: '<S6>/D_pr1' */
  Second_att_control_codeblock__B.D_pr1 = kD_Pitch_rate_PID *
    Second_att_control_codeblock__B.Diff_l;

  /* Sum: '<S6>/Sum2' */
  Second_att_control_codeblock__B.P_pr_j =
    (Second_att_control_codeblock__B.P_pr1_p +
     Second_att_control_codeblock__B.I_pr1_j) +
    Second_att_control_codeblock__B.D_pr1;

  /* Saturate: '<S6>/Saturation1' */
  u0 = Second_att_control_codeblock__B.P_pr_j;
  u1 = Second_att_control_codeblock__P.Saturation1_LowerSat;
  u2 = Second_att_control_codeblock__P.Saturation1_UpperSat;
  if (u0 > u2) {
    Second_att_control_codeblock__B.Saturation1 = u2;
  } else if (u0 < u1) {
    Second_att_control_codeblock__B.Saturation1 = u1;
  } else {
    Second_att_control_codeblock__B.Saturation1 = u0;
  }

  /* End of Saturate: '<S6>/Saturation1' */

  /* Gain: '<S6>/Gain1' */
  Second_att_control_codeblock__B.Gain1 =
    Second_att_control_codeblock__P.Gain1_Gain *
    Second_att_control_codeblock__B.Saturation1;

  /* DataTypeConversion: '<S3>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/set_yaw'
   */
  Second_att_control_codeblock__B.DataTypeConversion2 =
    Second_att_control_codeblock__U.set_yaw;

  /* Fcn: '<S3>/Fcn7' */
  Second_att_control_codeblock__B.Fcn7 =
    (Second_att_control_codeblock__B.DataTypeConversion2 - 1500.0F) / 500.0F;

  /* Saturate: '<S3>/Saturation7' */
  u0 = Second_att_control_codeblock__B.Fcn7;
  u1 = Second_att_control_codeblock__P.Saturation7_LowerSat;
  u2 = Second_att_control_codeblock__P.Saturation7_UpperSat;
  if (u0 > u2) {
    Second_att_control_codeblock__B.Saturation7 = u2;
  } else if (u0 < u1) {
    Second_att_control_codeblock__B.Saturation7 = u1;
  } else {
    Second_att_control_codeblock__B.Saturation7 = u0;
  }

  /* End of Saturate: '<S3>/Saturation7' */

  /* Sum: '<S7>/Sum' incorporates:
   *  Inport: '<Root>/r'
   */
  Second_att_control_codeblock__B.Sum =
    Second_att_control_codeblock__B.Saturation7 -
    Second_att_control_codeblock__U.r;

  /* Gain: '<S7>/Gain' */
  Second_att_control_codeblock__B.Gain_f = Yaw_angel_rate_P *
    Second_att_control_codeblock__B.Sum;

  /* Gain: '<S47>/Proportional Gain' */
  Second_att_control_codeblock__B.ProportionalGain = kP_Yaw_rate_PID *
    Second_att_control_codeblock__B.Gain_f;

  /* DiscreteIntegrator: '<S42>/Integrator' */
  Second_att_control_codeblock__B.Integrator =
    Second_att_control_codeblock_DW.Integrator_DSTATE;

  /* Sum: '<S51>/Sum' */
  Second_att_control_codeblock__B.Sum_f =
    Second_att_control_codeblock__B.ProportionalGain +
    Second_att_control_codeblock__B.Integrator;

  /* DataTypeConversion: '<S3>/Data Type Conversion3' incorporates:
   *  Inport: '<Root>/set_thrust'
   */
  Second_att_control_codeblock__B.DataTypeConversion3 =
    Second_att_control_codeblock__U.set_thrust;

  /* Fcn: '<S3>/Fcn6' */
  Second_att_control_codeblock__B.Fcn6 =
    (Second_att_control_codeblock__B.DataTypeConversion3 - 1000.0F) / 1000.0F;

  /* Saturate: '<S3>/Saturation10' */
  u0 = Second_att_control_codeblock__B.Fcn6;
  u1 = Second_att_control_codeblock__P.Saturation10_LowerSat;
  u2 = Second_att_control_codeblock__P.Saturation10_UpperSat;
  if (u0 > u2) {
    Second_att_control_codeblock__B.Saturation10 = u2;
  } else if (u0 < u1) {
    Second_att_control_codeblock__B.Saturation10 = u1;
  } else {
    Second_att_control_codeblock__B.Saturation10 = u0;
  }

  /* End of Saturate: '<S3>/Saturation10' */

  /* MATLAB Function: '<S1>/pwm_out1' */
  u0 = rt_roundf_snf(((-Second_att_control_codeblock__B.Gain_p -
                       Second_att_control_codeblock__B.Sum_f) *
                      Second_att_control_codeblock__B.Saturation10 / 3.0F +
                      Second_att_control_codeblock__B.Saturation10) * 1000.0F);
  if (u0 < 65536.0F) {
    if (u0 >= 0.0F) {
      y = (uint16_T)u0;
    } else {
      y = 0U;
    }
  } else {
    y = MAX_uint16_T;
  }

  tmp = y + 1000U;
  if (tmp > 65535U) {
    tmp = 65535U;
  }

  Second_att_control_codeblock__B.M1 = (uint16_T)tmp;
  u0 = rt_roundf_snf(((Second_att_control_codeblock__B.Gain_p +
                       Second_att_control_codeblock__B.Sum_f) *
                      Second_att_control_codeblock__B.Saturation10 / 3.0F +
                      Second_att_control_codeblock__B.Saturation10) * 1000.0F);
  if (u0 < 65536.0F) {
    if (u0 >= 0.0F) {
      y = (uint16_T)u0;
    } else {
      y = 0U;
    }
  } else {
    y = MAX_uint16_T;
  }

  tmp = y + 1000U;
  if (tmp > 65535U) {
    tmp = 65535U;
  }

  Second_att_control_codeblock__B.M2 = (uint16_T)tmp;
  u0 = rt_roundf_snf((((Second_att_control_codeblock__B.Gain_p / 2.0F +
                        Second_att_control_codeblock__B.Gain1) -
                       Second_att_control_codeblock__B.Sum_f) *
                      Second_att_control_codeblock__B.Saturation10 / 3.0F +
                      Second_att_control_codeblock__B.Saturation10) * 1000.0F);
  if (u0 < 65536.0F) {
    if (u0 >= 0.0F) {
      y = (uint16_T)u0;
    } else {
      y = 0U;
    }
  } else {
    y = MAX_uint16_T;
  }

  tmp = y + 1000U;
  if (tmp > 65535U) {
    tmp = 65535U;
  }

  Second_att_control_codeblock__B.M3 = (uint16_T)tmp;
  u0 = rt_roundf_snf((((-Second_att_control_codeblock__B.Gain1 -
                        Second_att_control_codeblock__B.Gain_p / 2.0F) +
                       Second_att_control_codeblock__B.Sum_f) *
                      Second_att_control_codeblock__B.Saturation10 / 3.0F +
                      Second_att_control_codeblock__B.Saturation10) * 1000.0F);
  if (u0 < 65536.0F) {
    if (u0 >= 0.0F) {
      y = (uint16_T)u0;
    } else {
      y = 0U;
    }
  } else {
    y = MAX_uint16_T;
  }

  tmp = y + 1000U;
  if (tmp > 65535U) {
    tmp = 65535U;
  }

  Second_att_control_codeblock__B.M4 = (uint16_T)tmp;
  u0 = rt_roundf_snf((((Second_att_control_codeblock__B.Gain1 -
                        Second_att_control_codeblock__B.Gain_p / 2.0F) +
                       Second_att_control_codeblock__B.Sum_f) *
                      Second_att_control_codeblock__B.Saturation10 / 3.0F +
                      Second_att_control_codeblock__B.Saturation10) * 1000.0F);
  if (u0 < 65536.0F) {
    if (u0 >= 0.0F) {
      y = (uint16_T)u0;
    } else {
      y = 0U;
    }
  } else {
    y = MAX_uint16_T;
  }

  tmp = y + 1000U;
  if (tmp > 65535U) {
    tmp = 65535U;
  }

  Second_att_control_codeblock__B.M5 = (uint16_T)tmp;
  u0 = rt_roundf_snf((((Second_att_control_codeblock__B.Gain_p / 2.0F +
                        -Second_att_control_codeblock__B.Gain1) -
                       Second_att_control_codeblock__B.Sum_f) *
                      Second_att_control_codeblock__B.Saturation10 / 3.0F +
                      Second_att_control_codeblock__B.Saturation10) * 1000.0F);
  if (u0 < 65536.0F) {
    if (u0 >= 0.0F) {
      y = (uint16_T)u0;
    } else {
      y = 0U;
    }
  } else {
    y = MAX_uint16_T;
  }

  tmp = y + 1000U;
  if (tmp > 65535U) {
    tmp = 65535U;
  }

  Second_att_control_codeblock__B.M6 = (uint16_T)tmp;

  /* End of MATLAB Function: '<S1>/pwm_out1' */

  /* Switch: '<S1>/Switch' incorporates:
   *  Inport: '<Root>/Arm_cmd'
   */
  if (Second_att_control_codeblock__U.Arm_cmd >
      Second_att_control_codeblock__P.Switch_Threshold) {
    /* Saturate: '<S1>/Saturation' */
    if (Second_att_control_codeblock__B.M1 >
        Second_att_control_codeblock__P.Saturation_UpperSat_d) {
      y = Second_att_control_codeblock__P.Saturation_UpperSat_d;
    } else if (Second_att_control_codeblock__B.M1 <
               Second_att_control_codeblock__P.Saturation_LowerSat_i) {
      y = Second_att_control_codeblock__P.Saturation_LowerSat_i;
    } else {
      y = Second_att_control_codeblock__B.M1;
    }

    Second_att_control_codeblock__B.Saturation_o[0] = y;
    if (Second_att_control_codeblock__B.M2 >
        Second_att_control_codeblock__P.Saturation_UpperSat_d) {
      y = Second_att_control_codeblock__P.Saturation_UpperSat_d;
    } else if (Second_att_control_codeblock__B.M2 <
               Second_att_control_codeblock__P.Saturation_LowerSat_i) {
      y = Second_att_control_codeblock__P.Saturation_LowerSat_i;
    } else {
      y = Second_att_control_codeblock__B.M2;
    }

    Second_att_control_codeblock__B.Saturation_o[1] = y;
    if (Second_att_control_codeblock__B.M3 >
        Second_att_control_codeblock__P.Saturation_UpperSat_d) {
      y = Second_att_control_codeblock__P.Saturation_UpperSat_d;
    } else if (Second_att_control_codeblock__B.M3 <
               Second_att_control_codeblock__P.Saturation_LowerSat_i) {
      y = Second_att_control_codeblock__P.Saturation_LowerSat_i;
    } else {
      y = Second_att_control_codeblock__B.M3;
    }

    Second_att_control_codeblock__B.Saturation_o[2] = y;
    if (Second_att_control_codeblock__B.M4 >
        Second_att_control_codeblock__P.Saturation_UpperSat_d) {
      y = Second_att_control_codeblock__P.Saturation_UpperSat_d;
    } else if (Second_att_control_codeblock__B.M4 <
               Second_att_control_codeblock__P.Saturation_LowerSat_i) {
      y = Second_att_control_codeblock__P.Saturation_LowerSat_i;
    } else {
      y = Second_att_control_codeblock__B.M4;
    }

    Second_att_control_codeblock__B.Saturation_o[3] = y;
    if (Second_att_control_codeblock__B.M5 >
        Second_att_control_codeblock__P.Saturation_UpperSat_d) {
      y = Second_att_control_codeblock__P.Saturation_UpperSat_d;
    } else if (Second_att_control_codeblock__B.M5 <
               Second_att_control_codeblock__P.Saturation_LowerSat_i) {
      y = Second_att_control_codeblock__P.Saturation_LowerSat_i;
    } else {
      y = Second_att_control_codeblock__B.M5;
    }

    Second_att_control_codeblock__B.Saturation_o[4] = y;
    if (Second_att_control_codeblock__B.M6 >
        Second_att_control_codeblock__P.Saturation_UpperSat_d) {
      y = Second_att_control_codeblock__P.Saturation_UpperSat_d;
    } else if (Second_att_control_codeblock__B.M6 <
               Second_att_control_codeblock__P.Saturation_LowerSat_i) {
      y = Second_att_control_codeblock__P.Saturation_LowerSat_i;
    } else {
      y = Second_att_control_codeblock__B.M6;
    }

    Second_att_control_codeblock__B.Saturation_o[5] = y;

    /* End of Saturate: '<S1>/Saturation' */

    /* Outport: '<Root>/PWM_OUT' */
    for (i = 0; i < 6; i++) {
      Second_att_control_codeblock__Y.PWM_OUT[i] =
        Second_att_control_codeblock__B.Saturation_o[i];
    }
  } else {
    /* Outport: '<Root>/PWM_OUT' incorporates:
     *  Constant: '<S1>/Constant'
     */
    for (i = 0; i < 6; i++) {
      Second_att_control_codeblock__Y.PWM_OUT[i] =
        Second_att_control_codeblock__P.Constant_Value;
    }
  }

  /* End of Switch: '<S1>/Switch' */

  /* Delay: '<S6>/Delay' */
  Second_att_control_codeblock__B.Delay =
    Second_att_control_codeblock_DW.Delay_DSTATE;

  /* Gain: '<S6>/antiWU_Gain' */
  Second_att_control_codeblock__B.antiWU_Gain =
    Second_att_control_codeblock__P.antiWU_Gain_Gain *
    Second_att_control_codeblock__B.Delay;

  /* Sum: '<S6>/Add' */
  Second_att_control_codeblock__B.Add =
    Second_att_control_codeblock__B.pitchrollerror_b -
    Second_att_control_codeblock__B.antiWU_Gain;

  /* Delay: '<S6>/Delay1' */
  Second_att_control_codeblock__B.Delay1 =
    Second_att_control_codeblock_DW.Delay1_DSTATE;

  /* Gain: '<S6>/antiWU_Gain1' */
  Second_att_control_codeblock__B.antiWU_Gain1 =
    Second_att_control_codeblock__P.antiWU_Gain1_Gain *
    Second_att_control_codeblock__B.Delay1;

  /* Sum: '<S6>/Add1' */
  Second_att_control_codeblock__B.Add1 =
    Second_att_control_codeblock__B.pitchrollerror_i -
    Second_att_control_codeblock__B.antiWU_Gain1;

  /* Gain: '<S39>/Integral Gain' */
  Second_att_control_codeblock__B.IntegralGain = kI_Yaw_rate_PID *
    Second_att_control_codeblock__B.Gain_f;

  /* Update for DiscreteIntegrator: '<S5>/Discrete-Time Integrator' */
  Second_att_control_codeblock_DW.DiscreteTimeIntegrator_DSTATE +=
    Second_att_control_codeblock__P.DiscreteTimeIntegrator_gainval *
    Second_att_control_codeblock__B.pitchrollerror;

  /* Update for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' */
  Second_att_control_codeblock_DW.DiscreteTimeIntegrator_DSTATE_k +=
    Second_att_control_codeblock__P.DiscreteTimeIntegrator_gainva_l *
    Second_att_control_codeblock__B.Add;

  /* Update for UnitDelay: '<S8>/UD'
   *
   * Block description for '<S8>/UD':
   *
   *  Store in Global RAM
   */
  Second_att_control_codeblock_DW.UD_DSTATE =
    Second_att_control_codeblock__B.TSamp;

  /* Update for DiscreteIntegrator: '<S5>/Discrete-Time Integrator1' */
  Second_att_control_codeblock_DW.DiscreteTimeIntegrator1_DSTATE +=
    Second_att_control_codeblock__P.DiscreteTimeIntegrator1_gainval *
    Second_att_control_codeblock__B.pitchrollerror_m;

  /* Update for DiscreteIntegrator: '<S6>/Discrete-Time Integrator1' */
  Second_att_control_codeblock_DW.DiscreteTimeIntegrator1_DSTAT_d +=
    Second_att_control_codeblock__P.DiscreteTimeIntegrator1_gainv_k *
    Second_att_control_codeblock__B.Add1;

  /* Update for UnitDelay: '<S9>/UD'
   *
   * Block description for '<S9>/UD':
   *
   *  Store in Global RAM
   */
  Second_att_control_codeblock_DW.UD_DSTATE_e =
    Second_att_control_codeblock__B.TSamp_h;

  /* Update for DiscreteIntegrator: '<S42>/Integrator' */
  Second_att_control_codeblock_DW.Integrator_DSTATE +=
    Second_att_control_codeblock__P.Integrator_gainval *
    Second_att_control_codeblock__B.IntegralGain;

  /* Update for Delay: '<S6>/Delay' */
  Second_att_control_codeblock_DW.Delay_DSTATE =
    Second_att_control_codeblock__B.DiscreteTimeIntegrator_h;

  /* Update for Delay: '<S6>/Delay1' */
  Second_att_control_codeblock_DW.Delay1_DSTATE =
    Second_att_control_codeblock__B.DiscreteTimeIntegrator1_p;
}

/* Model initialize function */
void Second_att_control_codeblock_fly_initialize(void)
{
  /* InitializeConditions for DiscreteIntegrator: '<S5>/Discrete-Time Integrator' */
  Second_att_control_codeblock_DW.DiscreteTimeIntegrator_DSTATE =
    Second_att_control_codeblock__P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S6>/Discrete-Time Integrator' */
  Second_att_control_codeblock_DW.DiscreteTimeIntegrator_DSTATE_k =
    Second_att_control_codeblock__P.DiscreteTimeIntegrator_IC_k;

  /* InitializeConditions for UnitDelay: '<S8>/UD'
   *
   * Block description for '<S8>/UD':
   *
   *  Store in Global RAM
   */
  Second_att_control_codeblock_DW.UD_DSTATE =
    Second_att_control_codeblock__P.DiscreteDerivative_ICPrevScaled;

  /* InitializeConditions for DiscreteIntegrator: '<S5>/Discrete-Time Integrator1' */
  Second_att_control_codeblock_DW.DiscreteTimeIntegrator1_DSTATE =
    Second_att_control_codeblock__P.DiscreteTimeIntegrator1_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S6>/Discrete-Time Integrator1' */
  Second_att_control_codeblock_DW.DiscreteTimeIntegrator1_DSTAT_d =
    Second_att_control_codeblock__P.DiscreteTimeIntegrator1_IC_j;

  /* InitializeConditions for UnitDelay: '<S9>/UD'
   *
   * Block description for '<S9>/UD':
   *
   *  Store in Global RAM
   */
  Second_att_control_codeblock_DW.UD_DSTATE_e =
    Second_att_control_codeblock__P.DiscreteDerivative1_ICPrevScale;

  /* InitializeConditions for DiscreteIntegrator: '<S42>/Integrator' */
  Second_att_control_codeblock_DW.Integrator_DSTATE =
    Second_att_control_codeblock__P.DiscretePIDController_InitialCo;

  /* InitializeConditions for Delay: '<S6>/Delay' */
  Second_att_control_codeblock_DW.Delay_DSTATE =
    Second_att_control_codeblock__P.Delay_InitialCondition;

  /* InitializeConditions for Delay: '<S6>/Delay1' */
  Second_att_control_codeblock_DW.Delay1_DSTATE =
    Second_att_control_codeblock__P.Delay1_InitialCondition;
}

/* Model terminate function */
void Second_att_control_codeblock_fly_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
