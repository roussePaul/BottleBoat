/* Include files */

#include <stddef.h>
#include "blas.h"
#include "SailingYachtModel2_sfun.h"
#include "c5_SailingYachtModel2.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "SailingYachtModel2_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c5_debug_family_names[39] = { "par", "V_in", "x", "y", "phi",
  "psi", "v", "p", "r", "nu", "delta_r", "delta_sbar", "y_w", "M_RB", "C_RB",
  "M_A", "C_A", "M", "v_t", "v_tw", "R1", "R2", "v_tb", "V_awb", "V_awu",
  "V_awv", "alpha_aw", "v_aku", "v_akv", "alpha_ak", "alpha_e", "v_ahu", "v_ahv",
  "v_ah", "alpha_ah", "u", "nargin", "nargout", "alpha" };

static const char * c5_b_debug_family_names[3] = { "nargin", "nargout", "par" };

/* Function Declarations */
static void initialize_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance);
static void initialize_params_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance);
static void enable_c5_SailingYachtModel2(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance);
static void disable_c5_SailingYachtModel2(SFc5_SailingYachtModel2InstanceStruct *
  chartInstance);
static void c5_update_debugger_state_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance);
static void set_sim_state_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance, const mxArray *c5_st);
static void finalize_c5_SailingYachtModel2(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance);
static void sf_gateway_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance);
static void c5_chartstep_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance);
static void initSimStructsc5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static real_T c5_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_alpha, const char_T *c5_identifier);
static real_T c5_b_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_c_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[3]);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_d_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[9]);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_e_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[16]);
static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_f_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[4]);
static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static void c5_g_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[11]);
static void c5_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_g_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_h_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  c5_srLgvkCzuuZn3rWrmrpDanB *c5_y);
static void c5_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static void c5_info_helper(const mxArray **c5_info);
static const mxArray *c5_emlrt_marshallOut(const char * c5_u);
static const mxArray *c5_b_emlrt_marshallOut(const uint32_T c5_u);
static real_T c5_log(SFc5_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T c5_x);
static void c5_eml_error(SFc5_SailingYachtModel2InstanceStruct *chartInstance);
static void c5_eml_scalar_eg(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance);
static void c5_threshold(SFc5_SailingYachtModel2InstanceStruct *chartInstance);
static void c5_b_eml_scalar_eg(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance);
static real_T c5_atan2(SFc5_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c5_y, real_T c5_x);
static void c5_c_eml_scalar_eg(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance);
static real_T c5_mpower(SFc5_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c5_a);
static void c5_b_eml_error(SFc5_SailingYachtModel2InstanceStruct *chartInstance);
static const mxArray *c5_h_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_i_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static uint8_T c5_j_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_SailingYachtModel2, const
  char_T *c5_identifier);
static uint8_T c5_k_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_log(SFc5_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T *c5_x);
static void init_dsm_address_info(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance)
{
  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_is_active_c5_SailingYachtModel2 = 0U;
}

