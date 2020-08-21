//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl.h
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
#ifndef RTW_HEADER_positionControl_h_
#define RTW_HEADER_positionControl_h_
#include <cmath>
#include "rtwtypes.h"
#include "positionControl_types.h"

// Macros for accessing real-time model data structure

//
//  Exported Global Parameters
//
//  Note: Exported global parameters are tunable parameters with an exported
//  global storage class designation.  Code generation will declare the memory for
//  these parameters and exports their symbols.
//

extern real_T Yaw_angleToRate_P;       // Variable: Yaw_angleToRate_P
                                          //  Referenced by: '<S1>/Gain'

extern real_T pos_x_D;                 // Variable: pos_x_D
                                          //  Referenced by: '<S33>/Derivative Gain'

extern real_T pos_x_I;                 // Variable: pos_x_I
                                          //  Referenced by: '<S36>/Integral Gain'

extern real_T pos_x_P;                 // Variable: pos_x_P
                                          //  Referenced by: '<S44>/Proportional Gain'

extern real_T pos_x_vel_D;             // Variable: pos_x_vel_D
                                          //  Referenced by: '<S81>/Derivative Gain'

extern real_T pos_x_vel_I;             // Variable: pos_x_vel_I
                                          //  Referenced by: '<S84>/Integral Gain'

extern real_T pos_x_vel_P;             // Variable: pos_x_vel_P
                                          //  Referenced by: '<S92>/Proportional Gain'

extern real_T pos_y_I;                 // Variable: pos_y_I
                                          //  Referenced by: '<S180>/Integral Gain'

extern real_T pos_y_P;                 // Variable: pos_y_P
                                          //  Referenced by: '<S188>/Proportional Gain'

extern real_T pos_y_vel_D;             // Variable: pos_y_vel_D
                                          //  Referenced by: '<S225>/Derivative Gain'

extern real_T pos_y_vel_I;             // Variable: pos_y_vel_I
                                          //  Referenced by: '<S228>/Integral Gain'

extern real_T pos_y_vel_P;             // Variable: pos_y_vel_P
                                          //  Referenced by: '<S236>/Proportional Gain'

extern real_T pos_z_D;                 // Variable: pos_z_D
                                          //  Referenced by: '<S129>/Derivative Gain'

extern real_T pos_z_I;                 // Variable: pos_z_I
                                          //  Referenced by: '<S132>/Integral Gain'

extern real_T pos_z_P;                 // Variable: pos_z_P
                                          //  Referenced by: '<S140>/Proportional Gain'


