//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: positionEstimator.cpp
//
// Code generated for Simulink model 'positionEstimator'.
//
// Model version                  : 1.32
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Tue Sep 22 17:54:59 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "positionEstimator.h"
#define NumBitsPerChar                 8U

extern real_T rt_modd_snf(real_T u0, real_T u1);
extern real_T rt_atan2d_snf(real_T u0, real_T u1);

//===========*
//  Constants *
// ===========
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

//
//  UNUSED_PARAMETER(x)
//    Used to specify that a function parameter (argument) is required but not
//    accessed by the function body.

#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)                                   // do nothing
# else

//
//  This is the semi-ANSI standard way of indicating that an
//  unused function parameter is required.

#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

extern "C" {
  real_T rtInf;
  real_T rtMinusInf;
  real_T rtNaN;
  real32_T rtInfF;
  real32_T rtMinusInfF;
  real32_T rtNaNF;
}
  extern "C"
{
  //
  // Initialize rtNaN needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetNaN(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T nan = 0.0;
    if (bitsPerReal == 32U) {
      nan = rtGetNaNF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF80000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      nan = tmpVal.fltVal;
    }

    return nan;
  }

  //
  // Initialize rtNaNF needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetNaNF(void)
  {
    IEEESingle nanF = { { 0 } };

    nanF.wordL.wordLuint = 0xFFC00000U;
    return nanF.wordL.wordLreal;
  }
}

extern "C" {
  //
  // Initialize the rtInf, rtMinusInf, and rtNaN needed by the
  // generated code. NaN is initialized as non-signaling. Assumes IEEE.
  //
  static void rt_InitInfAndNaN(size_t realSize)
  {
    (void) (realSize);
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
  }

  // Test if value is infinite
  static boolean_T rtIsInf(real_T value)
  {
    return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
  }

  // Test if single-precision value is infinite
  static boolean_T rtIsInfF(real32_T value)
  {
    return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
  }

  // Test if value is not a number
  static boolean_T rtIsNaN(real_T value)
  {
    boolean_T result = (boolean_T) 0;
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    if (bitsPerReal == 32U) {
      result = rtIsNaNF((real32_T)value);
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.fltVal = value;
      result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) ==
                           0x7FF00000 &&
                           ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                            (tmpVal.bitVal.words.wordL != 0) ));
    }

    return result;
  }

  // Test if single-precision value is not a number
  static boolean_T rtIsNaNF(real32_T value)
  {
    IEEESingle tmp;
    tmp.wordL.wordLreal = value;
    return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                       (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
  }
}
  extern "C"
{
  //
  // Initialize rtInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T inf = 0.0;
    if (bitsPerReal == 32U) {
      inf = rtGetInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0x7FF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      inf = tmpVal.fltVal;
    }

    return inf;
  }

  //
  // Initialize rtInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetInfF(void)
  {
    IEEESingle infF;
    infF.wordL.wordLuint = 0x7F800000U;
    return infF.wordL.wordLreal;
  }

  //
  // Initialize rtMinusInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetMinusInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T minf = 0.0;
    if (bitsPerReal == 32U) {
      minf = rtGetMinusInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      minf = tmpVal.fltVal;
    }

    return minf;
  }

  //
  // Initialize rtMinusInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetMinusInfF(void)
  {
    IEEESingle minfF;
    minfF.wordL.wordLuint = 0xFF800000U;
    return minfF.wordL.wordLreal;
  }
}

//
// System initialize for enable system:
//    '<S1>/Correct2'
//    '<S1>/Correct4'
//
void positionEstimatorModelClass::Correct2_Init(DW_Correct2 *localDW, P_Correct2
  *localP)
{
  // SystemInitialize for Outport: '<S6>/yBlockOrdering'
  localDW->blockOrdering = localP->yBlockOrdering_Y0;
}

//
// Output and update for enable system:
//    '<S1>/Correct2'
//    '<S1>/Correct4'
//
void positionEstimatorModelClass::Correct2(boolean_T rtu_Enable, real_T
  rtu_yMeas, real_T rtu_R, boolean_T rtu_uBlockOrdering, DW_Correct2 *localDW,
  real_T rtd_P_i[9], real_T rtd_x[3])
{
  real_T y;
  real_T dHdx[3];
  real_T imvec[3];
  real_T epsilon;
  boolean_T blockOrdering;
  int32_T i;
  real_T imvec_0[9];
  real_T tmp[9];
  int32_T i_0;
  real_T imvec_1;

  // Outputs for Enabled SubSystem: '<S1>/Correct2' incorporates:
  //   EnablePort: '<S6>/Enable'

  if (rtu_Enable) {
    // DataStoreRead: '<S6>/Data Store ReadX'
    localDW->DataStoreReadX[0] = rtd_x[0];
    localDW->DataStoreReadX[1] = rtd_x[1];
    localDW->DataStoreReadX[2] = rtd_x[2];

    // MATLAB Function: '<S6>/Correct'
    localDW->blockOrdering = rtu_uBlockOrdering;
    blockOrdering = localDW->blockOrdering;
    localDW->blockOrdering = blockOrdering;
    for (i = 0; i < 9; i++) {
      // DataStoreRead: '<S6>/Data Store ReadP'
      localDW->DataStoreReadP[i] = rtd_P_i[i];

      // MATLAB Function: '<S6>/Correct'
      localDW->P_c[i] = localDW->DataStoreReadP[i];
      epsilon = localDW->P_c[i];
      localDW->P_c[i] = epsilon;
    }

    // MATLAB Function: '<S6>/Correct'
    for (i = 0; i < 3; i++) {
      imvec[0] = localDW->DataStoreReadX[0];
      epsilon = 1.4901161193847656E-8 * std::abs(localDW->DataStoreReadX[i]);
      if ((1.4901161193847656E-8 > epsilon) || rtIsNaN(epsilon)) {
        epsilon = 1.4901161193847656E-8;
      }

      imvec[i] = localDW->DataStoreReadX[i] + epsilon;
      dHdx[i] = (imvec[0] - localDW->DataStoreReadX[0]) / epsilon;
    }

    epsilon = 0.0;
    for (i = 0; i < 3; i++) {
      y = localDW->P_c[3 * i] * dHdx[0];
      y += localDW->P_c[3 * i + 1] * dHdx[1];
      y += localDW->P_c[3 * i + 2] * dHdx[2];
      epsilon += y * dHdx[i];
    }

    epsilon += rtu_R;
    y = rtu_yMeas - localDW->DataStoreReadX[0];
    for (i = 0; i < 3; i++) {
      imvec_1 = localDW->P_c[i] * dHdx[0];
      imvec_1 += localDW->P_c[i + 3] * dHdx[1];
      imvec_1 += localDW->P_c[i + 6] * dHdx[2];
      imvec_1 /= epsilon;
      localDW->xNew[i] = imvec_1 * y + localDW->DataStoreReadX[i];
      imvec[i] = imvec_1;
    }

    for (i = 0; i < 3; i++) {
      epsilon = dHdx[i];
      imvec_0[3 * i] = imvec[0] * epsilon;
      imvec_0[3 * i + 1] = imvec[1] * epsilon;
      imvec_0[3 * i + 2] = imvec[2] * epsilon;
    }

    for (i = 0; i < 3; i++) {
      for (i_0 = 0; i_0 < 3; i_0++) {
        imvec_1 = localDW->P_c[3 * i] * imvec_0[i_0];
        imvec_1 += localDW->P_c[3 * i + 1] * imvec_0[i_0 + 3];
        imvec_1 += localDW->P_c[3 * i + 2] * imvec_0[i_0 + 6];
        tmp[i_0 + 3 * i] = localDW->P_c[3 * i + i_0] - imvec_1;
      }
    }

    for (i = 0; i < 9; i++) {
      localDW->P_c[i] = tmp[i];

      // DataStoreWrite: '<S6>/Data Store WriteP'
      rtd_P_i[i] = localDW->P_c[i];
    }

    // DataStoreWrite: '<S6>/Data Store WriteX'
    rtd_x[0] = localDW->xNew[0];
    rtd_x[1] = localDW->xNew[1];
    rtd_x[2] = localDW->xNew[2];
  }

  // End of Outputs for SubSystem: '<S1>/Correct2'
}

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  boolean_T yEq;
  real_T q;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else if (rtIsInf(u1)) {
    if ((u1 < 0.0) != (u0 < 0.0)) {
      y = u1;
    }
  } else {
    y = std::fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > std::floor(u1))) {
      q = std::abs(u0 / u1);
      yEq = !(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0;
    } else {
      if ((u0 < 0.0) != (u1 < 0.0)) {
        y += u1;
      }
    }
  }

  return y;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T tmp;
  int32_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u1 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u0 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2(static_cast<real_T>(tmp_0), static_cast<real_T>(tmp));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

