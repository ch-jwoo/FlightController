/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Second_att_control_codeblock.h
 *
 * Code generated for Simulink model 'Second_att_control_codeblock'.
 *
 * Model version                  : 1.11
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Tue Jul 14 00:19:24 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Second_att_control_codeblock_h_
#define RTW_HEADER_Second_att_control_codeblock_h_
#include <math.h>
#ifndef Second_att_control_codeblock_COMMON_INCLUDES_
# define Second_att_control_codeblock_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                       /* Second_att_control_codeblock_COMMON_INCLUDES_ */

#include "Second_att_control_codeblock_types.h"

/* Macros for accessing real-time model data structure */

/* Block signals (default storage) */
typedef struct {
  real_T Filter;                       /* '<S136>/Filter' */
  real_T SumD;                         /* '<S136>/SumD' */
  real_T FilterCoefficient;            /* '<S144>/Filter Coefficient' */
  real_T Sum;                          /* '<S150>/Sum' */
  real_T Saturation;                   /* '<S148>/Saturation' */
  real32_T DataTypeConversion;         /* '<S4>/Data Type Conversion' */
  real32_T Fcn2;                       /* '<S4>/Fcn2' */
  real32_T Saturation9;                /* '<S4>/Saturation9' */
  real32_T DataTypeConversion1;        /* '<S4>/Data Type Conversion1' */
  real32_T Fcn5;                       /* '<S4>/Fcn5' */
  real32_T Saturation8;                /* '<S4>/Saturation8' */
  real32_T Gain2[2];                   /* '<S4>/Gain2' */
  real32_T urad_max[2];                /* '<S4>/1//rad_max' */
  real32_T FF_roll_gain;               /* '<S7>/FF_roll_gain' */
  real32_T Sum_f;                      /* '<S7>/Sum' */
  real32_T ProportionalGain;           /* '<S48>/Proportional Gain' */
  real32_T Integrator;                 /* '<S43>/Integrator' */
  real32_T Sum_j;                      /* '<S52>/Sum' */
  real32_T Sum1;                       /* '<S7>/Sum1' */
  real32_T Sum_c;                      /* '<S8>/Sum' */
  real32_T ProportionalGain_b;         /* '<S194>/Proportional Gain' */
  real32_T Integrator_b;               /* '<S189>/Integrator' */
  real32_T DerivativeGain;             /* '<S183>/Derivative Gain' */
  real32_T Filter_h;                   /* '<S184>/Filter' */
  real32_T SumD_h;                     /* '<S184>/SumD' */
  real32_T FilterCoefficient_a;        /* '<S192>/Filter Coefficient' */
  real32_T Sum_n;                      /* '<S198>/Sum' */
  real32_T Saturation_b;               /* '<S196>/Saturation' */
  real32_T FF_pitch_gain;              /* '<S7>/FF_pitch_gain' */
  real32_T Sum2;                       /* '<S7>/Sum2' */
  real32_T ProportionalGain_l;         /* '<S96>/Proportional Gain' */
  real32_T Integrator_f;               /* '<S91>/Integrator' */
  real32_T Sum_l;                      /* '<S100>/Sum' */
  real32_T Sum3;                       /* '<S7>/Sum3' */
  real32_T Sum1_h;                     /* '<S8>/Sum1' */
  real32_T ProportionalGain_b4;        /* '<S146>/Proportional Gain' */
  real32_T Integrator_a;               /* '<S141>/Integrator' */
  real32_T DerivativeGain_o;           /* '<S135>/Derivative Gain' */
  real32_T DataTypeConversion2;        /* '<S4>/Data Type Conversion2' */
  real32_T Fcn7;                       /* '<S4>/Fcn7' */
  real32_T Saturation7;                /* '<S4>/Saturation7' */
  real32_T Sum_m;                      /* '<S9>/Sum' */
  real32_T Gain;                       /* '<S9>/Gain' */
  real32_T ProportionalGain_j;         /* '<S243>/Proportional Gain' */
  real32_T Integrator_d;               /* '<S238>/Integrator' */
  real32_T Sum_f3;                     /* '<S247>/Sum' */
  real32_T Saturation_o;               /* '<S245>/Saturation' */
  real32_T DataTypeConversion3;        /* '<S4>/Data Type Conversion3' */
  real32_T Fcn6;                       /* '<S4>/Fcn6' */
  real32_T Saturation10;               /* '<S4>/Saturation10' */
  real32_T IntegralGain;               /* '<S40>/Integral Gain' */
  real32_T IntegralGain_f;             /* '<S88>/Integral Gain' */
  real32_T IntegralGain_d;             /* '<S186>/Integral Gain' */
  real32_T IntegralGain_e;             /* '<S138>/Integral Gain' */
  real32_T IntegralGain_h;             /* '<S235>/Integral Gain' */
  uint16_T M1;                         /* '<S1>/pwm_out1' */
  uint16_T M2;                         /* '<S1>/pwm_out1' */
  uint16_T M3;                         /* '<S1>/pwm_out1' */
  uint16_T M4;                         /* '<S1>/pwm_out1' */
  uint16_T M5;                         /* '<S1>/pwm_out1' */
  uint16_T M6;                         /* '<S1>/pwm_out1' */
} B_Second_att_control_codebloc_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Filter_DSTATE;                /* '<S136>/Filter' */
  real_T SumD_DWORK1;                  /* '<S136>/SumD' */
  real32_T Integrator_DSTATE;          /* '<S43>/Integrator' */
  real32_T Integrator_DSTATE_n;        /* '<S189>/Integrator' */
  real32_T Filter_DSTATE_n;            /* '<S184>/Filter' */
  real32_T Integrator_DSTATE_l;        /* '<S91>/Integrator' */
  real32_T Integrator_DSTATE_d;        /* '<S141>/Integrator' */
  real32_T Integrator_DSTATE_j;        /* '<S238>/Integrator' */
} DW_Second_att_control_codeblo_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T Roll;                       /* '<Root>/Roll' */
  real32_T Pitch;                      /* '<Root>/Pitch' */
  real32_T p;                          /* '<Root>/p' */
  real32_T q;                          /* '<Root>/q' */
  real32_T r;                          /* '<Root>/r' */
  uint16_T set_thrust;                 /* '<Root>/set_thrust' */
  uint16_T set_roll;                   /* '<Root>/set_roll' */
  uint16_T set_pitch;                  /* '<Root>/set_pitch' */
  uint16_T set_yaw;                    /* '<Root>/set_yaw' */
  uint16_T Arm_cmd;                    /* '<Root>/Arm_cmd' */
} ExtU_Second_att_control_codeb_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint16_T PWM_OUT[6];                 /* '<Root>/PWM_OUT' */
  boolean_T ARMControl;                /* '<Root>/ARM Control' */
} ExtY_Second_att_control_codeb_T;

