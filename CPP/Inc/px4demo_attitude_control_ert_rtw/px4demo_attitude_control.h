/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: px4demo_attitude_control.h
 *
 * Code generated for Simulink model 'px4demo_attitude_control'.
 *
 * Model version                  : 1.25
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Sat Jul 11 16:13:56 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_px4demo_attitude_control_h_
#define RTW_HEADER_px4demo_attitude_control_h_
#include <math.h>
#include <stddef.h>
#ifndef px4demo_attitude_control_COMMON_INCLUDES_
# define px4demo_attitude_control_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                           /* px4demo_attitude_control_COMMON_INCLUDES_ */

#include "px4demo_attitude_control_types.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Sum;                          /* '<S243>/Sum' */
  real_T Saturation;                   /* '<S241>/Saturation' */
  real32_T Sum18;                      /* '<S2>/Sum18' */
} B_px4demo_attitude_control_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S234>/Integrator' */
  real32_T Integrator_DSTATE_g;        /* '<S138>/Integrator' */
  real32_T Integrator_DSTATE_b;        /* '<S186>/Integrator' */
  real32_T Integrator_DSTATE_bd;       /* '<S42>/Integrator' */
  real32_T Integrator_DSTATE_h;        /* '<S90>/Integrator' */
} DW_px4demo_attitude_control_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T phi;                        /* '<Root>/In1' */
  real32_T theta;                      /* '<Root>/In2' */
  uint16_T target_roll;                /* '<Root>/In3' */
  uint16_T target_pitch;               /* '<Root>/In4' */
  uint16_T target_thrust;              /* '<Root>/In5' */
  uint16_T target_yaw;                 /* '<Root>/In6' */
  uint16_T armingControl;              /* '<Root>/In7' */
  real32_T p;                          /* '<Root>/In8' */
  real32_T q;                          /* '<Root>/In9' */
  real32_T r;                          /* '<Root>/In10' */
} ExtU_px4demo_attitude_control_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  boolean_T ARMControl;                /* '<Root>/ARM Control' */
  uint16_T PWM[6];                     /* '<Root>/PWM' */
} ExtY_px4demo_attitude_control_T;

