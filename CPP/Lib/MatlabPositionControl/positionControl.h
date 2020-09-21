//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl.h
//
// Code generated for Simulink model 'positionControl'.
//
// Model version                  : 1.19
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Mon Sep 21 22:15:56 2020
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

extern real_T hoverThr;                // Variable: hoverThr
                                          //  Referenced by: '<S1>/Constant'

extern real_T pos_x_D;                 // Variable: pos_x_D
                                          //  Referenced by: '<S35>/Derivative Gain'

extern real_T pos_x_I;                 // Variable: pos_x_I
                                          //  Referenced by: '<S38>/Integral Gain'

extern real_T pos_x_P;                 // Variable: pos_x_P
                                          //  Referenced by: '<S46>/Proportional Gain'

extern real_T pos_x_vel_D;             // Variable: pos_x_vel_D
                                          //  Referenced by: '<S83>/Derivative Gain'

extern real_T pos_x_vel_I;             // Variable: pos_x_vel_I
                                          //  Referenced by: '<S86>/Integral Gain'

extern real_T pos_x_vel_P;             // Variable: pos_x_vel_P
                                          //  Referenced by: '<S94>/Proportional Gain'

extern real_T pos_y_D;                 // Variable: pos_y_D
                                          //  Referenced by: '<S181>/Derivative Gain'

extern real_T pos_y_I;                 // Variable: pos_y_I
                                          //  Referenced by: '<S184>/Integral Gain'

extern real_T pos_y_P;                 // Variable: pos_y_P
                                          //  Referenced by: '<S192>/Proportional Gain'

extern real_T pos_y_vel_D;             // Variable: pos_y_vel_D
                                          //  Referenced by: '<S229>/Derivative Gain'

extern real_T pos_y_vel_I;             // Variable: pos_y_vel_I
                                          //  Referenced by: '<S232>/Integral Gain'

extern real_T pos_y_vel_P;             // Variable: pos_y_vel_P
                                          //  Referenced by: '<S240>/Proportional Gain'

extern real_T pos_z_D;                 // Variable: pos_z_D
                                          //  Referenced by: '<S277>/Derivative Gain'

extern real_T pos_z_I;                 // Variable: pos_z_I
                                          //  Referenced by: '<S280>/Integral Gain'

extern real_T pos_z_P;                 // Variable: pos_z_P
                                          //  Referenced by: '<S288>/Proportional Gain'

extern real_T pos_z_vel_D;             // Variable: pos_z_vel_D
                                          //  Referenced by: '<S131>/Derivative Gain'

extern real_T pos_z_vel_I;             // Variable: pos_z_vel_I
                                          //  Referenced by: '<S136>/Integral Gain'

extern real_T pos_z_vel_P;             // Variable: pos_z_vel_P
                                          //  Referenced by: '<S144>/Proportional Gain'

extern real32_T Yaw_angleToRate_P;     // Variable: Yaw_angleToRate_P
                                          //  Referenced by: '<S1>/Gain'