// Class declaration for model positionControl
class positionControlModelClass {
  // public data and function members
 public:
  // Block signals (default storage)
  typedef struct {
    real_T DataTypeConversion;         // '<S1>/Data Type Conversion'
    real_T TrigonometricFunction_o1;   // '<S7>/Trigonometric Function'
    real_T TrigonometricFunction_o2;   // '<S7>/Trigonometric Function'
    real_T MatrixConcatenate[4];       // '<S7>/Matrix Concatenate'
    real_T x_error;                    // '<S1>/Add'
    real_T ProportionalGain;           // '<S44>/Proportional Gain'
    real_T Integrator;                 // '<S39>/Integrator'
    real_T DerivativeGain;             // '<S33>/Derivative Gain'
    real_T Filter;                     // '<S34>/Filter'
    real_T SumD;                       // '<S34>/SumD'
    real_T FilterCoefficient;          // '<S42>/Filter Coefficient'
    real_T Sum;                        // '<S48>/Sum'
    real_T Saturation;                 // '<S46>/Saturation'
    real_T y_error;                    // '<S1>/Add4'
    real_T ProportionalGain_p;         // '<S188>/Proportional Gain'
    real_T Integrator_f;               // '<S183>/Integrator'
    real_T DerivativeGain_n;           // '<S177>/Derivative Gain'
    real_T Filter_p;                   // '<S178>/Filter'
    real_T SumD_k;                     // '<S178>/SumD'
    real_T FilterCoefficient_n;        // '<S186>/Filter Coefficient'
    real_T Sum_k;                      // '<S192>/Sum'
    real_T Saturation_o;               // '<S190>/Saturation'
    real_T Add1[2];                    // '<S1>/Add1'
    real_T vel_error[2];               // '<S1>/Matrix Multiply'
    real_T ProportionalGain_m;         // '<S236>/Proportional Gain'
    real_T Integrator_h;               // '<S231>/Integrator'
    real_T DerivativeGain_c;           // '<S225>/Derivative Gain'
    real_T Filter_g;                   // '<S226>/Filter'
    real_T SumD_f;                     // '<S226>/SumD'
    real_T FilterCoefficient_e;        // '<S234>/Filter Coefficient'
    real_T Sum_m;                      // '<S240>/Sum'
    real_T Saturation_l;               // '<S238>/Saturation'
    real_T Gain1;                      // '<S1>/Gain1'
    real_T ProportionalGain_h;         // '<S92>/Proportional Gain'
    real_T Integrator_c;               // '<S87>/Integrator'
    real_T DerivativeGain_p;           // '<S81>/Derivative Gain'
    real_T Filter_i;                   // '<S82>/Filter'
    real_T SumD_h;                     // '<S82>/SumD'
    real_T FilterCoefficient_f;        // '<S90>/Filter Coefficient'
    real_T Sum_o;                      // '<S96>/Sum'
    real_T Saturation_j;               // '<S94>/Saturation'
    real_T Sum_my;                     // '<S1>/Sum'
    real_T Gain;                       // '<S1>/Gain'
    real_T alt_error;                  // '<S1>/Add2'
    real_T Gain2;                      // '<S1>/Gain2'
    real_T ProportionalGain_k;         // '<S140>/Proportional Gain'
    real_T Integrator_p;               // '<S135>/Integrator'
    real_T DerivativeGain_pu;          // '<S129>/Derivative Gain'
    real_T Filter_m;                   // '<S130>/Filter'
    real_T SumD_b;                     // '<S130>/SumD'
    real_T FilterCoefficient_a;        // '<S138>/Filter Coefficient'
    real_T Sum_c;                      // '<S144>/Sum'
    real_T Saturation_li;              // '<S142>/Saturation'
    real_T IntegralGain;               // '<S36>/Integral Gain'
    real_T SumI2;                      // '<S80>/SumI2'
    real_T Kb;                         // '<S80>/Kb'
    real_T IntegralGain_k;             // '<S84>/Integral Gain'
    real_T SumI4;                      // '<S80>/SumI4'
    real_T IntegralGain_o;             // '<S180>/Integral Gain'
    real_T SumI2_n;                    // '<S224>/SumI2'
    real_T Kb_e;                       // '<S224>/Kb'
    real_T IntegralGain_b;             // '<S228>/Integral Gain'
    real_T SumI4_c;                    // '<S224>/SumI4'
    real_T ZeroGain;                   // '<S128>/ZeroGain'
    real_T DeadZone;                   // '<S128>/DeadZone'
    real_T SignPreSat;                 // '<S128>/SignPreSat'
    real_T IntegralGain_l;             // '<S132>/Integral Gain'
    real_T SignPreIntegrator;          // '<S128>/SignPreIntegrator'
    real_T Switch;                     // '<S128>/Switch'
    int8_T DataTypeConv1;              // '<S128>/DataTypeConv1'
    int8_T DataTypeConv2;              // '<S128>/DataTypeConv2'
    boolean_T NotEqual;                // '<S128>/NotEqual'
    boolean_T Equal1;                  // '<S128>/Equal1'
    boolean_T AND3;                    // '<S128>/AND3'
  } B_positionControl_T;

  // Block states (default storage) for system '<Root>'
  typedef struct {
    real_T Integrator_DSTATE;          // '<S39>/Integrator'
    real_T Filter_DSTATE;              // '<S34>/Filter'
    real_T Integrator_DSTATE_k;        // '<S183>/Integrator'
    real_T Filter_DSTATE_m;            // '<S178>/Filter'
    real_T Integrator_DSTATE_f;        // '<S231>/Integrator'
    real_T Filter_DSTATE_j;            // '<S226>/Filter'
    real_T Integrator_DSTATE_m;        // '<S87>/Integrator'
    real_T Filter_DSTATE_d;            // '<S82>/Filter'
    real_T Integrator_DSTATE_b;        // '<S135>/Integrator'
    real_T Filter_DSTATE_e;            // '<S130>/Filter'
  } DW_positionControl_T;

  // External inputs (root inport signals with default storage)
  typedef struct {
    real32_T estim_yaw;                // '<Root>/estim_yaw'
    real_T set_yaw;                    // '<Root>/set_yaw'
    real_T set_x;                      // '<Root>/set_x'
    real_T set_y;                      // '<Root>/set_y'
    real_T set_z;                      // '<Root>/set_z'
    real_T estim_x;                    // '<Root>/estim_x'
    real_T estim_y;                    // '<Root>/estim_y'
    real_T estim_z;                    // '<Root>/estim_z'
    real_T estim_dx;                   // '<Root>/estim_dx'
    real_T estim_dy;                   // '<Root>/estim_dy'
    real_T estim_dz;                   // '<Root>/estim_dz'
  } ExtU_positionControl_T;

  // External outputs (root outports fed by signals with default storage)
  typedef struct {
    real32_T des_roll;                 // '<Root>/des_roll'
    real32_T des_pitch;                // '<Root>/des_pitch'
    real32_T des_yaw_rate;             // '<Root>/des_yaw_rate'
    real32_T des_Thrust;               // '<Root>/des_Thrust'
  } ExtY_positionControl_T;

  // Parameters (default storage)
  struct P_positionControl_T {
    real_T pos_y_D;                    // Variable: pos_y_D
                                          //  Referenced by: '<S177>/Derivative Gain'

    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S34>/Filter'