static void initialize_params_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c5_SailingYachtModel2(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c5_SailingYachtModel2(SFc5_SailingYachtModel2InstanceStruct *
  chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c5_update_debugger_state_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  real_T c5_hoistedGlobal;
  real_T c5_u;
  const mxArray *c5_b_y = NULL;
  uint8_T c5_b_hoistedGlobal;
  uint8_T c5_b_u;
  const mxArray *c5_c_y = NULL;
  real_T *c5_alpha;
  c5_alpha = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(2, 1), false);
  c5_hoistedGlobal = *c5_alpha;
  c5_u = c5_hoistedGlobal;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_b_hoistedGlobal = chartInstance->c5_is_active_c5_SailingYachtModel2;
  c5_b_u = c5_b_hoistedGlobal;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  real_T *c5_alpha;
  c5_alpha = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c5_doneDoubleBufferReInit = true;
  c5_u = sf_mex_dup(c5_st);
  *c5_alpha = c5_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u,
    0)), "alpha");
  chartInstance->c5_is_active_c5_SailingYachtModel2 = c5_j_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 1)),
     "is_active_c5_SailingYachtModel2");
  sf_mex_destroy(&c5_u);
  c5_update_debugger_state_c5_SailingYachtModel2(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_SailingYachtModel2(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance)
{
  int32_T c5_i0;
  real_T *c5_alpha;
  real_T (*c5_u)[11];
  c5_alpha = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_u = (real_T (*)[11])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  for (c5_i0 = 0; c5_i0 < 11; c5_i0++) {
    _SFD_DATA_RANGE_CHECK((*c5_u)[c5_i0], 0U);
  }

  chartInstance->c5_sfEvent = CALL_EVENT;
  c5_chartstep_c5_SailingYachtModel2(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_SailingYachtModel2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*c5_alpha, 1U);
}

static void c5_chartstep_c5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance)
{
  int32_T c5_i1;
  real_T c5_u[11];
  uint32_T c5_debug_family_var_map[39];
  c5_srLgvkCzuuZn3rWrmrpDanB c5_par;
  real_T c5_V_in[11];
  real_T c5_x;
  real_T c5_y;
  real_T c5_phi;
  real_T c5_psi;
  real_T c5_v;
  real_T c5_p;
  real_T c5_r;
  real_T c5_nu[4];
  real_T c5_delta_r;
  real_T c5_delta_sbar;
  real_T c5_y_w;
  real_T c5_M_RB[16];
  real_T c5_C_RB[16];
  real_T c5_M_A[16];
  real_T c5_C_A[16];
  real_T c5_M[16];
  real_T c5_v_t[3];
  real_T c5_v_tw[3];
  real_T c5_R1[9];
  real_T c5_R2[9];
  real_T c5_v_tb[3];
  real_T c5_V_awb[3];
  real_T c5_V_awu;
  real_T c5_V_awv;
  real_T c5_alpha_aw;
  real_T c5_v_aku;
  real_T c5_v_akv;
  real_T c5_alpha_ak;
  real_T c5_alpha_e;
  real_T c5_v_ahu;
  real_T c5_v_ahv;
  real_T c5_v_ah;
  real_T c5_alpha_ah;
  real_T c5_b_u;
  real_T c5_b_V_in[3];
  real_T c5_nargin = 1.0;
  real_T c5_nargout = 1.0;
  real_T c5_alpha;
  static c5_srLgvkCzuuZn3rWrmrpDanB c5_r0 = { 25900.0, 133690.0, 24760.0, 2180.0,
    970.0, 17430.0, 106500.0, 101650.0, -13160.0, -6190.0, 4730.0, 10.0,
    3.1415926535897931, 1.2, 170.0, 0.0005, 11.58, -11.58, 0.0, 0.0, -11.58, 0.6,
    0.3, 1025.0, 1.17, 1.9, 0.8, -8.2, -0.78, -8.2, 0.0, -0.78, 8.7, 2.49, 0.7,
    0.0, -0.58, 0.0, 0.0, -0.58, 0.0, -1.18, 0.0, 0.0, -1.18, 60000.0, -8.0, 3.6,
    -5.89, 8160.0, 120000.0, 50000.0 };

  int32_T c5_i2;
  int32_T c5_i3;
  int32_T c5_i4;
  int32_T c5_i5;
  int32_T c5_i6;
  int32_T c5_i7;
  int32_T c5_i8;
  int32_T c5_i9;
  int32_T c5_i10;
  static real_T c5_b[3] = { -10.0, 1.2246467991473533E-15, 0.0 };

  real_T c5_b_x;
  real_T c5_c_x;
  real_T c5_A;
  real_T c5_d_x;
  real_T c5_e_x;
  real_T c5_f_x;
  real_T c5_b_y;
  real_T c5_b_A;
  real_T c5_g_x;
  real_T c5_h_x;
  real_T c5_i_x;
  real_T c5_c_y;
  real_T c5_a;
  int32_T c5_i11;
  real_T c5_j_x;
  real_T c5_k_x;
  real_T c5_l_x;
  real_T c5_m_x;
  real_T c5_n_x;
  real_T c5_o_x;
  real_T c5_p_x;
  real_T c5_q_x;
  int32_T c5_i12;
  int32_T c5_i13;
  static real_T c5_dv0[3] = { 0.0, 0.0, 1.0 };

  real_T c5_r_x;
  real_T c5_s_x;
  real_T c5_t_x;
  real_T c5_u_x;
  real_T c5_v_x;
  real_T c5_w_x;
  real_T c5_x_x;
  real_T c5_y_x;
  int32_T c5_i14;
  int32_T c5_i15;
  static real_T c5_dv1[3] = { 1.0, 0.0, 0.0 };

  int32_T c5_i16;
  real_T c5_b_a[9];
  int32_T c5_i17;
  real_T c5_b_b[9];
  int32_T c5_i18;
  int32_T c5_i19;
  int32_T c5_i20;
  real_T c5_d_y[9];
  int32_T c5_i21;
  int32_T c5_i22;
  int32_T c5_i23;
  real_T c5_c_b[3];
  int32_T c5_i24;
  int32_T c5_i25;
  int32_T c5_i26;
  real_T c5_C[3];
  int32_T c5_i27;
  int32_T c5_i28;
  int32_T c5_i29;
  int32_T c5_i30;
  int32_T c5_i31;
  int32_T c5_i32;
  real_T c5_c1;
  real_T c5_c2;
  real_T c5_c3;
  int32_T c5_i33;
  real_T c5_ab_x;
  real_T c5_bb_x;
  real_T c5_c_A;
  real_T c5_B;
  real_T c5_cb_x;
  real_T c5_e_y;
  real_T c5_db_x;
  real_T c5_f_y;
  real_T c5_eb_x;
  real_T c5_g_y;
  real_T c5_fb_x;
  real_T c5_gb_x;
  real_T *c5_b_alpha;
  real_T (*c5_c_u)[11];
  c5_b_alpha = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_c_u = (real_T (*)[11])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  for (c5_i1 = 0; c5_i1 < 11; c5_i1++) {
    c5_u[c5_i1] = (*c5_c_u)[c5_i1];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 39U, 41U, c5_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_par, 0U, c5_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_V_in, MAX_uint32_T,
    c5_b_sf_marshallOut, c5_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_x, 2U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_y, 3U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_phi, 4U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_psi, 5U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_v, 6U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_p, 7U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_r, 8U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_nu, 9U, c5_f_sf_marshallOut,
    c5_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_delta_r, 10U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_delta_sbar, 11U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_y_w, 12U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_M_RB, 13U, c5_e_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_C_RB, 14U, c5_e_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_M_A, 15U, c5_e_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_C_A, 16U, c5_e_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_M, 17U, c5_e_sf_marshallOut,
    c5_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_v_t, 18U, c5_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_v_tw, 19U, c5_c_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_R1, 20U, c5_d_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_R2, 21U, c5_d_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_v_tb, 22U, c5_c_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_V_awb, 23U, c5_c_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_V_awu, 24U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_V_awv, 25U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_alpha_aw, 26U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_v_aku, 27U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_v_akv, 28U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_alpha_ak, 29U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_alpha_e, 30U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_v_ahu, 31U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_v_ahv, 32U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_v_ah, 33U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_alpha_ah, 34U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_u, MAX_uint32_T, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c5_b_V_in, MAX_uint32_T,
    c5_c_sf_marshallOut, c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 36U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 37U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c5_u, 35U, c5_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_alpha, 38U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 19);
  c5_par = c5_r0;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 22);
  for (c5_i2 = 0; c5_i2 < 11; c5_i2++) {
    c5_V_in[c5_i2] = c5_u[c5_i2];
  }

  _SFD_SYMBOL_SWITCH(1U, 1U);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 24);
  c5_x = c5_V_in[3];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 25);
  c5_y = c5_V_in[4];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 26);
  c5_phi = c5_V_in[5];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 27);
  c5_psi = c5_V_in[6];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 28);
  c5_b_u = c5_V_in[7];
  _SFD_SYMBOL_SWITCH(35U, 35U);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 29);
  c5_v = c5_V_in[8];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 30);
  c5_p = c5_V_in[9];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 31);
  c5_r = c5_V_in[10];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 32);
  c5_nu[0] = c5_b_u;
  c5_nu[1] = c5_v;
  c5_nu[2] = c5_p;
  c5_nu[3] = c5_r;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 35);
  c5_delta_r = c5_V_in[0];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 36);
  c5_delta_sbar = c5_V_in[1];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 37);
  c5_y_w = c5_V_in[2];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 40);
  c5_M_RB[0] = c5_par.m;
  c5_M_RB[4] = 0.0;
  c5_M_RB[8] = 0.0;
  c5_M_RB[12] = 0.0;
  c5_M_RB[1] = 0.0;
  c5_M_RB[5] = c5_par.m;
  c5_M_RB[9] = 0.0;
  c5_M_RB[13] = 0.0;
  c5_M_RB[2] = 0.0;
  c5_M_RB[6] = 0.0;
  c5_M_RB[10] = c5_par.Ixx;
  c5_M_RB[14] = -c5_par.Ixz;
  c5_M_RB[3] = 0.0;
  c5_M_RB[7] = 0.0;
  c5_M_RB[11] = -c5_par.Ixz;
  c5_M_RB[15] = c5_par.Izz;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 41);
  c5_C_RB[0] = 0.0;
  c5_C_RB[4] = -25900.0 * c5_r;
  c5_C_RB[8] = 0.0;
  c5_C_RB[12] = 0.0;
  c5_C_RB[1] = 25900.0 * c5_r;
  c5_C_RB[5] = 0.0;
  c5_C_RB[9] = 0.0;
  c5_C_RB[13] = 0.0;
  c5_i3 = 0;
  for (c5_i4 = 0; c5_i4 < 4; c5_i4++) {
    c5_C_RB[c5_i3 + 2] = 0.0;
    c5_i3 += 4;
  }

  c5_i5 = 0;
  for (c5_i6 = 0; c5_i6 < 4; c5_i6++) {
    c5_C_RB[c5_i5 + 3] = 0.0;
    c5_i5 += 4;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 43);
  c5_M_A[0] = c5_par.a11;
  c5_M_A[4] = 0.0;
  c5_M_A[8] = 0.0;
  c5_M_A[12] = 0.0;
  c5_M_A[1] = 0.0;
  c5_M_A[5] = c5_par.a22;
  c5_M_A[9] = c5_par.a24;
  c5_M_A[13] = c5_par.a26;
  c5_M_A[2] = 0.0;
  c5_M_A[6] = c5_par.a24;
  c5_M_A[10] = c5_par.a44;
  c5_M_A[14] = c5_par.a46;
  c5_M_A[3] = 0.0;
  c5_M_A[7] = c5_par.a26;
  c5_M_A[11] = c5_par.a46;
  c5_M_A[15] = c5_par.a66;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 44);
  c5_C_A[0] = 0.0;
  c5_C_A[4] = 0.0;
  c5_C_A[8] = 0.0;
  c5_C_A[12] = (-17430.0 * c5_nu[1] - -13160.0 * c5_nu[2]) - -6190.0 * c5_nu[3];
  c5_C_A[1] = 0.0;
  c5_C_A[5] = 0.0;
  c5_C_A[9] = 0.0;
  c5_C_A[13] = 970.0 * c5_nu[0];
  c5_i7 = 0;
  for (c5_i8 = 0; c5_i8 < 4; c5_i8++) {
    c5_C_A[c5_i7 + 2] = 0.0;
    c5_i7 += 4;
  }

  c5_C_A[3] = (17430.0 * c5_nu[1] + -13160.0 * c5_nu[2]) + -6190.0 * c5_nu[3];
  c5_C_A[7] = -970.0 * c5_nu[0];
  c5_C_A[11] = 0.0;
  c5_C_A[15] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 46);
  for (c5_i9 = 0; c5_i9 < 16; c5_i9++) {
    c5_M[c5_i9] = c5_M_RB[c5_i9] + c5_M_A[c5_i9];
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 50);
  for (c5_i10 = 0; c5_i10 < 3; c5_i10++) {
    c5_v_t[c5_i10] = c5_b[c5_i10];
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 51);
  c5_b_x = c5_phi;
  c5_c_x = c5_b_x;
  c5_c_x = muDoubleScalarCos(c5_c_x);
  c5_A = 11.58 * c5_c_x;
  c5_d_x = c5_A;
  c5_e_x = c5_d_x;
  c5_f_x = c5_e_x;
  c5_b_y = c5_f_x / 0.0005;
  c5_b_A = c5_b_y;
  c5_b_log(chartInstance, &c5_b_A);
  c5_g_x = c5_b_A;
  c5_h_x = c5_g_x;
  c5_i_x = c5_h_x;
  c5_c_y = c5_i_x / 10.050181931686932;
  c5_a = c5_c_y;
  for (c5_i11 = 0; c5_i11 < 3; c5_i11++) {
    c5_v_tw[c5_i11] = c5_a * c5_b[c5_i11];
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 52);
  c5_j_x = -c5_psi;
  c5_k_x = c5_j_x;
  c5_k_x = muDoubleScalarCos(c5_k_x);
  c5_l_x = -c5_psi;
  c5_m_x = c5_l_x;
  c5_m_x = muDoubleScalarSin(c5_m_x);
  c5_n_x = -c5_psi;
  c5_o_x = c5_n_x;
  c5_o_x = muDoubleScalarSin(c5_o_x);
  c5_p_x = -c5_psi;
  c5_q_x = c5_p_x;
  c5_q_x = muDoubleScalarCos(c5_q_x);
  c5_R1[0] = c5_k_x;
  c5_R1[3] = -c5_m_x;
  c5_R1[6] = 0.0;
  c5_R1[1] = c5_o_x;
  c5_R1[4] = c5_q_x;
  c5_R1[7] = 0.0;
  c5_i12 = 0;
  for (c5_i13 = 0; c5_i13 < 3; c5_i13++) {
    c5_R1[c5_i12 + 2] = c5_dv0[c5_i13];
    c5_i12 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 53);
  c5_r_x = -c5_phi;
  c5_s_x = c5_r_x;
  c5_s_x = muDoubleScalarCos(c5_s_x);
  c5_t_x = -c5_phi;
  c5_u_x = c5_t_x;
  c5_u_x = muDoubleScalarSin(c5_u_x);
  c5_v_x = -c5_phi;
  c5_w_x = c5_v_x;
  c5_w_x = muDoubleScalarSin(c5_w_x);
  c5_x_x = -c5_phi;
  c5_y_x = c5_x_x;
  c5_y_x = muDoubleScalarCos(c5_y_x);
  c5_i14 = 0;
  for (c5_i15 = 0; c5_i15 < 3; c5_i15++) {
    c5_R2[c5_i14] = c5_dv1[c5_i15];
    c5_i14 += 3;
  }

  c5_R2[1] = 0.0;
  c5_R2[4] = c5_s_x;
  c5_R2[7] = -c5_u_x;
  c5_R2[2] = 0.0;
  c5_R2[5] = c5_w_x;
  c5_R2[8] = c5_y_x;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 54);
  for (c5_i16 = 0; c5_i16 < 9; c5_i16++) {
    c5_b_a[c5_i16] = c5_R2[c5_i16];
  }

  for (c5_i17 = 0; c5_i17 < 9; c5_i17++) {
    c5_b_b[c5_i17] = c5_R1[c5_i17];
  }

  c5_eml_scalar_eg(chartInstance);
  c5_eml_scalar_eg(chartInstance);
  c5_threshold(chartInstance);
  for (c5_i18 = 0; c5_i18 < 3; c5_i18++) {
    c5_i19 = 0;
    for (c5_i20 = 0; c5_i20 < 3; c5_i20++) {
      c5_d_y[c5_i19 + c5_i18] = 0.0;
      c5_i21 = 0;
      for (c5_i22 = 0; c5_i22 < 3; c5_i22++) {
        c5_d_y[c5_i19 + c5_i18] += c5_b_a[c5_i21 + c5_i18] * c5_b_b[c5_i22 +
          c5_i19];
        c5_i21 += 3;
      }

      c5_i19 += 3;
    }
  }

  for (c5_i23 = 0; c5_i23 < 3; c5_i23++) {
    c5_c_b[c5_i23] = c5_v_tw[c5_i23];
  }

  c5_b_eml_scalar_eg(chartInstance);
  c5_b_eml_scalar_eg(chartInstance);
  for (c5_i24 = 0; c5_i24 < 3; c5_i24++) {
    c5_v_tb[c5_i24] = 0.0;
  }

  for (c5_i25 = 0; c5_i25 < 3; c5_i25++) {
    c5_v_tb[c5_i25] = 0.0;
  }

  for (c5_i26 = 0; c5_i26 < 3; c5_i26++) {
    c5_C[c5_i26] = c5_v_tb[c5_i26];
  }

  for (c5_i27 = 0; c5_i27 < 3; c5_i27++) {
    c5_v_tb[c5_i27] = c5_C[c5_i27];
  }

  c5_threshold(chartInstance);
  for (c5_i28 = 0; c5_i28 < 3; c5_i28++) {
    c5_C[c5_i28] = c5_v_tb[c5_i28];
  }

  for (c5_i29 = 0; c5_i29 < 3; c5_i29++) {
    c5_v_tb[c5_i29] = c5_C[c5_i29];
  }

  for (c5_i30 = 0; c5_i30 < 3; c5_i30++) {
    c5_v_tb[c5_i30] = 0.0;
    c5_i31 = 0;
    for (c5_i32 = 0; c5_i32 < 3; c5_i32++) {
      c5_v_tb[c5_i30] += c5_d_y[c5_i31 + c5_i30] * c5_c_b[c5_i32];
      c5_i31 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 55);
  c5_b_V_in[0] = c5_b_u;
  c5_b_V_in[1] = c5_v;
  c5_b_V_in[2] = 0.0;
  _SFD_SYMBOL_SWITCH(1U, 36U);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 56);
  c5_c_b[0] = c5_p;
  c5_c_b[1] = 0.0;
  c5_c_b[2] = c5_r;
  c5_c1 = c5_c_b[1] * -11.58 - c5_c_b[2] * 0.0;
  c5_c2 = c5_c_b[2] * 0.0 - c5_c_b[0] * -11.58;
  c5_c3 = c5_c_b[0] * 0.0 - c5_c_b[1] * 0.0;
  c5_c_b[0] = c5_c1;
  c5_c_b[1] = c5_c2;
  c5_c_b[2] = c5_c3;
  for (c5_i33 = 0; c5_i33 < 3; c5_i33++) {
    c5_V_awb[c5_i33] = (c5_v_tb[c5_i33] - c5_b_V_in[c5_i33]) - c5_c_b[c5_i33];
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 57);
  c5_V_awu = c5_V_awb[0];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 58);
  c5_V_awv = c5_V_awb[1];
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 59);
  c5_alpha_aw = c5_atan2(chartInstance, c5_V_awv, -c5_V_awu);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 63);
  c5_v_aku = -c5_b_u + c5_r * 0.0;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 64);
  c5_v_akv = (-c5_v - c5_r * 0.0) + c5_p * -0.58;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 65);
  c5_alpha_ak = c5_atan2(chartInstance, c5_v_akv, -c5_v_aku);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 66);
  c5_alpha_e = c5_alpha_ak;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 69);
  c5_v_ahu = -c5_b_u + c5_r * 0.0;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 70);
  c5_ab_x = c5_phi;
  c5_bb_x = c5_ab_x;
  c5_bb_x = muDoubleScalarCos(c5_bb_x);
  c5_c_A = (-c5_v - c5_r * 0.0) + c5_p * -1.18;
  c5_B = c5_bb_x;
  c5_cb_x = c5_c_A;
  c5_e_y = c5_B;
  c5_db_x = c5_cb_x;
  c5_f_y = c5_e_y;
  c5_eb_x = c5_db_x;
  c5_g_y = c5_f_y;
  c5_v_ahv = c5_eb_x / c5_g_y;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 71);
  c5_fb_x = c5_mpower(chartInstance, c5_v_aku) + c5_mpower(chartInstance,
    c5_v_akv);
  c5_v_ah = c5_fb_x;
  if (c5_v_ah < 0.0) {
    c5_b_eml_error(chartInstance);
  }

  c5_gb_x = c5_v_ah;
  c5_v_ah = c5_gb_x;
  c5_v_ah = muDoubleScalarSqrt(c5_v_ah);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 72);
  c5_alpha_ah = c5_atan2(chartInstance, c5_v_ahv, -c5_v_ahu);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 73);
  c5_alpha = c5_v_ah;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -73);
  _SFD_SYMBOL_SCOPE_POP();
  *c5_b_alpha = c5_alpha;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
}