/* Parameters (default storage) */
struct P_px4demo_attitude_control_T_ {
  real32_T KiPitchAttitude;            /* Variable: KiPitchAttitude
                                        * Referenced by: '<S39>/Integral Gain'
                                        */
  real32_T KiPitchRate;                /* Variable: KiPitchRate
                                        * Referenced by: '<S87>/Integral Gain'
                                        */
  real32_T KiRollAttitude;             /* Variable: KiRollAttitude
                                        * Referenced by: '<S135>/Integral Gain'
                                        */
  real32_T KiRollRate;                 /* Variable: KiRollRate
                                        * Referenced by: '<S183>/Integral Gain'
                                        */
  real32_T KiYawRate;                  /* Variable: KiYawRate
                                        * Referenced by: '<S231>/Integral Gain'
                                        */
  real32_T KpPitchAttitude;            /* Variable: KpPitchAttitude
                                        * Referenced by: '<S47>/Proportional Gain'
                                        */
  real32_T KpPitchRate;                /* Variable: KpPitchRate
                                        * Referenced by: '<S95>/Proportional Gain'
                                        */
  real32_T KpRollAttitude;             /* Variable: KpRollAttitude
                                        * Referenced by: '<S143>/Proportional Gain'
                                        */
  real32_T KpRollRate;                 /* Variable: KpRollRate
                                        * Referenced by: '<S191>/Proportional Gain'
                                        */
  real32_T KpYawRate;                  /* Variable: KpYawRate
                                        * Referenced by: '<S239>/Proportional Gain'
                                        */
  real_T yaw_rate_InitialConditionForIntegrator;
                       /* Mask Parameter: yaw_rate_InitialConditionForIntegrator
                        * Referenced by: '<S234>/Integrator'
                        */
  real_T yaw_rate_Kb;                  /* Mask Parameter: yaw_rate_Kb
                                        * Referenced by: '<S227>/Kb'
                                        */
  real_T yaw_rate_LowerSaturationLimit;
                                /* Mask Parameter: yaw_rate_LowerSaturationLimit
                                 * Referenced by: '<S241>/Saturation'
                                 */
  real_T yaw_rate_UpperSaturationLimit;
                                /* Mask Parameter: yaw_rate_UpperSaturationLimit
                                 * Referenced by: '<S241>/Saturation'
                                 */
  real32_T roll_attitude_InitialConditionForIntegrator;
                  /* Mask Parameter: roll_attitude_InitialConditionForIntegrator
                   * Referenced by: '<S138>/Integrator'
                   */
  real32_T roll_rate_InitialConditionForIntegrator;
                      /* Mask Parameter: roll_rate_InitialConditionForIntegrator
                       * Referenced by: '<S186>/Integrator'
                       */
  real32_T pitch_attitude_InitialConditionForIntegrator;
                 /* Mask Parameter: pitch_attitude_InitialConditionForIntegrator
                  * Referenced by: '<S42>/Integrator'
                  */
  real32_T pitch_rate_InitialConditionForIntegrator;
                     /* Mask Parameter: pitch_rate_InitialConditionForIntegrator
                      * Referenced by: '<S90>/Integrator'
                      */
  real32_T pitch_rate_Kb;              /* Mask Parameter: pitch_rate_Kb
                                        * Referenced by: '<S83>/Kb'
                                        */
  real32_T pitch_attitude_Kb;          /* Mask Parameter: pitch_attitude_Kb
                                        * Referenced by: '<S35>/Kb'
                                        */
  real32_T roll_rate_Kb;               /* Mask Parameter: roll_rate_Kb
                                        * Referenced by: '<S179>/Kb'
                                        */
  real32_T roll_attitude_Kb;           /* Mask Parameter: roll_attitude_Kb
                                        * Referenced by: '<S131>/Kb'
                                        */
  real32_T roll_attitude_LowerSaturationLimit;
                           /* Mask Parameter: roll_attitude_LowerSaturationLimit
                            * Referenced by: '<S145>/Saturation'
                            */
  real32_T roll_rate_LowerSaturationLimit;
                               /* Mask Parameter: roll_rate_LowerSaturationLimit
                                * Referenced by: '<S193>/Saturation'
                                */
  real32_T pitch_attitude_LowerSaturationLimit;
                          /* Mask Parameter: pitch_attitude_LowerSaturationLimit
                           * Referenced by: '<S49>/Saturation'
                           */
  real32_T pitch_rate_LowerSaturationLimit;
                              /* Mask Parameter: pitch_rate_LowerSaturationLimit
                               * Referenced by: '<S97>/Saturation'
                               */
  real32_T roll_attitude_UpperSaturationLimit;
                           /* Mask Parameter: roll_attitude_UpperSaturationLimit
                            * Referenced by: '<S145>/Saturation'
                            */
  real32_T roll_rate_UpperSaturationLimit;
                               /* Mask Parameter: roll_rate_UpperSaturationLimit
                                * Referenced by: '<S193>/Saturation'
                                */
  real32_T pitch_attitude_UpperSaturationLimit;
                          /* Mask Parameter: pitch_attitude_UpperSaturationLimit
                           * Referenced by: '<S49>/Saturation'
                           */
  real32_T pitch_rate_UpperSaturationLimit;
                              /* Mask Parameter: pitch_rate_UpperSaturationLimit
                               * Referenced by: '<S97>/Saturation'
                               */
  uint16_T CompareToConstant3_const; /* Mask Parameter: CompareToConstant3_const
                                      * Referenced by: '<S5>/Constant'
                                      */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S234>/Integrator'
                                        */
  real32_T urads_max_Gain;             /* Computed Parameter: urads_max_Gain
                                        * Referenced by: '<S2>/1 // rads_max'
                                        */
  real32_T urad_max_Gain;              /* Computed Parameter: urad_max_Gain
                                        * Referenced by: '<S2>/1 // rad_max'
                                        */
  real32_T Saturation9_UpperSat;     /* Computed Parameter: Saturation9_UpperSat
                                      * Referenced by: '<S3>/Saturation9'
                                      */
  real32_T Saturation9_LowerSat;     /* Computed Parameter: Saturation9_LowerSat
                                      * Referenced by: '<S3>/Saturation9'
                                      */
  real32_T Saturation8_UpperSat;     /* Computed Parameter: Saturation8_UpperSat
                                      * Referenced by: '<S3>/Saturation8'
                                      */
  real32_T Saturation8_LowerSat;     /* Computed Parameter: Saturation8_LowerSat
                                      * Referenced by: '<S3>/Saturation8'
                                      */
  real32_T Gain2_Gain[2];              /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S3>/Gain2'
                                        */
  real32_T Integrator_gainval_i;     /* Computed Parameter: Integrator_gainval_i
                                      * Referenced by: '<S138>/Integrator'
                                      */
  real32_T Integrator_gainval_h;     /* Computed Parameter: Integrator_gainval_h
                                      * Referenced by: '<S186>/Integrator'
                                      */
  real32_T Integrator_gainval_d;     /* Computed Parameter: Integrator_gainval_d
                                      * Referenced by: '<S42>/Integrator'
                                      */
  real32_T Integrator_gainval_dp;   /* Computed Parameter: Integrator_gainval_dp
                                     * Referenced by: '<S90>/Integrator'
                                     */
  real32_T urads_max_yaw_Gain;         /* Computed Parameter: urads_max_yaw_Gain
                                        * Referenced by: '<S2>/1 // rads_max_yaw'
                                        */
  real32_T Saturation7_UpperSat;     /* Computed Parameter: Saturation7_UpperSat
                                      * Referenced by: '<S3>/Saturation7'
                                      */
  real32_T Saturation7_LowerSat;     /* Computed Parameter: Saturation7_LowerSat
                                      * Referenced by: '<S3>/Saturation7'
                                      */
  real32_T Saturation10_UpperSat;   /* Computed Parameter: Saturation10_UpperSat
                                     * Referenced by: '<S3>/Saturation10'
                                     */
  real32_T Saturation10_LowerSat;   /* Computed Parameter: Saturation10_LowerSat
                                     * Referenced by: '<S3>/Saturation10'
                                     */
  uint16_T Output_Limits1_UpperSat;
                                  /* Computed Parameter: Output_Limits1_UpperSat
                                   * Referenced by: '<Root>/Output_Limits1'
                                   */
  uint16_T Output_Limits1_LowerSat;
                                  /* Computed Parameter: Output_Limits1_LowerSat
                                   * Referenced by: '<Root>/Output_Limits1'
                                   */
};

