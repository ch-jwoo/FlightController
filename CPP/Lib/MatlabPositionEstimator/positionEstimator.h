//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionEstimator.h
//
// Code generated for Simulink model 'positionEstimator'.
//
// Model version                  : 1.34
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Mon Sep 28 23:39:25 2020
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
#include "rtwtypes.h"

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
  // Block signals and states (default storage) for system '<S1>/Correct2'
  typedef struct {
    real_T DataStoreReadX[3];          // '<S6>/Data Store ReadX'
    real_T DataStoreReadP[9];          // '<S6>/Data Store ReadP'
    real_T xNew[3];                    // '<S6>/Correct'
    real_T P_c[9];                     // '<S6>/Correct'
    boolean_T blockOrdering;           // '<S6>/Correct'
  } DW_Correct2;

  // Block signals and states (default storage) for system '<Root>'
  typedef struct {
    DW_Correct2 Correct4;              // '<S1>/Correct4'
    DW_Correct2 Correct2_a;            // '<S1>/Correct2'
    real_T Sum1[2];                    // '<S46>/Sum1'
    real_T UnitConversion[2];          // '<S50>/Unit Conversion'
    real_T UnitConversion_h[2];        // '<S27>/Unit Conversion'
    real_T Sum_o[2];                   // '<S23>/Sum'
    real_T DataStoreReadX[6];          // '<S19>/Data Store ReadX'
    real_T xNew[6];                    // '<S19>/Predict'
    real_T P_a[36];                    // '<S19>/Predict'
    real_T DataStoreRead[6];           // '<S18>/Data Store Read'
    real_T DataStoreRead1[36];         // '<S18>/Data Store Read1'
    real_T DataStoreReadX_a[6];        // '<S17>/Data Store ReadX'
    real_T TmpSignalConversionAtSFunctionI[4];// '<S17>/Correct'
    real_T xNew_j[6];                  // '<S17>/Correct'
    real_T P_f[36];                    // '<S17>/Correct'
    real_T DataStoreReadX_e[6];        // '<S16>/Data Store ReadX'
    real_T TmpSignalConversionAtSFunctio_c[2];// '<S16>/Correct'
    real_T xNew_a[6];                  // '<S16>/Correct'
    real_T P_p[36];                    // '<S16>/Correct'
    real_T DataStoreReadX_g[3];        // '<S10>/Data Store ReadX'
    real_T xNew_k[3];                  // '<S10>/Predict'
    real_T P_i[9];                     // '<S10>/Predict'
    real_T DataStoreRead_f[3];         // '<S9>/Data Store Read'
    real_T DataStoreRead1_h[9];        // '<S9>/Data Store Read1'
    real_T DataStoreReadX_i[3];        // '<S7>/Data Store ReadX'
    real_T xNew_p[3];                  // '<S7>/Correct'
    real_T P_ak[9];                    // '<S7>/Correct'
    real_T DataStoreReadX_o[3];        // '<S5>/Data Store ReadX'
    real_T xNew_o[3];                  // '<S5>/Correct'
    real_T P_g[9];                     // '<S5>/Correct'
    real_T P_i_m[9];                   // '<S1>/DataStoreMemory - P'
    real_T x[3];                       // '<S1>/DataStoreMemory - x'
    real_T P_k[36];                    // '<S2>/DataStoreMemory - P'
    real_T x_o[6];                     // '<S2>/DataStoreMemory - x'
    real_T Abs;                        // '<S60>/Abs'
    real_T Switch;                     // '<S60>/Switch'
    real_T Abs1;                       // '<S57>/Abs1'
    real_T Switch_b;                   // '<S57>/Switch'
    real_T Switch1;                    // '<S48>/Switch1'
    real_T Sum;                        // '<S48>/Sum'
    real_T Abs_i;                      // '<S58>/Abs'
    real_T Switch_h;                   // '<S58>/Switch'
    real_T Abs_b;                      // '<S54>/Abs'
    real_T Switch_f;                   // '<S54>/Switch'
    real_T Abs1_j;                     // '<S51>/Abs1'
    real_T Switch_j;                   // '<S51>/Switch'
    real_T Switch1_b;                  // '<S47>/Switch1'
    real_T Sum_j;                      // '<S47>/Sum'
    real_T Abs_b0;                     // '<S52>/Abs'
    real_T Switch_m;                   // '<S52>/Switch'
    real_T Sum_a;                      // '<S67>/Sum'
    real_T Product1;                   // '<S68>/Product1'
    real_T Sum1_e;                     // '<S68>/Sum1'
    real_T sqrt_c;                     // '<S68>/sqrt'
    real_T UnitConversion_m;           // '<S65>/Unit Conversion'
    real_T TrigonometricFunction1;     // '<S66>/Trigonometric Function1'
    real_T Product1_n;                 // '<S66>/Product1'
    real_T Sum1_c;                     // '<S66>/Sum1'
    real_T sqrt_d;                     // '<S64>/sqrt'
    real_T Rn;                         // '<S64>/Product1'
    real_T Product2;                   // '<S64>/Product2'
    real_T Sum1_g;                     // '<S64>/Sum1'
    real_T Rm;                         // '<S64>/Product3'
    real_T TrigonometricFunction1_l;   // '<S64>/Trigonometric Function1'
    real_T dNorth;                     // '<S49>/dNorth'
    real_T UnitConversion_p;           // '<S63>/Unit Conversion'
    real_T SinCos_o1;                  // '<S49>/SinCos'
    real_T SinCos_o2;                  // '<S49>/SinCos'
    real_T xcos;                       // '<S49>/x*cos'
    real_T TrigonometricFunction;      // '<S64>/Trigonometric Function'
    real_T Product4;                   // '<S64>/Product4'
    real_T TrigonometricFunction2;     // '<S64>/Trigonometric Function2'
    real_T dEast;                      // '<S49>/dEast'
    real_T ysin;                       // '<S49>/y*sin'
    real_T xsin;                       // '<S49>/x*sin'
    real_T ycos;                       // '<S49>/y*cos'
    real_T NED_convert1;               // '<Root>/NED_convert1'
    real_T NED_convert;                // '<Root>/NED_convert'
    real_T alt;                        // '<S46>/Sum'
    real_T Pz;                         // '<S46>/Ze2height'
    real_T UnitConversion_me;          // '<S41>/Unit Conversion'
    real_T SinCos_o1_f;                // '<S26>/SinCos'
    real_T SinCos_o2_e;                // '<S26>/SinCos'
    real_T xcos_p;                     // '<S26>/x*cos'
    real_T ysin_m;                     // '<S26>/y*sin'
    real_T Sum_g;                      // '<S26>/Sum'
    real_T Sum_ah;                     // '<S44>/Sum'
    real_T Product1_f;                 // '<S45>/Product1'
    real_T Sum1_p;                     // '<S45>/Sum1'
    real_T sqrt_p;                     // '<S45>/sqrt'
    real_T Abs_o;                      // '<S37>/Abs'
    real_T Switch_e;                   // '<S37>/Switch'
    real_T Abs1_c;                     // '<S34>/Abs1'
    real_T Switch_i;                   // '<S34>/Switch'
    real_T UnitConversion_a;           // '<S42>/Unit Conversion'
    real_T TrigonometricFunction1_b;   // '<S43>/Trigonometric Function1'
    real_T Product1_k;                 // '<S43>/Product1'
    real_T Sum1_l;                     // '<S43>/Sum1'
    real_T sqrt_f;                     // '<S40>/sqrt'
    real_T Rn_n;                       // '<S40>/Product1'
    real_T Product2_c;                 // '<S40>/Product2'
    real_T Sum1_l4;                    // '<S40>/Sum1'
    real_T Rm_o;                       // '<S40>/Product3'
    real_T TrigonometricFunction1_p;   // '<S40>/Trigonometric Function1'
    real_T radlat;                     // '<S26>/rad lat'
    real_T TrigonometricFunction_f;    // '<S40>/Trigonometric Function'
    real_T Product4_n;                 // '<S40>/Product4'
    real_T TrigonometricFunction2_d;   // '<S40>/Trigonometric Function2'
    real_T xsin_n;                     // '<S26>/x*sin'
    real_T ycos_k;                     // '<S26>/y*cos'
    real_T Sum1_a;                     // '<S26>/Sum1'
    real_T radlong;                    // '<S26>/rad long '
    real_T Switch1_l;                  // '<S25>/Switch1'
    real_T Sum_c;                      // '<S25>/Sum'
    real_T Abs_c;                      // '<S35>/Abs'
    real_T Switch_ed;                  // '<S35>/Switch'
    real_T Abs_d;                      // '<S31>/Abs'
    real_T Switch_js;                  // '<S31>/Switch'
    real_T Abs1_n;                     // '<S28>/Abs1'
    real_T Switch_l;                   // '<S28>/Switch'
    real_T Switch1_m;                  // '<S24>/Switch1'
    real_T Sum_ad;                     // '<S24>/Sum'
    real_T Abs_b4;                     // '<S29>/Abs'
    real_T Switch_g;                   // '<S29>/Switch'
    real_T alt_o;                      // '<S23>/Ze2height'
    real_T Bias;                       // '<S58>/Bias'
    real_T MathFunction1;              // '<S58>/Math Function1'
    real_T Bias1;                      // '<S58>/Bias1'
    real_T Bias_m;                     // '<S60>/Bias'
    real_T MathFunction1_i;            // '<S60>/Math Function1'
    real_T Bias1_k;                    // '<S60>/Bias1'
    real_T Bias_d;                     // '<S57>/Bias'
    real_T Gain;                       // '<S57>/Gain'
    real_T Bias1_o;                    // '<S57>/Bias1'
    real_T Sign1;                      // '<S57>/Sign1'
    real_T Divide1;                    // '<S57>/Divide1'
    real_T Bias_j;                     // '<S52>/Bias'
    real_T MathFunction1_h;            // '<S52>/Math Function1'
    real_T Bias1_p;                    // '<S52>/Bias1'
    real_T Bias_e;                     // '<S54>/Bias'
    real_T MathFunction1_o;            // '<S54>/Math Function1'
    real_T Bias1_oh;                   // '<S54>/Bias1'
    real_T Bias_mj;                    // '<S51>/Bias'
    real_T Gain_c;                     // '<S51>/Gain'
    real_T Bias1_n;                    // '<S51>/Bias1'
    real_T Sign1_g;                    // '<S51>/Sign1'
    real_T Divide1_h;                  // '<S51>/Divide1'
    real_T Bias_i;                     // '<S35>/Bias'
    real_T MathFunction1_p;            // '<S35>/Math Function1'
    real_T Bias1_ny;                   // '<S35>/Bias1'
    real_T Bias_g;                     // '<S37>/Bias'
    real_T MathFunction1_b;            // '<S37>/Math Function1'
    real_T Bias1_f;                    // '<S37>/Bias1'
    real_T Bias_et;                    // '<S34>/Bias'
    real_T Gain_f;                     // '<S34>/Gain'
    real_T Bias1_d;                    // '<S34>/Bias1'
    real_T Sign1_j;                    // '<S34>/Sign1'
    real_T Divide1_o;                  // '<S34>/Divide1'
    real_T Bias_c;                     // '<S29>/Bias'
    real_T MathFunction1_ha;           // '<S29>/Math Function1'
    real_T Bias1_g;                    // '<S29>/Bias1'
    real_T Bias_f;                     // '<S31>/Bias'
    real_T MathFunction1_l;            // '<S31>/Math Function1'
    real_T Bias1_a;                    // '<S31>/Bias1'
    real_T Bias_fd;                    // '<S28>/Bias'
    real_T Gain_m;                     // '<S28>/Gain'
    real_T Bias1_i;                    // '<S28>/Bias1'
    real_T Sign1_d;                    // '<S28>/Sign1'
    real_T Divide1_og;                 // '<S28>/Divide1'
    boolean_T Compare;                 // '<S61>/Compare'
    boolean_T Compare_c;               // '<S59>/Compare'
    boolean_T Compare_d;               // '<S62>/Compare'
    boolean_T Compare_ds;              // '<S55>/Compare'
    boolean_T Compare_m;               // '<S53>/Compare'
    boolean_T Compare_k;               // '<S56>/Compare'
    boolean_T DataTypeConversion_Enable1;// '<S2>/DataTypeConversion_Enable1'
    boolean_T LogicalOperator;         // '<Root>/Logical Operator'
    boolean_T DataTypeConversion_Enable1_a;// '<S1>/DataTypeConversion_Enable1'
    boolean_T DataTypeConversion_Enable3;// '<S1>/DataTypeConversion_Enable3'
    boolean_T DataTypeConversion_Enable4;// '<S1>/DataTypeConversion_Enable4'
    boolean_T Compare_cm;              // '<S38>/Compare'
    boolean_T Compare_a;               // '<S36>/Compare'
    boolean_T Compare_a0;              // '<S39>/Compare'
    boolean_T Compare_ko;              // '<S32>/Compare'
    boolean_T Compare_j;               // '<S30>/Compare'
    boolean_T Compare_e;               // '<S33>/Compare'
    boolean_T uBlockOrdering;          // '<S18>/uBlockOrdering'
    boolean_T blockOrdering;           // '<S17>/Correct'
    boolean_T blockOrdering_f;         // '<S16>/Correct'
    boolean_T uBlockOrdering_b;        // '<S9>/uBlockOrdering'
    boolean_T blockOrdering_p;         // '<S7>/Correct'
    boolean_T blockOrdering_k;         // '<S5>/Correct'
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
    real_T Lidar_height;               // '<Root>/Lidar_height'
    real_T LidarFlag;                  // '<Root>/LidarFlag'
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
    real_T Estim_LatLon[2];            // '<Root>/Estim_LatLon'
    real_T Estim_Alt;                  // '<Root>/Estim_Alt'
    real_T GPSrawX;                    // '<Root>/GPSrawX'
    real_T GPSrawY;                    // '<Root>/GPSrawY'
    real_T GPSrawVX;                   // '<Root>/GPSrawVX'
    real_T GPSrawVY;                   // '<Root>/GPSrawVY'
  } ExtY;

  // Parameters for system: '<S1>/Correct2'
  struct P_Correct2 {
    boolean_T yBlockOrdering_Y0;       // Computed Parameter: yBlockOrdering_Y0
                                          //  Referenced by: '<S6>/yBlockOrdering'

  };

  // Parameters (default storage)
  struct P {
    real_T CompareToConstant_const;   // Mask Parameter: CompareToConstant_const
                                         //  Referenced by: '<S61>/Constant'

    real_T CompareToConstant_const_d;
                                    // Mask Parameter: CompareToConstant_const_d
                                       //  Referenced by: '<S59>/Constant'

    real_T CompareToConstant_const_j;
                                    // Mask Parameter: CompareToConstant_const_j
                                       //  Referenced by: '<S62>/Constant'

    real_T CompareToConstant_const_n;
                                    // Mask Parameter: CompareToConstant_const_n
                                       //  Referenced by: '<S55>/Constant'

    real_T CompareToConstant_const_e;
                                    // Mask Parameter: CompareToConstant_const_e
                                       //  Referenced by: '<S53>/Constant'

    real_T CompareToConstant_const_ei;
                                   // Mask Parameter: CompareToConstant_const_ei
                                      //  Referenced by: '<S56>/Constant'

    real_T CompareToConstant_const_f;
                                    // Mask Parameter: CompareToConstant_const_f
                                       //  Referenced by: '<S38>/Constant'

    real_T CompareToConstant_const_i;
                                    // Mask Parameter: CompareToConstant_const_i
                                       //  Referenced by: '<S36>/Constant'

    real_T CompareToConstant_const_l;
                                    // Mask Parameter: CompareToConstant_const_l
                                       //  Referenced by: '<S39>/Constant'

    real_T CompareToConstant_const_em;
                                   // Mask Parameter: CompareToConstant_const_em
                                      //  Referenced by: '<S32>/Constant'

    real_T CompareToConstant_const_j3;
                                   // Mask Parameter: CompareToConstant_const_j3
                                      //  Referenced by: '<S30>/Constant'

    real_T CompareToConstant_const_ik;
                                   // Mask Parameter: CompareToConstant_const_ik
                                      //  Referenced by: '<S33>/Constant'

    real_T Constant1_Value;            // Expression: 0
                                          //  Referenced by: '<S24>/Constant1'

    real_T Constant_Value;             // Expression: 180
                                          //  Referenced by: '<S24>/Constant'

    real_T Bias_Bias;                  // Expression: -90
                                          //  Referenced by: '<S28>/Bias'

    real_T Gain_Gain;                  // Expression: -1
                                          //  Referenced by: '<S28>/Gain'

    real_T Bias1_Bias;                 // Expression: +90
                                          //  Referenced by: '<S28>/Bias1'

    real_T Constant2_Value;            // Expression: 360
                                          //  Referenced by: '<S31>/Constant2'

    real_T Bias_Bias_n;                // Expression: 180
                                          //  Referenced by: '<S31>/Bias'

    real_T Bias1_Bias_k;               // Expression: -180
                                          //  Referenced by: '<S31>/Bias1'

    real_T Constant2_Value_j;          // Expression: 360
                                          //  Referenced by: '<S29>/Constant2'

    real_T Bias_Bias_k;                // Expression: 180
                                          //  Referenced by: '<S29>/Bias'

    real_T Bias1_Bias_i;               // Expression: -180
                                          //  Referenced by: '<S29>/Bias1'

    real_T Constant1_Value_f;          // Expression: 0
                                          //  Referenced by: '<S25>/Constant1'

    real_T Constant_Value_l;           // Expression: 180
                                          //  Referenced by: '<S25>/Constant'

    real_T Bias_Bias_o;                // Expression: -90
                                          //  Referenced by: '<S34>/Bias'

    real_T Gain_Gain_o;                // Expression: -1
                                          //  Referenced by: '<S34>/Gain'

    real_T Bias1_Bias_d;               // Expression: +90
                                          //  Referenced by: '<S34>/Bias1'

    real_T Constant2_Value_c;          // Expression: 360
                                          //  Referenced by: '<S37>/Constant2'

    real_T Bias_Bias_l;                // Expression: 180
                                          //  Referenced by: '<S37>/Bias'

    real_T Bias1_Bias_o;               // Expression: -180
                                          //  Referenced by: '<S37>/Bias1'

    real_T Constant2_Value_k;          // Expression: 360
                                          //  Referenced by: '<S35>/Constant2'

    real_T Bias_Bias_p;                // Expression: 180
                                          //  Referenced by: '<S35>/Bias'

    real_T Bias1_Bias_m;               // Expression: -180
                                          //  Referenced by: '<S35>/Bias1'

    real_T Constant1_Value_k;          // Expression: 0
                                          //  Referenced by: '<S47>/Constant1'

    real_T Constant_Value_lu;          // Expression: 180
                                          //  Referenced by: '<S47>/Constant'

    real_T Bias_Bias_d;                // Expression: -90
                                          //  Referenced by: '<S51>/Bias'

    real_T Gain_Gain_k;                // Expression: -1
                                          //  Referenced by: '<S51>/Gain'

    real_T Bias1_Bias_h;               // Expression: +90
                                          //  Referenced by: '<S51>/Bias1'

    real_T Constant2_Value_p;          // Expression: 360
                                          //  Referenced by: '<S54>/Constant2'

    real_T Bias_Bias_b;                // Expression: 180
                                          //  Referenced by: '<S54>/Bias'

    real_T Bias1_Bias_p;               // Expression: -180
                                          //  Referenced by: '<S54>/Bias1'

    real_T Constant2_Value_g;          // Expression: 360
                                          //  Referenced by: '<S52>/Constant2'

    real_T Bias_Bias_a;                // Expression: 180
                                          //  Referenced by: '<S52>/Bias'

    real_T Bias1_Bias_l;               // Expression: -180
                                          //  Referenced by: '<S52>/Bias1'

    real_T Constant1_Value_fz;         // Expression: 0
                                          //  Referenced by: '<S48>/Constant1'

    real_T Constant_Value_m;           // Expression: 180
                                          //  Referenced by: '<S48>/Constant'

    real_T Bias_Bias_e;                // Expression: -90
                                          //  Referenced by: '<S57>/Bias'

    real_T Gain_Gain_n;                // Expression: -1
                                          //  Referenced by: '<S57>/Gain'

    real_T Bias1_Bias_c;               // Expression: +90
                                          //  Referenced by: '<S57>/Bias1'

    real_T Constant2_Value_jr;         // Expression: 360
                                          //  Referenced by: '<S60>/Constant2'

    real_T Bias_Bias_al;               // Expression: 180
                                          //  Referenced by: '<S60>/Bias'

    real_T Bias1_Bias_k2;              // Expression: -180
                                          //  Referenced by: '<S60>/Bias1'

    real_T Constant2_Value_kz;         // Expression: 360
                                          //  Referenced by: '<S58>/Constant2'

    real_T Bias_Bias_dq;               // Expression: 180
                                          //  Referenced by: '<S58>/Bias'

    real_T Bias1_Bias_cz;              // Expression: -180
                                          //  Referenced by: '<S58>/Bias1'

    real_T Constant2_Value_h;          // Expression: 1
                                          //  Referenced by: '<S64>/Constant2'

    real_T Constant1_Value_d;          // Expression: R
                                          //  Referenced by: '<S64>/Constant1'

    real_T Constant_Value_f;           // Expression: 1
                                          //  Referenced by: '<S66>/Constant'

    real_T Constant_Value_a;           // Expression: 1
                                          //  Referenced by: '<S68>/Constant'

    real_T Constant_Value_c;           // Expression: F
                                          //  Referenced by: '<S67>/Constant'

    real_T f_Value;                    // Expression: 1
                                          //  Referenced by: '<S67>/f'

    real_T Constant_Value_ch;          // Expression: 1
                                          //  Referenced by: '<S64>/Constant'

    real_T flatx_from_N_Value;         // Expression: 0
                                          //  Referenced by: '<S4>/flat-x_from_N'

    real_T Constant3_Value;            // Expression: 1
                                          //  Referenced by: '<S64>/Constant3'

    real_T R2_Value[16];               // Expression: p.R{2}
                                          //  Referenced by: '<S2>/R2'

    real_T MeasurementFcn2Inputs_Value;// Expression: 1
                                          //  Referenced by: '<S2>/MeasurementFcn2Inputs'

    real_T R1_Value[4];                // Expression: p.R{1}
                                          //  Referenced by: '<S2>/R1'

    real_T MeasurementFcn1Inputs_Value;// Expression: 0
                                          //  Referenced by: '<S2>/MeasurementFcn1Inputs'

    real_T NED_convert1_Gain;          // Expression: -1
                                          //  Referenced by: '<Root>/NED_convert1'

    real_T R4_Value;                   // Expression: p.R{4}
                                          //  Referenced by: '<S1>/R4'

    real_T MeasurementFcn4Inputs_Value;// Expression: 1
                                          //  Referenced by: '<S1>/MeasurementFcn4Inputs'

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

    real_T Constant_Value_ay;          // Expression: 0
                                          //  Referenced by: '<S3>/Constant'

    real_T Constant2_Value_l;          // Expression: 1
                                          //  Referenced by: '<S40>/Constant2'

    real_T Constant1_Value_l;          // Expression: R
                                          //  Referenced by: '<S40>/Constant1'

    real_T Constant_Value_g;           // Expression: 1
                                          //  Referenced by: '<S43>/Constant'

    real_T Constant_Value_j;           // Expression: 1
                                          //  Referenced by: '<S45>/Constant'

    real_T Constant_Value_d;           // Expression: F
                                          //  Referenced by: '<S44>/Constant'

    real_T f_Value_f;                  // Expression: 1
                                          //  Referenced by: '<S44>/f'

    real_T Constant_Value_g2;          // Expression: 1
                                          //  Referenced by: '<S40>/Constant'

    real_T Constant3_Value_l;          // Expression: 1
                                          //  Referenced by: '<S40>/Constant3'

    real_T Q_Value;                    // Expression: p.Q
                                          //  Referenced by: '<S1>/Q'

    real_T StateTransitionFcnInputs_Value;// Expression: 0
                                             //  Referenced by: '<S1>/StateTransitionFcnInputs'

    real_T DataStoreMemoryP_InitialValue[9];// Expression: p.InitialCovariance
                                               //  Referenced by: '<S1>/DataStoreMemory - P'

    real_T DataStoreMemoryx_InitialValue[3];// Expression: p.InitialState
                                               //  Referenced by: '<S1>/DataStoreMemory - x'

    real_T Q_Value_c[36];              // Expression: p.Q
                                          //  Referenced by: '<S2>/Q'

    real_T StateTransitionFcnInputs_Valu_l;// Expression: 0
                                              //  Referenced by: '<S2>/StateTransitionFcnInputs'

    real_T DataStoreMemoryP_InitialValue_h[36];// Expression: p.InitialCovariance
                                                  //  Referenced by: '<S2>/DataStoreMemory - P'

    real_T DataStoreMemoryx_InitialValue_k[6];// Expression: p.InitialState
                                                 //  Referenced by: '<S2>/DataStoreMemory - x'

    boolean_T yBlockOrdering_Y0;       // Computed Parameter: yBlockOrdering_Y0
                                          //  Referenced by: '<S5>/yBlockOrdering'

    boolean_T yBlockOrdering_Y0_b;    // Computed Parameter: yBlockOrdering_Y0_b
                                         //  Referenced by: '<S7>/yBlockOrdering'

    boolean_T yBlockOrdering_Y0_k;    // Computed Parameter: yBlockOrdering_Y0_k
                                         //  Referenced by: '<S16>/yBlockOrdering'

    boolean_T yBlockOrdering_Y0_m;    // Computed Parameter: yBlockOrdering_Y0_m
                                         //  Referenced by: '<S17>/yBlockOrdering'

    boolean_T BlockOrdering_Value;     // Expression: true()
                                          //  Referenced by: '<S2>/BlockOrdering'

    boolean_T BlockOrdering_Value_b;   // Expression: true()
                                          //  Referenced by: '<S1>/BlockOrdering'

    P_Correct2 Correct4;               // '<S1>/Correct4'
    P_Correct2 Correct2_a;             // '<S1>/Correct2'
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

  static P rtP;
  // private data and function members
 private:
  // Tunable parameters

  // Block signals and states
  DW rtDW;

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // Real-Time Model
  RT_MODEL rtM;

  // private member function(s) for subsystem '<S1>/Correct2'
  void Correct2_Init(DW_Correct2 *localDW, P_Correct2 *localP);
  void Correct2(boolean_T rtu_Enable, real_T rtu_yMeas, real_T rtu_R, boolean_T
                rtu_uBlockOrdering, DW_Correct2 *localDW, real_T rtd_P_i[9],
                real_T rtd_x[3]);

  // private member function(s) for subsystem '<Root>'
  void EKFCorrector_correctStateAndCov(real_T x[6], real_T P_0[36], const real_T
    y[4], const real_T Pxy[24], const real_T Pyy[16], const real_T dHdx[24]);
}