static void initSimStructsc5_SailingYachtModel2
  (SFc5_SailingYachtModel2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber)
{
  (void)c5_machineNumber;
  _SFD_SCRIPT_TRANSLATION(c5_chartNumber, c5_instanceNumber, 0U,
    sf_debug_get_script_id(
    "/home/paul/KTH/Optimal Control/BottleBoat/Simulink/modeleBoat.m"));
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_alpha, const char_T *c5_identifier)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_alpha), &c5_thisId);
  sf_mex_destroy(&c5_alpha);
  return c5_y;
}

static real_T c5_b_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d0, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_alpha;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_alpha = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_alpha), &c5_thisId);
  sf_mex_destroy(&c5_alpha);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i34;
  real_T c5_b_inData[11];
  int32_T c5_i35;
  real_T c5_u[11];
  const mxArray *c5_y = NULL;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i34 = 0; c5_i34 < 11; c5_i34++) {
    c5_b_inData[c5_i34] = (*(real_T (*)[11])c5_inData)[c5_i34];
  }

  for (c5_i35 = 0; c5_i35 < 11; c5_i35++) {
    c5_u[c5_i35] = c5_b_inData[c5_i35];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 11), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i36;
  real_T c5_b_inData[3];
  int32_T c5_i37;
  real_T c5_u[3];
  const mxArray *c5_y = NULL;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i36 = 0; c5_i36 < 3; c5_i36++) {
    c5_b_inData[c5_i36] = (*(real_T (*)[3])c5_inData)[c5_i36];
  }

  for (c5_i37 = 0; c5_i37 < 3; c5_i37++) {
    c5_u[c5_i37] = c5_b_inData[c5_i37];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_c_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[3])
{
  real_T c5_dv2[3];
  int32_T c5_i38;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv2, 1, 0, 0U, 1, 0U, 1, 3);
  for (c5_i38 = 0; c5_i38 < 3; c5_i38++) {
    c5_y[c5_i38] = c5_dv2[c5_i38];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_V_in;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[3];
  int32_T c5_i39;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_V_in = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_V_in), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_V_in);
  for (c5_i39 = 0; c5_i39 < 3; c5_i39++) {
    (*(real_T (*)[3])c5_outData)[c5_i39] = c5_y[c5_i39];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i40;
  int32_T c5_i41;
  int32_T c5_i42;
  real_T c5_b_inData[9];
  int32_T c5_i43;
  int32_T c5_i44;
  int32_T c5_i45;
  real_T c5_u[9];
  const mxArray *c5_y = NULL;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_i40 = 0;
  for (c5_i41 = 0; c5_i41 < 3; c5_i41++) {
    for (c5_i42 = 0; c5_i42 < 3; c5_i42++) {
      c5_b_inData[c5_i42 + c5_i40] = (*(real_T (*)[9])c5_inData)[c5_i42 + c5_i40];
    }

    c5_i40 += 3;
  }

  c5_i43 = 0;
  for (c5_i44 = 0; c5_i44 < 3; c5_i44++) {
    for (c5_i45 = 0; c5_i45 < 3; c5_i45++) {
      c5_u[c5_i45 + c5_i43] = c5_b_inData[c5_i45 + c5_i43];
    }

    c5_i43 += 3;
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_d_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[9])
{
  real_T c5_dv3[9];
  int32_T c5_i46;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv3, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c5_i46 = 0; c5_i46 < 9; c5_i46++) {
    c5_y[c5_i46] = c5_dv3[c5_i46];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_R2;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[9];
  int32_T c5_i47;
  int32_T c5_i48;
  int32_T c5_i49;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_R2 = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_R2), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_R2);
  c5_i47 = 0;
  for (c5_i48 = 0; c5_i48 < 3; c5_i48++) {
    for (c5_i49 = 0; c5_i49 < 3; c5_i49++) {
      (*(real_T (*)[9])c5_outData)[c5_i49 + c5_i47] = c5_y[c5_i49 + c5_i47];
    }

    c5_i47 += 3;
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i50;
  int32_T c5_i51;
  int32_T c5_i52;
  real_T c5_b_inData[16];
  int32_T c5_i53;
  int32_T c5_i54;
  int32_T c5_i55;
  real_T c5_u[16];
  const mxArray *c5_y = NULL;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_i50 = 0;
  for (c5_i51 = 0; c5_i51 < 4; c5_i51++) {
    for (c5_i52 = 0; c5_i52 < 4; c5_i52++) {
      c5_b_inData[c5_i52 + c5_i50] = (*(real_T (*)[16])c5_inData)[c5_i52 +
        c5_i50];
    }

    c5_i50 += 4;
  }

  c5_i53 = 0;
  for (c5_i54 = 0; c5_i54 < 4; c5_i54++) {
    for (c5_i55 = 0; c5_i55 < 4; c5_i55++) {
      c5_u[c5_i55 + c5_i53] = c5_b_inData[c5_i55 + c5_i53];
    }

    c5_i53 += 4;
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 2, 4, 4), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_e_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[16])
{
  real_T c5_dv4[16];
  int32_T c5_i56;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv4, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c5_i56 = 0; c5_i56 < 16; c5_i56++) {
    c5_y[c5_i56] = c5_dv4[c5_i56];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_M;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[16];
  int32_T c5_i57;
  int32_T c5_i58;
  int32_T c5_i59;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_M = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_M), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_M);
  c5_i57 = 0;
  for (c5_i58 = 0; c5_i58 < 4; c5_i58++) {
    for (c5_i59 = 0; c5_i59 < 4; c5_i59++) {
      (*(real_T (*)[16])c5_outData)[c5_i59 + c5_i57] = c5_y[c5_i59 + c5_i57];
    }

    c5_i57 += 4;
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i60;
  real_T c5_b_inData[4];
  int32_T c5_i61;
  real_T c5_u[4];
  const mxArray *c5_y = NULL;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i60 = 0; c5_i60 < 4; c5_i60++) {
    c5_b_inData[c5_i60] = (*(real_T (*)[4])c5_inData)[c5_i60];
  }

  for (c5_i61 = 0; c5_i61 < 4; c5_i61++) {
    c5_u[c5_i61] = c5_b_inData[c5_i61];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_f_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[4])
{
  real_T c5_dv5[4];
  int32_T c5_i62;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv5, 1, 0, 0U, 1, 0U, 1, 4);
  for (c5_i62 = 0; c5_i62 < 4; c5_i62++) {
    c5_y[c5_i62] = c5_dv5[c5_i62];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_nu;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[4];
  int32_T c5_i63;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_nu = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nu), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_nu);
  for (c5_i63 = 0; c5_i63 < 4; c5_i63++) {
    (*(real_T (*)[4])c5_outData)[c5_i63] = c5_y[c5_i63];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static void c5_g_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  real_T c5_y[11])
{
  real_T c5_dv6[11];
  int32_T c5_i64;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv6, 1, 0, 0U, 1, 0U, 1, 11);
  for (c5_i64 = 0; c5_i64 < 11; c5_i64++) {
    c5_y[c5_i64] = c5_dv6[c5_i64];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_V_in;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[11];
  int32_T c5_i65;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_V_in = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_V_in), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_V_in);
  for (c5_i65 = 0; c5_i65 < 11; c5_i65++) {
    (*(real_T (*)[11])c5_outData)[c5_i65] = c5_y[c5_i65];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_g_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  c5_srLgvkCzuuZn3rWrmrpDanB c5_u;
  const mxArray *c5_y = NULL;
  real_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  real_T c5_c_u;
  const mxArray *c5_c_y = NULL;
  real_T c5_d_u;
  const mxArray *c5_d_y = NULL;
  real_T c5_e_u;
  const mxArray *c5_e_y = NULL;
  real_T c5_f_u;
  const mxArray *c5_f_y = NULL;
  real_T c5_g_u;
  const mxArray *c5_g_y = NULL;
  real_T c5_h_u;
  const mxArray *c5_h_y = NULL;
  real_T c5_i_u;
  const mxArray *c5_i_y = NULL;
  real_T c5_j_u;
  const mxArray *c5_j_y = NULL;
  real_T c5_k_u;
  const mxArray *c5_k_y = NULL;
  real_T c5_l_u;
  const mxArray *c5_l_y = NULL;
  real_T c5_m_u;
  const mxArray *c5_m_y = NULL;
  real_T c5_n_u;
  const mxArray *c5_n_y = NULL;
  real_T c5_o_u;
  const mxArray *c5_o_y = NULL;
  real_T c5_p_u;
  const mxArray *c5_p_y = NULL;
  real_T c5_q_u;
  const mxArray *c5_q_y = NULL;
  real_T c5_r_u;
  const mxArray *c5_r_y = NULL;
  real_T c5_s_u;
  const mxArray *c5_s_y = NULL;
  real_T c5_t_u;
  const mxArray *c5_t_y = NULL;
  real_T c5_u_u;
  const mxArray *c5_u_y = NULL;
  real_T c5_v_u;
  const mxArray *c5_v_y = NULL;
  real_T c5_w_u;
  const mxArray *c5_w_y = NULL;
  real_T c5_x_u;
  const mxArray *c5_x_y = NULL;
  real_T c5_y_u;
  const mxArray *c5_y_y = NULL;
  real_T c5_ab_u;
  const mxArray *c5_ab_y = NULL;
  real_T c5_bb_u;
  const mxArray *c5_bb_y = NULL;
  real_T c5_cb_u;
  const mxArray *c5_cb_y = NULL;
  real_T c5_db_u;
  const mxArray *c5_db_y = NULL;
  real_T c5_eb_u;
  const mxArray *c5_eb_y = NULL;
  real_T c5_fb_u;
  const mxArray *c5_fb_y = NULL;
  real_T c5_gb_u;
  const mxArray *c5_gb_y = NULL;
  real_T c5_hb_u;
  const mxArray *c5_hb_y = NULL;
  real_T c5_ib_u;
  const mxArray *c5_ib_y = NULL;
  real_T c5_jb_u;
  const mxArray *c5_jb_y = NULL;
  real_T c5_kb_u;
  const mxArray *c5_kb_y = NULL;
  real_T c5_lb_u;
  const mxArray *c5_lb_y = NULL;
  real_T c5_mb_u;
  const mxArray *c5_mb_y = NULL;
  real_T c5_nb_u;
  const mxArray *c5_nb_y = NULL;
  real_T c5_ob_u;
  const mxArray *c5_ob_y = NULL;
  real_T c5_pb_u;
  const mxArray *c5_pb_y = NULL;
  real_T c5_qb_u;
  const mxArray *c5_qb_y = NULL;
  real_T c5_rb_u;
  const mxArray *c5_rb_y = NULL;
  real_T c5_sb_u;
  const mxArray *c5_sb_y = NULL;
  real_T c5_tb_u;
  const mxArray *c5_tb_y = NULL;
  real_T c5_ub_u;
  const mxArray *c5_ub_y = NULL;
  real_T c5_vb_u;
  const mxArray *c5_vb_y = NULL;
  real_T c5_wb_u;
  const mxArray *c5_wb_y = NULL;
  real_T c5_xb_u;
  const mxArray *c5_xb_y = NULL;
  real_T c5_yb_u;
  const mxArray *c5_yb_y = NULL;
  real_T c5_ac_u;
  const mxArray *c5_ac_y = NULL;
  real_T c5_bc_u;
  const mxArray *c5_bc_y = NULL;
  real_T c5_cc_u;
  const mxArray *c5_cc_y = NULL;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(c5_srLgvkCzuuZn3rWrmrpDanB *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c5_b_u = c5_u.m;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_b_y, "m", "m", 0);
  c5_c_u = c5_u.Ixx;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_c_y, "Ixx", "Ixx", 0);
  c5_d_u = c5_u.Izz;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_d_y, "Izz", "Izz", 0);
  c5_e_u = c5_u.Ixz;
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_e_y, "Ixz", "Ixz", 0);
  c5_f_u = c5_u.a11;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_f_y, "a11", "a11", 0);
  c5_g_u = c5_u.a22;
  c5_g_y = NULL;
  sf_mex_assign(&c5_g_y, sf_mex_create("y", &c5_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_g_y, "a22", "a22", 0);
  c5_h_u = c5_u.a44;
  c5_h_y = NULL;
  sf_mex_assign(&c5_h_y, sf_mex_create("y", &c5_h_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_h_y, "a44", "a44", 0);
  c5_i_u = c5_u.a66;
  c5_i_y = NULL;
  sf_mex_assign(&c5_i_y, sf_mex_create("y", &c5_i_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_i_y, "a66", "a66", 0);
  c5_j_u = c5_u.a24;
  c5_j_y = NULL;
  sf_mex_assign(&c5_j_y, sf_mex_create("y", &c5_j_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_j_y, "a24", "a24", 0);
  c5_k_u = c5_u.a26;
  c5_k_y = NULL;
  sf_mex_assign(&c5_k_y, sf_mex_create("y", &c5_k_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_k_y, "a26", "a26", 0);
  c5_l_u = c5_u.a46;
  c5_l_y = NULL;
  sf_mex_assign(&c5_l_y, sf_mex_create("y", &c5_l_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_l_y, "a46", "a46", 0);
  c5_m_u = c5_u.vt;
  c5_m_y = NULL;
  sf_mex_assign(&c5_m_y, sf_mex_create("y", &c5_m_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_m_y, "vt", "vt", 0);
  c5_n_u = c5_u.alpha_w;
  c5_n_y = NULL;
  sf_mex_assign(&c5_n_y, sf_mex_create("y", &c5_n_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_n_y, "alpha_w", "alpha_w", 0);
  c5_o_u = c5_u.rho_a;
  c5_o_y = NULL;
  sf_mex_assign(&c5_o_y, sf_mex_create("y", &c5_o_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_o_y, "rho_a", "rho_a", 0);
  c5_p_u = c5_u.As;
  c5_p_y = NULL;
  sf_mex_assign(&c5_p_y, sf_mex_create("y", &c5_p_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_p_y, "As", "As", 0);
  c5_q_u = c5_u.h0;
  c5_q_y = NULL;
  sf_mex_assign(&c5_q_y, sf_mex_create("y", &c5_q_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_q_y, "h0", "h0", 0);
  c5_r_u = c5_u.h1;
  c5_r_y = NULL;
  sf_mex_assign(&c5_r_y, sf_mex_create("y", &c5_r_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_r_y, "h1", "h1", 0);
  c5_s_u = c5_u.z_s;
  c5_s_y = NULL;
  sf_mex_assign(&c5_s_y, sf_mex_create("y", &c5_s_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_s_y, "z_s", "z_s", 0);
  c5_t_u = c5_u.xs;
  c5_t_y = NULL;
  sf_mex_assign(&c5_t_y, sf_mex_create("y", &c5_t_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_t_y, "xs", "xs", 0);
  c5_u_u = c5_u.ys;
  c5_u_y = NULL;
  sf_mex_assign(&c5_u_y, sf_mex_create("y", &c5_u_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_u_y, "ys", "ys", 0);
  c5_v_u = c5_u.zs;
  c5_v_y = NULL;
  sf_mex_assign(&c5_v_y, sf_mex_create("y", &c5_v_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_v_y, "zs", "zs", 0);
  c5_w_u = c5_u.Xce;
  c5_w_y = NULL;
  sf_mex_assign(&c5_w_y, sf_mex_create("y", &c5_w_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_w_y, "Xce", "Xce", 0);
  c5_x_u = c5_u.Xm;
  c5_x_y = NULL;
  sf_mex_assign(&c5_x_y, sf_mex_create("y", &c5_x_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_x_y, "Xm", "Xm", 0);
  c5_y_u = c5_u.rho_w;
  c5_y_y = NULL;
  sf_mex_assign(&c5_y_y, sf_mex_create("y", &c5_y_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_y_y, "rho_w", "rho_w", 0);
  c5_ab_u = c5_u.Ar;
  c5_ab_y = NULL;
  sf_mex_assign(&c5_ab_y, sf_mex_create("y", &c5_ab_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_ab_y, "Ar", "Ar", 0);
  c5_bb_u = c5_u.d_r;
  c5_bb_y = NULL;
  sf_mex_assign(&c5_bb_y, sf_mex_create("y", &c5_bb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_bb_y, "d_r", "d_r", 0);
  c5_cb_u = c5_u.zeta_r;
  c5_cb_y = NULL;
  sf_mex_assign(&c5_cb_y, sf_mex_create("y", &c5_cb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_cb_y, "zeta_r", "zeta_r", 0);
  c5_db_u = c5_u.x_r;
  c5_db_y = NULL;
  sf_mex_assign(&c5_db_y, sf_mex_create("y", &c5_db_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_db_y, "x_r", "x_r", 0);
  c5_eb_u = c5_u.z_r;
  c5_eb_y = NULL;
  sf_mex_assign(&c5_eb_y, sf_mex_create("y", &c5_eb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_eb_y, "z_r", "z_r", 0);
  c5_fb_u = c5_u.xr;
  c5_fb_y = NULL;
  sf_mex_assign(&c5_fb_y, sf_mex_create("y", &c5_fb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_fb_y, "xr", "xr", 0);
  c5_gb_u = c5_u.yr;
  c5_gb_y = NULL;
  sf_mex_assign(&c5_gb_y, sf_mex_create("y", &c5_gb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_gb_y, "yr", "yr", 0);
  c5_hb_u = c5_u.zr;
  c5_hb_y = NULL;
  sf_mex_assign(&c5_hb_y, sf_mex_create("y", &c5_hb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_hb_y, "zr", "zr", 0);
  c5_ib_u = c5_u.Ak;
  c5_ib_y = NULL;
  sf_mex_assign(&c5_ib_y, sf_mex_create("y", &c5_ib_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_ib_y, "Ak", "Ak", 0);
  c5_jb_u = c5_u.d_k;
  c5_jb_y = NULL;
  sf_mex_assign(&c5_jb_y, sf_mex_create("y", &c5_jb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_jb_y, "d_k", "d_k", 0);
  c5_kb_u = c5_u.zeta_k;
  c5_kb_y = NULL;
  sf_mex_assign(&c5_kb_y, sf_mex_create("y", &c5_kb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_kb_y, "zeta_k", "zeta_k", 0);
  c5_lb_u = c5_u.x_k;
  c5_lb_y = NULL;
  sf_mex_assign(&c5_lb_y, sf_mex_create("y", &c5_lb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_lb_y, "x_k", "x_k", 0);
  c5_mb_u = c5_u.z_k;
  c5_mb_y = NULL;
  sf_mex_assign(&c5_mb_y, sf_mex_create("y", &c5_mb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_mb_y, "z_k", "z_k", 0);
  c5_nb_u = c5_u.xk;
  c5_nb_y = NULL;
  sf_mex_assign(&c5_nb_y, sf_mex_create("y", &c5_nb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_nb_y, "xk", "xk", 0);
  c5_ob_u = c5_u.yk;
  c5_ob_y = NULL;
  sf_mex_assign(&c5_ob_y, sf_mex_create("y", &c5_ob_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_ob_y, "yk", "yk", 0);
  c5_pb_u = c5_u.zk;
  c5_pb_y = NULL;
  sf_mex_assign(&c5_pb_y, sf_mex_create("y", &c5_pb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_pb_y, "zk", "zk", 0);
  c5_qb_u = c5_u.x_h;
  c5_qb_y = NULL;
  sf_mex_assign(&c5_qb_y, sf_mex_create("y", &c5_qb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_qb_y, "x_h", "x_h", 0);
  c5_rb_u = c5_u.z_h;
  c5_rb_y = NULL;
  sf_mex_assign(&c5_rb_y, sf_mex_create("y", &c5_rb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_rb_y, "z_h", "z_h", 0);
  c5_sb_u = c5_u.xh;
  c5_sb_y = NULL;
  sf_mex_assign(&c5_sb_y, sf_mex_create("y", &c5_sb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_sb_y, "xh", "xh", 0);
  c5_tb_u = c5_u.yh;
  c5_tb_y = NULL;
  sf_mex_assign(&c5_tb_y, sf_mex_create("y", &c5_tb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_tb_y, "yh", "yh", 0);
  c5_ub_u = c5_u.zh;
  c5_ub_y = NULL;
  sf_mex_assign(&c5_ub_y, sf_mex_create("y", &c5_ub_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_ub_y, "zh", "zh", 0);
  c5_vb_u = c5_u.w_c;
  c5_vb_y = NULL;
  sf_mex_assign(&c5_vb_y, sf_mex_create("y", &c5_vb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_vb_y, "w_c", "w_c", 0);
  c5_wb_u = c5_u.x_c;
  c5_wb_y = NULL;
  sf_mex_assign(&c5_wb_y, sf_mex_create("y", &c5_wb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_wb_y, "x_c", "x_c", 0);
  c5_xb_u = c5_u.y_bm;
  c5_xb_y = NULL;
  sf_mex_assign(&c5_xb_y, sf_mex_create("y", &c5_xb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_xb_y, "y_bm", "y_bm", 0);
  c5_yb_u = c5_u.a;
  c5_yb_y = NULL;
  sf_mex_assign(&c5_yb_y, sf_mex_create("y", &c5_yb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_yb_y, "a", "a", 0);
  c5_ac_u = c5_u.b;
  c5_ac_y = NULL;
  sf_mex_assign(&c5_ac_y, sf_mex_create("y", &c5_ac_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_ac_y, "b", "b", 0);
  c5_bc_u = c5_u.c;
  c5_bc_y = NULL;
  sf_mex_assign(&c5_bc_y, sf_mex_create("y", &c5_bc_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_bc_y, "c", "c", 0);
  c5_cc_u = c5_u.d;
  c5_cc_y = NULL;
  sf_mex_assign(&c5_cc_y, sf_mex_create("y", &c5_cc_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_cc_y, "d", "d", 0);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_h_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  c5_srLgvkCzuuZn3rWrmrpDanB *c5_y)
{
  emlrtMsgIdentifier c5_thisId;
  static const char * c5_fieldNames[52] = { "m", "Ixx", "Izz", "Ixz", "a11",
    "a22", "a44", "a66", "a24", "a26", "a46", "vt", "alpha_w", "rho_a", "As",
    "h0", "h1", "z_s", "xs", "ys", "zs", "Xce", "Xm", "rho_w", "Ar", "d_r",
    "zeta_r", "x_r", "z_r", "xr", "yr", "zr", "Ak", "d_k", "zeta_k", "x_k",
    "z_k", "xk", "yk", "zk", "x_h", "z_h", "xh", "yh", "zh", "w_c", "x_c",
    "y_bm", "a", "b", "c", "d" };

  c5_thisId.fParent = c5_parentId;
  sf_mex_check_struct(c5_parentId, c5_u, 52, c5_fieldNames, 0U, NULL);
  c5_thisId.fIdentifier = "m";
  c5_y->m = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c5_u,
    "m", "m", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "Ixx";
  c5_y->Ixx = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "Ixx", "Ixx", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "Izz";
  c5_y->Izz = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "Izz", "Izz", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "Ixz";
  c5_y->Ixz = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "Ixz", "Ixz", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "a11";
  c5_y->a11 = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "a11", "a11", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "a22";
  c5_y->a22 = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "a22", "a22", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "a44";
  c5_y->a44 = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "a44", "a44", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "a66";
  c5_y->a66 = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "a66", "a66", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "a24";
  c5_y->a24 = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "a24", "a24", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "a26";
  c5_y->a26 = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "a26", "a26", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "a46";
  c5_y->a46 = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "a46", "a46", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "vt";
  c5_y->vt = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "vt", "vt", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "alpha_w";
  c5_y->alpha_w = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "alpha_w", "alpha_w", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "rho_a";
  c5_y->rho_a = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "rho_a", "rho_a", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "As";
  c5_y->As = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "As", "As", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "h0";
  c5_y->h0 = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "h0", "h0", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "h1";
  c5_y->h1 = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "h1", "h1", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "z_s";
  c5_y->z_s = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "z_s", "z_s", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "xs";
  c5_y->xs = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "xs", "xs", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "ys";
  c5_y->ys = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "ys", "ys", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "zs";
  c5_y->zs = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "zs", "zs", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "Xce";
  c5_y->Xce = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "Xce", "Xce", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "Xm";
  c5_y->Xm = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "Xm", "Xm", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "rho_w";
  c5_y->rho_w = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "rho_w", "rho_w", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "Ar";
  c5_y->Ar = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "Ar", "Ar", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "d_r";
  c5_y->d_r = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "d_r", "d_r", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "zeta_r";
  c5_y->zeta_r = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
                                        (c5_u, "zeta_r", "zeta_r", 0)),
    &c5_thisId);
  c5_thisId.fIdentifier = "x_r";
  c5_y->x_r = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "x_r", "x_r", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "z_r";
  c5_y->z_r = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "z_r", "z_r", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "xr";
  c5_y->xr = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "xr", "xr", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "yr";
  c5_y->yr = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "yr", "yr", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "zr";
  c5_y->zr = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "zr", "zr", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "Ak";
  c5_y->Ak = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "Ak", "Ak", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "d_k";
  c5_y->d_k = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "d_k", "d_k", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "zeta_k";
  c5_y->zeta_k = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
                                        (c5_u, "zeta_k", "zeta_k", 0)),
    &c5_thisId);
  c5_thisId.fIdentifier = "x_k";
  c5_y->x_k = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "x_k", "x_k", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "z_k";
  c5_y->z_k = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "z_k", "z_k", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "xk";
  c5_y->xk = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "xk", "xk", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "yk";
  c5_y->yk = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "yk", "yk", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "zk";
  c5_y->zk = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "zk", "zk", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "x_h";
  c5_y->x_h = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "x_h", "x_h", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "z_h";
  c5_y->z_h = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "z_h", "z_h", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "xh";
  c5_y->xh = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "xh", "xh", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "yh";
  c5_y->yh = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "yh", "yh", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "zh";
  c5_y->zh = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "zh", "zh", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "w_c";
  c5_y->w_c = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "w_c", "w_c", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "x_c";
  c5_y->x_c = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "x_c", "x_c", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "y_bm";
  c5_y->y_bm = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "y_bm", "y_bm", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "a";
  c5_y->a = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c5_u,
    "a", "a", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "b";
  c5_y->b = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c5_u,
    "b", "b", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "c";
  c5_y->c = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c5_u,
    "c", "c", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "d";
  c5_y->d = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c5_u,
    "d", "d", 0)), &c5_thisId);
  sf_mex_destroy(&c5_u);
}

static void c5_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_par;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  c5_srLgvkCzuuZn3rWrmrpDanB c5_y;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_par = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_par), &c5_thisId, &c5_y);
  sf_mex_destroy(&c5_par);
  *(c5_srLgvkCzuuZn3rWrmrpDanB *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_SailingYachtModel2_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_createstruct("structure", 2, 55, 1),
                false);
  c5_info_helper(&c5_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c5_nameCaptureInfo);
  return c5_nameCaptureInfo;
}

static void c5_info_helper(const mxArray **c5_info)
{
  const mxArray *c5_rhs0 = NULL;
  const mxArray *c5_lhs0 = NULL;
  const mxArray *c5_rhs1 = NULL;
  const mxArray *c5_lhs1 = NULL;
  const mxArray *c5_rhs2 = NULL;
  const mxArray *c5_lhs2 = NULL;
  const mxArray *c5_rhs3 = NULL;
  const mxArray *c5_lhs3 = NULL;
  const mxArray *c5_rhs4 = NULL;
  const mxArray *c5_lhs4 = NULL;
  const mxArray *c5_rhs5 = NULL;
  const mxArray *c5_lhs5 = NULL;
  const mxArray *c5_rhs6 = NULL;
  const mxArray *c5_lhs6 = NULL;
  const mxArray *c5_rhs7 = NULL;
  const mxArray *c5_lhs7 = NULL;
  const mxArray *c5_rhs8 = NULL;
  const mxArray *c5_lhs8 = NULL;
  const mxArray *c5_rhs9 = NULL;
  const mxArray *c5_lhs9 = NULL;
  const mxArray *c5_rhs10 = NULL;
  const mxArray *c5_lhs10 = NULL;
  const mxArray *c5_rhs11 = NULL;
  const mxArray *c5_lhs11 = NULL;
  const mxArray *c5_rhs12 = NULL;
  const mxArray *c5_lhs12 = NULL;
  const mxArray *c5_rhs13 = NULL;
  const mxArray *c5_lhs13 = NULL;
  const mxArray *c5_rhs14 = NULL;
  const mxArray *c5_lhs14 = NULL;
  const mxArray *c5_rhs15 = NULL;
  const mxArray *c5_lhs15 = NULL;
  const mxArray *c5_rhs16 = NULL;
  const mxArray *c5_lhs16 = NULL;
  const mxArray *c5_rhs17 = NULL;
  const mxArray *c5_lhs17 = NULL;
  const mxArray *c5_rhs18 = NULL;
  const mxArray *c5_lhs18 = NULL;
  const mxArray *c5_rhs19 = NULL;
  const mxArray *c5_lhs19 = NULL;
  const mxArray *c5_rhs20 = NULL;
  const mxArray *c5_lhs20 = NULL;
  const mxArray *c5_rhs21 = NULL;
  const mxArray *c5_lhs21 = NULL;
  const mxArray *c5_rhs22 = NULL;
  const mxArray *c5_lhs22 = NULL;
  const mxArray *c5_rhs23 = NULL;
  const mxArray *c5_lhs23 = NULL;
  const mxArray *c5_rhs24 = NULL;
  const mxArray *c5_lhs24 = NULL;
  const mxArray *c5_rhs25 = NULL;
  const mxArray *c5_lhs25 = NULL;
  const mxArray *c5_rhs26 = NULL;
  const mxArray *c5_lhs26 = NULL;
  const mxArray *c5_rhs27 = NULL;
  const mxArray *c5_lhs27 = NULL;
  const mxArray *c5_rhs28 = NULL;
  const mxArray *c5_lhs28 = NULL;
  const mxArray *c5_rhs29 = NULL;
  const mxArray *c5_lhs29 = NULL;
  const mxArray *c5_rhs30 = NULL;
  const mxArray *c5_lhs30 = NULL;
  const mxArray *c5_rhs31 = NULL;
  const mxArray *c5_lhs31 = NULL;
  const mxArray *c5_rhs32 = NULL;
  const mxArray *c5_lhs32 = NULL;
  const mxArray *c5_rhs33 = NULL;
  const mxArray *c5_lhs33 = NULL;
  const mxArray *c5_rhs34 = NULL;
  const mxArray *c5_lhs34 = NULL;
  const mxArray *c5_rhs35 = NULL;
  const mxArray *c5_lhs35 = NULL;
  const mxArray *c5_rhs36 = NULL;
  const mxArray *c5_lhs36 = NULL;
  const mxArray *c5_rhs37 = NULL;
  const mxArray *c5_lhs37 = NULL;
  const mxArray *c5_rhs38 = NULL;
  const mxArray *c5_lhs38 = NULL;
  const mxArray *c5_rhs39 = NULL;
  const mxArray *c5_lhs39 = NULL;
  const mxArray *c5_rhs40 = NULL;
  const mxArray *c5_lhs40 = NULL;
  const mxArray *c5_rhs41 = NULL;
  const mxArray *c5_lhs41 = NULL;
  const mxArray *c5_rhs42 = NULL;
  const mxArray *c5_lhs42 = NULL;
  const mxArray *c5_rhs43 = NULL;
  const mxArray *c5_lhs43 = NULL;
  const mxArray *c5_rhs44 = NULL;
  const mxArray *c5_lhs44 = NULL;
  const mxArray *c5_rhs45 = NULL;
  const mxArray *c5_lhs45 = NULL;
  const mxArray *c5_rhs46 = NULL;
  const mxArray *c5_lhs46 = NULL;
  const mxArray *c5_rhs47 = NULL;
  const mxArray *c5_lhs47 = NULL;
  const mxArray *c5_rhs48 = NULL;
  const mxArray *c5_lhs48 = NULL;
  const mxArray *c5_rhs49 = NULL;
  const mxArray *c5_lhs49 = NULL;
  const mxArray *c5_rhs50 = NULL;
  const mxArray *c5_lhs50 = NULL;
  const mxArray *c5_rhs51 = NULL;
  const mxArray *c5_lhs51 = NULL;
  const mxArray *c5_rhs52 = NULL;
  const mxArray *c5_lhs52 = NULL;
  const mxArray *c5_rhs53 = NULL;
  const mxArray *c5_lhs53 = NULL;
  const mxArray *c5_rhs54 = NULL;
  const mxArray *c5_lhs54 = NULL;
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("modeleBoat"), "name", "name",
                  0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[E]/home/paul/KTH/Optimal Control/BottleBoat/Simulink/modeleBoat.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1430582785U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c5_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("cos"), "name", "name", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c5_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_cos"), "name",
                  "name", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286818722U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c5_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("sin"), "name", "name", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c5_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286818736U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c5_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("abs"), "name", "name", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c5_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c5_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286818712U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c5_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("mrdivide"), "name", "name", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c5_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c5_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("rdivide"), "name", "name", 10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c5_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c5_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c5_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_div"), "name", "name", 13);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c5_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 14);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 14);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c5_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 15);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("log"), "name", "name", 15);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log.m"), "resolved",
                  "resolved", 15);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1343830380U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c5_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log.m"), "context",
                  "context", 16);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_error"), "name", "name",
                  16);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1343830358U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c5_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log.m"), "context",
                  "context", 17);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_log"), "name",
                  "name", 17);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286818728U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c5_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log.m"),
                  "context", "context", 18);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("realmax"), "name", "name", 18);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m"), "resolved",
                  "resolved", 18);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1307651242U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c5_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_realmax"), "name", "name",
                  19);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c5_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 20);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c5_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log.m"),
                  "context", "context", 21);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("mrdivide"), "name", "name", 21);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 21);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c5_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 22);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 22);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c5_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 23);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 23);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c5_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 24);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 24);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c5_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 25);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 25);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 25);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c5_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 26);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 26);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c5_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 27);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  27);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c5_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 28);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 28);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c5_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 29);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 29);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c5_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 30);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 30);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c5_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 31);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 31);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c5_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 32);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 32);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c5_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 33);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 33);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c5_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 34);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.refblas.xgemm"),
                  "name", "name", 34);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c5_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 35);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("cross"), "name", "name", 35);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m"), "resolved",
                  "resolved", 35);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286818842U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c5_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 36);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("atan2"), "name", "name", 36);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "resolved",
                  "resolved", 36);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c5_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 37);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 37);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 37);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c5_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 38);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 38);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 38);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c5_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 39);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 39);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c5_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 40);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_atan2"), "name",
                  "name", 40);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m"),
                  "resolved", "resolved", 40);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286818720U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c5_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 41);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("mpower"), "name", "name", 41);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 41);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363713878U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c5_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 42);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 42);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 42);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c5_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 43);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("ismatrix"), "name", "name", 43);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 43);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1331304858U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c5_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 44);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("power"), "name", "name", 44);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 44);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c5_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 45);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 45);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c5_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 46);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 46);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 46);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 46);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c5_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 47);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 47);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 47);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c5_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 48);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("floor"), "name", "name", 48);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 48);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 48);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c5_rhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 49);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 49);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 49);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 49);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c5_rhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 50);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 50);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 50);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 50);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c5_rhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 51);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 51);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 51);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 51);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c5_rhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 52);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("sqrt"), "name", "name", 52);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 52);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "resolved",
                  "resolved", 52);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c5_rhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 53);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_error"), "name", "name",
                  53);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 53);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 53);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1343830358U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c5_rhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 54);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalar_sqrt"), "name",
                  "name", 54);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 54);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m"),
                  "resolved", "resolved", 54);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286818738U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c5_rhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs54), "lhs", "lhs",
                  54);
  sf_mex_destroy(&c5_rhs0);
  sf_mex_destroy(&c5_lhs0);
  sf_mex_destroy(&c5_rhs1);
  sf_mex_destroy(&c5_lhs1);
  sf_mex_destroy(&c5_rhs2);
  sf_mex_destroy(&c5_lhs2);
  sf_mex_destroy(&c5_rhs3);
  sf_mex_destroy(&c5_lhs3);
  sf_mex_destroy(&c5_rhs4);
  sf_mex_destroy(&c5_lhs4);
  sf_mex_destroy(&c5_rhs5);
  sf_mex_destroy(&c5_lhs5);
  sf_mex_destroy(&c5_rhs6);
  sf_mex_destroy(&c5_lhs6);
  sf_mex_destroy(&c5_rhs7);
  sf_mex_destroy(&c5_lhs7);
  sf_mex_destroy(&c5_rhs8);
  sf_mex_destroy(&c5_lhs8);
  sf_mex_destroy(&c5_rhs9);
  sf_mex_destroy(&c5_lhs9);
  sf_mex_destroy(&c5_rhs10);
  sf_mex_destroy(&c5_lhs10);
  sf_mex_destroy(&c5_rhs11);
  sf_mex_destroy(&c5_lhs11);
  sf_mex_destroy(&c5_rhs12);
  sf_mex_destroy(&c5_lhs12);
  sf_mex_destroy(&c5_rhs13);
  sf_mex_destroy(&c5_lhs13);
  sf_mex_destroy(&c5_rhs14);
  sf_mex_destroy(&c5_lhs14);
  sf_mex_destroy(&c5_rhs15);
  sf_mex_destroy(&c5_lhs15);
  sf_mex_destroy(&c5_rhs16);
  sf_mex_destroy(&c5_lhs16);
  sf_mex_destroy(&c5_rhs17);
  sf_mex_destroy(&c5_lhs17);
  sf_mex_destroy(&c5_rhs18);
  sf_mex_destroy(&c5_lhs18);
  sf_mex_destroy(&c5_rhs19);
  sf_mex_destroy(&c5_lhs19);
  sf_mex_destroy(&c5_rhs20);
  sf_mex_destroy(&c5_lhs20);
  sf_mex_destroy(&c5_rhs21);
  sf_mex_destroy(&c5_lhs21);
  sf_mex_destroy(&c5_rhs22);
  sf_mex_destroy(&c5_lhs22);
  sf_mex_destroy(&c5_rhs23);
  sf_mex_destroy(&c5_lhs23);
  sf_mex_destroy(&c5_rhs24);
  sf_mex_destroy(&c5_lhs24);
  sf_mex_destroy(&c5_rhs25);
  sf_mex_destroy(&c5_lhs25);
  sf_mex_destroy(&c5_rhs26);
  sf_mex_destroy(&c5_lhs26);
  sf_mex_destroy(&c5_rhs27);
  sf_mex_destroy(&c5_lhs27);
  sf_mex_destroy(&c5_rhs28);
  sf_mex_destroy(&c5_lhs28);
  sf_mex_destroy(&c5_rhs29);
  sf_mex_destroy(&c5_lhs29);
  sf_mex_destroy(&c5_rhs30);
  sf_mex_destroy(&c5_lhs30);
  sf_mex_destroy(&c5_rhs31);
  sf_mex_destroy(&c5_lhs31);
  sf_mex_destroy(&c5_rhs32);
  sf_mex_destroy(&c5_lhs32);
  sf_mex_destroy(&c5_rhs33);
  sf_mex_destroy(&c5_lhs33);
  sf_mex_destroy(&c5_rhs34);
  sf_mex_destroy(&c5_lhs34);
  sf_mex_destroy(&c5_rhs35);
  sf_mex_destroy(&c5_lhs35);
  sf_mex_destroy(&c5_rhs36);
  sf_mex_destroy(&c5_lhs36);
  sf_mex_destroy(&c5_rhs37);
  sf_mex_destroy(&c5_lhs37);
  sf_mex_destroy(&c5_rhs38);
  sf_mex_destroy(&c5_lhs38);
  sf_mex_destroy(&c5_rhs39);
  sf_mex_destroy(&c5_lhs39);
  sf_mex_destroy(&c5_rhs40);
  sf_mex_destroy(&c5_lhs40);
  sf_mex_destroy(&c5_rhs41);
  sf_mex_destroy(&c5_lhs41);
  sf_mex_destroy(&c5_rhs42);
  sf_mex_destroy(&c5_lhs42);
  sf_mex_destroy(&c5_rhs43);
  sf_mex_destroy(&c5_lhs43);
  sf_mex_destroy(&c5_rhs44);
  sf_mex_destroy(&c5_lhs44);
  sf_mex_destroy(&c5_rhs45);
  sf_mex_destroy(&c5_lhs45);
  sf_mex_destroy(&c5_rhs46);
  sf_mex_destroy(&c5_lhs46);
  sf_mex_destroy(&c5_rhs47);
  sf_mex_destroy(&c5_lhs47);
  sf_mex_destroy(&c5_rhs48);
  sf_mex_destroy(&c5_lhs48);
  sf_mex_destroy(&c5_rhs49);
  sf_mex_destroy(&c5_lhs49);
  sf_mex_destroy(&c5_rhs50);
  sf_mex_destroy(&c5_lhs50);
  sf_mex_destroy(&c5_rhs51);
  sf_mex_destroy(&c5_lhs51);
  sf_mex_destroy(&c5_rhs52);
  sf_mex_destroy(&c5_lhs52);
  sf_mex_destroy(&c5_rhs53);
  sf_mex_destroy(&c5_lhs53);
  sf_mex_destroy(&c5_rhs54);
  sf_mex_destroy(&c5_lhs54);
}

