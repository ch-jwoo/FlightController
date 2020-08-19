//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl.cpp
//
// Code generated for Simulink model 'positionControl'.
//
// Model version                  : 1.7
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Wed Aug 19 08:09:50 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "positionControl.h"
#include "positionControl_private.h"

// Exported block parameters
real_T Yaw_angleToRate_P = 0.04;       // Variable: Yaw_angleToRate_P
                                          //  Referenced by: '<S1>/Gain'

real_T pos_x_D = 0.0;                  // Variable: pos_x_D
                                          //  Referenced by: '<S34>/Derivative Gain'

real_T pos_x_I = 0.02;                  // Variable: pos_x_I
                                          //  Referenced by: '<S37>/Integral Gain'

real_T pos_x_P = 0.2;                  // Variable: pos_x_P
                                          //  Referenced by: '<S45>/Proportional Gain'

real_T pos_x_vel_D = 0.001;            // Variable: pos_x_vel_D
                                          //  Referenced by: '<S82>/Derivative Gain'

real_T pos_x_vel_I = 0.02;             // Variable: pos_x_vel_I
                                          //  Referenced by: '<S85>/Integral Gain'

real_T pos_x_vel_P = 0.2;              // Variable: pos_x_vel_P
                                          //  Referenced by: '<S93>/Proportional Gain'

real_T pos_y_I = 0.02;                  // Variable: pos_y_I
                                          //  Referenced by: '<S229>/Integral Gain'

real_T pos_y_P = 0.2;                  // Variable: pos_y_P
                                          //  Referenced by: '<S237>/Proportional Gain'

real_T pos_y_vel_D = 0.001;            // Variable: pos_y_vel_D
                                          //  Referenced by: '<S274>/Derivative Gain'

real_T pos_y_vel_I = 0.02;             // Variable: pos_y_vel_I
                                          //  Referenced by: '<S277>/Integral Gain'

real_T pos_y_vel_P = 0.2;              // Variable: pos_y_vel_P
                                          //  Referenced by: '<S285>/Proportional Gain'

real_T pos_z_D = 0.0;                  // Variable: pos_z_D
                                          //  Referenced by: '<S130>/Derivative Gain'

real_T pos_z_I = 0.0;                  // Variable: pos_z_I
                                          //  Referenced by: '<S133>/Integral Gain'

real_T pos_z_P = 0.6;                  // Variable: pos_z_P
                                          //  Referenced by: '<S141>/Proportional Gain'

real_T pos_z_vel_D = 0.001;            // Variable: pos_z_vel_D
                                          //  Referenced by: '<S178>/Derivative Gain'

real_T pos_z_vel_I = 0.02;              // Variable: pos_z_vel_I
                                          //  Referenced by: '<S181>/Integral Gain'

real_T pos_z_vel_P = 0.4;              // Variable: pos_z_vel_P
                                          //  Referenced by: '<S189>/Proportional Gain'