// Class declaration for model positionControl
class positionControlModelClass {
  // public data and function members
 public:
  // Block signals (default storage)
  typedef struct {
    real_T DataTypeConversion;         // '<S1>/Data Type Conversion'
    real_T TrigonometricFunction_o1;   // '<S9>/Trigonometric Function'
    real_T TrigonometricFunction_o2;   // '<S9>/Trigonometric Function'
    real_T MatrixConcatenate[4];       // '<S9>/Matrix Concatenate'
    real_T x_error;                    // '<S1>/Add'
    real_T ProportionalGain;           // '<S46>/Proportional Gain'
    real_T Integrator;                 // '<S41>/Integrator'
    real_T DerivativeGain;             // '<S35>/Derivative Gain'
    real_T Filter;                     // '<S36>/Filter'
    real_T SumD;                       // '<S36>/SumD'
    real_T FilterCoefficient;          // '<S44>/Filter Coefficient'
    real_T Sum;                        // '<S50>/Sum'
    real_T Saturation;                 // '<S48>/Saturation'
    real_T y_error;                    // '<S1>/Add4'
    real_T ProportionalGain_p;         // '<S192>/Proportional Gain'
    real_T Integrator_f;               // '<S187>/Integrator'
    real_T DerivativeGain_n;           // '<S181>/Derivative Gain'
    real_T Filter_p;                   // '<S182>/Filter'
    real_T SumD_k;                     // '<S182>/SumD'
    real_T FilterCoefficient_n;        // '<S190>/Filter Coefficient'
    real_T Sum_k;                      // '<S196>/Sum'
    real_T Saturation_o;               // '<S194>/Saturation'
    real_T Add1[2];                    // '<S1>/Add1'
    real_T vel_error[2];               // '<S1>/Matrix Multiply'
    real_T ProportionalGain_m;         // '<S240>/Proportional Gain'
    real_T Integrator_h;               // '<S235>/Integrator'
    real_T DerivativeGain_c;           // '<S229>/Derivative Gain'
    real_T Filter_g;                   // '<S230>/Filter'
    real_T SumD_f;                     // '<S230>/SumD'
    real_T FilterCoefficient_e;        // '<S238>/Filter Coefficient'
    real_T Sum_m;                      // '<S244>/Sum'
    real_T Saturation_l;               // '<S242>/Saturation'
    real_T ProportionalGain_h;         // '<S94>/Proportional Gain'
    real_T Integrator_c;               // '<S89>/Integrator'
    real_T DerivativeGain_p;           // '<S83>/Derivative Gain'
    real_T Filter_i;                   // '<S84>/Filter'
    real_T SumD_h;                     // '<S84>/SumD'
    real_T FilterCoefficient_f;        // '<S92>/Filter Coefficient'
    real_T Sum_o;                      // '<S98>/Sum'
    real_T Saturation_j;               // '<S96>/Saturation'
    real_T Gain1;                      // '<S1>/Gain1'
    real_T alt_error;                  // '<S1>/Add2'
    real_T Gain2;                      // '<S1>/Gain2'
    real_T ProportionalGain_j;         // '<S288>/Proportional Gain'
    real_T Integrator_ca;              // '<S283>/Integrator'
    real_T DerivativeGain_f;           // '<S277>/Derivative Gain'
    real_T Filter_gq;                  // '<S278>/Filter'
    real_T SumD_d;                     // '<S278>/SumD'
    real_T FilterCoefficient_j;        // '<S286>/Filter Coefficient'
    real_T Sum_d;                      // '<S292>/Sum'
    real_T Saturation_jh;              // '<S290>/Saturation'
    real_T Gain3;                      // '<S1>/Gain3'
    real_T Add3;                       // '<S1>/Add3'
    real_T ProportionalGain_k;         // '<S144>/Proportional Gain'
    real_T Integrator_p;               // '<S139>/Integrator'
    real_T DerivativeGain_pu;          // '<S131>/Derivative Gain'
    real_T Tsamp;                      // '<S134>/Tsamp'
    real_T UD;                         // '<S132>/UD'
    real_T Diff;                       // '<S132>/Diff'
    real_T Sum_c;                      // '<S148>/Sum'
    real_T Saturation_li;              // '<S146>/Saturation'
    real_T Sum1;                       // '<S1>/Sum1'
    real_T Saturation_jb;              // '<S1>/Saturation'
    real_T IntegralGain;               // '<S38>/Integral Gain'
    real_T SumI2;                      // '<S82>/SumI2'
    real_T Kb;                         // '<S82>/Kb'
    real_T IntegralGain_k;             // '<S86>/Integral Gain'
    real_T SumI4;                      // '<S82>/SumI4'
    real_T IntegralGain_o;             // '<S184>/Integral Gain'
    real_T SumI2_n;                    // '<S228>/SumI2'
    real_T Kb_e;                       // '<S228>/Kb'
    real_T IntegralGain_b;             // '<S232>/Integral Gain'
    real_T SumI4_c;                    // '<S228>/SumI4'
    real_T ZeroGain;                   // '<S130>/ZeroGain'
    real_T DeadZone;                   // '<S130>/DeadZone'
    real_T SignPreSat;                 // '<S130>/SignPreSat'
    real_T IntegralGain_l;             // '<S136>/Integral Gain'
    real_T SignPreIntegrator;          // '<S130>/SignPreIntegrator'
    real_T Switch;                     // '<S130>/Switch'
    real_T ZeroGain_a;                 // '<S276>/ZeroGain'
    real_T DeadZone_b;                 // '<S276>/DeadZone'
    real_T SignPreSat_i;               // '<S276>/SignPreSat'
    real_T IntegralGain_g;             // '<S280>/Integral Gain'
    real_T SignPreIntegrator_h;        // '<S276>/SignPreIntegrator'
    real_T Switch_h;                   // '<S276>/Switch'
    real32_T Sum_my;                   // '<S1>/Sum'
    real32_T y;                        // '<S1>/MATLAB Function'
    int8_T DataTypeConv1;              // '<S130>/DataTypeConv1'
    int8_T DataTypeConv2;              // '<S130>/DataTypeConv2'
    int8_T DataTypeConv1_e;            // '<S276>/DataTypeConv1'
    int8_T DataTypeConv2_m;            // '<S276>/DataTypeConv2'
    boolean_T NotEqual;                // '<S130>/NotEqual'
    boolean_T Equal1;                  // '<S130>/Equal1'
    boolean_T AND3;                    // '<S130>/AND3'
    boolean_T NotEqual_i;              // '<S276>/NotEqual'
    boolean_T Equal1_l;                // '<S276>/Equal1'
    boolean_T AND3_m;                  // '<S276>/AND3'
  } B_positionControl_T;

  // Block states (default storage) for system '<Root>'
  typedef struct {
    real_T Integrator_DSTATE;          // '<S41>/Integrator'
    real_T Filter_DSTATE;              // '<S36>/Filter'
    real_T Integrator_DSTATE_k;        // '<S187>/Integrator'
    real_T Filter_DSTATE_m;            // '<S182>/Filter'
    real_T Integrator_DSTATE_f;        // '<S235>/Integrator'
    real_T Filter_DSTATE_j;            // '<S230>/Filter'
    real_T Integrator_DSTATE_m;        // '<S89>/Integrator'
    real_T Filter_DSTATE_d;            // '<S84>/Filter'
    real_T Integrator_DSTATE_p;        // '<S283>/Integrator'
    real_T Filter_DSTATE_mo;           // '<S278>/Filter'
    real_T Integrator_DSTATE_b;        // '<S139>/Integrator'
    real_T UD_DSTATE;                  // '<S132>/UD'
  } DW_positionControl_T;

