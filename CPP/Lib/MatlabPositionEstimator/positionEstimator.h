//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionEstimator.h
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
#ifndef RTW_HEADER_positionEstimator_h_
#define RTW_HEADER_positionEstimator_h_
#include <stddef.h>
#include <cfloat>
#include <cmath>
#include <math.h>
#include <MatlabPositionEstimator/rtwtypes.h>

// Model Code Variants

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

extern "C" {
  static real_T rtGetNaN(void);
  static real32_T rtGetNaNF(void);
}                                      // extern "C"
  extern "C"
{
  extern real_T rtInf;
  extern real_T rtMinusInf;
  extern real_T rtNaN;
  extern real32_T rtInfF;
  extern real32_T rtMinusInfF;
  extern real32_T rtNaNF;
  static void rt_InitInfAndNaN(size_t realSize);
  static boolean_T rtIsInf(real_T value);
  static boolean_T rtIsInfF(real32_T value);
  static boolean_T rtIsNaN(real_T value);
  static boolean_T rtIsNaNF(real32_T value);
  typedef struct {
    struct {
      uint32_T wordH;
      uint32_T wordL;
    } words;
  } BigEndianIEEEDouble;

  typedef struct {
    struct {
      uint32_T wordL;
      uint32_T wordH;
    } words;
  } LittleEndianIEEEDouble;

  typedef struct {
    union {
      real32_T wordLreal;
      uint32_T wordLuint;
    } wordL;
  } IEEESingle;
}                                      // extern "C"