static const mxArray *c5_emlrt_marshallOut(const char * c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c5_u)), false);
  return c5_y;
}

static const mxArray *c5_b_emlrt_marshallOut(const uint32_T c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 7, 0U, 0U, 0U, 0), false);
  return c5_y;
}

static real_T c5_log(SFc5_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T c5_x)
{
  real_T c5_b_x;
  c5_b_x = c5_x;
  c5_b_log(chartInstance, &c5_b_x);
  return c5_b_x;
}

static void c5_eml_error(SFc5_SailingYachtModel2InstanceStruct *chartInstance)
{
  int32_T c5_i66;
  static char_T c5_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c5_u[30];
  const mxArray *c5_y = NULL;
  int32_T c5_i67;
  static char_T c5_cv1[3] = { 'l', 'o', 'g' };

  char_T c5_b_u[3];
  const mxArray *c5_b_y = NULL;
  (void)chartInstance;
  for (c5_i66 = 0; c5_i66 < 30; c5_i66++) {
    c5_u[c5_i66] = c5_cv0[c5_i66];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 10, 0U, 1U, 0U, 2, 1, 30), false);
  for (c5_i67 = 0; c5_i67 < 3; c5_i67++) {
    c5_b_u[c5_i67] = c5_cv1[c5_i67];
  }

  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_b_u, 10, 0U, 1U, 0U, 2, 1, 3),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c5_y, 14, c5_b_y));
}

