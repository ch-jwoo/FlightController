/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: px4demo_attitude_control.c
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

/* Block signals (default storage) */
B_px4demo_attitude_control_T px4demo_attitude_control_B;

/* Block states (default storage) */
DW_px4demo_attitude_control_T px4demo_attitude_control_DW;

/* External inputs (root inport signals with default storage) */
ExtU_px4demo_attitude_control_T px4demo_attitude_control_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_px4demo_attitude_control_T px4demo_attitude_control_Y;

/* Real-time model */
RT_MODEL_px4demo_attitude_control_T px4demo_attitude_control_M_;
RT_MODEL_px4demo_attitude_control_T *const px4demo_attitude_control_M =
  &px4demo_attitude_control_M_;

/* Model step function */
void px4demo_attitude_control_step(void)
{
  real32_T rtb_Sum_o;
  real32_T rtb_Saturation_i;
  real32_T rtb_Sum21;
  real32_T rtb_Sum_i;
  real32_T rtb_Saturation_cx;
  real32_T rtb_Sum19;
  real32_T rtb_Sum_oe;
  real32_T rtb_Saturation_a;
  real32_T rtb_Sum22;
  real32_T rtb_Sum_a;
  real32_T rtb_Saturation_n;
  real32_T rtb_Sum17;
  real32_T rtb_Saturation10;
  real32_T tmp;
  uint32_T tmp_0;
  uint16_T tmp_1;

  /* Fcn: '<S3>/Fcn2' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion'
   *  Inport: '<Root>/In3'
   */
  rtb_Sum17 = ((real32_T)px4demo_attitude_control_U.target_roll - 1500.0F) /
    500.0F;

  /* Fcn: '<S3>/Fcn5' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion1'
   *  Inport: '<Root>/In4'
   */
  rtb_Sum19 = ((real32_T)px4demo_attitude_control_U.target_pitch - 1500.0F) /
    500.0F;

  /* Saturate: '<S3>/Saturation9' */
  if (rtb_Sum17 > px4demo_attitude_control_P.Saturation9_UpperSat) {
    rtb_Sum17 = px4demo_attitude_control_P.Saturation9_UpperSat;
  } else {
    if (rtb_Sum17 < px4demo_attitude_control_P.Saturation9_LowerSat) {
      rtb_Sum17 = px4demo_attitude_control_P.Saturation9_LowerSat;
    }
  }

  /* End of Saturate: '<S3>/Saturation9' */

  /* Sum: '<S2>/Sum18' incorporates:
   *  Gain: '<S2>/1 // rad_max'
   *  Gain: '<S3>/Gain2'
   *  Inport: '<Root>/In1'
   */
  px4demo_attitude_control_B.Sum18 = px4demo_attitude_control_P.Gain2_Gain[0] *
    rtb_Sum17 - px4demo_attitude_control_P.urad_max_Gain *
    px4demo_attitude_control_U.phi;

  /* Sum: '<S147>/Sum' incorporates:
   *  DiscreteIntegrator: '<S138>/Integrator'
   *  Gain: '<S143>/Proportional Gain'
   */
  rtb_Sum_o = px4demo_attitude_control_P.KpRollAttitude *
    px4demo_attitude_control_B.Sum18 +
    px4demo_attitude_control_DW.Integrator_DSTATE_g;

  /* Saturate: '<S145>/Saturation' */
  if (rtb_Sum_o > px4demo_attitude_control_P.roll_attitude_UpperSaturationLimit)
  {
    rtb_Saturation_i =
      px4demo_attitude_control_P.roll_attitude_UpperSaturationLimit;
  } else if (rtb_Sum_o <
             px4demo_attitude_control_P.roll_attitude_LowerSaturationLimit) {
    rtb_Saturation_i =
      px4demo_attitude_control_P.roll_attitude_LowerSaturationLimit;
  } else {
    rtb_Saturation_i = rtb_Sum_o;
  }

  /* End of Saturate: '<S145>/Saturation' */

  /* Sum: '<S2>/Sum21' incorporates:
   *  Gain: '<S2>/1 // rads_max'
   *  Inport: '<Root>/In8'
   */
  rtb_Sum21 = rtb_Saturation_i - px4demo_attitude_control_P.urads_max_Gain *
    px4demo_attitude_control_U.p;

  /* Sum: '<S195>/Sum' incorporates:
   *  DiscreteIntegrator: '<S186>/Integrator'
   *  Gain: '<S191>/Proportional Gain'
   */
  rtb_Sum_i = px4demo_attitude_control_P.KpRollRate * rtb_Sum21 +
    px4demo_attitude_control_DW.Integrator_DSTATE_b;

  /* Saturate: '<S193>/Saturation' */
  if (rtb_Sum_i > px4demo_attitude_control_P.roll_rate_UpperSaturationLimit) {
    rtb_Saturation_cx =
      px4demo_attitude_control_P.roll_rate_UpperSaturationLimit;
  } else if (rtb_Sum_i <
             px4demo_attitude_control_P.roll_rate_LowerSaturationLimit) {
    rtb_Saturation_cx =
      px4demo_attitude_control_P.roll_rate_LowerSaturationLimit;
  } else {
    rtb_Saturation_cx = rtb_Sum_i;
  }

  /* End of Saturate: '<S193>/Saturation' */

  /* Saturate: '<S3>/Saturation8' */
  if (rtb_Sum19 > px4demo_attitude_control_P.Saturation8_UpperSat) {
    rtb_Sum19 = px4demo_attitude_control_P.Saturation8_UpperSat;
  } else {
    if (rtb_Sum19 < px4demo_attitude_control_P.Saturation8_LowerSat) {
      rtb_Sum19 = px4demo_attitude_control_P.Saturation8_LowerSat;
    }
  }

  /* End of Saturate: '<S3>/Saturation8' */

  /* Sum: '<S2>/Sum19' incorporates:
   *  Gain: '<S2>/1 // rad_max'
   *  Gain: '<S3>/Gain2'
   *  Inport: '<Root>/In2'
   */
  rtb_Sum19 = px4demo_attitude_control_P.Gain2_Gain[1] * rtb_Sum19 -
    px4demo_attitude_control_P.urad_max_Gain * px4demo_attitude_control_U.theta;

  /* Sum: '<S51>/Sum' incorporates:
   *  DiscreteIntegrator: '<S42>/Integrator'
   *  Gain: '<S47>/Proportional Gain'
   */
  rtb_Sum_oe = px4demo_attitude_control_P.KpPitchAttitude * rtb_Sum19 +
    px4demo_attitude_control_DW.Integrator_DSTATE_bd;

  /* Saturate: '<S49>/Saturation' */
  if (rtb_Sum_oe >
      px4demo_attitude_control_P.pitch_attitude_UpperSaturationLimit) {
    rtb_Saturation_a =
      px4demo_attitude_control_P.pitch_attitude_UpperSaturationLimit;
  } else if (rtb_Sum_oe <
             px4demo_attitude_control_P.pitch_attitude_LowerSaturationLimit) {
    rtb_Saturation_a =
      px4demo_attitude_control_P.pitch_attitude_LowerSaturationLimit;
  } else {
    rtb_Saturation_a = rtb_Sum_oe;
  }

  /* End of Saturate: '<S49>/Saturation' */

  /* Sum: '<S2>/Sum22' incorporates:
   *  Gain: '<S2>/1 // rads_max'
   *  Inport: '<Root>/In9'
   */
  rtb_Sum22 = rtb_Saturation_a - px4demo_attitude_control_P.urads_max_Gain *
    px4demo_attitude_control_U.q;

  /* Sum: '<S99>/Sum' incorporates:
   *  DiscreteIntegrator: '<S90>/Integrator'
   *  Gain: '<S95>/Proportional Gain'
   */
  rtb_Sum_a = px4demo_attitude_control_P.KpPitchRate * rtb_Sum22 +
    px4demo_attitude_control_DW.Integrator_DSTATE_h;

  /* Saturate: '<S97>/Saturation' */
  if (rtb_Sum_a > px4demo_attitude_control_P.pitch_rate_UpperSaturationLimit) {
    rtb_Saturation_n =
      px4demo_attitude_control_P.pitch_rate_UpperSaturationLimit;
  } else if (rtb_Sum_a <
             px4demo_attitude_control_P.pitch_rate_LowerSaturationLimit) {
    rtb_Saturation_n =
      px4demo_attitude_control_P.pitch_rate_LowerSaturationLimit;
  } else {
    rtb_Saturation_n = rtb_Sum_a;
  }

  /* End of Saturate: '<S97>/Saturation' */

  /* Fcn: '<S3>/Fcn7' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion2'
   *  Inport: '<Root>/In6'
   */
  rtb_Sum17 = ((real32_T)px4demo_attitude_control_U.target_yaw - 1500.0F) /
    500.0F;

  /* Saturate: '<S3>/Saturation7' */
  if (rtb_Sum17 > px4demo_attitude_control_P.Saturation7_UpperSat) {
    rtb_Sum17 = px4demo_attitude_control_P.Saturation7_UpperSat;
  } else {
    if (rtb_Sum17 < px4demo_attitude_control_P.Saturation7_LowerSat) {
      rtb_Sum17 = px4demo_attitude_control_P.Saturation7_LowerSat;
    }
  }

  /* End of Saturate: '<S3>/Saturation7' */

  /* Sum: '<S2>/Sum17' incorporates:
   *  Gain: '<S2>/1 // rads_max_yaw'
   *  Inport: '<Root>/In10'
   */
  rtb_Sum17 -= px4demo_attitude_control_P.urads_max_yaw_Gain *
    px4demo_attitude_control_U.r;

  /* Sum: '<S243>/Sum' incorporates:
   *  DiscreteIntegrator: '<S234>/Integrator'
   *  Gain: '<S239>/Proportional Gain'
   */
  px4demo_attitude_control_B.Sum = px4demo_attitude_control_P.KpYawRate *
    rtb_Sum17 + px4demo_attitude_control_DW.Integrator_DSTATE;

  /* Saturate: '<S241>/Saturation' */
  if (px4demo_attitude_control_B.Sum >
      px4demo_attitude_control_P.yaw_rate_UpperSaturationLimit) {
    px4demo_attitude_control_B.Saturation =
      px4demo_attitude_control_P.yaw_rate_UpperSaturationLimit;
  } else if (px4demo_attitude_control_B.Sum <
             px4demo_attitude_control_P.yaw_rate_LowerSaturationLimit) {
    px4demo_attitude_control_B.Saturation =
      px4demo_attitude_control_P.yaw_rate_LowerSaturationLimit;
  } else {
    px4demo_attitude_control_B.Saturation = px4demo_attitude_control_B.Sum;
  }

  /* End of Saturate: '<S241>/Saturation' */

  /* Fcn: '<S3>/Fcn6' incorporates:
   *  DataTypeConversion: '<S3>/Data Type Conversion3'
   *  Inport: '<Root>/In5'
   */
  rtb_Saturation10 = ((real32_T)px4demo_attitude_control_U.target_thrust -
                      1000.0F) / 1000.0F;

  /* Saturate: '<S3>/Saturation10' */
  if (rtb_Saturation10 > px4demo_attitude_control_P.Saturation10_UpperSat) {
    rtb_Saturation10 = px4demo_attitude_control_P.Saturation10_UpperSat;
  } else {
    if (rtb_Saturation10 < px4demo_attitude_control_P.Saturation10_LowerSat) {
      rtb_Saturation10 = px4demo_attitude_control_P.Saturation10_LowerSat;
    }
  }

  /* End of Saturate: '<S3>/Saturation10' */

  /* MATLAB Function: '<Root>/pwm_out1' */
  tmp = roundf(((-rtb_Saturation_cx - (real32_T)
                 px4demo_attitude_control_B.Saturation) * rtb_Saturation10 /
                3.0F + rtb_Saturation10) * 1000.0F);
  if (tmp < 65536.0F) {
    if (tmp >= 0.0F) {
      tmp_1 = (uint16_T)tmp;
    } else {
      tmp_1 = 0U;
    }
  } else {
    tmp_1 = MAX_uint16_T;
  }

  tmp_0 = tmp_1 + 1000U;
  if (tmp_0 > 65535U) {
    tmp_0 = 65535U;
  }

  /* Saturate: '<Root>/Output_Limits1' incorporates:
   *  MATLAB Function: '<Root>/pwm_out1'
   */
  if ((uint16_T)tmp_0 > px4demo_attitude_control_P.Output_Limits1_UpperSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[0] =
      px4demo_attitude_control_P.Output_Limits1_UpperSat;
  } else if ((uint16_T)tmp_0 <
             px4demo_attitude_control_P.Output_Limits1_LowerSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[0] =
      px4demo_attitude_control_P.Output_Limits1_LowerSat;
  } else {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[0] = (uint16_T)tmp_0;
  }

  /* MATLAB Function: '<Root>/pwm_out1' */
  tmp = roundf(((rtb_Saturation_cx + (real32_T)
                 px4demo_attitude_control_B.Saturation) * rtb_Saturation10 /
                3.0F + rtb_Saturation10) * 1000.0F);
  if (tmp < 65536.0F) {
    if (tmp >= 0.0F) {
      tmp_1 = (uint16_T)tmp;
    } else {
      tmp_1 = 0U;
    }
  } else {
    tmp_1 = MAX_uint16_T;
  }

  tmp_0 = tmp_1 + 1000U;
  if (tmp_0 > 65535U) {
    tmp_0 = 65535U;
  }

  /* Saturate: '<Root>/Output_Limits1' incorporates:
   *  MATLAB Function: '<Root>/pwm_out1'
   */
  if ((uint16_T)tmp_0 > px4demo_attitude_control_P.Output_Limits1_UpperSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[1] =
      px4demo_attitude_control_P.Output_Limits1_UpperSat;
  } else if ((uint16_T)tmp_0 <
             px4demo_attitude_control_P.Output_Limits1_LowerSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[1] =
      px4demo_attitude_control_P.Output_Limits1_LowerSat;
  } else {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[1] = (uint16_T)tmp_0;
  }

  /* MATLAB Function: '<Root>/pwm_out1' */
  tmp = roundf((((rtb_Saturation_cx / 2.0F + rtb_Saturation_n) - (real32_T)
                 px4demo_attitude_control_B.Saturation) * rtb_Saturation10 /
                3.0F + rtb_Saturation10) * 1000.0F);
  if (tmp < 65536.0F) {
    if (tmp >= 0.0F) {
      tmp_1 = (uint16_T)tmp;
    } else {
      tmp_1 = 0U;
    }
  } else {
    tmp_1 = MAX_uint16_T;
  }

  tmp_0 = tmp_1 + 1000U;
  if (tmp_0 > 65535U) {
    tmp_0 = 65535U;
  }

  /* Saturate: '<Root>/Output_Limits1' incorporates:
   *  MATLAB Function: '<Root>/pwm_out1'
   */
  if ((uint16_T)tmp_0 > px4demo_attitude_control_P.Output_Limits1_UpperSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[2] =
      px4demo_attitude_control_P.Output_Limits1_UpperSat;
  } else if ((uint16_T)tmp_0 <
             px4demo_attitude_control_P.Output_Limits1_LowerSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[2] =
      px4demo_attitude_control_P.Output_Limits1_LowerSat;
  } else {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[2] = (uint16_T)tmp_0;
  }

  /* MATLAB Function: '<Root>/pwm_out1' */
  tmp = roundf((((-rtb_Saturation_n - rtb_Saturation_cx / 2.0F) + (real32_T)
                 px4demo_attitude_control_B.Saturation) * rtb_Saturation10 /
                3.0F + rtb_Saturation10) * 1000.0F);
  if (tmp < 65536.0F) {
    if (tmp >= 0.0F) {
      tmp_1 = (uint16_T)tmp;
    } else {
      tmp_1 = 0U;
    }
  } else {
    tmp_1 = MAX_uint16_T;
  }

  tmp_0 = tmp_1 + 1000U;
  if (tmp_0 > 65535U) {
    tmp_0 = 65535U;
  }

  /* Saturate: '<Root>/Output_Limits1' incorporates:
   *  MATLAB Function: '<Root>/pwm_out1'
   */
  if ((uint16_T)tmp_0 > px4demo_attitude_control_P.Output_Limits1_UpperSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[3] =
      px4demo_attitude_control_P.Output_Limits1_UpperSat;
  } else if ((uint16_T)tmp_0 <
             px4demo_attitude_control_P.Output_Limits1_LowerSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[3] =
      px4demo_attitude_control_P.Output_Limits1_LowerSat;
  } else {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[3] = (uint16_T)tmp_0;
  }

  /* MATLAB Function: '<Root>/pwm_out1' */
  tmp = roundf((((rtb_Saturation_n - rtb_Saturation_cx / 2.0F) + (real32_T)
                 px4demo_attitude_control_B.Saturation) * rtb_Saturation10 /
                3.0F + rtb_Saturation10) * 1000.0F);
  if (tmp < 65536.0F) {
    if (tmp >= 0.0F) {
      tmp_1 = (uint16_T)tmp;
    } else {
      tmp_1 = 0U;
    }
  } else {
    tmp_1 = MAX_uint16_T;
  }

  tmp_0 = tmp_1 + 1000U;
  if (tmp_0 > 65535U) {
    tmp_0 = 65535U;
  }

  /* Saturate: '<Root>/Output_Limits1' incorporates:
   *  MATLAB Function: '<Root>/pwm_out1'
   */
  if ((uint16_T)tmp_0 > px4demo_attitude_control_P.Output_Limits1_UpperSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[4] =
      px4demo_attitude_control_P.Output_Limits1_UpperSat;
  } else if ((uint16_T)tmp_0 <
             px4demo_attitude_control_P.Output_Limits1_LowerSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[4] =
      px4demo_attitude_control_P.Output_Limits1_LowerSat;
  } else {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[4] = (uint16_T)tmp_0;
  }

  /* MATLAB Function: '<Root>/pwm_out1' */
  tmp = roundf((((rtb_Saturation_cx / 2.0F + -rtb_Saturation_n) - (real32_T)
                 px4demo_attitude_control_B.Saturation) * rtb_Saturation10 /
                3.0F + rtb_Saturation10) * 1000.0F);
  if (tmp < 65536.0F) {
    if (tmp >= 0.0F) {
      tmp_1 = (uint16_T)tmp;
    } else {
      tmp_1 = 0U;
    }
  } else {
    tmp_1 = MAX_uint16_T;
  }

  tmp_0 = tmp_1 + 1000U;
  if (tmp_0 > 65535U) {
    tmp_0 = 65535U;
  }

  /* Saturate: '<Root>/Output_Limits1' incorporates:
   *  MATLAB Function: '<Root>/pwm_out1'
   */
  if ((uint16_T)tmp_0 > px4demo_attitude_control_P.Output_Limits1_UpperSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[5] =
      px4demo_attitude_control_P.Output_Limits1_UpperSat;
  } else if ((uint16_T)tmp_0 <
             px4demo_attitude_control_P.Output_Limits1_LowerSat) {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[5] =
      px4demo_attitude_control_P.Output_Limits1_LowerSat;
  } else {
    /* Outport: '<Root>/PWM' */
    px4demo_attitude_control_Y.PWM[5] = (uint16_T)tmp_0;
  }

  /* Outport: '<Root>/ARM Control' incorporates:
   *  Constant: '<S5>/Constant'
   *  Inport: '<Root>/In7'
   *  RelationalOperator: '<S5>/Compare'
   */
  px4demo_attitude_control_Y.ARMControl =
    (px4demo_attitude_control_U.armingControl >=
     px4demo_attitude_control_P.CompareToConstant3_const);

  /* Update for DiscreteIntegrator: '<S138>/Integrator' incorporates:
   *  Gain: '<S131>/Kb'
   *  Gain: '<S135>/Integral Gain'
   *  Sum: '<S131>/SumI2'
   *  Sum: '<S131>/SumI4'
   */
  px4demo_attitude_control_DW.Integrator_DSTATE_g += ((rtb_Saturation_i -
    rtb_Sum_o) * px4demo_attitude_control_P.roll_attitude_Kb +
    px4demo_attitude_control_P.KiRollAttitude * px4demo_attitude_control_B.Sum18)
    * px4demo_attitude_control_P.Integrator_gainval_i;

  /* Update for DiscreteIntegrator: '<S186>/Integrator' incorporates:
   *  Gain: '<S179>/Kb'
   *  Gain: '<S183>/Integral Gain'
   *  Sum: '<S179>/SumI2'
   *  Sum: '<S179>/SumI4'
   */
  px4demo_attitude_control_DW.Integrator_DSTATE_b += ((rtb_Saturation_cx -
    rtb_Sum_i) * px4demo_attitude_control_P.roll_rate_Kb +
    px4demo_attitude_control_P.KiRollRate * rtb_Sum21) *
    px4demo_attitude_control_P.Integrator_gainval_h;

  /* Update for DiscreteIntegrator: '<S42>/Integrator' incorporates:
   *  Gain: '<S35>/Kb'
   *  Gain: '<S39>/Integral Gain'
   *  Sum: '<S35>/SumI2'
   *  Sum: '<S35>/SumI4'
   */
  px4demo_attitude_control_DW.Integrator_DSTATE_bd += ((rtb_Saturation_a -
    rtb_Sum_oe) * px4demo_attitude_control_P.pitch_attitude_Kb +
    px4demo_attitude_control_P.KiPitchAttitude * rtb_Sum19) *
    px4demo_attitude_control_P.Integrator_gainval_d;

  /* Update for DiscreteIntegrator: '<S90>/Integrator' incorporates:
   *  Gain: '<S83>/Kb'
   *  Gain: '<S87>/Integral Gain'
   *  Sum: '<S83>/SumI2'
   *  Sum: '<S83>/SumI4'
   */
  px4demo_attitude_control_DW.Integrator_DSTATE_h += ((rtb_Saturation_n -
    rtb_Sum_a) * px4demo_attitude_control_P.pitch_rate_Kb +
    px4demo_attitude_control_P.KiPitchRate * rtb_Sum22) *
    px4demo_attitude_control_P.Integrator_gainval_dp;

  /* Update for DiscreteIntegrator: '<S234>/Integrator' incorporates:
   *  Gain: '<S227>/Kb'
   *  Gain: '<S231>/Integral Gain'
   *  Sum: '<S227>/SumI2'
   *  Sum: '<S227>/SumI4'
   */
  px4demo_attitude_control_DW.Integrator_DSTATE +=
    ((px4demo_attitude_control_B.Saturation - px4demo_attitude_control_B.Sum) *
     px4demo_attitude_control_P.yaw_rate_Kb +
     px4demo_attitude_control_P.KiYawRate * rtb_Sum17) *
    px4demo_attitude_control_P.Integrator_gainval;
}

/* Model initialize function */
void px4demo_attitude_control_initialize(void)
{
  /* InitializeConditions for DiscreteIntegrator: '<S138>/Integrator' */
  px4demo_attitude_control_DW.Integrator_DSTATE_g =
    px4demo_attitude_control_P.roll_attitude_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteIntegrator: '<S186>/Integrator' */
  px4demo_attitude_control_DW.Integrator_DSTATE_b =
    px4demo_attitude_control_P.roll_rate_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteIntegrator: '<S42>/Integrator' */
  px4demo_attitude_control_DW.Integrator_DSTATE_bd =
    px4demo_attitude_control_P.pitch_attitude_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteIntegrator: '<S90>/Integrator' */
  px4demo_attitude_control_DW.Integrator_DSTATE_h =
    px4demo_attitude_control_P.pitch_rate_InitialConditionForIntegrator;

  /* InitializeConditions for DiscreteIntegrator: '<S234>/Integrator' */
  px4demo_attitude_control_DW.Integrator_DSTATE =
    px4demo_attitude_control_P.yaw_rate_InitialConditionForIntegrator;
}

/* Model terminate function */
void px4demo_attitude_control_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
