//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl.h
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
                                          //  Referenced by: '<S179>/Derivative Gain'

extern real_T pos_y_I;                 // Variable: pos_y_I
                                          //  Referenced by: '<S182>/Integral Gain'

extern real_T pos_y_P;                 // Variable: pos_y_P
                                          //  Referenced by: '<S190>/Proportional Gain'

extern real_T pos_y_vel_D;             // Variable: pos_y_vel_D
                                          //  Referenced by: '<S227>/Derivative Gain'

extern real_T pos_y_vel_I;             // Variable: pos_y_vel_I
                                          //  Referenced by: '<S230>/Integral Gain'

extern real_T pos_y_vel_P;             // Variable: pos_y_vel_P
                                          //  Referenced by: '<S238>/Proportional Gain'

extern real_T pos_z_D;                 // Variable: pos_z_D
                                          //  Referenced by: '<S275>/Derivative Gain'

extern real_T pos_z_I;                 // Variable: pos_z_I
                                          //  Referenced by: '<S278>/Integral Gain'

extern real_T pos_z_P;                 // Variable: pos_z_P
                                          //  Referenced by: '<S286>/Proportional Gain'

extern real_T pos_z_vel_D;             // Variable: pos_z_vel_D
                                          //  Referenced by: '<S131>/Derivative Gain'

extern real_T pos_z_vel_I;             // Variable: pos_z_vel_I
                                          //  Referenced by: '<S134>/Integral Gain'

