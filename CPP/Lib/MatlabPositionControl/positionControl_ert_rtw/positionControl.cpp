//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl.cpp
//
// Code generated for Simulink model 'positionControl'.
//
// Model version                  : 1.8
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Fri Aug 21 23:47:28 2020
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

real_T pos_x_D = 0.1;                  // Variable: pos_x_D
                                          //  Referenced by: '<S33>/Derivative Gain'

real_T pos_x_I = 0.0;                  // Variable: pos_x_I
                                          //  Referenced by: '<S36>/Integral Gain'

real_T pos_x_P = 0.7;                  // Variable: pos_x_P
                                          //  Referenced by: '<S44>/Proportional Gain'

real_T pos_x_vel_D = 0.11;             // Variable: pos_x_vel_D
                                          //  Referenced by: '<S81>/Derivative Gain'

real_T pos_x_vel_I = 0.0;              // Variable: pos_x_vel_I
                                          //  Referenced by: '<S84>/Integral Gain'

real_T pos_x_vel_P = 0.17;             // Variable: pos_x_vel_P
                                          //  Referenced by: '<S92>/Proportional Gain'

real_T pos_y_I = 0.0;                  // Variable: pos_y_I
                                          //  Referenced by: '<S180>/Integral Gain'

real_T pos_y_P = 0.88;                 // Variable: pos_y_P
                                          //  Referenced by: '<S188>/Proportional Gain'

real_T pos_y_vel_D = 0.11;             // Variable: pos_y_vel_D
                                          //  Referenced by: '<S225>/Derivative Gain'

real_T pos_y_vel_I = 0.3;              // Variable: pos_y_vel_I
                                          //  Referenced by: '<S228>/Integral Gain'

real_T pos_y_vel_P = 0.17;             // Variable: pos_y_vel_P
                                          //  Referenced by: '<S236>/Proportional Gain'

real_T pos_z_D = 0.01;                 // Variable: pos_z_D
                                          //  Referenced by: '<S129>/Derivative Gain'

real_T pos_z_I = 0.2;                  // Variable: pos_z_I
                                          //  Referenced by: '<S132>/Integral Gain'