/* Real-time Model Data Structure */
struct tag_RTM_px4demo_attitude_control_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
extern P_px4demo_attitude_control_T px4demo_attitude_control_P;

/* Block signals (default storage) */
extern B_px4demo_attitude_control_T px4demo_attitude_control_B;

/* Block states (default storage) */
extern DW_px4demo_attitude_control_T px4demo_attitude_control_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_px4demo_attitude_control_T px4demo_attitude_control_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_px4demo_attitude_control_T px4demo_attitude_control_Y;

/* Model entry point functions */
extern void px4demo_attitude_control_initialize(void);
extern void px4demo_attitude_control_step(void);
extern void px4demo_attitude_control_terminate(void);

/* Real-time Model object */
extern RT_MODEL_px4demo_attitude_control_T *const px4demo_attitude_control_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'px4demo_attitude_control'
 * '<S1>'   : 'px4demo_attitude_control/ARMINGControl'
 * '<S2>'   : 'px4demo_attitude_control/AttitudeControl'
 * '<S3>'   : 'px4demo_attitude_control/InputConditioning'
 * '<S4>'   : 'px4demo_attitude_control/pwm_out1'
 * '<S5>'   : 'px4demo_attitude_control/ARMINGControl/Compare To Constant3'
 * '<S6>'   : 'px4demo_attitude_control/AttitudeControl/pitch_attitude'
 * '<S7>'   : 'px4demo_attitude_control/AttitudeControl/pitch_rate'
 * '<S8>'   : 'px4demo_attitude_control/AttitudeControl/roll_attitude'
 * '<S9>'   : 'px4demo_attitude_control/AttitudeControl/roll_rate'
 * '<S10>'  : 'px4demo_attitude_control/AttitudeControl/yaw_rate'
 * '<S11>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Anti-windup'
 * '<S12>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/D Gain'
 * '<S13>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Filter'
 * '<S14>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Filter ICs'
 * '<S15>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/I Gain'
 * '<S16>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Ideal P Gain'
 * '<S17>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Ideal P Gain Fdbk'
 * '<S18>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Integrator'
 * '<S19>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Integrator ICs'
 * '<S20>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/N Copy'
 * '<S21>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/N Gain'
 * '<S22>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/P Copy'
 * '<S23>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Parallel P Gain'
 * '<S24>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Reset Signal'
 * '<S25>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Saturation'
 * '<S26>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Saturation Fdbk'
 * '<S27>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Sum'
 * '<S28>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Sum Fdbk'
 * '<S29>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Tracking Mode'
 * '<S30>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Tracking Mode Sum'
 * '<S31>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Tsamp - Integral'
 * '<S32>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Tsamp - Ngain'
 * '<S33>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/postSat Signal'
 * '<S34>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/preSat Signal'
 * '<S35>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Anti-windup/Back Calculation'
 * '<S36>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/D Gain/Disabled'
 * '<S37>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Filter/Disabled'
 * '<S38>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Filter ICs/Disabled'
 * '<S39>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/I Gain/Internal Parameters'
 * '<S40>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Ideal P Gain/Passthrough'
 * '<S41>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Ideal P Gain Fdbk/Disabled'
 * '<S42>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Integrator/Discrete'
 * '<S43>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Integrator ICs/Internal IC'
 * '<S44>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/N Copy/Disabled wSignal Specification'
 * '<S45>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/N Gain/Disabled'
 * '<S46>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/P Copy/Disabled'
 * '<S47>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Parallel P Gain/Internal Parameters'
 * '<S48>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Reset Signal/Disabled'
 * '<S49>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Saturation/Enabled'
 * '<S50>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Saturation Fdbk/Disabled'
 * '<S51>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Sum/Sum_PI'
 * '<S52>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Sum Fdbk/Disabled'
 * '<S53>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Tracking Mode/Disabled'
 * '<S54>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Tracking Mode Sum/Passthrough'
 * '<S55>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Tsamp - Integral/Passthrough'
 * '<S56>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/Tsamp - Ngain/Passthrough'
 * '<S57>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/postSat Signal/Forward_Path'
 * '<S58>'  : 'px4demo_attitude_control/AttitudeControl/pitch_attitude/preSat Signal/Forward_Path'
 * '<S59>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Anti-windup'
 * '<S60>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/D Gain'
 * '<S61>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Filter'
 * '<S62>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Filter ICs'
 * '<S63>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/I Gain'
 * '<S64>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Ideal P Gain'
 * '<S65>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Ideal P Gain Fdbk'
 * '<S66>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Integrator'
 * '<S67>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Integrator ICs'
 * '<S68>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/N Copy'
 * '<S69>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/N Gain'
 * '<S70>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/P Copy'
 * '<S71>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Parallel P Gain'
 * '<S72>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Reset Signal'
 * '<S73>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Saturation'
 * '<S74>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Saturation Fdbk'
 * '<S75>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Sum'
 * '<S76>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Sum Fdbk'
 * '<S77>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Tracking Mode'
 * '<S78>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Tracking Mode Sum'
 * '<S79>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Tsamp - Integral'
 * '<S80>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Tsamp - Ngain'
 * '<S81>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/postSat Signal'
 * '<S82>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/preSat Signal'
 * '<S83>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Anti-windup/Back Calculation'
 * '<S84>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/D Gain/Disabled'
 * '<S85>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Filter/Disabled'
 * '<S86>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Filter ICs/Disabled'
 * '<S87>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/I Gain/Internal Parameters'
 * '<S88>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Ideal P Gain/Passthrough'
 * '<S89>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Ideal P Gain Fdbk/Disabled'
 * '<S90>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Integrator/Discrete'
 * '<S91>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Integrator ICs/Internal IC'
 * '<S92>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/N Copy/Disabled wSignal Specification'
 * '<S93>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/N Gain/Disabled'
 * '<S94>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/P Copy/Disabled'
 * '<S95>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Parallel P Gain/Internal Parameters'
 * '<S96>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Reset Signal/Disabled'
 * '<S97>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Saturation/Enabled'
 * '<S98>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Saturation Fdbk/Disabled'
 * '<S99>'  : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Sum/Sum_PI'
 * '<S100>' : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Sum Fdbk/Disabled'
 * '<S101>' : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Tracking Mode/Disabled'
 * '<S102>' : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Tracking Mode Sum/Passthrough'
 * '<S103>' : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Tsamp - Integral/Passthrough'
 * '<S104>' : 'px4demo_attitude_control/AttitudeControl/pitch_rate/Tsamp - Ngain/Passthrough'
 * '<S105>' : 'px4demo_attitude_control/AttitudeControl/pitch_rate/postSat Signal/Forward_Path'
 * '<S106>' : 'px4demo_attitude_control/AttitudeControl/pitch_rate/preSat Signal/Forward_Path'
 * '<S107>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Anti-windup'
 * '<S108>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/D Gain'
 * '<S109>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Filter'
 * '<S110>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Filter ICs'
 * '<S111>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/I Gain'
 * '<S112>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Ideal P Gain'
 * '<S113>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Ideal P Gain Fdbk'
 * '<S114>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Integrator'
 * '<S115>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Integrator ICs'
 * '<S116>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/N Copy'
 * '<S117>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/N Gain'
 * '<S118>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/P Copy'
 * '<S119>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Parallel P Gain'
 * '<S120>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Reset Signal'
 * '<S121>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Saturation'
 * '<S122>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Saturation Fdbk'
 * '<S123>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Sum'
 * '<S124>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Sum Fdbk'
 * '<S125>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Tracking Mode'
 * '<S126>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Tracking Mode Sum'
 * '<S127>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Tsamp - Integral'
 * '<S128>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Tsamp - Ngain'
 * '<S129>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/postSat Signal'
 * '<S130>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/preSat Signal'
 * '<S131>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Anti-windup/Back Calculation'
 * '<S132>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/D Gain/Disabled'
 * '<S133>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Filter/Disabled'
 * '<S134>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Filter ICs/Disabled'
 * '<S135>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/I Gain/Internal Parameters'
 * '<S136>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Ideal P Gain/Passthrough'
 * '<S137>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Ideal P Gain Fdbk/Disabled'
 * '<S138>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Integrator/Discrete'
 * '<S139>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Integrator ICs/Internal IC'
 * '<S140>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/N Copy/Disabled wSignal Specification'
 * '<S141>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/N Gain/Disabled'
 * '<S142>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/P Copy/Disabled'
 * '<S143>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Parallel P Gain/Internal Parameters'
 * '<S144>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Reset Signal/Disabled'
 * '<S145>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Saturation/Enabled'
 * '<S146>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Saturation Fdbk/Disabled'
 * '<S147>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Sum/Sum_PI'
 * '<S148>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Sum Fdbk/Disabled'
 * '<S149>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Tracking Mode/Disabled'
 * '<S150>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Tracking Mode Sum/Passthrough'
 * '<S151>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Tsamp - Integral/Passthrough'
 * '<S152>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/Tsamp - Ngain/Passthrough'
 * '<S153>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/postSat Signal/Forward_Path'
 * '<S154>' : 'px4demo_attitude_control/AttitudeControl/roll_attitude/preSat Signal/Forward_Path'
 * '<S155>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Anti-windup'
 * '<S156>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/D Gain'
 * '<S157>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Filter'
 * '<S158>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Filter ICs'
 * '<S159>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/I Gain'
 * '<S160>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Ideal P Gain'
 * '<S161>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Ideal P Gain Fdbk'
 * '<S162>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Integrator'
 * '<S163>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Integrator ICs'
 * '<S164>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/N Copy'
 * '<S165>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/N Gain'
 * '<S166>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/P Copy'
 * '<S167>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Parallel P Gain'
 * '<S168>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Reset Signal'
 * '<S169>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Saturation'
 * '<S170>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Saturation Fdbk'
 * '<S171>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Sum'
 * '<S172>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Sum Fdbk'
 * '<S173>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Tracking Mode'
 * '<S174>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Tracking Mode Sum'
 * '<S175>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Tsamp - Integral'
 * '<S176>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Tsamp - Ngain'
 * '<S177>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/postSat Signal'
 * '<S178>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/preSat Signal'
 * '<S179>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Anti-windup/Back Calculation'
 * '<S180>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/D Gain/Disabled'
 * '<S181>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Filter/Disabled'
 * '<S182>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Filter ICs/Disabled'
 * '<S183>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/I Gain/Internal Parameters'
 * '<S184>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Ideal P Gain/Passthrough'
 * '<S185>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Ideal P Gain Fdbk/Disabled'
 * '<S186>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Integrator/Discrete'
 * '<S187>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Integrator ICs/Internal IC'
 * '<S188>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/N Copy/Disabled wSignal Specification'
 * '<S189>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/N Gain/Disabled'
 * '<S190>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/P Copy/Disabled'
 * '<S191>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Parallel P Gain/Internal Parameters'
 * '<S192>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Reset Signal/Disabled'
 * '<S193>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Saturation/Enabled'
 * '<S194>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Saturation Fdbk/Disabled'
 * '<S195>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Sum/Sum_PI'
 * '<S196>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Sum Fdbk/Disabled'
 * '<S197>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Tracking Mode/Disabled'
 * '<S198>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Tracking Mode Sum/Passthrough'
 * '<S199>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Tsamp - Integral/Passthrough'
 * '<S200>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/Tsamp - Ngain/Passthrough'
 * '<S201>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/postSat Signal/Forward_Path'
 * '<S202>' : 'px4demo_attitude_control/AttitudeControl/roll_rate/preSat Signal/Forward_Path'
 * '<S203>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Anti-windup'
 * '<S204>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/D Gain'
 * '<S205>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Filter'
 * '<S206>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Filter ICs'
 * '<S207>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/I Gain'
 * '<S208>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Ideal P Gain'
 * '<S209>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Ideal P Gain Fdbk'
 * '<S210>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Integrator'
 * '<S211>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Integrator ICs'
 * '<S212>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/N Copy'
 * '<S213>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/N Gain'
 * '<S214>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/P Copy'
 * '<S215>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Parallel P Gain'
 * '<S216>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Reset Signal'
 * '<S217>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Saturation'
 * '<S218>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Saturation Fdbk'
 * '<S219>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Sum'
 * '<S220>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Sum Fdbk'
 * '<S221>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Tracking Mode'
 * '<S222>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Tracking Mode Sum'
 * '<S223>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Tsamp - Integral'
 * '<S224>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Tsamp - Ngain'
 * '<S225>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/postSat Signal'
 * '<S226>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/preSat Signal'
 * '<S227>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Anti-windup/Back Calculation'
 * '<S228>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/D Gain/Disabled'
 * '<S229>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Filter/Disabled'
 * '<S230>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Filter ICs/Disabled'
 * '<S231>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/I Gain/Internal Parameters'
 * '<S232>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Ideal P Gain/Passthrough'
 * '<S233>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Ideal P Gain Fdbk/Disabled'
 * '<S234>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Integrator/Discrete'
 * '<S235>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Integrator ICs/Internal IC'
 * '<S236>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/N Copy/Disabled wSignal Specification'
 * '<S237>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/N Gain/Disabled'
 * '<S238>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/P Copy/Disabled'
 * '<S239>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Parallel P Gain/Internal Parameters'
 * '<S240>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Reset Signal/Disabled'
 * '<S241>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Saturation/Enabled'
 * '<S242>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Saturation Fdbk/Disabled'
 * '<S243>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Sum/Sum_PI'
 * '<S244>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Sum Fdbk/Disabled'
 * '<S245>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Tracking Mode/Disabled'
 * '<S246>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Tracking Mode Sum/Passthrough'
 * '<S247>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Tsamp - Integral/Passthrough'
 * '<S248>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/Tsamp - Ngain/Passthrough'
 * '<S249>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/postSat Signal/Forward_Path'
 * '<S250>' : 'px4demo_attitude_control/AttitudeControl/yaw_rate/preSat Signal/Forward_Path'
 */
#endif                              /* RTW_HEADER_px4demo_attitude_control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