extern "C" {
  static real_T rtGetInf(void);
  static real32_T rtGetInfF(void);
  static real_T rtGetMinusInf(void);
  static real32_T rtGetMinusInfF(void);
}                                      // extern "C"
  // Class declaration for model positionEstimator
  class positionEstimatorModelClass
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  typedef struct {
    real_T Sum1[2];                    // '<S20>/Sum1'
    real_T UnitConversion[2];          // '<S24>/Unit Conversion'
    real_T DataStoreReadX[6];          // '<S16>/Data Store ReadX'
    real_T xNew[6];                    // '<S16>/Predict'
    real_T P_n[36];                    // '<S16>/Predict'
    real_T DataStoreRead[6];           // '<S15>/Data Store Read'
    real_T DataStoreRead1[36];         // '<S15>/Data Store Read1'
    real_T DataStoreReadX_j[6];        // '<S14>/Data Store ReadX'
    real_T TmpSignalConversionAtSFunctionI[4];// '<S14>/Correct'
    real_T xNew_g[6];                  // '<S14>/Correct'
    real_T P_f[36];                    // '<S14>/Correct'
    real_T DataStoreReadX_p[6];        // '<S13>/Data Store ReadX'
    real_T TmpSignalConversionAtSFunctio_i[2];// '<S13>/Correct'
    real_T xNew_n[6];                  // '<S13>/Correct'
    real_T P_k[36];                    // '<S13>/Correct'
    real_T DataStoreReadX_g[3];        // '<S8>/Data Store ReadX'
    real_T xNew_k[3];                  // '<S8>/Predict'
    real_T P_i[9];                     // '<S8>/Predict'
    real_T DataStoreRead_f[3];         // '<S7>/Data Store Read'
    real_T DataStoreRead1_h[9];        // '<S7>/Data Store Read1'
    real_T DataStoreReadX_i[3];        // '<S6>/Data Store ReadX'
    real_T xNew_p[3];                  // '<S6>/Correct'
    real_T P_a[9];                     // '<S6>/Correct'
    real_T DataStoreReadX_m[3];        // '<S5>/Data Store ReadX'
    real_T xNew_g1[3];                 // '<S5>/Correct'
    real_T P_c[9];                     // '<S5>/Correct'
    real_T DataStoreReadX_o[3];        // '<S4>/Data Store ReadX'
    real_T xNew_o[3];                  // '<S4>/Correct'
    real_T P_g[9];                     // '<S4>/Correct'
    real_T P_i_m[9];                   // '<S1>/DataStoreMemory - P'
    real_T x[3];                       // '<S1>/DataStoreMemory - x'
    real_T P_n_c[36];                  // '<S2>/DataStoreMemory - P'
    real_T x_p[6];                     // '<S2>/DataStoreMemory - x'
    real_T Abs;                        // '<S34>/Abs'
    real_T Switch;                     // '<S34>/Switch'
    real_T Abs1;                       // '<S31>/Abs1'
    real_T Switch_b;                   // '<S31>/Switch'
    real_T Switch1;                    // '<S22>/Switch1'
    real_T Sum;                        // '<S22>/Sum'
    real_T Abs_i;                      // '<S32>/Abs'
    real_T Switch_h;                   // '<S32>/Switch'
    real_T Abs_b;                      // '<S28>/Abs'
    real_T Switch_f;                   // '<S28>/Switch'
    real_T Abs1_j;                     // '<S25>/Abs1'
    real_T Switch_j;                   // '<S25>/Switch'
    real_T Switch1_b;                  // '<S21>/Switch1'
    real_T Sum_j;                      // '<S21>/Sum'
    real_T Abs_b0;                     // '<S26>/Abs'
    real_T Switch_m;                   // '<S26>/Switch'
    real_T Sum_a;                      // '<S41>/Sum'
    real_T Product1;                   // '<S42>/Product1'
    real_T Sum1_e;                     // '<S42>/Sum1'
    real_T sqrt_c;                     // '<S42>/sqrt'
    real_T UnitConversion_m;           // '<S39>/Unit Conversion'
    real_T TrigonometricFunction1;     // '<S40>/Trigonometric Function1'
    real_T Product1_n;                 // '<S40>/Product1'
    real_T Sum1_c;                     // '<S40>/Sum1'
    real_T sqrt_d;                     // '<S38>/sqrt'
    real_T Rn;                         // '<S38>/Product1'
    real_T Product2;                   // '<S38>/Product2'
    real_T Sum1_g;                     // '<S38>/Sum1'
    real_T Rm;                         // '<S38>/Product3'
    real_T TrigonometricFunction1_l;   // '<S38>/Trigonometric Function1'
    real_T dNorth;                     // '<S23>/dNorth'
    real_T UnitConversion_p;           // '<S37>/Unit Conversion'
    real_T SinCos_o1;                  // '<S23>/SinCos'
    real_T SinCos_o2;                  // '<S23>/SinCos'
    real_T xcos;                       // '<S23>/x*cos'
    real_T TrigonometricFunction;      // '<S38>/Trigonometric Function'
    real_T Product4;                   // '<S38>/Product4'
    real_T TrigonometricFunction2;     // '<S38>/Trigonometric Function2'
    real_T dEast;                      // '<S23>/dEast'
    real_T ysin;                       // '<S23>/y*sin'
    real_T Px;                         // '<S23>/Sum2'
    real_T xsin;                       // '<S23>/x*sin'
    real_T ycos;                       // '<S23>/y*cos'
    real_T Py;                         // '<S23>/Sum3'
    real_T NED_convert;                // '<Root>/NED_convert'
    real_T alt;                        // '<S20>/Sum'
    real_T Pz;                         // '<S20>/Ze2height'
    real_T Bias;                       // '<S32>/Bias'
    real_T MathFunction1;              // '<S32>/Math Function1'
    real_T Bias1;                      // '<S32>/Bias1'
    real_T Bias_m;                     // '<S34>/Bias'
    real_T MathFunction1_i;            // '<S34>/Math Function1'
    real_T Bias1_k;                    // '<S34>/Bias1'
    real_T Bias_d;                     // '<S31>/Bias'
    real_T Gain;                       // '<S31>/Gain'
    real_T Bias1_o;                    // '<S31>/Bias1'
    real_T Sign1;                      // '<S31>/Sign1'
    real_T Divide1;                    // '<S31>/Divide1'
    real_T Bias_j;                     // '<S26>/Bias'
    real_T MathFunction1_h;            // '<S26>/Math Function1'
    real_T Bias1_p;                    // '<S26>/Bias1'
    real_T Bias_e;                     // '<S28>/Bias'
    real_T MathFunction1_o;            // '<S28>/Math Function1'
    real_T Bias1_oh;                   // '<S28>/Bias1'
    real_T Bias_mj;                    // '<S25>/Bias'
    real_T Gain_c;                     // '<S25>/Gain'
    real_T Bias1_n;                    // '<S25>/Bias1'
    real_T Sign1_g;                    // '<S25>/Sign1'
    real_T Divide1_h;                  // '<S25>/Divide1'
    boolean_T Compare;                 // '<S35>/Compare'
    boolean_T Compare_c;               // '<S33>/Compare'
    boolean_T Compare_d;               // '<S36>/Compare'
    boolean_T Compare_ds;              // '<S29>/Compare'
    boolean_T Compare_m;               // '<S27>/Compare'
    boolean_T Compare_k;               // '<S30>/Compare'
    boolean_T DataTypeConversion_Enable1;// '<S2>/DataTypeConversion_Enable1'
    boolean_T LogicalOperator;         // '<Root>/Logical Operator'
    boolean_T DataTypeConversion_Enable1_a;// '<S1>/DataTypeConversion_Enable1'
    boolean_T DataTypeConversion_Enable3;// '<S1>/DataTypeConversion_Enable3'
    boolean_T uBlockOrdering;          // '<S15>/uBlockOrdering'
    boolean_T blockOrdering;           // '<S14>/Correct'
    boolean_T blockOrdering_f;         // '<S13>/Correct'
    boolean_T uBlockOrdering_b;        // '<S7>/uBlockOrdering'
    boolean_T blockOrdering_p;         // '<S6>/Correct'
    boolean_T blockOrdering_n;         // '<S5>/Correct'
    boolean_T blockOrdering_k;         // '<S4>/Correct'
  } DW;

  // External inputs (root inport signals with default storage)
  typedef struct {
    real_T AhrsFlag;                   // '<Root>/AhrsFlag'
    real_T ax;                         // '<Root>/ax'
    real_T ay;                         // '<Root>/ay'
    real_T az;                         // '<Root>/az'
    real_T GpsFlag;                    // '<Root>/GpsFlag'
    real_T lat;                        // '<Root>/lat'
    real_T lon;                        // '<Root>/lon'
    real_T alt;                        // '<Root>/alt'
    real_T vx;                         // '<Root>/vx'
    real_T vy;                         // '<Root>/vy'
    real_T BaroFlag;                   // '<Root>/BaroFlag'
    real_T baroZ;                      // '<Root>/baroZ'
    real_T HOME_lla[3];                // '<Root>/HOME_lla'
    real_T GPS_switch;                 // '<Root>/GPS_switch'
  } ExtU;

  // External outputs (root outports fed by signals with default storage)
  typedef struct {
    real_T estiX;                      // '<Root>/estiX'
    real_T estiY;                      // '<Root>/estiY'
    real_T estiZ;                      // '<Root>/estiZ'
    real_T estiVX;                     // '<Root>/estiVX'
    real_T estiVY;                     // '<Root>/estiVY'
    real_T estiVZ;                     // '<Root>/estiVZ'
    real_T estiAX;                     // '<Root>/estiAX'
    real_T estiAY;                     // '<Root>/estiAY'
    real_T estiAZ;                     // '<Root>/estiAZ'
  } ExtY;

  // Parameters (default storage)
  struct P {
    real_T CompareToConstant_const;   // Mask Parameter: CompareToConstant_const
                                         //  Referenced by: '<S35>/Constant'

    real_T CompareToConstant_const_d;
                                    // Mask Parameter: CompareToConstant_const_d
                                       //  Referenced by: '<S33>/Constant'

    real_T CompareToConstant_const_j;
                                    // Mask Parameter: CompareToConstant_const_j
                                       //  Referenced by: '<S36>/Constant'

    real_T CompareToConstant_const_n;
                                    // Mask Parameter: CompareToConstant_const_n
                                       //  Referenced by: '<S29>/Constant'

    real_T CompareToConstant_const_e;
                                    // Mask Parameter: CompareToConstant_const_e
                                       //  Referenced by: '<S27>/Constant'

    real_T CompareToConstant_const_ei;
                                   // Mask Parameter: CompareToConstant_const_ei
                                      //  Referenced by: '<S30>/Constant'

    real_T Constant1_Value;            // Expression: 0
                                          //  Referenced by: '<S21>/Constant1'

    real_T Constant_Value;             // Expression: 180
                                          //  Referenced by: '<S21>/Constant'

    real_T Bias_Bias;                  // Expression: -90
                                          //  Referenced by: '<S25>/Bias'

    real_T Gain_Gain;                  // Expression: -1
                                          //  Referenced by: '<S25>/Gain'

    real_T Bias1_Bias;                 // Expression: +90
                                          //  Referenced by: '<S25>/Bias1'

    real_T Constant2_Value;            // Expression: 360
                                          //  Referenced by: '<S28>/Constant2'

    real_T Bias_Bias_b;                // Expression: 180
                                          //  Referenced by: '<S28>/Bias'

    real_T Bias1_Bias_p;               // Expression: -180
                                          //  Referenced by: '<S28>/Bias1'

    real_T Constant2_Value_g;          // Expression: 360
                                          //  Referenced by: '<S26>/Constant2'

    real_T Bias_Bias_a;                // Expression: 180
                                          //  Referenced by: '<S26>/Bias'

    real_T Bias1_Bias_l;               // Expression: -180
                                          //  Referenced by: '<S26>/Bias1'

    real_T Constant1_Value_f;          // Expression: 0
                                          //  Referenced by: '<S22>/Constant1'

    real_T Constant_Value_m;           // Expression: 180
                                          //  Referenced by: '<S22>/Constant'

    real_T Bias_Bias_e;                // Expression: -90
                                          //  Referenced by: '<S31>/Bias'

    real_T Gain_Gain_n;                // Expression: -1
                                          //  Referenced by: '<S31>/Gain'

    real_T Bias1_Bias_c;               // Expression: +90
                                          //  Referenced by: '<S31>/Bias1'

    real_T Constant2_Value_j;          // Expression: 360
                                          //  Referenced by: '<S34>/Constant2'

    real_T Bias_Bias_al;               // Expression: 180
                                          //  Referenced by: '<S34>/Bias'

    real_T Bias1_Bias_k;               // Expression: -180
                                          //  Referenced by: '<S34>/Bias1'

    real_T Constant2_Value_k;          // Expression: 360
                                          //  Referenced by: '<S32>/Constant2'

    real_T Bias_Bias_d;                // Expression: 180
                                          //  Referenced by: '<S32>/Bias'

    real_T Bias1_Bias_cz;              // Expression: -180
                                          //  Referenced by: '<S32>/Bias1'

    real_T Constant2_Value_h;          // Expression: 1
                                          //  Referenced by: '<S38>/Constant2'

    real_T Constant1_Value_d;          // Expression: R
                                          //  Referenced by: '<S38>/Constant1'

    real_T Constant_Value_f;           // Expression: 1
                                          //  Referenced by: '<S40>/Constant'

    real_T Constant_Value_a;           // Expression: 1
                                          //  Referenced by: '<S42>/Constant'

    real_T Constant_Value_c;           // Expression: F
                                          //  Referenced by: '<S41>/Constant'

    real_T f_Value;                    // Expression: 1
                                          //  Referenced by: '<S41>/f'

    real_T Constant_Value_ch;          // Expression: 1
                                          //  Referenced by: '<S38>/Constant'

    real_T flatx_from_N_Value;         // Expression: 0
                                          //  Referenced by: '<S3>/flat-x_from_N'

    real_T Constant3_Value;            // Expression: 1
                                          //  Referenced by: '<S38>/Constant3'

    real_T R2_Value[16];               // Expression: p.R{2}
                                          //  Referenced by: '<S2>/R2'

    real_T MeasurementFcn2Inputs_Value;// Expression: 1
                                          //  Referenced by: '<S2>/MeasurementFcn2Inputs'

    real_T R1_Value[4];                // Expression: p.R{1}
                                          //  Referenced by: '<S2>/R1'

    real_T MeasurementFcn1Inputs_Value;// Expression: 0
                                          //  Referenced by: '<S2>/MeasurementFcn1Inputs'

    real_T NED_convert_Gain;           // Expression: -1
                                          //  Referenced by: '<Root>/NED_convert'

    real_T R3_Value;                   // Expression: p.R{3}
                                          //  Referenced by: '<S1>/R3'

    real_T MeasurementFcn3Inputs_Value;// Expression: 1
                                          //  Referenced by: '<S1>/MeasurementFcn3Inputs'

    real_T R2_Value_g;                 // Expression: p.R{2}
                                          //  Referenced by: '<S1>/R2'

    real_T MeasurementFcn2Inputs_Value_k;// Expression: 1
                                            //  Referenced by: '<S1>/MeasurementFcn2Inputs'

    real_T R1_Value_j;                 // Expression: p.R{1}
                                          //  Referenced by: '<S1>/R1'

    real_T MeasurementFcn1Inputs_Value_e;// Expression: 0
                                            //  Referenced by: '<S1>/MeasurementFcn1Inputs'

    real_T Q_Value;                    // Expression: p.Q
                                          //  Referenced by: '<S1>/Q'

    real_T StateTransitionFcnInputs_Value;// Expression: 0
                                             //  Referenced by: '<S1>/StateTransitionFcnInputs'

    real_T DataStoreMemoryP_InitialValue[9];// Expression: p.InitialCovariance
                                               //  Referenced by: '<S1>/DataStoreMemory - P'

    real_T DataStoreMemoryx_InitialValue[3];// Expression: p.InitialState
                                               //  Referenced by: '<S1>/DataStoreMemory - x'

    real_T Q_Value_c;                  // Expression: p.Q
                                          //  Referenced by: '<S2>/Q'

    real_T StateTransitionFcnInputs_Valu_k;// Expression: 0
                                              //  Referenced by: '<S2>/StateTransitionFcnInputs'

    real_T DataStoreMemoryP_InitialValue_m[36];// Expression: p.InitialCovariance
                                                  //  Referenced by: '<S2>/DataStoreMemory - P'

    real_T DataStoreMemoryx_InitialValue_j[6];// Expression: p.InitialState
                                                 //  Referenced by: '<S2>/DataStoreMemory - x'

    boolean_T yBlockOrdering_Y0;       // Computed Parameter: yBlockOrdering_Y0
                                          //  Referenced by: '<S4>/yBlockOrdering'

    boolean_T yBlockOrdering_Y0_k;    // Computed Parameter: yBlockOrdering_Y0_k
                                         //  Referenced by: '<S5>/yBlockOrdering'

    boolean_T yBlockOrdering_Y0_b;    // Computed Parameter: yBlockOrdering_Y0_b
                                         //  Referenced by: '<S6>/yBlockOrdering'

    boolean_T yBlockOrdering_Y0_a;    // Computed Parameter: yBlockOrdering_Y0_a
                                         //  Referenced by: '<S13>/yBlockOrdering'

    boolean_T yBlockOrdering_Y0_g;    // Computed Parameter: yBlockOrdering_Y0_g
                                         //  Referenced by: '<S14>/yBlockOrdering'

    boolean_T BlockOrdering_Value;     // Expression: true()
                                          //  Referenced by: '<S2>/BlockOrdering'

    boolean_T BlockOrdering_Value_b;   // Expression: true()
                                          //  Referenced by: '<S1>/BlockOrdering'

  };

  // Real-time Model Data Structure
  struct RT_MODEL {
    const char_T * volatile errorStatus;
  };

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  positionEstimatorModelClass();

  // Destructor
  ~positionEstimatorModelClass();

  // Root-level structure-based inputs set method

  // Root inports set method
  void setExternalInputs(const ExtU* pExtU)
  {
    rtU = *pExtU;
  }

  // Root-level structure-based outputs get method

  // Root outports get method
  const positionEstimatorModelClass::ExtY & getExternalOutputs() const
  {
    return rtY;
  }

  // Real-Time Model get method
  positionEstimatorModelClass::RT_MODEL * getRTM();

  // private data and function members
 private:
  // Tunable parameters
  static P rtP;

  // Block signals and states
  DW rtDW;

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // Real-Time Model
  RT_MODEL rtM;

  // private member function(s) for subsystem '<Root>'
  void EKFCorrector_correctStateAndCov(real_T x[6], real_T P_0[36], const real_T
    y[4], const real_T Pxy[24], const real_T Pyy[16], const real_T dHdx[24]);
}