real_T pos_z_P = 0.27;                 // Variable: pos_z_P
                                          //  Referenced by: '<S140>/Proportional Gain'


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

  // Trigonometry: '<S7>/Trigonometric Function'
  cosOut = positionControl_B.DataTypeConversion;
  sinOut = std::sin(cosOut);
  cosOut = std::cos(cosOut);
  positionControl_B.TrigonometricFunction_o1 = sinOut;
  positionControl_B.TrigonometricFunction_o2 = cosOut;

  // SignalConversion generated from: '<S7>/Vector Concatenate'
  positionControl_B.MatrixConcatenate[0] =
    positionControl_B.TrigonometricFunction_o2;

  // Gain: '<S7>/Gain'
  positionControl_B.MatrixConcatenate[1] = positionControl_P.Gain_Gain *
    positionControl_B.TrigonometricFunction_o1;

  // SignalConversion generated from: '<S7>/Vector Concatenate1'
  positionControl_B.MatrixConcatenate[2] =
    positionControl_B.TrigonometricFunction_o1;

  // SignalConversion generated from: '<S7>/Vector Concatenate1'
  positionControl_B.MatrixConcatenate[3] =
    positionControl_B.TrigonometricFunction_o2;

  // Sum: '<S1>/Add' incorporates:
  //   Inport: '<Root>/estim_x'
  //   Inport: '<Root>/set_x'

  positionControl_B.x_error = positionControl_U.set_x -
    positionControl_U.estim_x;

  // Gain: '<S44>/Proportional Gain'
  positionControl_B.ProportionalGain = pos_x_P * positionControl_B.x_error;

  // DiscreteIntegrator: '<S39>/Integrator'
  positionControl_B.Integrator = positionControl_DW.Integrator_DSTATE;

  // Gain: '<S33>/Derivative Gain'
  positionControl_B.DerivativeGain = pos_x_D * positionControl_B.x_error;

  // DiscreteIntegrator: '<S34>/Filter'
  positionControl_B.Filter = positionControl_DW.Filter_DSTATE;

  // Sum: '<S34>/SumD'
  positionControl_B.SumD = positionControl_B.DerivativeGain -
    positionControl_B.Filter;

  // Gain: '<S42>/Filter Coefficient'
  positionControl_B.FilterCoefficient = positionControl_P.PIDController_N *
    positionControl_B.SumD;

  // Sum: '<S48>/Sum'
  positionControl_B.Sum = (positionControl_B.ProportionalGain +
    positionControl_B.Integrator) + positionControl_B.FilterCoefficient;

  // Saturate: '<S46>/Saturation'
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

  // End of Saturate: '<S46>/Saturation'

  // Sum: '<S1>/Add4' incorporates:
  //   Inport: '<Root>/estim_y'
  //   Inport: '<Root>/set_y'

  positionControl_B.y_error = positionControl_U.set_y -
    positionControl_U.estim_y;

  // Gain: '<S188>/Proportional Gain'
  positionControl_B.ProportionalGain_p = pos_y_P * positionControl_B.y_error;

  // DiscreteIntegrator: '<S183>/Integrator'
  positionControl_B.Integrator_f = positionControl_DW.Integrator_DSTATE_k;

  // Gain: '<S177>/Derivative Gain'
  positionControl_B.DerivativeGain_n = positionControl_P.pos_y_D *
    positionControl_B.y_error;

  // DiscreteIntegrator: '<S178>/Filter'
  positionControl_B.Filter_p = positionControl_DW.Filter_DSTATE_m;

  // Sum: '<S178>/SumD'
  positionControl_B.SumD_k = positionControl_B.DerivativeGain_n -
    positionControl_B.Filter_p;

  // Gain: '<S186>/Filter Coefficient'
  positionControl_B.FilterCoefficient_n = positionControl_P.PIDController4_N *
    positionControl_B.SumD_k;

  // Sum: '<S192>/Sum'
  positionControl_B.Sum_k = (positionControl_B.ProportionalGain_p +
    positionControl_B.Integrator_f) + positionControl_B.FilterCoefficient_n;

  // Saturate: '<S190>/Saturation'
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

  // End of Saturate: '<S190>/Saturation'

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

  // Gain: '<S236>/Proportional Gain'
  positionControl_B.ProportionalGain_m = pos_y_vel_P *
    positionControl_B.vel_error[1];

  // DiscreteIntegrator: '<S231>/Integrator'
  positionControl_B.Integrator_h = positionControl_DW.Integrator_DSTATE_f;

  // Gain: '<S225>/Derivative Gain'
  positionControl_B.DerivativeGain_c = pos_y_vel_D *
    positionControl_B.vel_error[1];

  // DiscreteIntegrator: '<S226>/Filter'
  positionControl_B.Filter_g = positionControl_DW.Filter_DSTATE_j;

  // Sum: '<S226>/SumD'
  positionControl_B.SumD_f = positionControl_B.DerivativeGain_c -
    positionControl_B.Filter_g;

  // Gain: '<S234>/Filter Coefficient'
  positionControl_B.FilterCoefficient_e = positionControl_P.PIDController5_N *
    positionControl_B.SumD_f;

  // Sum: '<S240>/Sum'
  positionControl_B.Sum_m = (positionControl_B.ProportionalGain_m +
    positionControl_B.Integrator_h) + positionControl_B.FilterCoefficient_e;

  // Saturate: '<S238>/Saturation'
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

  // End of Saturate: '<S238>/Saturation'

  // Gain: '<S1>/Gain1'
  positionControl_B.Gain1 = positionControl_P.Gain1_Gain *
    positionControl_B.Saturation_l;

  // Outport: '<Root>/des_roll' incorporates:
  //   DataTypeConversion: '<S1>/Data Type Conversion3'

  positionControl_Y.des_roll = static_cast<real32_T>(positionControl_B.Gain1);

  // Gain: '<S92>/Proportional Gain'
  positionControl_B.ProportionalGain_h = pos_x_vel_P *
    positionControl_B.vel_error[0];

  // DiscreteIntegrator: '<S87>/Integrator'
  positionControl_B.Integrator_c = positionControl_DW.Integrator_DSTATE_m;

  // Gain: '<S81>/Derivative Gain'
  positionControl_B.DerivativeGain_p = pos_x_vel_D *
    positionControl_B.vel_error[0];

  // DiscreteIntegrator: '<S82>/Filter'
  positionControl_B.Filter_i = positionControl_DW.Filter_DSTATE_d;

  // Sum: '<S82>/SumD'
  positionControl_B.SumD_h = positionControl_B.DerivativeGain_p -
    positionControl_B.Filter_i;

  // Gain: '<S90>/Filter Coefficient'
  positionControl_B.FilterCoefficient_f = positionControl_P.PIDController1_N *
    positionControl_B.SumD_h;

  // Sum: '<S96>/Sum'
  positionControl_B.Sum_o = (positionControl_B.ProportionalGain_h +
    positionControl_B.Integrator_c) + positionControl_B.FilterCoefficient_f;

  // Saturate: '<S94>/Saturation'
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

  // End of Saturate: '<S94>/Saturation'

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

  // Gain: '<S1>/Gain2'
  positionControl_B.Gain2 = positionControl_P.Gain2_Gain *
    positionControl_B.alt_error;

  // Gain: '<S140>/Proportional Gain'
  positionControl_B.ProportionalGain_k = pos_z_P * positionControl_B.Gain2;

  // DiscreteIntegrator: '<S135>/Integrator'
  positionControl_B.Integrator_p = positionControl_DW.Integrator_DSTATE_b;

  // Gain: '<S129>/Derivative Gain'
  positionControl_B.DerivativeGain_pu = pos_z_D * positionControl_B.Gain2;

  // DiscreteIntegrator: '<S130>/Filter'
  positionControl_B.Filter_m = positionControl_DW.Filter_DSTATE_e;

  // Sum: '<S130>/SumD'
  positionControl_B.SumD_b = positionControl_B.DerivativeGain_pu -
    positionControl_B.Filter_m;

  // Gain: '<S138>/Filter Coefficient'
  positionControl_B.FilterCoefficient_a = positionControl_P.PIDController3_N *
    positionControl_B.SumD_b;

  // Sum: '<S144>/Sum'
  positionControl_B.Sum_c = (positionControl_B.ProportionalGain_k +
    positionControl_B.Integrator_p) + positionControl_B.FilterCoefficient_a;

  // Saturate: '<S142>/Saturation'
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

  // End of Saturate: '<S142>/Saturation'

  // Outport: '<Root>/des_Thrust' incorporates:
  //   DataTypeConversion: '<S1>/Data Type Conversion4'

  positionControl_Y.des_Thrust = static_cast<real32_T>
    (positionControl_B.Saturation_li);

  // Gain: '<S36>/Integral Gain'
  positionControl_B.IntegralGain = pos_x_I * positionControl_B.x_error;

  // Sum: '<S80>/SumI2'
  positionControl_B.SumI2 = positionControl_B.Saturation_j -
    positionControl_B.Sum_o;

  // Gain: '<S80>/Kb'
  positionControl_B.Kb = positionControl_P.PIDController1_Kb *
    positionControl_B.SumI2;

  // Gain: '<S84>/Integral Gain'
  positionControl_B.IntegralGain_k = pos_x_vel_I * positionControl_B.vel_error[0];

  // Sum: '<S80>/SumI4'
  positionControl_B.SumI4 = positionControl_B.Kb +
    positionControl_B.IntegralGain_k;

  // Gain: '<S180>/Integral Gain'
  positionControl_B.IntegralGain_o = pos_y_I * positionControl_B.y_error;

  // Sum: '<S224>/SumI2'
  positionControl_B.SumI2_n = positionControl_B.Saturation_l -
    positionControl_B.Sum_m;

  // Gain: '<S224>/Kb'
  positionControl_B.Kb_e = positionControl_P.PIDController5_Kb *
    positionControl_B.SumI2_n;

  // Gain: '<S228>/Integral Gain'
  positionControl_B.IntegralGain_b = pos_y_vel_I * positionControl_B.vel_error[1];

  // Sum: '<S224>/SumI4'
  positionControl_B.SumI4_c = positionControl_B.Kb_e +
    positionControl_B.IntegralGain_b;

  // Gain: '<S128>/ZeroGain'
  positionControl_B.ZeroGain = positionControl_P.ZeroGain_Gain *
    positionControl_B.Sum_c;

  // DeadZone: '<S128>/DeadZone'
  if (positionControl_B.Sum_c >
      positionControl_P.PIDController3_UpperSaturationL) {
    positionControl_B.DeadZone = positionControl_B.Sum_c -
      positionControl_P.PIDController3_UpperSaturationL;
  } else if (positionControl_B.Sum_c >=
             positionControl_P.PIDController3_LowerSaturationL) {
    positionControl_B.DeadZone = 0.0;
  } else {
    positionControl_B.DeadZone = positionControl_B.Sum_c -
      positionControl_P.PIDController3_LowerSaturationL;
  }

  // End of DeadZone: '<S128>/DeadZone'

  // RelationalOperator: '<S128>/NotEqual'
  positionControl_B.NotEqual = (positionControl_B.ZeroGain !=
    positionControl_B.DeadZone);

  // Signum: '<S128>/SignPreSat'
  cosOut = positionControl_B.DeadZone;
  if (cosOut < 0.0) {
    positionControl_B.SignPreSat = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreSat = 1.0;
  } else {
    positionControl_B.SignPreSat = cosOut;
  }

  // End of Signum: '<S128>/SignPreSat'

  // DataTypeConversion: '<S128>/DataTypeConv1'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreSat), 256.0);
  positionControl_B.DataTypeConv1 = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>
    (static_cast<uint8_T>(cosOut))));

  // Gain: '<S132>/Integral Gain'
  positionControl_B.IntegralGain_l = pos_z_I * positionControl_B.Gain2;

  // Signum: '<S128>/SignPreIntegrator'
  cosOut = positionControl_B.IntegralGain_l;
  if (cosOut < 0.0) {
    positionControl_B.SignPreIntegrator = -1.0;
  } else if (cosOut > 0.0) {
    positionControl_B.SignPreIntegrator = 1.0;
  } else {
    positionControl_B.SignPreIntegrator = cosOut;
  }

  // End of Signum: '<S128>/SignPreIntegrator'

  // DataTypeConversion: '<S128>/DataTypeConv2'
  cosOut = std::fmod(std::floor(positionControl_B.SignPreIntegrator), 256.0);
  positionControl_B.DataTypeConv2 = static_cast<int8_T>(cosOut < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>(static_cast<
    uint8_T>(-cosOut)))) : static_cast<int32_T>(static_cast<int8_T>(static_cast<
    uint8_T>(cosOut))));

  // RelationalOperator: '<S128>/Equal1'
  positionControl_B.Equal1 = (positionControl_B.DataTypeConv1 ==
    positionControl_B.DataTypeConv2);

  // Logic: '<S128>/AND3'
  positionControl_B.AND3 = (positionControl_B.NotEqual &&
    positionControl_B.Equal1);

  // Switch: '<S128>/Switch' incorporates:
  //   Constant: '<S128>/Constant1'

  if (positionControl_B.AND3) {
    positionControl_B.Switch = positionControl_P.Constant1_Value;
  } else {
    positionControl_B.Switch = positionControl_B.IntegralGain_l;
  }

  // End of Switch: '<S128>/Switch'

  // Update for DiscreteIntegrator: '<S39>/Integrator'
  positionControl_DW.Integrator_DSTATE += positionControl_P.Integrator_gainval *
    positionControl_B.IntegralGain;

  // Update for DiscreteIntegrator: '<S34>/Filter'
  positionControl_DW.Filter_DSTATE += positionControl_P.Filter_gainval *
    positionControl_B.FilterCoefficient;

  // Update for DiscreteIntegrator: '<S183>/Integrator'
  positionControl_DW.Integrator_DSTATE_k +=
    positionControl_P.Integrator_gainval_l * positionControl_B.IntegralGain_o;

  // Update for DiscreteIntegrator: '<S178>/Filter'
  positionControl_DW.Filter_DSTATE_m += positionControl_P.Filter_gainval_l *
    positionControl_B.FilterCoefficient_n;

  // Update for DiscreteIntegrator: '<S231>/Integrator'
  positionControl_DW.Integrator_DSTATE_f +=
    positionControl_P.Integrator_gainval_k * positionControl_B.SumI4_c;

  // Update for DiscreteIntegrator: '<S226>/Filter'
  positionControl_DW.Filter_DSTATE_j += positionControl_P.Filter_gainval_i *
    positionControl_B.FilterCoefficient_e;

  // Update for DiscreteIntegrator: '<S87>/Integrator'
  positionControl_DW.Integrator_DSTATE_m +=
    positionControl_P.Integrator_gainval_lc * positionControl_B.SumI4;

  // Update for DiscreteIntegrator: '<S82>/Filter'
  positionControl_DW.Filter_DSTATE_d += positionControl_P.Filter_gainval_l5 *
    positionControl_B.FilterCoefficient_f;

  // Update for DiscreteIntegrator: '<S135>/Integrator'
  positionControl_DW.Integrator_DSTATE_b +=
    positionControl_P.Integrator_gainval_a * positionControl_B.Switch;

  // Update for DiscreteIntegrator: '<S130>/Filter'
  positionControl_DW.Filter_DSTATE_e += positionControl_P.Filter_gainval_g *
    positionControl_B.FilterCoefficient_a;
}