    real_T PIDController4_InitialCondition;
                              // Mask Parameter: PIDController4_InitialCondition
                                 //  Referenced by: '<S178>/Filter'

    real_T PIDController5_InitialCondition;
                              // Mask Parameter: PIDController5_InitialCondition
                                 //  Referenced by: '<S226>/Filter'

    real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S82>/Filter'

    real_T PIDController3_InitialCondition;
                              // Mask Parameter: PIDController3_InitialCondition
                                 //  Referenced by: '<S130>/Filter'

    real_T PIDController_InitialConditio_c;
                              // Mask Parameter: PIDController_InitialConditio_c
                                 //  Referenced by: '<S39>/Integrator'

    real_T PIDController4_InitialConditi_i;
                              // Mask Parameter: PIDController4_InitialConditi_i
                                 //  Referenced by: '<S183>/Integrator'

    real_T PIDController5_InitialConditi_c;
                              // Mask Parameter: PIDController5_InitialConditi_c
                                 //  Referenced by: '<S231>/Integrator'

    real_T PIDController1_InitialConditi_a;
                              // Mask Parameter: PIDController1_InitialConditi_a
                                 //  Referenced by: '<S87>/Integrator'

    real_T PIDController3_InitialConditi_d;
                              // Mask Parameter: PIDController3_InitialConditi_d
                                 //  Referenced by: '<S135>/Integrator'

    real_T PIDController1_Kb;          // Mask Parameter: PIDController1_Kb
                                          //  Referenced by: '<S80>/Kb'

    real_T PIDController5_Kb;          // Mask Parameter: PIDController5_Kb
                                          //  Referenced by: '<S224>/Kb'

    real_T PIDController_LowerSaturationLi;
                              // Mask Parameter: PIDController_LowerSaturationLi
                                 //  Referenced by: '<S46>/Saturation'

    real_T PIDController4_LowerSaturationL;
                              // Mask Parameter: PIDController4_LowerSaturationL
                                 //  Referenced by: '<S190>/Saturation'

    real_T PIDController5_LowerSaturationL;
                              // Mask Parameter: PIDController5_LowerSaturationL
                                 //  Referenced by: '<S238>/Saturation'

    real_T PIDController1_LowerSaturationL;
                              // Mask Parameter: PIDController1_LowerSaturationL
                                 //  Referenced by: '<S94>/Saturation'

    real_T PIDController3_LowerSaturationL;
                              // Mask Parameter: PIDController3_LowerSaturationL
                                 //  Referenced by:
                                 //    '<S128>/DeadZone'
                                 //    '<S142>/Saturation'

    real_T PIDController_N;            // Mask Parameter: PIDController_N
                                          //  Referenced by: '<S42>/Filter Coefficient'

    real_T PIDController4_N;           // Mask Parameter: PIDController4_N
                                          //  Referenced by: '<S186>/Filter Coefficient'

    real_T PIDController5_N;           // Mask Parameter: PIDController5_N
                                          //  Referenced by: '<S234>/Filter Coefficient'

    real_T PIDController1_N;           // Mask Parameter: PIDController1_N
                                          //  Referenced by: '<S90>/Filter Coefficient'

    real_T PIDController3_N;           // Mask Parameter: PIDController3_N
                                          //  Referenced by: '<S138>/Filter Coefficient'

    real_T PIDController_UpperSaturationLi;
                              // Mask Parameter: PIDController_UpperSaturationLi
                                 //  Referenced by: '<S46>/Saturation'

    real_T PIDController4_UpperSaturationL;
                              // Mask Parameter: PIDController4_UpperSaturationL
                                 //  Referenced by: '<S190>/Saturation'

    real_T PIDController5_UpperSaturationL;
                              // Mask Parameter: PIDController5_UpperSaturationL
                                 //  Referenced by: '<S238>/Saturation'

    real_T PIDController1_UpperSaturationL;
                              // Mask Parameter: PIDController1_UpperSaturationL
                                 //  Referenced by: '<S94>/Saturation'

    real_T PIDController3_UpperSaturationL;
                              // Mask Parameter: PIDController3_UpperSaturationL
                                 //  Referenced by:
                                 //    '<S128>/DeadZone'
                                 //    '<S142>/Saturation'

    real_T Constant1_Value;            // Expression: 0
                                          //  Referenced by: '<S128>/Constant1'

    real_T Gain_Gain;                  // Expression: -1
                                          //  Referenced by: '<S7>/Gain'

    real_T Integrator_gainval;         // Computed Parameter: Integrator_gainval
                                          //  Referenced by: '<S39>/Integrator'

    real_T Filter_gainval;             // Computed Parameter: Filter_gainval
                                          //  Referenced by: '<S34>/Filter'

    real_T Integrator_gainval_l;     // Computed Parameter: Integrator_gainval_l
                                        //  Referenced by: '<S183>/Integrator'

    real_T Filter_gainval_l;           // Computed Parameter: Filter_gainval_l
                                          //  Referenced by: '<S178>/Filter'

