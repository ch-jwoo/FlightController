//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionControl.h
//
// Code generated for Simulink model 'positionControl'.
//
// Model version                  : 1.10
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Sun Aug 23 20:26:15 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_positionControl_h_
#define RTW_HEADER_positionControl_h_
#include <MatlabPositionControl/positionControl_types.h>
#include <MatlabPositionControl/rtwtypes.h>
#include <cmath>

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

extern real_T ZvelMax;                 // Variable: ZvelMax
                                          //  Referenced by: '<S287>/Saturation'

extern real_T hoverThr;                // Variable: hoverThr
                                          //  Referenced by: '<S1>/Constant'

extern real_T pos_x_D;                 // Variable: pos_x_D
                                          //  Referenced by: '<S34>/Derivative Gain'

extern real_T pos_x_I;                 // Variable: pos_x_I
                                          //  Referenced by: '<S37>/Integral Gain'

extern real_T pos_x_P;                 // Variable: pos_x_P
                                          //  Referenced by: '<S45>/Proportional Gain'

extern real_T pos_x_vel_D;             // Variable: pos_x_vel_D
                                          //  Referenced by: '<S82>/Derivative Gain'

extern real_T pos_x_vel_I;             // Variable: pos_x_vel_I
                                          //  Referenced by: '<S85>/Integral Gain'

extern real_T pos_x_vel_P;             // Variable: pos_x_vel_P
                                          //  Referenced by: '<S93>/Proportional Gain'

extern real_T pos_y_D;                 // Variable: pos_y_D
                                          //  Referenced by: '<S178>/Derivative Gain'

extern real_T pos_y_I;                 // Variable: pos_y_I
                                          //  Referenced by: '<S181>/Integral Gain'

extern real_T pos_y_P;                 // Variable: pos_y_P
                                          //  Referenced by: '<S189>/Proportional Gain'

extern real_T pos_y_vel_D;             // Variable: pos_y_vel_D
                                          //  Referenced by: '<S226>/Derivative Gain'

extern real_T pos_y_vel_I;             // Variable: pos_y_vel_I
                                          //  Referenced by: '<S229>/Integral Gain'

extern real_T pos_y_vel_P;             // Variable: pos_y_vel_P
                                          //  Referenced by: '<S237>/Proportional Gain'

extern real_T pos_z_D;                 // Variable: pos_z_D
                                          //  Referenced by: '<S274>/Derivative Gain'

extern real_T pos_z_I;                 // Variable: pos_z_I
                                          //  Referenced by: '<S277>/Integral Gain'

extern real_T pos_z_P;                 // Variable: pos_z_P
                                          //  Referenced by: '<S285>/Proportional Gain'

extern real_T pos_z_vel_D;             // Variable: pos_z_vel_D
                                          //  Referenced by: '<S130>/Derivative Gain'

extern real_T pos_z_vel_I;             // Variable: pos_z_vel_I
                                          //  Referenced by: '<S133>/Integral Gain'

extern real_T pos_z_vel_P;             // Variable: pos_z_vel_P
                                          //  Referenced by: '<S141>/Proportional Gain'