static void c5_eml_scalar_eg(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c5_threshold(SFc5_SailingYachtModel2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c5_b_eml_scalar_eg(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static real_T c5_atan2(SFc5_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c5_y, real_T c5_x)
{
  real_T c5_b_y;
  real_T c5_b_x;
  c5_c_eml_scalar_eg(chartInstance);
  c5_b_y = c5_y;
  c5_b_x = c5_x;
  return muDoubleScalarAtan2(c5_b_y, c5_b_x);
}

static void c5_c_eml_scalar_eg(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static real_T c5_mpower(SFc5_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c5_a)
{
  real_T c5_b_a;
  real_T c5_c_a;
  real_T c5_ak;
  real_T c5_d_a;
  c5_b_a = c5_a;
  c5_c_a = c5_b_a;
  c5_c_eml_scalar_eg(chartInstance);
  c5_ak = c5_c_a;
  c5_d_a = c5_ak;
  c5_c_eml_scalar_eg(chartInstance);
  return c5_d_a * c5_d_a;
}

static void c5_b_eml_error(SFc5_SailingYachtModel2InstanceStruct *chartInstance)
{
  int32_T c5_i68;
  static char_T c5_cv2[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c5_u[30];
  const mxArray *c5_y = NULL;
  int32_T c5_i69;
  static char_T c5_cv3[4] = { 's', 'q', 'r', 't' };

  char_T c5_b_u[4];
  const mxArray *c5_b_y = NULL;
  (void)chartInstance;
  for (c5_i68 = 0; c5_i68 < 30; c5_i68++) {
    c5_u[c5_i68] = c5_cv2[c5_i68];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 10, 0U, 1U, 0U, 2, 1, 30), false);
  for (c5_i69 = 0; c5_i69 < 4; c5_i69++) {
    c5_b_u[c5_i69] = c5_cv3[c5_i69];
  }

  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c5_y, 14, c5_b_y));
}

static const mxArray *c5_h_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_i_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i70;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i70, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i70;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static uint8_T c5_j_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_SailingYachtModel2, const
  char_T *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_k_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_is_active_c5_SailingYachtModel2), &c5_thisId);
  sf_mex_destroy(&c5_b_is_active_c5_SailingYachtModel2);
  return c5_y;
}

