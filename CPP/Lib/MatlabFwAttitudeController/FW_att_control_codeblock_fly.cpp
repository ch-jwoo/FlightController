//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: FW_att_control_codeblock_fly.cpp
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

real32_T fw_rt_roundf_snf(real32_T u)
{
  real32_T y;
  if (std::abs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = std::floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = std::ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

// Model step function
void FW_px4_AlgorithmModelClass::step()
{
  uint16_T y;
  real32_T u0;
  real32_T u1;
  real32_T u2;

  // Gain: '<Root>/roll_dircection' incorporates:
  //   Inport: '<Root>/set_roll'

  FW_att_control_codeblock_fly_B.roll_dircection =
    FW_att_control_codeblock_fly_P.roll_dircection_Gain *
    FW_att_control_codeblock_fly_U.set_roll;

  // Gain: '<Root>/pitch_direction' incorporates:
  //   Inport: '<Root>/set_pitch'

  FW_att_control_codeblock_fly_B.pitch_direction =
    FW_att_control_codeblock_fly_P.pitch_direction_Gain *
    FW_att_control_codeblock_fly_U.set_pitch;

  // Gain: '<S1>/FW_Max_angle_coef'
  FW_att_control_codeblock_fly_B.FW_Max_angle_coef[0] =
    FW_att_control_codeblock_fly_P.FW_Max_angle_coef *
    FW_att_control_codeblock_fly_B.roll_dircection;
  FW_att_control_codeblock_fly_B.FW_Max_angle_coef[1] =
    FW_att_control_codeblock_fly_P.FW_Max_angle_coef *
    FW_att_control_codeblock_fly_B.pitch_direction;

  // Sum: '<S4>/Sum' incorporates:
  //   Inport: '<Root>/Roll'

  FW_att_control_codeblock_fly_B.pitchrollerror =
    FW_att_control_codeblock_fly_B.FW_Max_angle_coef[0] -
    FW_att_control_codeblock_fly_U.Roll;

  // Gain: '<S4>/P_pr'
  FW_att_control_codeblock_fly_B.P_pr =
    FW_att_control_codeblock_fly_P.FW_Angle_rate_roll_PI_kP *
    FW_att_control_codeblock_fly_B.pitchrollerror;

  // DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
  FW_att_control_codeblock_fly_B.DiscreteTimeIntegrator =
    FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator_DSTATE;

  // Gain: '<S4>/I_pr'
  FW_att_control_codeblock_fly_B.I_pr =
    FW_att_control_codeblock_fly_P.FW_Angle_rate_roll_PI_kI *
    FW_att_control_codeblock_fly_B.DiscreteTimeIntegrator;

  // Sum: '<S4>/Sum16'
  FW_att_control_codeblock_fly_B.P_pr_m = FW_att_control_codeblock_fly_B.P_pr +
    FW_att_control_codeblock_fly_B.I_pr;

  // Sum: '<S5>/Sum' incorporates:
  //   Inport: '<Root>/p'

  FW_att_control_codeblock_fly_B.pitchrollerror_b =
    FW_att_control_codeblock_fly_B.P_pr_m - FW_att_control_codeblock_fly_U.p;

  // Gain: '<S5>/P_pr'
  FW_att_control_codeblock_fly_B.P_pr_b =
    FW_att_control_codeblock_fly_P.FW_kP_Roll_rate_PID *
    FW_att_control_codeblock_fly_B.pitchrollerror_b;

  // DiscreteIntegrator: '<S5>/Discrete-Time Integrator'
  FW_att_control_codeblock_fly_B.DiscreteTimeIntegrator_h =
    FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator_DSTATE_k;

  // Gain: '<S5>/I_pr'
  FW_att_control_codeblock_fly_B.I_pr_d =
    FW_att_control_codeblock_fly_P.FW_kI_Roll_rate_PID *
    FW_att_control_codeblock_fly_B.DiscreteTimeIntegrator_h;

  // SampleTimeMath: '<S7>/TSamp'
  //
  //  About '<S7>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )

  FW_att_control_codeblock_fly_B.TSamp =
    FW_att_control_codeblock_fly_B.pitchrollerror_b *
    FW_att_control_codeblock_fly_P.TSamp_WtEt;

  // UnitDelay: '<S7>/UD'
  //
  //  Block description for '<S7>/UD':
  //
  //   Store in Global RAM

  FW_att_control_codeblock_fly_B.Uk1 = FW_att_control_codeblock_fly_DW.UD_DSTATE;

  // Sum: '<S7>/Diff'
  //
  //  Block description for '<S7>/Diff':
  //
  //   Add in CPU

  FW_att_control_codeblock_fly_B.Diff = FW_att_control_codeblock_fly_B.TSamp -
    FW_att_control_codeblock_fly_B.Uk1;

  // Gain: '<S5>/D_pr'
  FW_att_control_codeblock_fly_B.D_pr =
    FW_att_control_codeblock_fly_P.FW_kD_Roll_rate_PID *
    FW_att_control_codeblock_fly_B.Diff;

  // Sum: '<S5>/Sum16'
  FW_att_control_codeblock_fly_B.P_pr_d = (FW_att_control_codeblock_fly_B.P_pr_b
    + FW_att_control_codeblock_fly_B.I_pr_d) +
    FW_att_control_codeblock_fly_B.D_pr;

  // Saturate: '<S5>/Roll_rate'
  u0 = FW_att_control_codeblock_fly_B.P_pr_d;
  u1 = FW_att_control_codeblock_fly_P.Roll_rate_LowerSat;
  u2 = FW_att_control_codeblock_fly_P.Roll_rate_UpperSat;
  if (u0 > u2) {
    FW_att_control_codeblock_fly_B.Roll_rate = u2;
  } else if (u0 < u1) {
    FW_att_control_codeblock_fly_B.Roll_rate = u1;
  } else {
    FW_att_control_codeblock_fly_B.Roll_rate = u0;
  }

  // End of Saturate: '<S5>/Roll_rate'

  // Sum: '<S4>/Sum2' incorporates:
  //   Inport: '<Root>/Pitch'

  FW_att_control_codeblock_fly_B.pitchrollerror_m =
    FW_att_control_codeblock_fly_B.FW_Max_angle_coef[1] -
    FW_att_control_codeblock_fly_U.Pitch;

  // Gain: '<S4>/P_pr1'
  FW_att_control_codeblock_fly_B.P_pr1 =
    FW_att_control_codeblock_fly_P.FW_Angle_rate_pitch_kP *
    FW_att_control_codeblock_fly_B.pitchrollerror_m;

  // DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
  FW_att_control_codeblock_fly_B.DiscreteTimeIntegrator1 =
    FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator1_DSTATE;

  // Gain: '<S4>/I_pr1'
  FW_att_control_codeblock_fly_B.I_pr1 =
    FW_att_control_codeblock_fly_P.FW_Angle_rate_pitch_kI *
    FW_att_control_codeblock_fly_B.DiscreteTimeIntegrator1;

  // Sum: '<S4>/Sum1'
  FW_att_control_codeblock_fly_B.P_pr_o = FW_att_control_codeblock_fly_B.P_pr1 +
    FW_att_control_codeblock_fly_B.I_pr1;

  // Sum: '<S5>/Sum1' incorporates:
  //   Inport: '<Root>/q'

  FW_att_control_codeblock_fly_B.pitchrollerror_i =
    FW_att_control_codeblock_fly_B.P_pr_o - FW_att_control_codeblock_fly_U.q;

  // Gain: '<S5>/P_pr1'
  FW_att_control_codeblock_fly_B.P_pr1_p =
    FW_att_control_codeblock_fly_P.FW_kP_Pitch_rate_PID *
    FW_att_control_codeblock_fly_B.pitchrollerror_i;

  // DiscreteIntegrator: '<S5>/Discrete-Time Integrator1'
  FW_att_control_codeblock_fly_B.DiscreteTimeIntegrator1_p =
    FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator1_DSTAT_d;

  // Gain: '<S5>/I_pr1'
  FW_att_control_codeblock_fly_B.I_pr1_j =
    FW_att_control_codeblock_fly_P.FW_kI_Pitch_rate_PID *
    FW_att_control_codeblock_fly_B.DiscreteTimeIntegrator1_p;

  // SampleTimeMath: '<S8>/TSamp'
  //
  //  About '<S8>/TSamp':
  //   y = u * K where K = 1 / ( w * Ts )

  FW_att_control_codeblock_fly_B.TSamp_h =
    FW_att_control_codeblock_fly_B.pitchrollerror_i *
    FW_att_control_codeblock_fly_P.TSamp_WtEt_l;

  // UnitDelay: '<S8>/UD'
  //
  //  Block description for '<S8>/UD':
  //
  //   Store in Global RAM

  FW_att_control_codeblock_fly_B.Uk1_i =
    FW_att_control_codeblock_fly_DW.UD_DSTATE_e;

  // Sum: '<S8>/Diff'
  //
  //  Block description for '<S8>/Diff':
  //
  //   Add in CPU

  FW_att_control_codeblock_fly_B.Diff_l = FW_att_control_codeblock_fly_B.TSamp_h
    - FW_att_control_codeblock_fly_B.Uk1_i;

  // Gain: '<S5>/D_pr1'
  FW_att_control_codeblock_fly_B.D_pr1 =
    FW_att_control_codeblock_fly_P.FW_kD_Pitch_rate_PID *
    FW_att_control_codeblock_fly_B.Diff_l;

  // Sum: '<S5>/Sum2'
  FW_att_control_codeblock_fly_B.P_pr_j =
    (FW_att_control_codeblock_fly_B.P_pr1_p +
     FW_att_control_codeblock_fly_B.I_pr1_j) +
    FW_att_control_codeblock_fly_B.D_pr1;

  // Saturate: '<S5>/Pitch_rate'
  u0 = FW_att_control_codeblock_fly_B.P_pr_j;
  u1 = FW_att_control_codeblock_fly_P.Pitch_rate_LowerSat;
  u2 = FW_att_control_codeblock_fly_P.Pitch_rate_UpperSat;
  if (u0 > u2) {
    FW_att_control_codeblock_fly_B.Pitch_rate = u2;
  } else if (u0 < u1) {
    FW_att_control_codeblock_fly_B.Pitch_rate = u1;
  } else {
    FW_att_control_codeblock_fly_B.Pitch_rate = u0;
  }

  // End of Saturate: '<S5>/Pitch_rate'

  // Sum: '<S6>/Sum' incorporates:
  //   Inport: '<Root>/r'
  //   Inport: '<Root>/set_yaw'

  FW_att_control_codeblock_fly_B.Sum = FW_att_control_codeblock_fly_U.set_yaw -
    FW_att_control_codeblock_fly_U.r;

  // Gain: '<S6>/Gain'
  FW_att_control_codeblock_fly_B.Gain =
    FW_att_control_codeblock_fly_P.FW_Yaw_angel_rate_P *
    FW_att_control_codeblock_fly_B.Sum;

  // Gain: '<S46>/Proportional Gain'
  FW_att_control_codeblock_fly_B.ProportionalGain =
    FW_att_control_codeblock_fly_P.FW_kP_Yaw_rate_PID *
    FW_att_control_codeblock_fly_B.Gain;

  // DiscreteIntegrator: '<S41>/Integrator'
  FW_att_control_codeblock_fly_B.Integrator =
    FW_att_control_codeblock_fly_DW.Integrator_DSTATE;

  // Sum: '<S50>/Sum'
  FW_att_control_codeblock_fly_B.Sum_f =
    FW_att_control_codeblock_fly_B.ProportionalGain +
    FW_att_control_codeblock_fly_B.Integrator;

  // MATLAB Function: '<S1>/pwm_out1' incorporates:
  //   Inport: '<Root>/set_thrust'

  u0 = fw_rt_roundf_snf((-FW_att_control_codeblock_fly_B.Sum_f *
                      FW_att_control_codeblock_fly_U.set_thrust / 2.0F +
                      FW_att_control_codeblock_fly_U.set_thrust) * 1000.0F +
                     1000.0F);
  if (u0 < 65536.0F) {
    if (u0 >= 0.0F) {
      y = static_cast<uint16_T>(u0);
    } else {
      y = 0U;
    }
  } else {
    y = MAX_uint16_T;
  }

  FW_att_control_codeblock_fly_B.M1 = y;
  FW_att_control_codeblock_fly_B.M2 = 1000U;
  u0 = fw_rt_roundf_snf((FW_att_control_codeblock_fly_B.Sum_f *
                      FW_att_control_codeblock_fly_U.set_thrust / 2.0F +
                      FW_att_control_codeblock_fly_U.set_thrust) * 1000.0F +
                     1000.0F);
  if (u0 < 65536.0F) {
    if (u0 >= 0.0F) {
      y = static_cast<uint16_T>(u0);
    } else {
      y = 0U;
    }
  } else {
    y = MAX_uint16_T;
  }

  FW_att_control_codeblock_fly_B.M3 = y;
  FW_att_control_codeblock_fly_B.M4 = 1000U;
  u0 = fw_rt_roundf_snf((0.6F * FW_att_control_codeblock_fly_B.Roll_rate + 0.6F *
                      FW_att_control_codeblock_fly_B.Pitch_rate) / 2.0F * 500.0F
                     + 1500.0F);
  if (u0 < 65536.0F) {
    if (u0 >= 0.0F) {
      y = static_cast<uint16_T>(u0);
    } else {
      y = 0U;
    }
  } else {
    y = MAX_uint16_T;
  }

  FW_att_control_codeblock_fly_B.S1 = y;
  u0 = fw_rt_roundf_snf((0.6F * FW_att_control_codeblock_fly_B.Roll_rate - 0.6F *
                      FW_att_control_codeblock_fly_B.Pitch_rate) / 2.0F * 500.0F
                     + 1500.0F);
  if (u0 < 65536.0F) {
    if (u0 >= 0.0F) {
      y = static_cast<uint16_T>(u0);
    } else {
      y = 0U;
    }
  } else {
    y = MAX_uint16_T;
  }

  FW_att_control_codeblock_fly_B.S2 = y;
  FW_att_control_codeblock_fly_B.S3 = 1000U;
  FW_att_control_codeblock_fly_B.S4 = 1000U;

  // End of MATLAB Function: '<S1>/pwm_out1'

  // Saturate: '<S1>/Saturation'
  if (FW_att_control_codeblock_fly_B.M1 >
      FW_att_control_codeblock_fly_P.Saturation_UpperSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_UpperSat;
  } else if (FW_att_control_codeblock_fly_B.M1 <
             FW_att_control_codeblock_fly_P.Saturation_LowerSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_LowerSat;
  } else {
    y = FW_att_control_codeblock_fly_B.M1;
  }

  // Outport: '<Root>/PWM_OUT' incorporates:
  //   Saturate: '<S1>/Saturation'

  FW_att_control_codeblock_fly_Y.PWM_OUT[0] = y;

  // Saturate: '<S1>/Saturation'
  if (FW_att_control_codeblock_fly_B.M2 >
      FW_att_control_codeblock_fly_P.Saturation_UpperSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_UpperSat;
  } else if (FW_att_control_codeblock_fly_B.M2 <
             FW_att_control_codeblock_fly_P.Saturation_LowerSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_LowerSat;
  } else {
    y = FW_att_control_codeblock_fly_B.M2;
  }

  // Outport: '<Root>/PWM_OUT' incorporates:
  //   Saturate: '<S1>/Saturation'

  FW_att_control_codeblock_fly_Y.PWM_OUT[1] = y;

  // Saturate: '<S1>/Saturation'
  if (FW_att_control_codeblock_fly_B.M3 >
      FW_att_control_codeblock_fly_P.Saturation_UpperSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_UpperSat;
  } else if (FW_att_control_codeblock_fly_B.M3 <
             FW_att_control_codeblock_fly_P.Saturation_LowerSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_LowerSat;
  } else {
    y = FW_att_control_codeblock_fly_B.M3;
  }

  // Outport: '<Root>/PWM_OUT' incorporates:
  //   Saturate: '<S1>/Saturation'

  FW_att_control_codeblock_fly_Y.PWM_OUT[2] = y;

  // Saturate: '<S1>/Saturation'
  if (FW_att_control_codeblock_fly_B.M4 >
      FW_att_control_codeblock_fly_P.Saturation_UpperSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_UpperSat;
  } else if (FW_att_control_codeblock_fly_B.M4 <
             FW_att_control_codeblock_fly_P.Saturation_LowerSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_LowerSat;
  } else {
    y = FW_att_control_codeblock_fly_B.M4;
  }

  // Outport: '<Root>/PWM_OUT' incorporates:
  //   Saturate: '<S1>/Saturation'

  FW_att_control_codeblock_fly_Y.PWM_OUT[3] = y;

  // Saturate: '<S1>/Saturation'
  if (FW_att_control_codeblock_fly_B.S1 >
      FW_att_control_codeblock_fly_P.Saturation_UpperSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_UpperSat;
  } else if (FW_att_control_codeblock_fly_B.S1 <
             FW_att_control_codeblock_fly_P.Saturation_LowerSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_LowerSat;
  } else {
    y = FW_att_control_codeblock_fly_B.S1;
  }

  // Outport: '<Root>/PWM_OUT' incorporates:
  //   Saturate: '<S1>/Saturation'

  FW_att_control_codeblock_fly_Y.PWM_OUT[4] = y;

  // Saturate: '<S1>/Saturation'
  if (FW_att_control_codeblock_fly_B.S2 >
      FW_att_control_codeblock_fly_P.Saturation_UpperSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_UpperSat;
  } else if (FW_att_control_codeblock_fly_B.S2 <
             FW_att_control_codeblock_fly_P.Saturation_LowerSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_LowerSat;
  } else {
    y = FW_att_control_codeblock_fly_B.S2;
  }

  // Outport: '<Root>/PWM_OUT' incorporates:
  //   Saturate: '<S1>/Saturation'

  FW_att_control_codeblock_fly_Y.PWM_OUT[5] = y;

  // Saturate: '<S1>/Saturation'
  if (FW_att_control_codeblock_fly_B.S3 >
      FW_att_control_codeblock_fly_P.Saturation_UpperSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_UpperSat;
  } else if (FW_att_control_codeblock_fly_B.S3 <
             FW_att_control_codeblock_fly_P.Saturation_LowerSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_LowerSat;
  } else {
    y = FW_att_control_codeblock_fly_B.S3;
  }

  // Outport: '<Root>/PWM_OUT' incorporates:
  //   Saturate: '<S1>/Saturation'

  FW_att_control_codeblock_fly_Y.PWM_OUT[6] = y;

  // Saturate: '<S1>/Saturation'
  if (FW_att_control_codeblock_fly_B.S4 >
      FW_att_control_codeblock_fly_P.Saturation_UpperSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_UpperSat;
  } else if (FW_att_control_codeblock_fly_B.S4 <
             FW_att_control_codeblock_fly_P.Saturation_LowerSat) {
    y = FW_att_control_codeblock_fly_P.Saturation_LowerSat;
  } else {
    y = FW_att_control_codeblock_fly_B.S4;
  }

  // Outport: '<Root>/PWM_OUT' incorporates:
  //   Saturate: '<S1>/Saturation'

  FW_att_control_codeblock_fly_Y.PWM_OUT[7] = y;

  // Delay: '<S5>/Delay'
  FW_att_control_codeblock_fly_B.Delay =
    FW_att_control_codeblock_fly_DW.Delay_DSTATE;

  // Gain: '<S5>/antiWU_Gain'
  FW_att_control_codeblock_fly_B.antiWU_Gain =
    FW_att_control_codeblock_fly_P.antiWU_Gain_Gain *
    FW_att_control_codeblock_fly_B.Delay;

  // Sum: '<S5>/Add'
  FW_att_control_codeblock_fly_B.Add =
    FW_att_control_codeblock_fly_B.pitchrollerror_b -
    FW_att_control_codeblock_fly_B.antiWU_Gain;

  // Delay: '<S5>/Delay1'
  FW_att_control_codeblock_fly_B.Delay1 =
    FW_att_control_codeblock_fly_DW.Delay1_DSTATE;

  // Gain: '<S5>/antiWU_Gain1'
  FW_att_control_codeblock_fly_B.antiWU_Gain1 =
    FW_att_control_codeblock_fly_P.antiWU_Gain1_Gain *
    FW_att_control_codeblock_fly_B.Delay1;

  // Sum: '<S5>/Add1'
  FW_att_control_codeblock_fly_B.Add1 =
    FW_att_control_codeblock_fly_B.pitchrollerror_i -
    FW_att_control_codeblock_fly_B.antiWU_Gain1;

  // Gain: '<S38>/Integral Gain'
  FW_att_control_codeblock_fly_B.IntegralGain =
    FW_att_control_codeblock_fly_P.FW_kI_Yaw_rate_PID *
    FW_att_control_codeblock_fly_B.Gain;

  // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
  FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator_DSTATE +=
    FW_att_control_codeblock_fly_P.DiscreteTimeIntegrator_gainval *
    FW_att_control_codeblock_fly_B.pitchrollerror;

  // Update for DiscreteIntegrator: '<S5>/Discrete-Time Integrator'
  FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator_DSTATE_k +=
    FW_att_control_codeblock_fly_P.DiscreteTimeIntegrator_gainva_l *
    FW_att_control_codeblock_fly_B.Add;

  // Update for UnitDelay: '<S7>/UD'
  //
  //  Block description for '<S7>/UD':
  //
  //   Store in Global RAM

  FW_att_control_codeblock_fly_DW.UD_DSTATE =
    FW_att_control_codeblock_fly_B.TSamp;

  // Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
  FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator1_DSTATE +=
    FW_att_control_codeblock_fly_P.DiscreteTimeIntegrator1_gainval *
    FW_att_control_codeblock_fly_B.pitchrollerror_m;

  // Update for DiscreteIntegrator: '<S5>/Discrete-Time Integrator1'
  FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator1_DSTAT_d +=
    FW_att_control_codeblock_fly_P.DiscreteTimeIntegrator1_gainv_k *
    FW_att_control_codeblock_fly_B.Add1;

  // Update for UnitDelay: '<S8>/UD'
  //
  //  Block description for '<S8>/UD':
  //
  //   Store in Global RAM

  FW_att_control_codeblock_fly_DW.UD_DSTATE_e =
    FW_att_control_codeblock_fly_B.TSamp_h;

  // Update for DiscreteIntegrator: '<S41>/Integrator'
  FW_att_control_codeblock_fly_DW.Integrator_DSTATE +=
    FW_att_control_codeblock_fly_P.Integrator_gainval *
    FW_att_control_codeblock_fly_B.IntegralGain;

  // Update for Delay: '<S5>/Delay'
  FW_att_control_codeblock_fly_DW.Delay_DSTATE =
    FW_att_control_codeblock_fly_B.DiscreteTimeIntegrator_h;

  // Update for Delay: '<S5>/Delay1'
  FW_att_control_codeblock_fly_DW.Delay1_DSTATE =
    FW_att_control_codeblock_fly_B.DiscreteTimeIntegrator1_p;
}

// Model initialize function
void FW_px4_AlgorithmModelClass::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' 
  FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator_DSTATE =
    FW_att_control_codeblock_fly_P.DiscreteTimeIntegrator_IC;

  // InitializeConditions for DiscreteIntegrator: '<S5>/Discrete-Time Integrator' 
  FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator_DSTATE_k =
    FW_att_control_codeblock_fly_P.DiscreteTimeIntegrator_IC_k;

  // InitializeConditions for UnitDelay: '<S7>/UD'
  //
  //  Block description for '<S7>/UD':
  //
  //   Store in Global RAM

  FW_att_control_codeblock_fly_DW.UD_DSTATE =
    FW_att_control_codeblock_fly_P.DiscreteDerivative_ICPrevScaled;

  // InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' 
  FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator1_DSTATE =
    FW_att_control_codeblock_fly_P.DiscreteTimeIntegrator1_IC;

  // InitializeConditions for DiscreteIntegrator: '<S5>/Discrete-Time Integrator1' 
  FW_att_control_codeblock_fly_DW.DiscreteTimeIntegrator1_DSTAT_d =
    FW_att_control_codeblock_fly_P.DiscreteTimeIntegrator1_IC_j;

  // InitializeConditions for UnitDelay: '<S8>/UD'
  //
  //  Block description for '<S8>/UD':
  //
  //   Store in Global RAM

  FW_att_control_codeblock_fly_DW.UD_DSTATE_e =
    FW_att_control_codeblock_fly_P.DiscreteDerivative1_ICPrevScale;

  // InitializeConditions for DiscreteIntegrator: '<S41>/Integrator'
  FW_att_control_codeblock_fly_DW.Integrator_DSTATE =
    FW_att_control_codeblock_fly_P.DiscretePIDController_InitialCo;

  // InitializeConditions for Delay: '<S5>/Delay'
  FW_att_control_codeblock_fly_DW.Delay_DSTATE =
    FW_att_control_codeblock_fly_P.Delay_InitialCondition;

  // InitializeConditions for Delay: '<S5>/Delay1'
  FW_att_control_codeblock_fly_DW.Delay1_DSTATE =
    FW_att_control_codeblock_fly_P.Delay1_InitialCondition;
}

// Model terminate function
void FW_px4_AlgorithmModelClass::terminate()
{
  // (no terminate code required)
}

// Constructor
FW_px4_AlgorithmModelClass::FW_px4_AlgorithmModelClass():
  FW_att_control_codeblock_fly_B()
  ,FW_att_control_codeblock_fly_DW()
  ,FW_att_control_codeblock_fly_U()
  ,FW_att_control_codeblock_fly_Y()
{
  // Currently there is no constructor body generated.
}

// Destructor
FW_px4_AlgorithmModelClass::~FW_px4_AlgorithmModelClass()
{
  // Currently there is no destructor body generated.
}

//
// File trailer for generated code.
//
// [EOF]
//