// Function for MATLAB Function: '<S17>/Correct'
void positionEstimatorModelClass::EKFCorrector_correctStateAndCov(real_T x[6],
  real_T P_0[36], const real_T y[4], const real_T Pxy[24], const real_T Pyy[16],
  const real_T dHdx[24])
{
  real_T X_0[24];
  real_T A[16];
  int8_T ipiv[4];
  int32_T b_j;
  int32_T c;
  int32_T ix;
  real_T smax;
  int32_T iy;
  real_T b_y;
  int32_T jA;
  int32_T c_ix;
  int32_T d;
  int32_T ijA;
  real_T X_1[36];
  real_T P_1[36];
  int8_T ipiv_0;
  for (b_j = 0; b_j < 16; b_j++) {
    A[b_j] = Pyy[b_j];
  }

  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  ipiv[3] = 4;
  for (b_j = 0; b_j < 3; b_j++) {
    c = b_j * 5;
    jA = 0;
    ix = c;
    smax = std::abs(A[c]);
    for (iy = 2; iy <= 4 - b_j; iy++) {
      ix++;
      b_y = std::abs(A[ix]);
      if (b_y > smax) {
        jA = iy - 1;
        smax = b_y;
      }
    }

    if (A[c + jA] != 0.0) {
      if (jA != 0) {
        ipiv[b_j] = static_cast<int8_T>((b_j + jA) + 1);
        ix = b_j;
        iy = b_j + jA;
        smax = A[ix];
        A[ix] = A[iy];
        A[iy] = smax;
        ix += 4;
        iy += 4;
        smax = A[ix];
        A[ix] = A[iy];
        A[iy] = smax;
        ix += 4;
        iy += 4;
        smax = A[ix];
        A[ix] = A[iy];
        A[iy] = smax;
        ix += 4;
        iy += 4;
        smax = A[ix];
        A[ix] = A[iy];
        A[iy] = smax;
      }

      jA = (c - b_j) + 4;
      for (ix = c + 1; ix < jA; ix++) {
        A[ix] /= A[c];
      }
    }

    jA = c;
    ix = c + 4;
    for (iy = 0; iy <= 2 - b_j; iy++) {
      if (A[ix] != 0.0) {
        smax = -A[ix];
        c_ix = c + 1;
        d = (jA - b_j) + 8;
        for (ijA = jA + 5; ijA < d; ijA++) {
          A[ijA] += A[c_ix] * smax;
          c_ix++;
        }
      }

      ix += 4;
      jA += 4;
    }
  }

  for (b_j = 0; b_j < 24; b_j++) {
    X_0[b_j] = Pxy[b_j];
  }

  for (b_j = 0; b_j < 4; b_j++) {
    jA = 6 * b_j;
    ix = b_j << 2;
    for (iy = 0; iy < b_j; iy++) {
      c_ix = 6 * iy;
      if (A[iy + ix] != 0.0) {
        for (c = 0; c < 6; c++) {
          X_0[c + jA] -= A[iy + ix] * X_0[c + c_ix];
        }
      }
    }

    smax = 1.0 / A[b_j + ix];
    for (c = 0; c < 6; c++) {
      X_0[c + jA] *= smax;
    }
  }

  for (b_j = 3; b_j >= 0; b_j--) {
    jA = 6 * b_j;
    ix = (b_j << 2) - 1;
    for (iy = b_j + 2; iy < 5; iy++) {
      c_ix = (iy - 1) * 6;
      if (A[iy + ix] != 0.0) {
        for (c = 0; c < 6; c++) {
          X_0[c + jA] -= A[iy + ix] * X_0[c + c_ix];
        }
      }
    }
  }

  for (b_j = 2; b_j >= 0; b_j--) {
    ipiv_0 = ipiv[b_j];
    if (b_j + 1 != ipiv_0) {
      jA = ipiv_0 - 1;
      for (c = 0; c < 6; c++) {
        smax = X_0[6 * b_j + c];
        X_0[c + 6 * b_j] = X_0[6 * jA + c];
        X_0[c + 6 * jA] = smax;
      }
    }
  }

  for (b_j = 0; b_j < 6; b_j++) {
    smax = X_0[b_j] * y[0];
    smax += X_0[b_j + 6] * y[1];
    smax += X_0[b_j + 12] * y[2];
    smax += X_0[b_j + 18] * y[3];
    x[b_j] += smax;
    for (c = 0; c < 6; c++) {
      X_1[b_j + 6 * c] = 0.0;
      smax = X_1[6 * c + b_j];
      smax += dHdx[c << 2] * X_0[b_j];
      X_1[b_j + 6 * c] = smax;
      smax = X_1[6 * c + b_j];
      smax += dHdx[(c << 2) + 1] * X_0[b_j + 6];
      X_1[b_j + 6 * c] = smax;
      smax = X_1[6 * c + b_j];
      smax += dHdx[(c << 2) + 2] * X_0[b_j + 12];
      X_1[b_j + 6 * c] = smax;
      smax = X_1[6 * c + b_j];
      smax += dHdx[(c << 2) + 3] * X_0[b_j + 18];
      X_1[b_j + 6 * c] = smax;
    }

    for (c = 0; c < 6; c++) {
      smax = 0.0;
      for (jA = 0; jA < 6; jA++) {
        smax += X_1[6 * jA + b_j] * P_0[6 * c + jA];
      }

      P_1[b_j + 6 * c] = P_0[6 * c + b_j] - smax;
    }
  }

  for (b_j = 0; b_j < 36; b_j++) {
    P_0[b_j] = P_1[b_j];
  }
}