static uint8_T c5_k_emlrt_marshallIn(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u0, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_log(SFc5_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T *c5_x)
{
  if (*c5_x < 0.0) {
    c5_eml_error(chartInstance);
  }

  *c5_x = muDoubleScalarLog(*c5_x);
}

static void init_dsm_address_info(SFc5_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c5_SailingYachtModel2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3661851310U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3820323901U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2671865623U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2928172688U);
}

mxArray *sf_c5_SailingYachtModel2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("d723Ad8nMruGiQ0x7PmEOH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(11);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c5_SailingYachtModel2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_SailingYachtModel2_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c5_SailingYachtModel2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"alpha\",},{M[8],M[0],T\"is_active_c5_SailingYachtModel2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_SailingYachtModel2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_SailingYachtModel2InstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _SailingYachtModel2MachineNumber_,
           5,
           1,
           1,
           0,
           2,
           0,
           0,
           0,
           0,
           1,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_SailingYachtModel2MachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_SailingYachtModel2MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _SailingYachtModel2MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_SET_DATA_PROPS(1,2,0,1,"alpha");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",618,-1,2342);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"modeleBoat",0,-1,2259);

        {
          unsigned int dimVector[1];
          dimVector[0]= 11;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sf_marshallOut,(MexInFcnForType)c5_sf_marshallIn);

        {
          real_T *c5_alpha;
          real_T (*c5_u)[11];
          c5_alpha = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c5_u = (real_T (*)[11])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c5_u);
          _SFD_SET_DATA_VALUE_PTR(1U, c5_alpha);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _SailingYachtModel2MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "7cprSD6170H43CZpogqnmG";
}

