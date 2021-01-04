//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: FW_att_control_codeblock_fly.h
//
// Code generated for Simulink model 'FW_att_control_codeblock_fly'.
//
// Model version                  : 1.53
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Sat Oct  3 15:03:51 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_FW_att_control_codeblock_fly_h_
#define RTW_HEADER_FW_att_control_codeblock_fly_h_
#include <cmath>
#include "rtwtypes.h"
#include "FW_att_control_codeblock_fly_types.h"

// Macros for accessing real-time model data structure

// Class declaration for model FW_att_control_codeblock_fly
class FW_px4_AlgorithmModelClass {
  // public data and function members
 public:
  // Block signals (default storage)
  typedef struct {
    real32_T roll_dircection;          // '<Root>/roll_dircection'
    real32_T pitch_direction;          // '<Root>/pitch_direction'
    real32_T FW_Max_angle_coef[2];     // '<S1>/FW_Max_angle_coef'
    real32_T pitchrollerror;           // '<S4>/Sum'
    real32_T P_pr;                     // '<S4>/P_pr'
    real32_T DiscreteTimeIntegrator;   // '<S4>/Discrete-Time Integrator'
    real32_T I_pr;                     // '<S4>/I_pr'
    real32_T P_pr_m;                   // '<S4>/Sum16'
    real32_T pitchrollerror_b;         // '<S5>/Sum'
    real32_T P_pr_b;                   // '<S5>/P_pr'
    real32_T DiscreteTimeIntegrator_h; // '<S5>/Discrete-Time Integrator'
    real32_T I_pr_d;                   // '<S5>/I_pr'
    real32_T TSamp;                    // '<S7>/TSamp'
    real32_T Uk1;                      // '<S7>/UD'
    real32_T Diff;                     // '<S7>/Diff'
    real32_T D_pr;                     // '<S5>/D_pr'
    real32_T P_pr_d;                   // '<S5>/Sum16'
    real32_T Roll_rate;                // '<S5>/Roll_rate'
    real32_T pitchrollerror_m;         // '<S4>/Sum2'
    real32_T P_pr1;                    // '<S4>/P_pr1'
    real32_T DiscreteTimeIntegrator1;  // '<S4>/Discrete-Time Integrator1'
    real32_T I_pr1;                    // '<S4>/I_pr1'
    real32_T P_pr_o;                   // '<S4>/Sum1'
    real32_T pitchrollerror_i;         // '<S5>/Sum1'
    real32_T P_pr1_p;                  // '<S5>/P_pr1'
    real32_T DiscreteTimeIntegrator1_p;// '<S5>/Discrete-Time Integrator1'
    real32_T I_pr1_j;                  // '<S5>/I_pr1'
    real32_T TSamp_h;                  // '<S8>/TSamp'
    real32_T Uk1_i;                    // '<S8>/UD'
    real32_T Diff_l;                   // '<S8>/Diff'
    real32_T D_pr1;                    // '<S5>/D_pr1'
    real32_T P_pr_j;                   // '<S5>/Sum2'
    real32_T Pitch_rate;               // '<S5>/Pitch_rate'
    real32_T Sum;                      // '<S6>/Sum'
    real32_T Gain;                     // '<S6>/Gain'
    real32_T ProportionalGain;         // '<S46>/Proportional Gain'
    real32_T Integrator;               // '<S41>/Integrator'
    real32_T Sum_f;                    // '<S50>/Sum'
    real32_T Delay;                    // '<S5>/Delay'
    real32_T antiWU_Gain;              // '<S5>/antiWU_Gain'
    real32_T Add;                      // '<S5>/Add'
    real32_T Delay1;                   // '<S5>/Delay1'
    real32_T antiWU_Gain1;             // '<S5>/antiWU_Gain1'
    real32_T Add1;                     // '<S5>/Add1'
    real32_T IntegralGain;             // '<S38>/Integral Gain'
    uint16_T M1;                       // '<S1>/pwm_out1'
    uint16_T M2;                       // '<S1>/pwm_out1'
    uint16_T M3;                       // '<S1>/pwm_out1'
    uint16_T M4;                       // '<S1>/pwm_out1'
    uint16_T S1;                       // '<S1>/pwm_out1'
    uint16_T S2;                       // '<S1>/pwm_out1'
    uint16_T S3;                       // '<S1>/pwm_out1'
    uint16_T S4;                       // '<S1>/pwm_out1'
  } B_FW_att_control_codeblock_fl_T;