// Model step function
void positionEstimatorModelClass::step()
{
  real_T Pxy[12];
  real_T Pyy[4];
  real_T dHdx[12];
  real_T gain[12];
  real_T z[2];
  real_T imvec[6];
  real_T epsilon;
  int32_T r1;
  real_T a22;
  int32_T k;
  boolean_T blockOrdering;
  real_T dHdx_0[24];
  real_T dHdx_1[3];
  real_T imvec_0[3];
  int32_T i;
  real_T dHdx_2[24];
  real_T tmp[24];
  real_T dHdx_3[16];
  real_T gain_0[36];
  real_T tmp_0[36];
  real_T imvec_1[9];
  real_T a[9];
  real_T b_a[9];
  real_T imvec_2;
  static const int8_T a_0[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 };

  static const real_T a_1[9] = { 1.0, 0.0, 0.0, 0.01, 1.0, 0.0, 5.0E-5, 0.01,
    1.0 };

  static const real_T b[9] = { 1.0, 0.01, 5.0E-5, 0.0, 1.0, 0.01, 0.0, 0.0, 1.0
  };

  static const real_T b_a_0[3] = { 2.5E-5, 0.005, 1.0 };

  static const real_T a_2[36] = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.01, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.01, 0.0, 1.0, 0.0, 0.0,
    5.0E-5, 0.0, 0.01, 0.0, 1.0, 0.0, 0.0, 5.0E-5, 0.0, 0.01, 0.0, 1.0 };

  static const real_T b_0[36] = { 1.0, 0.0, 0.01, 0.0, 5.0E-5, 0.0, 0.0, 1.0,
    0.0, 0.01, 0.0, 5.0E-5, 0.0, 0.0, 1.0, 0.0, 0.01, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.01, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  // Abs: '<S60>/Abs' incorporates:
  //   Inport: '<Root>/HOME_lla'

  rtDW.Abs = std::abs(rtU.HOME_lla[0]);

  // RelationalOperator: '<S61>/Compare' incorporates:
  //   Constant: '<S61>/Constant'

  rtDW.Compare = (rtDW.Abs > rtP.CompareToConstant_const);

  // Switch: '<S60>/Switch' incorporates:
  //   Inport: '<Root>/HOME_lla'

  if (rtDW.Compare) {
    // Bias: '<S60>/Bias' incorporates:
    //   Inport: '<Root>/HOME_lla'

    rtDW.Bias_m = rtU.HOME_lla[0] + rtP.Bias_Bias_al;

    // Math: '<S60>/Math Function1' incorporates:
    //   Constant: '<S60>/Constant2'

    rtDW.MathFunction1_i = rt_modd_snf(rtDW.Bias_m, rtP.Constant2_Value_jr);

    // Bias: '<S60>/Bias1'
    rtDW.Bias1_k = rtDW.MathFunction1_i + rtP.Bias1_Bias_k2;
    rtDW.Switch = rtDW.Bias1_k;
  } else {
    rtDW.Switch = rtU.HOME_lla[0];
  }

  // End of Switch: '<S60>/Switch'

  // Abs: '<S57>/Abs1'
  rtDW.Abs1 = std::abs(rtDW.Switch);

  // RelationalOperator: '<S59>/Compare' incorporates:
  //   Constant: '<S59>/Constant'

  rtDW.Compare_c = (rtDW.Abs1 > rtP.CompareToConstant_const_d);

  // Switch: '<S57>/Switch' incorporates:
  //   Constant: '<S48>/Constant'
  //   Constant: '<S48>/Constant1'
  //   Switch: '<S48>/Switch1'

  if (rtDW.Compare_c) {
    // Bias: '<S57>/Bias'
    rtDW.Bias_d = rtDW.Abs1 + rtP.Bias_Bias_e;

    // Gain: '<S57>/Gain'
    rtDW.Gain = rtP.Gain_Gain_n * rtDW.Bias_d;

    // Bias: '<S57>/Bias1'
    rtDW.Bias1_o = rtDW.Gain + rtP.Bias1_Bias_c;

    // Signum: '<S57>/Sign1'
    a22 = rtDW.Switch;
    if (a22 < 0.0) {
      rtDW.Sign1 = -1.0;
    } else if (a22 > 0.0) {
      rtDW.Sign1 = 1.0;
    } else if (a22 == 0.0) {
      rtDW.Sign1 = 0.0;
    } else {
      rtDW.Sign1 = (rtNaN);
    }

    // End of Signum: '<S57>/Sign1'

    // Product: '<S57>/Divide1'
    rtDW.Divide1 = rtDW.Sign1 * rtDW.Bias1_o;
    rtDW.Switch_b = rtDW.Divide1;
    rtDW.Switch1 = rtP.Constant_Value_m;
  } else {
    rtDW.Switch_b = rtDW.Switch;
    rtDW.Switch1 = rtP.Constant1_Value_fz;
  }

  // End of Switch: '<S57>/Switch'

  // Sum: '<S48>/Sum' incorporates:
  //   Inport: '<Root>/HOME_lla'

  rtDW.Sum = rtDW.Switch1 + rtU.HOME_lla[1];

  // Abs: '<S58>/Abs'
  rtDW.Abs_i = std::abs(rtDW.Sum);

  // RelationalOperator: '<S62>/Compare' incorporates:
  //   Constant: '<S62>/Constant'

  rtDW.Compare_d = (rtDW.Abs_i > rtP.CompareToConstant_const_j);

  // Switch: '<S58>/Switch'
  if (rtDW.Compare_d) {
    // Bias: '<S58>/Bias'
    rtDW.Bias = rtDW.Sum + rtP.Bias_Bias_dq;

    // Math: '<S58>/Math Function1' incorporates:
    //   Constant: '<S58>/Constant2'

    rtDW.MathFunction1 = rt_modd_snf(rtDW.Bias, rtP.Constant2_Value_kz);

    // Bias: '<S58>/Bias1'
    rtDW.Bias1 = rtDW.MathFunction1 + rtP.Bias1_Bias_cz;
    rtDW.Switch_h = rtDW.Bias1;
  } else {
    rtDW.Switch_h = rtDW.Sum;
  }

  // End of Switch: '<S58>/Switch'

  // Sum: '<S46>/Sum1' incorporates:
  //   Inport: '<Root>/lat'
  //   Inport: '<Root>/lon'

  rtDW.Sum1[0] = rtU.lat - rtDW.Switch_b;
  rtDW.Sum1[1] = rtU.lon - rtDW.Switch_h;

  // Abs: '<S54>/Abs'
  rtDW.Abs_b = std::abs(rtDW.Sum1[0]);

  // RelationalOperator: '<S55>/Compare' incorporates:
  //   Constant: '<S55>/Constant'

  rtDW.Compare_ds = (rtDW.Abs_b > rtP.CompareToConstant_const_n);

  // Switch: '<S54>/Switch'
  if (rtDW.Compare_ds) {
    // Bias: '<S54>/Bias'
    rtDW.Bias_e = rtDW.Sum1[0] + rtP.Bias_Bias_b;

    // Math: '<S54>/Math Function1' incorporates:
    //   Constant: '<S54>/Constant2'

    rtDW.MathFunction1_o = rt_modd_snf(rtDW.Bias_e, rtP.Constant2_Value_p);

    // Bias: '<S54>/Bias1'
    rtDW.Bias1_oh = rtDW.MathFunction1_o + rtP.Bias1_Bias_p;
    rtDW.Switch_f = rtDW.Bias1_oh;
  } else {
    rtDW.Switch_f = rtDW.Sum1[0];
  }

  // End of Switch: '<S54>/Switch'

  // Abs: '<S51>/Abs1'
  rtDW.Abs1_j = std::abs(rtDW.Switch_f);

  // RelationalOperator: '<S53>/Compare' incorporates:
  //   Constant: '<S53>/Constant'

  rtDW.Compare_m = (rtDW.Abs1_j > rtP.CompareToConstant_const_e);

  // Switch: '<S51>/Switch' incorporates:
  //   Constant: '<S47>/Constant'
  //   Constant: '<S47>/Constant1'
  //   Switch: '<S47>/Switch1'

  if (rtDW.Compare_m) {
    // Bias: '<S51>/Bias'
    rtDW.Bias_mj = rtDW.Abs1_j + rtP.Bias_Bias_d;

    // Gain: '<S51>/Gain'
    rtDW.Gain_c = rtP.Gain_Gain_k * rtDW.Bias_mj;

    // Bias: '<S51>/Bias1'
    rtDW.Bias1_n = rtDW.Gain_c + rtP.Bias1_Bias_h;

    // Signum: '<S51>/Sign1'
    a22 = rtDW.Switch_f;
    if (a22 < 0.0) {
      rtDW.Sign1_g = -1.0;
    } else if (a22 > 0.0) {
      rtDW.Sign1_g = 1.0;
    } else if (a22 == 0.0) {
      rtDW.Sign1_g = 0.0;
    } else {
      rtDW.Sign1_g = (rtNaN);
    }

    // End of Signum: '<S51>/Sign1'

    // Product: '<S51>/Divide1'
    rtDW.Divide1_h = rtDW.Sign1_g * rtDW.Bias1_n;
    rtDW.Switch_j = rtDW.Divide1_h;
    rtDW.Switch1_b = rtP.Constant_Value_lu;
  } else {
    rtDW.Switch_j = rtDW.Switch_f;
    rtDW.Switch1_b = rtP.Constant1_Value_k;
  }

  // End of Switch: '<S51>/Switch'

  // Sum: '<S47>/Sum'
  rtDW.Sum_j = rtDW.Switch1_b + rtDW.Sum1[1];

  // Abs: '<S52>/Abs'
  rtDW.Abs_b0 = std::abs(rtDW.Sum_j);

  // RelationalOperator: '<S56>/Compare' incorporates:
  //   Constant: '<S56>/Constant'

  rtDW.Compare_k = (rtDW.Abs_b0 > rtP.CompareToConstant_const_ei);

  // Switch: '<S52>/Switch'
  if (rtDW.Compare_k) {
    // Bias: '<S52>/Bias'
    rtDW.Bias_j = rtDW.Sum_j + rtP.Bias_Bias_a;

    // Math: '<S52>/Math Function1' incorporates:
    //   Constant: '<S52>/Constant2'

    rtDW.MathFunction1_h = rt_modd_snf(rtDW.Bias_j, rtP.Constant2_Value_g);

    // Bias: '<S52>/Bias1'
    rtDW.Bias1_p = rtDW.MathFunction1_h + rtP.Bias1_Bias_l;
    rtDW.Switch_m = rtDW.Bias1_p;
  } else {
    rtDW.Switch_m = rtDW.Sum_j;
  }

  // End of Switch: '<S52>/Switch'

  // UnitConversion: '<S50>/Unit Conversion'
  // Unit Conversion - from: deg to: rad
  // Expression: output = (0.0174533*input) + (0)
  rtDW.UnitConversion[0] = 0.017453292519943295 * rtDW.Switch_j;
  rtDW.UnitConversion[1] = 0.017453292519943295 * rtDW.Switch_m;

  // Sum: '<S67>/Sum' incorporates:
  //   Constant: '<S67>/Constant'
  //   Constant: '<S67>/f'

  rtDW.Sum_a = rtP.f_Value - rtP.Constant_Value_c;

  // Product: '<S68>/Product1'
  rtDW.Product1 = rtDW.Sum_a * rtDW.Sum_a;

  // Sum: '<S68>/Sum1' incorporates:
  //   Constant: '<S68>/Constant'

  rtDW.Sum1_e = rtP.Constant_Value_a - rtDW.Product1;

  // Sqrt: '<S68>/sqrt'
  rtDW.sqrt_c = std::sqrt(rtDW.Sum1_e);

  // UnitConversion: '<S65>/Unit Conversion'
  // Unit Conversion - from: deg to: rad
  // Expression: output = (0.0174533*input) + (0)
  rtDW.UnitConversion_m = 0.017453292519943295 * rtDW.Switch_b;

  // Trigonometry: '<S66>/Trigonometric Function1'
  rtDW.TrigonometricFunction1 = std::sin(rtDW.UnitConversion_m);

  // Product: '<S66>/Product1'
  rtDW.Product1_n = rtDW.sqrt_c * rtDW.sqrt_c * rtDW.TrigonometricFunction1 *
    rtDW.TrigonometricFunction1;

  // Sum: '<S66>/Sum1' incorporates:
  //   Constant: '<S66>/Constant'

  rtDW.Sum1_c = rtP.Constant_Value_f - rtDW.Product1_n;

  // Sqrt: '<S64>/sqrt'
  rtDW.sqrt_d = std::sqrt(rtDW.Sum1_c);

  // Product: '<S64>/Product1' incorporates:
  //   Constant: '<S64>/Constant1'

  rtDW.Rn = rtP.Constant1_Value_d / rtDW.sqrt_d;

  // Product: '<S64>/Product2'
  rtDW.Product2 = rtDW.sqrt_c * rtDW.sqrt_c;

  // Sum: '<S64>/Sum1' incorporates:
  //   Constant: '<S64>/Constant'

  rtDW.Sum1_g = rtP.Constant_Value_ch - rtDW.Product2;

  // Product: '<S64>/Product3'
  rtDW.Rm = rtDW.Rn * rtDW.Sum1_g / rtDW.Sum1_c;

  // Trigonometry: '<S64>/Trigonometric Function1' incorporates:
  //   Constant: '<S64>/Constant2'

  rtDW.TrigonometricFunction1_l = rt_atan2d_snf(rtP.Constant2_Value_h, rtDW.Rm);

  // Product: '<S49>/dNorth'
  rtDW.dNorth = rtDW.UnitConversion[0] / rtDW.TrigonometricFunction1_l;

  // UnitConversion: '<S63>/Unit Conversion' incorporates:
  //   Constant: '<S4>/flat-x_from_N'

  // Unit Conversion - from: deg to: rad
  // Expression: output = (0.0174533*input) + (0)
  rtDW.UnitConversion_p = 0.017453292519943295 * rtP.flatx_from_N_Value;

  // Trigonometry: '<S49>/SinCos'
  a22 = rtDW.UnitConversion_p;
  epsilon = std::sin(a22);
  a22 = std::cos(a22);
  rtDW.SinCos_o1 = epsilon;
  rtDW.SinCos_o2 = a22;

  // Product: '<S49>/x*cos'
  rtDW.xcos = rtDW.dNorth * rtDW.SinCos_o2;

  // Trigonometry: '<S64>/Trigonometric Function'
  rtDW.TrigonometricFunction = std::cos(rtDW.UnitConversion_m);

  // Product: '<S64>/Product4'
  rtDW.Product4 = rtDW.Rn * rtDW.TrigonometricFunction;

  // Trigonometry: '<S64>/Trigonometric Function2' incorporates:
  //   Constant: '<S64>/Constant3'

  rtDW.TrigonometricFunction2 = rt_atan2d_snf(rtP.Constant3_Value, rtDW.Product4);

  // Product: '<S49>/dEast'
  rtDW.dEast = 1.0 / rtDW.TrigonometricFunction2 * rtDW.UnitConversion[1];

  // Product: '<S49>/y*sin'
  rtDW.ysin = rtDW.dEast * rtDW.SinCos_o1;

  // Outport: '<Root>/GPSrawX' incorporates:
  //   Sum: '<S49>/Sum2'

  rtY.GPSrawX = rtDW.xcos + rtDW.ysin;

  // Product: '<S49>/x*sin'
  rtDW.xsin = rtDW.dNorth * rtDW.SinCos_o1;

  // Product: '<S49>/y*cos'
  rtDW.ycos = rtDW.dEast * rtDW.SinCos_o2;

  // Outport: '<Root>/GPSrawY' incorporates:
  //   Sum: '<S49>/Sum3'

  rtY.GPSrawY = rtDW.ycos - rtDW.xsin;

  // DataTypeConversion: '<S2>/DataTypeConversion_Enable1' incorporates:
  //   Inport: '<Root>/AhrsFlag'

  rtDW.DataTypeConversion_Enable1 = (rtU.AhrsFlag != 0.0);

  // Outputs for Enabled SubSystem: '<S2>/Correct1' incorporates:
  //   EnablePort: '<S16>/Enable'

  if (rtDW.DataTypeConversion_Enable1) {
    // DataStoreRead: '<S16>/Data Store ReadX'
    for (i = 0; i < 6; i++) {
      rtDW.DataStoreReadX_p[i] = rtDW.x_p[i];
    }

    // End of DataStoreRead: '<S16>/Data Store ReadX'

    // SignalConversion generated from: '<S20>/ SFunction ' incorporates:
    //   Inport: '<Root>/ax'
    //   Inport: '<Root>/ay'
    //   MATLAB Function: '<S16>/Correct'

    rtDW.TmpSignalConversionAtSFunctio_i[0] = rtU.ax;
    rtDW.TmpSignalConversionAtSFunctio_i[1] = rtU.ay;

    // MATLAB Function: '<S16>/Correct' incorporates:
    //   Constant: '<S2>/BlockOrdering'

    rtDW.blockOrdering_f = rtP.BlockOrdering_Value;
    blockOrdering = rtDW.blockOrdering_f;
    rtDW.blockOrdering_f = blockOrdering;
    for (i = 0; i < 36; i++) {
      // DataStoreRead: '<S16>/Data Store ReadP'
      rtDW.P_k[i] = rtDW.P_n_c[i];

      // MATLAB Function: '<S16>/Correct'
      a22 = rtDW.P_k[i];
      rtDW.P_k[i] = a22;
    }

    // MATLAB Function: '<S16>/Correct' incorporates:
    //   Constant: '<S2>/R1'

    for (i = 0; i < 2; i++) {
      z[i] = 0.0;
      for (k = 0; k < 6; k++) {
        a22 = z[i];
        a22 += static_cast<real_T>(a_0[(k << 1) + i]) * rtDW.DataStoreReadX_p[k];
        z[i] = a22;
      }
    }

    for (r1 = 0; r1 < 6; r1++) {
      for (i = 0; i < 6; i++) {
        imvec[i] = rtDW.DataStoreReadX_p[i];
      }

      epsilon = 1.4901161193847656E-8 * std::abs(rtDW.DataStoreReadX_p[r1]);
      if ((1.4901161193847656E-8 > epsilon) || rtIsNaN(epsilon)) {
        epsilon = 1.4901161193847656E-8;
      }

      imvec[r1] = rtDW.DataStoreReadX_p[r1] + epsilon;
      for (i = 0; i < 2; i++) {
        imvec_2 = 0.0;
        for (k = 0; k < 6; k++) {
          imvec_2 += static_cast<real_T>(a_0[(k << 1) + i]) * imvec[k];
        }

        dHdx[i + (r1 << 1)] = (imvec_2 - z[i]) / epsilon;
      }
    }

    for (i = 0; i < 6; i++) {
      for (k = 0; k < 2; k++) {
        Pxy[i + 6 * k] = 0.0;
        for (r1 = 0; r1 < 6; r1++) {
          a22 = Pxy[6 * k + i];
          a22 += rtDW.P_k[6 * r1 + i] * dHdx[(r1 << 1) + k];
          Pxy[i + 6 * k] = a22;
        }
      }
    }

    for (i = 0; i < 2; i++) {
      for (k = 0; k < 6; k++) {
        gain[i + (k << 1)] = 0.0;
        for (r1 = 0; r1 < 6; r1++) {
          a22 = gain[(k << 1) + i];
          a22 += dHdx[(r1 << 1) + i] * rtDW.P_k[6 * k + r1];
          gain[i + (k << 1)] = a22;
        }
      }

      for (k = 0; k < 2; k++) {
        imvec_2 = 0.0;
        for (r1 = 0; r1 < 6; r1++) {
          imvec_2 += gain[(r1 << 1) + i] * dHdx[(r1 << 1) + k];
        }

        Pyy[i + (k << 1)] = rtP.R1_Value[(k << 1) + i] + imvec_2;
      }
    }

    if (std::abs(Pyy[1]) > std::abs(Pyy[0])) {
      r1 = 1;
      i = 0;
    } else {
      r1 = 0;
      i = 1;
    }

    epsilon = Pyy[i] / Pyy[r1];
    a22 = Pyy[i + 2] - Pyy[r1 + 2] * epsilon;
    for (k = 0; k < 6; k++) {
      gain[k + 6 * r1] = Pxy[k] / Pyy[r1];
      gain[k + 6 * i] = (Pxy[k + 6] - gain[6 * r1 + k] * Pyy[r1 + 2]) / a22;
      gain[k + 6 * r1] -= gain[6 * i + k] * epsilon;
    }

    for (i = 0; i < 2; i++) {
      imvec_2 = 0.0;
      for (k = 0; k < 6; k++) {
        imvec_2 += static_cast<real_T>(a_0[(k << 1) + i]) *
          rtDW.DataStoreReadX_p[k];
      }

      z[i] = rtDW.TmpSignalConversionAtSFunctio_i[i] - imvec_2;
    }

    for (i = 0; i < 6; i++) {
      imvec_2 = gain[i] * z[0];
      imvec_2 += gain[i + 6] * z[1];
      rtDW.xNew_n[i] = rtDW.DataStoreReadX_p[i] + imvec_2;
      for (k = 0; k < 6; k++) {
        gain_0[i + 6 * k] = 0.0;
        a22 = gain_0[6 * k + i];
        a22 += dHdx[k << 1] * gain[i];
        gain_0[i + 6 * k] = a22;
        a22 = gain_0[6 * k + i];
        a22 += dHdx[(k << 1) + 1] * gain[i + 6];
        gain_0[i + 6 * k] = a22;
      }

      for (k = 0; k < 6; k++) {
        imvec_2 = 0.0;
        for (r1 = 0; r1 < 6; r1++) {
          imvec_2 += gain_0[6 * r1 + i] * rtDW.P_k[6 * k + r1];
        }

        tmp_0[i + 6 * k] = rtDW.P_k[6 * k + i] - imvec_2;
      }
    }

    for (i = 0; i < 36; i++) {
      rtDW.P_k[i] = tmp_0[i];

      // DataStoreWrite: '<S16>/Data Store WriteP'
      rtDW.P_n_c[i] = rtDW.P_k[i];
    }

    // DataStoreWrite: '<S16>/Data Store WriteX'
    for (i = 0; i < 6; i++) {
      rtDW.x_p[i] = rtDW.xNew_n[i];
    }

    // End of DataStoreWrite: '<S16>/Data Store WriteX'
  }

  // End of Outputs for SubSystem: '<S2>/Correct1'

  // Logic: '<Root>/Logical Operator' incorporates:
  //   Inport: '<Root>/GPS_switch'
  //   Inport: '<Root>/GpsFlag'

  rtDW.LogicalOperator = ((rtU.GPS_switch != 0.0) && (rtU.GpsFlag != 0.0));

  // Outputs for Enabled SubSystem: '<S2>/Correct2' incorporates:
  //   EnablePort: '<S17>/Enable'

  if (rtDW.LogicalOperator) {
    // DataStoreRead: '<S17>/Data Store ReadX'
    for (i = 0; i < 6; i++) {
      rtDW.DataStoreReadX_j[i] = rtDW.x_p[i];
    }

    // End of DataStoreRead: '<S17>/Data Store ReadX'

    // SignalConversion generated from: '<S21>/ SFunction ' incorporates:
    //   Inport: '<Root>/vx'
    //   Inport: '<Root>/vy'
    //   MATLAB Function: '<S17>/Correct'
    //   Outport: '<Root>/GPSrawX'
    //   Outport: '<Root>/GPSrawY'

    rtDW.TmpSignalConversionAtSFunctionI[0] = rtY.GPSrawX;
    rtDW.TmpSignalConversionAtSFunctionI[1] = rtY.GPSrawY;
    rtDW.TmpSignalConversionAtSFunctionI[2] = rtU.vx;
    rtDW.TmpSignalConversionAtSFunctionI[3] = rtU.vy;

    // MATLAB Function: '<S17>/Correct'
    rtDW.blockOrdering = rtDW.blockOrdering_f;
    blockOrdering = rtDW.blockOrdering;
    rtDW.blockOrdering = blockOrdering;
    for (i = 0; i < 36; i++) {
      // DataStoreRead: '<S17>/Data Store ReadP'
      rtDW.P_f[i] = rtDW.P_n_c[i];

      // MATLAB Function: '<S17>/Correct'
      a22 = rtDW.P_f[i];
      rtDW.P_f[i] = a22;
    }

    // MATLAB Function: '<S17>/Correct' incorporates:
    //   Constant: '<S2>/R2'

    for (r1 = 0; r1 < 6; r1++) {
      for (i = 0; i < 6; i++) {
        imvec[i] = rtDW.DataStoreReadX_j[i];
      }

      epsilon = 1.4901161193847656E-8 * std::abs(rtDW.DataStoreReadX_j[r1]);
      if ((1.4901161193847656E-8 > epsilon) || rtIsNaN(epsilon)) {
        epsilon = 1.4901161193847656E-8;
      }

      imvec[r1] = rtDW.DataStoreReadX_j[r1] + epsilon;
      dHdx_0[r1 << 2] = (imvec[0] - rtDW.DataStoreReadX_j[0]) / epsilon;
      dHdx_0[(r1 << 2) + 1] = (imvec[1] - rtDW.DataStoreReadX_j[1]) / epsilon;
      dHdx_0[(r1 << 2) + 2] = (imvec[2] - rtDW.DataStoreReadX_j[2]) / epsilon;
      dHdx_0[(r1 << 2) + 3] = (imvec[3] - rtDW.DataStoreReadX_j[3]) / epsilon;
    }

    for (i = 0; i < 6; i++) {
      imvec[i] = rtDW.DataStoreReadX_j[i];
    }

    for (i = 0; i < 4; i++) {
      for (k = 0; k < 6; k++) {
        dHdx_2[i + (k << 2)] = 0.0;
        for (r1 = 0; r1 < 6; r1++) {
          a22 = dHdx_2[(k << 2) + i];
          a22 += dHdx_0[(r1 << 2) + i] * rtDW.P_f[6 * k + r1];
          dHdx_2[i + (k << 2)] = a22;
        }
      }

      Pyy[i] = rtDW.TmpSignalConversionAtSFunctionI[i] - rtDW.DataStoreReadX_j[i];
    }

    for (i = 0; i < 6; i++) {
      for (k = 0; k < 4; k++) {
        tmp[i + 6 * k] = 0.0;
        for (r1 = 0; r1 < 6; r1++) {
          imvec_2 = tmp[6 * k + i];
          imvec_2 += rtDW.P_f[6 * r1 + i] * dHdx_0[(r1 << 2) + k];
          tmp[i + 6 * k] = imvec_2;
        }
      }
    }

    for (i = 0; i < 4; i++) {
      for (k = 0; k < 4; k++) {
        imvec_2 = 0.0;
        for (r1 = 0; r1 < 6; r1++) {
          imvec_2 += dHdx_2[(r1 << 2) + i] * dHdx_0[(r1 << 2) + k];
        }

        dHdx_3[i + (k << 2)] = rtP.R2_Value[(k << 2) + i] + imvec_2;
      }
    }

    EKFCorrector_correctStateAndCov(imvec, rtDW.P_f, Pyy, tmp, dHdx_3, dHdx_0);
    for (i = 0; i < 6; i++) {
      rtDW.xNew_g[i] = imvec[i];
    }

    // DataStoreWrite: '<S17>/Data Store WriteP'
    for (i = 0; i < 36; i++) {
      rtDW.P_n_c[i] = rtDW.P_f[i];
    }

    // End of DataStoreWrite: '<S17>/Data Store WriteP'

    // DataStoreWrite: '<S17>/Data Store WriteX'
    for (i = 0; i < 6; i++) {
      rtDW.x_p[i] = rtDW.xNew_g[i];
    }

    // End of DataStoreWrite: '<S17>/Data Store WriteX'
  }

  // End of Outputs for SubSystem: '<S2>/Correct2'

  // Outputs for Atomic SubSystem: '<S2>/Output'
  // DataStoreRead: '<S18>/Data Store Read'
  for (i = 0; i < 6; i++) {
    rtDW.DataStoreRead[i] = rtDW.x_p[i];
  }

  // End of DataStoreRead: '<S18>/Data Store Read'

  // DataStoreRead: '<S18>/Data Store Read1'
  for (i = 0; i < 36; i++) {
    rtDW.DataStoreRead1[i] = rtDW.P_n_c[i];
  }

  // End of DataStoreRead: '<S18>/Data Store Read1'

  // Inport: '<S18>/uBlockOrdering'
  rtDW.uBlockOrdering = rtDW.blockOrdering;

  // End of Outputs for SubSystem: '<S2>/Output'

  // Outport: '<Root>/estiX'
  rtY.estiX = rtDW.DataStoreRead[0];

  // Outport: '<Root>/estiY'
  rtY.estiY = rtDW.DataStoreRead[1];

  // Gain: '<Root>/NED_convert1' incorporates:
  //   Inport: '<Root>/Lidar_height'

  rtDW.NED_convert1 = rtP.NED_convert1_Gain * rtU.Lidar_height;

  // Gain: '<Root>/NED_convert' incorporates:
  //   Inport: '<Root>/baroZ'

  rtDW.NED_convert = rtP.NED_convert_Gain * rtU.baroZ;

  // Sum: '<S46>/Sum' incorporates:
  //   Inport: '<Root>/HOME_lla'
  //   Inport: '<Root>/alt'

  rtDW.alt = rtU.alt + rtU.HOME_lla[2];

  // UnaryMinus: '<S46>/Ze2height'
  rtDW.Pz = -rtDW.alt;

  // DataTypeConversion: '<S1>/DataTypeConversion_Enable1' incorporates:
  //   Inport: '<Root>/AhrsFlag'

  rtDW.DataTypeConversion_Enable1_a = (rtU.AhrsFlag != 0.0);

  // Outputs for Enabled SubSystem: '<S1>/Correct1' incorporates:
  //   EnablePort: '<S5>/Enable'

  if (rtDW.DataTypeConversion_Enable1_a) {
    // DataStoreRead: '<S5>/Data Store ReadX'
    rtDW.DataStoreReadX_o[0] = rtDW.x[0];
    rtDW.DataStoreReadX_o[1] = rtDW.x[1];
    rtDW.DataStoreReadX_o[2] = rtDW.x[2];

    // MATLAB Function: '<S5>/Correct' incorporates:
    //   Constant: '<S1>/BlockOrdering'

    rtDW.blockOrdering_k = rtP.BlockOrdering_Value_b;
    blockOrdering = rtDW.blockOrdering_k;
    rtDW.blockOrdering_k = blockOrdering;
    for (i = 0; i < 9; i++) {
      // DataStoreRead: '<S5>/Data Store ReadP'
      rtDW.P_g[i] = rtDW.P_i_m[i];

      // MATLAB Function: '<S5>/Correct'
      a22 = rtDW.P_g[i];
      rtDW.P_g[i] = a22;
    }

    // MATLAB Function: '<S5>/Correct' incorporates:
    //   Constant: '<S1>/R1'
    //   Inport: '<Root>/az'

    for (r1 = 0; r1 < 3; r1++) {
      imvec_0[2] = rtDW.DataStoreReadX_o[2];
      epsilon = 1.4901161193847656E-8 * std::abs(rtDW.DataStoreReadX_o[r1]);
      if ((1.4901161193847656E-8 > epsilon) || rtIsNaN(epsilon)) {
        epsilon = 1.4901161193847656E-8;
      }

      imvec_0[r1] = rtDW.DataStoreReadX_o[r1] + epsilon;
      dHdx_1[r1] = (imvec_0[2] - rtDW.DataStoreReadX_o[2]) / epsilon;
    }

    a22 = 0.0;
    for (i = 0; i < 3; i++) {
      epsilon = rtDW.P_g[3 * i] * dHdx_1[0];
      epsilon += rtDW.P_g[3 * i + 1] * dHdx_1[1];
      epsilon += rtDW.P_g[3 * i + 2] * dHdx_1[2];
      a22 += epsilon * dHdx_1[i];
    }

    epsilon = a22 + rtP.R1_Value_j;
    a22 = rtU.az - rtDW.DataStoreReadX_o[2];
    for (i = 0; i < 3; i++) {
      imvec_2 = rtDW.P_g[i] * dHdx_1[0];
      imvec_2 += rtDW.P_g[i + 3] * dHdx_1[1];
      imvec_2 += rtDW.P_g[i + 6] * dHdx_1[2];
      imvec_2 /= epsilon;
      rtDW.xNew_o[i] = imvec_2 * a22 + rtDW.DataStoreReadX_o[i];
      imvec_0[i] = imvec_2;
    }

    for (i = 0; i < 3; i++) {
      a22 = dHdx_1[i];
      imvec_1[3 * i] = imvec_0[0] * a22;
      imvec_1[3 * i + 1] = imvec_0[1] * a22;
      imvec_1[3 * i + 2] = imvec_0[2] * a22;
    }

    for (i = 0; i < 3; i++) {
      for (k = 0; k < 3; k++) {
        imvec_2 = rtDW.P_g[3 * i] * imvec_1[k];
        imvec_2 += rtDW.P_g[3 * i + 1] * imvec_1[k + 3];
        imvec_2 += rtDW.P_g[3 * i + 2] * imvec_1[k + 6];
        a[k + 3 * i] = rtDW.P_g[3 * i + k] - imvec_2;
      }
    }

    for (i = 0; i < 9; i++) {
      rtDW.P_g[i] = a[i];

      // DataStoreWrite: '<S5>/Data Store WriteP'
      rtDW.P_i_m[i] = rtDW.P_g[i];
    }

    // DataStoreWrite: '<S5>/Data Store WriteX'
    rtDW.x[0] = rtDW.xNew_o[0];
    rtDW.x[1] = rtDW.xNew_o[1];
    rtDW.x[2] = rtDW.xNew_o[2];
  }

  // End of Outputs for SubSystem: '<S1>/Correct1'

  // Outputs for Enabled SubSystem: '<S1>/Correct2'
  // Constant: '<S1>/R2'
  Correct2(rtDW.LogicalOperator, rtDW.Pz, rtP.R2_Value_g, rtDW.blockOrdering_k,
           &rtDW.Correct2_a, rtDW.P_i_m, rtDW.x);

  // End of Outputs for SubSystem: '<S1>/Correct2'

  // DataTypeConversion: '<S1>/DataTypeConversion_Enable3' incorporates:
  //   Inport: '<Root>/BaroFlag'

  rtDW.DataTypeConversion_Enable3 = (rtU.BaroFlag != 0.0);

  // Outputs for Enabled SubSystem: '<S1>/Correct3' incorporates:
  //   EnablePort: '<S7>/Enable'

  if (rtDW.DataTypeConversion_Enable3) {
    // DataStoreRead: '<S7>/Data Store ReadX'
    rtDW.DataStoreReadX_i[0] = rtDW.x[0];
    rtDW.DataStoreReadX_i[1] = rtDW.x[1];
    rtDW.DataStoreReadX_i[2] = rtDW.x[2];

    // DataStoreRead: '<S7>/Data Store ReadP'
    for (i = 0; i < 9; i++) {
      rtDW.P_a[i] = rtDW.P_i_m[i];
    }

    // End of DataStoreRead: '<S7>/Data Store ReadP'

    // MATLAB Function: '<S7>/Correct' incorporates:
    //   Constant: '<S1>/R3'

    rtDW.blockOrdering_p = rtDW.Correct2_a.blockOrdering;
    blockOrdering = rtDW.blockOrdering_p;
    rtDW.blockOrdering_p = blockOrdering;
    for (i = 0; i < 9; i++) {
      a22 = rtDW.P_a[i];
      rtDW.P_a[i] = a22;
    }

    for (r1 = 0; r1 < 3; r1++) {
      imvec_0[0] = rtDW.DataStoreReadX_i[0];
      epsilon = 1.4901161193847656E-8 * std::abs(rtDW.DataStoreReadX_i[r1]);
      if ((1.4901161193847656E-8 > epsilon) || rtIsNaN(epsilon)) {
        epsilon = 1.4901161193847656E-8;
      }

      imvec_0[r1] = rtDW.DataStoreReadX_i[r1] + epsilon;
      dHdx_1[r1] = (imvec_0[0] - rtDW.DataStoreReadX_i[0]) / epsilon;
    }

    a22 = 0.0;
    for (i = 0; i < 3; i++) {
      epsilon = rtDW.P_a[3 * i] * dHdx_1[0];
      epsilon += rtDW.P_a[3 * i + 1] * dHdx_1[1];
      epsilon += rtDW.P_a[3 * i + 2] * dHdx_1[2];
      a22 += epsilon * dHdx_1[i];
    }

    epsilon = a22 + rtP.R3_Value;
    a22 = rtDW.NED_convert - rtDW.DataStoreReadX_i[0];
    for (i = 0; i < 3; i++) {
      imvec_2 = rtDW.P_a[i] * dHdx_1[0];
      imvec_2 += rtDW.P_a[i + 3] * dHdx_1[1];
      imvec_2 += rtDW.P_a[i + 6] * dHdx_1[2];
      imvec_2 /= epsilon;
      rtDW.xNew_p[i] = imvec_2 * a22 + rtDW.DataStoreReadX_i[i];
      imvec_0[i] = imvec_2;
    }

    for (i = 0; i < 3; i++) {
      a22 = dHdx_1[i];
      imvec_1[3 * i] = imvec_0[0] * a22;
      imvec_1[3 * i + 1] = imvec_0[1] * a22;
      imvec_1[3 * i + 2] = imvec_0[2] * a22;
    }

    for (i = 0; i < 3; i++) {
      for (k = 0; k < 3; k++) {
        imvec_2 = rtDW.P_a[3 * i] * imvec_1[k];
        imvec_2 += rtDW.P_a[3 * i + 1] * imvec_1[k + 3];
        imvec_2 += rtDW.P_a[3 * i + 2] * imvec_1[k + 6];
        a[k + 3 * i] = rtDW.P_a[3 * i + k] - imvec_2;
      }
    }

    for (i = 0; i < 9; i++) {
      rtDW.P_a[i] = a[i];

      // DataStoreWrite: '<S7>/Data Store WriteP'
      rtDW.P_i_m[i] = rtDW.P_a[i];
    }

    // End of MATLAB Function: '<S7>/Correct'

    // DataStoreWrite: '<S7>/Data Store WriteX'
    rtDW.x[0] = rtDW.xNew_p[0];
    rtDW.x[1] = rtDW.xNew_p[1];
    rtDW.x[2] = rtDW.xNew_p[2];
  }

  // End of Outputs for SubSystem: '<S1>/Correct3'

  // DataTypeConversion: '<S1>/DataTypeConversion_Enable4' incorporates:
  //   Inport: '<Root>/LidarFlag'

  rtDW.DataTypeConversion_Enable4 = (rtU.LidarFlag != 0.0);

  // Outputs for Enabled SubSystem: '<S1>/Correct4'
  // Constant: '<S1>/R4'
  Correct2(rtDW.DataTypeConversion_Enable4, rtDW.NED_convert1, rtP.R4_Value,
           rtDW.blockOrdering_p, &rtDW.Correct4, rtDW.P_i_m, rtDW.x);

  // End of Outputs for SubSystem: '<S1>/Correct4'

  // Outputs for Atomic SubSystem: '<S1>/Output'
  // DataStoreRead: '<S9>/Data Store Read'
  rtDW.DataStoreRead_f[0] = rtDW.x[0];
  rtDW.DataStoreRead_f[1] = rtDW.x[1];
  rtDW.DataStoreRead_f[2] = rtDW.x[2];

  // DataStoreRead: '<S9>/Data Store Read1'
  for (i = 0; i < 9; i++) {
    rtDW.DataStoreRead1_h[i] = rtDW.P_i_m[i];
  }

  // End of DataStoreRead: '<S9>/Data Store Read1'

  // Inport: '<S9>/uBlockOrdering'
  rtDW.uBlockOrdering_b = rtDW.Correct4.blockOrdering;

  // End of Outputs for SubSystem: '<S1>/Output'

  // Outport: '<Root>/estiZ'
  rtY.estiZ = rtDW.DataStoreRead_f[0];

  // Outport: '<Root>/estiVX'
  rtY.estiVX = rtDW.DataStoreRead[2];

  // Outport: '<Root>/estiVY'
  rtY.estiVY = rtDW.DataStoreRead[3];

  // Outport: '<Root>/estiVZ'
  rtY.estiVZ = rtDW.DataStoreRead_f[1];

  // Outport: '<Root>/estiAX'
  rtY.estiAX = rtDW.DataStoreRead[4];

  // Outport: '<Root>/estiAY'
  rtY.estiAY = rtDW.DataStoreRead[5];

  // Outport: '<Root>/estiAZ'
  rtY.estiAZ = rtDW.DataStoreRead_f[2];

  // UnitConversion: '<S41>/Unit Conversion' incorporates:
  //   Constant: '<S3>/Constant'

  // Unit Conversion - from: deg to: rad
  // Expression: output = (0.0174533*input) + (0)
  rtDW.UnitConversion_me = 0.017453292519943295 * rtP.Constant_Value_ay;

  // Trigonometry: '<S26>/SinCos'
  a22 = rtDW.UnitConversion_me;
  epsilon = std::sin(a22);
  a22 = std::cos(a22);
  rtDW.SinCos_o1_f = epsilon;
  rtDW.SinCos_o2_e = a22;

  // Product: '<S26>/x*cos'
  rtDW.xcos_p = rtDW.DataStoreRead[0] * rtDW.SinCos_o2_e;

  // Product: '<S26>/y*sin'
  rtDW.ysin_m = rtDW.DataStoreRead[1] * rtDW.SinCos_o1_f;

  // Sum: '<S26>/Sum'
  rtDW.Sum_g = rtDW.xcos_p - rtDW.ysin_m;

  // Sum: '<S44>/Sum' incorporates:
  //   Constant: '<S44>/Constant'
  //   Constant: '<S44>/f'

  rtDW.Sum_ah = rtP.f_Value_f - rtP.Constant_Value_d;

  // Product: '<S45>/Product1'
  rtDW.Product1_f = rtDW.Sum_ah * rtDW.Sum_ah;

  // Sum: '<S45>/Sum1' incorporates:
  //   Constant: '<S45>/Constant'

  rtDW.Sum1_p = rtP.Constant_Value_j - rtDW.Product1_f;

  // Sqrt: '<S45>/sqrt'
  rtDW.sqrt_p = std::sqrt(rtDW.Sum1_p);

  // Abs: '<S37>/Abs' incorporates:
  //   Inport: '<Root>/HOME_lla'

  rtDW.Abs_o = std::abs(rtU.HOME_lla[0]);

  // RelationalOperator: '<S38>/Compare' incorporates:
  //   Constant: '<S38>/Constant'

  rtDW.Compare_cm = (rtDW.Abs_o > rtP.CompareToConstant_const_f);

  // Switch: '<S37>/Switch' incorporates:
  //   Inport: '<Root>/HOME_lla'

  if (rtDW.Compare_cm) {
    // Bias: '<S37>/Bias' incorporates:
    //   Inport: '<Root>/HOME_lla'

    rtDW.Bias_g = rtU.HOME_lla[0] + rtP.Bias_Bias_l;

    // Math: '<S37>/Math Function1' incorporates:
    //   Constant: '<S37>/Constant2'

    rtDW.MathFunction1_b = rt_modd_snf(rtDW.Bias_g, rtP.Constant2_Value_c);

    // Bias: '<S37>/Bias1'
    rtDW.Bias1_f = rtDW.MathFunction1_b + rtP.Bias1_Bias_o;
    rtDW.Switch_e = rtDW.Bias1_f;
  } else {
    rtDW.Switch_e = rtU.HOME_lla[0];
  }

  // End of Switch: '<S37>/Switch'

  // Abs: '<S34>/Abs1'
  rtDW.Abs1_c = std::abs(rtDW.Switch_e);

  // RelationalOperator: '<S36>/Compare' incorporates:
  //   Constant: '<S36>/Constant'

  rtDW.Compare_a = (rtDW.Abs1_c > rtP.CompareToConstant_const_i);

  // Switch: '<S34>/Switch' incorporates:
  //   Constant: '<S25>/Constant'
  //   Constant: '<S25>/Constant1'
  //   Switch: '<S25>/Switch1'

  if (rtDW.Compare_a) {
    // Bias: '<S34>/Bias'
    rtDW.Bias_et = rtDW.Abs1_c + rtP.Bias_Bias_o;

    // Gain: '<S34>/Gain'
    rtDW.Gain_f = rtP.Gain_Gain_o * rtDW.Bias_et;

    // Bias: '<S34>/Bias1'
    rtDW.Bias1_d = rtDW.Gain_f + rtP.Bias1_Bias_d;

    // Signum: '<S34>/Sign1'
    a22 = rtDW.Switch_e;
    if (a22 < 0.0) {
      rtDW.Sign1_j = -1.0;
    } else if (a22 > 0.0) {
      rtDW.Sign1_j = 1.0;
    } else if (a22 == 0.0) {
      rtDW.Sign1_j = 0.0;
    } else {
      rtDW.Sign1_j = (rtNaN);
    }

    // End of Signum: '<S34>/Sign1'

    // Product: '<S34>/Divide1'
    rtDW.Divide1_o = rtDW.Sign1_j * rtDW.Bias1_d;
    rtDW.Switch_i = rtDW.Divide1_o;
    rtDW.Switch1_l = rtP.Constant_Value_l;
  } else {
    rtDW.Switch_i = rtDW.Switch_e;
    rtDW.Switch1_l = rtP.Constant1_Value_f;
  }

  // End of Switch: '<S34>/Switch'

  // UnitConversion: '<S42>/Unit Conversion'
  // Unit Conversion - from: deg to: rad
  // Expression: output = (0.0174533*input) + (0)
  rtDW.UnitConversion_a = 0.017453292519943295 * rtDW.Switch_i;

  // Trigonometry: '<S43>/Trigonometric Function1'
  rtDW.TrigonometricFunction1_b = std::sin(rtDW.UnitConversion_a);

  // Product: '<S43>/Product1'
  rtDW.Product1_k = rtDW.sqrt_p * rtDW.sqrt_p * rtDW.TrigonometricFunction1_b *
    rtDW.TrigonometricFunction1_b;

  // Sum: '<S43>/Sum1' incorporates:
  //   Constant: '<S43>/Constant'

  rtDW.Sum1_l = rtP.Constant_Value_g - rtDW.Product1_k;

  // Sqrt: '<S40>/sqrt'
  rtDW.sqrt_f = std::sqrt(rtDW.Sum1_l);

  // Product: '<S40>/Product1' incorporates:
  //   Constant: '<S40>/Constant1'

  rtDW.Rn_n = rtP.Constant1_Value_l / rtDW.sqrt_f;

  // Product: '<S40>/Product2'
  rtDW.Product2_c = rtDW.sqrt_p * rtDW.sqrt_p;

  // Sum: '<S40>/Sum1' incorporates:
  //   Constant: '<S40>/Constant'

  rtDW.Sum1_l4 = rtP.Constant_Value_g2 - rtDW.Product2_c;

  // Product: '<S40>/Product3'
  rtDW.Rm_o = rtDW.Rn_n * rtDW.Sum1_l4 / rtDW.Sum1_l;

  // Trigonometry: '<S40>/Trigonometric Function1' incorporates:
  //   Constant: '<S40>/Constant2'

  rtDW.TrigonometricFunction1_p = rt_atan2d_snf(rtP.Constant2_Value_l, rtDW.Rm_o);

  // Product: '<S26>/rad lat'
  rtDW.radlat = rtDW.Sum_g * rtDW.TrigonometricFunction1_p;

  // Trigonometry: '<S40>/Trigonometric Function'
  rtDW.TrigonometricFunction_f = std::cos(rtDW.UnitConversion_a);

  // Product: '<S40>/Product4'
  rtDW.Product4_n = rtDW.Rn_n * rtDW.TrigonometricFunction_f;

  // Trigonometry: '<S40>/Trigonometric Function2' incorporates:
  //   Constant: '<S40>/Constant3'

  rtDW.TrigonometricFunction2_d = rt_atan2d_snf(rtP.Constant3_Value_l,
    rtDW.Product4_n);

  // Product: '<S26>/x*sin'
  rtDW.xsin_n = rtDW.DataStoreRead[0] * rtDW.SinCos_o1_f;

  // Product: '<S26>/y*cos'
  rtDW.ycos_k = rtDW.DataStoreRead[1] * rtDW.SinCos_o2_e;

  // Sum: '<S26>/Sum1'
  rtDW.Sum1_a = rtDW.xsin_n + rtDW.ycos_k;

  // Product: '<S26>/rad long '
  rtDW.radlong = rtDW.TrigonometricFunction2_d * rtDW.Sum1_a;

  // UnitConversion: '<S27>/Unit Conversion'
  // Unit Conversion - from: rad to: deg
  // Expression: output = (57.2958*input) + (0)
  rtDW.UnitConversion_h[0] = 57.295779513082323 * rtDW.radlat;
  rtDW.UnitConversion_h[1] = 57.295779513082323 * rtDW.radlong;

  // Sum: '<S25>/Sum' incorporates:
  //   Inport: '<Root>/HOME_lla'

  rtDW.Sum_c = rtDW.Switch1_l + rtU.HOME_lla[1];

  // Abs: '<S35>/Abs'
  rtDW.Abs_c = std::abs(rtDW.Sum_c);

  // RelationalOperator: '<S39>/Compare' incorporates:
  //   Constant: '<S39>/Constant'

  rtDW.Compare_a0 = (rtDW.Abs_c > rtP.CompareToConstant_const_l);

  // Switch: '<S35>/Switch'
  if (rtDW.Compare_a0) {
    // Bias: '<S35>/Bias'
    rtDW.Bias_i = rtDW.Sum_c + rtP.Bias_Bias_p;

    // Math: '<S35>/Math Function1' incorporates:
    //   Constant: '<S35>/Constant2'

    rtDW.MathFunction1_p = rt_modd_snf(rtDW.Bias_i, rtP.Constant2_Value_k);

    // Bias: '<S35>/Bias1'
    rtDW.Bias1_ny = rtDW.MathFunction1_p + rtP.Bias1_Bias_m;
    rtDW.Switch_ed = rtDW.Bias1_ny;
  } else {
    rtDW.Switch_ed = rtDW.Sum_c;
  }

  // End of Switch: '<S35>/Switch'

  // Sum: '<S23>/Sum'
  rtDW.Sum_o[0] = rtDW.UnitConversion_h[0] + rtDW.Switch_i;
  rtDW.Sum_o[1] = rtDW.UnitConversion_h[1] + rtDW.Switch_ed;

  // Abs: '<S31>/Abs'
  rtDW.Abs_d = std::abs(rtDW.Sum_o[0]);

  // RelationalOperator: '<S32>/Compare' incorporates:
  //   Constant: '<S32>/Constant'

  rtDW.Compare_ko = (rtDW.Abs_d > rtP.CompareToConstant_const_em);

  // Switch: '<S31>/Switch'
  if (rtDW.Compare_ko) {
    // Bias: '<S31>/Bias'
    rtDW.Bias_f = rtDW.Sum_o[0] + rtP.Bias_Bias_n;

    // Math: '<S31>/Math Function1' incorporates:
    //   Constant: '<S31>/Constant2'

    rtDW.MathFunction1_l = rt_modd_snf(rtDW.Bias_f, rtP.Constant2_Value);

    // Bias: '<S31>/Bias1'
    rtDW.Bias1_a = rtDW.MathFunction1_l + rtP.Bias1_Bias_k;
    rtDW.Switch_js = rtDW.Bias1_a;
  } else {
    rtDW.Switch_js = rtDW.Sum_o[0];
  }

  // End of Switch: '<S31>/Switch'

  // Abs: '<S28>/Abs1'
  rtDW.Abs1_n = std::abs(rtDW.Switch_js);

  // RelationalOperator: '<S30>/Compare' incorporates:
  //   Constant: '<S30>/Constant'

  rtDW.Compare_j = (rtDW.Abs1_n > rtP.CompareToConstant_const_j3);

  // Switch: '<S28>/Switch' incorporates:
  //   Constant: '<S24>/Constant'
  //   Constant: '<S24>/Constant1'
  //   Switch: '<S24>/Switch1'

  if (rtDW.Compare_j) {
    // Bias: '<S28>/Bias'
    rtDW.Bias_fd = rtDW.Abs1_n + rtP.Bias_Bias;

    // Gain: '<S28>/Gain'
    rtDW.Gain_m = rtP.Gain_Gain * rtDW.Bias_fd;

    // Bias: '<S28>/Bias1'
    rtDW.Bias1_i = rtDW.Gain_m + rtP.Bias1_Bias;

    // Signum: '<S28>/Sign1'
    a22 = rtDW.Switch_js;
    if (a22 < 0.0) {
      rtDW.Sign1_d = -1.0;
    } else if (a22 > 0.0) {
      rtDW.Sign1_d = 1.0;
    } else if (a22 == 0.0) {
      rtDW.Sign1_d = 0.0;
    } else {
      rtDW.Sign1_d = (rtNaN);
    }

    // End of Signum: '<S28>/Sign1'

    // Product: '<S28>/Divide1'
    rtDW.Divide1_og = rtDW.Sign1_d * rtDW.Bias1_i;
    rtDW.Switch_l = rtDW.Divide1_og;
    rtDW.Switch1_m = rtP.Constant_Value;
  } else {
    rtDW.Switch_l = rtDW.Switch_js;
    rtDW.Switch1_m = rtP.Constant1_Value;
  }

  // End of Switch: '<S28>/Switch'

  // Sum: '<S24>/Sum'
  rtDW.Sum_ad = rtDW.Switch1_m + rtDW.Sum_o[1];

  // Abs: '<S29>/Abs'
  rtDW.Abs_b4 = std::abs(rtDW.Sum_ad);

  // RelationalOperator: '<S33>/Compare' incorporates:
  //   Constant: '<S33>/Constant'

  rtDW.Compare_e = (rtDW.Abs_b4 > rtP.CompareToConstant_const_ik);

  // Switch: '<S29>/Switch'
  if (rtDW.Compare_e) {
    // Bias: '<S29>/Bias'
    rtDW.Bias_c = rtDW.Sum_ad + rtP.Bias_Bias_k;

    // Math: '<S29>/Math Function1' incorporates:
    //   Constant: '<S29>/Constant2'

    rtDW.MathFunction1_ha = rt_modd_snf(rtDW.Bias_c, rtP.Constant2_Value_j);

    // Bias: '<S29>/Bias1'
    rtDW.Bias1_g = rtDW.MathFunction1_ha + rtP.Bias1_Bias_i;
    rtDW.Switch_g = rtDW.Bias1_g;
  } else {
    rtDW.Switch_g = rtDW.Sum_ad;
  }

  // End of Switch: '<S29>/Switch'

  // Outport: '<Root>/Estim_LatLon'
  rtY.Estim_LatLon[0] = rtDW.Switch_l;
  rtY.Estim_LatLon[1] = rtDW.Switch_g;

  // UnaryMinus: '<S23>/Ze2height'
  rtDW.alt_o = -rtDW.DataStoreRead_f[0];

  // Outport: '<Root>/Estim_Alt' incorporates:
  //   Inport: '<Root>/HOME_lla'
  //   Sum: '<S23>/Sum1'

  rtY.Estim_Alt = rtDW.alt_o - rtU.HOME_lla[2];

  // Outputs for Atomic SubSystem: '<S1>/Predict'
  // DataStoreRead: '<S10>/Data Store ReadX'
  rtDW.DataStoreReadX_g[0] = rtDW.x[0];
  rtDW.DataStoreReadX_g[1] = rtDW.x[1];
  rtDW.DataStoreReadX_g[2] = rtDW.x[2];
  for (i = 0; i < 9; i++) {
    // DataStoreRead: '<S10>/Data Store ReadP'
    rtDW.P_i[i] = rtDW.P_i_m[i];

    // MATLAB Function: '<S10>/Predict'
    a22 = rtDW.P_i[i];
    rtDW.P_i[i] = a22;
  }

  // MATLAB Function: '<S10>/Predict' incorporates:
  //   Constant: '<S1>/Q'

  for (i = 0; i < 3; i++) {
    imvec_2 = 0.0;
    for (k = 0; k < 3; k++) {
      imvec_2 += a_1[3 * k + i] * rtDW.DataStoreReadX_g[k];
      imvec_1[i + 3 * k] = 0.0;
      a22 = imvec_1[3 * k + i];
      a22 += rtDW.P_i[3 * k] * a_1[i];
      imvec_1[i + 3 * k] = a22;
      a22 = imvec_1[3 * k + i];
      a22 += rtDW.P_i[3 * k + 1] * a_1[i + 3];
      imvec_1[i + 3 * k] = a22;
      a22 = imvec_1[3 * k + i];
      a22 += rtDW.P_i[3 * k + 2] * a_1[i + 6];
      imvec_1[i + 3 * k] = a22;
    }

    rtDW.xNew_k[i] = imvec_2;
    for (k = 0; k < 3; k++) {
      a[i + 3 * k] = 0.0;
      a22 = a[3 * k + i];
      a22 += b[3 * k] * imvec_1[i];
      a[i + 3 * k] = a22;
      a22 = a[3 * k + i];
      a22 += b[3 * k + 1] * imvec_1[i + 3];
      a[i + 3 * k] = a22;
      a22 = a[3 * k + i];
      a22 += b[3 * k + 2] * imvec_1[i + 6];
      a[i + 3 * k] = a22;
      b_a[k + 3 * i] = b_a_0[k] * rtP.Q_Value * b_a_0[i];
    }
  }

  for (i = 0; i < 9; i++) {
    rtDW.P_i[i] = a[i] + b_a[i];

    // DataStoreWrite: '<S10>/Data Store WriteP'
    rtDW.P_i_m[i] = rtDW.P_i[i];
  }

  // DataStoreWrite: '<S10>/Data Store WriteX'
  rtDW.x[0] = rtDW.xNew_k[0];
  rtDW.x[1] = rtDW.xNew_k[1];
  rtDW.x[2] = rtDW.xNew_k[2];

  // End of Outputs for SubSystem: '<S1>/Predict'

  // Outputs for Atomic SubSystem: '<S2>/Predict'
  // DataStoreRead: '<S19>/Data Store ReadX'
  for (i = 0; i < 6; i++) {
    rtDW.DataStoreReadX[i] = rtDW.x_p[i];
  }

  // End of DataStoreRead: '<S19>/Data Store ReadX'
  for (i = 0; i < 36; i++) {
    // DataStoreRead: '<S19>/Data Store ReadP'
    rtDW.P_n[i] = rtDW.P_n_c[i];

    // MATLAB Function: '<S19>/Predict'
    a22 = rtDW.P_n[i];
    rtDW.P_n[i] = a22;
  }

  // MATLAB Function: '<S19>/Predict' incorporates:
  //   Constant: '<S2>/Q'

  for (i = 0; i < 6; i++) {
    rtDW.xNew[i] = 0.0;
    for (k = 0; k < 6; k++) {
      rtDW.xNew[i] += a_2[6 * k + i] * rtDW.DataStoreReadX[k];
      gain_0[i + 6 * k] = 0.0;
      for (r1 = 0; r1 < 6; r1++) {
        a22 = gain_0[6 * k + i];
        a22 += a_2[6 * r1 + i] * rtDW.P_n[6 * k + r1];
        gain_0[i + 6 * k] = a22;
      }
    }
  }

  for (i = 0; i < 6; i++) {
    for (k = 0; k < 6; k++) {
      imvec_2 = 0.0;
      for (r1 = 0; r1 < 6; r1++) {
        imvec_2 += gain_0[6 * r1 + k] * b_0[6 * i + r1];
      }

      rtDW.P_n[k + 6 * i] = rtP.Q_Value_c[6 * i + k] + imvec_2;
    }
  }

  // DataStoreWrite: '<S19>/Data Store WriteP'
  for (i = 0; i < 36; i++) {
    rtDW.P_n_c[i] = rtDW.P_n[i];
  }

  // End of DataStoreWrite: '<S19>/Data Store WriteP'

  // DataStoreWrite: '<S19>/Data Store WriteX'
  for (i = 0; i < 6; i++) {
    rtDW.x_p[i] = rtDW.xNew[i];
  }

  // End of DataStoreWrite: '<S19>/Data Store WriteX'
  // End of Outputs for SubSystem: '<S2>/Predict'
}