// Class declaration for model positionControl
class positionControlModelClass {
  // public data and function members
 public:
  // Block signals (default storage)
  typedef struct {
    real_T DataTypeConversion;         // '<S1>/Data Type Conversion'
    real_T TrigonometricFunction_o1;   // '<S8>/Trigonometric Function'
    real_T TrigonometricFunction_o2;   // '<S8>/Trigonometric Function'
    real_T MatrixConcatenate[4];       // '<S8>/Matrix Concatenate'
    real_T x_error;                    // '<S1>/Add'
    real_T ProportionalGain;           // '<S45>/Proportional Gain'
    real_T Integrator;                 // '<S40>/Integrator'
    real_T DerivativeGain;             // '<S34>/Derivative Gain'
    real_T Filter;                     // '<S35>/Filter'
    real_T SumD;                       // '<S35>/SumD'
    real_T FilterCoefficient;          // '<S43>/Filter Coefficient'
    real_T Sum;                        // '<S49>/Sum'
    real_T Saturation;                 // '<S47>/Saturation'
    real_T y_error;                    // '<S1>/Add4'
    real_T ProportionalGain_p;         // '<S189>/Proportional Gain'
    real_T Integrator_f;               // '<S184>/Integrator'
    real_T DerivativeGain_n;           // '<S178>/Derivative Gain'
    real_T Filter_p;                   // '<S179>/Filter'
    real_T SumD_k;                     // '<S179>/SumD'
    real_T FilterCoefficient_n;        // '<S187>/Filter Coefficient'
    real_T Sum_k;                      // '<S193>/Sum'
    real_T Saturation_o;               // '<S191>/Saturation'
    real_T Add1[2];                    // '<S1>/Add1'
    real_T vel_error[2];               // '<S1>/Matrix Multiply'
    real_T ProportionalGain_m;         // '<S237>/Proportional Gain'
    real_T Integrator_h;               // '<S232>/Integrator'
    real_T DerivativeGain_c;           // '<S226>/Derivative Gain'
    real_T Filter_g;                   // '<S227>/Filter'
    real_T SumD_f;                     // '<S227>/SumD'
    real_T FilterCoefficient_e;        // '<S235>/Filter Coefficient'
    real_T Sum_m;                      // '<S241>/Sum'
    real_T Saturation_l;               // '<S239>/Saturation'
    real_T Gain1;                      // '<S1>/Gain1'
    real_T ProportionalGain_h;         // '<S93>/Proportional Gain'
    real_T Integrator_c;               // '<S88>/Integrator'
    real_T DerivativeGain_p;           // '<S82>/Derivative Gain'
    real_T Filter_i;                   // '<S83>/Filter'
    real_T SumD_h;                     // '<S83>/SumD'
    real_T FilterCoefficient_f;        // '<S91>/Filter Coefficient'
    real_T Sum_o;                      // '<S97>/Sum'
    real_T Saturation_j;               // '<S95>/Saturation'
    real_T Sum_my;                     // '<S1>/Sum'
    real_T Gain;                       // '<S1>/Gain'
    real_T alt_error;                  // '<S1>/Add2'
    real_T Gain2;                      // '<S1>/Gain2'
    real_T ProportionalGain_j;         // '<S285>/Proportional Gain'
    real_T Integrator_ca;              // '<S280>/Integrator'
    real_T DerivativeGain_f;           // '<S274>/Derivative Gain'
    real_T Filter_gq;                  // '<S275>/Filter'
    real_T SumD_d;                     // '<S275>/SumD'
    real_T FilterCoefficient_j;        // '<S283>/Filter Coefficient'
    real_T Sum_d;                      // '<S289>/Sum'
    real_T Saturation_jh;              // '<S287>/Saturation'
    real_T Gain3;                      // '<S1>/Gain3'
    real_T Add3;                       // '<S1>/Add3'
    real_T ProportionalGain_k;         // '<S141>/Proportional Gain'
    real_T Integrator_p;               // '<S136>/Integrator'
    real_T DerivativeGain_pu;          // '<S130>/Derivative Gain'
    real_T Filter_m;                   // '<S131>/Filter'
    real_T SumD_b;                     // '<S131>/SumD'
    real_T FilterCoefficient_a;        // '<S139>/Filter Coefficient'
    real_T Sum_c;                      // '<S145>/Sum'
    real_T Saturation_li;              // '<S143>/Saturation'
    real_T Sum1;                       // '<S1>/Sum1'
    real_T IntegralGain;               // '<S37>/Integral Gain'
    real_T SumI2;                      // '<S81>/SumI2'
    real_T Kb;                         // '<S81>/Kb'
    real_T IntegralGain_k;             // '<S85>/Integral Gain'
    real_T SumI4;                      // '<S81>/SumI4'
    real_T IntegralGain_o;             // '<S181>/Integral Gain'
    real_T SumI2_n;                    // '<S225>/SumI2'
    real_T Kb_e;                       // '<S225>/Kb'
    real_T IntegralGain_b;             // '<S229>/Integral Gain'
    real_T SumI4_c;                    // '<S225>/SumI4'
    real_T ZeroGain;                   // '<S129>/ZeroGain'
    real_T DeadZone;                   // '<S129>/DeadZone'
    real_T SignPreSat;                 // '<S129>/SignPreSat'
    real_T IntegralGain_l;             // '<S133>/Integral Gain'
    real_T SignPreIntegrator;          // '<S129>/SignPreIntegrator'
    real_T Switch;                     // '<S129>/Switch'
    real_T IntegralGain_g;             // '<S277>/Integral Gain'
    int8_T DataTypeConv1;              // '<S129>/DataTypeConv1'
    int8_T DataTypeConv2;              // '<S129>/DataTypeConv2'
    boolean_T NotEqual;                // '<S129>/NotEqual'
    boolean_T Equal1;                  // '<S129>/Equal1'
    boolean_T AND3;                    // '<S129>/AND3'
  } B_positionControl_T;