  // Block states (default storage) for system '<Root>'
  typedef struct {
    real32_T DiscreteTimeIntegrator_DSTATE;// '<S4>/Discrete-Time Integrator'
    real32_T DiscreteTimeIntegrator_DSTATE_k;// '<S5>/Discrete-Time Integrator'
    real32_T UD_DSTATE;                // '<S7>/UD'
    real32_T DiscreteTimeIntegrator1_DSTATE;// '<S4>/Discrete-Time Integrator1'
    real32_T DiscreteTimeIntegrator1_DSTAT_d;// '<S5>/Discrete-Time Integrator1' 
    real32_T UD_DSTATE_e;              // '<S8>/UD'
    real32_T Integrator_DSTATE;        // '<S41>/Integrator'
    real32_T Delay_DSTATE;             // '<S5>/Delay'
    real32_T Delay1_DSTATE;            // '<S5>/Delay1'
  } DW_FW_att_control_codeblock_f_T;

  // External inputs (root inport signals with default storage)
  typedef struct {
    real32_T Roll;                     // '<Root>/Roll'
    real32_T Pitch;                    // '<Root>/Pitch'
    real32_T p;                        // '<Root>/p'
    real32_T q;                        // '<Root>/q'
    real32_T r;                        // '<Root>/r'
    real32_T set_thrust;               // '<Root>/set_thrust'
    real32_T set_roll;                 // '<Root>/set_roll'
    real32_T set_pitch;                // '<Root>/set_pitch'
    real32_T set_yaw;                  // '<Root>/set_yaw'
  } ExtU_FW_att_control_codeblock_T;

  // External outputs (root outports fed by signals with default storage)
  typedef struct {
    uint16_T PWM_OUT[8];               // '<Root>/PWM_OUT'
  } ExtY_FW_att_control_codeblock_T;

  // Parameters (default storage)
  struct P_FW_att_control_codeblock_fl_T {
    real32_T FW_Angle_rate_pitch_kI;   // Variable: FW_Angle_rate_pitch_kI
                                          //  Referenced by: '<S4>/I_pr1'

    real32_T FW_Angle_rate_pitch_kP;   // Variable: FW_Angle_rate_pitch_kP
                                          //  Referenced by: '<S4>/P_pr1'

    real32_T FW_Angle_rate_roll_PI_kI; // Variable: FW_Angle_rate_roll_PI_kI
                                          //  Referenced by: '<S4>/I_pr'

    real32_T FW_Angle_rate_roll_PI_kP; // Variable: FW_Angle_rate_roll_PI_kP
                                          //  Referenced by: '<S4>/P_pr'

    real32_T FW_Max_angle_coef;        // Variable: FW_Max_angle_coef
                                          //  Referenced by: '<S1>/FW_Max_angle_coef'

    real32_T FW_Yaw_angel_rate_P;      // Variable: FW_Yaw_angel_rate_P
                                          //  Referenced by: '<S6>/Gain'

    real32_T FW_kD_Pitch_rate_PID;     // Variable: FW_kD_Pitch_rate_PID
                                          //  Referenced by: '<S5>/D_pr1'

    real32_T FW_kD_Roll_rate_PID;      // Variable: FW_kD_Roll_rate_PID
                                          //  Referenced by: '<S5>/D_pr'

    real32_T FW_kI_Pitch_rate_PID;     // Variable: FW_kI_Pitch_rate_PID
                                          //  Referenced by: '<S5>/I_pr1'

    real32_T FW_kI_Roll_rate_PID;      // Variable: FW_kI_Roll_rate_PID
                                          //  Referenced by: '<S5>/I_pr'

    real32_T FW_kI_Yaw_rate_PID;       // Variable: FW_kI_Yaw_rate_PID
                                          //  Referenced by: '<S38>/Integral Gain'

    real32_T FW_kP_Pitch_rate_PID;     // Variable: FW_kP_Pitch_rate_PID
                                          //  Referenced by: '<S5>/P_pr1'

    real32_T FW_kP_Roll_rate_PID;      // Variable: FW_kP_Roll_rate_PID
                                          //  Referenced by: '<S5>/P_pr'

    real32_T FW_kP_Yaw_rate_PID;       // Variable: FW_kP_Yaw_rate_PID
                                          //  Referenced by: '<S46>/Proportional Gain'

    real32_T DiscreteDerivative_ICPrevScaled;
                              // Mask Parameter: DiscreteDerivative_ICPrevScaled
                                 //  Referenced by: '<S7>/UD'

