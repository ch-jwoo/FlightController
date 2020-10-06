//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TECS.cpp
//
// Code generated for Simulink model 'TECS'.
//
// Model version                  : 1.27
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Mon Oct  5 14:56:44 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "TECS.h"
#include "TECS_private.h"

// Model step function
void fw_TECSModelClass::step()
{
  real_T rtb_STE_error;
  real_T rtb_SPE_est;
  real_T rtb_SKE_dem;
  real_T rtb_SKE_est;
  real_T rtb_SPE_rate_dem;
  real_T rtb_SPED_rate;
  real_T rtb_throttle_predicted;
  real_T u0_tmp;

  // Gain: '<S1>/ACCEL_ONE_G' incorporates:
  //   Inport: '<Root>/set_ALT'

  rtb_STE_error = TECS_P.ACCEL_ONE_G_Gain * TECS_U.set_ALT;

  // Gain: '<S1>/ACCEL_ONE_G2' incorporates:
  //   Inport: '<Root>/ALT'

  rtb_SPE_est = TECS_P.ACCEL_ONE_G2_Gain * TECS_U.ALT;

  // Gain: '<S1>/Gain' incorporates:
  //   Inport: '<Root>/set_Airspeed'
  //   Math: '<S1>/Square'

  rtb_SKE_dem = TECS_U.set_Airspeed * TECS_U.set_Airspeed * TECS_P.Gain_Gain;

  // Gain: '<S1>/Gain1' incorporates:
  //   Inport: '<Root>/Airspeed'
  //   Math: '<S1>/Square1'

  rtb_SKE_est = TECS_U.Airspeed * TECS_U.Airspeed * TECS_P.Gain1_Gain;

  // Gain: '<S1>/ACCEL_ONE_G1' incorporates:
  //   Gain: '<S1>/FW_T_HRATE_FF'
  //   Gain: '<S41>/Proportional Gain'
  //   Inport: '<Root>/ALT'
  //   Inport: '<Root>/set_ALT'
  //   Inport: '<Root>/vz'
  //   Sum: '<S1>/Sum1'
  //   Sum: '<S1>/Sum2'

  rtb_SPE_rate_dem = ((TECS_U.set_ALT - TECS_U.ALT) * TECS_P.FW_T_HRATE_P_P +
                      TECS_P.FW_T_HRATE_FF_Gain * TECS_U.vz) *
    TECS_P.ACCEL_ONE_G1_Gain;

  // Product: '<S1>/Product' incorporates:
  //   Gain: '<S89>/Proportional Gain'
  //   Inport: '<Root>/Airspeed'
  //   Inport: '<Root>/set_Airspeed'
  //   Sum: '<S1>/Sum'

  TECS_B.SKE_rate_dem = (TECS_U.set_Airspeed - TECS_U.Airspeed) *
    TECS_P.FW_T_SRATE_P_P * TECS_U.Airspeed;

  // Gain: '<S1>/ACCEL_ONE_G3' incorporates:
  //   Inport: '<Root>/vz'

  rtb_SPED_rate = TECS_P.ACCEL_ONE_G3_Gain * TECS_U.vz;

  // Product: '<S1>/Product1' incorporates:
  //   Inport: '<Root>/Airspeed'
  //   Inport: '<Root>/ax'

  TECS_B.SKE_rate = TECS_U.Airspeed * TECS_U.ax;

  // Sum: '<S101>/Subtract' incorporates:
  //   Gain: '<S101>/FW_T_SPDWEIGHT'

  rtb_throttle_predicted = ((TECS_P.FW_T_SPDWEIGHT_Gain * rtb_STE_error -
    TECS_P.FW_T_SPDWEIGHT_Gain * rtb_SPE_est) - TECS_P.FW_T_SPDWEIGHT_Gain *
    rtb_SKE_dem) + TECS_P.FW_T_SPDWEIGHT_Gain * rtb_SKE_est;

  // Sum: '<S101>/Subtract1' incorporates:
  //   Gain: '<S101>/FW_T_SPDWEIGHT'
  //   Sum: '<S101>/Subtract2'

  u0_tmp = TECS_P.FW_T_SPDWEIGHT_Gain * rtb_SPE_rate_dem -
    TECS_P.FW_T_SPDWEIGHT_Gain * TECS_B.SKE_rate_dem;

  // Product: '<S101>/Divide' incorporates:
  //   DiscreteIntegrator: '<S136>/Integrator'
  //   Gain: '<S101>/ACCEL_ONE_G'
  //   Gain: '<S101>/FW_T_SPDWEIGHT'
  //   Gain: '<S101>/FW_T_TIME_CONST'
  //   Gain: '<S101>/FW_T_TIME_CONST_'
  //   Gain: '<S189>/Proportional Gain'
  //   Inport: '<Root>/Airspeed'
  //   Sum: '<S101>/Subtract1'
  //   Sum: '<S101>/Subtract3'

  TECS_Y.pitch = ((((u0_tmp - TECS_P.FW_T_SPDWEIGHT_Gain * rtb_SPED_rate) +
                    TECS_P.FW_T_SPDWEIGHT_Gain * TECS_B.SKE_rate) *
                   TECS_P.FW_T_PITCH_DAMP_P + (TECS_DW.Integrator_DSTATE +
    rtb_throttle_predicted)) + u0_tmp * TECS_P.FW_T_TIME_CONST_Gain) /
    (TECS_P.FW_T_TIME_CONST_Gain_p * TECS_U.Airspeed * TECS_P.ACCEL_ONE_G_Gain_j);

  // Saturate: '<S101>/Saturation'
  if (TECS_Y.pitch > TECS_P.Saturation_UpperSat) {
    // Product: '<S101>/Divide' incorporates:
    //   Outport: '<Root>/pitch'

    TECS_Y.pitch = TECS_P.Saturation_UpperSat;
  } else {
    if (TECS_Y.pitch < TECS_P.Saturation_LowerSat) {
      // Product: '<S101>/Divide' incorporates:
      //   Outport: '<Root>/pitch'

      TECS_Y.pitch = TECS_P.Saturation_LowerSat;
    }
  }

  // End of Saturate: '<S101>/Saturation'

  // Sum: '<S102>/Subtract'
  rtb_STE_error = ((rtb_STE_error - rtb_SPE_est) + rtb_SKE_dem) - rtb_SKE_est;

  // Sum: '<S102>/Subtract1' incorporates:
  //   Sum: '<S102>/Subtract3'

  u0_tmp = rtb_SPE_rate_dem + TECS_B.SKE_rate_dem;

  // Gain: '<S336>/Proportional Gain' incorporates:
  //   Gain: '<S240>/Proportional Gain'
  //   Gain: '<S288>/Proportional Gain'
  //   Sum: '<S102>/Subtract1'
  //   Sum: '<S102>/Subtract2'

  rtb_STE_error = (((u0_tmp - rtb_SPED_rate) - TECS_B.SKE_rate) *
                   TECS_P.FW_T_THR_DAMP_P + (TECS_P.FW_T_INTEG_GAIN_P *
    rtb_STE_error + rtb_STE_error)) * TECS_P.STE_to_throttle_P;

  // Sum: '<S102>/Sum' incorporates:
  //   Constant: '<S102>/FW_THR_CRUISE'
  //   Gain: '<S102>/FW_T_PRE_GAIN'

  u0_tmp = u0_tmp * TECS_P.FW_T_PRE_GAIN_Gain + TECS_P.FW_THR_CRUISE_Value;

  // Saturate: '<S338>/Saturation'
  if (rtb_STE_error > TECS_P.STE_to_throttle_UpperSaturation) {
    rtb_STE_error = TECS_P.STE_to_throttle_UpperSaturation;
  } else {
    if (rtb_STE_error < TECS_P.STE_to_throttle_LowerSaturation) {
      rtb_STE_error = TECS_P.STE_to_throttle_LowerSaturation;
    }
  }

  // End of Saturate: '<S338>/Saturation'

  // Saturate: '<S102>/Saturation'
  if (u0_tmp > TECS_P.Saturation_UpperSat_i) {
    u0_tmp = TECS_P.Saturation_UpperSat_i;
  } else {
    if (u0_tmp < TECS_P.Saturation_LowerSat_f) {
      u0_tmp = TECS_P.Saturation_LowerSat_f;
    }
  }

  // End of Saturate: '<S102>/Saturation'

  // Sum: '<S102>/Sum1'
  TECS_Y.throttle = rtb_STE_error + u0_tmp;

  // Saturate: '<S102>/Saturation1'
  if (TECS_Y.throttle > TECS_P.Saturation1_UpperSat) {
    // Sum: '<S102>/Sum1' incorporates:
    //   Outport: '<Root>/throttle'

    TECS_Y.throttle = TECS_P.Saturation1_UpperSat;
  } else {
    if (TECS_Y.throttle < TECS_P.Saturation1_LowerSat) {
      // Sum: '<S102>/Sum1' incorporates:
      //   Outport: '<Root>/throttle'

      TECS_Y.throttle = TECS_P.Saturation1_LowerSat;
    }
  }

  // End of Saturate: '<S102>/Saturation1'

  // Update for DiscreteIntegrator: '<S136>/Integrator' incorporates:
  //   Gain: '<S133>/Integral Gain'

  TECS_DW.Integrator_DSTATE += TECS_P.FW_T_INTEGRAL_GAIN_I *
    rtb_throttle_predicted * TECS_P.Integrator_gainval;
}

// Model initialize function
void fw_TECSModelClass::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S136>/Integrator'
  TECS_DW.Integrator_DSTATE = TECS_P.FW_T_INTEGRAL_GAIN_InitialCondi;
}

// Model terminate function
void fw_TECSModelClass::terminate()
{
  // (no terminate code required)
}

// Constructor
fw_TECSModelClass::fw_TECSModelClass():
  TECS_B()
  ,TECS_DW()
  ,TECS_U()
  ,TECS_Y()
  ,TECS_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
fw_TECSModelClass::~fw_TECSModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
fw_TECSModelClass::RT_MODEL_TECS_T * fw_TECSModelClass::getRTM()
{
  return (&TECS_M);
}

//
// File trailer for generated code.
//
// [EOF]
//