static void sf_opaque_initialize_c5_SailingYachtModel2(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_SailingYachtModel2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c5_SailingYachtModel2((SFc5_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
  initialize_c5_SailingYachtModel2((SFc5_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c5_SailingYachtModel2(void *chartInstanceVar)
{
  enable_c5_SailingYachtModel2((SFc5_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c5_SailingYachtModel2(void *chartInstanceVar)
{
  disable_c5_SailingYachtModel2((SFc5_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c5_SailingYachtModel2(void *chartInstanceVar)
{
  sf_gateway_c5_SailingYachtModel2((SFc5_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c5_SailingYachtModel2(SimStruct*
  S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c5_SailingYachtModel2
    ((SFc5_SailingYachtModel2InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_SailingYachtModel2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c5_SailingYachtModel2(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c5_SailingYachtModel2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c5_SailingYachtModel2((SFc5_SailingYachtModel2InstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c5_SailingYachtModel2(SimStruct* S)
{
  return sf_internal_get_sim_state_c5_SailingYachtModel2(S);
}

static void sf_opaque_set_sim_state_c5_SailingYachtModel2(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c5_SailingYachtModel2(S, st);
}

static void sf_opaque_terminate_c5_SailingYachtModel2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_SailingYachtModel2InstanceStruct*) chartInstanceVar)
      ->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_SailingYachtModel2_optimization_info();
    }

    finalize_c5_SailingYachtModel2((SFc5_SailingYachtModel2InstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_SailingYachtModel2((SFc5_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_SailingYachtModel2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c5_SailingYachtModel2
      ((SFc5_SailingYachtModel2InstanceStruct*)(chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_SailingYachtModel2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_SailingYachtModel2_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,5,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,5,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2153048465U));
  ssSetChecksum1(S,(939133481U));
  ssSetChecksum2(S,(1395353867U));
  ssSetChecksum3(S,(2437189640U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_SailingYachtModel2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_SailingYachtModel2(SimStruct *S)
{
  SFc5_SailingYachtModel2InstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc5_SailingYachtModel2InstanceStruct *)utMalloc(sizeof
    (SFc5_SailingYachtModel2InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_SailingYachtModel2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c5_SailingYachtModel2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c5_SailingYachtModel2;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c5_SailingYachtModel2;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_SailingYachtModel2;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c5_SailingYachtModel2;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c5_SailingYachtModel2;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c5_SailingYachtModel2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c5_SailingYachtModel2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_SailingYachtModel2;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_SailingYachtModel2;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c5_SailingYachtModel2;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c5_SailingYachtModel2_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_SailingYachtModel2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_SailingYachtModel2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_SailingYachtModel2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_SailingYachtModel2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