    real32_T DiscreteDerivative1_ICPrevScale;
                              // Mask Parameter: DiscreteDerivative1_ICPrevScale
                                 //  Referenced by: '<S8>/UD'

    real32_T DiscretePIDController_InitialCo;
                              // Mask Parameter: DiscretePIDController_InitialCo
                                 //  Referenced by: '<S41>/Integrator'

    real32_T roll_dircection_Gain;   // Computed Parameter: roll_dircection_Gain
                                        //  Referenced by: '<Root>/roll_dircection'

    real32_T pitch_direction_Gain;   // Computed Parameter: pitch_direction_Gain
                                        //  Referenced by: '<Root>/pitch_direction'

    real32_T DiscreteTimeIntegrator_gainval;
                           // Computed Parameter: DiscreteTimeIntegrator_gainval
                              //  Referenced by: '<S4>/Discrete-Time Integrator'

    real32_T DiscreteTimeIntegrator_IC;
                                // Computed Parameter: DiscreteTimeIntegrator_IC
                                   //  Referenced by: '<S4>/Discrete-Time Integrator'

    real32_T DiscreteTimeIntegrator_gainva_l;
                          // Computed Parameter: DiscreteTimeIntegrator_gainva_l
                             //  Referenced by: '<S5>/Discrete-Time Integrator'

    real32_T DiscreteTimeIntegrator_IC_k;
                              // Computed Parameter: DiscreteTimeIntegrator_IC_k
                                 //  Referenced by: '<S5>/Discrete-Time Integrator'

    real32_T TSamp_WtEt;               // Computed Parameter: TSamp_WtEt
                                          //  Referenced by: '<S7>/TSamp'

    real32_T Roll_rate_UpperSat;       // Computed Parameter: Roll_rate_UpperSat
                                          //  Referenced by: '<S5>/Roll_rate'

    real32_T Roll_rate_LowerSat;       // Computed Parameter: Roll_rate_LowerSat
                                          //  Referenced by: '<S5>/Roll_rate'

    real32_T DiscreteTimeIntegrator1_gainval;
                          // Computed Parameter: DiscreteTimeIntegrator1_gainval
                             //  Referenced by: '<S4>/Discrete-Time Integrator1'

    real32_T DiscreteTimeIntegrator1_IC;
                               // Computed Parameter: DiscreteTimeIntegrator1_IC
                                  //  Referenced by: '<S4>/Discrete-Time Integrator1'

    real32_T DiscreteTimeIntegrator1_gainv_k;
                          // Computed Parameter: DiscreteTimeIntegrator1_gainv_k
                             //  Referenced by: '<S5>/Discrete-Time Integrator1'

    real32_T DiscreteTimeIntegrator1_IC_j;
                             // Computed Parameter: DiscreteTimeIntegrator1_IC_j
                                //  Referenced by: '<S5>/Discrete-Time Integrator1'

    real32_T TSamp_WtEt_l;             // Computed Parameter: TSamp_WtEt_l
                                          //  Referenced by: '<S8>/TSamp'

    real32_T Pitch_rate_UpperSat;     // Computed Parameter: Pitch_rate_UpperSat
                                         //  Referenced by: '<S5>/Pitch_rate'

    real32_T Pitch_rate_LowerSat;     // Computed Parameter: Pitch_rate_LowerSat
                                         //  Referenced by: '<S5>/Pitch_rate'

    real32_T Integrator_gainval;       // Computed Parameter: Integrator_gainval
                                          //  Referenced by: '<S41>/Integrator'

    real32_T Delay_InitialCondition;
                                   // Computed Parameter: Delay_InitialCondition
                                      //  Referenced by: '<S5>/Delay'

    real32_T antiWU_Gain_Gain;         // Computed Parameter: antiWU_Gain_Gain
                                          //  Referenced by: '<S5>/antiWU_Gain'

    real32_T Delay1_InitialCondition;
                                  // Computed Parameter: Delay1_InitialCondition
                                     //  Referenced by: '<S5>/Delay1'

    real32_T antiWU_Gain1_Gain;        // Computed Parameter: antiWU_Gain1_Gain
                                          //  Referenced by: '<S5>/antiWU_Gain1'

    uint16_T Saturation_UpperSat;     // Computed Parameter: Saturation_UpperSat
                                         //  Referenced by: '<S1>/Saturation'

    uint16_T Saturation_LowerSat;     // Computed Parameter: Saturation_LowerSat
                                         //  Referenced by: '<S1>/Saturation'

  };

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  FW_px4_AlgorithmModelClass();

