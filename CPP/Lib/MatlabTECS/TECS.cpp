//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TECS.cpp
//
// Code generated for Simulink model 'TECS'.
//
// Model version                  : 1.30
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Thu Oct 15 15:30:38 2020
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
  real_T rtb_SKE_est;
  real_T rtb_SPE_rate_dem;
  real_T rtb_SEB_rate_dem;
  real_T rtb_IntegralGain;
  boolean_T rtb_NotEqual;
  boolean_T rtb_NotEqual_b;
  real_T rtb_FW_T_SPDWEIGHT_idx_7;
  real_T tmp;
  real_T u0_tmp;

  // Gain: '<S1>/ACCEL_ONE_G' incorporates:
  //   Inport: '<Root>/set_ALT'

  TECS_B.SPE_dem = TECS_P.ACCEL_ONE_G_Gain * TECS_U.set_ALT;

  // Gain: '<S1>/ACCEL_ONE_G2' incorporates:
  //   Inport: '<Root>/ALT'

  TECS_B.SPE_est = TECS_P.ACCEL_ONE_G2_Gain * TECS_U.ALT;

  // Gain: '<S1>/Gain' incorporates:
  //   Inport: '<Root>/set_Airspeed'
  //   Math: '<S1>/Square'

  TECS_B.SKE_dem = TECS_U.set_Airspeed * TECS_U.set_Airspeed * TECS_P.Gain_Gain;

  // Gain: '<S1>/Gain1' incorporates:
  //   Inport: '<Root>/Airspeed'
  //   Math: '<S1>/Square1'

  rtb_SKE_est = TECS_U.Airspeed * TECS_U.Airspeed * TECS_P.Gain1_Gain;

  // Sum: '<S4>/Subtract'
  rtb_IntegralGain = ((TECS_B.SPE_dem - TECS_B.SPE_est) + TECS_B.SKE_dem) -
    rtb_SKE_est;

  // Gain: '<S1>/ACCEL_ONE_G1' incorporates:
  //   Gain: '<S1>/FW_T_HRATE_P'
  //   Inport: '<Root>/ALT'
  //   Inport: '<Root>/set_ALT'
  //   Sum: '<S1>/Sum1'

  rtb_SPE_rate_dem = (TECS_U.set_ALT - TECS_U.ALT) * TECS_P.FW_T_HRATE_P_Gain *
    TECS_P.ACCEL_ONE_G1_Gain;

  // Product: '<S1>/Product' incorporates:
  //   Gain: '<S1>/FW_T_SRATE_P'
  //   Inport: '<Root>/Airspeed'
  //   Inport: '<Root>/set_Airspeed'
  //   Sum: '<S1>/Sum'

  TECS_B.SKE_rate_dem = (TECS_U.set_Airspeed - TECS_U.Airspeed) *
    TECS_P.FW_T_SRATE_P_Gain * TECS_U.Airspeed;

  // Gain: '<S1>/ACCEL_ONE_G3' incorporates:
  //   Inport: '<Root>/vz'

  rtb_SEB_rate_dem = TECS_P.ACCEL_ONE_G3_Gain * TECS_U.vz;

  // Product: '<S1>/Product1' incorporates:
  //   Inport: '<Root>/Airspeed'
  //   Inport: '<Root>/ax'

  TECS_B.IntegralGain_m = TECS_U.Airspeed * TECS_U.ax;

  // Sum: '<S4>/Subtract3' incorporates:
  //   Sum: '<S4>/Subtract1'

  u0_tmp = rtb_SPE_rate_dem + TECS_B.SKE_rate_dem;

  // Sum: '<S4>/Sum' incorporates:
  //   Constant: '<S4>/FW_THR_CRUISE'
  //   Gain: '<S4>/FW_T_PRE_GAIN'
  //   Sum: '<S4>/Subtract3'

  rtb_FW_T_SPDWEIGHT_idx_7 = u0_tmp * TECS_P.FW_T_PRE_GAIN_Gain +
    TECS_P.FW_THR_CRUISE_Value;

  // Saturate: '<S93>/Saturation' incorporates:
  //   DiscreteIntegrator: '<S86>/Integrator'

  if (TECS_DW.Integrator_DSTATE > TECS_P.DiscretePIDController_UpperSatu) {
    tmp = TECS_P.DiscretePIDController_UpperSatu;
  } else if (TECS_DW.Integrator_DSTATE < TECS_P.DiscretePIDController_LowerSatu)
  {
    tmp = TECS_P.DiscretePIDController_LowerSatu;
  } else {
    tmp = TECS_DW.Integrator_DSTATE;
  }

  // End of Saturate: '<S93>/Saturation'

  // Saturate: '<S4>/Saturation'
  if (rtb_FW_T_SPDWEIGHT_idx_7 > TECS_P.Saturation_UpperSat) {
    rtb_FW_T_SPDWEIGHT_idx_7 = TECS_P.Saturation_UpperSat;
  } else {
    if (rtb_FW_T_SPDWEIGHT_idx_7 < TECS_P.Saturation_LowerSat) {
      rtb_FW_T_SPDWEIGHT_idx_7 = TECS_P.Saturation_LowerSat;
    }
  }

  // End of Saturate: '<S4>/Saturation'

  // Sum: '<S4>/Sum1' incorporates:
  //   Gain: '<S4>/FW_T_THR_DAMP'
  //   Gain: '<S4>/STE_to_throttle'
  //   Sum: '<S4>/Subtract1'
  //   Sum: '<S4>/Subtract2'

  rtb_FW_T_SPDWEIGHT_idx_7 += (((u0_tmp - rtb_SEB_rate_dem) -
    TECS_B.IntegralGain_m) * TECS_P.FW_T_THR_DAMP_Gain + (tmp + rtb_IntegralGain))
    * TECS_P.STE_to_throttle_Gain;

  // Saturate: '<S4>/Saturation1'
  if (rtb_FW_T_SPDWEIGHT_idx_7 > TECS_P.Saturation1_UpperSat) {
    // Outport: '<Root>/throttle'
    TECS_Y.throttle = TECS_P.Saturation1_UpperSat;
  } else if (rtb_FW_T_SPDWEIGHT_idx_7 < TECS_P.Saturation1_LowerSat) {
    // Outport: '<Root>/throttle'
    TECS_Y.throttle = TECS_P.Saturation1_LowerSat;
  } else {
    // Outport: '<Root>/throttle'
    TECS_Y.throttle = rtb_FW_T_SPDWEIGHT_idx_7;
  }

  // End of Saturate: '<S4>/Saturation1'

  // Gain: '<S3>/FW_T_SPDWEIGHT'
  rtb_FW_T_SPDWEIGHT_idx_7 = TECS_P.FW_T_SPDWEIGHT_Gain * TECS_B.IntegralGain_m;

  // Sum: '<S3>/Subtract' incorporates:
  //   Gain: '<S3>/FW_T_SPDWEIGHT'

  TECS_B.IntegralGain_m = ((TECS_P.FW_T_SPDWEIGHT_Gain * TECS_B.SPE_dem -
    TECS_P.FW_T_SPDWEIGHT_Gain * TECS_B.SPE_est) - TECS_P.FW_T_SPDWEIGHT_Gain *
    TECS_B.SKE_dem) + TECS_P.FW_T_SPDWEIGHT_Gain * rtb_SKE_est;

  // Saturate: '<S44>/Saturation' incorporates:
  //   DiscreteIntegrator: '<S37>/Integrator'

  if (TECS_DW.Integrator_DSTATE_a > TECS_P.DiscretePIDController_UpperSa_f) {
    tmp = TECS_P.DiscretePIDController_UpperSa_f;
  } else if (TECS_DW.Integrator_DSTATE_a <
             TECS_P.DiscretePIDController_LowerSa_p) {
    tmp = TECS_P.DiscretePIDController_LowerSa_p;
  } else {
    tmp = TECS_DW.Integrator_DSTATE_a;
  }

  // End of Saturate: '<S44>/Saturation'

  // Sum: '<S3>/Subtract1' incorporates:
  //   Gain: '<S3>/FW_T_SPDWEIGHT'
  //   Sum: '<S3>/Subtract2'

  u0_tmp = TECS_P.FW_T_SPDWEIGHT_Gain * rtb_SPE_rate_dem -
    TECS_P.FW_T_SPDWEIGHT_Gain * TECS_B.SKE_rate_dem;

  // Product: '<S3>/Divide' incorporates:
  //   Gain: '<S3>/ACCEL_ONE_G'
  //   Gain: '<S3>/FW_T_P_TIME_CONST'
  //   Gain: '<S3>/FW_T_P_TIME_CONST_'
  //   Gain: '<S3>/FW_T_SPDWEIGHT'
  //   Gain: '<S3>/STE_T_INTEG_GAIN1'
  //   Inport: '<Root>/Airspeed'
  //   Sum: '<S3>/Subtract1'
  //   Sum: '<S3>/Subtract3'

  rtb_FW_T_SPDWEIGHT_idx_7 = ((((u0_tmp - TECS_P.FW_T_SPDWEIGHT_Gain *
    rtb_SEB_rate_dem) + rtb_FW_T_SPDWEIGHT_idx_7) *
    TECS_P.STE_T_INTEG_GAIN1_Gain + (tmp + TECS_B.IntegralGain_m)) + u0_tmp *
    TECS_P.FW_T_P_TIME_CONST_Gain) / (TECS_P.FW_T_P_TIME_CONST_Gain_p *
    TECS_U.Airspeed * TECS_P.ACCEL_ONE_G_Gain_j);

  // Saturate: '<S3>/Saturation'
  if (rtb_FW_T_SPDWEIGHT_idx_7 > TECS_P.Saturation_UpperSat_m) {
    // Outport: '<Root>/pitch'
    TECS_Y.pitch = TECS_P.Saturation_UpperSat_m;
  } else if (rtb_FW_T_SPDWEIGHT_idx_7 < TECS_P.Saturation_LowerSat_n) {
    // Outport: '<Root>/pitch'
    TECS_Y.pitch = TECS_P.Saturation_LowerSat_n;
  } else {
    // Outport: '<Root>/pitch'
    TECS_Y.pitch = rtb_FW_T_SPDWEIGHT_idx_7;
  }

  // End of Saturate: '<S3>/Saturation'

  // DeadZone: '<S30>/DeadZone' incorporates:
  //   DiscreteIntegrator: '<S37>/Integrator'

  if (TECS_DW.Integrator_DSTATE_a > TECS_P.DiscretePIDController_UpperSa_f) {
    TECS_B.SPE_dem = TECS_DW.Integrator_DSTATE_a -
      TECS_P.DiscretePIDController_UpperSa_f;
  } else if (TECS_DW.Integrator_DSTATE_a >=
             TECS_P.DiscretePIDController_LowerSa_p) {
    TECS_B.SPE_dem = 0.0;
  } else {
    TECS_B.SPE_dem = TECS_DW.Integrator_DSTATE_a -
      TECS_P.DiscretePIDController_LowerSa_p;
  }

  // End of DeadZone: '<S30>/DeadZone'

  // RelationalOperator: '<S30>/NotEqual' incorporates:
  //   DiscreteIntegrator: '<S37>/Integrator'
  //   Gain: '<S30>/ZeroGain'

  rtb_NotEqual = (TECS_P.ZeroGain_Gain * TECS_DW.Integrator_DSTATE_a !=
                  TECS_B.SPE_dem);

  // Signum: '<S30>/SignPreSat'
  if (TECS_B.SPE_dem < 0.0) {
    TECS_B.SPE_dem = -1.0;
  } else {
    if (TECS_B.SPE_dem > 0.0) {
      TECS_B.SPE_dem = 1.0;
    }
  }

  // End of Signum: '<S30>/SignPreSat'

  // Gain: '<S34>/Integral Gain'
  TECS_B.IntegralGain_m *= TECS_P.DiscretePIDController_I;

  // DataTypeConversion: '<S30>/DataTypeConv1'
  tmp = std::fmod(TECS_B.SPE_dem, 256.0);

  // Signum: '<S30>/SignPreIntegrator'
  if (TECS_B.IntegralGain_m < 0.0) {
    TECS_B.SPE_dem = -1.0;
  } else if (TECS_B.IntegralGain_m > 0.0) {
    TECS_B.SPE_dem = 1.0;
  } else {
    TECS_B.SPE_dem = TECS_B.IntegralGain_m;
  }

  // End of Signum: '<S30>/SignPreIntegrator'

  // DataTypeConversion: '<S30>/DataTypeConv2'
  TECS_B.SPE_dem = std::fmod(TECS_B.SPE_dem, 256.0);

  // Logic: '<S30>/AND3' incorporates:
  //   DataTypeConversion: '<S30>/DataTypeConv1'
  //   DataTypeConversion: '<S30>/DataTypeConv2'
  //   RelationalOperator: '<S30>/Equal1'

  rtb_NotEqual = (rtb_NotEqual && ((tmp < 0.0 ? static_cast<int32_T>(
    static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>(-tmp)))) :
    static_cast<int32_T>(static_cast<int8_T>(static_cast<uint8_T>(tmp)))) ==
    (TECS_B.SPE_dem < 0.0 ? static_cast<int32_T>(static_cast<int8_T>(-
    static_cast<int8_T>(static_cast<uint8_T>(-TECS_B.SPE_dem)))) :
     static_cast<int32_T>(static_cast<int8_T>(static_cast<uint8_T>
    (TECS_B.SPE_dem))))));

  // DeadZone: '<S79>/DeadZone' incorporates:
  //   DiscreteIntegrator: '<S86>/Integrator'

  if (TECS_DW.Integrator_DSTATE > TECS_P.DiscretePIDController_UpperSatu) {
    TECS_B.SPE_dem = TECS_DW.Integrator_DSTATE -
      TECS_P.DiscretePIDController_UpperSatu;
  } else if (TECS_DW.Integrator_DSTATE >= TECS_P.DiscretePIDController_LowerSatu)
  {
    TECS_B.SPE_dem = 0.0;
  } else {
    TECS_B.SPE_dem = TECS_DW.Integrator_DSTATE -
      TECS_P.DiscretePIDController_LowerSatu;
  }

  // End of DeadZone: '<S79>/DeadZone'

  // RelationalOperator: '<S79>/NotEqual' incorporates:
  //   DiscreteIntegrator: '<S86>/Integrator'
  //   Gain: '<S79>/ZeroGain'

  rtb_NotEqual_b = (TECS_P.ZeroGain_Gain_l * TECS_DW.Integrator_DSTATE !=
                    TECS_B.SPE_dem);

  // Signum: '<S79>/SignPreSat'
  if (TECS_B.SPE_dem < 0.0) {
    TECS_B.SPE_dem = -1.0;
  } else {
    if (TECS_B.SPE_dem > 0.0) {
      TECS_B.SPE_dem = 1.0;
    }
  }

  // End of Signum: '<S79>/SignPreSat'

  // Gain: '<S83>/Integral Gain'
  rtb_IntegralGain *= TECS_P.DiscretePIDController_I_l;

  // DataTypeConversion: '<S79>/DataTypeConv1'
  tmp = std::fmod(TECS_B.SPE_dem, 256.0);

  // Signum: '<S79>/SignPreIntegrator'
  if (rtb_IntegralGain < 0.0) {
    TECS_B.SPE_dem = -1.0;
  } else if (rtb_IntegralGain > 0.0) {
    TECS_B.SPE_dem = 1.0;
  } else {
    TECS_B.SPE_dem = rtb_IntegralGain;
  }

  // End of Signum: '<S79>/SignPreIntegrator'

  // DataTypeConversion: '<S79>/DataTypeConv2'
  TECS_B.SPE_dem = std::fmod(TECS_B.SPE_dem, 256.0);

  // Switch: '<S79>/Switch' incorporates:
  //   Constant: '<S79>/Constant1'
  //   DataTypeConversion: '<S79>/DataTypeConv1'
  //   DataTypeConversion: '<S79>/DataTypeConv2'
  //   Logic: '<S79>/AND3'
  //   RelationalOperator: '<S79>/Equal1'

  if (rtb_NotEqual_b && ((tmp < 0.0 ? static_cast<int32_T>(static_cast<int8_T>(-
          static_cast<int8_T>(static_cast<uint8_T>(-tmp)))) :
                          static_cast<int32_T>(static_cast<int8_T>
         (static_cast<uint8_T>(tmp)))) == (TECS_B.SPE_dem < 0.0 ?
        static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>(
           static_cast<uint8_T>(-TECS_B.SPE_dem)))) : static_cast<int32_T>(
         static_cast<int8_T>(static_cast<uint8_T>(TECS_B.SPE_dem)))))) {
    rtb_IntegralGain = TECS_P.Constant1_Value_k;
  }

  // End of Switch: '<S79>/Switch'

  // Update for DiscreteIntegrator: '<S86>/Integrator'
  TECS_DW.Integrator_DSTATE += TECS_P.Integrator_gainval * rtb_IntegralGain;

  // Switch: '<S30>/Switch' incorporates:
  //   Constant: '<S30>/Constant1'

  if (rtb_NotEqual) {
    TECS_B.IntegralGain_m = TECS_P.Constant1_Value;
  }

  // End of Switch: '<S30>/Switch'

  // Update for DiscreteIntegrator: '<S37>/Integrator'
  TECS_DW.Integrator_DSTATE_a += TECS_P.Integrator_gainval_m *
    TECS_B.IntegralGain_m;
}

// Model initialize function
void fw_TECSModelClass::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S86>/Integrator'
  TECS_DW.Integrator_DSTATE = TECS_P.DiscretePIDController_InitialCo;

  // InitializeConditions for DiscreteIntegrator: '<S37>/Integrator'
  TECS_DW.Integrator_DSTATE_a = TECS_P.DiscretePIDController_Initial_f;
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