    real_T Integrator_gainval_k;     // Computed Parameter: Integrator_gainval_k
                                        //  Referenced by: '<S231>/Integrator'

    real_T Filter_gainval_i;           // Computed Parameter: Filter_gainval_i
                                          //  Referenced by: '<S226>/Filter'

    real_T Gain1_Gain;                 // Expression: -1
                                          //  Referenced by: '<S1>/Gain1'

    real_T Integrator_gainval_lc;   // Computed Parameter: Integrator_gainval_lc
                                       //  Referenced by: '<S87>/Integrator'

    real_T Filter_gainval_l5;          // Computed Parameter: Filter_gainval_l5
                                          //  Referenced by: '<S82>/Filter'

    real_T Gain2_Gain;                 // Expression: -1
                                          //  Referenced by: '<S1>/Gain2'

    real_T Integrator_gainval_a;     // Computed Parameter: Integrator_gainval_a
                                        //  Referenced by: '<S135>/Integrator'

    real_T Filter_gainval_g;           // Computed Parameter: Filter_gainval_g
                                          //  Referenced by: '<S130>/Filter'

    real_T ZeroGain_Gain;              // Expression: 0
                                          //  Referenced by: '<S128>/ZeroGain'

  };

  // Tunable parameters
  static P_positionControl_T positionControl_P;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  positionControlModelClass();

  // Destructor
  ~positionControlModelClass();

  // Block parameters get method
  const positionControlModelClass::P_positionControl_T & getBlockParameters()
    const;

  // Block parameters set method
  void setBlockParameters(const P_positionControl_T *ppositionControl_P);

  // Root-level structure-based inputs set method

  // Root inports set method
  void setExternalInputs(const ExtU_positionControl_T* pExtU_positionControl_T)
  {
    positionControl_U = *pExtU_positionControl_T;
  }

  // Root-level structure-based outputs get method

  // Root outports get method
  const positionControlModelClass::ExtY_positionControl_T & getExternalOutputs()
    const
  {
    return positionControl_Y;
  }

  // private data and function members
 private:
  // Block signals
  B_positionControl_T positionControl_B;

  // Block states
  DW_positionControl_T positionControl_DW;

  // External inputs
  ExtU_positionControl_T positionControl_U;