  // Block states (default storage) for system '<Root>'
  typedef struct {
    real_T Integrator_DSTATE;          // '<S40>/Integrator'
    real_T Filter_DSTATE;              // '<S35>/Filter'
    real_T Integrator_DSTATE_k;        // '<S184>/Integrator'
    real_T Filter_DSTATE_m;            // '<S179>/Filter'
    real_T Integrator_DSTATE_f;        // '<S232>/Integrator'
    real_T Filter_DSTATE_j;            // '<S227>/Filter'
    real_T Integrator_DSTATE_m;        // '<S88>/Integrator'
    real_T Filter_DSTATE_d;            // '<S83>/Filter'
    real_T Integrator_DSTATE_p;        // '<S280>/Integrator'
    real_T Filter_DSTATE_mo;           // '<S275>/Filter'
    real_T Integrator_DSTATE_b;        // '<S136>/Integrator'
    real_T Filter_DSTATE_e;            // '<S131>/Filter'
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
    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S35>/Filter'

    real_T PIDController4_InitialCondition;
                              // Mask Parameter: PIDController4_InitialCondition
                                 //  Referenced by: '<S179>/Filter'

    real_T PIDController5_InitialCondition;
                              // Mask Parameter: PIDController5_InitialCondition
                                 //  Referenced by: '<S227>/Filter'

    real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S83>/Filter'

    real_T ZPostoVel_InitialConditionForFi;
                              // Mask Parameter: ZPostoVel_InitialConditionForFi
                                 //  Referenced by: '<S275>/Filter'

    real_T PIDController3_InitialCondition;
                              // Mask Parameter: PIDController3_InitialCondition
                                 //  Referenced by: '<S131>/Filter'

    real_T PIDController_InitialConditio_c;
                              // Mask Parameter: PIDController_InitialConditio_c
                                 //  Referenced by: '<S40>/Integrator'

    real_T PIDController4_InitialConditi_i;
                              // Mask Parameter: PIDController4_InitialConditi_i
                                 //  Referenced by: '<S184>/Integrator'

    real_T PIDController5_InitialConditi_c;
                              // Mask Parameter: PIDController5_InitialConditi_c
                                 //  Referenced by: '<S232>/Integrator'

    real_T PIDController1_InitialConditi_a;
                              // Mask Parameter: PIDController1_InitialConditi_a
                                 //  Referenced by: '<S88>/Integrator'

    real_T ZPostoVel_InitialConditionForIn;
                              // Mask Parameter: ZPostoVel_InitialConditionForIn
                                 //  Referenced by: '<S280>/Integrator'

    real_T PIDController3_InitialConditi_d;
                              // Mask Parameter: PIDController3_InitialConditi_d
                                 //  Referenced by: '<S136>/Integrator'

    real_T PIDController1_Kb;          // Mask Parameter: PIDController1_Kb
                                          //  Referenced by: '<S81>/Kb'

    real_T PIDController5_Kb;          // Mask Parameter: PIDController5_Kb
                                          //  Referenced by: '<S225>/Kb'

    real_T PIDController_LowerSaturationLi;
                              // Mask Parameter: PIDController_LowerSaturationLi
                                 //  Referenced by: '<S47>/Saturation'

    real_T PIDController4_LowerSaturationL;
                              // Mask Parameter: PIDController4_LowerSaturationL
                                 //  Referenced by: '<S191>/Saturation'

    real_T PIDController5_LowerSaturationL;
                              // Mask Parameter: PIDController5_LowerSaturationL
                                 //  Referenced by: '<S239>/Saturation'

    real_T PIDController1_LowerSaturationL;
                              // Mask Parameter: PIDController1_LowerSaturationL
                                 //  Referenced by: '<S95>/Saturation'

    real_T PIDController3_LowerSaturationL;
                              // Mask Parameter: PIDController3_LowerSaturationL
                                 //  Referenced by:
                                 //    '<S129>/DeadZone'
                                 //    '<S143>/Saturation'

    real_T PIDController_N;            // Mask Parameter: PIDController_N
                                          //  Referenced by: '<S43>/Filter Coefficient'

    real_T PIDController4_N;           // Mask Parameter: PIDController4_N
                                          //  Referenced by: '<S187>/Filter Coefficient'

    real_T PIDController5_N;           // Mask Parameter: PIDController5_N
                                          //  Referenced by: '<S235>/Filter Coefficient'

    real_T PIDController1_N;           // Mask Parameter: PIDController1_N
                                          //  Referenced by: '<S91>/Filter Coefficient'

    real_T ZPostoVel_N;                // Mask Parameter: ZPostoVel_N
                                          //  Referenced by: '<S283>/Filter Coefficient'

    real_T PIDController3_N;           // Mask Parameter: PIDController3_N
                                          //  Referenced by: '<S139>/Filter Coefficient'

    real_T PIDController_UpperSaturationLi;
                              // Mask Parameter: PIDController_UpperSaturationLi
                                 //  Referenced by: '<S47>/Saturation'

    real_T PIDController4_UpperSaturationL;
                              // Mask Parameter: PIDController4_UpperSaturationL
                                 //  Referenced by: '<S191>/Saturation'

    real_T PIDController5_UpperSaturationL;
                              // Mask Parameter: PIDController5_UpperSaturationL
                                 //  Referenced by: '<S239>/Saturation'

    real_T PIDController1_UpperSaturationL;
                              // Mask Parameter: PIDController1_UpperSaturationL
                                 //  Referenced by: '<S95>/Saturation'

    real_T PIDController3_UpperSaturationL;
                              // Mask Parameter: PIDController3_UpperSaturationL
                                 //  Referenced by:
                                 //    '<S129>/DeadZone'
                                 //    '<S143>/Saturation'

    real_T Constant1_Value;            // Expression: 0
                                          //  Referenced by: '<S129>/Constant1'

    real_T Gain_Gain;                  // Expression: -1
                                          //  Referenced by: '<S8>/Gain'

    real_T Integrator_gainval;         // Computed Parameter: Integrator_gainval
                                          //  Referenced by: '<S40>/Integrator'

    real_T Filter_gainval;             // Computed Parameter: Filter_gainval
                                          //  Referenced by: '<S35>/Filter'

    real_T Integrator_gainval_l;     // Computed Parameter: Integrator_gainval_l
                                        //  Referenced by: '<S184>/Integrator'

    real_T Filter_gainval_l;           // Computed Parameter: Filter_gainval_l
                                          //  Referenced by: '<S179>/Filter'

    real_T Integrator_gainval_k;     // Computed Parameter: Integrator_gainval_k
                                        //  Referenced by: '<S232>/Integrator'

    real_T Filter_gainval_i;           // Computed Parameter: Filter_gainval_i
                                          //  Referenced by: '<S227>/Filter'

    real_T Gain1_Gain;                 // Expression: -1
                                          //  Referenced by: '<S1>/Gain1'

    real_T Integrator_gainval_lc;   // Computed Parameter: Integrator_gainval_lc
                                       //  Referenced by: '<S88>/Integrator'

    real_T Filter_gainval_l5;          // Computed Parameter: Filter_gainval_l5
                                          //  Referenced by: '<S83>/Filter'

    real_T Gain2_Gain;                 // Expression: -1
                                          //  Referenced by: '<S1>/Gain2'

    real_T Integrator_gainval_j;     // Computed Parameter: Integrator_gainval_j
                                        //  Referenced by: '<S280>/Integrator'

    real_T Filter_gainval_c;           // Computed Parameter: Filter_gainval_c
                                          //  Referenced by: '<S275>/Filter'

    real_T Gain3_Gain;                 // Expression: -1
                                          //  Referenced by: '<S1>/Gain3'

    real_T Integrator_gainval_a;     // Computed Parameter: Integrator_gainval_a
                                        //  Referenced by: '<S136>/Integrator'

    real_T Filter_gainval_g;           // Computed Parameter: Filter_gainval_g
                                          //  Referenced by: '<S131>/Filter'

    real_T ZeroGain_Gain;              // Expression: 0
                                          //  Referenced by: '<S129>/ZeroGain'

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
//  '<S7>'   : 'positionControl/position control/ZPostoVel'
//  '<S8>'   : 'positionControl/position control/rot_matrix'
//  '<S9>'   : 'positionControl/position control/PID Controller/Anti-windup'
//  '<S10>'  : 'positionControl/position control/PID Controller/D Gain'
//  '<S11>'  : 'positionControl/position control/PID Controller/Filter'
//  '<S12>'  : 'positionControl/position control/PID Controller/Filter ICs'
//  '<S13>'  : 'positionControl/position control/PID Controller/I Gain'
//  '<S14>'  : 'positionControl/position control/PID Controller/Ideal P Gain'
//  '<S15>'  : 'positionControl/position control/PID Controller/Ideal P Gain Fdbk'
//  '<S16>'  : 'positionControl/position control/PID Controller/Integrator'
//  '<S17>'  : 'positionControl/position control/PID Controller/Integrator ICs'
//  '<S18>'  : 'positionControl/position control/PID Controller/N Copy'
//  '<S19>'  : 'positionControl/position control/PID Controller/N Gain'
//  '<S20>'  : 'positionControl/position control/PID Controller/P Copy'
//  '<S21>'  : 'positionControl/position control/PID Controller/Parallel P Gain'
//  '<S22>'  : 'positionControl/position control/PID Controller/Reset Signal'
//  '<S23>'  : 'positionControl/position control/PID Controller/Saturation'
//  '<S24>'  : 'positionControl/position control/PID Controller/Saturation Fdbk'
//  '<S25>'  : 'positionControl/position control/PID Controller/Sum'
//  '<S26>'  : 'positionControl/position control/PID Controller/Sum Fdbk'
//  '<S27>'  : 'positionControl/position control/PID Controller/Tracking Mode'
//  '<S28>'  : 'positionControl/position control/PID Controller/Tracking Mode Sum'
//  '<S29>'  : 'positionControl/position control/PID Controller/Tsamp - Integral'
//  '<S30>'  : 'positionControl/position control/PID Controller/Tsamp - Ngain'
//  '<S31>'  : 'positionControl/position control/PID Controller/postSat Signal'
//  '<S32>'  : 'positionControl/position control/PID Controller/preSat Signal'
//  '<S33>'  : 'positionControl/position control/PID Controller/Anti-windup/Passthrough'
//  '<S34>'  : 'positionControl/position control/PID Controller/D Gain/Internal Parameters'
//  '<S35>'  : 'positionControl/position control/PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S36>'  : 'positionControl/position control/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S37>'  : 'positionControl/position control/PID Controller/I Gain/Internal Parameters'
//  '<S38>'  : 'positionControl/position control/PID Controller/Ideal P Gain/Passthrough'
//  '<S39>'  : 'positionControl/position control/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S40>'  : 'positionControl/position control/PID Controller/Integrator/Discrete'
//  '<S41>'  : 'positionControl/position control/PID Controller/Integrator ICs/Internal IC'
//  '<S42>'  : 'positionControl/position control/PID Controller/N Copy/Disabled'
//  '<S43>'  : 'positionControl/position control/PID Controller/N Gain/Internal Parameters'
//  '<S44>'  : 'positionControl/position control/PID Controller/P Copy/Disabled'
//  '<S45>'  : 'positionControl/position control/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S46>'  : 'positionControl/position control/PID Controller/Reset Signal/Disabled'
//  '<S47>'  : 'positionControl/position control/PID Controller/Saturation/Enabled'
//  '<S48>'  : 'positionControl/position control/PID Controller/Saturation Fdbk/Disabled'
//  '<S49>'  : 'positionControl/position control/PID Controller/Sum/Sum_PID'
//  '<S50>'  : 'positionControl/position control/PID Controller/Sum Fdbk/Disabled'
//  '<S51>'  : 'positionControl/position control/PID Controller/Tracking Mode/Disabled'
//  '<S52>'  : 'positionControl/position control/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S53>'  : 'positionControl/position control/PID Controller/Tsamp - Integral/Passthrough'
//  '<S54>'  : 'positionControl/position control/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S55>'  : 'positionControl/position control/PID Controller/postSat Signal/Forward_Path'
//  '<S56>'  : 'positionControl/position control/PID Controller/preSat Signal/Forward_Path'
//  '<S57>'  : 'positionControl/position control/PID Controller1/Anti-windup'
//  '<S58>'  : 'positionControl/position control/PID Controller1/D Gain'
//  '<S59>'  : 'positionControl/position control/PID Controller1/Filter'
//  '<S60>'  : 'positionControl/position control/PID Controller1/Filter ICs'
//  '<S61>'  : 'positionControl/position control/PID Controller1/I Gain'
//  '<S62>'  : 'positionControl/position control/PID Controller1/Ideal P Gain'
//  '<S63>'  : 'positionControl/position control/PID Controller1/Ideal P Gain Fdbk'
//  '<S64>'  : 'positionControl/position control/PID Controller1/Integrator'
//  '<S65>'  : 'positionControl/position control/PID Controller1/Integrator ICs'
//  '<S66>'  : 'positionControl/position control/PID Controller1/N Copy'
//  '<S67>'  : 'positionControl/position control/PID Controller1/N Gain'
//  '<S68>'  : 'positionControl/position control/PID Controller1/P Copy'
//  '<S69>'  : 'positionControl/position control/PID Controller1/Parallel P Gain'
//  '<S70>'  : 'positionControl/position control/PID Controller1/Reset Signal'
//  '<S71>'  : 'positionControl/position control/PID Controller1/Saturation'
//  '<S72>'  : 'positionControl/position control/PID Controller1/Saturation Fdbk'
//  '<S73>'  : 'positionControl/position control/PID Controller1/Sum'
//  '<S74>'  : 'positionControl/position control/PID Controller1/Sum Fdbk'
//  '<S75>'  : 'positionControl/position control/PID Controller1/Tracking Mode'
//  '<S76>'  : 'positionControl/position control/PID Controller1/Tracking Mode Sum'
//  '<S77>'  : 'positionControl/position control/PID Controller1/Tsamp - Integral'
//  '<S78>'  : 'positionControl/position control/PID Controller1/Tsamp - Ngain'
//  '<S79>'  : 'positionControl/position control/PID Controller1/postSat Signal'
//  '<S80>'  : 'positionControl/position control/PID Controller1/preSat Signal'
//  '<S81>'  : 'positionControl/position control/PID Controller1/Anti-windup/Back Calculation'
//  '<S82>'  : 'positionControl/position control/PID Controller1/D Gain/Internal Parameters'
//  '<S83>'  : 'positionControl/position control/PID Controller1/Filter/Disc. Forward Euler Filter'
//  '<S84>'  : 'positionControl/position control/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S85>'  : 'positionControl/position control/PID Controller1/I Gain/Internal Parameters'
//  '<S86>'  : 'positionControl/position control/PID Controller1/Ideal P Gain/Passthrough'
//  '<S87>'  : 'positionControl/position control/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S88>'  : 'positionControl/position control/PID Controller1/Integrator/Discrete'
//  '<S89>'  : 'positionControl/position control/PID Controller1/Integrator ICs/Internal IC'
//  '<S90>'  : 'positionControl/position control/PID Controller1/N Copy/Disabled'
//  '<S91>'  : 'positionControl/position control/PID Controller1/N Gain/Internal Parameters'
//  '<S92>'  : 'positionControl/position control/PID Controller1/P Copy/Disabled'
//  '<S93>'  : 'positionControl/position control/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S94>'  : 'positionControl/position control/PID Controller1/Reset Signal/Disabled'
//  '<S95>'  : 'positionControl/position control/PID Controller1/Saturation/Enabled'
//  '<S96>'  : 'positionControl/position control/PID Controller1/Saturation Fdbk/Disabled'
//  '<S97>'  : 'positionControl/position control/PID Controller1/Sum/Sum_PID'
//  '<S98>'  : 'positionControl/position control/PID Controller1/Sum Fdbk/Disabled'
//  '<S99>'  : 'positionControl/position control/PID Controller1/Tracking Mode/Disabled'
//  '<S100>' : 'positionControl/position control/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S101>' : 'positionControl/position control/PID Controller1/Tsamp - Integral/Passthrough'
//  '<S102>' : 'positionControl/position control/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S103>' : 'positionControl/position control/PID Controller1/postSat Signal/Forward_Path'
//  '<S104>' : 'positionControl/position control/PID Controller1/preSat Signal/Forward_Path'
//  '<S105>' : 'positionControl/position control/PID Controller3/Anti-windup'
//  '<S106>' : 'positionControl/position control/PID Controller3/D Gain'
//  '<S107>' : 'positionControl/position control/PID Controller3/Filter'
//  '<S108>' : 'positionControl/position control/PID Controller3/Filter ICs'
//  '<S109>' : 'positionControl/position control/PID Controller3/I Gain'
//  '<S110>' : 'positionControl/position control/PID Controller3/Ideal P Gain'
//  '<S111>' : 'positionControl/position control/PID Controller3/Ideal P Gain Fdbk'
//  '<S112>' : 'positionControl/position control/PID Controller3/Integrator'
//  '<S113>' : 'positionControl/position control/PID Controller3/Integrator ICs'
//  '<S114>' : 'positionControl/position control/PID Controller3/N Copy'
//  '<S115>' : 'positionControl/position control/PID Controller3/N Gain'
//  '<S116>' : 'positionControl/position control/PID Controller3/P Copy'
//  '<S117>' : 'positionControl/position control/PID Controller3/Parallel P Gain'
//  '<S118>' : 'positionControl/position control/PID Controller3/Reset Signal'
//  '<S119>' : 'positionControl/position control/PID Controller3/Saturation'
//  '<S120>' : 'positionControl/position control/PID Controller3/Saturation Fdbk'
//  '<S121>' : 'positionControl/position control/PID Controller3/Sum'
//  '<S122>' : 'positionControl/position control/PID Controller3/Sum Fdbk'
//  '<S123>' : 'positionControl/position control/PID Controller3/Tracking Mode'
//  '<S124>' : 'positionControl/position control/PID Controller3/Tracking Mode Sum'
//  '<S125>' : 'positionControl/position control/PID Controller3/Tsamp - Integral'
//  '<S126>' : 'positionControl/position control/PID Controller3/Tsamp - Ngain'
//  '<S127>' : 'positionControl/position control/PID Controller3/postSat Signal'
//  '<S128>' : 'positionControl/position control/PID Controller3/preSat Signal'
//  '<S129>' : 'positionControl/position control/PID Controller3/Anti-windup/Disc. Clamping Parallel'
//  '<S130>' : 'positionControl/position control/PID Controller3/D Gain/Internal Parameters'
//  '<S131>' : 'positionControl/position control/PID Controller3/Filter/Disc. Forward Euler Filter'
//  '<S132>' : 'positionControl/position control/PID Controller3/Filter ICs/Internal IC - Filter'
//  '<S133>' : 'positionControl/position control/PID Controller3/I Gain/Internal Parameters'
//  '<S134>' : 'positionControl/position control/PID Controller3/Ideal P Gain/Passthrough'
//  '<S135>' : 'positionControl/position control/PID Controller3/Ideal P Gain Fdbk/Disabled'
//  '<S136>' : 'positionControl/position control/PID Controller3/Integrator/Discrete'
//  '<S137>' : 'positionControl/position control/PID Controller3/Integrator ICs/Internal IC'
//  '<S138>' : 'positionControl/position control/PID Controller3/N Copy/Disabled'
//  '<S139>' : 'positionControl/position control/PID Controller3/N Gain/Internal Parameters'
//  '<S140>' : 'positionControl/position control/PID Controller3/P Copy/Disabled'
//  '<S141>' : 'positionControl/position control/PID Controller3/Parallel P Gain/Internal Parameters'
//  '<S142>' : 'positionControl/position control/PID Controller3/Reset Signal/Disabled'
//  '<S143>' : 'positionControl/position control/PID Controller3/Saturation/Enabled'
//  '<S144>' : 'positionControl/position control/PID Controller3/Saturation Fdbk/Disabled'
//  '<S145>' : 'positionControl/position control/PID Controller3/Sum/Sum_PID'
//  '<S146>' : 'positionControl/position control/PID Controller3/Sum Fdbk/Disabled'
//  '<S147>' : 'positionControl/position control/PID Controller3/Tracking Mode/Disabled'
//  '<S148>' : 'positionControl/position control/PID Controller3/Tracking Mode Sum/Passthrough'
//  '<S149>' : 'positionControl/position control/PID Controller3/Tsamp - Integral/Passthrough'
//  '<S150>' : 'positionControl/position control/PID Controller3/Tsamp - Ngain/Passthrough'
//  '<S151>' : 'positionControl/position control/PID Controller3/postSat Signal/Forward_Path'
//  '<S152>' : 'positionControl/position control/PID Controller3/preSat Signal/Forward_Path'
//  '<S153>' : 'positionControl/position control/PID Controller4/Anti-windup'
//  '<S154>' : 'positionControl/position control/PID Controller4/D Gain'
//  '<S155>' : 'positionControl/position control/PID Controller4/Filter'
//  '<S156>' : 'positionControl/position control/PID Controller4/Filter ICs'
//  '<S157>' : 'positionControl/position control/PID Controller4/I Gain'
//  '<S158>' : 'positionControl/position control/PID Controller4/Ideal P Gain'
//  '<S159>' : 'positionControl/position control/PID Controller4/Ideal P Gain Fdbk'
//  '<S160>' : 'positionControl/position control/PID Controller4/Integrator'
//  '<S161>' : 'positionControl/position control/PID Controller4/Integrator ICs'
//  '<S162>' : 'positionControl/position control/PID Controller4/N Copy'
//  '<S163>' : 'positionControl/position control/PID Controller4/N Gain'
//  '<S164>' : 'positionControl/position control/PID Controller4/P Copy'
//  '<S165>' : 'positionControl/position control/PID Controller4/Parallel P Gain'
//  '<S166>' : 'positionControl/position control/PID Controller4/Reset Signal'
//  '<S167>' : 'positionControl/position control/PID Controller4/Saturation'
//  '<S168>' : 'positionControl/position control/PID Controller4/Saturation Fdbk'
//  '<S169>' : 'positionControl/position control/PID Controller4/Sum'
//  '<S170>' : 'positionControl/position control/PID Controller4/Sum Fdbk'
//  '<S171>' : 'positionControl/position control/PID Controller4/Tracking Mode'
//  '<S172>' : 'positionControl/position control/PID Controller4/Tracking Mode Sum'
//  '<S173>' : 'positionControl/position control/PID Controller4/Tsamp - Integral'
//  '<S174>' : 'positionControl/position control/PID Controller4/Tsamp - Ngain'
//  '<S175>' : 'positionControl/position control/PID Controller4/postSat Signal'
//  '<S176>' : 'positionControl/position control/PID Controller4/preSat Signal'
//  '<S177>' : 'positionControl/position control/PID Controller4/Anti-windup/Passthrough'
//  '<S178>' : 'positionControl/position control/PID Controller4/D Gain/Internal Parameters'
//  '<S179>' : 'positionControl/position control/PID Controller4/Filter/Disc. Forward Euler Filter'
//  '<S180>' : 'positionControl/position control/PID Controller4/Filter ICs/Internal IC - Filter'
//  '<S181>' : 'positionControl/position control/PID Controller4/I Gain/Internal Parameters'
//  '<S182>' : 'positionControl/position control/PID Controller4/Ideal P Gain/Passthrough'
//  '<S183>' : 'positionControl/position control/PID Controller4/Ideal P Gain Fdbk/Disabled'
//  '<S184>' : 'positionControl/position control/PID Controller4/Integrator/Discrete'
//  '<S185>' : 'positionControl/position control/PID Controller4/Integrator ICs/Internal IC'
//  '<S186>' : 'positionControl/position control/PID Controller4/N Copy/Disabled'
//  '<S187>' : 'positionControl/position control/PID Controller4/N Gain/Internal Parameters'
//  '<S188>' : 'positionControl/position control/PID Controller4/P Copy/Disabled'
//  '<S189>' : 'positionControl/position control/PID Controller4/Parallel P Gain/Internal Parameters'
//  '<S190>' : 'positionControl/position control/PID Controller4/Reset Signal/Disabled'
//  '<S191>' : 'positionControl/position control/PID Controller4/Saturation/Enabled'
//  '<S192>' : 'positionControl/position control/PID Controller4/Saturation Fdbk/Disabled'
//  '<S193>' : 'positionControl/position control/PID Controller4/Sum/Sum_PID'
//  '<S194>' : 'positionControl/position control/PID Controller4/Sum Fdbk/Disabled'
//  '<S195>' : 'positionControl/position control/PID Controller4/Tracking Mode/Disabled'
//  '<S196>' : 'positionControl/position control/PID Controller4/Tracking Mode Sum/Passthrough'
//  '<S197>' : 'positionControl/position control/PID Controller4/Tsamp - Integral/Passthrough'
//  '<S198>' : 'positionControl/position control/PID Controller4/Tsamp - Ngain/Passthrough'
//  '<S199>' : 'positionControl/position control/PID Controller4/postSat Signal/Forward_Path'
//  '<S200>' : 'positionControl/position control/PID Controller4/preSat Signal/Forward_Path'
//  '<S201>' : 'positionControl/position control/PID Controller5/Anti-windup'
//  '<S202>' : 'positionControl/position control/PID Controller5/D Gain'
//  '<S203>' : 'positionControl/position control/PID Controller5/Filter'
//  '<S204>' : 'positionControl/position control/PID Controller5/Filter ICs'
//  '<S205>' : 'positionControl/position control/PID Controller5/I Gain'
//  '<S206>' : 'positionControl/position control/PID Controller5/Ideal P Gain'
//  '<S207>' : 'positionControl/position control/PID Controller5/Ideal P Gain Fdbk'
//  '<S208>' : 'positionControl/position control/PID Controller5/Integrator'
//  '<S209>' : 'positionControl/position control/PID Controller5/Integrator ICs'
//  '<S210>' : 'positionControl/position control/PID Controller5/N Copy'
//  '<S211>' : 'positionControl/position control/PID Controller5/N Gain'
//  '<S212>' : 'positionControl/position control/PID Controller5/P Copy'
//  '<S213>' : 'positionControl/position control/PID Controller5/Parallel P Gain'
//  '<S214>' : 'positionControl/position control/PID Controller5/Reset Signal'
//  '<S215>' : 'positionControl/position control/PID Controller5/Saturation'
//  '<S216>' : 'positionControl/position control/PID Controller5/Saturation Fdbk'
//  '<S217>' : 'positionControl/position control/PID Controller5/Sum'
//  '<S218>' : 'positionControl/position control/PID Controller5/Sum Fdbk'
//  '<S219>' : 'positionControl/position control/PID Controller5/Tracking Mode'
//  '<S220>' : 'positionControl/position control/PID Controller5/Tracking Mode Sum'
//  '<S221>' : 'positionControl/position control/PID Controller5/Tsamp - Integral'
//  '<S222>' : 'positionControl/position control/PID Controller5/Tsamp - Ngain'
//  '<S223>' : 'positionControl/position control/PID Controller5/postSat Signal'
//  '<S224>' : 'positionControl/position control/PID Controller5/preSat Signal'
//  '<S225>' : 'positionControl/position control/PID Controller5/Anti-windup/Back Calculation'
//  '<S226>' : 'positionControl/position control/PID Controller5/D Gain/Internal Parameters'
//  '<S227>' : 'positionControl/position control/PID Controller5/Filter/Disc. Forward Euler Filter'
//  '<S228>' : 'positionControl/position control/PID Controller5/Filter ICs/Internal IC - Filter'
//  '<S229>' : 'positionControl/position control/PID Controller5/I Gain/Internal Parameters'
//  '<S230>' : 'positionControl/position control/PID Controller5/Ideal P Gain/Passthrough'
//  '<S231>' : 'positionControl/position control/PID Controller5/Ideal P Gain Fdbk/Disabled'
//  '<S232>' : 'positionControl/position control/PID Controller5/Integrator/Discrete'
//  '<S233>' : 'positionControl/position control/PID Controller5/Integrator ICs/Internal IC'
//  '<S234>' : 'positionControl/position control/PID Controller5/N Copy/Disabled'
//  '<S235>' : 'positionControl/position control/PID Controller5/N Gain/Internal Parameters'
//  '<S236>' : 'positionControl/position control/PID Controller5/P Copy/Disabled'
//  '<S237>' : 'positionControl/position control/PID Controller5/Parallel P Gain/Internal Parameters'
//  '<S238>' : 'positionControl/position control/PID Controller5/Reset Signal/Disabled'
//  '<S239>' : 'positionControl/position control/PID Controller5/Saturation/Enabled'
//  '<S240>' : 'positionControl/position control/PID Controller5/Saturation Fdbk/Disabled'
//  '<S241>' : 'positionControl/position control/PID Controller5/Sum/Sum_PID'
//  '<S242>' : 'positionControl/position control/PID Controller5/Sum Fdbk/Disabled'
//  '<S243>' : 'positionControl/position control/PID Controller5/Tracking Mode/Disabled'
//  '<S244>' : 'positionControl/position control/PID Controller5/Tracking Mode Sum/Passthrough'
//  '<S245>' : 'positionControl/position control/PID Controller5/Tsamp - Integral/Passthrough'
//  '<S246>' : 'positionControl/position control/PID Controller5/Tsamp - Ngain/Passthrough'
//  '<S247>' : 'positionControl/position control/PID Controller5/postSat Signal/Forward_Path'
//  '<S248>' : 'positionControl/position control/PID Controller5/preSat Signal/Forward_Path'
//  '<S249>' : 'positionControl/position control/ZPostoVel/Anti-windup'
//  '<S250>' : 'positionControl/position control/ZPostoVel/D Gain'
//  '<S251>' : 'positionControl/position control/ZPostoVel/Filter'
//  '<S252>' : 'positionControl/position control/ZPostoVel/Filter ICs'
//  '<S253>' : 'positionControl/position control/ZPostoVel/I Gain'
//  '<S254>' : 'positionControl/position control/ZPostoVel/Ideal P Gain'
//  '<S255>' : 'positionControl/position control/ZPostoVel/Ideal P Gain Fdbk'
//  '<S256>' : 'positionControl/position control/ZPostoVel/Integrator'
//  '<S257>' : 'positionControl/position control/ZPostoVel/Integrator ICs'
//  '<S258>' : 'positionControl/position control/ZPostoVel/N Copy'
//  '<S259>' : 'positionControl/position control/ZPostoVel/N Gain'
//  '<S260>' : 'positionControl/position control/ZPostoVel/P Copy'
//  '<S261>' : 'positionControl/position control/ZPostoVel/Parallel P Gain'
//  '<S262>' : 'positionControl/position control/ZPostoVel/Reset Signal'
//  '<S263>' : 'positionControl/position control/ZPostoVel/Saturation'
//  '<S264>' : 'positionControl/position control/ZPostoVel/Saturation Fdbk'
//  '<S265>' : 'positionControl/position control/ZPostoVel/Sum'
//  '<S266>' : 'positionControl/position control/ZPostoVel/Sum Fdbk'
//  '<S267>' : 'positionControl/position control/ZPostoVel/Tracking Mode'
//  '<S268>' : 'positionControl/position control/ZPostoVel/Tracking Mode Sum'
//  '<S269>' : 'positionControl/position control/ZPostoVel/Tsamp - Integral'
//  '<S270>' : 'positionControl/position control/ZPostoVel/Tsamp - Ngain'
//  '<S271>' : 'positionControl/position control/ZPostoVel/postSat Signal'
//  '<S272>' : 'positionControl/position control/ZPostoVel/preSat Signal'
//  '<S273>' : 'positionControl/position control/ZPostoVel/Anti-windup/Passthrough'
//  '<S274>' : 'positionControl/position control/ZPostoVel/D Gain/Internal Parameters'
//  '<S275>' : 'positionControl/position control/ZPostoVel/Filter/Disc. Forward Euler Filter'
//  '<S276>' : 'positionControl/position control/ZPostoVel/Filter ICs/Internal IC - Filter'
//  '<S277>' : 'positionControl/position control/ZPostoVel/I Gain/Internal Parameters'
//  '<S278>' : 'positionControl/position control/ZPostoVel/Ideal P Gain/Passthrough'
//  '<S279>' : 'positionControl/position control/ZPostoVel/Ideal P Gain Fdbk/Disabled'
//  '<S280>' : 'positionControl/position control/ZPostoVel/Integrator/Discrete'
//  '<S281>' : 'positionControl/position control/ZPostoVel/Integrator ICs/Internal IC'
//  '<S282>' : 'positionControl/position control/ZPostoVel/N Copy/Disabled'
//  '<S283>' : 'positionControl/position control/ZPostoVel/N Gain/Internal Parameters'
//  '<S284>' : 'positionControl/position control/ZPostoVel/P Copy/Disabled'
//  '<S285>' : 'positionControl/position control/ZPostoVel/Parallel P Gain/Internal Parameters'
//  '<S286>' : 'positionControl/position control/ZPostoVel/Reset Signal/Disabled'
//  '<S287>' : 'positionControl/position control/ZPostoVel/Saturation/Enabled'
//  '<S288>' : 'positionControl/position control/ZPostoVel/Saturation Fdbk/Disabled'
//  '<S289>' : 'positionControl/position control/ZPostoVel/Sum/Sum_PID'
//  '<S290>' : 'positionControl/position control/ZPostoVel/Sum Fdbk/Disabled'
//  '<S291>' : 'positionControl/position control/ZPostoVel/Tracking Mode/Disabled'
//  '<S292>' : 'positionControl/position control/ZPostoVel/Tracking Mode Sum/Passthrough'
//  '<S293>' : 'positionControl/position control/ZPostoVel/Tsamp - Integral/Passthrough'
//  '<S294>' : 'positionControl/position control/ZPostoVel/Tsamp - Ngain/Passthrough'
//  '<S295>' : 'positionControl/position control/ZPostoVel/postSat Signal/Forward_Path'
//  '<S296>' : 'positionControl/position control/ZPostoVel/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_positionControl_h_

//
// File trailer for generated code.
//
// [EOF]
//
