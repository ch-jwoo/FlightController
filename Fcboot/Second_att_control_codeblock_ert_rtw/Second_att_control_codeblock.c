/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Second_att_control_codeblock.c
 *
 * Code generated for Simulink model 'Second_att_control_codeblock'.
 *
 * Model version                  : 1.11
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Tue Jul 14 00:19:24 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Second_att_control_codeblock.h"
#include "Second_att_control_codeblock_private.h"

/* Exported block parameters */
real32_T Angle_rate_pitch_kI = 1.0F;   /* Variable: Angle_rate_pitch_kI
                                        * Referenced by: '<S88>/Integral Gain'
                                        */
real32_T Angle_rate_pitch_kP = 4.0F;   /* Variable: Angle_rate_pitch_kP
                                        * Referenced by: '<S96>/Proportional Gain'
                                        */
real32_T Angle_rate_roll_PI_kI = 1.0F; /* Variable: Angle_rate_roll_PI_kI
                                        * Referenced by: '<S40>/Integral Gain'
                                        */
real32_T Angle_rate_roll_PI_kP = 4.0F; /* Variable: Angle_rate_roll_PI_kP
                                        * Referenced by: '<S48>/Proportional Gain'
                                        */
real32_T kD_Pitch_rate_PID = 0.0F;     /* Variable: kD_Pitch_rate_PID
                                        * Referenced by: '<S135>/Derivative Gain'
                                        */
real32_T kD_Roll_rate_PID = 0.0F;      /* Variable: kD_Roll_rate_PID
                                        * Referenced by: '<S183>/Derivative Gain'
                                        */
real32_T kI_Pitch_rate_PID = 0.3F;     /* Variable: kI_Pitch_rate_PID
                                        * Referenced by: '<S138>/Integral Gain'
                                        */
real32_T kI_Roll_rate_PID = 0.3F;      /* Variable: kI_Roll_rate_PID
                                        * Referenced by: '<S186>/Integral Gain'
                                        */
real32_T kI_Yaw_rate_PID = 0.3F;       /* Variable: kI_Yaw_rate_PID
                                        * Referenced by: '<S235>/Integral Gain'
                                        */
real32_T kP_Pitch_rate_PID = 0.4F;     /* Variable: kP_Pitch_rate_PID
                                        * Referenced by: '<S146>/Proportional Gain'
                                        */
real32_T kP_Roll_rate_PID = 0.4F;      /* Variable: kP_Roll_rate_PID
                                        * Referenced by: '<S194>/Proportional Gain'
                                        */
real32_T kP_Yaw_rate_PID = 0.4F;       /* Variable: kP_Yaw_rate_PID
                                        * Referenced by: '<S243>/Proportional Gain'
                                        */

/* Exported data definition */

/* Const memory section */
/* Definition for custom storage class: Const */
const real32_T Hz_LPF_Pitch_rate = 20.0F;
                                /* Referenced by: '<S144>/Filter Coefficient' */
const real32_T Hz_LPF_Roll_rate = 20.0F;
                                /* Referenced by: '<S192>/Filter Coefficient' */
const real32_T Max_angle_coef = 0.5F;  /* Referenced by: '<S4>/1//rad_max' */
const real32_T Yaw_rate_max_rad = 1.04719734F;/* Referenced by: '<S9>/Gain' */

/* Block signals (default storage) */
B_Second_att_control_codebloc_T Second_att_control_codeblock_B;