extern real_T pos_z_vel_P;             // Variable: pos_z_vel_P
                                          //  Referenced by: '<S142>/Proportional Gain'

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
    real_T ProportionalGain_p;         // '<S190>/Proportional Gain'
    real_T Integrator_f;               // '<S185>/Integrator'
    real_T DerivativeGain_n;           // '<S179>/Derivative Gain'
    real_T Filter_p;                   // '<S180>/Filter'
    real_T SumD_k;                     // '<S180>/SumD'
    real_T FilterCoefficient_n;        // '<S188>/Filter Coefficient'
    real_T Sum_k;                      // '<S194>/Sum'
    real_T Saturation_o;               // '<S192>/Saturation'
    real_T Add1[2];                    // '<S1>/Add1'
    real_T vel_error[2];               // '<S1>/Matrix Multiply'
    real_T ProportionalGain_m;         // '<S238>/Proportional Gain'
    real_T Integrator_h;               // '<S233>/Integrator'
    real_T DerivativeGain_c;           // '<S227>/Derivative Gain'
    real_T Filter_g;                   // '<S228>/Filter'
    real_T SumD_f;                     // '<S228>/SumD'
    real_T FilterCoefficient_e;        // '<S236>/Filter Coefficient'
    real_T Sum_m;                      // '<S242>/Sum'
    real_T Saturation_l;               // '<S240>/Saturation'
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
    real_T ProportionalGain_j;         // '<S286>/Proportional Gain'
    real_T Integrator_ca;              // '<S281>/Integrator'
    real_T DerivativeGain_f;           // '<S275>/Derivative Gain'
    real_T Filter_gq;                  // '<S276>/Filter'
    real_T SumD_d;                     // '<S276>/SumD'
    real_T FilterCoefficient_j;        // '<S284>/Filter Coefficient'
    real_T Sum_d;                      // '<S290>/Sum'
    real_T Saturation_jh;              // '<S288>/Saturation'
    real_T Gain3;                      // '<S1>/Gain3'
    real_T Add3;                       // '<S1>/Add3'
    real_T ProportionalGain_k;         // '<S142>/Proportional Gain'
    real_T Integrator_p;               // '<S137>/Integrator'
    real_T DerivativeGain_pu;          // '<S131>/Derivative Gain'
    real_T Filter_m;                   // '<S132>/Filter'
    real_T SumD_b;                     // '<S132>/SumD'
    real_T FilterCoefficient_a;        // '<S140>/Filter Coefficient'
    real_T Sum_c;                      // '<S146>/Sum'
    real_T Saturation_li;              // '<S144>/Saturation'
    real_T Sum1;                       // '<S1>/Sum1'
    real_T Saturation_jb;              // '<S1>/Saturation'
    real_T ZeroGain;                   // '<S34>/ZeroGain'
    real_T DeadZone;                   // '<S34>/DeadZone'
    real_T SignPreSat;                 // '<S34>/SignPreSat'
    real_T IntegralGain;               // '<S38>/Integral Gain'
    real_T SignPreIntegrator;          // '<S34>/SignPreIntegrator'
    real_T Switch;                     // '<S34>/Switch'
    real_T ZeroGain_h;                 // '<S82>/ZeroGain'
    real_T DeadZone_p;                 // '<S82>/DeadZone'
    real_T SignPreSat_i;               // '<S82>/SignPreSat'
    real_T IntegralGain_k;             // '<S86>/Integral Gain'
    real_T SignPreIntegrator_p;        // '<S82>/SignPreIntegrator'
    real_T Switch_b;                   // '<S82>/Switch'
    real_T ZeroGain_o;                 // '<S178>/ZeroGain'
    real_T DeadZone_g;                 // '<S178>/DeadZone'
    real_T SignPreSat_ij;              // '<S178>/SignPreSat'
    real_T IntegralGain_o;             // '<S182>/Integral Gain'
    real_T SignPreIntegrator_d;        // '<S178>/SignPreIntegrator'
    real_T Switch_p;                   // '<S178>/Switch'
    real_T ZeroGain_b;                 // '<S226>/ZeroGain'
    real_T DeadZone_m;                 // '<S226>/DeadZone'
    real_T SignPreSat_n;               // '<S226>/SignPreSat'
    real_T IntegralGain_b;             // '<S230>/Integral Gain'
    real_T SignPreIntegrator_n;        // '<S226>/SignPreIntegrator'
    real_T Switch_m;                   // '<S226>/Switch'
    real_T ZeroGain_e;                 // '<S130>/ZeroGain'
    real_T DeadZone_e;                 // '<S130>/DeadZone'
    real_T SignPreSat_h;               // '<S130>/SignPreSat'
    real_T IntegralGain_l;             // '<S134>/Integral Gain'
    real_T SignPreIntegrator_dl;       // '<S130>/SignPreIntegrator'
    real_T Switch_e;                   // '<S130>/Switch'
    real_T ZeroGain_a;                 // '<S274>/ZeroGain'
    real_T DeadZone_b;                 // '<S274>/DeadZone'
    real_T SignPreSat_ir;              // '<S274>/SignPreSat'
    real_T IntegralGain_g;             // '<S278>/Integral Gain'
    real_T SignPreIntegrator_h;        // '<S274>/SignPreIntegrator'
    real_T Switch_h;                   // '<S274>/Switch'
    real32_T Sum_my;                   // '<S1>/Sum'
    real32_T y;                        // '<S1>/MATLAB Function'
    int8_T DataTypeConv1;              // '<S34>/DataTypeConv1'
    int8_T DataTypeConv2;              // '<S34>/DataTypeConv2'
    int8_T DataTypeConv1_b;            // '<S82>/DataTypeConv1'
    int8_T DataTypeConv2_o;            // '<S82>/DataTypeConv2'
    int8_T DataTypeConv1_l;            // '<S178>/DataTypeConv1'
    int8_T DataTypeConv2_d;            // '<S178>/DataTypeConv2'
    int8_T DataTypeConv1_e;            // '<S226>/DataTypeConv1'
    int8_T DataTypeConv2_a;            // '<S226>/DataTypeConv2'
    int8_T DataTypeConv1_m;            // '<S130>/DataTypeConv1'
    int8_T DataTypeConv2_j;            // '<S130>/DataTypeConv2'
    int8_T DataTypeConv1_es;           // '<S274>/DataTypeConv1'
    int8_T DataTypeConv2_m;            // '<S274>/DataTypeConv2'
    boolean_T NotEqual;                // '<S34>/NotEqual'
    boolean_T Equal1;                  // '<S34>/Equal1'
    boolean_T AND3;                    // '<S34>/AND3'
    boolean_T NotEqual_k;              // '<S82>/NotEqual'
    boolean_T Equal1_d;                // '<S82>/Equal1'
    boolean_T AND3_a;                  // '<S82>/AND3'
    boolean_T NotEqual_e;              // '<S178>/NotEqual'
    boolean_T Equal1_a;                // '<S178>/Equal1'
    boolean_T AND3_o;                  // '<S178>/AND3'
    boolean_T NotEqual_p;              // '<S226>/NotEqual'
    boolean_T Equal1_c;                // '<S226>/Equal1'
    boolean_T AND3_n;                  // '<S226>/AND3'
    boolean_T NotEqual_o;              // '<S130>/NotEqual'
    boolean_T Equal1_i;                // '<S130>/Equal1'
    boolean_T AND3_nv;                 // '<S130>/AND3'
    boolean_T NotEqual_i;              // '<S274>/NotEqual'
    boolean_T Equal1_l;                // '<S274>/Equal1'
    boolean_T AND3_m;                  // '<S274>/AND3'
  } B_positionControl_T;

  // Block states (default storage) for system '<Root>'
  typedef struct {
    real_T Integrator_DSTATE;          // '<S41>/Integrator'
    real_T Filter_DSTATE;              // '<S36>/Filter'
    real_T Integrator_DSTATE_k;        // '<S185>/Integrator'
    real_T Filter_DSTATE_m;            // '<S180>/Filter'
    real_T Integrator_DSTATE_f;        // '<S233>/Integrator'
    real_T Filter_DSTATE_j;            // '<S228>/Filter'
    real_T Integrator_DSTATE_m;        // '<S89>/Integrator'
    real_T Filter_DSTATE_d;            // '<S84>/Filter'
    real_T Integrator_DSTATE_p;        // '<S281>/Integrator'
    real_T Filter_DSTATE_mo;           // '<S276>/Filter'
    real_T Integrator_DSTATE_b;        // '<S137>/Integrator'
    real_T Filter_DSTATE_e;            // '<S132>/Filter'
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
                                          //    '<S34>/DeadZone'
                                          //    '<S48>/Saturation'
                                          //    '<S178>/DeadZone'
                                          //    '<S192>/Saturation'

    real_T vel_climbMax;               // Variable: vel_climbMax
                                          //  Referenced by:
                                          //    '<S274>/DeadZone'
                                          //    '<S288>/Saturation'

    real_T vel_descentMax;             // Variable: vel_descentMax
                                          //  Referenced by:
                                          //    '<S274>/DeadZone'
                                          //    '<S288>/Saturation'

    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S36>/Filter'

    real_T PIDController4_InitialCondition;
                              // Mask Parameter: PIDController4_InitialCondition
                                 //  Referenced by: '<S180>/Filter'

    real_T PIDController5_InitialCondition;
                              // Mask Parameter: PIDController5_InitialCondition
                                 //  Referenced by: '<S228>/Filter'

    real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S84>/Filter'

    real_T ZPostoVel_InitialConditionForFi;
                              // Mask Parameter: ZPostoVel_InitialConditionForFi
                                 //  Referenced by: '<S276>/Filter'

    real_T PIDController3_InitialCondition;
                              // Mask Parameter: PIDController3_InitialCondition
                                 //  Referenced by: '<S132>/Filter'

    real_T PIDController_InitialConditio_c;
                              // Mask Parameter: PIDController_InitialConditio_c
                                 //  Referenced by: '<S41>/Integrator'

    real_T PIDController4_InitialConditi_i;
                              // Mask Parameter: PIDController4_InitialConditi_i
                                 //  Referenced by: '<S185>/Integrator'

    real_T PIDController5_InitialConditi_c;
                              // Mask Parameter: PIDController5_InitialConditi_c
                                 //  Referenced by: '<S233>/Integrator'

    real_T PIDController1_InitialConditi_a;
                              // Mask Parameter: PIDController1_InitialConditi_a
                                 //  Referenced by: '<S89>/Integrator'

    real_T ZPostoVel_InitialConditionForIn;
                              // Mask Parameter: ZPostoVel_InitialConditionForIn
                                 //  Referenced by: '<S281>/Integrator'

    real_T PIDController3_InitialConditi_d;
                              // Mask Parameter: PIDController3_InitialConditi_d
                                 //  Referenced by: '<S137>/Integrator'

    real_T PIDController5_LowerSaturationL;
                              // Mask Parameter: PIDController5_LowerSaturationL
                                 //  Referenced by:
                                 //    '<S226>/DeadZone'
                                 //    '<S240>/Saturation'

    real_T PIDController1_LowerSaturationL;
                              // Mask Parameter: PIDController1_LowerSaturationL
                                 //  Referenced by:
                                 //    '<S82>/DeadZone'
                                 //    '<S96>/Saturation'

    real_T PIDController3_LowerSaturationL;
                              // Mask Parameter: PIDController3_LowerSaturationL
                                 //  Referenced by:
                                 //    '<S130>/DeadZone'
                                 //    '<S144>/Saturation'

    real_T PIDController_N;            // Mask Parameter: PIDController_N
                                          //  Referenced by: '<S44>/Filter Coefficient'

    real_T PIDController4_N;           // Mask Parameter: PIDController4_N
                                          //  Referenced by: '<S188>/Filter Coefficient'

    real_T PIDController5_N;           // Mask Parameter: PIDController5_N
                                          //  Referenced by: '<S236>/Filter Coefficient'

    real_T PIDController1_N;           // Mask Parameter: PIDController1_N
                                          //  Referenced by: '<S92>/Filter Coefficient'

    real_T ZPostoVel_N;                // Mask Parameter: ZPostoVel_N
                                          //  Referenced by: '<S284>/Filter Coefficient'

    real_T PIDController3_N;           // Mask Parameter: PIDController3_N
                                          //  Referenced by: '<S140>/Filter Coefficient'

    real_T PIDController5_UpperSaturationL;
                              // Mask Parameter: PIDController5_UpperSaturationL
                                 //  Referenced by:
                                 //    '<S226>/DeadZone'
                                 //    '<S240>/Saturation'

    real_T PIDController1_UpperSaturationL;
                              // Mask Parameter: PIDController1_UpperSaturationL
                                 //  Referenced by:
                                 //    '<S82>/DeadZone'
                                 //    '<S96>/Saturation'

    real_T PIDController3_UpperSaturationL;
                              // Mask Parameter: PIDController3_UpperSaturationL
                                 //  Referenced by:
                                 //    '<S130>/DeadZone'
                                 //    '<S144>/Saturation'

    real_T Constant1_Value;            // Expression: 0
                                          //  Referenced by: '<S34>/Constant1'

    real_T Constant1_Value_m;          // Expression: 0
                                          //  Referenced by: '<S82>/Constant1'

    real_T Constant1_Value_l;          // Expression: 0
                                          //  Referenced by: '<S178>/Constant1'

    real_T Constant1_Value_n;          // Expression: 0
                                          //  Referenced by: '<S226>/Constant1'

    real_T Constant1_Value_k;          // Expression: 0
                                          //  Referenced by: '<S130>/Constant1'

    real_T Constant1_Value_ke;         // Expression: 0
                                          //  Referenced by: '<S274>/Constant1'

    real_T Gain_Gain;                  // Expression: -1
                                          //  Referenced by: '<S9>/Gain'

    real_T Integrator_gainval;         // Computed Parameter: Integrator_gainval
                                          //  Referenced by: '<S41>/Integrator'

    real_T Filter_gainval;             // Computed Parameter: Filter_gainval
                                          //  Referenced by: '<S36>/Filter'

    real_T Integrator_gainval_l;     // Computed Parameter: Integrator_gainval_l
                                        //  Referenced by: '<S185>/Integrator'

    real_T Filter_gainval_l;           // Computed Parameter: Filter_gainval_l
                                          //  Referenced by: '<S180>/Filter'

    real_T Integrator_gainval_k;     // Computed Parameter: Integrator_gainval_k
                                        //  Referenced by: '<S233>/Integrator'

    real_T Filter_gainval_i;           // Computed Parameter: Filter_gainval_i
                                          //  Referenced by: '<S228>/Filter'

    real_T Integrator_gainval_lc;   // Computed Parameter: Integrator_gainval_lc
                                       //  Referenced by: '<S89>/Integrator'

    real_T Filter_gainval_l5;          // Computed Parameter: Filter_gainval_l5
                                          //  Referenced by: '<S84>/Filter'

    real_T Gain1_Gain;                 // Expression: -1
                                          //  Referenced by: '<S1>/Gain1'

    real_T Gain2_Gain;                 // Expression: -1
                                          //  Referenced by: '<S1>/Gain2'

    real_T Integrator_gainval_j;     // Computed Parameter: Integrator_gainval_j
                                        //  Referenced by: '<S281>/Integrator'

    real_T Filter_gainval_c;           // Computed Parameter: Filter_gainval_c
                                          //  Referenced by: '<S276>/Filter'

    real_T Gain3_Gain;                 // Expression: -1
                                          //  Referenced by: '<S1>/Gain3'

    real_T Integrator_gainval_a;     // Computed Parameter: Integrator_gainval_a
                                        //  Referenced by: '<S137>/Integrator'

    real_T Filter_gainval_g;           // Computed Parameter: Filter_gainval_g
                                          //  Referenced by: '<S132>/Filter'

    real_T Saturation_UpperSat;        // Expression: 1
                                          //  Referenced by: '<S1>/Saturation'

    real_T Saturation_LowerSat;        // Expression: 0
                                          //  Referenced by: '<S1>/Saturation'

    real_T ZeroGain_Gain;              // Expression: 0
                                          //  Referenced by: '<S34>/ZeroGain'

    real_T ZeroGain_Gain_c;            // Expression: 0
                                          //  Referenced by: '<S82>/ZeroGain'

    real_T ZeroGain_Gain_j;            // Expression: 0
                                          //  Referenced by: '<S178>/ZeroGain'

    real_T ZeroGain_Gain_m;            // Expression: 0
                                          //  Referenced by: '<S226>/ZeroGain'

    real_T ZeroGain_Gain_h;            // Expression: 0
                                          //  Referenced by: '<S130>/ZeroGain'

    real_T ZeroGain_Gain_b;            // Expression: 0
                                          //  Referenced by: '<S274>/ZeroGain'

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
//  '<S34>'  : 'positionControl/position control/PID Controller/Anti-windup/Disc. Clamping Parallel'
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
//  '<S82>'  : 'positionControl/position control/PID Controller1/Anti-windup/Disc. Clamping Parallel'
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
//  '<S132>' : 'positionControl/position control/PID Controller3/Filter/Disc. Forward Euler Filter'
//  '<S133>' : 'positionControl/position control/PID Controller3/Filter ICs/Internal IC - Filter'
//  '<S134>' : 'positionControl/position control/PID Controller3/I Gain/Internal Parameters'
//  '<S135>' : 'positionControl/position control/PID Controller3/Ideal P Gain/Passthrough'
//  '<S136>' : 'positionControl/position control/PID Controller3/Ideal P Gain Fdbk/Disabled'
//  '<S137>' : 'positionControl/position control/PID Controller3/Integrator/Discrete'
//  '<S138>' : 'positionControl/position control/PID Controller3/Integrator ICs/Internal IC'
//  '<S139>' : 'positionControl/position control/PID Controller3/N Copy/Disabled'
//  '<S140>' : 'positionControl/position control/PID Controller3/N Gain/Internal Parameters'
//  '<S141>' : 'positionControl/position control/PID Controller3/P Copy/Disabled'
//  '<S142>' : 'positionControl/position control/PID Controller3/Parallel P Gain/Internal Parameters'
//  '<S143>' : 'positionControl/position control/PID Controller3/Reset Signal/Disabled'
//  '<S144>' : 'positionControl/position control/PID Controller3/Saturation/Enabled'
//  '<S145>' : 'positionControl/position control/PID Controller3/Saturation Fdbk/Disabled'
//  '<S146>' : 'positionControl/position control/PID Controller3/Sum/Sum_PID'
//  '<S147>' : 'positionControl/position control/PID Controller3/Sum Fdbk/Disabled'
//  '<S148>' : 'positionControl/position control/PID Controller3/Tracking Mode/Disabled'
//  '<S149>' : 'positionControl/position control/PID Controller3/Tracking Mode Sum/Passthrough'
//  '<S150>' : 'positionControl/position control/PID Controller3/Tsamp - Integral/Passthrough'
//  '<S151>' : 'positionControl/position control/PID Controller3/Tsamp - Ngain/Passthrough'
//  '<S152>' : 'positionControl/position control/PID Controller3/postSat Signal/Forward_Path'
//  '<S153>' : 'positionControl/position control/PID Controller3/preSat Signal/Forward_Path'
//  '<S154>' : 'positionControl/position control/PID Controller4/Anti-windup'
//  '<S155>' : 'positionControl/position control/PID Controller4/D Gain'
//  '<S156>' : 'positionControl/position control/PID Controller4/Filter'
//  '<S157>' : 'positionControl/position control/PID Controller4/Filter ICs'
//  '<S158>' : 'positionControl/position control/PID Controller4/I Gain'
//  '<S159>' : 'positionControl/position control/PID Controller4/Ideal P Gain'
//  '<S160>' : 'positionControl/position control/PID Controller4/Ideal P Gain Fdbk'
//  '<S161>' : 'positionControl/position control/PID Controller4/Integrator'
//  '<S162>' : 'positionControl/position control/PID Controller4/Integrator ICs'
//  '<S163>' : 'positionControl/position control/PID Controller4/N Copy'
//  '<S164>' : 'positionControl/position control/PID Controller4/N Gain'
//  '<S165>' : 'positionControl/position control/PID Controller4/P Copy'
//  '<S166>' : 'positionControl/position control/PID Controller4/Parallel P Gain'
//  '<S167>' : 'positionControl/position control/PID Controller4/Reset Signal'
//  '<S168>' : 'positionControl/position control/PID Controller4/Saturation'
//  '<S169>' : 'positionControl/position control/PID Controller4/Saturation Fdbk'
//  '<S170>' : 'positionControl/position control/PID Controller4/Sum'
//  '<S171>' : 'positionControl/position control/PID Controller4/Sum Fdbk'
//  '<S172>' : 'positionControl/position control/PID Controller4/Tracking Mode'
//  '<S173>' : 'positionControl/position control/PID Controller4/Tracking Mode Sum'
//  '<S174>' : 'positionControl/position control/PID Controller4/Tsamp - Integral'
//  '<S175>' : 'positionControl/position control/PID Controller4/Tsamp - Ngain'
//  '<S176>' : 'positionControl/position control/PID Controller4/postSat Signal'
//  '<S177>' : 'positionControl/position control/PID Controller4/preSat Signal'
//  '<S178>' : 'positionControl/position control/PID Controller4/Anti-windup/Disc. Clamping Parallel'
//  '<S179>' : 'positionControl/position control/PID Controller4/D Gain/Internal Parameters'
//  '<S180>' : 'positionControl/position control/PID Controller4/Filter/Disc. Forward Euler Filter'
//  '<S181>' : 'positionControl/position control/PID Controller4/Filter ICs/Internal IC - Filter'
//  '<S182>' : 'positionControl/position control/PID Controller4/I Gain/Internal Parameters'
//  '<S183>' : 'positionControl/position control/PID Controller4/Ideal P Gain/Passthrough'
//  '<S184>' : 'positionControl/position control/PID Controller4/Ideal P Gain Fdbk/Disabled'
//  '<S185>' : 'positionControl/position control/PID Controller4/Integrator/Discrete'
//  '<S186>' : 'positionControl/position control/PID Controller4/Integrator ICs/Internal IC'
//  '<S187>' : 'positionControl/position control/PID Controller4/N Copy/Disabled'
//  '<S188>' : 'positionControl/position control/PID Controller4/N Gain/Internal Parameters'
//  '<S189>' : 'positionControl/position control/PID Controller4/P Copy/Disabled'
//  '<S190>' : 'positionControl/position control/PID Controller4/Parallel P Gain/Internal Parameters'
//  '<S191>' : 'positionControl/position control/PID Controller4/Reset Signal/Disabled'
//  '<S192>' : 'positionControl/position control/PID Controller4/Saturation/Enabled'
//  '<S193>' : 'positionControl/position control/PID Controller4/Saturation Fdbk/Disabled'
//  '<S194>' : 'positionControl/position control/PID Controller4/Sum/Sum_PID'
//  '<S195>' : 'positionControl/position control/PID Controller4/Sum Fdbk/Disabled'
//  '<S196>' : 'positionControl/position control/PID Controller4/Tracking Mode/Disabled'
//  '<S197>' : 'positionControl/position control/PID Controller4/Tracking Mode Sum/Passthrough'
//  '<S198>' : 'positionControl/position control/PID Controller4/Tsamp - Integral/Passthrough'
//  '<S199>' : 'positionControl/position control/PID Controller4/Tsamp - Ngain/Passthrough'
//  '<S200>' : 'positionControl/position control/PID Controller4/postSat Signal/Forward_Path'
//  '<S201>' : 'positionControl/position control/PID Controller4/preSat Signal/Forward_Path'
//  '<S202>' : 'positionControl/position control/PID Controller5/Anti-windup'
//  '<S203>' : 'positionControl/position control/PID Controller5/D Gain'
//  '<S204>' : 'positionControl/position control/PID Controller5/Filter'
//  '<S205>' : 'positionControl/position control/PID Controller5/Filter ICs'
//  '<S206>' : 'positionControl/position control/PID Controller5/I Gain'
//  '<S207>' : 'positionControl/position control/PID Controller5/Ideal P Gain'
//  '<S208>' : 'positionControl/position control/PID Controller5/Ideal P Gain Fdbk'
//  '<S209>' : 'positionControl/position control/PID Controller5/Integrator'
//  '<S210>' : 'positionControl/position control/PID Controller5/Integrator ICs'
//  '<S211>' : 'positionControl/position control/PID Controller5/N Copy'
//  '<S212>' : 'positionControl/position control/PID Controller5/N Gain'
//  '<S213>' : 'positionControl/position control/PID Controller5/P Copy'
//  '<S214>' : 'positionControl/position control/PID Controller5/Parallel P Gain'
//  '<S215>' : 'positionControl/position control/PID Controller5/Reset Signal'
//  '<S216>' : 'positionControl/position control/PID Controller5/Saturation'
//  '<S217>' : 'positionControl/position control/PID Controller5/Saturation Fdbk'
//  '<S218>' : 'positionControl/position control/PID Controller5/Sum'
//  '<S219>' : 'positionControl/position control/PID Controller5/Sum Fdbk'
//  '<S220>' : 'positionControl/position control/PID Controller5/Tracking Mode'
//  '<S221>' : 'positionControl/position control/PID Controller5/Tracking Mode Sum'
//  '<S222>' : 'positionControl/position control/PID Controller5/Tsamp - Integral'
//  '<S223>' : 'positionControl/position control/PID Controller5/Tsamp - Ngain'
//  '<S224>' : 'positionControl/position control/PID Controller5/postSat Signal'
//  '<S225>' : 'positionControl/position control/PID Controller5/preSat Signal'
//  '<S226>' : 'positionControl/position control/PID Controller5/Anti-windup/Disc. Clamping Parallel'
//  '<S227>' : 'positionControl/position control/PID Controller5/D Gain/Internal Parameters'
//  '<S228>' : 'positionControl/position control/PID Controller5/Filter/Disc. Forward Euler Filter'
//  '<S229>' : 'positionControl/position control/PID Controller5/Filter ICs/Internal IC - Filter'
//  '<S230>' : 'positionControl/position control/PID Controller5/I Gain/Internal Parameters'
//  '<S231>' : 'positionControl/position control/PID Controller5/Ideal P Gain/Passthrough'
//  '<S232>' : 'positionControl/position control/PID Controller5/Ideal P Gain Fdbk/Disabled'
//  '<S233>' : 'positionControl/position control/PID Controller5/Integrator/Discrete'
//  '<S234>' : 'positionControl/position control/PID Controller5/Integrator ICs/Internal IC'
//  '<S235>' : 'positionControl/position control/PID Controller5/N Copy/Disabled'
//  '<S236>' : 'positionControl/position control/PID Controller5/N Gain/Internal Parameters'
//  '<S237>' : 'positionControl/position control/PID Controller5/P Copy/Disabled'
//  '<S238>' : 'positionControl/position control/PID Controller5/Parallel P Gain/Internal Parameters'
//  '<S239>' : 'positionControl/position control/PID Controller5/Reset Signal/Disabled'
//  '<S240>' : 'positionControl/position control/PID Controller5/Saturation/Enabled'
//  '<S241>' : 'positionControl/position control/PID Controller5/Saturation Fdbk/Disabled'
//  '<S242>' : 'positionControl/position control/PID Controller5/Sum/Sum_PID'
//  '<S243>' : 'positionControl/position control/PID Controller5/Sum Fdbk/Disabled'
//  '<S244>' : 'positionControl/position control/PID Controller5/Tracking Mode/Disabled'
//  '<S245>' : 'positionControl/position control/PID Controller5/Tracking Mode Sum/Passthrough'
//  '<S246>' : 'positionControl/position control/PID Controller5/Tsamp - Integral/Passthrough'
//  '<S247>' : 'positionControl/position control/PID Controller5/Tsamp - Ngain/Passthrough'
//  '<S248>' : 'positionControl/position control/PID Controller5/postSat Signal/Forward_Path'
//  '<S249>' : 'positionControl/position control/PID Controller5/preSat Signal/Forward_Path'
//  '<S250>' : 'positionControl/position control/ZPostoVel/Anti-windup'
//  '<S251>' : 'positionControl/position control/ZPostoVel/D Gain'
//  '<S252>' : 'positionControl/position control/ZPostoVel/Filter'
//  '<S253>' : 'positionControl/position control/ZPostoVel/Filter ICs'
//  '<S254>' : 'positionControl/position control/ZPostoVel/I Gain'
//  '<S255>' : 'positionControl/position control/ZPostoVel/Ideal P Gain'
//  '<S256>' : 'positionControl/position control/ZPostoVel/Ideal P Gain Fdbk'
//  '<S257>' : 'positionControl/position control/ZPostoVel/Integrator'
//  '<S258>' : 'positionControl/position control/ZPostoVel/Integrator ICs'
//  '<S259>' : 'positionControl/position control/ZPostoVel/N Copy'
//  '<S260>' : 'positionControl/position control/ZPostoVel/N Gain'
//  '<S261>' : 'positionControl/position control/ZPostoVel/P Copy'
//  '<S262>' : 'positionControl/position control/ZPostoVel/Parallel P Gain'
//  '<S263>' : 'positionControl/position control/ZPostoVel/Reset Signal'
//  '<S264>' : 'positionControl/position control/ZPostoVel/Saturation'
//  '<S265>' : 'positionControl/position control/ZPostoVel/Saturation Fdbk'
//  '<S266>' : 'positionControl/position control/ZPostoVel/Sum'
//  '<S267>' : 'positionControl/position control/ZPostoVel/Sum Fdbk'
//  '<S268>' : 'positionControl/position control/ZPostoVel/Tracking Mode'
//  '<S269>' : 'positionControl/position control/ZPostoVel/Tracking Mode Sum'
//  '<S270>' : 'positionControl/position control/ZPostoVel/Tsamp - Integral'
//  '<S271>' : 'positionControl/position control/ZPostoVel/Tsamp - Ngain'
//  '<S272>' : 'positionControl/position control/ZPostoVel/postSat Signal'
//  '<S273>' : 'positionControl/position control/ZPostoVel/preSat Signal'
//  '<S274>' : 'positionControl/position control/ZPostoVel/Anti-windup/Disc. Clamping Parallel'
//  '<S275>' : 'positionControl/position control/ZPostoVel/D Gain/Internal Parameters'
//  '<S276>' : 'positionControl/position control/ZPostoVel/Filter/Disc. Forward Euler Filter'
//  '<S277>' : 'positionControl/position control/ZPostoVel/Filter ICs/Internal IC - Filter'
//  '<S278>' : 'positionControl/position control/ZPostoVel/I Gain/Internal Parameters'
//  '<S279>' : 'positionControl/position control/ZPostoVel/Ideal P Gain/Passthrough'
//  '<S280>' : 'positionControl/position control/ZPostoVel/Ideal P Gain Fdbk/Disabled'
//  '<S281>' : 'positionControl/position control/ZPostoVel/Integrator/Discrete'
//  '<S282>' : 'positionControl/position control/ZPostoVel/Integrator ICs/Internal IC'
//  '<S283>' : 'positionControl/position control/ZPostoVel/N Copy/Disabled'
//  '<S284>' : 'positionControl/position control/ZPostoVel/N Gain/Internal Parameters'
//  '<S285>' : 'positionControl/position control/ZPostoVel/P Copy/Disabled'
//  '<S286>' : 'positionControl/position control/ZPostoVel/Parallel P Gain/Internal Parameters'
//  '<S287>' : 'positionControl/position control/ZPostoVel/Reset Signal/Disabled'
//  '<S288>' : 'positionControl/position control/ZPostoVel/Saturation/Enabled'
//  '<S289>' : 'positionControl/position control/ZPostoVel/Saturation Fdbk/Disabled'
//  '<S290>' : 'positionControl/position control/ZPostoVel/Sum/Sum_PID'
//  '<S291>' : 'positionControl/position control/ZPostoVel/Sum Fdbk/Disabled'
//  '<S292>' : 'positionControl/position control/ZPostoVel/Tracking Mode/Disabled'
//  '<S293>' : 'positionControl/position control/ZPostoVel/Tracking Mode Sum/Passthrough'
//  '<S294>' : 'positionControl/position control/ZPostoVel/Tsamp - Integral/Passthrough'
//  '<S295>' : 'positionControl/position control/ZPostoVel/Tsamp - Ngain/Passthrough'
//  '<S296>' : 'positionControl/position control/ZPostoVel/postSat Signal/Forward_Path'
//  '<S297>' : 'positionControl/position control/ZPostoVel/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_positionControl_h_

//
// File trailer for generated code.
//
// [EOF]
//