// Model initialize function
void positionEstimatorModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    int32_T i;

    // Start for DataStoreMemory: '<S1>/DataStoreMemory - P'
    for (i = 0; i < 9; i++) {
      rtDW.P_i_m[i] = rtP.DataStoreMemoryP_InitialValue[i];
    }

    // End of Start for DataStoreMemory: '<S1>/DataStoreMemory - P'

    // Start for DataStoreMemory: '<S1>/DataStoreMemory - x'
    rtDW.x[0] = rtP.DataStoreMemoryx_InitialValue[0];
    rtDW.x[1] = rtP.DataStoreMemoryx_InitialValue[1];
    rtDW.x[2] = rtP.DataStoreMemoryx_InitialValue[2];

    // Start for DataStoreMemory: '<S2>/DataStoreMemory - P'
    for (i = 0; i < 36; i++) {
      rtDW.P_n_c[i] = rtP.DataStoreMemoryP_InitialValue_m[i];
    }

    // End of Start for DataStoreMemory: '<S2>/DataStoreMemory - P'

    // Start for DataStoreMemory: '<S2>/DataStoreMemory - x'
    for (i = 0; i < 6; i++) {
      rtDW.x_p[i] = rtP.DataStoreMemoryx_InitialValue_j[i];
    }

    // End of Start for DataStoreMemory: '<S2>/DataStoreMemory - x'

    // SystemInitialize for Enabled SubSystem: '<S2>/Correct1'
    // SystemInitialize for Outport: '<S16>/yBlockOrdering'
    rtDW.blockOrdering_f = rtP.yBlockOrdering_Y0_a;

    // End of SystemInitialize for SubSystem: '<S2>/Correct1'

    // SystemInitialize for Enabled SubSystem: '<S2>/Correct2'
    // SystemInitialize for Outport: '<S17>/yBlockOrdering'
    rtDW.blockOrdering = rtP.yBlockOrdering_Y0_g;

    // End of SystemInitialize for SubSystem: '<S2>/Correct2'

    // SystemInitialize for Enabled SubSystem: '<S1>/Correct1'
    // SystemInitialize for Outport: '<S5>/yBlockOrdering'
    rtDW.blockOrdering_k = rtP.yBlockOrdering_Y0;

    // End of SystemInitialize for SubSystem: '<S1>/Correct1'

    // SystemInitialize for Enabled SubSystem: '<S1>/Correct2'
    Correct2_Init(&rtDW.Correct2_a, &rtP.Correct2_a);

    // End of SystemInitialize for SubSystem: '<S1>/Correct2'

    // SystemInitialize for Enabled SubSystem: '<S1>/Correct3'
    // SystemInitialize for Outport: '<S7>/yBlockOrdering'
    rtDW.blockOrdering_p = rtP.yBlockOrdering_Y0_b;

    // End of SystemInitialize for SubSystem: '<S1>/Correct3'

    // SystemInitialize for Enabled SubSystem: '<S1>/Correct4'
    Correct2_Init(&rtDW.Correct4, &rtP.Correct4);

    // End of SystemInitialize for SubSystem: '<S1>/Correct4'
  }
}

// Constructor
positionEstimatorModelClass::positionEstimatorModelClass():
  rtDW()
  ,rtU()
  ,rtY()
  ,rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
positionEstimatorModelClass::~positionEstimatorModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
positionEstimatorModelClass::RT_MODEL * positionEstimatorModelClass::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