  // External outputs
  ExtY_positionControl_T positionControl_Y;
};

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
//  '<Root>' : 'positionControl'
//  '<S1>'   : 'positionControl/position control'
//  '<S2>'   : 'positionControl/position control/PID Controller'
//  '<S3>'   : 'positionControl/position control/PID Controller1'
//  '<S4>'   : 'positionControl/position control/PID Controller3'
//  '<S5>'   : 'positionControl/position control/PID Controller4'
//  '<S6>'   : 'positionControl/position control/PID Controller5'
//  '<S7>'   : 'positionControl/position control/rot_matrix'
//  '<S8>'   : 'positionControl/position control/PID Controller/Anti-windup'
//  '<S9>'   : 'positionControl/position control/PID Controller/D Gain'
//  '<S10>'  : 'positionControl/position control/PID Controller/Filter'
//  '<S11>'  : 'positionControl/position control/PID Controller/Filter ICs'
//  '<S12>'  : 'positionControl/position control/PID Controller/I Gain'
//  '<S13>'  : 'positionControl/position control/PID Controller/Ideal P Gain'
//  '<S14>'  : 'positionControl/position control/PID Controller/Ideal P Gain Fdbk'
//  '<S15>'  : 'positionControl/position control/PID Controller/Integrator'
//  '<S16>'  : 'positionControl/position control/PID Controller/Integrator ICs'
//  '<S17>'  : 'positionControl/position control/PID Controller/N Copy'
//  '<S18>'  : 'positionControl/position control/PID Controller/N Gain'
//  '<S19>'  : 'positionControl/position control/PID Controller/P Copy'
//  '<S20>'  : 'positionControl/position control/PID Controller/Parallel P Gain'
//  '<S21>'  : 'positionControl/position control/PID Controller/Reset Signal'
//  '<S22>'  : 'positionControl/position control/PID Controller/Saturation'
//  '<S23>'  : 'positionControl/position control/PID Controller/Saturation Fdbk'
//  '<S24>'  : 'positionControl/position control/PID Controller/Sum'
//  '<S25>'  : 'positionControl/position control/PID Controller/Sum Fdbk'
//  '<S26>'  : 'positionControl/position control/PID Controller/Tracking Mode'
//  '<S27>'  : 'positionControl/position control/PID Controller/Tracking Mode Sum'
//  '<S28>'  : 'positionControl/position control/PID Controller/Tsamp - Integral'
//  '<S29>'  : 'positionControl/position control/PID Controller/Tsamp - Ngain'
//  '<S30>'  : 'positionControl/position control/PID Controller/postSat Signal'
//  '<S31>'  : 'positionControl/position control/PID Controller/preSat Signal'
//  '<S32>'  : 'positionControl/position control/PID Controller/Anti-windup/Passthrough'
//  '<S33>'  : 'positionControl/position control/PID Controller/D Gain/Internal Parameters'
//  '<S34>'  : 'positionControl/position control/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S35>'  : 'positionControl/position control/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S36>'  : 'positionControl/position control/PID Controller/I Gain/Internal Parameters'
//  '<S37>'  : 'positionControl/position control/PID Controller/Ideal P Gain/Passthrough'
//  '<S38>'  : 'positionControl/position control/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S39>'  : 'positionControl/position control/PID Controller/Integrator/Discrete'
//  '<S40>'  : 'positionControl/position control/PID Controller/Integrator ICs/Internal IC'
//  '<S41>'  : 'positionControl/position control/PID Controller/N Copy/Disabled'
//  '<S42>'  : 'positionControl/position control/PID Controller/N Gain/Internal Parameters'
//  '<S43>'  : 'positionControl/position control/PID Controller/P Copy/Disabled'
//  '<S44>'  : 'positionControl/position control/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S45>'  : 'positionControl/position control/PID Controller/Reset Signal/Disabled'
//  '<S46>'  : 'positionControl/position control/PID Controller/Saturation/Enabled'
//  '<S47>'  : 'positionControl/position control/PID Controller/Saturation Fdbk/Disabled'
//  '<S48>'  : 'positionControl/position control/PID Controller/Sum/Sum_PID'
//  '<S49>'  : 'positionControl/position control/PID Controller/Sum Fdbk/Disabled'
//  '<S50>'  : 'positionControl/position control/PID Controller/Tracking Mode/Disabled'
//  '<S51>'  : 'positionControl/position control/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S52>'  : 'positionControl/position control/PID Controller/Tsamp - Integral/Passthrough'
//  '<S53>'  : 'positionControl/position control/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S54>'  : 'positionControl/position control/PID Controller/postSat Signal/Forward_Path'
//  '<S55>'  : 'positionControl/position control/PID Controller/preSat Signal/Forward_Path'
//  '<S56>'  : 'positionControl/position control/PID Controller1/Anti-windup'
//  '<S57>'  : 'positionControl/position control/PID Controller1/D Gain'
//  '<S58>'  : 'positionControl/position control/PID Controller1/Filter'
//  '<S59>'  : 'positionControl/position control/PID Controller1/Filter ICs'
//  '<S60>'  : 'positionControl/position control/PID Controller1/I Gain'
//  '<S61>'  : 'positionControl/position control/PID Controller1/Ideal P Gain'
//  '<S62>'  : 'positionControl/position control/PID Controller1/Ideal P Gain Fdbk'
//  '<S63>'  : 'positionControl/position control/PID Controller1/Integrator'
//  '<S64>'  : 'positionControl/position control/PID Controller1/Integrator ICs'
//  '<S65>'  : 'positionControl/position control/PID Controller1/N Copy'
//  '<S66>'  : 'positionControl/position control/PID Controller1/N Gain'
//  '<S67>'  : 'positionControl/position control/PID Controller1/P Copy'
//  '<S68>'  : 'positionControl/position control/PID Controller1/Parallel P Gain'
//  '<S69>'  : 'positionControl/position control/PID Controller1/Reset Signal'
//  '<S70>'  : 'positionControl/position control/PID Controller1/Saturation'
//  '<S71>'  : 'positionControl/position control/PID Controller1/Saturation Fdbk'
//  '<S72>'  : 'positionControl/position control/PID Controller1/Sum'
//  '<S73>'  : 'positionControl/position control/PID Controller1/Sum Fdbk'
//  '<S74>'  : 'positionControl/position control/PID Controller1/Tracking Mode'
//  '<S75>'  : 'positionControl/position control/PID Controller1/Tracking Mode Sum'
//  '<S76>'  : 'positionControl/position control/PID Controller1/Tsamp - Integral'
//  '<S77>'  : 'positionControl/position control/PID Controller1/Tsamp - Ngain'
//  '<S78>'  : 'positionControl/position control/PID Controller1/postSat Signal'
//  '<S79>'  : 'positionControl/position control/PID Controller1/preSat Signal'
//  '<S80>'  : 'positionControl/position control/PID Controller1/Anti-windup/Back Calculation'
//  '<S81>'  : 'positionControl/position control/PID Controller1/D Gain/Internal Parameters'
//  '<S82>'  : 'positionControl/position control/PID Controller1/Filter/Disc. Forward Euler Filter'
//  '<S83>'  : 'positionControl/position control/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S84>'  : 'positionControl/position control/PID Controller1/I Gain/Internal Parameters'
//  '<S85>'  : 'positionControl/position control/PID Controller1/Ideal P Gain/Passthrough'
//  '<S86>'  : 'positionControl/position control/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S87>'  : 'positionControl/position control/PID Controller1/Integrator/Discrete'
//  '<S88>'  : 'positionControl/position control/PID Controller1/Integrator ICs/Internal IC'
//  '<S89>'  : 'positionControl/position control/PID Controller1/N Copy/Disabled'
//  '<S90>'  : 'positionControl/position control/PID Controller1/N Gain/Internal Parameters'
//  '<S91>'  : 'positionControl/position control/PID Controller1/P Copy/Disabled'
//  '<S92>'  : 'positionControl/position control/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S93>'  : 'positionControl/position control/PID Controller1/Reset Signal/Disabled'
//  '<S94>'  : 'positionControl/position control/PID Controller1/Saturation/Enabled'
//  '<S95>'  : 'positionControl/position control/PID Controller1/Saturation Fdbk/Disabled'
//  '<S96>'  : 'positionControl/position control/PID Controller1/Sum/Sum_PID'
//  '<S97>'  : 'positionControl/position control/PID Controller1/Sum Fdbk/Disabled'
//  '<S98>'  : 'positionControl/position control/PID Controller1/Tracking Mode/Disabled'
//  '<S99>'  : 'positionControl/position control/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S100>' : 'positionControl/position control/PID Controller1/Tsamp - Integral/Passthrough'
//  '<S101>' : 'positionControl/position control/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S102>' : 'positionControl/position control/PID Controller1/postSat Signal/Forward_Path'
//  '<S103>' : 'positionControl/position control/PID Controller1/preSat Signal/Forward_Path'
//  '<S104>' : 'positionControl/position control/PID Controller3/Anti-windup'
//  '<S105>' : 'positionControl/position control/PID Controller3/D Gain'
//  '<S106>' : 'positionControl/position control/PID Controller3/Filter'
//  '<S107>' : 'positionControl/position control/PID Controller3/Filter ICs'
//  '<S108>' : 'positionControl/position control/PID Controller3/I Gain'
//  '<S109>' : 'positionControl/position control/PID Controller3/Ideal P Gain'
//  '<S110>' : 'positionControl/position control/PID Controller3/Ideal P Gain Fdbk'
//  '<S111>' : 'positionControl/position control/PID Controller3/Integrator'
//  '<S112>' : 'positionControl/position control/PID Controller3/Integrator ICs'
//  '<S113>' : 'positionControl/position control/PID Controller3/N Copy'
//  '<S114>' : 'positionControl/position control/PID Controller3/N Gain'
//  '<S115>' : 'positionControl/position control/PID Controller3/P Copy'
//  '<S116>' : 'positionControl/position control/PID Controller3/Parallel P Gain'
//  '<S117>' : 'positionControl/position control/PID Controller3/Reset Signal'
//  '<S118>' : 'positionControl/position control/PID Controller3/Saturation'
//  '<S119>' : 'positionControl/position control/PID Controller3/Saturation Fdbk'
//  '<S120>' : 'positionControl/position control/PID Controller3/Sum'
//  '<S121>' : 'positionControl/position control/PID Controller3/Sum Fdbk'
//  '<S122>' : 'positionControl/position control/PID Controller3/Tracking Mode'
//  '<S123>' : 'positionControl/position control/PID Controller3/Tracking Mode Sum'
//  '<S124>' : 'positionControl/position control/PID Controller3/Tsamp - Integral'
//  '<S125>' : 'positionControl/position control/PID Controller3/Tsamp - Ngain'
//  '<S126>' : 'positionControl/position control/PID Controller3/postSat Signal'
//  '<S127>' : 'positionControl/position control/PID Controller3/preSat Signal'
//  '<S128>' : 'positionControl/position control/PID Controller3/Anti-windup/Disc. Clamping Parallel'
//  '<S129>' : 'positionControl/position control/PID Controller3/D Gain/Internal Parameters'
//  '<S130>' : 'positionControl/position control/PID Controller3/Filter/Disc. Forward Euler Filter'
//  '<S131>' : 'positionControl/position control/PID Controller3/Filter ICs/Internal IC - Filter'
//  '<S132>' : 'positionControl/position control/PID Controller3/I Gain/Internal Parameters'
//  '<S133>' : 'positionControl/position control/PID Controller3/Ideal P Gain/Passthrough'
//  '<S134>' : 'positionControl/position control/PID Controller3/Ideal P Gain Fdbk/Disabled'
//  '<S135>' : 'positionControl/position control/PID Controller3/Integrator/Discrete'
//  '<S136>' : 'positionControl/position control/PID Controller3/Integrator ICs/Internal IC'
//  '<S137>' : 'positionControl/position control/PID Controller3/N Copy/Disabled'
//  '<S138>' : 'positionControl/position control/PID Controller3/N Gain/Internal Parameters'
//  '<S139>' : 'positionControl/position control/PID Controller3/P Copy/Disabled'
//  '<S140>' : 'positionControl/position control/PID Controller3/Parallel P Gain/Internal Parameters'
//  '<S141>' : 'positionControl/position control/PID Controller3/Reset Signal/Disabled'
//  '<S142>' : 'positionControl/position control/PID Controller3/Saturation/Enabled'
//  '<S143>' : 'positionControl/position control/PID Controller3/Saturation Fdbk/Disabled'
//  '<S144>' : 'positionControl/position control/PID Controller3/Sum/Sum_PID'
//  '<S145>' : 'positionControl/position control/PID Controller3/Sum Fdbk/Disabled'
//  '<S146>' : 'positionControl/position control/PID Controller3/Tracking Mode/Disabled'
//  '<S147>' : 'positionControl/position control/PID Controller3/Tracking Mode Sum/Passthrough'
//  '<S148>' : 'positionControl/position control/PID Controller3/Tsamp - Integral/Passthrough'
//  '<S149>' : 'positionControl/position control/PID Controller3/Tsamp - Ngain/Passthrough'
//  '<S150>' : 'positionControl/position control/PID Controller3/postSat Signal/Forward_Path'
//  '<S151>' : 'positionControl/position control/PID Controller3/preSat Signal/Forward_Path'
//  '<S152>' : 'positionControl/position control/PID Controller4/Anti-windup'
//  '<S153>' : 'positionControl/position control/PID Controller4/D Gain'
//  '<S154>' : 'positionControl/position control/PID Controller4/Filter'
//  '<S155>' : 'positionControl/position control/PID Controller4/Filter ICs'
//  '<S156>' : 'positionControl/position control/PID Controller4/I Gain'
//  '<S157>' : 'positionControl/position control/PID Controller4/Ideal P Gain'
//  '<S158>' : 'positionControl/position control/PID Controller4/Ideal P Gain Fdbk'
//  '<S159>' : 'positionControl/position control/PID Controller4/Integrator'
//  '<S160>' : 'positionControl/position control/PID Controller4/Integrator ICs'
//  '<S161>' : 'positionControl/position control/PID Controller4/N Copy'
//  '<S162>' : 'positionControl/position control/PID Controller4/N Gain'
//  '<S163>' : 'positionControl/position control/PID Controller4/P Copy'
//  '<S164>' : 'positionControl/position control/PID Controller4/Parallel P Gain'
//  '<S165>' : 'positionControl/position control/PID Controller4/Reset Signal'
//  '<S166>' : 'positionControl/position control/PID Controller4/Saturation'
//  '<S167>' : 'positionControl/position control/PID Controller4/Saturation Fdbk'
//  '<S168>' : 'positionControl/position control/PID Controller4/Sum'
//  '<S169>' : 'positionControl/position control/PID Controller4/Sum Fdbk'
//  '<S170>' : 'positionControl/position control/PID Controller4/Tracking Mode'
//  '<S171>' : 'positionControl/position control/PID Controller4/Tracking Mode Sum'
//  '<S172>' : 'positionControl/position control/PID Controller4/Tsamp - Integral'
//  '<S173>' : 'positionControl/position control/PID Controller4/Tsamp - Ngain'
//  '<S174>' : 'positionControl/position control/PID Controller4/postSat Signal'
//  '<S175>' : 'positionControl/position control/PID Controller4/preSat Signal'
//  '<S176>' : 'positionControl/position control/PID Controller4/Anti-windup/Passthrough'
//  '<S177>' : 'positionControl/position control/PID Controller4/D Gain/Internal Parameters'
//  '<S178>' : 'positionControl/position control/PID Controller4/Filter/Disc. Forward Euler Filter'
//  '<S179>' : 'positionControl/position control/PID Controller4/Filter ICs/Internal IC - Filter'
//  '<S180>' : 'positionControl/position control/PID Controller4/I Gain/Internal Parameters'
//  '<S181>' : 'positionControl/position control/PID Controller4/Ideal P Gain/Passthrough'
//  '<S182>' : 'positionControl/position control/PID Controller4/Ideal P Gain Fdbk/Disabled'
//  '<S183>' : 'positionControl/position control/PID Controller4/Integrator/Discrete'
//  '<S184>' : 'positionControl/position control/PID Controller4/Integrator ICs/Internal IC'
//  '<S185>' : 'positionControl/position control/PID Controller4/N Copy/Disabled'
//  '<S186>' : 'positionControl/position control/PID Controller4/N Gain/Internal Parameters'
//  '<S187>' : 'positionControl/position control/PID Controller4/P Copy/Disabled'
//  '<S188>' : 'positionControl/position control/PID Controller4/Parallel P Gain/Internal Parameters'
//  '<S189>' : 'positionControl/position control/PID Controller4/Reset Signal/Disabled'
//  '<S190>' : 'positionControl/position control/PID Controller4/Saturation/Enabled'
//  '<S191>' : 'positionControl/position control/PID Controller4/Saturation Fdbk/Disabled'
//  '<S192>' : 'positionControl/position control/PID Controller4/Sum/Sum_PID'
//  '<S193>' : 'positionControl/position control/PID Controller4/Sum Fdbk/Disabled'
//  '<S194>' : 'positionControl/position control/PID Controller4/Tracking Mode/Disabled'
//  '<S195>' : 'positionControl/position control/PID Controller4/Tracking Mode Sum/Passthrough'
//  '<S196>' : 'positionControl/position control/PID Controller4/Tsamp - Integral/Passthrough'
//  '<S197>' : 'positionControl/position control/PID Controller4/Tsamp - Ngain/Passthrough'
//  '<S198>' : 'positionControl/position control/PID Controller4/postSat Signal/Forward_Path'
//  '<S199>' : 'positionControl/position control/PID Controller4/preSat Signal/Forward_Path'
//  '<S200>' : 'positionControl/position control/PID Controller5/Anti-windup'
//  '<S201>' : 'positionControl/position control/PID Controller5/D Gain'
//  '<S202>' : 'positionControl/position control/PID Controller5/Filter'
//  '<S203>' : 'positionControl/position control/PID Controller5/Filter ICs'
//  '<S204>' : 'positionControl/position control/PID Controller5/I Gain'
//  '<S205>' : 'positionControl/position control/PID Controller5/Ideal P Gain'
//  '<S206>' : 'positionControl/position control/PID Controller5/Ideal P Gain Fdbk'
//  '<S207>' : 'positionControl/position control/PID Controller5/Integrator'
//  '<S208>' : 'positionControl/position control/PID Controller5/Integrator ICs'
//  '<S209>' : 'positionControl/position control/PID Controller5/N Copy'
//  '<S210>' : 'positionControl/position control/PID Controller5/N Gain'
//  '<S211>' : 'positionControl/position control/PID Controller5/P Copy'
//  '<S212>' : 'positionControl/position control/PID Controller5/Parallel P Gain'
//  '<S213>' : 'positionControl/position control/PID Controller5/Reset Signal'
//  '<S214>' : 'positionControl/position control/PID Controller5/Saturation'
//  '<S215>' : 'positionControl/position control/PID Controller5/Saturation Fdbk'
//  '<S216>' : 'positionControl/position control/PID Controller5/Sum'
//  '<S217>' : 'positionControl/position control/PID Controller5/Sum Fdbk'
//  '<S218>' : 'positionControl/position control/PID Controller5/Tracking Mode'
//  '<S219>' : 'positionControl/position control/PID Controller5/Tracking Mode Sum'
//  '<S220>' : 'positionControl/position control/PID Controller5/Tsamp - Integral'
//  '<S221>' : 'positionControl/position control/PID Controller5/Tsamp - Ngain'
//  '<S222>' : 'positionControl/position control/PID Controller5/postSat Signal'
//  '<S223>' : 'positionControl/position control/PID Controller5/preSat Signal'
//  '<S224>' : 'positionControl/position control/PID Controller5/Anti-windup/Back Calculation'
//  '<S225>' : 'positionControl/position control/PID Controller5/D Gain/Internal Parameters'
//  '<S226>' : 'positionControl/position control/PID Controller5/Filter/Disc. Forward Euler Filter'
//  '<S227>' : 'positionControl/position control/PID Controller5/Filter ICs/Internal IC - Filter'
//  '<S228>' : 'positionControl/position control/PID Controller5/I Gain/Internal Parameters'
//  '<S229>' : 'positionControl/position control/PID Controller5/Ideal P Gain/Passthrough'
//  '<S230>' : 'positionControl/position control/PID Controller5/Ideal P Gain Fdbk/Disabled'
//  '<S231>' : 'positionControl/position control/PID Controller5/Integrator/Discrete'
//  '<S232>' : 'positionControl/position control/PID Controller5/Integrator ICs/Internal IC'
//  '<S233>' : 'positionControl/position control/PID Controller5/N Copy/Disabled'
//  '<S234>' : 'positionControl/position control/PID Controller5/N Gain/Internal Parameters'
//  '<S235>' : 'positionControl/position control/PID Controller5/P Copy/Disabled'
//  '<S236>' : 'positionControl/position control/PID Controller5/Parallel P Gain/Internal Parameters'
//  '<S237>' : 'positionControl/position control/PID Controller5/Reset Signal/Disabled'
//  '<S238>' : 'positionControl/position control/PID Controller5/Saturation/Enabled'
//  '<S239>' : 'positionControl/position control/PID Controller5/Saturation Fdbk/Disabled'
//  '<S240>' : 'positionControl/position control/PID Controller5/Sum/Sum_PID'
//  '<S241>' : 'positionControl/position control/PID Controller5/Sum Fdbk/Disabled'
//  '<S242>' : 'positionControl/position control/PID Controller5/Tracking Mode/Disabled'
//  '<S243>' : 'positionControl/position control/PID Controller5/Tracking Mode Sum/Passthrough'
//  '<S244>' : 'positionControl/position control/PID Controller5/Tsamp - Integral/Passthrough'
//  '<S245>' : 'positionControl/position control/PID Controller5/Tsamp - Ngain/Passthrough'
//  '<S246>' : 'positionControl/position control/PID Controller5/postSat Signal/Forward_Path'
//  '<S247>' : 'positionControl/position control/PID Controller5/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_positionControl_h_

//
// File trailer for generated code.
//
// [EOF]
//
