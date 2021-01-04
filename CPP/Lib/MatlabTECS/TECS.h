//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: TECS.h
//
// Code generated for Simulink model 'TECS'.
//
// Model version                  : 1.30
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Thu Oct 15 15:30:38 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_TECS_h_
#define RTW_HEADER_TECS_h_
#include <cmath>
#include "rtwtypes.h"
#include "TECS_types.h"

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
    real_T IntegralGain_m;             // '<S34>/Integral Gain'
    real_T SPE_dem;                    // '<S1>/ACCEL_ONE_G'
    real_T SPE_est;                    // '<S1>/ACCEL_ONE_G2'
    real_T SKE_dem;                    // '<S1>/Gain'
  } B_TECS_T;

  // Block states (default storage) for system '<Root>'
  typedef struct {
    real_T Integrator_DSTATE;          // '<S86>/Integrator'
    real_T Integrator_DSTATE_a;        // '<S37>/Integrator'
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
    real_T DiscretePIDController_I;   // Mask Parameter: DiscretePIDController_I
                                         //  Referenced by: '<S34>/Integral Gain'

    real_T DiscretePIDController_I_l;
                                    // Mask Parameter: DiscretePIDController_I_l
                                       //  Referenced by: '<S83>/Integral Gain'

    real_T DiscretePIDController_InitialCo;
                              // Mask Parameter: DiscretePIDController_InitialCo
                                 //  Referenced by: '<S86>/Integrator'

    real_T DiscretePIDController_Initial_f;
                              // Mask Parameter: DiscretePIDController_Initial_f
                                 //  Referenced by: '<S37>/Integrator'

    real_T DiscretePIDController_LowerSatu;
                              // Mask Parameter: DiscretePIDController_LowerSatu
                                 //  Referenced by:
                                 //    '<S79>/DeadZone'
                                 //    '<S93>/Saturation'

    real_T DiscretePIDController_LowerSa_p;
                              // Mask Parameter: DiscretePIDController_LowerSa_p
                                 //  Referenced by:
                                 //    '<S30>/DeadZone'
                                 //    '<S44>/Saturation'

    real_T DiscretePIDController_UpperSatu;
                              // Mask Parameter: DiscretePIDController_UpperSatu
                                 //  Referenced by:
                                 //    '<S79>/DeadZone'
                                 //    '<S93>/Saturation'

    real_T DiscretePIDController_UpperSa_f;
                              // Mask Parameter: DiscretePIDController_UpperSa_f
                                 //  Referenced by:
                                 //    '<S30>/DeadZone'
                                 //    '<S44>/Saturation'

    real_T Constant1_Value;            // Expression: 0
                                          //  Referenced by: '<S30>/Constant1'

    real_T Constant1_Value_k;          // Expression: 0
                                          //  Referenced by: '<S79>/Constant1'

    real_T Integrator_gainval;         // Computed Parameter: Integrator_gainval
                                          //  Referenced by: '<S86>/Integrator'

    real_T ACCEL_ONE_G_Gain;           // Expression: ACCEL_ONE_G
                                          //  Referenced by: '<S1>/ACCEL_ONE_G'

    real_T ACCEL_ONE_G2_Gain;          // Expression: ACCEL_ONE_G
                                          //  Referenced by: '<S1>/ACCEL_ONE_G2'

    real_T Gain_Gain;                  // Expression: 1/2
                                          //  Referenced by: '<S1>/Gain'

    real_T Gain1_Gain;                 // Expression: 1/2
                                          //  Referenced by: '<S1>/Gain1'

    real_T FW_T_HRATE_P_Gain;          // Expression: FW_T_HRATE_P
                                          //  Referenced by: '<S1>/FW_T_HRATE_P'

    real_T ACCEL_ONE_G1_Gain;          // Expression: ACCEL_ONE_G
                                          //  Referenced by: '<S1>/ACCEL_ONE_G1'

    real_T FW_T_SRATE_P_Gain;          // Expression: FW_T_SRATE_P
                                          //  Referenced by: '<S1>/FW_T_SRATE_P'

    real_T ACCEL_ONE_G3_Gain;          // Expression: ACCEL_ONE_G
                                          //  Referenced by: '<S1>/ACCEL_ONE_G3'

    real_T FW_T_THR_DAMP_Gain;         // Expression: FW_T_THR_DAMP
                                          //  Referenced by: '<S4>/FW_T_THR_DAMP'

    real_T STE_to_throttle_Gain;       // Expression: STE_to_throttle
                                          //  Referenced by: '<S4>/STE_to_throttle'

    real_T FW_T_PRE_GAIN_Gain;         // Expression: FW_T_PRE_GAIN
                                          //  Referenced by: '<S4>/FW_T_PRE_GAIN'

    real_T FW_THR_CRUISE_Value;        // Expression: FW_THR_CRUISE
                                          //  Referenced by: '<S4>/FW_THR_CRUISE'

    real_T Saturation_UpperSat;        // Expression: 1
                                          //  Referenced by: '<S4>/Saturation'

    real_T Saturation_LowerSat;        // Expression: 0
                                          //  Referenced by: '<S4>/Saturation'

    real_T Saturation1_UpperSat;       // Expression: 1
                                          //  Referenced by: '<S4>/Saturation1'

    real_T Saturation1_LowerSat;       // Expression: 0
                                          //  Referenced by: '<S4>/Saturation1'

    real_T Integrator_gainval_m;     // Computed Parameter: Integrator_gainval_m
                                        //  Referenced by: '<S37>/Integrator'

    real_T FW_T_SPDWEIGHT_Gain;        // Expression: FW_T_SPDWEIGHT
                                          //  Referenced by: '<S3>/FW_T_SPDWEIGHT'

    real_T STE_T_INTEG_GAIN1_Gain;     // Expression: FW_T_PITCH_DAMP
                                          //  Referenced by: '<S3>/STE_T_INTEG_GAIN1'

    real_T FW_T_P_TIME_CONST_Gain;     // Expression: FW_T_P_TIME_CONST
                                          //  Referenced by: '<S3>/FW_T_P_TIME_CONST_'

    real_T FW_T_P_TIME_CONST_Gain_p;   // Expression: FW_T_P_TIME_CONST
                                          //  Referenced by: '<S3>/FW_T_P_TIME_CONST'

    real_T ACCEL_ONE_G_Gain_j;         // Expression: ACCEL_ONE_G
                                          //  Referenced by: '<S3>/ACCEL_ONE_G'

    real_T Saturation_UpperSat_m;      // Expression: 1
                                          //  Referenced by: '<S3>/Saturation'

    real_T Saturation_LowerSat_n;      // Expression: -1
                                          //  Referenced by: '<S3>/Saturation'

    real_T ZeroGain_Gain;              // Expression: 0
                                          //  Referenced by: '<S30>/ZeroGain'

    real_T ZeroGain_Gain_l;            // Expression: 0
                                          //  Referenced by: '<S79>/ZeroGain'

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

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S3>/Scope9' : Unused code path elimination


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
//  '<S2>'   : 'TECS/TECS/TECS'
//  '<S3>'   : 'TECS/TECS/TECS/pitch_control'
//  '<S4>'   : 'TECS/TECS/TECS/throttle_control'
//  '<S5>'   : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller'
//  '<S6>'   : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Anti-windup'
//  '<S7>'   : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/D Gain'
//  '<S8>'   : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Filter'
//  '<S9>'   : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Filter ICs'
//  '<S10>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/I Gain'
//  '<S11>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Ideal P Gain'
//  '<S12>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Ideal P Gain Fdbk'
//  '<S13>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Integrator'
//  '<S14>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Integrator ICs'
//  '<S15>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/N Copy'
//  '<S16>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/N Gain'
//  '<S17>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/P Copy'
//  '<S18>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Parallel P Gain'
//  '<S19>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Reset Signal'
//  '<S20>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Saturation'
//  '<S21>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Saturation Fdbk'
//  '<S22>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Sum'
//  '<S23>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Sum Fdbk'
//  '<S24>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Tracking Mode'
//  '<S25>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Tracking Mode Sum'
//  '<S26>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Tsamp - Integral'
//  '<S27>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Tsamp - Ngain'
//  '<S28>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/postSat Signal'
//  '<S29>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/preSat Signal'
//  '<S30>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S31>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/D Gain/Disabled'
//  '<S32>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Filter/Disabled'
//  '<S33>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Filter ICs/Disabled'
//  '<S34>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/I Gain/Internal Parameters'
//  '<S35>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Ideal P Gain/Passthrough'
//  '<S36>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S37>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Integrator/Discrete'
//  '<S38>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Integrator ICs/Internal IC'
//  '<S39>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/N Copy/Disabled wSignal Specification'
//  '<S40>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/N Gain/Disabled'
//  '<S41>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/P Copy/Disabled'
//  '<S42>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Parallel P Gain/Disabled'
//  '<S43>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Reset Signal/Disabled'
//  '<S44>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Saturation/Enabled'
//  '<S45>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Saturation Fdbk/Disabled'
//  '<S46>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Sum/Passthrough_I'
//  '<S47>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Sum Fdbk/Disabled'
//  '<S48>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Tracking Mode/Disabled'
//  '<S49>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Tracking Mode Sum/Passthrough'
//  '<S50>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Tsamp - Integral/Passthrough'
//  '<S51>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/Tsamp - Ngain/Passthrough'
//  '<S52>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/postSat Signal/Forward_Path'
//  '<S53>'  : 'TECS/TECS/TECS/pitch_control/Discrete PID Controller/preSat Signal/Forward_Path'
//  '<S54>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller'
//  '<S55>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Anti-windup'
//  '<S56>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/D Gain'
//  '<S57>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Filter'
//  '<S58>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Filter ICs'
//  '<S59>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/I Gain'
//  '<S60>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Ideal P Gain'
//  '<S61>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Ideal P Gain Fdbk'
//  '<S62>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Integrator'
//  '<S63>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Integrator ICs'
//  '<S64>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/N Copy'
//  '<S65>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/N Gain'
//  '<S66>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/P Copy'
//  '<S67>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Parallel P Gain'
//  '<S68>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Reset Signal'
//  '<S69>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Saturation'
//  '<S70>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Saturation Fdbk'
//  '<S71>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Sum'
//  '<S72>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Sum Fdbk'
//  '<S73>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Tracking Mode'
//  '<S74>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Tracking Mode Sum'
//  '<S75>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Tsamp - Integral'
//  '<S76>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Tsamp - Ngain'
//  '<S77>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/postSat Signal'
//  '<S78>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/preSat Signal'
//  '<S79>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel'
//  '<S80>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/D Gain/Disabled'
//  '<S81>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Filter/Disabled'
//  '<S82>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Filter ICs/Disabled'
//  '<S83>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/I Gain/Internal Parameters'
//  '<S84>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Ideal P Gain/Passthrough'
//  '<S85>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S86>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Integrator/Discrete'
//  '<S87>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Integrator ICs/Internal IC'
//  '<S88>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/N Copy/Disabled wSignal Specification'
//  '<S89>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/N Gain/Disabled'
//  '<S90>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/P Copy/Disabled'
//  '<S91>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Parallel P Gain/Disabled'
//  '<S92>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Reset Signal/Disabled'
//  '<S93>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Saturation/Enabled'
//  '<S94>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Saturation Fdbk/Disabled'
//  '<S95>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Sum/Passthrough_I'
//  '<S96>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Sum Fdbk/Disabled'
//  '<S97>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Tracking Mode/Disabled'
//  '<S98>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Tracking Mode Sum/Passthrough'
//  '<S99>'  : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Tsamp - Integral/Passthrough'
//  '<S100>' : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/Tsamp - Ngain/Passthrough'
//  '<S101>' : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/postSat Signal/Forward_Path'
//  '<S102>' : 'TECS/TECS/TECS/throttle_control/Discrete PID Controller/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_TECS_h_

//
// File trailer for generated code.
//
// [EOF]
//