// Model initialize function
void positionControlModelClass::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S39>/Integrator'
  positionControl_DW.Integrator_DSTATE =
    positionControl_P.PIDController_InitialConditio_c;

  // InitializeConditions for DiscreteIntegrator: '<S34>/Filter'
  positionControl_DW.Filter_DSTATE =
    positionControl_P.PIDController_InitialConditionF;

  // InitializeConditions for DiscreteIntegrator: '<S183>/Integrator'
  positionControl_DW.Integrator_DSTATE_k =
    positionControl_P.PIDController4_InitialConditi_i;

  // InitializeConditions for DiscreteIntegrator: '<S178>/Filter'
  positionControl_DW.Filter_DSTATE_m =
    positionControl_P.PIDController4_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S231>/Integrator'
  positionControl_DW.Integrator_DSTATE_f =
    positionControl_P.PIDController5_InitialConditi_c;

  // InitializeConditions for DiscreteIntegrator: '<S226>/Filter'
  positionControl_DW.Filter_DSTATE_j =
    positionControl_P.PIDController5_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S87>/Integrator'
  positionControl_DW.Integrator_DSTATE_m =
    positionControl_P.PIDController1_InitialConditi_a;

  // InitializeConditions for DiscreteIntegrator: '<S82>/Filter'
  positionControl_DW.Filter_DSTATE_d =
    positionControl_P.PIDController1_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S135>/Integrator'
  positionControl_DW.Integrator_DSTATE_b =
    positionControl_P.PIDController3_InitialConditi_d;

  // InitializeConditions for DiscreteIntegrator: '<S130>/Filter'
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
