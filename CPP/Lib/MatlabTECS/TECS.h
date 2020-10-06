
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TECS.h
//
// Code generated for Simulink model 'TECS'.
//
// Model version                  : 1.27
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Mon Oct  5 14:56:44 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_TECS_h_
#define RTW_HEADER_TECS_h_
#include <MatlabTECS/rtwtypes.h>
#include <MatlabTECS/TECS_types.h>
#include <stddef.h>

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Class declaration for model TECS
class fw_TECSModelClass {
  // public data and function members
 public:
  // Block signals (default storage)
  typedef struct {
    real_T SKE_rate_dem;               // '<S1>/Product'
    real_T SKE_rate;                   // '<S1>/Product1'
  } B_TECS_T;

  // Block states (default storage) for system '<Root>'
  typedef struct {
    real_T Integrator_DSTATE;          // '<S136>/Integrator'
  } DW_TECS_T;

  // External inputs (root inport signals with default storage)
  typedef struct {
    real_T set_Airspeed;               // '<Root>/set_Airspeed'
    real_T set_ALT;                    // '<Root>/set_ALT'
    real_T Airspeed;                   // '<Root>/Airspeed'
    real_T ALT;                        // '<Root>/ALT'
    real_T ax;                         // '<Root>/ax'
    real_T vz;                         // '<Root>/vz'
  } ExtU_TECS_T;

  // External outputs (root outports fed by signals with default storage)
  typedef struct {
    real_T throttle;                   // '<Root>/throttle'
    real_T pitch;                      // '<Root>/pitch'
  } ExtY_TECS_T;

  // Parameters (default storage)
  struct P_TECS_T {
    real_T FW_T_INTEGRAL_GAIN_I;       // Mask Parameter: FW_T_INTEGRAL_GAIN_I
                                          //  Referenced by: '<S133>/Integral Gain'

    real_T FW_T_INTEGRAL_GAIN_InitialCondi;
                              // Mask Parameter: FW_T_INTEGRAL_GAIN_InitialCondi
                                 //  Referenced by: '<S136>/Integrator'

    real_T STE_to_throttle_LowerSaturation;
                              // Mask Parameter: STE_to_throttle_LowerSaturation
                                 //  Referenced by: '<S338>/Saturation'

    real_T FW_T_HRATE_P_P;             // Mask Parameter: FW_T_HRATE_P_P
                                          //  Referenced by: '<S41>/Proportional Gain'

    real_T FW_T_SRATE_P_P;             // Mask Parameter: FW_T_SRATE_P_P
                                          //  Referenced by: '<S89>/Proportional Gain'

    real_T FW_T_PITCH_DAMP_P;          // Mask Parameter: FW_T_PITCH_DAMP_P
                                          //  Referenced by: '<S189>/Proportional Gain'

    real_T FW_T_THR_DAMP_P;            // Mask Parameter: FW_T_THR_DAMP_P
                                          //  Referenced by: '<S288>/Proportional Gain'

    real_T FW_T_INTEG_GAIN_P;          // Mask Parameter: FW_T_INTEG_GAIN_P
                                          //  Referenced by: '<S240>/Proportional Gain'

    real_T STE_to_throttle_P;          // Mask Parameter: STE_to_throttle_P
                                          //  Referenced by: '<S336>/Proportional Gain'

    real_T STE_to_throttle_UpperSaturation;
                              // Mask Parameter: STE_to_throttle_UpperSaturation
                                 //  Referenced by: '<S338>/Saturation'

    real_T ACCEL_ONE_G_Gain;           // Expression: ACCEL_ONE_G
                                          //  Referenced by: '<S1>/ACCEL_ONE_G'

    real_T ACCEL_ONE_G2_Gain;          // Expression: ACCEL_ONE_G
                                          //  Referenced by: '<S1>/ACCEL_ONE_G2'

    real_T Gain_Gain;                  // Expression: 1/2
                                          //  Referenced by: '<S1>/Gain'

    real_T Gain1_Gain;                 // Expression: 1/2
                                          //  Referenced by: '<S1>/Gain1'

    real_T FW_T_HRATE_FF_Gain;         // Expression: FW_T_HRATE_FF
                                          //  Referenced by: '<S1>/FW_T_HRATE_FF'