/* Block states (default storage) */
DW_Second_att_control_codeblo_T Second_att_control_codeblock_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Second_att_control_codeb_T Second_att_control_codeblock_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Second_att_control_codeb_T Second_att_control_codeblock_Y;
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
void Second_att_control_codeblock_step(void)
{
  uint32_T tmp;
  uint16_T y;
  real32_T u0;
  real_T u0_0;

  /* DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
   *  Inport: '<Root>/set_roll'
   */
  Second_att_control_codeblock_B.DataTypeConversion =
    Second_att_control_codeblock_U.set_roll;

  /* Fcn: '<S4>/Fcn2' */
  Second_att_control_codeblock_B.Fcn2 =
    (Second_att_control_codeblock_B.DataTypeConversion - 1500.0F) / 500.0F;

  /* Saturate: '<S4>/Saturation9' */
  u0 = Second_att_control_codeblock_B.Fcn2;
  if (u0 > 1.0F) {
    Second_att_control_codeblock_B.Saturation9 = 1.0F;
  } else if (u0 < -1.0F) {
    Second_att_control_codeblock_B.Saturation9 = -1.0F;
  } else {
    Second_att_control_codeblock_B.Saturation9 = u0;
  }

  /* End of Saturate: '<S4>/Saturation9' */

  /* DataTypeConversion: '<S4>/Data Type Conversion1' incorporates:
   *  Inport: '<Root>/set_pitch'
   */
  Second_att_control_codeblock_B.DataTypeConversion1 =
    Second_att_control_codeblock_U.set_pitch;

  /* Fcn: '<S4>/Fcn5' */
  Second_att_control_codeblock_B.Fcn5 =
    (Second_att_control_codeblock_B.DataTypeConversion1 - 1500.0F) / 500.0F;

  /* Saturate: '<S4>/Saturation8' */
  u0 = Second_att_control_codeblock_B.Fcn5;
  if (u0 > 1.0F) {
    Second_att_control_codeblock_B.Saturation8 = 1.0F;
  } else if (u0 < -1.0F) {
    Second_att_control_codeblock_B.Saturation8 = -1.0F;
  } else {
    Second_att_control_codeblock_B.Saturation8 = u0;
  }

  /* End of Saturate: '<S4>/Saturation8' */

  /* Gain: '<S4>/Gain2' */
  Second_att_control_codeblock_B.Gain2[0] =
    Second_att_control_codeblock_B.Saturation9;
  Second_att_control_codeblock_B.Gain2[1] =
    -Second_att_control_codeblock_B.Saturation8;

  /* Gain: '<S4>/1//rad_max' */
  Second_att_control_codeblock_B.urad_max[0] = Max_angle_coef *
    Second_att_control_codeblock_B.Gain2[0];
  Second_att_control_codeblock_B.urad_max[1] = Max_angle_coef *
    Second_att_control_codeblock_B.Gain2[1];

  /* Gain: '<S7>/FF_roll_gain' */
  Second_att_control_codeblock_B.FF_roll_gain = 0.0F *
    Second_att_control_codeblock_B.urad_max[0];

  /* Sum: '<S7>/Sum' incorporates:
   *  Inport: '<Root>/Roll'
   */
  Second_att_control_codeblock_B.Sum_f =
    Second_att_control_codeblock_B.urad_max[0] -
    Second_att_control_codeblock_U.Roll;

  /* Gain: '<S48>/Proportional Gain' */
  Second_att_control_codeblock_B.ProportionalGain = Angle_rate_roll_PI_kP *
    Second_att_control_codeblock_B.Sum_f;

  /* DiscreteIntegrator: '<S43>/Integrator' */
  Second_att_control_codeblock_B.Integrator =
    Second_att_control_codeblock_DW.Integrator_DSTATE;

  /* Sum: '<S52>/Sum' */
  Second_att_control_codeblock_B.Sum_j =
    Second_att_control_codeblock_B.ProportionalGain +
    Second_att_control_codeblock_B.Integrator;

  /* Sum: '<S7>/Sum1' */
  Second_att_control_codeblock_B.Sum1 =
    Second_att_control_codeblock_B.FF_roll_gain +
    Second_att_control_codeblock_B.Sum_j;

  /* Sum: '<S8>/Sum' incorporates:
   *  Inport: '<Root>/p'
   */
  Second_att_control_codeblock_B.Sum_c = Second_att_control_codeblock_B.Sum1 -
    Second_att_control_codeblock_U.p;

  /* Gain: '<S194>/Proportional Gain' */
  Second_att_control_codeblock_B.ProportionalGain_b = kP_Roll_rate_PID *
    Second_att_control_codeblock_B.Sum_c;

  /* DiscreteIntegrator: '<S189>/Integrator' */
  Second_att_control_codeblock_B.Integrator_b =
    Second_att_control_codeblock_DW.Integrator_DSTATE_n;

  /* Gain: '<S183>/Derivative Gain' */
  Second_att_control_codeblock_B.DerivativeGain = kD_Roll_rate_PID *
    Second_att_control_codeblock_B.Sum_c;

  /* DiscreteIntegrator: '<S184>/Filter' */
  Second_att_control_codeblock_B.Filter_h =
    Second_att_control_codeblock_DW.Filter_DSTATE_n;

  /* Sum: '<S184>/SumD' */
  Second_att_control_codeblock_B.SumD_h =
    Second_att_control_codeblock_B.DerivativeGain -
    Second_att_control_codeblock_B.Filter_h;

  /* Gain: '<S192>/Filter Coefficient' */
  Second_att_control_codeblock_B.FilterCoefficient_a = Hz_LPF_Roll_rate *
    Second_att_control_codeblock_B.SumD_h;

  /* Sum: '<S198>/Sum' */
  Second_att_control_codeblock_B.Sum_n =
    (Second_att_control_codeblock_B.ProportionalGain_b +
     Second_att_control_codeblock_B.Integrator_b) +
    Second_att_control_codeblock_B.FilterCoefficient_a;

  /* Saturate: '<S196>/Saturation' */
  u0 = Second_att_control_codeblock_B.Sum_n;
  if (u0 > 1.0F) {
    Second_att_control_codeblock_B.Saturation_b = 1.0F;
  } else if (u0 < -1.0F) {
    Second_att_control_codeblock_B.Saturation_b = -1.0F;
  } else {
    Second_att_control_codeblock_B.Saturation_b = u0;
  }

  /* End of Saturate: '<S196>/Saturation' */

  /* Gain: '<S7>/FF_pitch_gain' */
  Second_att_control_codeblock_B.FF_pitch_gain = 0.0F *
    Second_att_control_codeblock_B.urad_max[1];

  /* Sum: '<S7>/Sum2' incorporates:
   *  Inport: '<Root>/Pitch'
   */
  Second_att_control_codeblock_B.Sum2 = Second_att_control_codeblock_B.urad_max
    [1] - Second_att_control_codeblock_U.Pitch;

  /* Gain: '<S96>/Proportional Gain' */
  Second_att_control_codeblock_B.ProportionalGain_l = Angle_rate_pitch_kP *
    Second_att_control_codeblock_B.Sum2;

  /* DiscreteIntegrator: '<S91>/Integrator' */
  Second_att_control_codeblock_B.Integrator_f =
    Second_att_control_codeblock_DW.Integrator_DSTATE_l;

  /* Sum: '<S100>/Sum' */
  Second_att_control_codeblock_B.Sum_l =
    Second_att_control_codeblock_B.ProportionalGain_l +
    Second_att_control_codeblock_B.Integrator_f;

  /* Sum: '<S7>/Sum3' */
  Second_att_control_codeblock_B.Sum3 =
    Second_att_control_codeblock_B.FF_pitch_gain +
    Second_att_control_codeblock_B.Sum_l;

  /* Sum: '<S8>/Sum1' incorporates:
   *  Inport: '<Root>/q'
   */
  Second_att_control_codeblock_B.Sum1_h = Second_att_control_codeblock_B.Sum3 -
    Second_att_control_codeblock_U.q;

  /* Gain: '<S146>/Proportional Gain' */
  Second_att_control_codeblock_B.ProportionalGain_b4 = kP_Pitch_rate_PID *
    Second_att_control_codeblock_B.Sum1_h;

  /* DiscreteIntegrator: '<S141>/Integrator' */
  Second_att_control_codeblock_B.Integrator_a =
    Second_att_control_codeblock_DW.Integrator_DSTATE_d;

  /* Gain: '<S135>/Derivative Gain' */
  Second_att_control_codeblock_B.DerivativeGain_o = kD_Pitch_rate_PID *
    Second_att_control_codeblock_B.Sum1_h;

  /* DiscreteIntegrator: '<S136>/Filter' */
  Second_att_control_codeblock_B.Filter =
    Second_att_control_codeblock_DW.Filter_DSTATE;

  /* Sum: '<S136>/SumD' */
  Second_att_control_codeblock_B.SumD =
    Second_att_control_codeblock_B.DerivativeGain_o -
    Second_att_control_codeblock_B.Filter;

  /* Gain: '<S144>/Filter Coefficient' */
  Second_att_control_codeblock_B.FilterCoefficient = Hz_LPF_Pitch_rate *
    Second_att_control_codeblock_B.SumD;

  /* Sum: '<S150>/Sum' */
  Second_att_control_codeblock_B.Sum = ((real_T)
    Second_att_control_codeblock_B.ProportionalGain_b4 +
    Second_att_control_codeblock_B.Integrator_a) +
    Second_att_control_codeblock_B.FilterCoefficient;

  /* Saturate: '<S148>/Saturation' */
  u0_0 = Second_att_control_codeblock_B.Sum;
  if (u0_0 > 1.0) {
    Second_att_control_codeblock_B.Saturation = 1.0;
  } else if (u0_0 < -1.0) {
    Second_att_control_codeblock_B.Saturation = -1.0;
  } else {
    Second_att_control_codeblock_B.Saturation = u0_0;
  }

  /* End of Saturate: '<S148>/Saturation' */

  /* DataTypeConversion: '<S4>/Data Type Conversion2' incorporates:
   *  Inport: '<Root>/set_yaw'
   */
  Second_att_control_codeblock_B.DataTypeConversion2 =
    Second_att_control_codeblock_U.set_yaw;

  /* Fcn: '<S4>/Fcn7' */
  Second_att_control_codeblock_B.Fcn7 =
    (Second_att_control_codeblock_B.DataTypeConversion2 - 1500.0F) / 500.0F;

  /* Saturate: '<S4>/Saturation7' */
  u0 = Second_att_control_codeblock_B.Fcn7;
  if (u0 > 1.0F) {
    Second_att_control_codeblock_B.Saturation7 = 1.0F;
  } else if (u0 < -1.0F) {
    Second_att_control_codeblock_B.Saturation7 = -1.0F;
  } else {
    Second_att_control_codeblock_B.Saturation7 = u0;
  }

  /* End of Saturate: '<S4>/Saturation7' */

  /* Sum: '<S9>/Sum' incorporates:
   *  Inport: '<Root>/r'
   */
  Second_att_control_codeblock_B.Sum_m =
    Second_att_control_codeblock_B.Saturation7 -
    Second_att_control_codeblock_U.r;

  /* Gain: '<S9>/Gain' */
  Second_att_control_codeblock_B.Gain = Yaw_rate_max_rad *
    Second_att_control_codeblock_B.Sum_m;

  /* Gain: '<S243>/Proportional Gain' */
  Second_att_control_codeblock_B.ProportionalGain_j = kP_Yaw_rate_PID *
    Second_att_control_codeblock_B.Gain;

  /* DiscreteIntegrator: '<S238>/Integrator' */
  Second_att_control_codeblock_B.Integrator_d =
    Second_att_control_codeblock_DW.Integrator_DSTATE_j;

  /* Sum: '<S247>/Sum' */
  Second_att_control_codeblock_B.Sum_f3 =
    Second_att_control_codeblock_B.ProportionalGain_j +
    Second_att_control_codeblock_B.Integrator_d;

  /* Saturate: '<S245>/Saturation' */
  u0 = Second_att_control_codeblock_B.Sum_f3;
  if (u0 > 1.0F) {
    Second_att_control_codeblock_B.Saturation_o = 1.0F;
  } else if (u0 < -1.0F) {
    Second_att_control_codeblock_B.Saturation_o = -1.0F;
  } else {
    Second_att_control_codeblock_B.Saturation_o = u0;
  }

  /* End of Saturate: '<S245>/Saturation' */

  /* DataTypeConversion: '<S4>/Data Type Conversion3' incorporates:
   *  Inport: '<Root>/set_thrust'
   */
  Second_att_control_codeblock_B.DataTypeConversion3 =
    Second_att_control_codeblock_U.set_thrust;

  /* Fcn: '<S4>/Fcn6' */
  Second_att_control_codeblock_B.Fcn6 =
    (Second_att_control_codeblock_B.DataTypeConversion3 - 1000.0F) / 1000.0F;

  /* Saturate: '<S4>/Saturation10' */
  u0 = Second_att_control_codeblock_B.Fcn6;
  if (u0 > 1.0F) {
    Second_att_control_codeblock_B.Saturation10 = 1.0F;
  } else if (u0 < 0.0F) {
    Second_att_control_codeblock_B.Saturation10 = 0.0F;
  } else {
    Second_att_control_codeblock_B.Saturation10 = u0;
  }

  /* End of Saturate: '<S4>/Saturation10' */

  /* MATLAB Function: '<S1>/pwm_out1' */
  u0 = rt_roundf_snf(((-Second_att_control_codeblock_B.Saturation_b -
                       Second_att_control_codeblock_B.Saturation_o) *
                      Second_att_control_codeblock_B.Saturation10 / 3.0F +
                      Second_att_control_codeblock_B.Saturation10) * 1000.0F);
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

  Second_att_control_codeblock_B.M1 = (uint16_T)tmp;
  u0 = rt_roundf_snf(((Second_att_control_codeblock_B.Saturation_b +
                       Second_att_control_codeblock_B.Saturation_o) *
                      Second_att_control_codeblock_B.Saturation10 / 3.0F +
                      Second_att_control_codeblock_B.Saturation10) * 1000.0F);
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

  Second_att_control_codeblock_B.M2 = (uint16_T)tmp;
  u0 = rt_roundf_snf((((Second_att_control_codeblock_B.Saturation_b / 2.0F +
                        (real32_T)Second_att_control_codeblock_B.Saturation) -
                       Second_att_control_codeblock_B.Saturation_o) *
                      Second_att_control_codeblock_B.Saturation10 / 3.0F +
                      Second_att_control_codeblock_B.Saturation10) * 1000.0F);
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

  Second_att_control_codeblock_B.M3 = (uint16_T)tmp;
  u0 = rt_roundf_snf(((((real32_T)-Second_att_control_codeblock_B.Saturation -
                        Second_att_control_codeblock_B.Saturation_b / 2.0F) +
                       Second_att_control_codeblock_B.Saturation_o) *
                      Second_att_control_codeblock_B.Saturation10 / 3.0F +
                      Second_att_control_codeblock_B.Saturation10) * 1000.0F);
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

  Second_att_control_codeblock_B.M4 = (uint16_T)tmp;
  u0 = rt_roundf_snf(((((real32_T)Second_att_control_codeblock_B.Saturation -
                        Second_att_control_codeblock_B.Saturation_b / 2.0F) +
                       Second_att_control_codeblock_B.Saturation_o) *
                      Second_att_control_codeblock_B.Saturation10 / 3.0F +
                      Second_att_control_codeblock_B.Saturation10) * 1000.0F);
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

  Second_att_control_codeblock_B.M5 = (uint16_T)tmp;
  u0 = rt_roundf_snf((((Second_att_control_codeblock_B.Saturation_b / 2.0F +
                        (real32_T)-Second_att_control_codeblock_B.Saturation) -
                       Second_att_control_codeblock_B.Saturation_o) *
                      Second_att_control_codeblock_B.Saturation10 / 3.0F +
                      Second_att_control_codeblock_B.Saturation10) * 1000.0F);
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

  Second_att_control_codeblock_B.M6 = (uint16_T)tmp;

  /* End of MATLAB Function: '<S1>/pwm_out1' */

  /* Saturate: '<S1>/Saturation' */
  if (Second_att_control_codeblock_B.M1 > 2000) {
    y = 2000U;
  } else if (Second_att_control_codeblock_B.M1 < 1000) {
    y = 1000U;
  } else {
    y = Second_att_control_codeblock_B.M1;
  }

  /* Outport: '<Root>/PWM_OUT' incorporates:
   *  Saturate: '<S1>/Saturation'
   */
  Second_att_control_codeblock_Y.PWM_OUT[0] = y;

  /* Saturate: '<S1>/Saturation' */
  if (Second_att_control_codeblock_B.M2 > 2000) {
    y = 2000U;
  } else if (Second_att_control_codeblock_B.M2 < 1000) {
    y = 1000U;
  } else {
    y = Second_att_control_codeblock_B.M2;
  }

  /* Outport: '<Root>/PWM_OUT' incorporates:
   *  Saturate: '<S1>/Saturation'
   */
  Second_att_control_codeblock_Y.PWM_OUT[1] = y;

  /* Saturate: '<S1>/Saturation' */
  if (Second_att_control_codeblock_B.M3 > 2000) {
    y = 2000U;
  } else if (Second_att_control_codeblock_B.M3 < 1000) {
    y = 1000U;
  } else {
    y = Second_att_control_codeblock_B.M3;
  }

  /* Outport: '<Root>/PWM_OUT' incorporates:
   *  Saturate: '<S1>/Saturation'
   */
  Second_att_control_codeblock_Y.PWM_OUT[2] = y;

  /* Saturate: '<S1>/Saturation' */
  if (Second_att_control_codeblock_B.M4 > 2000) {
    y = 2000U;
  } else if (Second_att_control_codeblock_B.M4 < 1000) {
    y = 1000U;
  } else {
    y = Second_att_control_codeblock_B.M4;
  }

  /* Outport: '<Root>/PWM_OUT' incorporates:
   *  Saturate: '<S1>/Saturation'
   */
  Second_att_control_codeblock_Y.PWM_OUT[3] = y;

  /* Saturate: '<S1>/Saturation' */
  if (Second_att_control_codeblock_B.M5 > 2000) {
    y = 2000U;
  } else if (Second_att_control_codeblock_B.M5 < 1000) {
    y = 1000U;
  } else {
    y = Second_att_control_codeblock_B.M5;
  }

  /* Outport: '<Root>/PWM_OUT' incorporates:
   *  Saturate: '<S1>/Saturation'
   */
  Second_att_control_codeblock_Y.PWM_OUT[4] = y;

  /* Saturate: '<S1>/Saturation' */
  if (Second_att_control_codeblock_B.M6 > 2000) {
    y = 2000U;
  } else if (Second_att_control_codeblock_B.M6 < 1000) {
    y = 1000U;
  } else {
    y = Second_att_control_codeblock_B.M6;
  }

  /* Outport: '<Root>/PWM_OUT' incorporates:
   *  Saturate: '<S1>/Saturation'
   */
  Second_att_control_codeblock_Y.PWM_OUT[5] = y;

  /* Outport: '<Root>/ARM Control' incorporates:
   *  Constant: '<S6>/Constant'
   *  Inport: '<Root>/Arm_cmd'
   *  RelationalOperator: '<S6>/Compare'
   */
  Second_att_control_codeblock_Y.ARMControl =
    (Second_att_control_codeblock_U.Arm_cmd >= 1500);

  /* Gain: '<S40>/Integral Gain' */
  Second_att_control_codeblock_B.IntegralGain = Angle_rate_roll_PI_kI *
    Second_att_control_codeblock_B.Sum_f;

  /* Gain: '<S88>/Integral Gain' */
  Second_att_control_codeblock_B.IntegralGain_f = Angle_rate_pitch_kI *
    Second_att_control_codeblock_B.Sum2;

  /* Gain: '<S186>/Integral Gain' */
  Second_att_control_codeblock_B.IntegralGain_d = kI_Roll_rate_PID *
    Second_att_control_codeblock_B.Sum_c;

  /* Gain: '<S138>/Integral Gain' */
  Second_att_control_codeblock_B.IntegralGain_e = kI_Pitch_rate_PID *
    Second_att_control_codeblock_B.Sum1_h;

  /* Gain: '<S235>/Integral Gain' */
  Second_att_control_codeblock_B.IntegralGain_h = kI_Yaw_rate_PID *
    Second_att_control_codeblock_B.Gain;

  /* Update for DiscreteIntegrator: '<S43>/Integrator' */
  Second_att_control_codeblock_DW.Integrator_DSTATE += 0.01F *
    Second_att_control_codeblock_B.IntegralGain;

  /* Update for DiscreteIntegrator: '<S189>/Integrator' */
  Second_att_control_codeblock_DW.Integrator_DSTATE_n += 0.01F *
    Second_att_control_codeblock_B.IntegralGain_d;

  /* Update for DiscreteIntegrator: '<S184>/Filter' */
  Second_att_control_codeblock_DW.Filter_DSTATE_n += 0.01F *
    Second_att_control_codeblock_B.FilterCoefficient_a;

  /* Update for DiscreteIntegrator: '<S91>/Integrator' */
  Second_att_control_codeblock_DW.Integrator_DSTATE_l += 0.01F *
    Second_att_control_codeblock_B.IntegralGain_f;

  /* Update for DiscreteIntegrator: '<S141>/Integrator' */
  Second_att_control_codeblock_DW.Integrator_DSTATE_d += 0.01F *
    Second_att_control_codeblock_B.IntegralGain_e;

  /* Update for DiscreteIntegrator: '<S136>/Filter' */
  Second_att_control_codeblock_DW.Filter_DSTATE += 0.01 *
    Second_att_control_codeblock_B.FilterCoefficient;

  /* Update for DiscreteIntegrator: '<S238>/Integrator' */
  Second_att_control_codeblock_DW.Integrator_DSTATE_j += 0.01F *
    Second_att_control_codeblock_B.IntegralGain_h;
}

/* Model initialize function */
void Second_att_control_codeblock_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void Second_att_control_codeblock_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