// Model step function
void positionControlModelClass::step()
{
  real_T sinOut;
  real_T cosOut;
  real_T tmp;
  real_T tmp_0;
  real_T tmp_1;
  real_T u2;

  // DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
  //   Inport: '<Root>/estim_yaw'

  positionControl_B.DataTypeConversion = positionControl_U.estim_yaw;

  // Trigonometry: '<S8>/Trigonometric Function'
  cosOut = positionControl_B.DataTypeConversion;
  sinOut = std::sin(cosOut);
  cosOut = std::cos(cosOut);
  positionControl_B.TrigonometricFunction_o1 = sinOut;
  positionControl_B.TrigonometricFunction_o2 = cosOut;

  // SignalConversion generated from: '<S8>/Vector Concatenate'
  positionControl_B.MatrixConcatenate[0] =
    positionControl_B.TrigonometricFunction_o2;

  // Gain: '<S8>/Gain'
  positionControl_B.MatrixConcatenate[1] = positionControl_P.Gain_Gain *
    positionControl_B.TrigonometricFunction_o1;

  // SignalConversion generated from: '<S8>/Vector Concatenate1'
  positionControl_B.MatrixConcatenate[2] =
    positionControl_B.TrigonometricFunction_o1;

  // SignalConversion generated from: '<S8>/Vector Concatenate1'
  positionControl_B.MatrixConcatenate[3] =
    positionControl_B.TrigonometricFunction_o2;

  // Sum: '<S1>/Add' incorporates:
  //   Inport: '<Root>/estim_x'
  //   Inport: '<Root>/set_x'

  positionControl_B.x_error = positionControl_U.set_x -
    positionControl_U.estim_x;

  // Gain: '<S45>/Proportional Gain'
  positionControl_B.ProportionalGain = pos_x_P * positionControl_B.x_error;

  // DiscreteIntegrator: '<S40>/Integrator'
  positionControl_B.Integrator = positionControl_DW.Integrator_DSTATE;

  // Gain: '<S34>/Derivative Gain'
  positionControl_B.DerivativeGain = pos_x_D * positionControl_B.x_error;

  // DiscreteIntegrator: '<S35>/Filter'
  positionControl_B.Filter = positionControl_DW.Filter_DSTATE;

  // Sum: '<S35>/SumD'
  positionControl_B.SumD = positionControl_B.DerivativeGain -
    positionControl_B.Filter;

  // Gain: '<S43>/Filter Coefficient'
  positionControl_B.FilterCoefficient = positionControl_P.PIDController_N *
    positionControl_B.SumD;

  // Sum: '<S49>/Sum'
  positionControl_B.Sum = positionControl_B.ProportionalGain +
    positionControl_B.Integrator + positionControl_B.FilterCoefficient;

  // Saturate: '<S47>/Saturation'
  cosOut = positionControl_B.Sum;
  sinOut = positionControl_P.PIDController_LowerSaturationLi;
  u2 = positionControl_P.PIDController_UpperSaturationLi;
  if (cosOut > u2) {
    positionControl_B.Saturation = u2;
  } else if (cosOut < sinOut) {
    positionControl_B.Saturation = sinOut;
  } else {
    positionControl_B.Saturation = cosOut;
  }

  // End of Saturate: '<S47>/Saturation'

  // Sum: '<S1>/Add4' incorporates:
  //   Inport: '<Root>/estim_y'
  //   Inport: '<Root>/set_y'

  positionControl_B.y_error = positionControl_U.set_y -
    positionControl_U.estim_y;

  // Gain: '<S237>/Proportional Gain'
  positionControl_B.ProportionalGain_p = pos_y_P * positionControl_B.y_error;

  // DiscreteIntegrator: '<S232>/Integrator'
  positionControl_B.Integrator_f = positionControl_DW.Integrator_DSTATE_k;

  // Gain: '<S226>/Derivative Gain'
  positionControl_B.DerivativeGain_n = positionControl_P.pos_y_D *
    positionControl_B.y_error;

  // DiscreteIntegrator: '<S227>/Filter'
  positionControl_B.Filter_p = positionControl_DW.Filter_DSTATE_m;

  // Sum: '<S227>/SumD'
  positionControl_B.SumD_k = positionControl_B.DerivativeGain_n -
    positionControl_B.Filter_p;

  // Gain: '<S235>/Filter Coefficient'
  positionControl_B.FilterCoefficient_n = positionControl_P.PIDController4_N *
    positionControl_B.SumD_k;

  // Sum: '<S241>/Sum'
  positionControl_B.Sum_k = positionControl_B.ProportionalGain_p +
    positionControl_B.Integrator_f + positionControl_B.FilterCoefficient_n;

  // Saturate: '<S239>/Saturation'
  cosOut = positionControl_B.Sum_k;
  sinOut = positionControl_P.PIDController4_LowerSaturationL;
  u2 = positionControl_P.PIDController4_UpperSaturationL;
  if (cosOut > u2) {
    positionControl_B.Saturation_o = u2;
  } else if (cosOut < sinOut) {
    positionControl_B.Saturation_o = sinOut;
  } else {
    positionControl_B.Saturation_o = cosOut;
  }

  // End of Saturate: '<S239>/Saturation'

  // Sum: '<S1>/Add1' incorporates:
  //   Inport: '<Root>/estim_dx'
  //   Inport: '<Root>/estim_dy'

  positionControl_B.Add1[0] = positionControl_U.estim_dx -
    positionControl_B.Saturation;
  positionControl_B.Add1[1] = positionControl_U.estim_dy -
    positionControl_B.Saturation_o;

  // Product: '<S1>/Matrix Multiply'
  cosOut = positionControl_B.MatrixConcatenate[0];
  sinOut = positionControl_B.MatrixConcatenate[1];
  u2 = positionControl_B.MatrixConcatenate[2];
  tmp = positionControl_B.MatrixConcatenate[3];
  tmp_0 = positionControl_B.Add1[0];
  tmp_1 = positionControl_B.Add1[1];
  cosOut *= tmp_0;
  cosOut += u2 * tmp_1;
  positionControl_B.vel_error[0] = cosOut;
  sinOut *= tmp_0;
  sinOut += tmp * tmp_1;
  positionControl_B.vel_error[1] = sinOut;

  // Gain: '<S285>/Proportional Gain'
  positionControl_B.ProportionalGain_m = pos_y_vel_P *
    positionControl_B.vel_error[1];

  // DiscreteIntegrator: '<S280>/Integrator'
  positionControl_B.Integrator_h = positionControl_DW.Integrator_DSTATE_f;

  // Gain: '<S274>/Derivative Gain'
  positionControl_B.DerivativeGain_c = pos_y_vel_D *
    positionControl_B.vel_error[1];

  // DiscreteIntegrator: '<S275>/Filter'
  positionControl_B.Filter_g = positionControl_DW.Filter_DSTATE_j;

  // Sum: '<S275>/SumD'
  positionControl_B.SumD_f = positionControl_B.DerivativeGain_c -
    positionControl_B.Filter_g;

  // Gain: '<S283>/Filter Coefficient'
  positionControl_B.FilterCoefficient_e = positionControl_P.PIDController5_N *
    positionControl_B.SumD_f;

  // Sum: '<S289>/Sum'
  positionControl_B.Sum_m = positionControl_B.ProportionalGain_m +
    positionControl_B.Integrator_h + positionControl_B.FilterCoefficient_e;

  // Saturate: '<S287>/Saturation'
  cosOut = positionControl_B.Sum_m;
  sinOut = positionControl_P.PIDController5_LowerSaturationL;
  u2 = positionControl_P.PIDController5_UpperSaturationL;
  if (cosOut > u2) {
    positionControl_B.Saturation_l = u2;
  } else if (cosOut < sinOut) {
    positionControl_B.Saturation_l = sinOut;
  } else {
    positionControl_B.Saturation_l = cosOut;
  }

  // End of Saturate: '<S287>/Saturation'

  // Gain: '<S1>/Gain1'
  positionControl_B.Gain1 = positionControl_P.Gain1_Gain *
    positionControl_B.Saturation_l;

  // Outport: '<Root>/des_roll' incorporates:
  //   DataTypeConversion: '<S1>/Data Type Conversion3'

  positionControl_Y.des_roll = static_cast<real32_T>(positionControl_B.Gain1);

  // Gain: '<S93>/Proportional Gain'
  positionControl_B.ProportionalGain_h = pos_x_vel_P *
    positionControl_B.vel_error[0];

  // DiscreteIntegrator: '<S88>/Integrator'
  positionControl_B.Integrator_c = positionControl_DW.Integrator_DSTATE_m;

  // Gain: '<S82>/Derivative Gain'
  positionControl_B.DerivativeGain_p = pos_x_vel_D *
    positionControl_B.vel_error[0];

  // DiscreteIntegrator: '<S83>/Filter'
  positionControl_B.Filter_i = positionControl_DW.Filter_DSTATE_d;

  // Sum: '<S83>/SumD'
  positionControl_B.SumD_h = positionControl_B.DerivativeGain_p -
    positionControl_B.Filter_i;

  // Gain: '<S91>/Filter Coefficient'
  positionControl_B.FilterCoefficient_f = positionControl_P.PIDController1_N *
    positionControl_B.SumD_h;

  // Sum: '<S97>/Sum'
  positionControl_B.Sum_o = positionControl_B.ProportionalGain_h +
    positionControl_B.Integrator_c + positionControl_B.FilterCoefficient_f;

  // Saturate: '<S95>/Saturation'
  cosOut = positionControl_B.Sum_o;
  sinOut = positionControl_P.PIDController1_LowerSaturationL;
  u2 = positionControl_P.PIDController1_UpperSaturationL;
  if (cosOut > u2) {
    positionControl_B.Saturation_j = u2;
  } else if (cosOut < sinOut) {
    positionControl_B.Saturation_j = sinOut;
  } else {
    positionControl_B.Saturation_j = cosOut;
  }

  // End of Saturate: '<S95>/Saturation'

  // Outport: '<Root>/des_pitch' incorporates:
  //   DataTypeConversion: '<S1>/Data Type Conversion2'

  positionControl_Y.des_pitch = static_cast<real32_T>
    (positionControl_B.Saturation_j);

  // Sum: '<S1>/Sum' incorporates:
  //   Inport: '<Root>/set_yaw'

  positionControl_B.Sum_my = positionControl_U.set_yaw -
    positionControl_B.DataTypeConversion;

  // Gain: '<S1>/Gain'
  positionControl_B.Gain = Yaw_angleToRate_P * positionControl_B.Sum_my;

  // Outport: '<Root>/des_yaw_rate' incorporates:
  //   DataTypeConversion: '<S1>/Data Type Conversion1'

  positionControl_Y.des_yaw_rate = static_cast<real32_T>(positionControl_B.Gain);

  // Sum: '<S1>/Add2' incorporates:
  //   Inport: '<Root>/estim_z'
  //   Inport: '<Root>/set_z'

  positionControl_B.alt_error = positionControl_U.set_z -
    positionControl_U.estim_z;

  // Gain: '<S141>/Proportional Gain'
  positionControl_B.ProportionalGain_p4 = pos_z_P * positionControl_B.alt_error;

  // DiscreteIntegrator: '<S136>/Integrator'
  positionControl_B.Integrator_b = positionControl_DW.Integrator_DSTATE_j;

  // Gain: '<S130>/Derivative Gain'
  positionControl_B.DerivativeGain_b = pos_z_D * positionControl_B.alt_error;

  // DiscreteIntegrator: '<S131>/Filter'
  positionControl_B.Filter_o = positionControl_DW.Filter_DSTATE_mf;

  // Sum: '<S131>/SumD'
  positionControl_B.SumD_m = positionControl_B.DerivativeGain_b -
    positionControl_B.Filter_o;

  // Gain: '<S139>/Filter Coefficient'
  positionControl_B.FilterCoefficient_d = positionControl_P.PIDController2_N *
    positionControl_B.SumD_m;

  // Sum: '<S145>/Sum'
  positionControl_B.Sum_f = positionControl_B.ProportionalGain_p4 +
    positionControl_B.Integrator_b + positionControl_B.FilterCoefficient_d;

  // Saturate: '<S143>/Saturation'
  cosOut = positionControl_B.Sum_f;
  sinOut = positionControl_P.PIDController2_LowerSaturationL;
  u2 = positionControl_P.PIDController2_UpperSaturationL;
  if (cosOut > u2) {
    positionControl_B.Saturation_m = u2;
  } else if (cosOut < sinOut) {
    positionControl_B.Saturation_m = sinOut;
  } else {
    positionControl_B.Saturation_m = cosOut;
  }

  // End of Saturate: '<S143>/Saturation'

  // Sum: '<S1>/Add3' incorporates:
  //   Inport: '<Root>/estim_dz'

  positionControl_B.vz_error = positionControl_B.Saturation_m -
    positionControl_U.estim_dz;

  // Gain: '<S189>/Proportional Gain'
  positionControl_B.ProportionalGain_k = pos_z_vel_P *
    positionControl_B.vz_error;

  // DiscreteIntegrator: '<S184>/Integrator'
  positionControl_B.Integrator_p = positionControl_DW.Integrator_DSTATE_b;

  // Gain: '<S178>/Derivative Gain'
  positionControl_B.DerivativeGain_pu = pos_z_vel_D * positionControl_B.vz_error;

  // DiscreteIntegrator: '<S179>/Filter'
  positionControl_B.Filter_m = positionControl_DW.Filter_DSTATE_e;

  // Sum: '<S179>/SumD'
  positionControl_B.SumD_b = positionControl_B.DerivativeGain_pu -
    positionControl_B.Filter_m;

  // Gain: '<S187>/Filter Coefficient'
  positionControl_B.FilterCoefficient_a = positionControl_P.PIDController3_N *
    positionControl_B.SumD_b;

  // Sum: '<S193>/Sum'
  positionControl_B.Sum_c = positionControl_B.ProportionalGain_k +
    positionControl_B.Integrator_p + positionControl_B.FilterCoefficient_a;

  // Saturate: '<S191>/Saturation'
  cosOut = positionControl_B.Sum_c;
  sinOut = positionControl_P.PIDController3_LowerSaturationL;
  u2 = positionControl_P.PIDController3_UpperSaturationL;
  if (cosOut > u2) {
    positionControl_B.Saturation_li = u2;
  } else if (cosOut < sinOut) {
    positionControl_B.Saturation_li = sinOut;
  } else {
    positionControl_B.Saturation_li = cosOut;
  }

  // End of Saturate: '<S191>/Saturation'

  // Outport: '<Root>/des_Thrust' incorporates:
  //   DataTypeConversion: '<S1>/Data Type Conversion4'

  positionControl_Y.des_Thrust = static_cast<real32_T>
    (positionControl_B.Saturation_li);

  // Gain: '<S37>/Integral Gain'
  positionControl_B.IntegralGain = pos_x_I * positionControl_B.x_error;

  // Gain: '<S81>/ZeroGain'
  positionControl_B.ZeroGain = positionControl_P.ZeroGain_Gain *
    positionControl_B.Sum_o;

  // DeadZone: '<S81>/DeadZone'
  if (positionControl_B.Sum_o >
      positionControl_P.PIDController1_UpperSaturationL) {
    positionControl_B.DeadZone = positionControl_B.Sum_o -
      positionControl_P.PIDController1_UpperSaturationL;
  } else if (positionControl_B.Sum_o >=
             positionControl_P.PIDController1_LowerSaturationL) {
    positionControl_B.DeadZone = 0.0;
  } else {
    positionControl_B.DeadZone = positionControl_B.Sum_o -
      positionControl_P.PIDController1_LowerSaturationL;
  }

  // End of DeadZone: '<S81>/DeadZone'

  // RelationalOperator: '<S81>/NotEqual'
  positionControl_B.NotEqual = positionControl_B.ZeroGain !=
    positionControl_B.DeadZone;

  // Signum: '<S81>/SignPreSat'
  cosOut = positionControl_B.DeadZone;
  if (cosOut < 0.0) {
    positionControl_B.SignPreSat = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreSat = 1.0;
  } else {
    positionControl_B.SignPreSat = cosOut;
  }

  // End of Signum: '<S81>/SignPreSat'

  // DataTypeConversion: '<S81>/DataTypeConv1'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreSat), 256.0);
  positionControl_B.DataTypeConv1 = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // Gain: '<S85>/Integral Gain'
  positionControl_B.IntegralGain_k = pos_x_vel_I * positionControl_B.vel_error[0];

  // Signum: '<S81>/SignPreIntegrator'
  cosOut = positionControl_B.IntegralGain_k;
  if (cosOut < 0.0) {
    positionControl_B.SignPreIntegrator = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreIntegrator = 1.0;
  } else {
    positionControl_B.SignPreIntegrator = cosOut;
  }

  // End of Signum: '<S81>/SignPreIntegrator'

  // DataTypeConversion: '<S81>/DataTypeConv2'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreIntegrator), 256.0);
  positionControl_B.DataTypeConv2 = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>(static_cast<
    uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>(static_cast<
    uint8_T>(cosOut))));

  // RelationalOperator: '<S81>/Equal1'
  positionControl_B.Equal1 = positionControl_B.DataTypeConv1 ==
    positionControl_B.DataTypeConv2;

  // Logic: '<S81>/AND3'
  positionControl_B.AND3 = positionControl_B.NotEqual &&
    positionControl_B.Equal1;

  // Switch: '<S81>/Switch' incorporates:
  //   Constant: '<S81>/Constant1'

  if (positionControl_B.AND3) {
    positionControl_B.Switch = positionControl_P.Constant1_Value;
  } else {
    positionControl_B.Switch = positionControl_B.IntegralGain_k;
  }

  // End of Switch: '<S81>/Switch'

  // Gain: '<S229>/Integral Gain'
  positionControl_B.IntegralGain_o = pos_y_I * positionControl_B.y_error;

  // Gain: '<S273>/ZeroGain'
  positionControl_B.ZeroGain_b = positionControl_P.ZeroGain_Gain_m *
    positionControl_B.Sum_m;

  // DeadZone: '<S273>/DeadZone'
  if (positionControl_B.Sum_m >
      positionControl_P.PIDController5_UpperSaturationL) {
    positionControl_B.DeadZone_m = positionControl_B.Sum_m -
      positionControl_P.PIDController5_UpperSaturationL;
  } else if (positionControl_B.Sum_m >=
             positionControl_P.PIDController5_LowerSaturationL) {
    positionControl_B.DeadZone_m = 0.0;
  } else {
    positionControl_B.DeadZone_m = positionControl_B.Sum_m -
      positionControl_P.PIDController5_LowerSaturationL;
  }

  // End of DeadZone: '<S273>/DeadZone'

  // RelationalOperator: '<S273>/NotEqual'
  positionControl_B.NotEqual_p = positionControl_B.ZeroGain_b !=
    positionControl_B.DeadZone_m;

  // Signum: '<S273>/SignPreSat'
  cosOut = positionControl_B.DeadZone_m;
  if (cosOut < 0.0) {
    positionControl_B.SignPreSat_n = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreSat_n = 1.0;
  } else {
    positionControl_B.SignPreSat_n = cosOut;
  }

  // End of Signum: '<S273>/SignPreSat'

  // DataTypeConversion: '<S273>/DataTypeConv1'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreSat_n), 256.0);
  positionControl_B.DataTypeConv1_e = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // Gain: '<S277>/Integral Gain'
  positionControl_B.IntegralGain_b = pos_y_vel_I * positionControl_B.vel_error[1];

  // Signum: '<S273>/SignPreIntegrator'
  cosOut = positionControl_B.IntegralGain_b;
  if (cosOut < 0.0) {
    positionControl_B.SignPreIntegrator_n = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreIntegrator_n = 1.0;
  } else {
    positionControl_B.SignPreIntegrator_n = cosOut;
  }

  // End of Signum: '<S273>/SignPreIntegrator'

  // DataTypeConversion: '<S273>/DataTypeConv2'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreIntegrator_n), 256.0);
  positionControl_B.DataTypeConv2_a = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // RelationalOperator: '<S273>/Equal1'
  positionControl_B.Equal1_c = positionControl_B.DataTypeConv1_e ==
    positionControl_B.DataTypeConv2_a;

  // Logic: '<S273>/AND3'
  positionControl_B.AND3_n = positionControl_B.NotEqual_p &&
    positionControl_B.Equal1_c;

  // Switch: '<S273>/Switch' incorporates:
  //   Constant: '<S273>/Constant1'

  if (positionControl_B.AND3_n) {
    positionControl_B.Switch_m = positionControl_P.Constant1_Value_n;
  } else {
    positionControl_B.Switch_m = positionControl_B.IntegralGain_b;
  }

  // End of Switch: '<S273>/Switch'

  // Gain: '<S133>/Integral Gain'
  positionControl_B.IntegralGain_f = pos_z_I * positionControl_B.alt_error;

  // Gain: '<S177>/ZeroGain'
  positionControl_B.ZeroGain_e = positionControl_P.ZeroGain_Gain_h *
    positionControl_B.Sum_c;

  // DeadZone: '<S177>/DeadZone'
  if (positionControl_B.Sum_c >
      positionControl_P.PIDController3_UpperSaturationL) {
    positionControl_B.DeadZone_e = positionControl_B.Sum_c -
      positionControl_P.PIDController3_UpperSaturationL;
  } else if (positionControl_B.Sum_c >=
             positionControl_P.PIDController3_LowerSaturationL) {
    positionControl_B.DeadZone_e = 0.0;
  } else {
    positionControl_B.DeadZone_e = positionControl_B.Sum_c -
      positionControl_P.PIDController3_LowerSaturationL;
  }

  // End of DeadZone: '<S177>/DeadZone'

  // RelationalOperator: '<S177>/NotEqual'
  positionControl_B.NotEqual_o = positionControl_B.ZeroGain_e !=
    positionControl_B.DeadZone_e;

  // Signum: '<S177>/SignPreSat'
  cosOut = positionControl_B.DeadZone_e;
  if (cosOut < 0.0) {
    positionControl_B.SignPreSat_h = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreSat_h = 1.0;
  } else {
    positionControl_B.SignPreSat_h = cosOut;
  }

  // End of Signum: '<S177>/SignPreSat'

  // DataTypeConversion: '<S177>/DataTypeConv1'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreSat_h), 256.0);
  positionControl_B.DataTypeConv1_m = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // Gain: '<S181>/Integral Gain'
  positionControl_B.IntegralGain_l = pos_z_vel_I * positionControl_B.vz_error;

  // Signum: '<S177>/SignPreIntegrator'
  cosOut = positionControl_B.IntegralGain_l;
  if (cosOut < 0.0) {
    positionControl_B.SignPreIntegrator_d = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreIntegrator_d = 1.0;
  } else {
    positionControl_B.SignPreIntegrator_d = cosOut;
  }

  // End of Signum: '<S177>/SignPreIntegrator'

  // DataTypeConversion: '<S177>/DataTypeConv2'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreIntegrator_d), 256.0);
  positionControl_B.DataTypeConv2_j = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // RelationalOperator: '<S177>/Equal1'
  positionControl_B.Equal1_i = positionControl_B.DataTypeConv1_m ==
    positionControl_B.DataTypeConv2_j;

  // Logic: '<S177>/AND3'
  positionControl_B.AND3_nv = positionControl_B.NotEqual_o &&
    positionControl_B.Equal1_i;

  // Switch: '<S177>/Switch' incorporates:
  //   Constant: '<S177>/Constant1'

  if (positionControl_B.AND3_nv) {
    positionControl_B.Switch_e = positionControl_P.Constant1_Value_k;
  } else {
    positionControl_B.Switch_e = positionControl_B.IntegralGain_l;
  }

  // End of Switch: '<S177>/Switch'

  // Update for DiscreteIntegrator: '<S40>/Integrator'
  positionControl_DW.Integrator_DSTATE += positionControl_P.Integrator_gainval *
    positionControl_B.IntegralGain;

  // Update for DiscreteIntegrator: '<S35>/Filter'
  positionControl_DW.Filter_DSTATE += positionControl_P.Filter_gainval *
    positionControl_B.FilterCoefficient;

  // Update for DiscreteIntegrator: '<S232>/Integrator'
  positionControl_DW.Integrator_DSTATE_k +=
    positionControl_P.Integrator_gainval_l * positionControl_B.IntegralGain_o;

  // Update for DiscreteIntegrator: '<S227>/Filter'
  positionControl_DW.Filter_DSTATE_m += positionControl_P.Filter_gainval_l *
    positionControl_B.FilterCoefficient_n;

  // Update for DiscreteIntegrator: '<S280>/Integrator'
  positionControl_DW.Integrator_DSTATE_f +=
    positionControl_P.Integrator_gainval_k * positionControl_B.Switch_m;

  // Update for DiscreteIntegrator: '<S275>/Filter'
  positionControl_DW.Filter_DSTATE_j += positionControl_P.Filter_gainval_i *
    positionControl_B.FilterCoefficient_e;

  // Update for DiscreteIntegrator: '<S88>/Integrator'
  positionControl_DW.Integrator_DSTATE_m +=
    positionControl_P.Integrator_gainval_lc * positionControl_B.Switch;

  // Update for DiscreteIntegrator: '<S83>/Filter'
  positionControl_DW.Filter_DSTATE_d += positionControl_P.Filter_gainval_l5 *
    positionControl_B.FilterCoefficient_f;

  // Update for DiscreteIntegrator: '<S136>/Integrator'
  positionControl_DW.Integrator_DSTATE_j +=
    positionControl_P.Integrator_gainval_o * positionControl_B.IntegralGain_f;

  // Update for DiscreteIntegrator: '<S131>/Filter'
  positionControl_DW.Filter_DSTATE_mf += positionControl_P.Filter_gainval_f *
    positionControl_B.FilterCoefficient_d;

  // Update for DiscreteIntegrator: '<S184>/Integrator'
  positionControl_DW.Integrator_DSTATE_b +=
    positionControl_P.Integrator_gainval_a * positionControl_B.Switch_e;

  // Update for DiscreteIntegrator: '<S179>/Filter'
  positionControl_DW.Filter_DSTATE_e += positionControl_P.Filter_gainval_g *
    positionControl_B.FilterCoefficient_a;
}

