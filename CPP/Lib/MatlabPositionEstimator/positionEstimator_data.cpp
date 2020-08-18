//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionEstimator_data.cpp
//
// Code generated for Simulink model 'positionEstimator'.
//
// Model version                  : 1.21
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Mon Aug 17 12:21:06 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include <MatlabPositionEstimator/positionEstimator.h>

// Block parameters (default storage)
positionEstimatorModelClass::P positionEstimatorModelClass::rtP = {
  // Mask Parameter: CompareToConstant_const
  //  Referenced by: '<S35>/Constant'

  180.0,

  // Mask Parameter: CompareToConstant_const_d
  //  Referenced by: '<S33>/Constant'

  90.0,

  // Mask Parameter: CompareToConstant_const_j
  //  Referenced by: '<S36>/Constant'

  180.0,

  // Mask Parameter: CompareToConstant_const_n
  //  Referenced by: '<S29>/Constant'

  180.0,

  // Mask Parameter: CompareToConstant_const_e
  //  Referenced by: '<S27>/Constant'

  90.0,

  // Mask Parameter: CompareToConstant_const_ei
  //  Referenced by: '<S30>/Constant'

  180.0,

  // Expression: 0
  //  Referenced by: '<S21>/Constant1'

  0.0,

  // Expression: 180
  //  Referenced by: '<S21>/Constant'

  180.0,

  // Expression: -90
  //  Referenced by: '<S25>/Bias'

  -90.0,

  // Expression: -1
  //  Referenced by: '<S25>/Gain'

  -1.0,

  // Expression: +90
  //  Referenced by: '<S25>/Bias1'

  90.0,

  // Expression: 360
  //  Referenced by: '<S28>/Constant2'

  360.0,

  // Expression: 180
  //  Referenced by: '<S28>/Bias'

  180.0,

  // Expression: -180
  //  Referenced by: '<S28>/Bias1'

  -180.0,

  // Expression: 360
  //  Referenced by: '<S26>/Constant2'

  360.0,

  // Expression: 180
  //  Referenced by: '<S26>/Bias'

  180.0,

  // Expression: -180
  //  Referenced by: '<S26>/Bias1'

  -180.0,

  // Expression: 0
  //  Referenced by: '<S22>/Constant1'

  0.0,

  // Expression: 180
  //  Referenced by: '<S22>/Constant'

  180.0,

  // Expression: -90
  //  Referenced by: '<S31>/Bias'

  -90.0,

  // Expression: -1
  //  Referenced by: '<S31>/Gain'

  -1.0,

  // Expression: +90
  //  Referenced by: '<S31>/Bias1'

  90.0,

  // Expression: 360
  //  Referenced by: '<S34>/Constant2'

  360.0,

  // Expression: 180
  //  Referenced by: '<S34>/Bias'

  180.0,

  // Expression: -180
  //  Referenced by: '<S34>/Bias1'

  -180.0,

  // Expression: 360
  //  Referenced by: '<S32>/Constant2'

  360.0,

  // Expression: 180
  //  Referenced by: '<S32>/Bias'

  180.0,

  // Expression: -180
  //  Referenced by: '<S32>/Bias1'

  -180.0,

  // Expression: 1
  //  Referenced by: '<S38>/Constant2'

  1.0,

  // Expression: R
  //  Referenced by: '<S38>/Constant1'

  6.378137E+6,

  // Expression: 1
  //  Referenced by: '<S40>/Constant'

  1.0,

  // Expression: 1
  //  Referenced by: '<S42>/Constant'

  1.0,

  // Expression: F
  //  Referenced by: '<S41>/Constant'

  0.0033528106647474805,

  // Expression: 1
  //  Referenced by: '<S41>/f'

  1.0,

  // Expression: 1
  //  Referenced by: '<S38>/Constant'

  1.0,

  // Expression: 0
  //  Referenced by: '<S3>/flat-x_from_N'

  0.0,

  // Expression: 1
  //  Referenced by: '<S38>/Constant3'

  1.0,

  // Expression: p.R{2}
  //  Referenced by: '<S2>/R2'

  { 100.0, 0.0, 0.0, 0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 25.0, 0.0, 0.0, 0.0,
    0.0, 25.0 },

  // Expression: 1
  //  Referenced by: '<S2>/MeasurementFcn2Inputs'

  1.0,

  // Expression: p.R{1}
  //  Referenced by: '<S2>/R1'

  { 100.0, 0.0, 0.0, 100.0 },

  // Expression: 0
  //  Referenced by: '<S2>/MeasurementFcn1Inputs'

  0.0,

  // Expression: -1
  //  Referenced by: '<Root>/NED_convert'

  -1.0,

  // Expression: p.R{3}
  //  Referenced by: '<S1>/R3'

  0.25,

  // Expression: 1
  //  Referenced by: '<S1>/MeasurementFcn3Inputs'

  1.0,

  // Expression: p.R{2}
  //  Referenced by: '<S1>/R2'

  100.0,

  // Expression: 1
  //  Referenced by: '<S1>/MeasurementFcn2Inputs'

  1.0,

  // Expression: p.R{1}
  //  Referenced by: '<S1>/R1'

  4.0,

  // Expression: 0
  //  Referenced by: '<S1>/MeasurementFcn1Inputs'

  0.0,

  // Expression: p.Q
  //  Referenced by: '<S1>/Q'

  0.2,

  // Expression: 0
  //  Referenced by: '<S1>/StateTransitionFcnInputs'

  0.0,

  // Expression: p.InitialCovariance
  //  Referenced by: '<S1>/DataStoreMemory - P'

  { 0.5, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.5 },

  // Expression: p.InitialState
  //  Referenced by: '<S1>/DataStoreMemory - x'

  { 0.0, 0.0, 0.0 },

  // Expression: p.Q
  //  Referenced by: '<S2>/Q'

  0.2,

  // Expression: 0
  //  Referenced by: '<S2>/StateTransitionFcnInputs'

  0.0,

  // Expression: p.InitialCovariance
  //  Referenced by: '<S2>/DataStoreMemory - P'

  { 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.5 },

  // Expression: p.InitialState
  //  Referenced by: '<S2>/DataStoreMemory - x'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Computed Parameter: yBlockOrdering_Y0
  //  Referenced by: '<S4>/yBlockOrdering'

  0,

  // Computed Parameter: yBlockOrdering_Y0_k
  //  Referenced by: '<S5>/yBlockOrdering'

  0,

  // Computed Parameter: yBlockOrdering_Y0_b
  //  Referenced by: '<S6>/yBlockOrdering'

  0,

  // Computed Parameter: yBlockOrdering_Y0_a
  //  Referenced by: '<S13>/yBlockOrdering'

  0,

  // Computed Parameter: yBlockOrdering_Y0_g
  //  Referenced by: '<S14>/yBlockOrdering'

  0,

  // Expression: true()
  //  Referenced by: '<S2>/BlockOrdering'

  1,

  // Expression: true()
  //  Referenced by: '<S1>/BlockOrdering'

  1
};

//
// File trailer for generated code.
//
// [EOF]
//