;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S5>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S6>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S7>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S8>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S10>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S1>/checkMeasurementFcn1Signals' : Unused code path elimination
//  Block '<S1>/checkMeasurementFcn2Signals' : Unused code path elimination
//  Block '<S1>/checkMeasurementFcn3Signals' : Unused code path elimination
//  Block '<S1>/checkMeasurementFcn4Signals' : Unused code path elimination
//  Block '<S1>/checkStateTransitionFcnSignals' : Unused code path elimination
//  Block '<S16>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S17>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S19>/RegisterSimulinkFcn' : Unused code path elimination
//  Block '<S2>/checkMeasurementFcn1Signals' : Unused code path elimination
//  Block '<S2>/checkMeasurementFcn2Signals' : Unused code path elimination
//  Block '<S2>/checkStateTransitionFcnSignals' : Unused code path elimination
//  Block '<S1>/DataTypeConversion_Enable2' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_Q' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_R1' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_R2' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_R3' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_R4' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_uMeas1' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_uMeas2' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_uMeas3' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_uMeas4' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_uState' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_y1' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_y2' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_y3' : Eliminate redundant data type conversion
//  Block '<S1>/DataTypeConversion_y4' : Eliminate redundant data type conversion
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
//  '<S2>'   : 'positionEstimator/EKF_Position1'
//  '<S3>'   : 'positionEstimator/Subsystem'
//  '<S4>'   : 'positionEstimator/from_home'
//  '<S5>'   : 'positionEstimator/EKF_Altitude/Correct1'
//  '<S6>'   : 'positionEstimator/EKF_Altitude/Correct2'
//  '<S7>'   : 'positionEstimator/EKF_Altitude/Correct3'
//  '<S8>'   : 'positionEstimator/EKF_Altitude/Correct4'
//  '<S9>'   : 'positionEstimator/EKF_Altitude/Output'
//  '<S10>'  : 'positionEstimator/EKF_Altitude/Predict'
//  '<S11>'  : 'positionEstimator/EKF_Altitude/Correct1/Correct'
//  '<S12>'  : 'positionEstimator/EKF_Altitude/Correct2/Correct'
//  '<S13>'  : 'positionEstimator/EKF_Altitude/Correct3/Correct'
//  '<S14>'  : 'positionEstimator/EKF_Altitude/Correct4/Correct'
//  '<S15>'  : 'positionEstimator/EKF_Altitude/Predict/Predict'
//  '<S16>'  : 'positionEstimator/EKF_Position1/Correct1'
//  '<S17>'  : 'positionEstimator/EKF_Position1/Correct2'
//  '<S18>'  : 'positionEstimator/EKF_Position1/Output'
//  '<S19>'  : 'positionEstimator/EKF_Position1/Predict'
//  '<S20>'  : 'positionEstimator/EKF_Position1/Correct1/Correct'
//  '<S21>'  : 'positionEstimator/EKF_Position1/Correct2/Correct'
//  '<S22>'  : 'positionEstimator/EKF_Position1/Predict/Predict'
//  '<S23>'  : 'positionEstimator/Subsystem/Flat Earth to LLA'
//  '<S24>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap'
//  '<S25>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap1'
//  '<S26>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LongLat_offset'
//  '<S27>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/pos_deg'
//  '<S28>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap/Latitude Wrap 90'
//  '<S29>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap/Wrap Longitude'
//  '<S30>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap/Latitude Wrap 90/Compare To Constant'
//  '<S31>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap/Latitude Wrap 90/Wrap Angle 180'
//  '<S32>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap/Latitude Wrap 90/Wrap Angle 180/Compare To Constant'
//  '<S33>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap/Wrap Longitude/Compare To Constant'
//  '<S34>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap1/Latitude Wrap 90'
//  '<S35>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap1/Wrap Longitude'
//  '<S36>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap1/Latitude Wrap 90/Compare To Constant'
//  '<S37>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap1/Latitude Wrap 90/Wrap Angle 180'
//  '<S38>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap1/Latitude Wrap 90/Wrap Angle 180/Compare To Constant'
//  '<S39>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LatLong wrap1/Wrap Longitude/Compare To Constant'
//  '<S40>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LongLat_offset/Find Radian//Distance'
//  '<S41>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LongLat_offset/rotation_rad'
//  '<S42>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LongLat_offset/Find Radian//Distance/Angle Conversion2'
//  '<S43>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LongLat_offset/Find Radian//Distance/denom'
//  '<S44>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LongLat_offset/Find Radian//Distance/e'
//  '<S45>'  : 'positionEstimator/Subsystem/Flat Earth to LLA/LongLat_offset/Find Radian//Distance/e^4'
//  '<S46>'  : 'positionEstimator/from_home/LLA to Flat Earth'
//  '<S47>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap'
//  '<S48>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0'
//  '<S49>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem'
//  '<S50>'  : 'positionEstimator/from_home/LLA to Flat Earth/pos_rad'
//  '<S51>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Latitude Wrap 90'
//  '<S52>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Wrap Longitude'
//  '<S53>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Latitude Wrap 90/Compare To Constant'
//  '<S54>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Latitude Wrap 90/Wrap Angle 180'
//  '<S55>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Latitude Wrap 90/Wrap Angle 180/Compare To Constant'
//  '<S56>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap/Wrap Longitude/Compare To Constant'
//  '<S57>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Latitude Wrap 90'
//  '<S58>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Wrap Longitude'
//  '<S59>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Latitude Wrap 90/Compare To Constant'
//  '<S60>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Latitude Wrap 90/Wrap Angle 180'
//  '<S61>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Latitude Wrap 90/Wrap Angle 180/Compare To Constant'
//  '<S62>'  : 'positionEstimator/from_home/LLA to Flat Earth/LatLong wrap LL0/Wrap Longitude/Compare To Constant'
//  '<S63>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Angle Conversion2'
//  '<S64>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Find Radian//Distance'
//  '<S65>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Find Radian//Distance/Angle Conversion2'
//  '<S66>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Find Radian//Distance/denom'
//  '<S67>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Find Radian//Distance/e'
//  '<S68>'  : 'positionEstimator/from_home/LLA to Flat Earth/Subsystem/Find Radian//Distance/e^4'

#endif                                 // RTW_HEADER_positionEstimator_h_

//
// File trailer for generated code.
//
// [EOF]
//