// Model initialize function
void positionControlModelClass::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S40>/Integrator'
  positionControl_DW.Integrator_DSTATE =
    positionControl_P.PIDController_InitialConditio_c;

  // InitializeConditions for DiscreteIntegrator: '<S35>/Filter'
  positionControl_DW.Filter_DSTATE =
    positionControl_P.PIDController_InitialConditionF;

  // InitializeConditions for DiscreteIntegrator: '<S232>/Integrator'
  positionControl_DW.Integrator_DSTATE_k =
    positionControl_P.PIDController4_InitialConditi_i;

  // InitializeConditions for DiscreteIntegrator: '<S227>/Filter'
  positionControl_DW.Filter_DSTATE_m =
    positionControl_P.PIDController4_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S280>/Integrator'
  positionControl_DW.Integrator_DSTATE_f =
    positionControl_P.PIDController5_InitialConditi_c;

  // InitializeConditions for DiscreteIntegrator: '<S275>/Filter'
  positionControl_DW.Filter_DSTATE_j =
    positionControl_P.PIDController5_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S88>/Integrator'
  positionControl_DW.Integrator_DSTATE_m =
    positionControl_P.PIDController1_InitialConditi_a;

  // InitializeConditions for DiscreteIntegrator: '<S83>/Filter'
  positionControl_DW.Filter_DSTATE_d =
    positionControl_P.PIDController1_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S136>/Integrator'
  positionControl_DW.Integrator_DSTATE_j =
    positionControl_P.PIDController2_InitialConditi_n;

  // InitializeConditions for DiscreteIntegrator: '<S131>/Filter'
  positionControl_DW.Filter_DSTATE_mf =
    positionControl_P.PIDController2_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S184>/Integrator'
  positionControl_DW.Integrator_DSTATE_b =
    positionControl_P.PIDController3_InitialConditi_d;

  // InitializeConditions for DiscreteIntegrator: '<S179>/Filter'
  positionControl_DW.Filter_DSTATE_e =
    positionControl_P.PIDController3_InitialCondition;
}

// Model terminate function
void positionControlModelClass::terminate()
{
  // (no terminate code required)
}

// Constructor
positionControlModelClass::positionControlModelClass():
  positionControl_B()
  ,positionControl_DW()
  ,positionControl_U()
  ,positionControl_Y()
{
  // Currently there is no constructor body generated.
}

// Destructor
positionControlModelClass::~positionControlModelClass()
{
  // Currently there is no destructor body generated.
}

// Block parameters get method
const P_positionControl_T & positionControlModelClass::getBlockParameters()
  const
{
  return positionControl_P;
}

// Block parameters set method
void positionControlModelClass::setBlockParameters(const P_positionControl_T
  *ppositionControl_P)
{
  positionControl_P = *ppositionControl_P;
}

//
// File trailer for generated code.
//
// [EOF]
//