/* Block signals (default storage) */
extern B_Second_att_control_codebloc_T Second_att_control_codeblock_B;

/* Block states (default storage) */
extern DW_Second_att_control_codeblo_T Second_att_control_codeblock_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Second_att_control_codeb_T Second_att_control_codeblock_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Second_att_control_codeb_T Second_att_control_codeblock_Y;

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real32_T Angle_rate_pitch_kI;   /* Variable: Angle_rate_pitch_kI
                                        * Referenced by: '<S88>/Integral Gain'
                                        */
extern real32_T Angle_rate_pitch_kP;   /* Variable: Angle_rate_pitch_kP
                                        * Referenced by: '<S96>/Proportional Gain'
                                        */
extern real32_T Angle_rate_roll_PI_kI; /* Variable: Angle_rate_roll_PI_kI
                                        * Referenced by: '<S40>/Integral Gain'
                                        */
extern real32_T Angle_rate_roll_PI_kP; /* Variable: Angle_rate_roll_PI_kP
                                        * Referenced by: '<S48>/Proportional Gain'
                                        */
extern real32_T kD_Pitch_rate_PID;     /* Variable: kD_Pitch_rate_PID
                                        * Referenced by: '<S135>/Derivative Gain'
                                        */
extern real32_T kD_Roll_rate_PID;      /* Variable: kD_Roll_rate_PID
                                        * Referenced by: '<S183>/Derivative Gain'
                                        */
extern real32_T kI_Pitch_rate_PID;     /* Variable: kI_Pitch_rate_PID
                                        * Referenced by: '<S138>/Integral Gain'
                                        */
extern real32_T kI_Roll_rate_PID;      /* Variable: kI_Roll_rate_PID
                                        * Referenced by: '<S186>/Integral Gain'
                                        */