    real_T ACCEL_ONE_G1_Gain;          // Expression: ACCEL_ONE_G
                                          //  Referenced by: '<S1>/ACCEL_ONE_G1'

    real_T ACCEL_ONE_G3_Gain;          // Expression: ACCEL_ONE_G
                                          //  Referenced by: '<S1>/ACCEL_ONE_G3'

    real_T FW_T_SPDWEIGHT_Gain;        // Expression: FW_T_SPDWEIGHT
                                          //  Referenced by: '<S101>/FW_T_SPDWEIGHT'

    real_T Integrator_gainval;         // Computed Parameter: Integrator_gainval
                                          //  Referenced by: '<S136>/Integrator'

    real_T FW_T_TIME_CONST_Gain;       // Expression: FW_T_TIME_CONST
                                          //  Referenced by: '<S101>/FW_T_TIME_CONST_'

    real_T FW_T_TIME_CONST_Gain_p;     // Expression: FW_T_TIME_CONST
                                          //  Referenced by: '<S101>/FW_T_TIME_CONST'

    real_T ACCEL_ONE_G_Gain_j;         // Expression: ACCEL_ONE_G
                                          //  Referenced by: '<S101>/ACCEL_ONE_G'

    real_T Saturation_UpperSat;        // Expression: 1
                                          //  Referenced by: '<S101>/Saturation'

    real_T Saturation_LowerSat;        // Expression: -1
                                          //  Referenced by: '<S101>/Saturation'

    real_T FW_T_PRE_GAIN_Gain;         // Expression: FW_T_PRE_GAIN
                                          //  Referenced by: '<S102>/FW_T_PRE_GAIN'

    real_T FW_THR_CRUISE_Value;        // Expression: FW_THR_CRUISE
                                          //  Referenced by: '<S102>/FW_THR_CRUISE'

    real_T Saturation_UpperSat_i;      // Expression: 1
                                          //  Referenced by: '<S102>/Saturation'

    real_T Saturation_LowerSat_f;      // Expression: 0
                                          //  Referenced by: '<S102>/Saturation'

    real_T Saturation1_UpperSat;       // Expression: 1
                                          //  Referenced by: '<S102>/Saturation1'

    real_T Saturation1_LowerSat;       // Expression: 0
                                          //  Referenced by: '<S102>/Saturation1'

  };

  // Real-time Model Data Structure
  struct RT_MODEL_TECS_T {
    const char_T *errorStatus;
  };

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  fw_TECSModelClass();

  // Destructor
  ~fw_TECSModelClass();

  // Root-level structure-based inputs set method

  // Root inports set method
  void setExternalInputs(const ExtU_TECS_T* pExtU_TECS_T)
  {
    TECS_U = *pExtU_TECS_T;
  }

  // Root-level structure-based outputs get method

  // Root outports get method
  const fw_TECSModelClass::ExtY_TECS_T & getExternalOutputs() const
  {
    return TECS_Y;
  }

  // Real-Time Model get method
  fw_TECSModelClass::RT_MODEL_TECS_T * getRTM();

  // private data and function members
 private:
  // Tunable parameters
  static P_TECS_T TECS_P;

  // Block signals
  B_TECS_T TECS_B;

  // Block states
  DW_TECS_T TECS_DW;

  // External inputs
  ExtU_TECS_T TECS_U;

  // External outputs
  ExtY_TECS_T TECS_Y;

  // Real-Time Model
  RT_MODEL_TECS_T TECS_M;
};
#endif
//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S101>/Scope' : Unused code path elimination


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
//  '<Root>' : 'TECS'
//  '<S1>'   : 'TECS/TECS'
//  '<S2>'   : 'TECS/TECS/FW_T_HRATE_P'
//  '<S3>'   : 'TECS/TECS/FW_T_SRATE_P'
//  '<S4>'   : 'TECS/TECS/TECS'
//  '<S5>'   : 'TECS/TECS/FW_T_HRATE_P/Anti-windup'
//  '<S6>'   : 'TECS/TECS/FW_T_HRATE_P/D Gain'
//  '<S7>'   : 'TECS/TECS/FW_T_HRATE_P/Filter'
//  '<S8>'   : 'TECS/TECS/FW_T_HRATE_P/Filter ICs'
