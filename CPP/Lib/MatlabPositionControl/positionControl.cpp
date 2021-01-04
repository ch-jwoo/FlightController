//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl.cpp
//
// Code generated for Simulink model 'positionControl'.
//
// Model version                  : 1.20
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Wed Oct  7 21:39:34 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "positionControl.h"
#include "positionControl_private.h"

// Exported block parameters
real_T hoverThr = 1550.0;              // Variable: hoverThr
                                          //  Referenced by: '<S1>/Constant'

real_T pos_x_D = 0.0;                  // Variable: pos_x_D
                                          //  Referenced by: '<S35>/Derivative Gain'

real_T pos_x_I = 0.0;                  // Variable: pos_x_I
                                          //  Referenced by: '<S38>/Integral Gain'

real_T pos_x_P = 0.95;                 // Variable: pos_x_P
                                          //  Referenced by: '<S46>/Proportional Gain'

real_T pos_x_vel_D = 0.01;             // Variable: pos_x_vel_D
                                          //  Referenced by: '<S83>/Derivative Gain'

real_T pos_x_vel_I = 0.0;             // Variable: pos_x_vel_I
                                          //  Referenced by: '<S86>/Integral Gain'

real_T pos_x_vel_P = 0.09;             // Variable: pos_x_vel_P
                                          //  Referenced by: '<S94>/Proportional Gain'

real_T pos_y_D = 0.0;                  // Variable: pos_y_D
                                          //  Referenced by: '<S179>/Derivative Gain'

real_T pos_y_I = 0.0;                  // Variable: pos_y_I
                                          //  Referenced by: '<S182>/Integral Gain'

real_T pos_y_P = 0.95;                 // Variable: pos_y_P
                                          //  Referenced by: '<S190>/Proportional Gain'

real_T pos_y_vel_D = 0.01;             // Variable: pos_y_vel_D
                                          //  Referenced by: '<S227>/Derivative Gain'

real_T pos_y_vel_I = 0.0;             // Variable: pos_y_vel_I
                                          //  Referenced by: '<S230>/Integral Gain'

real_T pos_y_vel_P = 0.09;             // Variable: pos_y_vel_P
                                          //  Referenced by: '<S238>/Proportional Gain'

real_T pos_z_D = 0.0;                  // Variable: pos_z_D
                                          //  Referenced by: '<S275>/Derivative Gain'

real_T pos_z_I = 0.0;                  // Variable: pos_z_I
                                          //  Referenced by: '<S278>/Integral Gain'

real_T pos_z_P = 0.9;                  // Variable: pos_z_P
                                          //  Referenced by: '<S286>/Proportional Gain'

real_T pos_z_vel_D = 0.01;             // Variable: pos_z_vel_D
                                          //  Referenced by: '<S131>/Derivative Gain'

real_T pos_z_vel_I = 0.4;              // Variable: pos_z_vel_I
                                          //  Referenced by: '<S134>/Integral Gain'

real_T pos_z_vel_P = 0.15;              // Variable: pos_z_vel_P
                                          //  Referenced by: '<S142>/Proportional Gain'

real32_T Yaw_angleToRate_P = 0.3F;     // Variable: Yaw_angleToRate_P
                                          //  Referenced by: '<S1>/Gain'