extern real32_T kI_Yaw_rate_PID;       /* Variable: kI_Yaw_rate_PID
                                        * Referenced by: '<S235>/Integral Gain'
                                        */
extern real32_T kP_Pitch_rate_PID;     /* Variable: kP_Pitch_rate_PID
                                        * Referenced by: '<S146>/Proportional Gain'
                                        */
extern real32_T kP_Roll_rate_PID;      /* Variable: kP_Roll_rate_PID
                                        * Referenced by: '<S194>/Proportional Gain'
                                        */
extern real32_T kP_Yaw_rate_PID;       /* Variable: kP_Yaw_rate_PID
                                        * Referenced by: '<S243>/Proportional Gain'
                                        */

/* Model entry point functions */
extern void Second_att_control_codeblock_initialize(void);
extern void Second_att_control_codeblock_step(void);
extern void Second_att_control_codeblock_terminate(void);

/* Exported data declaration */

/* Const memory section */
/* Declaration for custom storage class: Const */
extern const real32_T Hz_LPF_Pitch_rate;
                                /* Referenced by: '<S144>/Filter Coefficient' */
extern const real32_T Hz_LPF_Roll_rate;
                                /* Referenced by: '<S192>/Filter Coefficient' */
extern const real32_T Max_angle_coef;  /* Referenced by: '<S4>/1//rad_max' */
extern const real32_T Yaw_rate_max_rad;/* Referenced by: '<S9>/Gain' */

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S7>/Scope' : Unused code path elimination
 */

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
 * '<Root>' : 'Second_att_control_codeblock'
 * '<S1>'   : 'Second_att_control_codeblock/Attitude Control1'
 * '<S2>'   : 'Second_att_control_codeblock/Attitude Control1/ARMINGControl'
 * '<S3>'   : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl'
 * '<S4>'   : 'Second_att_control_codeblock/Attitude Control1/InputConditioning'
 * '<S5>'   : 'Second_att_control_codeblock/Attitude Control1/pwm_out1'
 * '<S6>'   : 'Second_att_control_codeblock/Attitude Control1/ARMINGControl/Compare To Constant3'
 * '<S7>'   : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate'
 * '<S8>'   : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller'
 * '<S9>'   : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control'
 * '<S10>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller'
 * '<S11>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1'
 * '<S12>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Anti-windup'
 * '<S13>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/D Gain'
 * '<S14>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Filter'
 * '<S15>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Filter ICs'
 * '<S16>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/I Gain'
 * '<S17>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Ideal P Gain'
 * '<S18>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S19>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Integrator'
 * '<S20>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Integrator ICs'
 * '<S21>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/N Copy'
 * '<S22>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/N Gain'
 * '<S23>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/P Copy'
 * '<S24>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Parallel P Gain'
 * '<S25>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Reset Signal'
 * '<S26>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Saturation'
 * '<S27>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Saturation Fdbk'
 * '<S28>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Sum'
 * '<S29>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Sum Fdbk'
 * '<S30>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Tracking Mode'
 * '<S31>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Tracking Mode Sum'
 * '<S32>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Tsamp - Integral'
 * '<S33>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Tsamp - Ngain'
 * '<S34>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/postSat Signal'
 * '<S35>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/preSat Signal'
 * '<S36>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S37>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/D Gain/Disabled'
 * '<S38>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Filter/Disabled'
 * '<S39>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Filter ICs/Disabled'
 * '<S40>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S41>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S42>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S43>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Integrator/Discrete'
 * '<S44>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S45>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/N Copy/Disabled wSignal Specification'
 * '<S46>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/N Gain/Disabled'
 * '<S47>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/P Copy/Disabled'
 * '<S48>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S49>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Reset Signal/Disabled'
 * '<S50>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Saturation/Passthrough'
 * '<S51>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S52>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Sum/Sum_PI'
 * '<S53>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S54>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S55>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S56>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Tsamp - Integral/Passthrough'
 * '<S57>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S58>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S59>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S60>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Anti-windup'
 * '<S61>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/D Gain'
 * '<S62>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Filter'
 * '<S63>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Filter ICs'
 * '<S64>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/I Gain'
 * '<S65>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Ideal P Gain'
 * '<S66>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Ideal P Gain Fdbk'
 * '<S67>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Integrator'
 * '<S68>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Integrator ICs'
 * '<S69>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/N Copy'
 * '<S70>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/N Gain'
 * '<S71>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/P Copy'
 * '<S72>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Parallel P Gain'
 * '<S73>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Reset Signal'
 * '<S74>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Saturation'
 * '<S75>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Saturation Fdbk'
 * '<S76>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Sum'
 * '<S77>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Sum Fdbk'
 * '<S78>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Tracking Mode'
 * '<S79>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Tracking Mode Sum'
 * '<S80>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Tsamp - Integral'
 * '<S81>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Tsamp - Ngain'
 * '<S82>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/postSat Signal'
 * '<S83>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/preSat Signal'
 * '<S84>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Anti-windup/Passthrough'
 * '<S85>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/D Gain/Disabled'
 * '<S86>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Filter/Disabled'
 * '<S87>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Filter ICs/Disabled'
 * '<S88>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/I Gain/Internal Parameters'
 * '<S89>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Ideal P Gain/Passthrough'
 * '<S90>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S91>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Integrator/Discrete'
 * '<S92>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Integrator ICs/Internal IC'
 * '<S93>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S94>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/N Gain/Disabled'
 * '<S95>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/P Copy/Disabled'
 * '<S96>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S97>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Reset Signal/Disabled'
 * '<S98>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Saturation/Passthrough'
 * '<S99>'  : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Saturation Fdbk/Disabled'
 * '<S100>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Sum/Sum_PI'
 * '<S101>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Sum Fdbk/Disabled'
 * '<S102>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Tracking Mode/Disabled'
 * '<S103>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S104>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Tsamp - Integral/Passthrough'
 * '<S105>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S106>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/postSat Signal/Forward_Path'
 * '<S107>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_Angle_to_rate/Discrete PID Controller1/preSat Signal/Forward_Path'
 * '<S108>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID'
 * '<S109>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID'
 * '<S110>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Anti-windup'
 * '<S111>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/D Gain'
 * '<S112>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Filter'
 * '<S113>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Filter ICs'
 * '<S114>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/I Gain'
 * '<S115>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Ideal P Gain'
 * '<S116>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Ideal P Gain Fdbk'
 * '<S117>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Integrator'
 * '<S118>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Integrator ICs'
 * '<S119>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/N Copy'
 * '<S120>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/N Gain'
 * '<S121>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/P Copy'
 * '<S122>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Parallel P Gain'
 * '<S123>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Reset Signal'
 * '<S124>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Saturation'
 * '<S125>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Saturation Fdbk'
 * '<S126>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Sum'
 * '<S127>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Sum Fdbk'
 * '<S128>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Tracking Mode'
 * '<S129>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Tracking Mode Sum'
 * '<S130>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Tsamp - Integral'
 * '<S131>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Tsamp - Ngain'
 * '<S132>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/postSat Signal'
 * '<S133>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/preSat Signal'
 * '<S134>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Anti-windup/Passthrough'
 * '<S135>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/D Gain/Internal Parameters'
 * '<S136>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Filter/Disc. Forward Euler Filter'
 * '<S137>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Filter ICs/Internal IC - Filter'
 * '<S138>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/I Gain/Internal Parameters'
 * '<S139>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Ideal P Gain/Passthrough'
 * '<S140>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Ideal P Gain Fdbk/Disabled'
 * '<S141>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Integrator/Discrete'
 * '<S142>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Integrator ICs/Internal IC'
 * '<S143>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/N Copy/Disabled'
 * '<S144>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/N Gain/Internal Parameters'
 * '<S145>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/P Copy/Disabled'
 * '<S146>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Parallel P Gain/Internal Parameters'
 * '<S147>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Reset Signal/Disabled'
 * '<S148>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Saturation/Enabled'
 * '<S149>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Saturation Fdbk/Disabled'
 * '<S150>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Sum/Sum_PID'
 * '<S151>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Sum Fdbk/Disabled'
 * '<S152>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Tracking Mode/Disabled'
 * '<S153>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Tracking Mode Sum/Passthrough'
 * '<S154>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Tsamp - Integral/Passthrough'
 * '<S155>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/Tsamp - Ngain/Passthrough'
 * '<S156>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/postSat Signal/Forward_Path'
 * '<S157>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Pitch_rate_PID/preSat Signal/Forward_Path'
 * '<S158>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Anti-windup'
 * '<S159>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/D Gain'
 * '<S160>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Filter'
 * '<S161>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Filter ICs'
 * '<S162>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/I Gain'
 * '<S163>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Ideal P Gain'
 * '<S164>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Ideal P Gain Fdbk'
 * '<S165>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Integrator'
 * '<S166>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Integrator ICs'
 * '<S167>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/N Copy'
 * '<S168>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/N Gain'
 * '<S169>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/P Copy'
 * '<S170>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Parallel P Gain'
 * '<S171>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Reset Signal'
 * '<S172>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Saturation'
 * '<S173>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Saturation Fdbk'
 * '<S174>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Sum'
 * '<S175>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Sum Fdbk'
 * '<S176>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Tracking Mode'
 * '<S177>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Tracking Mode Sum'
 * '<S178>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Tsamp - Integral'
 * '<S179>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Tsamp - Ngain'
 * '<S180>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/postSat Signal'
 * '<S181>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/preSat Signal'
 * '<S182>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Anti-windup/Passthrough'
 * '<S183>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/D Gain/Internal Parameters'
 * '<S184>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Filter/Disc. Forward Euler Filter'
 * '<S185>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Filter ICs/Internal IC - Filter'
 * '<S186>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/I Gain/Internal Parameters'
 * '<S187>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Ideal P Gain/Passthrough'
 * '<S188>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Ideal P Gain Fdbk/Disabled'
 * '<S189>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Integrator/Discrete'
 * '<S190>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Integrator ICs/Internal IC'
 * '<S191>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/N Copy/Disabled'
 * '<S192>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/N Gain/Internal Parameters'
 * '<S193>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/P Copy/Disabled'
 * '<S194>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Parallel P Gain/Internal Parameters'
 * '<S195>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Reset Signal/Disabled'
 * '<S196>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Saturation/Enabled'
 * '<S197>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Saturation Fdbk/Disabled'
 * '<S198>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Sum/Sum_PID'
 * '<S199>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Sum Fdbk/Disabled'
 * '<S200>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Tracking Mode/Disabled'
 * '<S201>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Tracking Mode Sum/Passthrough'
 * '<S202>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Tsamp - Integral/Passthrough'
 * '<S203>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/Tsamp - Ngain/Passthrough'
 * '<S204>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/postSat Signal/Forward_Path'
 * '<S205>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Roll-pitch_rate_controller/Roll_rate_PID/preSat Signal/Forward_Path'
 * '<S206>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller'
 * '<S207>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Anti-windup'
 * '<S208>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/D Gain'
 * '<S209>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Filter'
 * '<S210>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Filter ICs'
 * '<S211>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/I Gain'
 * '<S212>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Ideal P Gain'
 * '<S213>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S214>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Integrator'
 * '<S215>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Integrator ICs'
 * '<S216>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/N Copy'
 * '<S217>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/N Gain'
 * '<S218>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/P Copy'
 * '<S219>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Parallel P Gain'
 * '<S220>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Reset Signal'
 * '<S221>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Saturation'
 * '<S222>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Saturation Fdbk'
 * '<S223>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Sum'
 * '<S224>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Sum Fdbk'
 * '<S225>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tracking Mode'
 * '<S226>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tracking Mode Sum'
 * '<S227>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tsamp - Integral'
 * '<S228>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tsamp - Ngain'
 * '<S229>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/postSat Signal'
 * '<S230>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/preSat Signal'
 * '<S231>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Anti-windup/Passthrough'
 * '<S232>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/D Gain/Disabled'
 * '<S233>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Filter/Disabled'
 * '<S234>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Filter ICs/Disabled'
 * '<S235>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S236>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S237>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S238>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Integrator/Discrete'
 * '<S239>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S240>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/N Copy/Disabled wSignal Specification'
 * '<S241>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/N Gain/Disabled'
 * '<S242>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/P Copy/Disabled'
 * '<S243>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S244>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Reset Signal/Disabled'
 * '<S245>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Saturation/Enabled'
 * '<S246>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S247>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Sum/Sum_PI'
 * '<S248>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S249>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S250>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S251>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tsamp - Integral/Passthrough'
 * '<S252>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S253>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S254>' : 'Second_att_control_codeblock/Attitude Control1/AttitudeControl/Yaw_rate_control/Discrete PID Controller/preSat Signal/Forward_Path'
 */
#endif                          /* RTW_HEADER_Second_att_control_codeblock_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