  // External inputs (root inport signals with default storage)
  typedef struct {
    real32_T estim_yaw;                // '<Root>/estim_yaw'
    real32_T set_yaw;                  // '<Root>/set_yaw'
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
    real_T vel_Horizon_Max;            // Variable: vel_Horizon_Max
                                          //  Referenced by:
                                          //    '<S48>/Saturation'
                                          //    '<S194>/Saturation'

    real_T vel_climbMax;               // Variable: vel_climbMax
                                          //  Referenced by:
                                          //    '<S276>/DeadZone'
                                          //    '<S290>/Saturation'

    real_T vel_descentMax;             // Variable: vel_descentMax
                                          //  Referenced by:
                                          //    '<S276>/DeadZone'
                                          //    '<S290>/Saturation'

    real_T PIDController3_DifferentiatorIC;
                              // Mask Parameter: PIDController3_DifferentiatorIC
                                 //  Referenced by: '<S132>/UD'

    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S36>/Filter'

    real_T PIDController4_InitialCondition;
                              // Mask Parameter: PIDController4_InitialCondition
                                 //  Referenced by: '<S182>/Filter'

    real_T PIDController5_InitialCondition;
                              // Mask Parameter: PIDController5_InitialCondition
                                 //  Referenced by: '<S230>/Filter'

    real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S84>/Filter'

    real_T ZPostoVel_InitialConditionForFi;
                              // Mask Parameter: ZPostoVel_InitialConditionForFi
                                 //  Referenced by: '<S278>/Filter'

    real_T PIDController_InitialConditio_c;
                              // Mask Parameter: PIDController_InitialConditio_c
                                 //  Referenced by: '<S41>/Integrator'

    real_T PIDController4_InitialConditi_i;
                              // Mask Parameter: PIDController4_InitialConditi_i
                                 //  Referenced by: '<S187>/Integrator'

    real_T PIDController5_InitialConditi_c;
                              // Mask Parameter: PIDController5_InitialConditi_c
                                 //  Referenced by: '<S235>/Integrator'

    real_T PIDController1_InitialConditi_a;
                              // Mask Parameter: PIDController1_InitialConditi_a
                                 //  Referenced by: '<S89>/Integrator'

    real_T ZPostoVel_InitialConditionForIn;
                              // Mask Parameter: ZPostoVel_InitialConditionForIn
                                 //  Referenced by: '<S283>/Integrator'

    real_T PIDController3_InitialCondition;
                              // Mask Parameter: PIDController3_InitialCondition
                                 //  Referenced by: '<S139>/Integrator'

    real_T PIDController1_Kb;          // Mask Parameter: PIDController1_Kb
                                          //  Referenced by: '<S82>/Kb'

    real_T PIDController5_Kb;          // Mask Parameter: PIDController5_Kb
                                          //  Referenced by: '<S228>/Kb'

    real_T PIDController5_LowerSaturationL;
                              // Mask Parameter: PIDController5_LowerSaturationL
                                 //  Referenced by: '<S242>/Saturation'

    real_T PIDController1_LowerSaturationL;
                              // Mask Parameter: PIDController1_LowerSaturationL
                                 //  Referenced by: '<S96>/Saturation'

    real_T PIDController3_LowerSaturationL;
                              // Mask Parameter: PIDController3_LowerSaturationL
                                 //  Referenced by:
                                 //    '<S130>/DeadZone'
                                 //    '<S146>/Saturation'

    real_T PIDController_N;            // Mask Parameter: PIDController_N
                                          //  Referenced by: '<S44>/Filter Coefficient'

    real_T PIDController4_N;           // Mask Parameter: PIDController4_N
                                          //  Referenced by: '<S190>/Filter Coefficient'

    real_T PIDController5_N;           // Mask Parameter: PIDController5_N
                                          //  Referenced by: '<S238>/Filter Coefficient'

    real_T PIDController1_N;           // Mask Parameter: PIDController1_N
                                          //  Referenced by: '<S92>/Filter Coefficient'

    real_T ZPostoVel_N;                // Mask Parameter: ZPostoVel_N
                                          //  Referenced by: '<S286>/Filter Coefficient'

    real_T PIDController5_UpperSaturationL;
                              // Mask Parameter: PIDController5_UpperSaturationL
                                 //  Referenced by: '<S242>/Saturation'

    real_T PIDController1_UpperSaturationL;
                              // Mask Parameter: PIDController1_UpperSaturationL
                                 //  Referenced by: '<S96>/Saturation'

    real_T PIDController3_UpperSaturationL;
                              // Mask Parameter: PIDController3_UpperSaturationL
                                 //  Referenced by:
                                 //    '<S130>/DeadZone'
                                 //    '<S146>/Saturation'

    real_T Constant1_Value;            // Expression: 0
                                          //  Referenced by: '<S130>/Constant1'

    real_T Constant1_Value_k;          // Expression: 0
                                          //  Referenced by: '<S276>/Constant1'

    real_T Gain_Gain;                  // Expression: -1
                                          //  Referenced by: '<S9>/Gain'

    real_T Integrator_gainval;         // Computed Parameter: Integrator_gainval
                                          //  Referenced by: '<S41>/Integrator'

    real_T Filter_gainval;             // Computed Parameter: Filter_gainval
                                          //  Referenced by: '<S36>/Filter'

    real_T Integrator_gainval_l;     // Computed Parameter: Integrator_gainval_l
                                        //  Referenced by: '<S187>/Integrator'

    real_T Filter_gainval_l;           // Computed Parameter: Filter_gainval_l
                                          //  Referenced by: '<S182>/Filter'

    real_T Integrator_gainval_k;     // Computed Parameter: Integrator_gainval_k
                                        //  Referenced by: '<S235>/Integrator'

    real_T Filter_gainval_i;           // Computed Parameter: Filter_gainval_i
                                          //  Referenced by: '<S230>/Filter'

    real_T Integrator_gainval_lc;   // Computed Parameter: Integrator_gainval_lc
                                       //  Referenced by: '<S89>/Integrator'

    real_T Filter_gainval_l5;          // Computed Parameter: Filter_gainval_l5
                                          //  Referenced by: '<S84>/Filter'

    real_T Gain1_Gain;                 // Expression: -1
                                          //  Referenced by: '<S1>/Gain1'

    real_T Gain2_Gain;                 // Expression: -1
                                          //  Referenced by: '<S1>/Gain2'

    real_T Integrator_gainval_j;     // Computed Parameter: Integrator_gainval_j
                                        //  Referenced by: '<S283>/Integrator'

    real_T Filter_gainval_c;           // Computed Parameter: Filter_gainval_c
                                          //  Referenced by: '<S278>/Filter'

    real_T Gain3_Gain;                 // Expression: -1
                                          //  Referenced by: '<S1>/Gain3'

    real_T Integrator_gainval_a;     // Computed Parameter: Integrator_gainval_a
                                        //  Referenced by: '<S139>/Integrator'

    real_T Tsamp_WtEt;                 // Computed Parameter: Tsamp_WtEt
                                          //  Referenced by: '<S134>/Tsamp'

    real_T Saturation_UpperSat;        // Expression: 1
                                          //  Referenced by: '<S1>/Saturation'

    real_T Saturation_LowerSat;        // Expression: 0
                                          //  Referenced by: '<S1>/Saturation'

    real_T ZeroGain_Gain;              // Expression: 0
                                          //  Referenced by: '<S130>/ZeroGain'

    real_T ZeroGain_Gain_b;            // Expression: 0
                                          //  Referenced by: '<S276>/ZeroGain'

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
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S132>/DTDup' : Unused code path elimination
//  Block '<S1>/Data Type Conversion1' : Eliminate redundant data type conversion


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
//  '<S2>'   : 'positionControl/position control/MATLAB Function'
//  '<S3>'   : 'positionControl/position control/PID Controller'
//  '<S4>'   : 'positionControl/position control/PID Controller1'
//  '<S5>'   : 'positionControl/position control/PID Controller3'
//  '<S6>'   : 'positionControl/position control/PID Controller4'
//  '<S7>'   : 'positionControl/position control/PID Controller5'
//  '<S8>'   : 'positionControl/position control/ZPostoVel'
//  '<S9>'   : 'positionControl/position control/rot_matrix'
//  '<S10>'  : 'positionControl/position control/PID Controller/Anti-windup'
//  '<S11>'  : 'positionControl/position control/PID Controller/D Gain'
//  '<S12>'  : 'positionControl/position control/PID Controller/Filter'
//  '<S13>'  : 'positionControl/position control/PID Controller/Filter ICs'
//  '<S14>'  : 'positionControl/position control/PID Controller/I Gain'
//  '<S15>'  : 'positionControl/position control/PID Controller/Ideal P Gain'
//  '<S16>'  : 'positionControl/position control/PID Controller/Ideal P Gain Fdbk'
//  '<S17>'  : 'positionControl/position control/PID Controller/Integrator'
//  '<S18>'  : 'positionControl/position control/PID Controller/Integrator ICs'
//  '<S19>'  : 'positionControl/position control/PID Controller/N Copy'
//  '<S20>'  : 'positionControl/position control/PID Controller/N Gain'
//  '<S21>'  : 'positionControl/position control/PID Controller/P Copy'
//  '<S22>'  : 'positionControl/position control/PID Controller/Parallel P Gain'
//  '<S23>'  : 'positionControl/position control/PID Controller/Reset Signal'
//  '<S24>'  : 'positionControl/position control/PID Controller/Saturation'
//  '<S25>'  : 'positionControl/position control/PID Controller/Saturation Fdbk'
//  '<S26>'  : 'positionControl/position control/PID Controller/Sum'
//  '<S27>'  : 'positionControl/position control/PID Controller/Sum Fdbk'
//  '<S28>'  : 'positionControl/position control/PID Controller/Tracking Mode'
//  '<S29>'  : 'positionControl/position control/PID Controller/Tracking Mode Sum'
//  '<S30>'  : 'positionControl/position control/PID Controller/Tsamp - Integral'
//  '<S31>'  : 'positionControl/position control/PID Controller/Tsamp - Ngain'
//  '<S32>'  : 'positionControl/position control/PID Controller/postSat Signal'
//  '<S33>'  : 'positionControl/position control/PID Controller/preSat Signal'
//  '<S34>'  : 'positionControl/position control/PID Controller/Anti-windup/Passthrough'
//  '<S35>'  : 'positionControl/position control/PID Controller/D Gain/Internal Parameters'
//  '<S36>'  : 'positionControl/position control/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S37>'  : 'positionControl/position control/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S38>'  : 'positionControl/position control/PID Controller/I Gain/Internal Parameters'
//  '<S39>'  : 'positionControl/position control/PID Controller/Ideal P Gain/Passthrough'
//  '<S40>'  : 'positionControl/position control/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S41>'  : 'positionControl/position control/PID Controller/Integrator/Discrete'
//  '<S42>'  : 'positionControl/position control/PID Controller/Integrator ICs/Internal IC'
//  '<S43>'  : 'positionControl/position control/PID Controller/N Copy/Disabled'
//  '<S44>'  : 'positionControl/position control/PID Controller/N Gain/Internal Parameters'
//  '<S45>'  : 'positionControl/position control/PID Controller/P Copy/Disabled'
//  '<S46>'  : 'positionControl/position control/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S47>'  : 'positionControl/position control/PID Controller/Reset Signal/Disabled'
//  '<S48>'  : 'positionControl/position control/PID Controller/Saturation/Enabled'
//  '<S49>'  : 'positionControl/position control/PID Controller/Saturation Fdbk/Disabled'
//  '<S50>'  : 'positionControl/position control/PID Controller/Sum/Sum_PID'
//  '<S51>'  : 'positionControl/position control/PID Controller/Sum Fdbk/Disabled'
//  '<S52>'  : 'positionControl/position control/PID Controller/Tracking Mode/Disabled'
//  '<S53>'  : 'positionControl/position control/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S54>'  : 'positionControl/position control/PID Controller/Tsamp - Integral/Passthrough'
//  '<S55>'  : 'positionControl/position control/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S56>'  : 'positionControl/position control/PID Controller/postSat Signal/Forward_Path'
//  '<S57>'  : 'positionControl/position control/PID Controller/preSat Signal/Forward_Path'
//  '<S58>'  : 'positionControl/position control/PID Controller1/Anti-windup'
//  '<S59>'  : 'positionControl/position control/PID Controller1/D Gain'
//  '<S60>'  : 'positionControl/position control/PID Controller1/Filter'
//  '<S61>'  : 'positionControl/position control/PID Controller1/Filter ICs'
//  '<S62>'  : 'positionControl/position control/PID Controller1/I Gain'
//  '<S63>'  : 'positionControl/position control/PID Controller1/Ideal P Gain'
//  '<S64>'  : 'positionControl/position control/PID Controller1/Ideal P Gain Fdbk'
//  '<S65>'  : 'positionControl/position control/PID Controller1/Integrator'
//  '<S66>'  : 'positionControl/position control/PID Controller1/Integrator ICs'
//  '<S67>'  : 'positionControl/position control/PID Controller1/N Copy'
//  '<S68>'  : 'positionControl/position control/PID Controller1/N Gain'
//  '<S69>'  : 'positionControl/position control/PID Controller1/P Copy'
//  '<S70>'  : 'positionControl/position control/PID Controller1/Parallel P Gain'
//  '<S71>'  : 'positionControl/position control/PID Controller1/Reset Signal'
//  '<S72>'  : 'positionControl/position control/PID Controller1/Saturation'
//  '<S73>'  : 'positionControl/position control/PID Controller1/Saturation Fdbk'
//  '<S74>'  : 'positionControl/position control/PID Controller1/Sum'
//  '<S75>'  : 'positionControl/position control/PID Controller1/Sum Fdbk'
//  '<S76>'  : 'positionControl/position control/PID Controller1/Tracking Mode'
//  '<S77>'  : 'positionControl/position control/PID Controller1/Tracking Mode Sum'
//  '<S78>'  : 'positionControl/position control/PID Controller1/Tsamp - Integral'
//  '<S79>'  : 'positionControl/position control/PID Controller1/Tsamp - Ngain'
//  '<S80>'  : 'positionControl/position control/PID Controller1/postSat Signal'
//  '<S81>'  : 'positionControl/position control/PID Controller1/preSat Signal'
//  '<S82>'  : 'positionControl/position control/PID Controller1/Anti-windup/Back Calculation'
//  '<S83>'  : 'positionControl/position control/PID Controller1/D Gain/Internal Parameters'
//  '<S84>'  : 'positionControl/position control/PID Controller1/Filter/Disc. Forward Euler Filter'
//  '<S85>'  : 'positionControl/position control/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S86>'  : 'positionControl/position control/PID Controller1/I Gain/Internal Parameters'
//  '<S87>'  : 'positionControl/position control/PID Controller1/Ideal P Gain/Passthrough'
//  '<S88>'  : 'positionControl/position control/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S89>'  : 'positionControl/position control/PID Controller1/Integrator/Discrete'
//  '<S90>'  : 'positionControl/position control/PID Controller1/Integrator ICs/Internal IC'
//  '<S91>'  : 'positionControl/position control/PID Controller1/N Copy/Disabled'
//  '<S92>'  : 'positionControl/position control/PID Controller1/N Gain/Internal Parameters'
//  '<S93>'  : 'positionControl/position control/PID Controller1/P Copy/Disabled'
//  '<S94>'  : 'positionControl/position control/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S95>'  : 'positionControl/position control/PID Controller1/Reset Signal/Disabled'
//  '<S96>'  : 'positionControl/position control/PID Controller1/Saturation/Enabled'
//  '<S97>'  : 'positionControl/position control/PID Controller1/Saturation Fdbk/Disabled'
//  '<S98>'  : 'positionControl/position control/PID Controller1/Sum/Sum_PID'
//  '<S99>'  : 'positionControl/position control/PID Controller1/Sum Fdbk/Disabled'
//  '<S100>' : 'positionControl/position control/PID Controller1/Tracking Mode/Disabled'
//  '<S101>' : 'positionControl/position control/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S102>' : 'positionControl/position control/PID Controller1/Tsamp - Integral/Passthrough'
//  '<S103>' : 'positionControl/position control/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S104>' : 'positionControl/position control/PID Controller1/postSat Signal/Forward_Path'
//  '<S105>' : 'positionControl/position control/PID Controller1/preSat Signal/Forward_Path'
//  '<S106>' : 'positionControl/position control/PID Controller3/Anti-windup'
//  '<S107>' : 'positionControl/position control/PID Controller3/D Gain'
//  '<S108>' : 'positionControl/position control/PID Controller3/Filter'
//  '<S109>' : 'positionControl/position control/PID Controller3/Filter ICs'
//  '<S110>' : 'positionControl/position control/PID Controller3/I Gain'
//  '<S111>' : 'positionControl/position control/PID Controller3/Ideal P Gain'
//  '<S112>' : 'positionControl/position control/PID Controller3/Ideal P Gain Fdbk'
//  '<S113>' : 'positionControl/position control/PID Controller3/Integrator'
//  '<S114>' : 'positionControl/position control/PID Controller3/Integrator ICs'
//  '<S115>' : 'positionControl/position control/PID Controller3/N Copy'
//  '<S116>' : 'positionControl/position control/PID Controller3/N Gain'
//  '<S117>' : 'positionControl/position control/PID Controller3/P Copy'
//  '<S118>' : 'positionControl/position control/PID Controller3/Parallel P Gain'
//  '<S119>' : 'positionControl/position control/PID Controller3/Reset Signal'
//  '<S120>' : 'positionControl/position control/PID Controller3/Saturation'
//  '<S121>' : 'positionControl/position control/PID Controller3/Saturation Fdbk'
//  '<S122>' : 'positionControl/position control/PID Controller3/Sum'
//  '<S123>' : 'positionControl/position control/PID Controller3/Sum Fdbk'
//  '<S124>' : 'positionControl/position control/PID Controller3/Tracking Mode'
//  '<S125>' : 'positionControl/position control/PID Controller3/Tracking Mode Sum'
//  '<S126>' : 'positionControl/position control/PID Controller3/Tsamp - Integral'
//  '<S127>' : 'positionControl/position control/PID Controller3/Tsamp - Ngain'
//  '<S128>' : 'positionControl/position control/PID Controller3/postSat Signal'
//  '<S129>' : 'positionControl/position control/PID Controller3/preSat Signal'
//  '<S130>' : 'positionControl/position control/PID Controller3/Anti-windup/Disc. Clamping Parallel'
//  '<S131>' : 'positionControl/position control/PID Controller3/D Gain/Internal Parameters'
//  '<S132>' : 'positionControl/position control/PID Controller3/Filter/Differentiator'
//  '<S133>' : 'positionControl/position control/PID Controller3/Filter/Differentiator/Tsamp'
//  '<S134>' : 'positionControl/position control/PID Controller3/Filter/Differentiator/Tsamp/Internal Ts'
//  '<S135>' : 'positionControl/position control/PID Controller3/Filter ICs/Internal IC - Differentiator'
//  '<S136>' : 'positionControl/position control/PID Controller3/I Gain/Internal Parameters'
//  '<S137>' : 'positionControl/position control/PID Controller3/Ideal P Gain/Passthrough'
//  '<S138>' : 'positionControl/position control/PID Controller3/Ideal P Gain Fdbk/Disabled'
//  '<S139>' : 'positionControl/position control/PID Controller3/Integrator/Discrete'
//  '<S140>' : 'positionControl/position control/PID Controller3/Integrator ICs/Internal IC'
//  '<S141>' : 'positionControl/position control/PID Controller3/N Copy/Disabled wSignal Specification'
//  '<S142>' : 'positionControl/position control/PID Controller3/N Gain/Passthrough'
//  '<S143>' : 'positionControl/position control/PID Controller3/P Copy/Disabled'
//  '<S144>' : 'positionControl/position control/PID Controller3/Parallel P Gain/Internal Parameters'
//  '<S145>' : 'positionControl/position control/PID Controller3/Reset Signal/Disabled'
//  '<S146>' : 'positionControl/position control/PID Controller3/Saturation/Enabled'
//  '<S147>' : 'positionControl/position control/PID Controller3/Saturation Fdbk/Disabled'
//  '<S148>' : 'positionControl/position control/PID Controller3/Sum/Sum_PID'
//  '<S149>' : 'positionControl/position control/PID Controller3/Sum Fdbk/Disabled'
//  '<S150>' : 'positionControl/position control/PID Controller3/Tracking Mode/Disabled'
//  '<S151>' : 'positionControl/position control/PID Controller3/Tracking Mode Sum/Passthrough'
//  '<S152>' : 'positionControl/position control/PID Controller3/Tsamp - Integral/Passthrough'
//  '<S153>' : 'positionControl/position control/PID Controller3/Tsamp - Ngain/Passthrough'
//  '<S154>' : 'positionControl/position control/PID Controller3/postSat Signal/Forward_Path'
//  '<S155>' : 'positionControl/position control/PID Controller3/preSat Signal/Forward_Path'
//  '<S156>' : 'positionControl/position control/PID Controller4/Anti-windup'
//  '<S157>' : 'positionControl/position control/PID Controller4/D Gain'
//  '<S158>' : 'positionControl/position control/PID Controller4/Filter'
//  '<S159>' : 'positionControl/position control/PID Controller4/Filter ICs'
//  '<S160>' : 'positionControl/position control/PID Controller4/I Gain'
//  '<S161>' : 'positionControl/position control/PID Controller4/Ideal P Gain'
//  '<S162>' : 'positionControl/position control/PID Controller4/Ideal P Gain Fdbk'
//  '<S163>' : 'positionControl/position control/PID Controller4/Integrator'
//  '<S164>' : 'positionControl/position control/PID Controller4/Integrator ICs'
//  '<S165>' : 'positionControl/position control/PID Controller4/N Copy'
//  '<S166>' : 'positionControl/position control/PID Controller4/N Gain'
//  '<S167>' : 'positionControl/position control/PID Controller4/P Copy'
//  '<S168>' : 'positionControl/position control/PID Controller4/Parallel P Gain'
//  '<S169>' : 'positionControl/position control/PID Controller4/Reset Signal'
//  '<S170>' : 'positionControl/position control/PID Controller4/Saturation'
//  '<S171>' : 'positionControl/position control/PID Controller4/Saturation Fdbk'
//  '<S172>' : 'positionControl/position control/PID Controller4/Sum'
//  '<S173>' : 'positionControl/position control/PID Controller4/Sum Fdbk'
//  '<S174>' : 'positionControl/position control/PID Controller4/Tracking Mode'
//  '<S175>' : 'positionControl/position control/PID Controller4/Tracking Mode Sum'
//  '<S176>' : 'positionControl/position control/PID Controller4/Tsamp - Integral'
//  '<S177>' : 'positionControl/position control/PID Controller4/Tsamp - Ngain'
//  '<S178>' : 'positionControl/position control/PID Controller4/postSat Signal'
//  '<S179>' : 'positionControl/position control/PID Controller4/preSat Signal'
//  '<S180>' : 'positionControl/position control/PID Controller4/Anti-windup/Passthrough'
//  '<S181>' : 'positionControl/position control/PID Controller4/D Gain/Internal Parameters'
//  '<S182>' : 'positionControl/position control/PID Controller4/Filter/Disc. Forward Euler Filter'
//  '<S183>' : 'positionControl/position control/PID Controller4/Filter ICs/Internal IC - Filter'
//  '<S184>' : 'positionControl/position control/PID Controller4/I Gain/Internal Parameters'
//  '<S185>' : 'positionControl/position control/PID Controller4/Ideal P Gain/Passthrough'
//  '<S186>' : 'positionControl/position control/PID Controller4/Ideal P Gain Fdbk/Disabled'
//  '<S187>' : 'positionControl/position control/PID Controller4/Integrator/Discrete'
//  '<S188>' : 'positionControl/position control/PID Controller4/Integrator ICs/Internal IC'
//  '<S189>' : 'positionControl/position control/PID Controller4/N Copy/Disabled'
//  '<S190>' : 'positionControl/position control/PID Controller4/N Gain/Internal Parameters'
//  '<S191>' : 'positionControl/position control/PID Controller4/P Copy/Disabled'
//  '<S192>' : 'positionControl/position control/PID Controller4/Parallel P Gain/Internal Parameters'
//  '<S193>' : 'positionControl/position control/PID Controller4/Reset Signal/Disabled'
//  '<S194>' : 'positionControl/position control/PID Controller4/Saturation/Enabled'
//  '<S195>' : 'positionControl/position control/PID Controller4/Saturation Fdbk/Disabled'
//  '<S196>' : 'positionControl/position control/PID Controller4/Sum/Sum_PID'
//  '<S197>' : 'positionControl/position control/PID Controller4/Sum Fdbk/Disabled'
//  '<S198>' : 'positionControl/position control/PID Controller4/Tracking Mode/Disabled'
//  '<S199>' : 'positionControl/position control/PID Controller4/Tracking Mode Sum/Passthrough'
//  '<S200>' : 'positionControl/position control/PID Controller4/Tsamp - Integral/Passthrough'
//  '<S201>' : 'positionControl/position control/PID Controller4/Tsamp - Ngain/Passthrough'
//  '<S202>' : 'positionControl/position control/PID Controller4/postSat Signal/Forward_Path'
//  '<S203>' : 'positionControl/position control/PID Controller4/preSat Signal/Forward_Path'
//  '<S204>' : 'positionControl/position control/PID Controller5/Anti-windup'
//  '<S205>' : 'positionControl/position control/PID Controller5/D Gain'
//  '<S206>' : 'positionControl/position control/PID Controller5/Filter'
//  '<S207>' : 'positionControl/position control/PID Controller5/Filter ICs'
//  '<S208>' : 'positionControl/position control/PID Controller5/I Gain'
//  '<S209>' : 'positionControl/position control/PID Controller5/Ideal P Gain'
//  '<S210>' : 'positionControl/position control/PID Controller5/Ideal P Gain Fdbk'
//  '<S211>' : 'positionControl/position control/PID Controller5/Integrator'
//  '<S212>' : 'positionControl/position control/PID Controller5/Integrator ICs'
//  '<S213>' : 'positionControl/position control/PID Controller5/N Copy'
//  '<S214>' : 'positionControl/position control/PID Controller5/N Gain'
//  '<S215>' : 'positionControl/position control/PID Controller5/P Copy'
//  '<S216>' : 'positionControl/position control/PID Controller5/Parallel P Gain'
//  '<S217>' : 'positionControl/position control/PID Controller5/Reset Signal'
//  '<S218>' : 'positionControl/position control/PID Controller5/Saturation'
//  '<S219>' : 'positionControl/position control/PID Controller5/Saturation Fdbk'
//  '<S220>' : 'positionControl/position control/PID Controller5/Sum'
//  '<S221>' : 'positionControl/position control/PID Controller5/Sum Fdbk'
//  '<S222>' : 'positionControl/position control/PID Controller5/Tracking Mode'
//  '<S223>' : 'positionControl/position control/PID Controller5/Tracking Mode Sum'
//  '<S224>' : 'positionControl/position control/PID Controller5/Tsamp - Integral'
//  '<S225>' : 'positionControl/position control/PID Controller5/Tsamp - Ngain'
//  '<S226>' : 'positionControl/position control/PID Controller5/postSat Signal'
//  '<S227>' : 'positionControl/position control/PID Controller5/preSat Signal'
//  '<S228>' : 'positionControl/position control/PID Controller5/Anti-windup/Back Calculation'
//  '<S229>' : 'positionControl/position control/PID Controller5/D Gain/Internal Parameters'
//  '<S230>' : 'positionControl/position control/PID Controller5/Filter/Disc. Forward Euler Filter'
//  '<S231>' : 'positionControl/position control/PID Controller5/Filter ICs/Internal IC - Filter'
//  '<S232>' : 'positionControl/position control/PID Controller5/I Gain/Internal Parameters'
//  '<S233>' : 'positionControl/position control/PID Controller5/Ideal P Gain/Passthrough'
//  '<S234>' : 'positionControl/position control/PID Controller5/Ideal P Gain Fdbk/Disabled'
//  '<S235>' : 'positionControl/position control/PID Controller5/Integrator/Discrete'
//  '<S236>' : 'positionControl/position control/PID Controller5/Integrator ICs/Internal IC'
//  '<S237>' : 'positionControl/position control/PID Controller5/N Copy/Disabled'
//  '<S238>' : 'positionControl/position control/PID Controller5/N Gain/Internal Parameters'
//  '<S239>' : 'positionControl/position control/PID Controller5/P Copy/Disabled'
//  '<S240>' : 'positionControl/position control/PID Controller5/Parallel P Gain/Internal Parameters'
//  '<S241>' : 'positionControl/position control/PID Controller5/Reset Signal/Disabled'
//  '<S242>' : 'positionControl/position control/PID Controller5/Saturation/Enabled'
//  '<S243>' : 'positionControl/position control/PID Controller5/Saturation Fdbk/Disabled'
//  '<S244>' : 'positionControl/position control/PID Controller5/Sum/Sum_PID'
//  '<S245>' : 'positionControl/position control/PID Controller5/Sum Fdbk/Disabled'
//  '<S246>' : 'positionControl/position control/PID Controller5/Tracking Mode/Disabled'
//  '<S247>' : 'positionControl/position control/PID Controller5/Tracking Mode Sum/Passthrough'
//  '<S248>' : 'positionControl/position control/PID Controller5/Tsamp - Integral/Passthrough'
//  '<S249>' : 'positionControl/position control/PID Controller5/Tsamp - Ngain/Passthrough'
//  '<S250>' : 'positionControl/position control/PID Controller5/postSat Signal/Forward_Path'
//  '<S251>' : 'positionControl/position control/PID Controller5/preSat Signal/Forward_Path'
//  '<S252>' : 'positionControl/position control/ZPostoVel/Anti-windup'
//  '<S253>' : 'positionControl/position control/ZPostoVel/D Gain'
//  '<S254>' : 'positionControl/position control/ZPostoVel/Filter'
//  '<S255>' : 'positionControl/position control/ZPostoVel/Filter ICs'
//  '<S256>' : 'positionControl/position control/ZPostoVel/I Gain'
//  '<S257>' : 'positionControl/position control/ZPostoVel/Ideal P Gain'
//  '<S258>' : 'positionControl/position control/ZPostoVel/Ideal P Gain Fdbk'
//  '<S259>' : 'positionControl/position control/ZPostoVel/Integrator'
//  '<S260>' : 'positionControl/position control/ZPostoVel/Integrator ICs'
//  '<S261>' : 'positionControl/position control/ZPostoVel/N Copy'
//  '<S262>' : 'positionControl/position control/ZPostoVel/N Gain'
//  '<S263>' : 'positionControl/position control/ZPostoVel/P Copy'
//  '<S264>' : 'positionControl/position control/ZPostoVel/Parallel P Gain'
//  '<S265>' : 'positionControl/position control/ZPostoVel/Reset Signal'
//  '<S266>' : 'positionControl/position control/ZPostoVel/Saturation'
//  '<S267>' : 'positionControl/position control/ZPostoVel/Saturation Fdbk'
//  '<S268>' : 'positionControl/position control/ZPostoVel/Sum'
//  '<S269>' : 'positionControl/position control/ZPostoVel/Sum Fdbk'
//  '<S270>' : 'positionControl/position control/ZPostoVel/Tracking Mode'
//  '<S271>' : 'positionControl/position control/ZPostoVel/Tracking Mode Sum'
//  '<S272>' : 'positionControl/position control/ZPostoVel/Tsamp - Integral'
//  '<S273>' : 'positionControl/position control/ZPostoVel/Tsamp - Ngain'
//  '<S274>' : 'positionControl/position control/ZPostoVel/postSat Signal'
//  '<S275>' : 'positionControl/position control/ZPostoVel/preSat Signal'
//  '<S276>' : 'positionControl/position control/ZPostoVel/Anti-windup/Disc. Clamping Parallel'
//  '<S277>' : 'positionControl/position control/ZPostoVel/D Gain/Internal Parameters'
//  '<S278>' : 'positionControl/position control/ZPostoVel/Filter/Disc. Forward Euler Filter'
//  '<S279>' : 'positionControl/position control/ZPostoVel/Filter ICs/Internal IC - Filter'
//  '<S280>' : 'positionControl/position control/ZPostoVel/I Gain/Internal Parameters'
//  '<S281>' : 'positionControl/position control/ZPostoVel/Ideal P Gain/Passthrough'
//  '<S282>' : 'positionControl/position control/ZPostoVel/Ideal P Gain Fdbk/Disabled'
//  '<S283>' : 'positionControl/position control/ZPostoVel/Integrator/Discrete'
//  '<S284>' : 'positionControl/position control/ZPostoVel/Integrator ICs/Internal IC'
//  '<S285>' : 'positionControl/position control/ZPostoVel/N Copy/Disabled'
//  '<S286>' : 'positionControl/position control/ZPostoVel/N Gain/Internal Parameters'
//  '<S287>' : 'positionControl/position control/ZPostoVel/P Copy/Disabled'
//  '<S288>' : 'positionControl/position control/ZPostoVel/Parallel P Gain/Internal Parameters'
//  '<S289>' : 'positionControl/position control/ZPostoVel/Reset Signal/Disabled'
//  '<S290>' : 'positionControl/position control/ZPostoVel/Saturation/Enabled'
//  '<S291>' : 'positionControl/position control/ZPostoVel/Saturation Fdbk/Disabled'
//  '<S292>' : 'positionControl/position control/ZPostoVel/Sum/Sum_PID'
//  '<S293>' : 'positionControl/position control/ZPostoVel/Sum Fdbk/Disabled'
//  '<S294>' : 'positionControl/position control/ZPostoVel/Tracking Mode/Disabled'
//  '<S295>' : 'positionControl/position control/ZPostoVel/Tracking Mode Sum/Passthrough'
//  '<S296>' : 'positionControl/position control/ZPostoVel/Tsamp - Integral/Passthrough'
//  '<S297>' : 'positionControl/position control/ZPostoVel/Tsamp - Ngain/Passthrough'
//  '<S298>' : 'positionControl/position control/ZPostoVel/postSat Signal/Forward_Path'
//  '<S299>' : 'positionControl/position control/ZPostoVel/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_positionControl_h_

//
// File trailer for generated code.
//
// [EOF]
//