  // Destructor
  ~FW_px4_AlgorithmModelClass();

  // Root-level structure-based inputs set method

  // Root inports set method
  void setExternalInputs(const ExtU_FW_att_control_codeblock_T
    * pExtU_FW_att_control_codeblock_T)
  {
    FW_att_control_codeblock_fly_U = *pExtU_FW_att_control_codeblock_T;
  }

  // Root-level structure-based outputs get method

  // Root outports get method
  const FW_px4_AlgorithmModelClass::ExtY_FW_att_control_codeblock_T
    & getExternalOutputs() const
  {
    return FW_att_control_codeblock_fly_Y;
  }

  // Tunable parameters
  static P_FW_att_control_codeblock_fl_T FW_att_control_codeblock_fly_P;
  // private data and function members
 private:

  // Block signals
  B_FW_att_control_codeblock_fl_T FW_att_control_codeblock_fly_B;

  // Block states
  DW_FW_att_control_codeblock_f_T FW_att_control_codeblock_fly_DW;

  // External inputs
  ExtU_FW_att_control_codeblock_T FW_att_control_codeblock_fly_U;

  // External outputs
  ExtY_FW_att_control_codeblock_T FW_att_control_codeblock_fly_Y;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S7>/Data Type Duplicate' : Unused code path elimination
//  Block '<S8>/Data Type Duplicate' : Unused code path elimination


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
//  '<Root>' : 'FW_att_control_codeblock_fly'
//  '<S1>'   : 'FW_att_control_codeblock_fly/FW_Attitude Control1'
//  '<S2>'   : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl'
//  '<S3>'   : 'FW_att_control_codeblock_fly/FW_Attitude Control1/pwm_out1'
//  '<S4>'   : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate'
//  '<S5>'   : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Roll-pitch_rate_controller'
//  '<S6>'   : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control'
//  '<S7>'   : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Discrete Derivative'
//  '<S8>'   : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Discrete Derivative1'
//  '<S9>'   : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller'
//  '<S10>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Anti-windup'
//  '<S11>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/D Gain'
//  '<S12>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Filter'
//  '<S13>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Filter ICs'
//  '<S14>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/I Gain'
//  '<S15>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Ideal P Gain'
//  '<S16>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Ideal P Gain Fdbk'
//  '<S17>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Integrator'
//  '<S18>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Integrator ICs'
//  '<S19>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/N Copy'
//  '<S20>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/N Gain'
//  '<S21>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/P Copy'
//  '<S22>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Parallel P Gain'
//  '<S23>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Reset Signal'
//  '<S24>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Saturation'
//  '<S25>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Saturation Fdbk'
//  '<S26>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Sum'
//  '<S27>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Sum Fdbk'
//  '<S28>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tracking Mode'
//  '<S29>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tracking Mode Sum'
//  '<S30>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tsamp - Integral'
//  '<S31>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tsamp - Ngain'
//  '<S32>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/postSat Signal'
//  '<S33>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/preSat Signal'
//  '<S34>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Anti-windup/Passthrough'
//  '<S35>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/D Gain/Disabled'
//  '<S36>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Filter/Disabled'
//  '<S37>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Filter ICs/Disabled'
//  '<S38>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/I Gain/Internal Parameters'
//  '<S39>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Ideal P Gain/Passthrough'
//  '<S40>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S41>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Integrator/Discrete'
//  '<S42>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Integrator ICs/Internal IC'
//  '<S43>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/N Copy/Disabled wSignal Specification'
//  '<S44>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/N Gain/Disabled'
//  '<S45>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/P Copy/Disabled'
//  '<S46>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Parallel P Gain/Internal Parameters'
//  '<S47>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Reset Signal/Disabled'
//  '<S48>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Saturation/Passthrough'
//  '<S49>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Saturation Fdbk/Disabled'
//  '<S50>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Sum/Sum_PI'
//  '<S51>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Sum Fdbk/Disabled'
//  '<S52>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tracking Mode/Disabled'
//  '<S53>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tracking Mode Sum/Passthrough'
//  '<S54>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tsamp - Integral/Passthrough'
//  '<S55>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tsamp - Ngain/Passthrough'
//  '<S56>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/postSat Signal/Forward_Path'
//  '<S57>'  : 'FW_att_control_codeblock_fly/FW_Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/preSat Signal/Forward_Path'

#endif                            // RTW_HEADER_FW_att_control_codeblock_fly_h_

//
// File trailer for generated code.
//
// [EOF]
//