// Model step function
void positionControlModelClass::step()
{
  real32_T err;
  real_T sinOut;
  real_T cosOut;
  real_T tmp;
  real_T tmp_0;
  real_T tmp_1;
  real_T u2;

  // DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
  //   Inport: '<Root>/estim_yaw'

  positionControl_B.DataTypeConversion = positionControl_U.estim_yaw;

  // Trigonometry: '<S9>/Trigonometric Function'
  cosOut = positionControl_B.DataTypeConversion;
  sinOut = std::sin(cosOut);
  cosOut = std::cos(cosOut);
  positionControl_B.TrigonometricFunction_o1 = sinOut;
  positionControl_B.TrigonometricFunction_o2 = cosOut;

  // SignalConversion generated from: '<S9>/Vector Concatenate'
  positionControl_B.MatrixConcatenate[0] =
    positionControl_B.TrigonometricFunction_o2;

  // Gain: '<S9>/Gain'
  positionControl_B.MatrixConcatenate[1] = positionControl_P.Gain_Gain *
    positionControl_B.TrigonometricFunction_o1;

  // SignalConversion generated from: '<S9>/Vector Concatenate1'
  positionControl_B.MatrixConcatenate[2] =
    positionControl_B.TrigonometricFunction_o1;

  // SignalConversion generated from: '<S9>/Vector Concatenate1'
  positionControl_B.MatrixConcatenate[3] =
    positionControl_B.TrigonometricFunction_o2;

  // Sum: '<S1>/Add' incorporates:
  //   Inport: '<Root>/estim_x'
  //   Inport: '<Root>/set_x'

  positionControl_B.x_error = positionControl_U.set_x -
    positionControl_U.estim_x;

  // Gain: '<S46>/Proportional Gain'
  positionControl_B.ProportionalGain = pos_x_P * positionControl_B.x_error;

  // DiscreteIntegrator: '<S41>/Integrator'
  positionControl_B.Integrator = positionControl_DW.Integrator_DSTATE;

  // Gain: '<S35>/Derivative Gain'
  positionControl_B.DerivativeGain = pos_x_D * positionControl_B.x_error;

  // DiscreteIntegrator: '<S36>/Filter'
  positionControl_B.Filter = positionControl_DW.Filter_DSTATE;

  // Sum: '<S36>/SumD'
  positionControl_B.SumD = positionControl_B.DerivativeGain -
    positionControl_B.Filter;

  // Gain: '<S44>/Filter Coefficient'
  positionControl_B.FilterCoefficient = positionControl_P.PIDController_N *
    positionControl_B.SumD;

  // Sum: '<S50>/Sum'
  positionControl_B.Sum = (positionControl_B.ProportionalGain +
    positionControl_B.Integrator) + positionControl_B.FilterCoefficient;

  // Saturate: '<S48>/Saturation'
  cosOut = -positionControl_P.vel_Horizon_Max;
  sinOut = positionControl_B.Sum;
  u2 = positionControl_P.vel_Horizon_Max;
  if (sinOut > u2) {
    positionControl_B.Saturation = u2;
  } else if (sinOut < cosOut) {
    positionControl_B.Saturation = cosOut;
  } else {
    positionControl_B.Saturation = sinOut;
  }

  // End of Saturate: '<S48>/Saturation'

  // Sum: '<S1>/Add4' incorporates:
  //   Inport: '<Root>/estim_y'
  //   Inport: '<Root>/set_y'

  positionControl_B.y_error = positionControl_U.set_y -
    positionControl_U.estim_y;

  // Gain: '<S190>/Proportional Gain'
  positionControl_B.ProportionalGain_p = pos_y_P * positionControl_B.y_error;

  // DiscreteIntegrator: '<S185>/Integrator'
  positionControl_B.Integrator_f = positionControl_DW.Integrator_DSTATE_k;

  // Gain: '<S179>/Derivative Gain'
  positionControl_B.DerivativeGain_n = pos_y_D * positionControl_B.y_error;

  // DiscreteIntegrator: '<S180>/Filter'
  positionControl_B.Filter_p = positionControl_DW.Filter_DSTATE_m;

  // Sum: '<S180>/SumD'
  positionControl_B.SumD_k = positionControl_B.DerivativeGain_n -
    positionControl_B.Filter_p;

  // Gain: '<S188>/Filter Coefficient'
  positionControl_B.FilterCoefficient_n = positionControl_P.PIDController4_N *
    positionControl_B.SumD_k;

  // Sum: '<S194>/Sum'
  positionControl_B.Sum_k = (positionControl_B.ProportionalGain_p +
    positionControl_B.Integrator_f) + positionControl_B.FilterCoefficient_n;

  // Saturate: '<S192>/Saturation'
  cosOut = -positionControl_P.vel_Horizon_Max;
  sinOut = positionControl_B.Sum_k;
  u2 = positionControl_P.vel_Horizon_Max;
  if (sinOut > u2) {
    positionControl_B.Saturation_o = u2;
  } else if (sinOut < cosOut) {
    positionControl_B.Saturation_o = cosOut;
  } else {
    positionControl_B.Saturation_o = sinOut;
  }

  // End of Saturate: '<S192>/Saturation'

  // Sum: '<S1>/Add1' incorporates:
  //   Inport: '<Root>/estim_dx'
  //   Inport: '<Root>/estim_dy'

  positionControl_B.Add1[0] = positionControl_B.Saturation -
    positionControl_U.estim_dx;
  positionControl_B.Add1[1] = positionControl_B.Saturation_o -
    positionControl_U.estim_dy;

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

  // Gain: '<S238>/Proportional Gain'
  positionControl_B.ProportionalGain_m = pos_y_vel_P *
    positionControl_B.vel_error[1];

  // DiscreteIntegrator: '<S233>/Integrator'
  positionControl_B.Integrator_h = positionControl_DW.Integrator_DSTATE_f;

  // Gain: '<S227>/Derivative Gain'
  positionControl_B.DerivativeGain_c = pos_y_vel_D *
    positionControl_B.vel_error[1];

  // DiscreteIntegrator: '<S228>/Filter'
  positionControl_B.Filter_g = positionControl_DW.Filter_DSTATE_j;

  // Sum: '<S228>/SumD'
  positionControl_B.SumD_f = positionControl_B.DerivativeGain_c -
    positionControl_B.Filter_g;

  // Gain: '<S236>/Filter Coefficient'
  positionControl_B.FilterCoefficient_e = positionControl_P.PIDController5_N *
    positionControl_B.SumD_f;

  // Sum: '<S242>/Sum'
  positionControl_B.Sum_m = (positionControl_B.ProportionalGain_m +
    positionControl_B.Integrator_h) + positionControl_B.FilterCoefficient_e;

  // Saturate: '<S240>/Saturation'
  sinOut = positionControl_B.Sum_m;
  cosOut = positionControl_P.PIDController5_LowerSaturationL;
  u2 = positionControl_P.PIDController5_UpperSaturationL;
  if (sinOut > u2) {
    positionControl_B.Saturation_l = u2;
  } else if (sinOut < cosOut) {
    positionControl_B.Saturation_l = cosOut;
  } else {
    positionControl_B.Saturation_l = sinOut;
  }

  // End of Saturate: '<S240>/Saturation'

  // Outport: '<Root>/des_roll' incorporates:
  //   DataTypeConversion: '<S1>/Data Type Conversion3'

  positionControl_Y.des_roll = static_cast<real32_T>
    (positionControl_B.Saturation_l);

  // Gain: '<S94>/Proportional Gain'
  positionControl_B.ProportionalGain_h = pos_x_vel_P *
    positionControl_B.vel_error[0];

  // DiscreteIntegrator: '<S89>/Integrator'
  positionControl_B.Integrator_c = positionControl_DW.Integrator_DSTATE_m;

  // Gain: '<S83>/Derivative Gain'
  positionControl_B.DerivativeGain_p = pos_x_vel_D *
    positionControl_B.vel_error[0];

  // DiscreteIntegrator: '<S84>/Filter'
  positionControl_B.Filter_i = positionControl_DW.Filter_DSTATE_d;

  // Sum: '<S84>/SumD'
  positionControl_B.SumD_h = positionControl_B.DerivativeGain_p -
    positionControl_B.Filter_i;

  // Gain: '<S92>/Filter Coefficient'
  positionControl_B.FilterCoefficient_f = positionControl_P.PIDController1_N *
    positionControl_B.SumD_h;

  // Sum: '<S98>/Sum'
  positionControl_B.Sum_o = (positionControl_B.ProportionalGain_h +
    positionControl_B.Integrator_c) + positionControl_B.FilterCoefficient_f;

  // Saturate: '<S96>/Saturation'
  sinOut = positionControl_B.Sum_o;
  cosOut = positionControl_P.PIDController1_LowerSaturationL;
  u2 = positionControl_P.PIDController1_UpperSaturationL;
  if (sinOut > u2) {
    positionControl_B.Saturation_j = u2;
  } else if (sinOut < cosOut) {
    positionControl_B.Saturation_j = cosOut;
  } else {
    positionControl_B.Saturation_j = sinOut;
  }

  // End of Saturate: '<S96>/Saturation'

  // Gain: '<S1>/Gain1'
  positionControl_B.Gain1 = positionControl_P.Gain1_Gain *
    positionControl_B.Saturation_j;

  // Outport: '<Root>/des_pitch' incorporates:
  //   DataTypeConversion: '<S1>/Data Type Conversion2'

  positionControl_Y.des_pitch = static_cast<real32_T>(positionControl_B.Gain1);

  // Sum: '<S1>/Sum' incorporates:
  //   Inport: '<Root>/estim_yaw'
  //   Inport: '<Root>/set_yaw'

  positionControl_B.Sum_my = positionControl_U.set_yaw -
    positionControl_U.estim_yaw;

  // MATLAB Function: '<S1>/MATLAB Function'
  err = positionControl_B.Sum_my;
  if (positionControl_B.Sum_my > 3.1415926535897931) {
    err = positionControl_B.Sum_my - 6.28318548F;
  } else {
    if (positionControl_B.Sum_my < -3.1415926535897931) {
      err = positionControl_B.Sum_my + 6.28318548F;
    }
  }

  positionControl_B.y = err;

  // End of MATLAB Function: '<S1>/MATLAB Function'

  // Outport: '<Root>/des_yaw_rate' incorporates:
  //   Gain: '<S1>/Gain'

  positionControl_Y.des_yaw_rate = Yaw_angleToRate_P * positionControl_B.y;

  // Sum: '<S1>/Add2' incorporates:
  //   Inport: '<Root>/estim_z'
  //   Inport: '<Root>/set_z'

  positionControl_B.alt_error = positionControl_U.set_z -
    positionControl_U.estim_z;

  // Gain: '<S1>/Gain2'
  positionControl_B.Gain2 = positionControl_P.Gain2_Gain *
    positionControl_B.alt_error;

  // Gain: '<S286>/Proportional Gain'
  positionControl_B.ProportionalGain_j = pos_z_P * positionControl_B.Gain2;

  // DiscreteIntegrator: '<S281>/Integrator'
  positionControl_B.Integrator_ca = positionControl_DW.Integrator_DSTATE_p;

  // Gain: '<S275>/Derivative Gain'
  positionControl_B.DerivativeGain_f = pos_z_D * positionControl_B.Gain2;

  // DiscreteIntegrator: '<S276>/Filter'
  positionControl_B.Filter_gq = positionControl_DW.Filter_DSTATE_mo;

  // Sum: '<S276>/SumD'
  positionControl_B.SumD_d = positionControl_B.DerivativeGain_f -
    positionControl_B.Filter_gq;

  // Gain: '<S284>/Filter Coefficient'
  positionControl_B.FilterCoefficient_j = positionControl_P.ZPostoVel_N *
    positionControl_B.SumD_d;

  // Sum: '<S290>/Sum'
  positionControl_B.Sum_d = (positionControl_B.ProportionalGain_j +
    positionControl_B.Integrator_ca) + positionControl_B.FilterCoefficient_j;

  // Saturate: '<S288>/Saturation'
  cosOut = -positionControl_P.vel_descentMax;
  sinOut = positionControl_B.Sum_d;
  u2 = positionControl_P.vel_climbMax;
  if (sinOut > u2) {
    positionControl_B.Saturation_jh = u2;
  } else if (sinOut < cosOut) {
    positionControl_B.Saturation_jh = cosOut;
  } else {
    positionControl_B.Saturation_jh = sinOut;
  }

  // End of Saturate: '<S288>/Saturation'

  // Gain: '<S1>/Gain3' incorporates:
  //   Inport: '<Root>/estim_dz'

  positionControl_B.Gain3 = positionControl_P.Gain3_Gain *
    positionControl_U.estim_dz;

  // Sum: '<S1>/Add3'
  positionControl_B.Add3 = positionControl_B.Saturation_jh -
    positionControl_B.Gain3;

  // Gain: '<S142>/Proportional Gain'
  positionControl_B.ProportionalGain_k = pos_z_vel_P * positionControl_B.Add3;

  // DiscreteIntegrator: '<S137>/Integrator'
  positionControl_B.Integrator_p = positionControl_DW.Integrator_DSTATE_b;

  // Gain: '<S131>/Derivative Gain'
  positionControl_B.DerivativeGain_pu = pos_z_vel_D * positionControl_B.Add3;

  // DiscreteIntegrator: '<S132>/Filter'
  positionControl_B.Filter_m = positionControl_DW.Filter_DSTATE_e;

  // Sum: '<S132>/SumD'
  positionControl_B.SumD_b = positionControl_B.DerivativeGain_pu -
    positionControl_B.Filter_m;

  // Gain: '<S140>/Filter Coefficient'
  positionControl_B.FilterCoefficient_a = positionControl_P.PIDController3_N *
    positionControl_B.SumD_b;

  // Sum: '<S146>/Sum'
  positionControl_B.Sum_c = (positionControl_B.ProportionalGain_k +
    positionControl_B.Integrator_p) + positionControl_B.FilterCoefficient_a;

  // Saturate: '<S144>/Saturation'
  sinOut = positionControl_B.Sum_c;
  cosOut = positionControl_P.PIDController3_LowerSaturationL;
  u2 = positionControl_P.PIDController3_UpperSaturationL;
  if (sinOut > u2) {
    positionControl_B.Saturation_li = u2;
  } else if (sinOut < cosOut) {
    positionControl_B.Saturation_li = cosOut;
  } else {
    positionControl_B.Saturation_li = sinOut;
  }

  // End of Saturate: '<S144>/Saturation'

  // Sum: '<S1>/Sum1' incorporates:
  //   Constant: '<S1>/Constant'

  cosOut = (hoverThr - 1000.0) / 1000.0;
  positionControl_B.Sum1 = positionControl_B.Saturation_li + cosOut;

  // Saturate: '<S1>/Saturation'
  sinOut = positionControl_B.Sum1;
  cosOut = positionControl_P.Saturation_LowerSat;
  u2 = positionControl_P.Saturation_UpperSat;
  if (sinOut > u2) {
    positionControl_B.Saturation_jb = u2;
  } else if (sinOut < cosOut) {
    positionControl_B.Saturation_jb = cosOut;
  } else {
    positionControl_B.Saturation_jb = sinOut;
  }

  // End of Saturate: '<S1>/Saturation'

  // Outport: '<Root>/des_Thrust' incorporates:
  //   DataTypeConversion: '<S1>/Data Type Conversion4'

  positionControl_Y.des_Thrust = static_cast<real32_T>
    (positionControl_B.Saturation_jb);

  // Gain: '<S34>/ZeroGain'
  positionControl_B.ZeroGain = positionControl_P.ZeroGain_Gain *
    positionControl_B.Sum;

  // DeadZone: '<S34>/DeadZone'
  if (positionControl_B.Sum > positionControl_P.vel_Horizon_Max) {
    positionControl_B.DeadZone = positionControl_B.Sum -
      positionControl_P.vel_Horizon_Max;
  } else {
    cosOut = -positionControl_P.vel_Horizon_Max;
    if (positionControl_B.Sum >= cosOut) {
      positionControl_B.DeadZone = 0.0;
    } else {
      cosOut = -positionControl_P.vel_Horizon_Max;
      positionControl_B.DeadZone = positionControl_B.Sum - cosOut;
    }
  }

  // End of DeadZone: '<S34>/DeadZone'

  // RelationalOperator: '<S34>/NotEqual'
  positionControl_B.NotEqual = (positionControl_B.ZeroGain !=
    positionControl_B.DeadZone);

  // Signum: '<S34>/SignPreSat'
  cosOut = positionControl_B.DeadZone;
  if (cosOut < 0.0) {
    positionControl_B.SignPreSat = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreSat = 1.0;
  } else {
    positionControl_B.SignPreSat = cosOut;
  }

  // End of Signum: '<S34>/SignPreSat'

  // DataTypeConversion: '<S34>/DataTypeConv1'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreSat), 256.0);
  positionControl_B.DataTypeConv1 = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // Gain: '<S38>/Integral Gain'
  positionControl_B.IntegralGain = pos_x_I * positionControl_B.x_error;

  // Signum: '<S34>/SignPreIntegrator'
  cosOut = positionControl_B.IntegralGain;
  if (cosOut < 0.0) {
    positionControl_B.SignPreIntegrator = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreIntegrator = 1.0;
  } else {
    positionControl_B.SignPreIntegrator = cosOut;
  }

  // End of Signum: '<S34>/SignPreIntegrator'

  // DataTypeConversion: '<S34>/DataTypeConv2'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreIntegrator), 256.0);
  positionControl_B.DataTypeConv2 = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>(static_cast<
    uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>(static_cast<
    uint8_T>(cosOut))));

  // RelationalOperator: '<S34>/Equal1'
  positionControl_B.Equal1 = (positionControl_B.DataTypeConv1 ==
    positionControl_B.DataTypeConv2);

  // Logic: '<S34>/AND3'
  positionControl_B.AND3 = (positionControl_B.NotEqual &&
    positionControl_B.Equal1);

  // Switch: '<S34>/Switch' incorporates:
  //   Constant: '<S34>/Constant1'

  if (positionControl_B.AND3) {
    positionControl_B.Switch = positionControl_P.Constant1_Value;
  } else {
    positionControl_B.Switch = positionControl_B.IntegralGain;
  }

  // End of Switch: '<S34>/Switch'

  // Gain: '<S82>/ZeroGain'
  positionControl_B.ZeroGain_h = positionControl_P.ZeroGain_Gain_c *
    positionControl_B.Sum_o;

  // DeadZone: '<S82>/DeadZone'
  if (positionControl_B.Sum_o >
      positionControl_P.PIDController1_UpperSaturationL) {
    positionControl_B.DeadZone_p = positionControl_B.Sum_o -
      positionControl_P.PIDController1_UpperSaturationL;
  } else if (positionControl_B.Sum_o >=
             positionControl_P.PIDController1_LowerSaturationL) {
    positionControl_B.DeadZone_p = 0.0;
  } else {
    positionControl_B.DeadZone_p = positionControl_B.Sum_o -
      positionControl_P.PIDController1_LowerSaturationL;
  }

  // End of DeadZone: '<S82>/DeadZone'

  // RelationalOperator: '<S82>/NotEqual'
  positionControl_B.NotEqual_k = (positionControl_B.ZeroGain_h !=
    positionControl_B.DeadZone_p);

  // Signum: '<S82>/SignPreSat'
  cosOut = positionControl_B.DeadZone_p;
  if (cosOut < 0.0) {
    positionControl_B.SignPreSat_i = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreSat_i = 1.0;
  } else {
    positionControl_B.SignPreSat_i = cosOut;
  }

  // End of Signum: '<S82>/SignPreSat'

  // DataTypeConversion: '<S82>/DataTypeConv1'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreSat_i), 256.0);
  positionControl_B.DataTypeConv1_b = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // Gain: '<S86>/Integral Gain'
  positionControl_B.IntegralGain_k = pos_x_vel_I * positionControl_B.vel_error[0];

  // Signum: '<S82>/SignPreIntegrator'
  cosOut = positionControl_B.IntegralGain_k;
  if (cosOut < 0.0) {
    positionControl_B.SignPreIntegrator_p = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreIntegrator_p = 1.0;
  } else {
    positionControl_B.SignPreIntegrator_p = cosOut;
  }

  // End of Signum: '<S82>/SignPreIntegrator'

  // DataTypeConversion: '<S82>/DataTypeConv2'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreIntegrator_p), 256.0);
  positionControl_B.DataTypeConv2_o = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // RelationalOperator: '<S82>/Equal1'
  positionControl_B.Equal1_d = (positionControl_B.DataTypeConv1_b ==
    positionControl_B.DataTypeConv2_o);

  // Logic: '<S82>/AND3'
  positionControl_B.AND3_a = (positionControl_B.NotEqual_k &&
    positionControl_B.Equal1_d);

  // Switch: '<S82>/Switch' incorporates:
  //   Constant: '<S82>/Constant1'

  if (positionControl_B.AND3_a) {
    positionControl_B.Switch_b = positionControl_P.Constant1_Value_m;
  } else {
    positionControl_B.Switch_b = positionControl_B.IntegralGain_k;
  }

  // End of Switch: '<S82>/Switch'

  // Gain: '<S178>/ZeroGain'
  positionControl_B.ZeroGain_o = positionControl_P.ZeroGain_Gain_j *
    positionControl_B.Sum_k;

  // DeadZone: '<S178>/DeadZone'
  if (positionControl_B.Sum_k > positionControl_P.vel_Horizon_Max) {
    positionControl_B.DeadZone_g = positionControl_B.Sum_k -
      positionControl_P.vel_Horizon_Max;
  } else {
    cosOut = -positionControl_P.vel_Horizon_Max;
    if (positionControl_B.Sum_k >= cosOut) {
      positionControl_B.DeadZone_g = 0.0;
    } else {
      cosOut = -positionControl_P.vel_Horizon_Max;
      positionControl_B.DeadZone_g = positionControl_B.Sum_k - cosOut;
    }
  }

  // End of DeadZone: '<S178>/DeadZone'

  // RelationalOperator: '<S178>/NotEqual'
  positionControl_B.NotEqual_e = (positionControl_B.ZeroGain_o !=
    positionControl_B.DeadZone_g);

  // Signum: '<S178>/SignPreSat'
  cosOut = positionControl_B.DeadZone_g;
  if (cosOut < 0.0) {
    positionControl_B.SignPreSat_ij = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreSat_ij = 1.0;
  } else {
    positionControl_B.SignPreSat_ij = cosOut;
  }

  // End of Signum: '<S178>/SignPreSat'

  // DataTypeConversion: '<S178>/DataTypeConv1'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreSat_ij), 256.0);
  positionControl_B.DataTypeConv1_l = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // Gain: '<S182>/Integral Gain'
  positionControl_B.IntegralGain_o = pos_y_I * positionControl_B.y_error;

  // Signum: '<S178>/SignPreIntegrator'
  cosOut = positionControl_B.IntegralGain_o;
  if (cosOut < 0.0) {
    positionControl_B.SignPreIntegrator_d = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreIntegrator_d = 1.0;
  } else {
    positionControl_B.SignPreIntegrator_d = cosOut;
  }

  // End of Signum: '<S178>/SignPreIntegrator'

  // DataTypeConversion: '<S178>/DataTypeConv2'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreIntegrator_d), 256.0);
  positionControl_B.DataTypeConv2_d = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // RelationalOperator: '<S178>/Equal1'
  positionControl_B.Equal1_a = (positionControl_B.DataTypeConv1_l ==
    positionControl_B.DataTypeConv2_d);

  // Logic: '<S178>/AND3'
  positionControl_B.AND3_o = (positionControl_B.NotEqual_e &&
    positionControl_B.Equal1_a);

  // Switch: '<S178>/Switch' incorporates:
  //   Constant: '<S178>/Constant1'

  if (positionControl_B.AND3_o) {
    positionControl_B.Switch_p = positionControl_P.Constant1_Value_l;
  } else {
    positionControl_B.Switch_p = positionControl_B.IntegralGain_o;
  }

  // End of Switch: '<S178>/Switch'

  // Gain: '<S226>/ZeroGain'
  positionControl_B.ZeroGain_b = positionControl_P.ZeroGain_Gain_m *
    positionControl_B.Sum_m;

  // DeadZone: '<S226>/DeadZone'
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

  // End of DeadZone: '<S226>/DeadZone'

  // RelationalOperator: '<S226>/NotEqual'
  positionControl_B.NotEqual_p = (positionControl_B.ZeroGain_b !=
    positionControl_B.DeadZone_m);

  // Signum: '<S226>/SignPreSat'
  cosOut = positionControl_B.DeadZone_m;
  if (cosOut < 0.0) {
    positionControl_B.SignPreSat_n = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreSat_n = 1.0;
  } else {
    positionControl_B.SignPreSat_n = cosOut;
  }

  // End of Signum: '<S226>/SignPreSat'

  // DataTypeConversion: '<S226>/DataTypeConv1'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreSat_n), 256.0);
  positionControl_B.DataTypeConv1_e = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // Gain: '<S230>/Integral Gain'
  positionControl_B.IntegralGain_b = pos_y_vel_I * positionControl_B.vel_error[1];

  // Signum: '<S226>/SignPreIntegrator'
  cosOut = positionControl_B.IntegralGain_b;
  if (cosOut < 0.0) {
    positionControl_B.SignPreIntegrator_n = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreIntegrator_n = 1.0;
  } else {
    positionControl_B.SignPreIntegrator_n = cosOut;
  }

  // End of Signum: '<S226>/SignPreIntegrator'

  // DataTypeConversion: '<S226>/DataTypeConv2'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreIntegrator_n), 256.0);
  positionControl_B.DataTypeConv2_a = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // RelationalOperator: '<S226>/Equal1'
  positionControl_B.Equal1_c = (positionControl_B.DataTypeConv1_e ==
    positionControl_B.DataTypeConv2_a);

  // Logic: '<S226>/AND3'
  positionControl_B.AND3_n = (positionControl_B.NotEqual_p &&
    positionControl_B.Equal1_c);

  // Switch: '<S226>/Switch' incorporates:
  //   Constant: '<S226>/Constant1'

  if (positionControl_B.AND3_n) {
    positionControl_B.Switch_m = positionControl_P.Constant1_Value_n;
  } else {
    positionControl_B.Switch_m = positionControl_B.IntegralGain_b;
  }

  // End of Switch: '<S226>/Switch'

  // Gain: '<S130>/ZeroGain'
  positionControl_B.ZeroGain_e = positionControl_P.ZeroGain_Gain_h *
    positionControl_B.Sum_c;

  // DeadZone: '<S130>/DeadZone'
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

  // End of DeadZone: '<S130>/DeadZone'

  // RelationalOperator: '<S130>/NotEqual'
  positionControl_B.NotEqual_o = (positionControl_B.ZeroGain_e !=
    positionControl_B.DeadZone_e);

  // Signum: '<S130>/SignPreSat'
  cosOut = positionControl_B.DeadZone_e;
  if (cosOut < 0.0) {
    positionControl_B.SignPreSat_h = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreSat_h = 1.0;
  } else {
    positionControl_B.SignPreSat_h = cosOut;
  }

  // End of Signum: '<S130>/SignPreSat'

  // DataTypeConversion: '<S130>/DataTypeConv1'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreSat_h), 256.0);
  positionControl_B.DataTypeConv1_m = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // Gain: '<S134>/Integral Gain'
  positionControl_B.IntegralGain_l = pos_z_vel_I * positionControl_B.Add3;

  // Signum: '<S130>/SignPreIntegrator'
  cosOut = positionControl_B.IntegralGain_l;
  if (cosOut < 0.0) {
    positionControl_B.SignPreIntegrator_dl = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreIntegrator_dl = 1.0;
  } else {
    positionControl_B.SignPreIntegrator_dl = cosOut;
  }

  // End of Signum: '<S130>/SignPreIntegrator'

  // DataTypeConversion: '<S130>/DataTypeConv2'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreIntegrator_dl), 256.0);
  positionControl_B.DataTypeConv2_j = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // RelationalOperator: '<S130>/Equal1'
  positionControl_B.Equal1_i = (positionControl_B.DataTypeConv1_m ==
    positionControl_B.DataTypeConv2_j);

  // Logic: '<S130>/AND3'
  positionControl_B.AND3_nv = (positionControl_B.NotEqual_o &&
    positionControl_B.Equal1_i);

  // Switch: '<S130>/Switch' incorporates:
  //   Constant: '<S130>/Constant1'

  if (positionControl_B.AND3_nv) {
    positionControl_B.Switch_e = positionControl_P.Constant1_Value_k;
  } else {
    positionControl_B.Switch_e = positionControl_B.IntegralGain_l;
  }

  // End of Switch: '<S130>/Switch'

  // Gain: '<S274>/ZeroGain'
  positionControl_B.ZeroGain_a = positionControl_P.ZeroGain_Gain_b *
    positionControl_B.Sum_d;

  // DeadZone: '<S274>/DeadZone'
  if (positionControl_B.Sum_d > positionControl_P.vel_climbMax) {
    positionControl_B.DeadZone_b = positionControl_B.Sum_d -
      positionControl_P.vel_climbMax;
  } else {
    cosOut = -positionControl_P.vel_descentMax;
    if (positionControl_B.Sum_d >= cosOut) {
      positionControl_B.DeadZone_b = 0.0;
    } else {
      cosOut = -positionControl_P.vel_descentMax;
      positionControl_B.DeadZone_b = positionControl_B.Sum_d - cosOut;
    }
  }

  // End of DeadZone: '<S274>/DeadZone'

  // RelationalOperator: '<S274>/NotEqual'
  positionControl_B.NotEqual_i = (positionControl_B.ZeroGain_a !=
    positionControl_B.DeadZone_b);

  // Signum: '<S274>/SignPreSat'
  cosOut = positionControl_B.DeadZone_b;
  if (cosOut < 0.0) {
    positionControl_B.SignPreSat_ir = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreSat_ir = 1.0;
  } else {
    positionControl_B.SignPreSat_ir = cosOut;
  }

  // End of Signum: '<S274>/SignPreSat'

  // DataTypeConversion: '<S274>/DataTypeConv1'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreSat_ir), 256.0);
  positionControl_B.DataTypeConv1_es = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // Gain: '<S278>/Integral Gain'
  positionControl_B.IntegralGain_g = pos_z_I * positionControl_B.Gain2;

  // Signum: '<S274>/SignPreIntegrator'
  cosOut = positionControl_B.IntegralGain_g;
  if (cosOut < 0.0) {
    positionControl_B.SignPreIntegrator_h = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreIntegrator_h = 1.0;
  } else {
    positionControl_B.SignPreIntegrator_h = cosOut;
  }

  // End of Signum: '<S274>/SignPreIntegrator'

  // DataTypeConversion: '<S274>/DataTypeConv2'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreIntegrator_h), 256.0);
  positionControl_B.DataTypeConv2_m = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // RelationalOperator: '<S274>/Equal1'
  positionControl_B.Equal1_l = (positionControl_B.DataTypeConv1_es ==
    positionControl_B.DataTypeConv2_m);

  // Logic: '<S274>/AND3'
  positionControl_B.AND3_m = (positionControl_B.NotEqual_i &&
    positionControl_B.Equal1_l);

  // Switch: '<S274>/Switch' incorporates:
  //   Constant: '<S274>/Constant1'

  if (positionControl_B.AND3_m) {
    positionControl_B.Switch_h = positionControl_P.Constant1_Value_ke;
  } else {
    positionControl_B.Switch_h = positionControl_B.IntegralGain_g;
  }

  // End of Switch: '<S274>/Switch'

  // Update for DiscreteIntegrator: '<S41>/Integrator'
  positionControl_DW.Integrator_DSTATE += positionControl_P.Integrator_gainval *
    positionControl_B.Switch;

  // Update for DiscreteIntegrator: '<S36>/Filter'
  positionControl_DW.Filter_DSTATE += positionControl_P.Filter_gainval *
    positionControl_B.FilterCoefficient;

  // Update for DiscreteIntegrator: '<S185>/Integrator'
  positionControl_DW.Integrator_DSTATE_k +=
    positionControl_P.Integrator_gainval_l * positionControl_B.Switch_p;

  // Update for DiscreteIntegrator: '<S180>/Filter'
  positionControl_DW.Filter_DSTATE_m += positionControl_P.Filter_gainval_l *
    positionControl_B.FilterCoefficient_n;

  // Update for DiscreteIntegrator: '<S233>/Integrator'
  positionControl_DW.Integrator_DSTATE_f +=
    positionControl_P.Integrator_gainval_k * positionControl_B.Switch_m;

  // Update for DiscreteIntegrator: '<S228>/Filter'
  positionControl_DW.Filter_DSTATE_j += positionControl_P.Filter_gainval_i *
    positionControl_B.FilterCoefficient_e;

  // Update for DiscreteIntegrator: '<S89>/Integrator'
  positionControl_DW.Integrator_DSTATE_m +=
    positionControl_P.Integrator_gainval_lc * positionControl_B.Switch_b;

  // Update for DiscreteIntegrator: '<S84>/Filter'
  positionControl_DW.Filter_DSTATE_d += positionControl_P.Filter_gainval_l5 *
    positionControl_B.FilterCoefficient_f;

  // Update for DiscreteIntegrator: '<S281>/Integrator'
  positionControl_DW.Integrator_DSTATE_p +=
    positionControl_P.Integrator_gainval_j * positionControl_B.Switch_h;

  // Update for DiscreteIntegrator: '<S276>/Filter'
  positionControl_DW.Filter_DSTATE_mo += positionControl_P.Filter_gainval_c *
    positionControl_B.FilterCoefficient_j;

  // Update for DiscreteIntegrator: '<S137>/Integrator'
  positionControl_DW.Integrator_DSTATE_b +=
    positionControl_P.Integrator_gainval_a * positionControl_B.Switch_e;

  // Update for DiscreteIntegrator: '<S132>/Filter'
  positionControl_DW.Filter_DSTATE_e += positionControl_P.Filter_gainval_g *
    positionControl_B.FilterCoefficient_a;
}