;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S4>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S5>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S6>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S8>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S1>/checkMeasurementFcn1Signals' : Unused code path elimination
//  Block '<S1>/checkMeasurementFcn2Signals' : Unused code path elimination
//  Block '<S1>/checkMeasurementFcn3Signals' : Unused code path elimination
//  Block '<S1>/checkStateTransitionFcnSignals' : Unused code path elimination
//  Block '<S13>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S14>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S16>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S2>/checkMeasurementFcn1Signals' : Unused code path elimination
//  Block '<S2>/checkMeasurementFcn2Signals' : Unused code path elimination
//  Block '<S2>/checkStateTransitionFcnSignals' : Unused code path elimination
//  Block '<S1>/DataTypeConversion_Enable2' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_Q' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_R1' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_R2' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_R3' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_uMeas1' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_uMeas2' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_uMeas3' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_uState' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_y1' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_y2' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_y3' : Eliminate redundant data type conversion
//  Block '<S2>/DataTypeConversion_Enable2' : Eliminate redundant data type conversion
//  Block '<S2>/DataTypeConversion_Q' : Eliminate redundant data type conversion
//  Block '<S2>/DataTypeConversion_R1' : Eliminate redundant data type conversion
//  Block '<S2>/DataTypeConversion_R2' : Eliminate redundant data type conversion
//  Block '<S2>/DataTypeConversion_uMeas1' : Eliminate redundant data type conversion
//  Block '<S2>/DataTypeConversion_uMeas2' : Eliminate redundant data type conversion
//  Block '<S2>/DataTypeConversion_uState' : Eliminate redundant data type conversion
//  Block '<S2>/DataTypeConversion_y1' : Eliminate redundant data type conversion
//  Block '<S2>/DataTypeConversion_y2' : Eliminate redundant data type conversion


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'positionEstimator'
//  '<S1>'   : 'positionEstimator/EKF_Altitude'
//  '<S2>'   : 'positionEstimator/EKF_Position'
//  '<S3>'   : 'positionEstimator/from_home'
//  '<S4>'   : 'positionEstimator/EKF_Altitude/Correct1'
//  '<S5>'   : 'positionEstimator/EKF_Altitude/Correct2'
//  '<S6>'   : 'positionEstimator/EKF_Altitude/Correct3'
//  '<S7>'   : 'positionEstimator/EKF_Altitude/Output'
//  '<S8>'   : 'positionEstimator/EKF_Altitude/Predict'
//  '<S9>'   : 'positionEstimator/EKF_Altitude/Correct1/Correct'
//  '<S10>'  : 'positionEstimator/EKF_Altitude/Correct2/Correct'
//  '<S11>'  : 'positionEstimator/EKF_Altitude/Correct3/Correct'
//  '<S12>'  : 'positionEstimator/EKF_Altitude/Predict/Predict'
//  '<S13>'  : 'positionEstimator/EKF_Position/Correct1'
//  '<S14>'  : 'positionEstimator/EKF_Position/Correct2'
//  '<S15>'  : 'positionEstimator/EKF_Position/Output'
//  '<S16>'  : 'positionEstimator/EKF_Position/Predict'
//  '<S17>'  : 'positionEstimator/EKF_Position/Correct1/Correct'
//  '<S18>'  : 'positionEstimator/EKF_Position/Correct2/Correct'
//  '<S19>'  : 'positionEstimator/EKF_Position/Predict/Predict'
//  '<S20>'  : 'positionEstimator/from_home/LLA to Flat Earth'
//  '<S21>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap'
//  '<S22>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0'
//  '<S23>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem'
//  '<S24>'  : 'positionEstimator/from_home/LLA to Flat Earth/pos_rad'
//  '<S25>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Latitude Wrap 90'
//  '<S26>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Wrap Longitude'
//  '<S27>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Latitude Wrap 90/Compare To Constant'
//  '<S28>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Latitude Wrap 90/Wrap Angle 180'
//  '<S29>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Latitude Wrap 90/Wrap Angle 180/Compare To Constant'
//  '<S30>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Wrap Longitude/Compare To Constant'
//  '<S31>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Latitude Wrap 90'
//  '<S32>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Wrap Longitude'
//  '<S33>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Latitude Wrap 90/Compare To Constant'
//  '<S34>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Latitude Wrap 90/Wrap Angle 180'
//  '<S35>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Latitude Wrap 90/Wrap Angle 180/Compare To Constant'
//  '<S36>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Wrap Longitude/Compare To Constant'
//  '<S37>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Angle Conversion2'
//  '<S38>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Find Radian//Distance'
//  '<S39>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Find Radian//Distance/Angle Conversion2'
//  '<S40>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Find Radian//Distance/denom'
//  '<S41>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Find Radian//Distance/e'
//  '<S42>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Find Radian//Distance/e^4'

#endif                                 // RTW_HEADER_positionEstimator_h_

//
// File trailer for generated code.
//
// [EOF]
//