// Model initialize function
void positionControlModelClass::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S41>/Integrator'
  positionControl_DW.Integrator_DSTATE =
    positionControl_P.PIDController_InitialConditio_c;

  // InitializeConditions for DiscreteIntegrator: '<S36>/Filter'
  positionControl_DW.Filter_DSTATE =
    positionControl_P.PIDController_InitialConditionF;

  // InitializeConditions for DiscreteIntegrator: '<S185>/Integrator'
  positionControl_DW.Integrator_DSTATE_k =
    positionControl_P.PIDController4_InitialConditi_i;

  // InitializeConditions for DiscreteIntegrator: '<S180>/Filter'
  positionControl_DW.Filter_DSTATE_m =
    positionControl_P.PIDController4_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S233>/Integrator'
  positionControl_DW.Integrator_DSTATE_f =
    positionControl_P.PIDController5_InitialConditi_c;

  // InitializeConditions for DiscreteIntegrator: '<S228>/Filter'
  positionControl_DW.Filter_DSTATE_j =
    positionControl_P.PIDController5_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S89>/Integrator'
  positionControl_DW.Integrator_DSTATE_m =
    positionControl_P.PIDController1_InitialConditi_a;

  // InitializeConditions for DiscreteIntegrator: '<S84>/Filter'
  positionControl_DW.Filter_DSTATE_d =
    positionControl_P.PIDController1_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S281>/Integrator'
  positionControl_DW.Integrator_DSTATE_p =
    positionControl_P.ZPostoVel_InitialConditionForIn;

  // InitializeConditions for DiscreteIntegrator: '<S276>/Filter'
  positionControl_DW.Filter_DSTATE_mo =
    positionControl_P.ZPostoVel_InitialConditionForFi;

  // InitializeConditions for DiscreteIntegrator: '<S137>/Integrator'
  positionControl_DW.Integrator_DSTATE_b =
    positionControl_P.PIDController3_InitialConditi_d;

  // InitializeConditions for DiscreteIntegrator: '<S132>/Filter'
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
const positionControlModelClass::P_positionControl_T & positionControlModelClass::
  getBlockParameters() const
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
