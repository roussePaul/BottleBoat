/* Include files */

#include <stddef.h>
#include "blas.h"
#include "SailingYachtModel2_sfun.h"
#include "c2_SailingYachtModel2.h"
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
static const char * c2_debug_family_names[83] = { "par", "V_in", "x", "y", "phi",
  "psi", "v", "p", "r", "nu", "delta_r", "delta_sbar", "y_w", "M_RB", "C_RB",
  "M_A", "C_A", "M", "v_t", "v_tw", "R1", "R2", "v_tb", "V_awb", "V_awu",
  "V_awv", "alpha_aw", "delta_s", "alpha_as", "Cls", "Cds", "Ls", "Ds",
  "tau_sail", "Mzs", "v_aru", "v_arv", "alpha_ar", "alpha_a", "Clr", "Cdr", "Lr",
  "Dr", "tau_rudder", "Mzr", "tau", "v_aku", "v_akv", "alpha_ak", "alpha_e",
  "Clk", "Cdk", "Lk", "Dk", "D_keel", "v_ahu", "v_ahv", "v_ah", "alpha_ah",
  "Frh", "D_hull", "J", "eta_dot", "phi_dot", "psi_dot", "D_heelandyaw", "D",
  "phi_deg", "M_xw", "M_zw", "G", "nu_dot", "u", "nargin", "nargout",
  "sail_coeff1", "sail_coeff2", "rudder_coeff1", "rudder_coeff2", "keel_coeff1",
  "keel_coeff2", "Frh_coeff", "X_dot_ext" };

static const char * c2_b_debug_family_names[3] = { "nargin", "nargout", "par" };

/* Function Declarations */
static void initialize_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void initialize_params_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void enable_c2_SailingYachtModel2(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance);
static void disable_c2_SailingYachtModel2(SFc2_SailingYachtModel2InstanceStruct *
  chartInstance);
static void c2_update_debugger_state_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void set_sim_state_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance, const mxArray *c2_st);
static void finalize_c2_SailingYachtModel2(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance);
static void sf_gateway_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void c2_chartstep_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void initSimStructsc2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_X_dot_ext, const char_T *c2_identifier,
  real_T c2_y[9]);
static void c2_b_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_d_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_e_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_f_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_g_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9]);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_h_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[11]);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_i_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  c2_srLgvkCzuuZn3rWrmrpDanB *c2_y);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(const char * c2_u);
static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u);
static void c2_b_info_helper(const mxArray **c2_info);
static void c2_c_info_helper(const mxArray **c2_info);
static real_T c2_abs(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T c2_x);
static real_T c2_log(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T c2_x);
static void c2_eml_error(SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void c2_eml_scalar_eg(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance);
static void c2_threshold(SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void c2_b_eml_scalar_eg(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance);
static void c2_cross(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T c2_a[3], real_T c2_b[3], real_T c2_c[3]);
static real_T c2_atan2(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_y, real_T c2_x);
static void c2_c_eml_scalar_eg(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance);
static real_T c2_mpower(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_a);
static real_T c2_sqrt(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                      real_T c2_x);
static void c2_b_eml_error(SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void c2_d_eml_scalar_eg(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance);
static void c2_eml_switch_helper(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance);
static void c2_mldivide(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_B[4], real_T c2_Y[4]);
static void c2_eml_matlab_zgetrf(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, real_T c2_A[16], real_T c2_b_A[16], int32_T c2_ipiv[4],
  int32_T *c2_info);
static int32_T c2_eml_ixamax(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[16], int32_T c2_ix0);
static void c2_check_forloop_overflow_error
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance, boolean_T c2_overflow);
static void c2_b_threshold(SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void c2_eml_xgeru(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  int32_T c2_m, int32_T c2_n, real_T c2_alpha1, int32_T c2_ix0, int32_T c2_iy0,
  real_T c2_A[16], int32_T c2_ia0, real_T c2_b_A[16]);
static void c2_eml_xtrsm(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[4], real_T c2_b_B[4]);
static void c2_c_threshold(SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void c2_scalarEg(SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static void c2_b_eml_xtrsm(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[4], real_T c2_b_B[4]);
static void c2_b_mldivide(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[4], real_T c2_Y[4]);
static void c2_eml_warning(SFc2_SailingYachtModel2InstanceStruct *chartInstance);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_j_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_k_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_SailingYachtModel2, const
  char_T *c2_identifier);
static uint8_T c2_l_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_log(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T *c2_x);
static void c2_b_sqrt(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                      real_T *c2_x);
static void c2_b_eml_matlab_zgetrf(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, real_T c2_A[16], int32_T c2_ipiv[4], int32_T *c2_info);
static void c2_b_eml_xgeru(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  int32_T c2_m, int32_T c2_n, real_T c2_alpha1, int32_T c2_ix0, int32_T c2_iy0,
  real_T c2_A[16], int32_T c2_ia0);
static void c2_c_eml_xtrsm(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[4]);
static void c2_d_eml_xtrsm(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[4]);
static void init_dsm_address_info(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_SailingYachtModel2 = 0U;
}

static void initialize_params_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_SailingYachtModel2(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_SailingYachtModel2(SFc2_SailingYachtModel2InstanceStruct *
  chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[9];
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real_T (*c2_X_dot_ext)[9];
  c2_X_dot_ext = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(2, 1), false);
  for (c2_i0 = 0; c2_i0 < 9; c2_i0++) {
    c2_u[c2_i0] = (*c2_X_dot_ext)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 9), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_SailingYachtModel2;
  c2_b_u = c2_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[9];
  int32_T c2_i1;
  real_T (*c2_X_dot_ext)[9];
  c2_X_dot_ext = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                      "X_dot_ext", c2_dv0);
  for (c2_i1 = 0; c2_i1 < 9; c2_i1++) {
    (*c2_X_dot_ext)[c2_i1] = c2_dv0[c2_i1];
  }

  chartInstance->c2_is_active_c2_SailingYachtModel2 = c2_k_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
     "is_active_c2_SailingYachtModel2");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_SailingYachtModel2(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_SailingYachtModel2(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  int32_T c2_i2;
  int32_T c2_i3;
  real_T *c2_sail_coeff1;
  real_T *c2_sail_coeff2;
  real_T *c2_rudder_coeff1;
  real_T *c2_rudder_coeff2;
  real_T *c2_keel_coeff1;
  real_T *c2_keel_coeff2;
  real_T *c2_Frh_coeff;
  real_T (*c2_X_dot_ext)[9];
  real_T (*c2_u)[11];
  c2_Frh_coeff = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
  c2_keel_coeff2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c2_keel_coeff1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c2_rudder_coeff2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c2_rudder_coeff1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c2_sail_coeff2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_sail_coeff1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_X_dot_ext = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_u = (real_T (*)[11])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i2 = 0; c2_i2 < 11; c2_i2++) {
    _SFD_DATA_RANGE_CHECK((*c2_u)[c2_i2], 0U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_SailingYachtModel2(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_SailingYachtModel2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c2_i3 = 0; c2_i3 < 9; c2_i3++) {
    _SFD_DATA_RANGE_CHECK((*c2_X_dot_ext)[c2_i3], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c2_sail_coeff1, 2U);
  _SFD_DATA_RANGE_CHECK(*c2_sail_coeff2, 3U);
  _SFD_DATA_RANGE_CHECK(*c2_rudder_coeff1, 4U);
  _SFD_DATA_RANGE_CHECK(*c2_rudder_coeff2, 5U);
  _SFD_DATA_RANGE_CHECK(*c2_keel_coeff1, 6U);
  _SFD_DATA_RANGE_CHECK(*c2_keel_coeff2, 7U);
  _SFD_DATA_RANGE_CHECK(*c2_Frh_coeff, 8U);
}

static void c2_chartstep_c2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  real_T c2_c_hoistedGlobal;
  real_T c2_d_hoistedGlobal;
  real_T c2_e_hoistedGlobal;
  real_T c2_f_hoistedGlobal;
  real_T c2_g_hoistedGlobal;
  int32_T c2_i4;
  real_T c2_u[11];
  real_T c2_sail_coeff1;
  real_T c2_sail_coeff2;
  real_T c2_rudder_coeff1;
  real_T c2_rudder_coeff2;
  real_T c2_keel_coeff1;
  real_T c2_keel_coeff2;
  real_T c2_Frh_coeff;
  uint32_T c2_debug_family_var_map[83];
  c2_srLgvkCzuuZn3rWrmrpDanB c2_par;
  real_T c2_V_in[11];
  real_T c2_x;
  real_T c2_y;
  real_T c2_phi;
  real_T c2_psi;
  real_T c2_v;
  real_T c2_p;
  real_T c2_r;
  real_T c2_nu[4];
  real_T c2_delta_r;
  real_T c2_delta_sbar;
  real_T c2_y_w;
  real_T c2_M_RB[16];
  real_T c2_C_RB[16];
  real_T c2_M_A[16];
  real_T c2_C_A[16];
  real_T c2_M[16];
  real_T c2_v_t[3];
  real_T c2_v_tw[3];
  real_T c2_R1[9];
  real_T c2_R2[9];
  real_T c2_v_tb[3];
  real_T c2_V_awb[3];
  real_T c2_V_awu;
  real_T c2_V_awv;
  real_T c2_alpha_aw;
  real_T c2_delta_s;
  real_T c2_alpha_as;
  real_T c2_Cls;
  real_T c2_Cds;
  real_T c2_Ls;
  real_T c2_Ds;
  real_T c2_tau_sail[4];
  real_T c2_Mzs;
  real_T c2_v_aru;
  real_T c2_v_arv;
  real_T c2_alpha_ar;
  real_T c2_alpha_a;
  real_T c2_Clr;
  real_T c2_Cdr;
  real_T c2_Lr;
  real_T c2_Dr;
  real_T c2_tau_rudder[4];
  real_T c2_Mzr;
  real_T c2_tau[4];
  real_T c2_v_aku;
  real_T c2_v_akv;
  real_T c2_alpha_ak;
  real_T c2_alpha_e;
  real_T c2_Clk;
  real_T c2_Cdk;
  real_T c2_Lk;
  real_T c2_Dk;
  real_T c2_D_keel[4];
  real_T c2_v_ahu;
  real_T c2_v_ahv;
  real_T c2_v_ah;
  real_T c2_alpha_ah;
  real_T c2_Frh;
  real_T c2_D_hull[4];
  real_T c2_J[16];
  real_T c2_eta_dot[4];
  real_T c2_phi_dot;
  real_T c2_psi_dot;
  real_T c2_D_heelandyaw[4];
  real_T c2_D[4];
  real_T c2_phi_deg;
  real_T c2_M_xw;
  real_T c2_M_zw;
  real_T c2_G[4];
  real_T c2_nu_dot[4];
  real_T c2_b_u;
  real_T c2_b_V_in[3];
  real_T c2_nargin = 8.0;
  real_T c2_nargout = 1.0;
  real_T c2_X_dot_ext[9];
  static c2_srLgvkCzuuZn3rWrmrpDanB c2_r0 = { 25900.0, 133690.0, 24760.0, 2180.0,
    970.0, 17430.0, 106500.0, 101650.0, -13160.0, -6190.0, 4730.0, 10.0,
    3.1415926535897931, 1.2, 170.0, 0.0005, 11.58, -11.58, 0.0, 0.0, -11.58, 0.6,
    0.3, 1025.0, 1.17, 1.9, 0.8, -8.2, -0.78, -8.2, 0.0, -0.78, 8.7, 2.49, 0.7,
    0.0, -0.58, 0.0, 0.0, -0.58, 0.0, -1.18, 0.0, 0.0, -1.18, 60000.0, -8.0, 3.6,
    -5.89, 8160.0, 120000.0, 50000.0 };

  int32_T c2_i5;
  int32_T c2_i6;
  static real_T c2_dv1[16] = { 25900.0, 0.0, 0.0, 0.0, 0.0, 25900.0, 0.0, 0.0,
    0.0, 0.0, 133690.0, -2180.0, 0.0, 0.0, -2180.0, 24760.0 };

  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  int32_T c2_i11;
  static real_T c2_dv2[16] = { 970.0, 0.0, 0.0, 0.0, 0.0, 17430.0, -13160.0,
    -6190.0, 0.0, -13160.0, 106500.0, 4730.0, 0.0, -6190.0, 4730.0, 101650.0 };

  int32_T c2_i12;
  int32_T c2_i13;
  int32_T c2_i14;
  static real_T c2_dv3[16] = { 26870.0, 0.0, 0.0, 0.0, 0.0, 43330.0, -13160.0,
    -6190.0, 0.0, -13160.0, 240190.0, 2550.0, 0.0, -6190.0, 2550.0, 126410.0 };

  int32_T c2_i15;
  static real_T c2_b[3] = { -10.0, 1.2246467991473533E-15, 0.0 };

  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_A;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_b_y;
  real_T c2_b_A;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_c_y;
  real_T c2_a;
  int32_T c2_i16;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_l_x;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_o_x;
  real_T c2_p_x;
  real_T c2_q_x;
  int32_T c2_i17;
  int32_T c2_i18;
  static real_T c2_dv4[3] = { 0.0, 0.0, 1.0 };

  real_T c2_r_x;
  real_T c2_s_x;
  real_T c2_t_x;
  real_T c2_u_x;
  real_T c2_v_x;
  real_T c2_w_x;
  real_T c2_x_x;
  real_T c2_y_x;
  int32_T c2_i19;
  int32_T c2_i20;
  static real_T c2_dv5[3] = { 1.0, 0.0, 0.0 };

  int32_T c2_i21;
  real_T c2_b_a[9];
  int32_T c2_i22;
  real_T c2_b_b[9];
  int32_T c2_i23;
  int32_T c2_i24;
  int32_T c2_i25;
  real_T c2_d_y[9];
  int32_T c2_i26;
  int32_T c2_i27;
  int32_T c2_i28;
  real_T c2_c_b[3];
  int32_T c2_i29;
  int32_T c2_i30;
  int32_T c2_i31;
  real_T c2_C[3];
  int32_T c2_i32;
  int32_T c2_i33;
  int32_T c2_i34;
  int32_T c2_i35;
  int32_T c2_i36;
  int32_T c2_i37;
  real_T c2_b_p[3];
  int32_T c2_i38;
  static real_T c2_dv6[3] = { 0.0, 0.0, -11.58 };

  real_T c2_dv7[3];
  int32_T c2_i39;
  real_T c2_ab_x;
  real_T c2_bb_x;
  real_T c2_cb_x;
  real_T c2_db_x;
  real_T c2_eb_x;
  real_T c2_fb_x;
  real_T c2_gb_x;
  real_T c2_hb_x;
  real_T c2_ib_x;
  real_T c2_jb_x;
  real_T c2_kb_x;
  real_T c2_lb_x;
  real_T c2_mb_x;
  real_T c2_nb_x;
  real_T c2_ob_x;
  real_T c2_pb_x;
  real_T c2_qb_x;
  real_T c2_rb_x;
  real_T c2_sb_x;
  real_T c2_tb_x;
  real_T c2_ub_x;
  real_T c2_vb_x;
  real_T c2_wb_x;
  real_T c2_xb_x;
  real_T c2_c_A;
  real_T c2_yb_x;
  real_T c2_ac_x;
  real_T c2_bc_x;
  real_T c2_e_y;
  real_T c2_cc_x;
  real_T c2_dc_x;
  real_T c2_ec_x;
  real_T c2_fc_x;
  real_T c2_gc_x;
  real_T c2_hc_x;
  real_T c2_ic_x;
  real_T c2_jc_x;
  real_T c2_kc_x;
  real_T c2_lc_x;
  real_T c2_mc_x;
  real_T c2_nc_x;
  real_T c2_oc_x;
  real_T c2_pc_x;
  real_T c2_qc_x;
  real_T c2_rc_x;
  int32_T c2_i40;
  real_T c2_d_A;
  real_T c2_sc_x;
  real_T c2_tc_x;
  real_T c2_uc_x;
  real_T c2_f_y;
  real_T c2_vc_x;
  real_T c2_wc_x;
  real_T c2_xc_x;
  real_T c2_yc_x;
  real_T c2_ad_x;
  real_T c2_bd_x;
  real_T c2_cd_x;
  real_T c2_dd_x;
  real_T c2_ed_x;
  real_T c2_fd_x;
  real_T c2_gd_x;
  real_T c2_hd_x;
  real_T c2_id_x;
  real_T c2_jd_x;
  real_T c2_kd_x;
  real_T c2_ld_x;
  real_T c2_md_x;
  real_T c2_nd_x;
  real_T c2_e_A;
  real_T c2_B;
  real_T c2_od_x;
  real_T c2_g_y;
  real_T c2_pd_x;
  real_T c2_h_y;
  real_T c2_qd_x;
  real_T c2_i_y;
  real_T c2_rd_x;
  real_T c2_sd_x;
  real_T c2_td_x;
  real_T c2_ud_x;
  real_T c2_vd_x;
  real_T c2_wd_x;
  real_T c2_xd_x;
  real_T c2_yd_x;
  real_T c2_ae_x;
  real_T c2_be_x;
  real_T c2_ce_x;
  real_T c2_de_x;
  real_T c2_ee_x;
  real_T c2_fe_x;
  real_T c2_ge_x;
  real_T c2_he_x;
  real_T c2_ie_x;
  real_T c2_je_x;
  real_T c2_ke_x;
  real_T c2_le_x;
  real_T c2_me_x;
  real_T c2_ne_x;
  real_T c2_oe_x;
  real_T c2_pe_x;
  real_T c2_qe_x;
  real_T c2_re_x;
  real_T c2_se_x;
  real_T c2_te_x;
  int32_T c2_i41;
  int32_T c2_i42;
  static real_T c2_dv8[4] = { 0.0, 0.0, 1.0, 0.0 };

  int32_T c2_i43;
  real_T c2_c_a[16];
  int32_T c2_i44;
  real_T c2_d_b[4];
  int32_T c2_i45;
  int32_T c2_i46;
  int32_T c2_i47;
  real_T c2_b_C[4];
  int32_T c2_i48;
  int32_T c2_i49;
  int32_T c2_i50;
  int32_T c2_i51;
  int32_T c2_i52;
  int32_T c2_i53;
  real_T c2_ue_x;
  real_T c2_ve_x;
  real_T c2_d0;
  real_T c2_d1;
  int32_T c2_i54;
  real_T c2_f_A;
  real_T c2_we_x;
  real_T c2_xe_x;
  real_T c2_ye_x;
  real_T c2_af_x;
  real_T c2_bf_x;
  real_T c2_cf_x;
  real_T c2_df_x;
  real_T c2_d2;
  int32_T c2_i55;
  int32_T c2_i56;
  int32_T c2_i57;
  int32_T c2_i58;
  int32_T c2_i59;
  int32_T c2_i60;
  int32_T c2_i61;
  int32_T c2_i62;
  real_T c2_j_y[4];
  int32_T c2_i63;
  int32_T c2_i64;
  int32_T c2_i65;
  real_T c2_c_C[4];
  int32_T c2_i66;
  real_T c2_dv9[16];
  int32_T c2_i67;
  real_T c2_b_D[4];
  int32_T c2_i68;
  real_T c2_dv10[16];
  int32_T c2_i69;
  real_T c2_b_G[4];
  int32_T c2_i70;
  real_T c2_dv11[16];
  int32_T c2_i71;
  real_T c2_b_tau[4];
  real_T c2_dv12[4];
  int32_T c2_i72;
  int32_T c2_i73;
  int32_T c2_i74;
  int32_T c2_i75;
  real_T *c2_b_sail_coeff1;
  real_T *c2_b_sail_coeff2;
  real_T *c2_b_rudder_coeff1;
  real_T *c2_b_rudder_coeff2;
  real_T *c2_b_keel_coeff1;
  real_T *c2_b_keel_coeff2;
  real_T *c2_b_Frh_coeff;
  real_T (*c2_b_X_dot_ext)[9];
  real_T (*c2_c_u)[11];
  c2_b_Frh_coeff = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
  c2_b_keel_coeff2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c2_b_keel_coeff1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c2_b_rudder_coeff2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c2_b_rudder_coeff1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c2_b_sail_coeff2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_b_sail_coeff1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_X_dot_ext = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_c_u = (real_T (*)[11])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_sail_coeff1;
  c2_b_hoistedGlobal = *c2_b_sail_coeff2;
  c2_c_hoistedGlobal = *c2_b_rudder_coeff1;
  c2_d_hoistedGlobal = *c2_b_rudder_coeff2;
  c2_e_hoistedGlobal = *c2_b_keel_coeff1;
  c2_f_hoistedGlobal = *c2_b_keel_coeff2;
  c2_g_hoistedGlobal = *c2_b_Frh_coeff;
  for (c2_i4 = 0; c2_i4 < 11; c2_i4++) {
    c2_u[c2_i4] = (*c2_c_u)[c2_i4];
  }

  c2_sail_coeff1 = c2_hoistedGlobal;
  c2_sail_coeff2 = c2_b_hoistedGlobal;
  c2_rudder_coeff1 = c2_c_hoistedGlobal;
  c2_rudder_coeff2 = c2_d_hoistedGlobal;
  c2_keel_coeff1 = c2_e_hoistedGlobal;
  c2_keel_coeff2 = c2_f_hoistedGlobal;
  c2_Frh_coeff = c2_g_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 83U, 85U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_par, 0U, c2_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_V_in, MAX_uint32_T,
    c2_c_sf_marshallOut, c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_x, 2U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_y, 3U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_phi, 4U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_psi, 5U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v, 6U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_p, 7U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_r, 8U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_nu, 9U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_delta_r, 10U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_delta_sbar, 11U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_y_w, 12U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_M_RB, 13U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_C_RB, 14U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_M_A, 15U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_C_A, 16U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_M, 17U, c2_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_v_t, 18U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_v_tw, 19U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_R1, 20U, c2_g_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_R2, 21U, c2_g_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_v_tb, 22U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_V_awb, 23U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_V_awu, 24U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_V_awv, 25U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_alpha_aw, 26U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_delta_s, 27U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_alpha_as, 28U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Cls, 29U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Cds, 30U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Ls, 31U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Ds, 32U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_tau_sail, 33U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Mzs, 34U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v_aru, 35U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v_arv, 36U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_alpha_ar, 37U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_alpha_a, 38U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Clr, 39U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Cdr, 40U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Lr, 41U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Dr, 42U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_tau_rudder, 43U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Mzr, 44U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_tau, 45U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v_aku, 46U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v_akv, 47U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_alpha_ak, 48U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_alpha_e, 49U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Clk, 50U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Cdk, 51U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Lk, 52U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Dk, 53U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_D_keel, 54U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v_ahu, 55U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v_ahv, 56U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v_ah, 57U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_alpha_ah, 58U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_Frh, 59U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_D_hull, 60U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_J, 61U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_eta_dot, 62U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_phi_dot, 63U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_psi_dot, 64U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_D_heelandyaw, 65U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_D, 66U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_phi_deg, 67U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_M_xw, 68U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_M_zw, 69U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_G, 70U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_nu_dot, 71U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_u, MAX_uint32_T,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_V_in, MAX_uint32_T,
    c2_d_sf_marshallOut, c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 73U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 74U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_u, 72U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_sail_coeff1, 75U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_sail_coeff2, 76U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_rudder_coeff1, 77U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_rudder_coeff2, 78U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_keel_coeff1, 79U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_keel_coeff2, 80U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_Frh_coeff, 81U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_X_dot_ext, 82U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 19);
  c2_par = c2_r0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 21);
  for (c2_i5 = 0; c2_i5 < 11; c2_i5++) {
    c2_V_in[c2_i5] = c2_u[c2_i5];
  }

  _SFD_SYMBOL_SWITCH(1U, 1U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
  c2_x = c2_V_in[3];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 24);
  c2_y = c2_V_in[4];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
  c2_phi = c2_V_in[5];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 26);
  c2_psi = c2_V_in[6];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
  c2_b_u = c2_V_in[7];
  _SFD_SYMBOL_SWITCH(72U, 72U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_v = c2_V_in[8];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
  c2_p = c2_V_in[9];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
  c2_r = c2_V_in[10];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  c2_nu[0] = c2_b_u;
  c2_nu[1] = c2_v;
  c2_nu[2] = c2_p;
  c2_nu[3] = c2_r;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
  c2_delta_r = c2_V_in[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
  c2_delta_sbar = c2_V_in[1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 36);
  c2_y_w = c2_V_in[2];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 39);
  for (c2_i6 = 0; c2_i6 < 16; c2_i6++) {
    c2_M_RB[c2_i6] = c2_dv1[c2_i6];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 40);
  c2_C_RB[0] = 0.0;
  c2_C_RB[4] = -25900.0 * c2_r;
  c2_C_RB[8] = 0.0;
  c2_C_RB[12] = 0.0;
  c2_C_RB[1] = 25900.0 * c2_r;
  c2_C_RB[5] = 0.0;
  c2_C_RB[9] = 0.0;
  c2_C_RB[13] = 0.0;
  c2_i7 = 0;
  for (c2_i8 = 0; c2_i8 < 4; c2_i8++) {
    c2_C_RB[c2_i7 + 2] = 0.0;
    c2_i7 += 4;
  }

  c2_i9 = 0;
  for (c2_i10 = 0; c2_i10 < 4; c2_i10++) {
    c2_C_RB[c2_i9 + 3] = 0.0;
    c2_i9 += 4;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 42);
  for (c2_i11 = 0; c2_i11 < 16; c2_i11++) {
    c2_M_A[c2_i11] = c2_dv2[c2_i11];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  c2_C_A[0] = 0.0;
  c2_C_A[4] = 0.0;
  c2_C_A[8] = 0.0;
  c2_C_A[12] = (-17430.0 * c2_nu[1] - -13160.0 * c2_nu[2]) - -6190.0 * c2_nu[3];
  c2_C_A[1] = 0.0;
  c2_C_A[5] = 0.0;
  c2_C_A[9] = 0.0;
  c2_C_A[13] = 970.0 * c2_nu[0];
  c2_i12 = 0;
  for (c2_i13 = 0; c2_i13 < 4; c2_i13++) {
    c2_C_A[c2_i12 + 2] = 0.0;
    c2_i12 += 4;
  }

  c2_C_A[3] = (17430.0 * c2_nu[1] + -13160.0 * c2_nu[2]) + -6190.0 * c2_nu[3];
  c2_C_A[7] = -970.0 * c2_nu[0];
  c2_C_A[11] = 0.0;
  c2_C_A[15] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 45);
  for (c2_i14 = 0; c2_i14 < 16; c2_i14++) {
    c2_M[c2_i14] = c2_dv3[c2_i14];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 49);
  for (c2_i15 = 0; c2_i15 < 3; c2_i15++) {
    c2_v_t[c2_i15] = c2_b[c2_i15];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 50);
  c2_b_x = c2_phi;
  c2_c_x = c2_b_x;
  c2_c_x = muDoubleScalarCos(c2_c_x);
  c2_A = 11.58 * c2_c_x;
  c2_d_x = c2_A;
  c2_e_x = c2_d_x;
  c2_f_x = c2_e_x;
  c2_b_y = c2_f_x / 0.0005;
  c2_b_A = c2_b_y;
  c2_b_log(chartInstance, &c2_b_A);
  c2_g_x = c2_b_A;
  c2_h_x = c2_g_x;
  c2_i_x = c2_h_x;
  c2_c_y = c2_i_x / 10.050181931686932;
  c2_a = c2_c_y;
  for (c2_i16 = 0; c2_i16 < 3; c2_i16++) {
    c2_v_tw[c2_i16] = c2_a * c2_b[c2_i16];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 51);
  c2_j_x = -c2_psi;
  c2_k_x = c2_j_x;
  c2_k_x = muDoubleScalarCos(c2_k_x);
  c2_l_x = -c2_psi;
  c2_m_x = c2_l_x;
  c2_m_x = muDoubleScalarSin(c2_m_x);
  c2_n_x = -c2_psi;
  c2_o_x = c2_n_x;
  c2_o_x = muDoubleScalarSin(c2_o_x);
  c2_p_x = -c2_psi;
  c2_q_x = c2_p_x;
  c2_q_x = muDoubleScalarCos(c2_q_x);
  c2_R1[0] = c2_k_x;
  c2_R1[3] = -c2_m_x;
  c2_R1[6] = 0.0;
  c2_R1[1] = c2_o_x;
  c2_R1[4] = c2_q_x;
  c2_R1[7] = 0.0;
  c2_i17 = 0;
  for (c2_i18 = 0; c2_i18 < 3; c2_i18++) {
    c2_R1[c2_i17 + 2] = c2_dv4[c2_i18];
    c2_i17 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 52);
  c2_r_x = -c2_phi;
  c2_s_x = c2_r_x;
  c2_s_x = muDoubleScalarCos(c2_s_x);
  c2_t_x = -c2_phi;
  c2_u_x = c2_t_x;
  c2_u_x = muDoubleScalarSin(c2_u_x);
  c2_v_x = -c2_phi;
  c2_w_x = c2_v_x;
  c2_w_x = muDoubleScalarSin(c2_w_x);
  c2_x_x = -c2_phi;
  c2_y_x = c2_x_x;
  c2_y_x = muDoubleScalarCos(c2_y_x);
  c2_i19 = 0;
  for (c2_i20 = 0; c2_i20 < 3; c2_i20++) {
    c2_R2[c2_i19] = c2_dv5[c2_i20];
    c2_i19 += 3;
  }

  c2_R2[1] = 0.0;
  c2_R2[4] = c2_s_x;
  c2_R2[7] = -c2_u_x;
  c2_R2[2] = 0.0;
  c2_R2[5] = c2_w_x;
  c2_R2[8] = c2_y_x;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 53);
  for (c2_i21 = 0; c2_i21 < 9; c2_i21++) {
    c2_b_a[c2_i21] = c2_R2[c2_i21];
  }

  for (c2_i22 = 0; c2_i22 < 9; c2_i22++) {
    c2_b_b[c2_i22] = c2_R1[c2_i22];
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i23 = 0; c2_i23 < 3; c2_i23++) {
    c2_i24 = 0;
    for (c2_i25 = 0; c2_i25 < 3; c2_i25++) {
      c2_d_y[c2_i24 + c2_i23] = 0.0;
      c2_i26 = 0;
      for (c2_i27 = 0; c2_i27 < 3; c2_i27++) {
        c2_d_y[c2_i24 + c2_i23] += c2_b_a[c2_i26 + c2_i23] * c2_b_b[c2_i27 +
          c2_i24];
        c2_i26 += 3;
      }

      c2_i24 += 3;
    }
  }

  for (c2_i28 = 0; c2_i28 < 3; c2_i28++) {
    c2_c_b[c2_i28] = c2_v_tw[c2_i28];
  }

  c2_b_eml_scalar_eg(chartInstance);
  c2_b_eml_scalar_eg(chartInstance);
  for (c2_i29 = 0; c2_i29 < 3; c2_i29++) {
    c2_v_tb[c2_i29] = 0.0;
  }

  for (c2_i30 = 0; c2_i30 < 3; c2_i30++) {
    c2_v_tb[c2_i30] = 0.0;
  }

  for (c2_i31 = 0; c2_i31 < 3; c2_i31++) {
    c2_C[c2_i31] = c2_v_tb[c2_i31];
  }

  for (c2_i32 = 0; c2_i32 < 3; c2_i32++) {
    c2_v_tb[c2_i32] = c2_C[c2_i32];
  }

  c2_threshold(chartInstance);
  for (c2_i33 = 0; c2_i33 < 3; c2_i33++) {
    c2_C[c2_i33] = c2_v_tb[c2_i33];
  }

  for (c2_i34 = 0; c2_i34 < 3; c2_i34++) {
    c2_v_tb[c2_i34] = c2_C[c2_i34];
  }

  for (c2_i35 = 0; c2_i35 < 3; c2_i35++) {
    c2_v_tb[c2_i35] = 0.0;
    c2_i36 = 0;
    for (c2_i37 = 0; c2_i37 < 3; c2_i37++) {
      c2_v_tb[c2_i35] += c2_d_y[c2_i36 + c2_i35] * c2_c_b[c2_i37];
      c2_i36 += 3;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 54);
  c2_b_V_in[0] = c2_b_u;
  c2_b_V_in[1] = c2_v;
  c2_b_V_in[2] = 0.0;
  _SFD_SYMBOL_SWITCH(1U, 73U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 55);
  c2_b_p[0] = c2_p;
  c2_b_p[1] = 0.0;
  c2_b_p[2] = c2_r;
  for (c2_i38 = 0; c2_i38 < 3; c2_i38++) {
    c2_dv7[c2_i38] = c2_dv6[c2_i38];
  }

  c2_cross(chartInstance, c2_b_p, c2_dv7, c2_c_b);
  for (c2_i39 = 0; c2_i39 < 3; c2_i39++) {
    c2_V_awb[c2_i39] = (c2_v_tb[c2_i39] - c2_b_V_in[c2_i39]) - c2_c_b[c2_i39];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 56);
  c2_V_awu = c2_V_awb[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 57);
  c2_V_awv = c2_V_awb[1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 58);
  c2_alpha_aw = c2_atan2(chartInstance, c2_V_awv, -c2_V_awu);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 61);
  if (CV_EML_IF(0, 1, 0, c2_alpha_aw > c2_delta_sbar)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 62);
    c2_delta_s = c2_delta_sbar;
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 63);
    if (CV_EML_IF(0, 1, 1, c2_alpha_aw < -c2_delta_sbar)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 64);
      c2_delta_s = -c2_delta_sbar;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 66);
      c2_delta_s = c2_alpha_aw;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 69);
  c2_alpha_as = c2_alpha_aw - c2_delta_s;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 71);
  c2_Cls = c2_sail_coeff1;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 72);
  c2_Cds = c2_sail_coeff2;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 74);
  c2_Ls = 102.0 * (c2_mpower(chartInstance, c2_V_awu) + c2_mpower(chartInstance,
    c2_V_awv)) * c2_Cls;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 75);
  c2_Ds = 102.0 * (c2_mpower(chartInstance, c2_V_awu) + c2_mpower(chartInstance,
    c2_V_awv)) * c2_Cds;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 77);
  c2_ab_x = c2_alpha_aw;
  c2_bb_x = c2_ab_x;
  c2_bb_x = muDoubleScalarSin(c2_bb_x);
  c2_cb_x = c2_alpha_aw;
  c2_db_x = c2_cb_x;
  c2_db_x = muDoubleScalarCos(c2_db_x);
  c2_eb_x = c2_alpha_aw;
  c2_fb_x = c2_eb_x;
  c2_fb_x = muDoubleScalarCos(c2_fb_x);
  c2_gb_x = c2_alpha_aw;
  c2_hb_x = c2_gb_x;
  c2_hb_x = muDoubleScalarSin(c2_hb_x);
  c2_ib_x = c2_alpha_aw;
  c2_jb_x = c2_ib_x;
  c2_jb_x = muDoubleScalarCos(c2_jb_x);
  c2_kb_x = c2_alpha_aw;
  c2_lb_x = c2_kb_x;
  c2_lb_x = muDoubleScalarSin(c2_lb_x);
  c2_mb_x = c2_alpha_aw;
  c2_nb_x = c2_mb_x;
  c2_nb_x = muDoubleScalarSin(c2_nb_x);
  c2_ob_x = c2_alpha_aw;
  c2_pb_x = c2_ob_x;
  c2_pb_x = muDoubleScalarCos(c2_pb_x);
  c2_qb_x = c2_delta_s;
  c2_rb_x = c2_qb_x;
  c2_rb_x = muDoubleScalarSin(c2_rb_x);
  c2_sb_x = c2_alpha_aw;
  c2_tb_x = c2_sb_x;
  c2_tb_x = muDoubleScalarCos(c2_tb_x);
  c2_ub_x = c2_alpha_aw;
  c2_vb_x = c2_ub_x;
  c2_vb_x = muDoubleScalarSin(c2_vb_x);
  c2_wb_x = c2_delta_s;
  c2_xb_x = c2_wb_x;
  c2_xb_x = muDoubleScalarCos(c2_xb_x);
  c2_tau_sail[0] = c2_Ls * c2_bb_x - c2_Ds * c2_db_x;
  c2_tau_sail[1] = c2_Ls * c2_fb_x + c2_Ds * c2_hb_x;
  c2_tau_sail[2] = -(c2_Ls * c2_jb_x + c2_Ds * c2_lb_x) * -11.58;
  c2_tau_sail[3] = -(c2_Ls * c2_nb_x - c2_Ds * c2_pb_x) * 0.6 * c2_rb_x + (c2_Ls
    * c2_tb_x + c2_Ds * c2_vb_x) * (c2_par.Xm - 0.6 * c2_xb_x);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 78);
  c2_Mzs = c2_tau_sail[3];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 81);
  c2_v_aru = -c2_b_u + c2_r * 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 82);
  c2_v_arv = (-c2_v - c2_r * -8.2) + c2_p * -0.78;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 83);
  c2_alpha_ar = c2_atan2(chartInstance, c2_v_arv, -c2_v_aru);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 84);
  c2_alpha_a = c2_alpha_ar - c2_delta_r;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 87);
  c2_Clr = c2_rudder_coeff1;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 88);
  c2_Cdr = c2_rudder_coeff2;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 90);
  c2_c_A = c2_mpower(chartInstance, c2_Clr) * 1.17;
  c2_yb_x = c2_c_A;
  c2_ac_x = c2_yb_x;
  c2_bc_x = c2_ac_x;
  c2_e_y = c2_bc_x / 18.145839167134646;
  c2_Cdr += c2_e_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 92);
  c2_Lr = 599.625 * (c2_mpower(chartInstance, c2_v_aru) + c2_mpower
                     (chartInstance, c2_v_arv)) * c2_Clr;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 93);
  c2_Dr = 599.625 * (c2_mpower(chartInstance, c2_v_aru) + c2_mpower
                     (chartInstance, c2_v_arv)) * c2_Cdr;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 95);
  c2_cc_x = c2_alpha_ar;
  c2_dc_x = c2_cc_x;
  c2_dc_x = muDoubleScalarSin(c2_dc_x);
  c2_ec_x = c2_alpha_ar;
  c2_fc_x = c2_ec_x;
  c2_fc_x = muDoubleScalarCos(c2_fc_x);
  c2_gc_x = c2_alpha_ar;
  c2_hc_x = c2_gc_x;
  c2_hc_x = muDoubleScalarCos(c2_hc_x);
  c2_ic_x = c2_alpha_ar;
  c2_jc_x = c2_ic_x;
  c2_jc_x = muDoubleScalarSin(c2_jc_x);
  c2_kc_x = c2_alpha_ar;
  c2_lc_x = c2_kc_x;
  c2_lc_x = muDoubleScalarCos(c2_lc_x);
  c2_mc_x = c2_alpha_ar;
  c2_nc_x = c2_mc_x;
  c2_nc_x = muDoubleScalarSin(c2_nc_x);
  c2_oc_x = c2_alpha_ar;
  c2_pc_x = c2_oc_x;
  c2_pc_x = muDoubleScalarCos(c2_pc_x);
  c2_qc_x = c2_alpha_ar;
  c2_rc_x = c2_qc_x;
  c2_rc_x = muDoubleScalarSin(c2_rc_x);
  c2_tau_rudder[0] = c2_Lr * c2_dc_x - c2_Dr * c2_fc_x;
  c2_tau_rudder[1] = c2_Lr * c2_hc_x + c2_Dr * c2_jc_x;
  c2_tau_rudder[2] = -(c2_Lr * c2_lc_x + c2_Dr * c2_nc_x) * -0.78;
  c2_tau_rudder[3] = (c2_Lr * c2_pc_x + c2_Dr * c2_rc_x) * -8.2;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 96);
  c2_Mzr = c2_tau_rudder[3];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 99);
  for (c2_i40 = 0; c2_i40 < 4; c2_i40++) {
    c2_tau[c2_i40] = c2_tau_sail[c2_i40] + c2_tau_rudder[c2_i40];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 103);
  c2_v_aku = -c2_b_u + c2_r * 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 104);
  c2_v_akv = (-c2_v - c2_r * 0.0) + c2_p * -0.58;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 105);
  c2_alpha_ak = c2_atan2(chartInstance, c2_v_akv, -c2_v_aku);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 106);
  c2_alpha_e = c2_alpha_ak;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 108);
  c2_Clk = c2_keel_coeff1;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 109);
  c2_Cdk = c2_keel_coeff2;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 111);
  c2_d_A = c2_mpower(chartInstance, c2_Clk) * 8.7;
  c2_sc_x = c2_d_A;
  c2_tc_x = c2_sc_x;
  c2_uc_x = c2_tc_x;
  c2_f_y = c2_uc_x / 27.269464056130911;
  c2_Cdk += c2_f_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 113);
  c2_Lk = 4458.75 * (c2_mpower(chartInstance, c2_v_aku) + c2_mpower
                     (chartInstance, c2_v_akv)) * c2_Clk;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 114);
  c2_Dk = 4458.75 * (c2_mpower(chartInstance, c2_v_aku) + c2_mpower
                     (chartInstance, c2_v_akv)) * c2_Cdk;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 116);
  c2_vc_x = c2_alpha_ak;
  c2_wc_x = c2_vc_x;
  c2_wc_x = muDoubleScalarSin(c2_wc_x);
  c2_xc_x = c2_alpha_ak;
  c2_yc_x = c2_xc_x;
  c2_yc_x = muDoubleScalarCos(c2_yc_x);
  c2_ad_x = c2_alpha_ak;
  c2_bd_x = c2_ad_x;
  c2_bd_x = muDoubleScalarCos(c2_bd_x);
  c2_cd_x = c2_alpha_ak;
  c2_dd_x = c2_cd_x;
  c2_dd_x = muDoubleScalarSin(c2_dd_x);
  c2_ed_x = c2_alpha_ak;
  c2_fd_x = c2_ed_x;
  c2_fd_x = muDoubleScalarCos(c2_fd_x);
  c2_gd_x = c2_alpha_ak;
  c2_hd_x = c2_gd_x;
  c2_hd_x = muDoubleScalarSin(c2_hd_x);
  c2_id_x = c2_alpha_ak;
  c2_jd_x = c2_id_x;
  c2_jd_x = muDoubleScalarCos(c2_jd_x);
  c2_kd_x = c2_alpha_ak;
  c2_ld_x = c2_kd_x;
  c2_ld_x = muDoubleScalarSin(c2_ld_x);
  c2_D_keel[0] = -c2_Lk * c2_wc_x + c2_Dk * c2_yc_x;
  c2_D_keel[1] = -c2_Lk * c2_bd_x - c2_Dk * c2_dd_x;
  c2_D_keel[2] = -(-c2_Lk * c2_fd_x - c2_Dk * c2_hd_x) * -0.58;
  c2_D_keel[3] = -(c2_Lk * c2_jd_x + c2_Dk * c2_ld_x) * 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 119);
  c2_v_ahu = -c2_b_u + c2_r * 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 120);
  c2_md_x = c2_phi;
  c2_nd_x = c2_md_x;
  c2_nd_x = muDoubleScalarCos(c2_nd_x);
  c2_e_A = (-c2_v - c2_r * 0.0) + c2_p * -1.18;
  c2_B = c2_nd_x;
  c2_od_x = c2_e_A;
  c2_g_y = c2_B;
  c2_pd_x = c2_od_x;
  c2_h_y = c2_g_y;
  c2_qd_x = c2_pd_x;
  c2_i_y = c2_h_y;
  c2_v_ahv = c2_qd_x / c2_i_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 121);
  c2_v_ah = c2_mpower(chartInstance, c2_v_aku) + c2_mpower(chartInstance,
    c2_v_akv);
  c2_b_sqrt(chartInstance, &c2_v_ah);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 122);
  c2_alpha_ah = c2_atan2(chartInstance, c2_v_ahv, -c2_v_ahu);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 124);
  c2_Frh = c2_Frh_coeff;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 126);
  c2_rd_x = c2_alpha_ah;
  c2_sd_x = c2_rd_x;
  c2_sd_x = muDoubleScalarCos(c2_sd_x);
  c2_td_x = c2_alpha_ah;
  c2_ud_x = c2_td_x;
  c2_ud_x = muDoubleScalarSin(c2_ud_x);
  c2_vd_x = c2_phi;
  c2_wd_x = c2_vd_x;
  c2_wd_x = muDoubleScalarCos(c2_wd_x);
  c2_xd_x = c2_alpha_ah;
  c2_yd_x = c2_xd_x;
  c2_yd_x = muDoubleScalarSin(c2_yd_x);
  c2_ae_x = c2_phi;
  c2_be_x = c2_ae_x;
  c2_be_x = muDoubleScalarCos(c2_be_x);
  c2_ce_x = c2_alpha_ah;
  c2_de_x = c2_ce_x;
  c2_de_x = muDoubleScalarSin(c2_de_x);
  c2_ee_x = c2_phi;
  c2_fe_x = c2_ee_x;
  c2_fe_x = muDoubleScalarCos(c2_fe_x);
  c2_D_hull[0] = c2_Frh * c2_sd_x;
  c2_D_hull[1] = -c2_Frh * c2_ud_x * c2_wd_x;
  c2_D_hull[2] = c2_Frh * c2_yd_x * c2_be_x * -1.18;
  c2_D_hull[3] = -c2_Frh * c2_de_x * c2_fe_x * 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 130U);
  c2_ge_x = c2_psi;
  c2_he_x = c2_ge_x;
  c2_he_x = muDoubleScalarCos(c2_he_x);
  c2_ie_x = c2_psi;
  c2_je_x = c2_ie_x;
  c2_je_x = muDoubleScalarSin(c2_je_x);
  c2_ke_x = c2_phi;
  c2_le_x = c2_ke_x;
  c2_le_x = muDoubleScalarCos(c2_le_x);
  c2_me_x = c2_psi;
  c2_ne_x = c2_me_x;
  c2_ne_x = muDoubleScalarSin(c2_ne_x);
  c2_oe_x = c2_psi;
  c2_pe_x = c2_oe_x;
  c2_pe_x = muDoubleScalarCos(c2_pe_x);
  c2_qe_x = c2_phi;
  c2_re_x = c2_qe_x;
  c2_re_x = muDoubleScalarCos(c2_re_x);
  c2_se_x = c2_phi;
  c2_te_x = c2_se_x;
  c2_te_x = muDoubleScalarCos(c2_te_x);
  c2_J[0] = c2_he_x;
  c2_J[4] = -c2_je_x * c2_le_x;
  c2_J[8] = 0.0;
  c2_J[12] = 0.0;
  c2_J[1] = c2_ne_x;
  c2_J[5] = c2_pe_x * c2_re_x;
  c2_J[9] = 0.0;
  c2_J[13] = 0.0;
  c2_i41 = 0;
  for (c2_i42 = 0; c2_i42 < 4; c2_i42++) {
    c2_J[c2_i41 + 2] = c2_dv8[c2_i42];
    c2_i41 += 4;
  }

  c2_J[3] = 0.0;
  c2_J[7] = 0.0;
  c2_J[11] = 0.0;
  c2_J[15] = c2_te_x;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 131U);
  for (c2_i43 = 0; c2_i43 < 16; c2_i43++) {
    c2_c_a[c2_i43] = c2_J[c2_i43];
  }

  for (c2_i44 = 0; c2_i44 < 4; c2_i44++) {
    c2_d_b[c2_i44] = c2_nu[c2_i44];
  }

  c2_d_eml_scalar_eg(chartInstance);
  c2_d_eml_scalar_eg(chartInstance);
  for (c2_i45 = 0; c2_i45 < 4; c2_i45++) {
    c2_eta_dot[c2_i45] = 0.0;
  }

  for (c2_i46 = 0; c2_i46 < 4; c2_i46++) {
    c2_eta_dot[c2_i46] = 0.0;
  }

  for (c2_i47 = 0; c2_i47 < 4; c2_i47++) {
    c2_b_C[c2_i47] = c2_eta_dot[c2_i47];
  }

  for (c2_i48 = 0; c2_i48 < 4; c2_i48++) {
    c2_eta_dot[c2_i48] = c2_b_C[c2_i48];
  }

  c2_threshold(chartInstance);
  for (c2_i49 = 0; c2_i49 < 4; c2_i49++) {
    c2_b_C[c2_i49] = c2_eta_dot[c2_i49];
  }

  for (c2_i50 = 0; c2_i50 < 4; c2_i50++) {
    c2_eta_dot[c2_i50] = c2_b_C[c2_i50];
  }

  for (c2_i51 = 0; c2_i51 < 4; c2_i51++) {
    c2_eta_dot[c2_i51] = 0.0;
    c2_i52 = 0;
    for (c2_i53 = 0; c2_i53 < 4; c2_i53++) {
      c2_eta_dot[c2_i51] += c2_c_a[c2_i52 + c2_i51] * c2_d_b[c2_i53];
      c2_i52 += 4;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 132U);
  c2_phi_dot = c2_eta_dot[2];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 133U);
  c2_psi_dot = c2_eta_dot[3];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 135U);
  c2_ue_x = c2_phi;
  c2_ve_x = c2_ue_x;
  c2_ve_x = muDoubleScalarCos(c2_ve_x);
  c2_d0 = c2_abs(chartInstance, c2_phi_dot);
  c2_d1 = c2_abs(chartInstance, c2_psi_dot);
  c2_D_heelandyaw[0] = 0.0;
  c2_D_heelandyaw[1] = 0.0;
  c2_D_heelandyaw[2] = 120000.0 * c2_phi_dot * c2_d0;
  c2_D_heelandyaw[3] = 50000.0 * c2_psi_dot * c2_d1 * c2_ve_x;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 138U);
  for (c2_i54 = 0; c2_i54 < 4; c2_i54++) {
    c2_D[c2_i54] = (c2_D_keel[c2_i54] + c2_D_hull[c2_i54]) +
      c2_D_heelandyaw[c2_i54];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 141U);
  c2_f_A = c2_phi * 180.0;
  c2_we_x = c2_f_A;
  c2_xe_x = c2_we_x;
  c2_ye_x = c2_xe_x;
  c2_phi_deg = c2_ye_x / 3.1415926535897931;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 142U);
  c2_af_x = c2_phi;
  c2_bf_x = c2_af_x;
  c2_bf_x = muDoubleScalarCos(c2_bf_x);
  c2_M_xw = -c2_y_w * 60000.0 * 3.6 * c2_bf_x;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 143U);
  c2_cf_x = c2_abs(chartInstance, c2_phi);
  c2_df_x = c2_cf_x;
  c2_df_x = muDoubleScalarSin(c2_df_x);
  c2_M_zw = -c2_y_w * 60000.0 * -8.0 * c2_df_x;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 144U);
  c2_d2 = c2_mpower(chartInstance, c2_phi_deg);
  c2_G[0] = 0.0;
  c2_G[1] = 0.0;
  c2_G[2] = (-5.89 * c2_d2 + 8160.0 * c2_phi_deg) + c2_M_xw;
  c2_G[3] = c2_M_zw;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 147U);
  for (c2_i55 = 0; c2_i55 < 16; c2_i55++) {
    c2_c_a[c2_i55] = c2_C_RB[c2_i55];
  }

  for (c2_i56 = 0; c2_i56 < 4; c2_i56++) {
    c2_d_b[c2_i56] = c2_nu[c2_i56];
  }

  c2_d_eml_scalar_eg(chartInstance);
  c2_d_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i57 = 0; c2_i57 < 4; c2_i57++) {
    c2_b_C[c2_i57] = 0.0;
    c2_i58 = 0;
    for (c2_i59 = 0; c2_i59 < 4; c2_i59++) {
      c2_b_C[c2_i57] += c2_c_a[c2_i58 + c2_i57] * c2_d_b[c2_i59];
      c2_i58 += 4;
    }
  }

  for (c2_i60 = 0; c2_i60 < 16; c2_i60++) {
    c2_c_a[c2_i60] = c2_C_A[c2_i60];
  }

  for (c2_i61 = 0; c2_i61 < 4; c2_i61++) {
    c2_d_b[c2_i61] = c2_nu[c2_i61];
  }

  c2_d_eml_scalar_eg(chartInstance);
  c2_d_eml_scalar_eg(chartInstance);
  c2_threshold(chartInstance);
  for (c2_i62 = 0; c2_i62 < 4; c2_i62++) {
    c2_j_y[c2_i62] = 0.0;
    c2_i63 = 0;
    for (c2_i64 = 0; c2_i64 < 4; c2_i64++) {
      c2_j_y[c2_i62] += c2_c_a[c2_i63 + c2_i62] * c2_d_b[c2_i64];
      c2_i63 += 4;
    }
  }

  for (c2_i65 = 0; c2_i65 < 4; c2_i65++) {
    c2_c_C[c2_i65] = c2_b_C[c2_i65] + c2_j_y[c2_i65];
  }

  c2_mldivide(chartInstance, c2_c_C, c2_b_C);
  for (c2_i66 = 0; c2_i66 < 16; c2_i66++) {
    c2_dv9[c2_i66] = c2_dv3[c2_i66];
  }

  for (c2_i67 = 0; c2_i67 < 4; c2_i67++) {
    c2_b_D[c2_i67] = c2_D[c2_i67];
  }

  c2_b_mldivide(chartInstance, c2_dv9, c2_b_D, c2_j_y);
  for (c2_i68 = 0; c2_i68 < 16; c2_i68++) {
    c2_dv10[c2_i68] = c2_dv3[c2_i68];
  }

  for (c2_i69 = 0; c2_i69 < 4; c2_i69++) {
    c2_b_G[c2_i69] = c2_G[c2_i69];
  }

  c2_b_mldivide(chartInstance, c2_dv10, c2_b_G, c2_d_b);
  for (c2_i70 = 0; c2_i70 < 16; c2_i70++) {
    c2_dv11[c2_i70] = c2_dv3[c2_i70];
  }

  for (c2_i71 = 0; c2_i71 < 4; c2_i71++) {
    c2_b_tau[c2_i71] = c2_tau[c2_i71];
  }

  c2_b_mldivide(chartInstance, c2_dv11, c2_b_tau, c2_dv12);
  for (c2_i72 = 0; c2_i72 < 4; c2_i72++) {
    c2_nu_dot[c2_i72] = ((c2_b_C[c2_i72] - c2_j_y[c2_i72]) - c2_d_b[c2_i72]) +
      c2_dv12[c2_i72];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 151U);
  for (c2_i73 = 0; c2_i73 < 4; c2_i73++) {
    c2_X_dot_ext[c2_i73] = c2_eta_dot[c2_i73];
  }

  for (c2_i74 = 0; c2_i74 < 4; c2_i74++) {
    c2_X_dot_ext[c2_i74 + 4] = c2_nu_dot[c2_i74];
  }

  c2_X_dot_ext[8] = c2_delta_s;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -151);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i75 = 0; c2_i75 < 9; c2_i75++) {
    (*c2_b_X_dot_ext)[c2_i75] = c2_X_dot_ext[c2_i75];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_SailingYachtModel2
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, c2_instanceNumber, 0U,
    sf_debug_get_script_id(
    "/home/paul/KTH/Optimal Control/BottleBoat/Simulink/modeleBoat.m"));
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i76;
  real_T c2_b_inData[9];
  int32_T c2_i77;
  real_T c2_u[9];
  const mxArray *c2_y = NULL;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i76 = 0; c2_i76 < 9; c2_i76++) {
    c2_b_inData[c2_i76] = (*(real_T (*)[9])c2_inData)[c2_i76];
  }

  for (c2_i77 = 0; c2_i77 < 9; c2_i77++) {
    c2_u[c2_i77] = c2_b_inData[c2_i77];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 9), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_X_dot_ext, const char_T *c2_identifier,
  real_T c2_y[9])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_X_dot_ext), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_X_dot_ext);
}

static void c2_b_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9])
{
  real_T c2_dv13[9];
  int32_T c2_i78;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv13, 1, 0, 0U, 1, 0U, 1, 9);
  for (c2_i78 = 0; c2_i78 < 9; c2_i78++) {
    c2_y[c2_i78] = c2_dv13[c2_i78];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_X_dot_ext;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[9];
  int32_T c2_i79;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_X_dot_ext = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_X_dot_ext), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_X_dot_ext);
  for (c2_i79 = 0; c2_i79 < 9; c2_i79++) {
    (*(real_T (*)[9])c2_outData)[c2_i79] = c2_y[c2_i79];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i80;
  real_T c2_b_inData[11];
  int32_T c2_i81;
  real_T c2_u[11];
  const mxArray *c2_y = NULL;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i80 = 0; c2_i80 < 11; c2_i80++) {
    c2_b_inData[c2_i80] = (*(real_T (*)[11])c2_inData)[c2_i80];
  }

  for (c2_i81 = 0; c2_i81 < 11; c2_i81++) {
    c2_u[c2_i81] = c2_b_inData[c2_i81];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 11), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d3;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d3, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d3;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i82;
  real_T c2_b_inData[3];
  int32_T c2_i83;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i82 = 0; c2_i82 < 3; c2_i82++) {
    c2_b_inData[c2_i82] = (*(real_T (*)[3])c2_inData)[c2_i82];
  }

  for (c2_i83 = 0; c2_i83 < 3; c2_i83++) {
    c2_u[c2_i83] = c2_b_inData[c2_i83];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_d_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3])
{
  real_T c2_dv14[3];
  int32_T c2_i84;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv14, 1, 0, 0U, 1, 0U, 1, 3);
  for (c2_i84 = 0; c2_i84 < 3; c2_i84++) {
    c2_y[c2_i84] = c2_dv14[c2_i84];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_V_in;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i85;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_V_in = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_V_in), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_V_in);
  for (c2_i85 = 0; c2_i85 < 3; c2_i85++) {
    (*(real_T (*)[3])c2_outData)[c2_i85] = c2_y[c2_i85];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i86;
  real_T c2_b_inData[4];
  int32_T c2_i87;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i86 = 0; c2_i86 < 4; c2_i86++) {
    c2_b_inData[c2_i86] = (*(real_T (*)[4])c2_inData)[c2_i86];
  }

  for (c2_i87 = 0; c2_i87 < 4; c2_i87++) {
    c2_u[c2_i87] = c2_b_inData[c2_i87];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4])
{
  real_T c2_dv15[4];
  int32_T c2_i88;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv15, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i88 = 0; c2_i88 < 4; c2_i88++) {
    c2_y[c2_i88] = c2_dv15[c2_i88];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nu_dot;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i89;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_nu_dot = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nu_dot), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_nu_dot);
  for (c2_i89 = 0; c2_i89 < 4; c2_i89++) {
    (*(real_T (*)[4])c2_outData)[c2_i89] = c2_y[c2_i89];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i90;
  int32_T c2_i91;
  int32_T c2_i92;
  real_T c2_b_inData[16];
  int32_T c2_i93;
  int32_T c2_i94;
  int32_T c2_i95;
  real_T c2_u[16];
  const mxArray *c2_y = NULL;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i90 = 0;
  for (c2_i91 = 0; c2_i91 < 4; c2_i91++) {
    for (c2_i92 = 0; c2_i92 < 4; c2_i92++) {
      c2_b_inData[c2_i92 + c2_i90] = (*(real_T (*)[16])c2_inData)[c2_i92 +
        c2_i90];
    }

    c2_i90 += 4;
  }

  c2_i93 = 0;
  for (c2_i94 = 0; c2_i94 < 4; c2_i94++) {
    for (c2_i95 = 0; c2_i95 < 4; c2_i95++) {
      c2_u[c2_i95 + c2_i93] = c2_b_inData[c2_i95 + c2_i93];
    }

    c2_i93 += 4;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 4, 4), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_f_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16])
{
  real_T c2_dv16[16];
  int32_T c2_i96;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv16, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c2_i96 = 0; c2_i96 < 16; c2_i96++) {
    c2_y[c2_i96] = c2_dv16[c2_i96];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_J;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[16];
  int32_T c2_i97;
  int32_T c2_i98;
  int32_T c2_i99;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_J = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_J), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_J);
  c2_i97 = 0;
  for (c2_i98 = 0; c2_i98 < 4; c2_i98++) {
    for (c2_i99 = 0; c2_i99 < 4; c2_i99++) {
      (*(real_T (*)[16])c2_outData)[c2_i99 + c2_i97] = c2_y[c2_i99 + c2_i97];
    }

    c2_i97 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i100;
  int32_T c2_i101;
  int32_T c2_i102;
  real_T c2_b_inData[9];
  int32_T c2_i103;
  int32_T c2_i104;
  int32_T c2_i105;
  real_T c2_u[9];
  const mxArray *c2_y = NULL;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i100 = 0;
  for (c2_i101 = 0; c2_i101 < 3; c2_i101++) {
    for (c2_i102 = 0; c2_i102 < 3; c2_i102++) {
      c2_b_inData[c2_i102 + c2_i100] = (*(real_T (*)[9])c2_inData)[c2_i102 +
        c2_i100];
    }

    c2_i100 += 3;
  }

  c2_i103 = 0;
  for (c2_i104 = 0; c2_i104 < 3; c2_i104++) {
    for (c2_i105 = 0; c2_i105 < 3; c2_i105++) {
      c2_u[c2_i105 + c2_i103] = c2_b_inData[c2_i105 + c2_i103];
    }

    c2_i103 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_g_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[9])
{
  real_T c2_dv17[9];
  int32_T c2_i106;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv17, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c2_i106 = 0; c2_i106 < 9; c2_i106++) {
    c2_y[c2_i106] = c2_dv17[c2_i106];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_R2;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[9];
  int32_T c2_i107;
  int32_T c2_i108;
  int32_T c2_i109;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_R2 = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_R2), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_R2);
  c2_i107 = 0;
  for (c2_i108 = 0; c2_i108 < 3; c2_i108++) {
    for (c2_i109 = 0; c2_i109 < 3; c2_i109++) {
      (*(real_T (*)[9])c2_outData)[c2_i109 + c2_i107] = c2_y[c2_i109 + c2_i107];
    }

    c2_i107 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_h_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[11])
{
  real_T c2_dv18[11];
  int32_T c2_i110;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv18, 1, 0, 0U, 1, 0U, 1, 11);
  for (c2_i110 = 0; c2_i110 < 11; c2_i110++) {
    c2_y[c2_i110] = c2_dv18[c2_i110];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_V_in;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[11];
  int32_T c2_i111;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_V_in = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_V_in), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_V_in);
  for (c2_i111 = 0; c2_i111 < 11; c2_i111++) {
    (*(real_T (*)[11])c2_outData)[c2_i111] = c2_y[c2_i111];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  c2_srLgvkCzuuZn3rWrmrpDanB c2_u;
  const mxArray *c2_y = NULL;
  real_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  real_T c2_c_u;
  const mxArray *c2_c_y = NULL;
  real_T c2_d_u;
  const mxArray *c2_d_y = NULL;
  real_T c2_e_u;
  const mxArray *c2_e_y = NULL;
  real_T c2_f_u;
  const mxArray *c2_f_y = NULL;
  real_T c2_g_u;
  const mxArray *c2_g_y = NULL;
  real_T c2_h_u;
  const mxArray *c2_h_y = NULL;
  real_T c2_i_u;
  const mxArray *c2_i_y = NULL;
  real_T c2_j_u;
  const mxArray *c2_j_y = NULL;
  real_T c2_k_u;
  const mxArray *c2_k_y = NULL;
  real_T c2_l_u;
  const mxArray *c2_l_y = NULL;
  real_T c2_m_u;
  const mxArray *c2_m_y = NULL;
  real_T c2_n_u;
  const mxArray *c2_n_y = NULL;
  real_T c2_o_u;
  const mxArray *c2_o_y = NULL;
  real_T c2_p_u;
  const mxArray *c2_p_y = NULL;
  real_T c2_q_u;
  const mxArray *c2_q_y = NULL;
  real_T c2_r_u;
  const mxArray *c2_r_y = NULL;
  real_T c2_s_u;
  const mxArray *c2_s_y = NULL;
  real_T c2_t_u;
  const mxArray *c2_t_y = NULL;
  real_T c2_u_u;
  const mxArray *c2_u_y = NULL;
  real_T c2_v_u;
  const mxArray *c2_v_y = NULL;
  real_T c2_w_u;
  const mxArray *c2_w_y = NULL;
  real_T c2_x_u;
  const mxArray *c2_x_y = NULL;
  real_T c2_y_u;
  const mxArray *c2_y_y = NULL;
  real_T c2_ab_u;
  const mxArray *c2_ab_y = NULL;
  real_T c2_bb_u;
  const mxArray *c2_bb_y = NULL;
  real_T c2_cb_u;
  const mxArray *c2_cb_y = NULL;
  real_T c2_db_u;
  const mxArray *c2_db_y = NULL;
  real_T c2_eb_u;
  const mxArray *c2_eb_y = NULL;
  real_T c2_fb_u;
  const mxArray *c2_fb_y = NULL;
  real_T c2_gb_u;
  const mxArray *c2_gb_y = NULL;
  real_T c2_hb_u;
  const mxArray *c2_hb_y = NULL;
  real_T c2_ib_u;
  const mxArray *c2_ib_y = NULL;
  real_T c2_jb_u;
  const mxArray *c2_jb_y = NULL;
  real_T c2_kb_u;
  const mxArray *c2_kb_y = NULL;
  real_T c2_lb_u;
  const mxArray *c2_lb_y = NULL;
  real_T c2_mb_u;
  const mxArray *c2_mb_y = NULL;
  real_T c2_nb_u;
  const mxArray *c2_nb_y = NULL;
  real_T c2_ob_u;
  const mxArray *c2_ob_y = NULL;
  real_T c2_pb_u;
  const mxArray *c2_pb_y = NULL;
  real_T c2_qb_u;
  const mxArray *c2_qb_y = NULL;
  real_T c2_rb_u;
  const mxArray *c2_rb_y = NULL;
  real_T c2_sb_u;
  const mxArray *c2_sb_y = NULL;
  real_T c2_tb_u;
  const mxArray *c2_tb_y = NULL;
  real_T c2_ub_u;
  const mxArray *c2_ub_y = NULL;
  real_T c2_vb_u;
  const mxArray *c2_vb_y = NULL;
  real_T c2_wb_u;
  const mxArray *c2_wb_y = NULL;
  real_T c2_xb_u;
  const mxArray *c2_xb_y = NULL;
  real_T c2_yb_u;
  const mxArray *c2_yb_y = NULL;
  real_T c2_ac_u;
  const mxArray *c2_ac_y = NULL;
  real_T c2_bc_u;
  const mxArray *c2_bc_y = NULL;
  real_T c2_cc_u;
  const mxArray *c2_cc_y = NULL;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(c2_srLgvkCzuuZn3rWrmrpDanB *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c2_b_u = c2_u.m;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_b_y, "m", "m", 0);
  c2_c_u = c2_u.Ixx;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_c_y, "Ixx", "Ixx", 0);
  c2_d_u = c2_u.Izz;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_d_y, "Izz", "Izz", 0);
  c2_e_u = c2_u.Ixz;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_e_y, "Ixz", "Ixz", 0);
  c2_f_u = c2_u.a11;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_f_y, "a11", "a11", 0);
  c2_g_u = c2_u.a22;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_g_y, "a22", "a22", 0);
  c2_h_u = c2_u.a44;
  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_h_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_h_y, "a44", "a44", 0);
  c2_i_u = c2_u.a66;
  c2_i_y = NULL;
  sf_mex_assign(&c2_i_y, sf_mex_create("y", &c2_i_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_i_y, "a66", "a66", 0);
  c2_j_u = c2_u.a24;
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", &c2_j_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_j_y, "a24", "a24", 0);
  c2_k_u = c2_u.a26;
  c2_k_y = NULL;
  sf_mex_assign(&c2_k_y, sf_mex_create("y", &c2_k_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_k_y, "a26", "a26", 0);
  c2_l_u = c2_u.a46;
  c2_l_y = NULL;
  sf_mex_assign(&c2_l_y, sf_mex_create("y", &c2_l_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_l_y, "a46", "a46", 0);
  c2_m_u = c2_u.vt;
  c2_m_y = NULL;
  sf_mex_assign(&c2_m_y, sf_mex_create("y", &c2_m_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_m_y, "vt", "vt", 0);
  c2_n_u = c2_u.alpha_w;
  c2_n_y = NULL;
  sf_mex_assign(&c2_n_y, sf_mex_create("y", &c2_n_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_n_y, "alpha_w", "alpha_w", 0);
  c2_o_u = c2_u.rho_a;
  c2_o_y = NULL;
  sf_mex_assign(&c2_o_y, sf_mex_create("y", &c2_o_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_o_y, "rho_a", "rho_a", 0);
  c2_p_u = c2_u.As;
  c2_p_y = NULL;
  sf_mex_assign(&c2_p_y, sf_mex_create("y", &c2_p_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_p_y, "As", "As", 0);
  c2_q_u = c2_u.h0;
  c2_q_y = NULL;
  sf_mex_assign(&c2_q_y, sf_mex_create("y", &c2_q_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_q_y, "h0", "h0", 0);
  c2_r_u = c2_u.h1;
  c2_r_y = NULL;
  sf_mex_assign(&c2_r_y, sf_mex_create("y", &c2_r_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_r_y, "h1", "h1", 0);
  c2_s_u = c2_u.z_s;
  c2_s_y = NULL;
  sf_mex_assign(&c2_s_y, sf_mex_create("y", &c2_s_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_s_y, "z_s", "z_s", 0);
  c2_t_u = c2_u.xs;
  c2_t_y = NULL;
  sf_mex_assign(&c2_t_y, sf_mex_create("y", &c2_t_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_t_y, "xs", "xs", 0);
  c2_u_u = c2_u.ys;
  c2_u_y = NULL;
  sf_mex_assign(&c2_u_y, sf_mex_create("y", &c2_u_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_u_y, "ys", "ys", 0);
  c2_v_u = c2_u.zs;
  c2_v_y = NULL;
  sf_mex_assign(&c2_v_y, sf_mex_create("y", &c2_v_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_v_y, "zs", "zs", 0);
  c2_w_u = c2_u.Xce;
  c2_w_y = NULL;
  sf_mex_assign(&c2_w_y, sf_mex_create("y", &c2_w_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_w_y, "Xce", "Xce", 0);
  c2_x_u = c2_u.Xm;
  c2_x_y = NULL;
  sf_mex_assign(&c2_x_y, sf_mex_create("y", &c2_x_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_x_y, "Xm", "Xm", 0);
  c2_y_u = c2_u.rho_w;
  c2_y_y = NULL;
  sf_mex_assign(&c2_y_y, sf_mex_create("y", &c2_y_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_y_y, "rho_w", "rho_w", 0);
  c2_ab_u = c2_u.Ar;
  c2_ab_y = NULL;
  sf_mex_assign(&c2_ab_y, sf_mex_create("y", &c2_ab_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_ab_y, "Ar", "Ar", 0);
  c2_bb_u = c2_u.d_r;
  c2_bb_y = NULL;
  sf_mex_assign(&c2_bb_y, sf_mex_create("y", &c2_bb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_bb_y, "d_r", "d_r", 0);
  c2_cb_u = c2_u.zeta_r;
  c2_cb_y = NULL;
  sf_mex_assign(&c2_cb_y, sf_mex_create("y", &c2_cb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_cb_y, "zeta_r", "zeta_r", 0);
  c2_db_u = c2_u.x_r;
  c2_db_y = NULL;
  sf_mex_assign(&c2_db_y, sf_mex_create("y", &c2_db_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_db_y, "x_r", "x_r", 0);
  c2_eb_u = c2_u.z_r;
  c2_eb_y = NULL;
  sf_mex_assign(&c2_eb_y, sf_mex_create("y", &c2_eb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_eb_y, "z_r", "z_r", 0);
  c2_fb_u = c2_u.xr;
  c2_fb_y = NULL;
  sf_mex_assign(&c2_fb_y, sf_mex_create("y", &c2_fb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_fb_y, "xr", "xr", 0);
  c2_gb_u = c2_u.yr;
  c2_gb_y = NULL;
  sf_mex_assign(&c2_gb_y, sf_mex_create("y", &c2_gb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_gb_y, "yr", "yr", 0);
  c2_hb_u = c2_u.zr;
  c2_hb_y = NULL;
  sf_mex_assign(&c2_hb_y, sf_mex_create("y", &c2_hb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_hb_y, "zr", "zr", 0);
  c2_ib_u = c2_u.Ak;
  c2_ib_y = NULL;
  sf_mex_assign(&c2_ib_y, sf_mex_create("y", &c2_ib_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_ib_y, "Ak", "Ak", 0);
  c2_jb_u = c2_u.d_k;
  c2_jb_y = NULL;
  sf_mex_assign(&c2_jb_y, sf_mex_create("y", &c2_jb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_jb_y, "d_k", "d_k", 0);
  c2_kb_u = c2_u.zeta_k;
  c2_kb_y = NULL;
  sf_mex_assign(&c2_kb_y, sf_mex_create("y", &c2_kb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_kb_y, "zeta_k", "zeta_k", 0);
  c2_lb_u = c2_u.x_k;
  c2_lb_y = NULL;
  sf_mex_assign(&c2_lb_y, sf_mex_create("y", &c2_lb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_lb_y, "x_k", "x_k", 0);
  c2_mb_u = c2_u.z_k;
  c2_mb_y = NULL;
  sf_mex_assign(&c2_mb_y, sf_mex_create("y", &c2_mb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_mb_y, "z_k", "z_k", 0);
  c2_nb_u = c2_u.xk;
  c2_nb_y = NULL;
  sf_mex_assign(&c2_nb_y, sf_mex_create("y", &c2_nb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_nb_y, "xk", "xk", 0);
  c2_ob_u = c2_u.yk;
  c2_ob_y = NULL;
  sf_mex_assign(&c2_ob_y, sf_mex_create("y", &c2_ob_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_ob_y, "yk", "yk", 0);
  c2_pb_u = c2_u.zk;
  c2_pb_y = NULL;
  sf_mex_assign(&c2_pb_y, sf_mex_create("y", &c2_pb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_pb_y, "zk", "zk", 0);
  c2_qb_u = c2_u.x_h;
  c2_qb_y = NULL;
  sf_mex_assign(&c2_qb_y, sf_mex_create("y", &c2_qb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_qb_y, "x_h", "x_h", 0);
  c2_rb_u = c2_u.z_h;
  c2_rb_y = NULL;
  sf_mex_assign(&c2_rb_y, sf_mex_create("y", &c2_rb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_rb_y, "z_h", "z_h", 0);
  c2_sb_u = c2_u.xh;
  c2_sb_y = NULL;
  sf_mex_assign(&c2_sb_y, sf_mex_create("y", &c2_sb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_sb_y, "xh", "xh", 0);
  c2_tb_u = c2_u.yh;
  c2_tb_y = NULL;
  sf_mex_assign(&c2_tb_y, sf_mex_create("y", &c2_tb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_tb_y, "yh", "yh", 0);
  c2_ub_u = c2_u.zh;
  c2_ub_y = NULL;
  sf_mex_assign(&c2_ub_y, sf_mex_create("y", &c2_ub_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_ub_y, "zh", "zh", 0);
  c2_vb_u = c2_u.w_c;
  c2_vb_y = NULL;
  sf_mex_assign(&c2_vb_y, sf_mex_create("y", &c2_vb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_vb_y, "w_c", "w_c", 0);
  c2_wb_u = c2_u.x_c;
  c2_wb_y = NULL;
  sf_mex_assign(&c2_wb_y, sf_mex_create("y", &c2_wb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_wb_y, "x_c", "x_c", 0);
  c2_xb_u = c2_u.y_bm;
  c2_xb_y = NULL;
  sf_mex_assign(&c2_xb_y, sf_mex_create("y", &c2_xb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_xb_y, "y_bm", "y_bm", 0);
  c2_yb_u = c2_u.a;
  c2_yb_y = NULL;
  sf_mex_assign(&c2_yb_y, sf_mex_create("y", &c2_yb_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_yb_y, "a", "a", 0);
  c2_ac_u = c2_u.b;
  c2_ac_y = NULL;
  sf_mex_assign(&c2_ac_y, sf_mex_create("y", &c2_ac_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_ac_y, "b", "b", 0);
  c2_bc_u = c2_u.c;
  c2_bc_y = NULL;
  sf_mex_assign(&c2_bc_y, sf_mex_create("y", &c2_bc_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_bc_y, "c", "c", 0);
  c2_cc_u = c2_u.d;
  c2_cc_y = NULL;
  sf_mex_assign(&c2_cc_y, sf_mex_create("y", &c2_cc_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_cc_y, "d", "d", 0);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_i_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  c2_srLgvkCzuuZn3rWrmrpDanB *c2_y)
{
  emlrtMsgIdentifier c2_thisId;
  static const char * c2_fieldNames[52] = { "m", "Ixx", "Izz", "Ixz", "a11",
    "a22", "a44", "a66", "a24", "a26", "a46", "vt", "alpha_w", "rho_a", "As",
    "h0", "h1", "z_s", "xs", "ys", "zs", "Xce", "Xm", "rho_w", "Ar", "d_r",
    "zeta_r", "x_r", "z_r", "xr", "yr", "zr", "Ak", "d_k", "zeta_k", "x_k",
    "z_k", "xk", "yk", "zk", "x_h", "z_h", "xh", "yh", "zh", "w_c", "x_c",
    "y_bm", "a", "b", "c", "d" };

  c2_thisId.fParent = c2_parentId;
  sf_mex_check_struct(c2_parentId, c2_u, 52, c2_fieldNames, 0U, NULL);
  c2_thisId.fIdentifier = "m";
  c2_y->m = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u,
    "m", "m", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Ixx";
  c2_y->Ixx = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "Ixx", "Ixx", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Izz";
  c2_y->Izz = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "Izz", "Izz", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Ixz";
  c2_y->Ixz = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "Ixz", "Ixz", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "a11";
  c2_y->a11 = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "a11", "a11", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "a22";
  c2_y->a22 = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "a22", "a22", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "a44";
  c2_y->a44 = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "a44", "a44", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "a66";
  c2_y->a66 = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "a66", "a66", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "a24";
  c2_y->a24 = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "a24", "a24", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "a26";
  c2_y->a26 = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "a26", "a26", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "a46";
  c2_y->a46 = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "a46", "a46", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "vt";
  c2_y->vt = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "vt", "vt", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "alpha_w";
  c2_y->alpha_w = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_u, "alpha_w", "alpha_w", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "rho_a";
  c2_y->rho_a = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "rho_a", "rho_a", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "As";
  c2_y->As = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "As", "As", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "h0";
  c2_y->h0 = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "h0", "h0", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "h1";
  c2_y->h1 = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "h1", "h1", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "z_s";
  c2_y->z_s = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "z_s", "z_s", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "xs";
  c2_y->xs = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "xs", "xs", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "ys";
  c2_y->ys = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "ys", "ys", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "zs";
  c2_y->zs = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "zs", "zs", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Xce";
  c2_y->Xce = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "Xce", "Xce", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Xm";
  c2_y->Xm = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "Xm", "Xm", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "rho_w";
  c2_y->rho_w = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "rho_w", "rho_w", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Ar";
  c2_y->Ar = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "Ar", "Ar", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "d_r";
  c2_y->d_r = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "d_r", "d_r", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "zeta_r";
  c2_y->zeta_r = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
                                        (c2_u, "zeta_r", "zeta_r", 0)),
    &c2_thisId);
  c2_thisId.fIdentifier = "x_r";
  c2_y->x_r = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "x_r", "x_r", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "z_r";
  c2_y->z_r = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "z_r", "z_r", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "xr";
  c2_y->xr = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "xr", "xr", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "yr";
  c2_y->yr = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "yr", "yr", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "zr";
  c2_y->zr = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "zr", "zr", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "Ak";
  c2_y->Ak = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "Ak", "Ak", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "d_k";
  c2_y->d_k = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "d_k", "d_k", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "zeta_k";
  c2_y->zeta_k = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
                                        (c2_u, "zeta_k", "zeta_k", 0)),
    &c2_thisId);
  c2_thisId.fIdentifier = "x_k";
  c2_y->x_k = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "x_k", "x_k", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "z_k";
  c2_y->z_k = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "z_k", "z_k", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "xk";
  c2_y->xk = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "xk", "xk", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "yk";
  c2_y->yk = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "yk", "yk", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "zk";
  c2_y->zk = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "zk", "zk", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "x_h";
  c2_y->x_h = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "x_h", "x_h", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "z_h";
  c2_y->z_h = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "z_h", "z_h", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "xh";
  c2_y->xh = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "xh", "xh", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "yh";
  c2_y->yh = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "yh", "yh", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "zh";
  c2_y->zh = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "zh", "zh", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "w_c";
  c2_y->w_c = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "w_c", "w_c", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "x_c";
  c2_y->x_c = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "x_c", "x_c", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "y_bm";
  c2_y->y_bm = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "y_bm", "y_bm", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "a";
  c2_y->a = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u,
    "a", "a", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "b";
  c2_y->b = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u,
    "b", "b", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "c";
  c2_y->c = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u,
    "c", "c", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "d";
  c2_y->d = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u,
    "d", "d", 0)), &c2_thisId);
  sf_mex_destroy(&c2_u);
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_par;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  c2_srLgvkCzuuZn3rWrmrpDanB c2_y;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_par = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_par), &c2_thisId, &c2_y);
  sf_mex_destroy(&c2_par);
  *(c2_srLgvkCzuuZn3rWrmrpDanB *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_SailingYachtModel2_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 170, 1),
                false);
  c2_info_helper(&c2_nameCaptureInfo);
  c2_b_info_helper(&c2_nameCaptureInfo);
  c2_c_info_helper(&c2_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs0 = NULL;
  const mxArray *c2_lhs0 = NULL;
  const mxArray *c2_rhs1 = NULL;
  const mxArray *c2_lhs1 = NULL;
  const mxArray *c2_rhs2 = NULL;
  const mxArray *c2_lhs2 = NULL;
  const mxArray *c2_rhs3 = NULL;
  const mxArray *c2_lhs3 = NULL;
  const mxArray *c2_rhs4 = NULL;
  const mxArray *c2_lhs4 = NULL;
  const mxArray *c2_rhs5 = NULL;
  const mxArray *c2_lhs5 = NULL;
  const mxArray *c2_rhs6 = NULL;
  const mxArray *c2_lhs6 = NULL;
  const mxArray *c2_rhs7 = NULL;
  const mxArray *c2_lhs7 = NULL;
  const mxArray *c2_rhs8 = NULL;
  const mxArray *c2_lhs8 = NULL;
  const mxArray *c2_rhs9 = NULL;
  const mxArray *c2_lhs9 = NULL;
  const mxArray *c2_rhs10 = NULL;
  const mxArray *c2_lhs10 = NULL;
  const mxArray *c2_rhs11 = NULL;
  const mxArray *c2_lhs11 = NULL;
  const mxArray *c2_rhs12 = NULL;
  const mxArray *c2_lhs12 = NULL;
  const mxArray *c2_rhs13 = NULL;
  const mxArray *c2_lhs13 = NULL;
  const mxArray *c2_rhs14 = NULL;
  const mxArray *c2_lhs14 = NULL;
  const mxArray *c2_rhs15 = NULL;
  const mxArray *c2_lhs15 = NULL;
  const mxArray *c2_rhs16 = NULL;
  const mxArray *c2_lhs16 = NULL;
  const mxArray *c2_rhs17 = NULL;
  const mxArray *c2_lhs17 = NULL;
  const mxArray *c2_rhs18 = NULL;
  const mxArray *c2_lhs18 = NULL;
  const mxArray *c2_rhs19 = NULL;
  const mxArray *c2_lhs19 = NULL;
  const mxArray *c2_rhs20 = NULL;
  const mxArray *c2_lhs20 = NULL;
  const mxArray *c2_rhs21 = NULL;
  const mxArray *c2_lhs21 = NULL;
  const mxArray *c2_rhs22 = NULL;
  const mxArray *c2_lhs22 = NULL;
  const mxArray *c2_rhs23 = NULL;
  const mxArray *c2_lhs23 = NULL;
  const mxArray *c2_rhs24 = NULL;
  const mxArray *c2_lhs24 = NULL;
  const mxArray *c2_rhs25 = NULL;
  const mxArray *c2_lhs25 = NULL;
  const mxArray *c2_rhs26 = NULL;
  const mxArray *c2_lhs26 = NULL;
  const mxArray *c2_rhs27 = NULL;
  const mxArray *c2_lhs27 = NULL;
  const mxArray *c2_rhs28 = NULL;
  const mxArray *c2_lhs28 = NULL;
  const mxArray *c2_rhs29 = NULL;
  const mxArray *c2_lhs29 = NULL;
  const mxArray *c2_rhs30 = NULL;
  const mxArray *c2_lhs30 = NULL;
  const mxArray *c2_rhs31 = NULL;
  const mxArray *c2_lhs31 = NULL;
  const mxArray *c2_rhs32 = NULL;
  const mxArray *c2_lhs32 = NULL;
  const mxArray *c2_rhs33 = NULL;
  const mxArray *c2_lhs33 = NULL;
  const mxArray *c2_rhs34 = NULL;
  const mxArray *c2_lhs34 = NULL;
  const mxArray *c2_rhs35 = NULL;
  const mxArray *c2_lhs35 = NULL;
  const mxArray *c2_rhs36 = NULL;
  const mxArray *c2_lhs36 = NULL;
  const mxArray *c2_rhs37 = NULL;
  const mxArray *c2_lhs37 = NULL;
  const mxArray *c2_rhs38 = NULL;
  const mxArray *c2_lhs38 = NULL;
  const mxArray *c2_rhs39 = NULL;
  const mxArray *c2_lhs39 = NULL;
  const mxArray *c2_rhs40 = NULL;
  const mxArray *c2_lhs40 = NULL;
  const mxArray *c2_rhs41 = NULL;
  const mxArray *c2_lhs41 = NULL;
  const mxArray *c2_rhs42 = NULL;
  const mxArray *c2_lhs42 = NULL;
  const mxArray *c2_rhs43 = NULL;
  const mxArray *c2_lhs43 = NULL;
  const mxArray *c2_rhs44 = NULL;
  const mxArray *c2_lhs44 = NULL;
  const mxArray *c2_rhs45 = NULL;
  const mxArray *c2_lhs45 = NULL;
  const mxArray *c2_rhs46 = NULL;
  const mxArray *c2_lhs46 = NULL;
  const mxArray *c2_rhs47 = NULL;
  const mxArray *c2_lhs47 = NULL;
  const mxArray *c2_rhs48 = NULL;
  const mxArray *c2_lhs48 = NULL;
  const mxArray *c2_rhs49 = NULL;
  const mxArray *c2_lhs49 = NULL;
  const mxArray *c2_rhs50 = NULL;
  const mxArray *c2_lhs50 = NULL;
  const mxArray *c2_rhs51 = NULL;
  const mxArray *c2_lhs51 = NULL;
  const mxArray *c2_rhs52 = NULL;
  const mxArray *c2_lhs52 = NULL;
  const mxArray *c2_rhs53 = NULL;
  const mxArray *c2_lhs53 = NULL;
  const mxArray *c2_rhs54 = NULL;
  const mxArray *c2_lhs54 = NULL;
  const mxArray *c2_rhs55 = NULL;
  const mxArray *c2_lhs55 = NULL;
  const mxArray *c2_rhs56 = NULL;
  const mxArray *c2_lhs56 = NULL;
  const mxArray *c2_rhs57 = NULL;
  const mxArray *c2_lhs57 = NULL;
  const mxArray *c2_rhs58 = NULL;
  const mxArray *c2_lhs58 = NULL;
  const mxArray *c2_rhs59 = NULL;
  const mxArray *c2_lhs59 = NULL;
  const mxArray *c2_rhs60 = NULL;
  const mxArray *c2_lhs60 = NULL;
  const mxArray *c2_rhs61 = NULL;
  const mxArray *c2_lhs61 = NULL;
  const mxArray *c2_rhs62 = NULL;
  const mxArray *c2_lhs62 = NULL;
  const mxArray *c2_rhs63 = NULL;
  const mxArray *c2_lhs63 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("modeleBoat"), "name", "name",
                  0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[E]/home/paul/KTH/Optimal Control/BottleBoat/Simulink/modeleBoat.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1430582785U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c2_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("cos"), "name", "name", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c2_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_cos"), "name",
                  "name", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818722U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c2_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("sin"), "name", "name", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c2_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818736U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c2_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c2_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c2_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818712U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c2_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mrdivide"), "name", "name", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c2_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c2_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("rdivide"), "name", "name", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c2_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c2_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c2_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_div"), "name", "name", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c2_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c2_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("log"), "name", "name", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log.m"), "resolved",
                  "resolved", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830380U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c2_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log.m"), "context",
                  "context", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_error"), "name", "name",
                  16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830358U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c2_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log.m"), "context",
                  "context", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_log"), "name",
                  "name", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818728U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c2_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log.m"),
                  "context", "context", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("realmax"), "name", "name", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m"), "resolved",
                  "resolved", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1307651242U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c2_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_realmax"), "name", "name",
                  19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c2_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c2_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log.m"),
                  "context", "context", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mrdivide"), "name", "name", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c2_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c2_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c2_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c2_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c2_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c2_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xgemm"), "name", "name",
                  27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c2_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c2_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c2_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c2_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c2_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c2_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c2_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xgemm"),
                  "name", "name", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c2_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("cross"), "name", "name", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m"), "resolved",
                  "resolved", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818842U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c2_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("atan2"), "name", "name", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "resolved",
                  "resolved", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830372U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c2_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c2_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c2_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c2_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m"), "context",
                  "context", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_atan2"), "name",
                  "name", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m"),
                  "resolved", "resolved", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818720U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c2_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mpower"), "name", "name", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713878U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c2_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c2_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("ismatrix"), "name", "name", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1331304858U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c2_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("power"), "name", "name", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c2_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c2_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c2_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c2_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c2_rhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c2_rhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c2_rhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c2_rhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("sqrt"), "name", "name", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "resolved",
                  "resolved", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830386U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c2_rhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_error"), "name", "name",
                  53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1343830358U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c2_rhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m"), "context",
                  "context", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_sqrt"), "name",
                  "name", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m"),
                  "resolved", "resolved", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818738U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c2_rhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs54), "lhs", "lhs",
                  54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mldivide"), "name", "name", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p"), "resolved",
                  "resolved", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1319729966U), "mFileTimeLo",
                  "mFileTimeLo", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 55);
  sf_mex_assign(&c2_rhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs55), "rhs", "rhs",
                  55);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs55), "lhs", "lhs",
                  55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p"), "context",
                  "context", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_lusolve"), "name", "name",
                  56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m"), "resolved",
                  "resolved", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370009886U), "fileTimeLo",
                  "fileTimeLo", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 56);
  sf_mex_assign(&c2_rhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs56), "rhs", "rhs",
                  56);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs56), "lhs", "lhs",
                  56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN"),
                  "context", "context", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xgetrf"), "name", "name",
                  57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m"),
                  "resolved", "resolved", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818806U), "fileTimeLo",
                  "fileTimeLo", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 57);
  sf_mex_assign(&c2_rhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs57), "rhs", "rhs",
                  57);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs57), "lhs", "lhs",
                  57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m"),
                  "context", "context", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_lapack_xgetrf"), "name",
                  "name", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m"),
                  "resolved", "resolved", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818810U), "fileTimeLo",
                  "fileTimeLo", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 58);
  sf_mex_assign(&c2_rhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs58), "rhs", "rhs",
                  58);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs58), "lhs", "lhs",
                  58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m"),
                  "context", "context", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_matlab_zgetrf"), "name",
                  "name", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "resolved", "resolved", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1302688994U), "fileTimeLo",
                  "fileTimeLo", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 59);
  sf_mex_assign(&c2_rhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs59), "rhs", "rhs",
                  59);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs59), "lhs", "lhs",
                  59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("realmin"), "name", "name", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "resolved",
                  "resolved", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1307651242U), "fileTimeLo",
                  "fileTimeLo", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 60);
  sf_mex_assign(&c2_rhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs60), "rhs", "rhs",
                  60);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs60), "lhs", "lhs",
                  60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m"), "context",
                  "context", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_realmin"), "name", "name",
                  61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "resolved",
                  "resolved", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1307651244U), "fileTimeLo",
                  "fileTimeLo", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 61);
  sf_mex_assign(&c2_rhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs61), "rhs", "rhs",
                  61);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs61), "lhs", "lhs",
                  61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "context",
                  "context", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 62);
  sf_mex_assign(&c2_rhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs62), "rhs", "rhs",
                  62);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs62), "lhs", "lhs",
                  62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eps"), "name", "name", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 63);
  sf_mex_assign(&c2_rhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs63), "rhs", "rhs",
                  63);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs63), "lhs", "lhs",
                  63);
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
  sf_mex_destroy(&c2_rhs1);
  sf_mex_destroy(&c2_lhs1);
  sf_mex_destroy(&c2_rhs2);
  sf_mex_destroy(&c2_lhs2);
  sf_mex_destroy(&c2_rhs3);
  sf_mex_destroy(&c2_lhs3);
  sf_mex_destroy(&c2_rhs4);
  sf_mex_destroy(&c2_lhs4);
  sf_mex_destroy(&c2_rhs5);
  sf_mex_destroy(&c2_lhs5);
  sf_mex_destroy(&c2_rhs6);
  sf_mex_destroy(&c2_lhs6);
  sf_mex_destroy(&c2_rhs7);
  sf_mex_destroy(&c2_lhs7);
  sf_mex_destroy(&c2_rhs8);
  sf_mex_destroy(&c2_lhs8);
  sf_mex_destroy(&c2_rhs9);
  sf_mex_destroy(&c2_lhs9);
  sf_mex_destroy(&c2_rhs10);
  sf_mex_destroy(&c2_lhs10);
  sf_mex_destroy(&c2_rhs11);
  sf_mex_destroy(&c2_lhs11);
  sf_mex_destroy(&c2_rhs12);
  sf_mex_destroy(&c2_lhs12);
  sf_mex_destroy(&c2_rhs13);
  sf_mex_destroy(&c2_lhs13);
  sf_mex_destroy(&c2_rhs14);
  sf_mex_destroy(&c2_lhs14);
  sf_mex_destroy(&c2_rhs15);
  sf_mex_destroy(&c2_lhs15);
  sf_mex_destroy(&c2_rhs16);
  sf_mex_destroy(&c2_lhs16);
  sf_mex_destroy(&c2_rhs17);
  sf_mex_destroy(&c2_lhs17);
  sf_mex_destroy(&c2_rhs18);
  sf_mex_destroy(&c2_lhs18);
  sf_mex_destroy(&c2_rhs19);
  sf_mex_destroy(&c2_lhs19);
  sf_mex_destroy(&c2_rhs20);
  sf_mex_destroy(&c2_lhs20);
  sf_mex_destroy(&c2_rhs21);
  sf_mex_destroy(&c2_lhs21);
  sf_mex_destroy(&c2_rhs22);
  sf_mex_destroy(&c2_lhs22);
  sf_mex_destroy(&c2_rhs23);
  sf_mex_destroy(&c2_lhs23);
  sf_mex_destroy(&c2_rhs24);
  sf_mex_destroy(&c2_lhs24);
  sf_mex_destroy(&c2_rhs25);
  sf_mex_destroy(&c2_lhs25);
  sf_mex_destroy(&c2_rhs26);
  sf_mex_destroy(&c2_lhs26);
  sf_mex_destroy(&c2_rhs27);
  sf_mex_destroy(&c2_lhs27);
  sf_mex_destroy(&c2_rhs28);
  sf_mex_destroy(&c2_lhs28);
  sf_mex_destroy(&c2_rhs29);
  sf_mex_destroy(&c2_lhs29);
  sf_mex_destroy(&c2_rhs30);
  sf_mex_destroy(&c2_lhs30);
  sf_mex_destroy(&c2_rhs31);
  sf_mex_destroy(&c2_lhs31);
  sf_mex_destroy(&c2_rhs32);
  sf_mex_destroy(&c2_lhs32);
  sf_mex_destroy(&c2_rhs33);
  sf_mex_destroy(&c2_lhs33);
  sf_mex_destroy(&c2_rhs34);
  sf_mex_destroy(&c2_lhs34);
  sf_mex_destroy(&c2_rhs35);
  sf_mex_destroy(&c2_lhs35);
  sf_mex_destroy(&c2_rhs36);
  sf_mex_destroy(&c2_lhs36);
  sf_mex_destroy(&c2_rhs37);
  sf_mex_destroy(&c2_lhs37);
  sf_mex_destroy(&c2_rhs38);
  sf_mex_destroy(&c2_lhs38);
  sf_mex_destroy(&c2_rhs39);
  sf_mex_destroy(&c2_lhs39);
  sf_mex_destroy(&c2_rhs40);
  sf_mex_destroy(&c2_lhs40);
  sf_mex_destroy(&c2_rhs41);
  sf_mex_destroy(&c2_lhs41);
  sf_mex_destroy(&c2_rhs42);
  sf_mex_destroy(&c2_lhs42);
  sf_mex_destroy(&c2_rhs43);
  sf_mex_destroy(&c2_lhs43);
  sf_mex_destroy(&c2_rhs44);
  sf_mex_destroy(&c2_lhs44);
  sf_mex_destroy(&c2_rhs45);
  sf_mex_destroy(&c2_lhs45);
  sf_mex_destroy(&c2_rhs46);
  sf_mex_destroy(&c2_lhs46);
  sf_mex_destroy(&c2_rhs47);
  sf_mex_destroy(&c2_lhs47);
  sf_mex_destroy(&c2_rhs48);
  sf_mex_destroy(&c2_lhs48);
  sf_mex_destroy(&c2_rhs49);
  sf_mex_destroy(&c2_lhs49);
  sf_mex_destroy(&c2_rhs50);
  sf_mex_destroy(&c2_lhs50);
  sf_mex_destroy(&c2_rhs51);
  sf_mex_destroy(&c2_lhs51);
  sf_mex_destroy(&c2_rhs52);
  sf_mex_destroy(&c2_lhs52);
  sf_mex_destroy(&c2_rhs53);
  sf_mex_destroy(&c2_lhs53);
  sf_mex_destroy(&c2_rhs54);
  sf_mex_destroy(&c2_lhs54);
  sf_mex_destroy(&c2_rhs55);
  sf_mex_destroy(&c2_lhs55);
  sf_mex_destroy(&c2_rhs56);
  sf_mex_destroy(&c2_lhs56);
  sf_mex_destroy(&c2_rhs57);
  sf_mex_destroy(&c2_lhs57);
  sf_mex_destroy(&c2_rhs58);
  sf_mex_destroy(&c2_lhs58);
  sf_mex_destroy(&c2_rhs59);
  sf_mex_destroy(&c2_lhs59);
  sf_mex_destroy(&c2_rhs60);
  sf_mex_destroy(&c2_lhs60);
  sf_mex_destroy(&c2_rhs61);
  sf_mex_destroy(&c2_lhs61);
  sf_mex_destroy(&c2_rhs62);
  sf_mex_destroy(&c2_lhs62);
  sf_mex_destroy(&c2_rhs63);
  sf_mex_destroy(&c2_lhs63);
}

static const mxArray *c2_emlrt_marshallOut(const char * c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c2_u)), false);
  return c2_y;
}

static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 7, 0U, 0U, 0U, 0), false);
  return c2_y;
}

static void c2_b_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs64 = NULL;
  const mxArray *c2_lhs64 = NULL;
  const mxArray *c2_rhs65 = NULL;
  const mxArray *c2_lhs65 = NULL;
  const mxArray *c2_rhs66 = NULL;
  const mxArray *c2_lhs66 = NULL;
  const mxArray *c2_rhs67 = NULL;
  const mxArray *c2_lhs67 = NULL;
  const mxArray *c2_rhs68 = NULL;
  const mxArray *c2_lhs68 = NULL;
  const mxArray *c2_rhs69 = NULL;
  const mxArray *c2_lhs69 = NULL;
  const mxArray *c2_rhs70 = NULL;
  const mxArray *c2_lhs70 = NULL;
  const mxArray *c2_rhs71 = NULL;
  const mxArray *c2_lhs71 = NULL;
  const mxArray *c2_rhs72 = NULL;
  const mxArray *c2_lhs72 = NULL;
  const mxArray *c2_rhs73 = NULL;
  const mxArray *c2_lhs73 = NULL;
  const mxArray *c2_rhs74 = NULL;
  const mxArray *c2_lhs74 = NULL;
  const mxArray *c2_rhs75 = NULL;
  const mxArray *c2_lhs75 = NULL;
  const mxArray *c2_rhs76 = NULL;
  const mxArray *c2_lhs76 = NULL;
  const mxArray *c2_rhs77 = NULL;
  const mxArray *c2_lhs77 = NULL;
  const mxArray *c2_rhs78 = NULL;
  const mxArray *c2_lhs78 = NULL;
  const mxArray *c2_rhs79 = NULL;
  const mxArray *c2_lhs79 = NULL;
  const mxArray *c2_rhs80 = NULL;
  const mxArray *c2_lhs80 = NULL;
  const mxArray *c2_rhs81 = NULL;
  const mxArray *c2_lhs81 = NULL;
  const mxArray *c2_rhs82 = NULL;
  const mxArray *c2_lhs82 = NULL;
  const mxArray *c2_rhs83 = NULL;
  const mxArray *c2_lhs83 = NULL;
  const mxArray *c2_rhs84 = NULL;
  const mxArray *c2_lhs84 = NULL;
  const mxArray *c2_rhs85 = NULL;
  const mxArray *c2_lhs85 = NULL;
  const mxArray *c2_rhs86 = NULL;
  const mxArray *c2_lhs86 = NULL;
  const mxArray *c2_rhs87 = NULL;
  const mxArray *c2_lhs87 = NULL;
  const mxArray *c2_rhs88 = NULL;
  const mxArray *c2_lhs88 = NULL;
  const mxArray *c2_rhs89 = NULL;
  const mxArray *c2_lhs89 = NULL;
  const mxArray *c2_rhs90 = NULL;
  const mxArray *c2_lhs90 = NULL;
  const mxArray *c2_rhs91 = NULL;
  const mxArray *c2_lhs91 = NULL;
  const mxArray *c2_rhs92 = NULL;
  const mxArray *c2_lhs92 = NULL;
  const mxArray *c2_rhs93 = NULL;
  const mxArray *c2_lhs93 = NULL;
  const mxArray *c2_rhs94 = NULL;
  const mxArray *c2_lhs94 = NULL;
  const mxArray *c2_rhs95 = NULL;
  const mxArray *c2_lhs95 = NULL;
  const mxArray *c2_rhs96 = NULL;
  const mxArray *c2_lhs96 = NULL;
  const mxArray *c2_rhs97 = NULL;
  const mxArray *c2_lhs97 = NULL;
  const mxArray *c2_rhs98 = NULL;
  const mxArray *c2_lhs98 = NULL;
  const mxArray *c2_rhs99 = NULL;
  const mxArray *c2_lhs99 = NULL;
  const mxArray *c2_rhs100 = NULL;
  const mxArray *c2_lhs100 = NULL;
  const mxArray *c2_rhs101 = NULL;
  const mxArray *c2_lhs101 = NULL;
  const mxArray *c2_rhs102 = NULL;
  const mxArray *c2_lhs102 = NULL;
  const mxArray *c2_rhs103 = NULL;
  const mxArray *c2_lhs103 = NULL;
  const mxArray *c2_rhs104 = NULL;
  const mxArray *c2_lhs104 = NULL;
  const mxArray *c2_rhs105 = NULL;
  const mxArray *c2_lhs105 = NULL;
  const mxArray *c2_rhs106 = NULL;
  const mxArray *c2_lhs106 = NULL;
  const mxArray *c2_rhs107 = NULL;
  const mxArray *c2_lhs107 = NULL;
  const mxArray *c2_rhs108 = NULL;
  const mxArray *c2_lhs108 = NULL;
  const mxArray *c2_rhs109 = NULL;
  const mxArray *c2_lhs109 = NULL;
  const mxArray *c2_rhs110 = NULL;
  const mxArray *c2_lhs110 = NULL;
  const mxArray *c2_rhs111 = NULL;
  const mxArray *c2_lhs111 = NULL;
  const mxArray *c2_rhs112 = NULL;
  const mxArray *c2_lhs112 = NULL;
  const mxArray *c2_rhs113 = NULL;
  const mxArray *c2_lhs113 = NULL;
  const mxArray *c2_rhs114 = NULL;
  const mxArray *c2_lhs114 = NULL;
  const mxArray *c2_rhs115 = NULL;
  const mxArray *c2_lhs115 = NULL;
  const mxArray *c2_rhs116 = NULL;
  const mxArray *c2_lhs116 = NULL;
  const mxArray *c2_rhs117 = NULL;
  const mxArray *c2_lhs117 = NULL;
  const mxArray *c2_rhs118 = NULL;
  const mxArray *c2_lhs118 = NULL;
  const mxArray *c2_rhs119 = NULL;
  const mxArray *c2_lhs119 = NULL;
  const mxArray *c2_rhs120 = NULL;
  const mxArray *c2_lhs120 = NULL;
  const mxArray *c2_rhs121 = NULL;
  const mxArray *c2_lhs121 = NULL;
  const mxArray *c2_rhs122 = NULL;
  const mxArray *c2_lhs122 = NULL;
  const mxArray *c2_rhs123 = NULL;
  const mxArray *c2_lhs123 = NULL;
  const mxArray *c2_rhs124 = NULL;
  const mxArray *c2_lhs124 = NULL;
  const mxArray *c2_rhs125 = NULL;
  const mxArray *c2_lhs125 = NULL;
  const mxArray *c2_rhs126 = NULL;
  const mxArray *c2_lhs126 = NULL;
  const mxArray *c2_rhs127 = NULL;
  const mxArray *c2_lhs127 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_is_float_class"), "name",
                  "name", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m"),
                  "resolved", "resolved", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818782U), "fileTimeLo",
                  "fileTimeLo", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 64);
  sf_mex_assign(&c2_rhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs64), "rhs", "rhs",
                  64);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs64), "lhs", "lhs",
                  64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_eps"), "name", "name", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "resolved",
                  "resolved", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 65);
  sf_mex_assign(&c2_rhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs65), "rhs", "rhs",
                  65);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs65), "lhs", "lhs",
                  65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "context",
                  "context", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326727996U), "fileTimeLo",
                  "fileTimeLo", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 66);
  sf_mex_assign(&c2_rhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs66), "rhs", "rhs",
                  66);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs66), "lhs", "lhs",
                  66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311255318U), "fileTimeLo",
                  "fileTimeLo", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 67);
  sf_mex_assign(&c2_rhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs67), "rhs", "rhs",
                  67);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs67), "lhs", "lhs",
                  67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378295984U), "fileTimeLo",
                  "fileTimeLo", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 68);
  sf_mex_assign(&c2_rhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs68), "rhs", "rhs",
                  68);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs68), "lhs", "lhs",
                  68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 69);
  sf_mex_assign(&c2_rhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs69), "rhs", "rhs",
                  69);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs69), "lhs", "lhs",
                  69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 70);
  sf_mex_assign(&c2_rhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs70), "rhs", "rhs",
                  70);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs70), "lhs", "lhs",
                  70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 71);
  sf_mex_assign(&c2_rhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs71), "rhs", "rhs",
                  71);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs71), "lhs", "lhs",
                  71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 72);
  sf_mex_assign(&c2_rhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs72), "rhs", "rhs",
                  72);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs72), "lhs", "lhs",
                  72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 73);
  sf_mex_assign(&c2_rhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs73), "rhs", "rhs",
                  73);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs73), "lhs", "lhs",
                  73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 74);
  sf_mex_assign(&c2_rhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs74), "rhs", "rhs",
                  74);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs74), "lhs", "lhs",
                  74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 75);
  sf_mex_assign(&c2_rhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs75), "rhs", "rhs",
                  75);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs75), "lhs", "lhs",
                  75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("colon"), "name", "name", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378295988U), "fileTimeLo",
                  "fileTimeLo", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 76);
  sf_mex_assign(&c2_rhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs76), "rhs", "rhs",
                  76);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs76), "lhs", "lhs",
                  76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("colon"), "name", "name", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378295988U), "fileTimeLo",
                  "fileTimeLo", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 77);
  sf_mex_assign(&c2_rhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs77), "rhs", "rhs",
                  77);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs77), "lhs", "lhs",
                  77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 78);
  sf_mex_assign(&c2_rhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs78), "rhs", "rhs",
                  78);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs78), "lhs", "lhs",
                  78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 79);
  sf_mex_assign(&c2_rhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs79), "rhs", "rhs",
                  79);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs79), "lhs", "lhs",
                  79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 80);
  sf_mex_assign(&c2_rhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs80), "rhs", "rhs",
                  80);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs80), "lhs", "lhs",
                  80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 81);
  sf_mex_assign(&c2_rhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs81), "rhs", "rhs",
                  81);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs81), "lhs", "lhs",
                  81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 82);
  sf_mex_assign(&c2_rhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs82), "rhs", "rhs",
                  82);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs82), "lhs", "lhs",
                  82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 83);
  sf_mex_assign(&c2_rhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs83), "rhs", "rhs",
                  83);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs83), "lhs", "lhs",
                  83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 84);
  sf_mex_assign(&c2_rhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs84), "rhs", "rhs",
                  84);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs84), "lhs", "lhs",
                  84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 85);
  sf_mex_assign(&c2_rhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs85), "rhs", "rhs",
                  85);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs85), "lhs", "lhs",
                  85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 86);
  sf_mex_assign(&c2_rhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs86), "rhs", "rhs",
                  86);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs86), "lhs", "lhs",
                  86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 87);
  sf_mex_assign(&c2_rhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs87), "rhs", "rhs",
                  87);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs87), "lhs", "lhs",
                  87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "context",
                  "context", 88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.isaUint"),
                  "name", "name", 88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/isaUint.p"),
                  "resolved", "resolved", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 88);
  sf_mex_assign(&c2_rhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs88), "rhs", "rhs",
                  88);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs88), "lhs", "lhs",
                  88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_unsigned_class"), "name",
                  "name", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "resolved", "resolved", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 89);
  sf_mex_assign(&c2_rhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs89), "rhs", "rhs",
                  89);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs89), "lhs", "lhs",
                  89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "context", "context", 90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.unsignedClass"),
                  "name", "name", 90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "resolved", "resolved", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 90);
  sf_mex_assign(&c2_rhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs90), "rhs", "rhs",
                  90);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs90), "lhs", "lhs",
                  90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "context", "context", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 91);
  sf_mex_assign(&c2_rhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs91), "rhs", "rhs",
                  91);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs91), "lhs", "lhs",
                  91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "context", "context", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 92);
  sf_mex_assign(&c2_rhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs92), "rhs", "rhs",
                  92);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs92), "lhs", "lhs",
                  92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 93);
  sf_mex_assign(&c2_rhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs93), "rhs", "rhs",
                  93);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs93), "lhs", "lhs",
                  93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 94);
  sf_mex_assign(&c2_rhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs94), "rhs", "rhs",
                  94);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs94), "lhs", "lhs",
                  94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 95);
  sf_mex_assign(&c2_rhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs95), "rhs", "rhs",
                  95);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs95), "lhs", "lhs",
                  95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 96);
  sf_mex_assign(&c2_rhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs96), "rhs", "rhs",
                  96);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs96), "lhs", "lhs",
                  96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 97);
  sf_mex_assign(&c2_rhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs97), "rhs", "rhs",
                  97);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs97), "lhs", "lhs",
                  97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_signed_integer_colon"),
                  "context", "context", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 98);
  sf_mex_assign(&c2_rhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs98), "rhs", "rhs",
                  98);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs98), "lhs", "lhs",
                  98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 99);
  sf_mex_assign(&c2_rhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs99), "rhs", "rhs",
                  99);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs99), "lhs", "lhs",
                  99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 100);
  sf_mex_assign(&c2_rhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs100), "rhs", "rhs",
                  100);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs100), "lhs", "lhs",
                  100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 101);
  sf_mex_assign(&c2_rhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs101), "rhs", "rhs",
                  101);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs101), "lhs", "lhs",
                  101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 102);
  sf_mex_assign(&c2_rhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs102), "rhs", "rhs",
                  102);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs102), "lhs", "lhs",
                  102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 103);
  sf_mex_assign(&c2_rhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs103), "rhs", "rhs",
                  103);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs103), "lhs", "lhs",
                  103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 104);
  sf_mex_assign(&c2_rhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs104), "rhs", "rhs",
                  104);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs104), "lhs", "lhs",
                  104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 105);
  sf_mex_assign(&c2_rhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs105), "rhs", "rhs",
                  105);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs105), "lhs", "lhs",
                  105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 106);
  sf_mex_assign(&c2_rhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs106), "rhs", "rhs",
                  106);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs106), "lhs", "lhs",
                  106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 107);
  sf_mex_assign(&c2_rhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs107), "rhs", "rhs",
                  107);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs107), "lhs", "lhs",
                  107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "context", "context", 108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 108);
  sf_mex_assign(&c2_rhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs108), "rhs", "rhs",
                  108);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs108), "lhs", "lhs",
                  108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 109);
  sf_mex_assign(&c2_rhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs109), "rhs", "rhs",
                  109);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs109), "lhs", "lhs",
                  109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 110);
  sf_mex_assign(&c2_rhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs110), "rhs", "rhs",
                  110);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs110), "lhs", "lhs",
                  110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_ixamax"), "name", "name",
                  111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "resolved", "resolved", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 111);
  sf_mex_assign(&c2_rhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs111), "rhs", "rhs",
                  111);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs111), "lhs", "lhs",
                  111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "context", "context", 112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 112);
  sf_mex_assign(&c2_rhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs112), "rhs", "rhs",
                  112);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs112), "lhs", "lhs",
                  112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m"),
                  "context", "context", 113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.ixamax"),
                  "name", "name", 113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "resolved", "resolved", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 113);
  sf_mex_assign(&c2_rhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs113), "rhs", "rhs",
                  113);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs113), "lhs", "lhs",
                  113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "context", "context", 114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 114);
  sf_mex_assign(&c2_rhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs114), "rhs", "rhs",
                  114);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs114), "lhs", "lhs",
                  114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p!below_threshold"),
                  "context", "context", 115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 115);
  sf_mex_assign(&c2_rhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs115), "rhs", "rhs",
                  115);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs115), "lhs", "lhs",
                  115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p!below_threshold"),
                  "context", "context", 116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("length"), "name", "name", 116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1303146206U), "fileTimeLo",
                  "fileTimeLo", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 116);
  sf_mex_assign(&c2_rhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs116), "rhs", "rhs",
                  116);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs116), "lhs", "lhs",
                  116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength"),
                  "context", "context", 117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 117);
  sf_mex_assign(&c2_rhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs117), "rhs", "rhs",
                  117);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs117), "lhs", "lhs",
                  117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/ixamax.p"),
                  "context", "context", 118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.ixamax"),
                  "name", "name", 118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "resolved", "resolved", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 118);
  sf_mex_assign(&c2_rhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs118), "rhs", "rhs",
                  118);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs118), "lhs", "lhs",
                  118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "context", "context", 119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xcabs1"),
                  "name", "name", 119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "resolved", "resolved", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 119);
  sf_mex_assign(&c2_rhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs119), "rhs", "rhs",
                  119);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs119), "lhs", "lhs",
                  119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xcabs1.p"),
                  "context", "context", 120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 120);
  sf_mex_assign(&c2_rhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs120), "rhs", "rhs",
                  120);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs120), "lhs", "lhs",
                  120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "context", "context", 121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 121);
  sf_mex_assign(&c2_rhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs121), "rhs", "rhs",
                  121);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs121), "lhs", "lhs",
                  121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/ixamax.p"),
                  "context", "context", 122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 122);
  sf_mex_assign(&c2_rhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs122), "rhs", "rhs",
                  122);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs122), "lhs", "lhs",
                  122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xswap"), "name", "name",
                  123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"),
                  "resolved", "resolved", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980692U), "fileTimeLo",
                  "fileTimeLo", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 123);
  sf_mex_assign(&c2_rhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs123), "rhs", "rhs",
                  123);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs123), "lhs", "lhs",
                  123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"), "context",
                  "context", 124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 124);
  sf_mex_assign(&c2_rhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs124), "rhs", "rhs",
                  124);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs124), "lhs", "lhs",
                  124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m"), "context",
                  "context", 125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xswap"),
                  "name", "name", 125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "resolved", "resolved", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 125);
  sf_mex_assign(&c2_rhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs125), "rhs", "rhs",
                  125);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs125), "lhs", "lhs",
                  125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "context", "context", 126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 126);
  sf_mex_assign(&c2_rhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs126), "rhs", "rhs",
                  126);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs126), "lhs", "lhs",
                  126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p!below_threshold"),
                  "context", "context", 127);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 127);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 127);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 127);
  sf_mex_assign(&c2_rhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs127), "rhs", "rhs",
                  127);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs127), "lhs", "lhs",
                  127);
  sf_mex_destroy(&c2_rhs64);
  sf_mex_destroy(&c2_lhs64);
  sf_mex_destroy(&c2_rhs65);
  sf_mex_destroy(&c2_lhs65);
  sf_mex_destroy(&c2_rhs66);
  sf_mex_destroy(&c2_lhs66);
  sf_mex_destroy(&c2_rhs67);
  sf_mex_destroy(&c2_lhs67);
  sf_mex_destroy(&c2_rhs68);
  sf_mex_destroy(&c2_lhs68);
  sf_mex_destroy(&c2_rhs69);
  sf_mex_destroy(&c2_lhs69);
  sf_mex_destroy(&c2_rhs70);
  sf_mex_destroy(&c2_lhs70);
  sf_mex_destroy(&c2_rhs71);
  sf_mex_destroy(&c2_lhs71);
  sf_mex_destroy(&c2_rhs72);
  sf_mex_destroy(&c2_lhs72);
  sf_mex_destroy(&c2_rhs73);
  sf_mex_destroy(&c2_lhs73);
  sf_mex_destroy(&c2_rhs74);
  sf_mex_destroy(&c2_lhs74);
  sf_mex_destroy(&c2_rhs75);
  sf_mex_destroy(&c2_lhs75);
  sf_mex_destroy(&c2_rhs76);
  sf_mex_destroy(&c2_lhs76);
  sf_mex_destroy(&c2_rhs77);
  sf_mex_destroy(&c2_lhs77);
  sf_mex_destroy(&c2_rhs78);
  sf_mex_destroy(&c2_lhs78);
  sf_mex_destroy(&c2_rhs79);
  sf_mex_destroy(&c2_lhs79);
  sf_mex_destroy(&c2_rhs80);
  sf_mex_destroy(&c2_lhs80);
  sf_mex_destroy(&c2_rhs81);
  sf_mex_destroy(&c2_lhs81);
  sf_mex_destroy(&c2_rhs82);
  sf_mex_destroy(&c2_lhs82);
  sf_mex_destroy(&c2_rhs83);
  sf_mex_destroy(&c2_lhs83);
  sf_mex_destroy(&c2_rhs84);
  sf_mex_destroy(&c2_lhs84);
  sf_mex_destroy(&c2_rhs85);
  sf_mex_destroy(&c2_lhs85);
  sf_mex_destroy(&c2_rhs86);
  sf_mex_destroy(&c2_lhs86);
  sf_mex_destroy(&c2_rhs87);
  sf_mex_destroy(&c2_lhs87);
  sf_mex_destroy(&c2_rhs88);
  sf_mex_destroy(&c2_lhs88);
  sf_mex_destroy(&c2_rhs89);
  sf_mex_destroy(&c2_lhs89);
  sf_mex_destroy(&c2_rhs90);
  sf_mex_destroy(&c2_lhs90);
  sf_mex_destroy(&c2_rhs91);
  sf_mex_destroy(&c2_lhs91);
  sf_mex_destroy(&c2_rhs92);
  sf_mex_destroy(&c2_lhs92);
  sf_mex_destroy(&c2_rhs93);
  sf_mex_destroy(&c2_lhs93);
  sf_mex_destroy(&c2_rhs94);
  sf_mex_destroy(&c2_lhs94);
  sf_mex_destroy(&c2_rhs95);
  sf_mex_destroy(&c2_lhs95);
  sf_mex_destroy(&c2_rhs96);
  sf_mex_destroy(&c2_lhs96);
  sf_mex_destroy(&c2_rhs97);
  sf_mex_destroy(&c2_lhs97);
  sf_mex_destroy(&c2_rhs98);
  sf_mex_destroy(&c2_lhs98);
  sf_mex_destroy(&c2_rhs99);
  sf_mex_destroy(&c2_lhs99);
  sf_mex_destroy(&c2_rhs100);
  sf_mex_destroy(&c2_lhs100);
  sf_mex_destroy(&c2_rhs101);
  sf_mex_destroy(&c2_lhs101);
  sf_mex_destroy(&c2_rhs102);
  sf_mex_destroy(&c2_lhs102);
  sf_mex_destroy(&c2_rhs103);
  sf_mex_destroy(&c2_lhs103);
  sf_mex_destroy(&c2_rhs104);
  sf_mex_destroy(&c2_lhs104);
  sf_mex_destroy(&c2_rhs105);
  sf_mex_destroy(&c2_lhs105);
  sf_mex_destroy(&c2_rhs106);
  sf_mex_destroy(&c2_lhs106);
  sf_mex_destroy(&c2_rhs107);
  sf_mex_destroy(&c2_lhs107);
  sf_mex_destroy(&c2_rhs108);
  sf_mex_destroy(&c2_lhs108);
  sf_mex_destroy(&c2_rhs109);
  sf_mex_destroy(&c2_lhs109);
  sf_mex_destroy(&c2_rhs110);
  sf_mex_destroy(&c2_lhs110);
  sf_mex_destroy(&c2_rhs111);
  sf_mex_destroy(&c2_lhs111);
  sf_mex_destroy(&c2_rhs112);
  sf_mex_destroy(&c2_lhs112);
  sf_mex_destroy(&c2_rhs113);
  sf_mex_destroy(&c2_lhs113);
  sf_mex_destroy(&c2_rhs114);
  sf_mex_destroy(&c2_lhs114);
  sf_mex_destroy(&c2_rhs115);
  sf_mex_destroy(&c2_lhs115);
  sf_mex_destroy(&c2_rhs116);
  sf_mex_destroy(&c2_lhs116);
  sf_mex_destroy(&c2_rhs117);
  sf_mex_destroy(&c2_lhs117);
  sf_mex_destroy(&c2_rhs118);
  sf_mex_destroy(&c2_lhs118);
  sf_mex_destroy(&c2_rhs119);
  sf_mex_destroy(&c2_lhs119);
  sf_mex_destroy(&c2_rhs120);
  sf_mex_destroy(&c2_lhs120);
  sf_mex_destroy(&c2_rhs121);
  sf_mex_destroy(&c2_lhs121);
  sf_mex_destroy(&c2_rhs122);
  sf_mex_destroy(&c2_lhs122);
  sf_mex_destroy(&c2_rhs123);
  sf_mex_destroy(&c2_lhs123);
  sf_mex_destroy(&c2_rhs124);
  sf_mex_destroy(&c2_lhs124);
  sf_mex_destroy(&c2_rhs125);
  sf_mex_destroy(&c2_lhs125);
  sf_mex_destroy(&c2_rhs126);
  sf_mex_destroy(&c2_lhs126);
  sf_mex_destroy(&c2_rhs127);
  sf_mex_destroy(&c2_lhs127);
}

static void c2_c_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs128 = NULL;
  const mxArray *c2_lhs128 = NULL;
  const mxArray *c2_rhs129 = NULL;
  const mxArray *c2_lhs129 = NULL;
  const mxArray *c2_rhs130 = NULL;
  const mxArray *c2_lhs130 = NULL;
  const mxArray *c2_rhs131 = NULL;
  const mxArray *c2_lhs131 = NULL;
  const mxArray *c2_rhs132 = NULL;
  const mxArray *c2_lhs132 = NULL;
  const mxArray *c2_rhs133 = NULL;
  const mxArray *c2_lhs133 = NULL;
  const mxArray *c2_rhs134 = NULL;
  const mxArray *c2_lhs134 = NULL;
  const mxArray *c2_rhs135 = NULL;
  const mxArray *c2_lhs135 = NULL;
  const mxArray *c2_rhs136 = NULL;
  const mxArray *c2_lhs136 = NULL;
  const mxArray *c2_rhs137 = NULL;
  const mxArray *c2_lhs137 = NULL;
  const mxArray *c2_rhs138 = NULL;
  const mxArray *c2_lhs138 = NULL;
  const mxArray *c2_rhs139 = NULL;
  const mxArray *c2_lhs139 = NULL;
  const mxArray *c2_rhs140 = NULL;
  const mxArray *c2_lhs140 = NULL;
  const mxArray *c2_rhs141 = NULL;
  const mxArray *c2_lhs141 = NULL;
  const mxArray *c2_rhs142 = NULL;
  const mxArray *c2_lhs142 = NULL;
  const mxArray *c2_rhs143 = NULL;
  const mxArray *c2_lhs143 = NULL;
  const mxArray *c2_rhs144 = NULL;
  const mxArray *c2_lhs144 = NULL;
  const mxArray *c2_rhs145 = NULL;
  const mxArray *c2_lhs145 = NULL;
  const mxArray *c2_rhs146 = NULL;
  const mxArray *c2_lhs146 = NULL;
  const mxArray *c2_rhs147 = NULL;
  const mxArray *c2_lhs147 = NULL;
  const mxArray *c2_rhs148 = NULL;
  const mxArray *c2_lhs148 = NULL;
  const mxArray *c2_rhs149 = NULL;
  const mxArray *c2_lhs149 = NULL;
  const mxArray *c2_rhs150 = NULL;
  const mxArray *c2_lhs150 = NULL;
  const mxArray *c2_rhs151 = NULL;
  const mxArray *c2_lhs151 = NULL;
  const mxArray *c2_rhs152 = NULL;
  const mxArray *c2_lhs152 = NULL;
  const mxArray *c2_rhs153 = NULL;
  const mxArray *c2_lhs153 = NULL;
  const mxArray *c2_rhs154 = NULL;
  const mxArray *c2_lhs154 = NULL;
  const mxArray *c2_rhs155 = NULL;
  const mxArray *c2_lhs155 = NULL;
  const mxArray *c2_rhs156 = NULL;
  const mxArray *c2_lhs156 = NULL;
  const mxArray *c2_rhs157 = NULL;
  const mxArray *c2_lhs157 = NULL;
  const mxArray *c2_rhs158 = NULL;
  const mxArray *c2_lhs158 = NULL;
  const mxArray *c2_rhs159 = NULL;
  const mxArray *c2_lhs159 = NULL;
  const mxArray *c2_rhs160 = NULL;
  const mxArray *c2_lhs160 = NULL;
  const mxArray *c2_rhs161 = NULL;
  const mxArray *c2_lhs161 = NULL;
  const mxArray *c2_rhs162 = NULL;
  const mxArray *c2_lhs162 = NULL;
  const mxArray *c2_rhs163 = NULL;
  const mxArray *c2_lhs163 = NULL;
  const mxArray *c2_rhs164 = NULL;
  const mxArray *c2_lhs164 = NULL;
  const mxArray *c2_rhs165 = NULL;
  const mxArray *c2_lhs165 = NULL;
  const mxArray *c2_rhs166 = NULL;
  const mxArray *c2_lhs166 = NULL;
  const mxArray *c2_rhs167 = NULL;
  const mxArray *c2_lhs167 = NULL;
  const mxArray *c2_rhs168 = NULL;
  const mxArray *c2_lhs168 = NULL;
  const mxArray *c2_rhs169 = NULL;
  const mxArray *c2_lhs169 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xswap.p"),
                  "context", "context", 128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xswap"),
                  "name", "name", 128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "resolved", "resolved", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 128);
  sf_mex_assign(&c2_rhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs128), "rhs", "rhs",
                  128);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs128), "lhs", "lhs",
                  128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 129);
  sf_mex_assign(&c2_rhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs129), "rhs", "rhs",
                  129);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs129), "lhs", "lhs",
                  129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 130);
  sf_mex_assign(&c2_rhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs130), "rhs", "rhs",
                  130);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs130), "lhs", "lhs",
                  130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818712U), "fileTimeLo",
                  "fileTimeLo", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 131);
  sf_mex_assign(&c2_rhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs131), "rhs", "rhs",
                  131);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs131), "lhs", "lhs",
                  131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 132);
  sf_mex_assign(&c2_rhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs132), "rhs", "rhs",
                  132);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs132), "lhs", "lhs",
                  132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xswap.p"),
                  "context", "context", 133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 133);
  sf_mex_assign(&c2_rhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs133), "rhs", "rhs",
                  133);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs133), "lhs", "lhs",
                  133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_div"), "name", "name", 134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 134);
  sf_mex_assign(&c2_rhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs134), "rhs", "rhs",
                  134);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs134), "lhs", "lhs",
                  134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m"),
                  "context", "context", 135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xgeru"), "name", "name",
                  135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"),
                  "resolved", "resolved", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 135);
  sf_mex_assign(&c2_rhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs135), "rhs", "rhs",
                  135);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs135), "lhs", "lhs",
                  135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"), "context",
                  "context", 136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 136);
  sf_mex_assign(&c2_rhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs136), "rhs", "rhs",
                  136);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs136), "lhs", "lhs",
                  136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m"), "context",
                  "context", 137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xgeru"),
                  "name", "name", 137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgeru.p"),
                  "resolved", "resolved", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 137);
  sf_mex_assign(&c2_rhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs137), "rhs", "rhs",
                  137);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs137), "lhs", "lhs",
                  137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgeru.p"),
                  "context", "context", 138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xger"),
                  "name", "name", 138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "resolved", "resolved", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 138);
  sf_mex_assign(&c2_rhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs138), "rhs", "rhs",
                  138);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs138), "lhs", "lhs",
                  138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "context", "context", 139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 139);
  sf_mex_assign(&c2_rhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs139), "rhs", "rhs",
                  139);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs139), "lhs", "lhs",
                  139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 140);
  sf_mex_assign(&c2_rhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs140), "rhs", "rhs",
                  140);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs140), "lhs", "lhs",
                  140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.int"),
                  "name", "name", 141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/int.p"),
                  "resolved", "resolved", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 141);
  sf_mex_assign(&c2_rhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs141), "rhs", "rhs",
                  141);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs141), "lhs", "lhs",
                  141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 142);
  sf_mex_assign(&c2_rhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs142), "rhs", "rhs",
                  142);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs142), "lhs", "lhs",
                  142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p!below_threshold"),
                  "context", "context", 143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311255318U), "fileTimeLo",
                  "fileTimeLo", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 143);
  sf_mex_assign(&c2_rhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs143), "rhs", "rhs",
                  143);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs143), "lhs", "lhs",
                  143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 144);
  sf_mex_assign(&c2_rhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs144), "rhs", "rhs",
                  144);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs144), "lhs", "lhs",
                  144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 145);
  sf_mex_assign(&c2_rhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs145), "rhs", "rhs",
                  145);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs145), "lhs", "lhs",
                  145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 146);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 146);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 146);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 146);
  sf_mex_assign(&c2_rhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs146), "rhs", "rhs",
                  146);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs146), "lhs", "lhs",
                  146);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 147);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 147);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 147);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 147);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 147);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 147);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 147);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 147);
  sf_mex_assign(&c2_rhs147, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs147, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs147), "rhs", "rhs",
                  147);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs147), "lhs", "lhs",
                  147);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xger.p"),
                  "context", "context", 148);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xger"),
                  "name", "name", 148);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 148);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xger.p"),
                  "resolved", "resolved", 148);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 148);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 148);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 148);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 148);
  sf_mex_assign(&c2_rhs148, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs148, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs148), "rhs", "rhs",
                  148);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs148), "lhs", "lhs",
                  148);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xger.p"),
                  "context", "context", 149);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xgerx"),
                  "name", "name", 149);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 149);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "resolved", "resolved", 149);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 149);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 149);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 149);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 149);
  sf_mex_assign(&c2_rhs149, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs149, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs149), "rhs", "rhs",
                  149);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs149), "lhs", "lhs",
                  149);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 150);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("abs"), "name", "name", 150);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 150);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 150);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 150);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 150);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 150);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 150);
  sf_mex_assign(&c2_rhs150, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs150, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs150), "rhs", "rhs",
                  150);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs150), "lhs", "lhs",
                  150);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 151);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 151);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 151);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 151);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 151);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 151);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 151);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 151);
  sf_mex_assign(&c2_rhs151, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs151, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs151), "rhs", "rhs",
                  151);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs151), "lhs", "lhs",
                  151);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 152);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 152);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 152);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 152);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 152);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 152);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 152);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 152);
  sf_mex_assign(&c2_rhs152, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs152, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs152), "rhs", "rhs",
                  152);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs152), "lhs", "lhs",
                  152);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 153);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 153);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 153);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 153);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 153);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 153);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 153);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 153);
  sf_mex_assign(&c2_rhs153, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs153, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs153), "rhs", "rhs",
                  153);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs153), "lhs", "lhs",
                  153);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgerx.p"),
                  "context", "context", 154);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 154);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 154);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 154);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 154);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 154);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 154);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 154);
  sf_mex_assign(&c2_rhs154, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs154, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs154), "rhs", "rhs",
                  154);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs154), "lhs", "lhs",
                  154);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN"),
                  "context", "context", 155);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 155);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 155);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 155);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 155);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 155);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 155);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 155);
  sf_mex_assign(&c2_rhs155, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs155, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs155), "rhs", "rhs",
                  155);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs155), "lhs", "lhs",
                  155);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN"),
                  "context", "context", 156);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 156);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 156);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 156);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 156);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 156);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 156);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 156);
  sf_mex_assign(&c2_rhs156, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs156, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs156), "rhs", "rhs",
                  156);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs156), "lhs", "lhs",
                  156);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolveNxN"),
                  "context", "context", 157);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_xtrsm"), "name", "name",
                  157);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 157);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m"),
                  "resolved", "resolved", 157);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980692U), "fileTimeLo",
                  "fileTimeLo", 157);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 157);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 157);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 157);
  sf_mex_assign(&c2_rhs157, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs157, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs157), "rhs", "rhs",
                  157);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs157), "lhs", "lhs",
                  157);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m"), "context",
                  "context", 158);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 158);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 158);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 158);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 158);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 158);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 158);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 158);
  sf_mex_assign(&c2_rhs158, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs158, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs158), "rhs", "rhs",
                  158);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs158), "lhs", "lhs",
                  158);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m"), "context",
                  "context", 159);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.xtrsm"),
                  "name", "name", 159);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 159);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "resolved", "resolved", 159);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 159);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 159);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 159);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 159);
  sf_mex_assign(&c2_rhs159, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs159, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs159), "rhs", "rhs",
                  159);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs159), "lhs", "lhs",
                  159);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "context", "context", 160);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 160);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 160);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 160);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 160);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 160);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 160);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 160);
  sf_mex_assign(&c2_rhs160, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs160, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs160), "rhs", "rhs",
                  160);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs160), "lhs", "lhs",
                  160);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p!below_threshold"),
                  "context", "context", 161);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 161);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 161);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 161);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 161);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 161);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 161);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 161);
  sf_mex_assign(&c2_rhs161, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs161, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs161), "rhs", "rhs",
                  161);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs161), "lhs", "lhs",
                  161);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "context", "context", 162);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 162);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 162);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 162);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 162);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 162);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 162);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 162);
  sf_mex_assign(&c2_rhs162, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs162, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs162), "rhs", "rhs",
                  162);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs162), "lhs", "lhs",
                  162);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xtrsm.p"),
                  "context", "context", 163);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.refblas.xtrsm"),
                  "name", "name", 163);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 163);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "resolved", "resolved", 163);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 163);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 163);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 163);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 163);
  sf_mex_assign(&c2_rhs163, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs163, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs163), "rhs", "rhs",
                  163);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs163), "lhs", "lhs",
                  163);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 164);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 164);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 164);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 164);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 164);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 164);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 164);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 164);
  sf_mex_assign(&c2_rhs164, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs164, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs164), "rhs", "rhs",
                  164);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs164), "lhs", "lhs",
                  164);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 165);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 165);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 165);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 165);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 165);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 165);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 165);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 165);
  sf_mex_assign(&c2_rhs165, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs165, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs165), "rhs", "rhs",
                  165);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs165), "lhs", "lhs",
                  165);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 166);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 166);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 166);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 166);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 166);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 166);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 166);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 166);
  sf_mex_assign(&c2_rhs166, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs166, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs166), "rhs", "rhs",
                  166);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs166), "lhs", "lhs",
                  166);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 167);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 167);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 167);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 167);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 167);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 167);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 167);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 167);
  sf_mex_assign(&c2_rhs167, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs167, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs167), "rhs", "rhs",
                  167);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs167), "lhs", "lhs",
                  167);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xtrsm.p"),
                  "context", "context", 168);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("rdivide"), "name", "name", 168);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 168);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 168);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 168);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 168);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 168);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 168);
  sf_mex_assign(&c2_rhs168, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs168, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs168), "rhs", "rhs",
                  168);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs168), "lhs", "lhs",
                  168);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!warn_singular"),
                  "context", "context", 169);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_warning"), "name", "name",
                  169);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 169);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m"), "resolved",
                  "resolved", 169);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286818802U), "fileTimeLo",
                  "fileTimeLo", 169);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 169);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 169);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 169);
  sf_mex_assign(&c2_rhs169, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs169, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs169), "rhs", "rhs",
                  169);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs169), "lhs", "lhs",
                  169);
  sf_mex_destroy(&c2_rhs128);
  sf_mex_destroy(&c2_lhs128);
  sf_mex_destroy(&c2_rhs129);
  sf_mex_destroy(&c2_lhs129);
  sf_mex_destroy(&c2_rhs130);
  sf_mex_destroy(&c2_lhs130);
  sf_mex_destroy(&c2_rhs131);
  sf_mex_destroy(&c2_lhs131);
  sf_mex_destroy(&c2_rhs132);
  sf_mex_destroy(&c2_lhs132);
  sf_mex_destroy(&c2_rhs133);
  sf_mex_destroy(&c2_lhs133);
  sf_mex_destroy(&c2_rhs134);
  sf_mex_destroy(&c2_lhs134);
  sf_mex_destroy(&c2_rhs135);
  sf_mex_destroy(&c2_lhs135);
  sf_mex_destroy(&c2_rhs136);
  sf_mex_destroy(&c2_lhs136);
  sf_mex_destroy(&c2_rhs137);
  sf_mex_destroy(&c2_lhs137);
  sf_mex_destroy(&c2_rhs138);
  sf_mex_destroy(&c2_lhs138);
  sf_mex_destroy(&c2_rhs139);
  sf_mex_destroy(&c2_lhs139);
  sf_mex_destroy(&c2_rhs140);
  sf_mex_destroy(&c2_lhs140);
  sf_mex_destroy(&c2_rhs141);
  sf_mex_destroy(&c2_lhs141);
  sf_mex_destroy(&c2_rhs142);
  sf_mex_destroy(&c2_lhs142);
  sf_mex_destroy(&c2_rhs143);
  sf_mex_destroy(&c2_lhs143);
  sf_mex_destroy(&c2_rhs144);
  sf_mex_destroy(&c2_lhs144);
  sf_mex_destroy(&c2_rhs145);
  sf_mex_destroy(&c2_lhs145);
  sf_mex_destroy(&c2_rhs146);
  sf_mex_destroy(&c2_lhs146);
  sf_mex_destroy(&c2_rhs147);
  sf_mex_destroy(&c2_lhs147);
  sf_mex_destroy(&c2_rhs148);
  sf_mex_destroy(&c2_lhs148);
  sf_mex_destroy(&c2_rhs149);
  sf_mex_destroy(&c2_lhs149);
  sf_mex_destroy(&c2_rhs150);
  sf_mex_destroy(&c2_lhs150);
  sf_mex_destroy(&c2_rhs151);
  sf_mex_destroy(&c2_lhs151);
  sf_mex_destroy(&c2_rhs152);
  sf_mex_destroy(&c2_lhs152);
  sf_mex_destroy(&c2_rhs153);
  sf_mex_destroy(&c2_lhs153);
  sf_mex_destroy(&c2_rhs154);
  sf_mex_destroy(&c2_lhs154);
  sf_mex_destroy(&c2_rhs155);
  sf_mex_destroy(&c2_lhs155);
  sf_mex_destroy(&c2_rhs156);
  sf_mex_destroy(&c2_lhs156);
  sf_mex_destroy(&c2_rhs157);
  sf_mex_destroy(&c2_lhs157);
  sf_mex_destroy(&c2_rhs158);
  sf_mex_destroy(&c2_lhs158);
  sf_mex_destroy(&c2_rhs159);
  sf_mex_destroy(&c2_lhs159);
  sf_mex_destroy(&c2_rhs160);
  sf_mex_destroy(&c2_lhs160);
  sf_mex_destroy(&c2_rhs161);
  sf_mex_destroy(&c2_lhs161);
  sf_mex_destroy(&c2_rhs162);
  sf_mex_destroy(&c2_lhs162);
  sf_mex_destroy(&c2_rhs163);
  sf_mex_destroy(&c2_lhs163);
  sf_mex_destroy(&c2_rhs164);
  sf_mex_destroy(&c2_lhs164);
  sf_mex_destroy(&c2_rhs165);
  sf_mex_destroy(&c2_lhs165);
  sf_mex_destroy(&c2_rhs166);
  sf_mex_destroy(&c2_lhs166);
  sf_mex_destroy(&c2_rhs167);
  sf_mex_destroy(&c2_lhs167);
  sf_mex_destroy(&c2_rhs168);
  sf_mex_destroy(&c2_lhs168);
  sf_mex_destroy(&c2_rhs169);
  sf_mex_destroy(&c2_lhs169);
}

static real_T c2_abs(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T c2_x)
{
  real_T c2_b_x;
  (void)chartInstance;
  c2_b_x = c2_x;
  return muDoubleScalarAbs(c2_b_x);
}

static real_T c2_log(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T c2_x)
{
  real_T c2_b_x;
  c2_b_x = c2_x;
  c2_b_log(chartInstance, &c2_b_x);
  return c2_b_x;
}

static void c2_eml_error(SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  int32_T c2_i112;
  static char_T c2_cv0[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c2_u[30];
  const mxArray *c2_y = NULL;
  int32_T c2_i113;
  static char_T c2_cv1[3] = { 'l', 'o', 'g' };

  char_T c2_b_u[3];
  const mxArray *c2_b_y = NULL;
  (void)chartInstance;
  for (c2_i112 = 0; c2_i112 < 30; c2_i112++) {
    c2_u[c2_i112] = c2_cv0[c2_i112];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 30), false);
  for (c2_i113 = 0; c2_i113 < 3; c2_i113++) {
    c2_b_u[c2_i113] = c2_cv1[c2_i113];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 3),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c2_y, 14, c2_b_y));
}

static void c2_eml_scalar_eg(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_threshold(SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_eml_scalar_eg(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_cross(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T c2_a[3], real_T c2_b[3], real_T c2_c[3])
{
  real_T c2_c1;
  real_T c2_c2;
  real_T c2_c3;
  (void)chartInstance;
  c2_c1 = c2_a[1] * c2_b[2] - c2_a[2] * c2_b[1];
  c2_c2 = c2_a[2] * c2_b[0] - c2_a[0] * c2_b[2];
  c2_c3 = c2_a[0] * c2_b[1] - c2_a[1] * c2_b[0];
  c2_c[0] = c2_c1;
  c2_c[1] = c2_c2;
  c2_c[2] = c2_c3;
}

static real_T c2_atan2(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_y, real_T c2_x)
{
  real_T c2_b_y;
  real_T c2_b_x;
  c2_c_eml_scalar_eg(chartInstance);
  c2_b_y = c2_y;
  c2_b_x = c2_x;
  return muDoubleScalarAtan2(c2_b_y, c2_b_x);
}

static void c2_c_eml_scalar_eg(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static real_T c2_mpower(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_a)
{
  real_T c2_b_a;
  real_T c2_c_a;
  real_T c2_ak;
  real_T c2_d_a;
  c2_b_a = c2_a;
  c2_c_a = c2_b_a;
  c2_c_eml_scalar_eg(chartInstance);
  c2_ak = c2_c_a;
  c2_d_a = c2_ak;
  c2_c_eml_scalar_eg(chartInstance);
  return c2_d_a * c2_d_a;
}

static real_T c2_sqrt(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                      real_T c2_x)
{
  real_T c2_b_x;
  c2_b_x = c2_x;
  c2_b_sqrt(chartInstance, &c2_b_x);
  return c2_b_x;
}

static void c2_b_eml_error(SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  int32_T c2_i114;
  static char_T c2_cv2[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'E', 'l', 'F', 'u', 'n', 'D', 'o', 'm', 'a', 'i', 'n',
    'E', 'r', 'r', 'o', 'r' };

  char_T c2_u[30];
  const mxArray *c2_y = NULL;
  int32_T c2_i115;
  static char_T c2_cv3[4] = { 's', 'q', 'r', 't' };

  char_T c2_b_u[4];
  const mxArray *c2_b_y = NULL;
  (void)chartInstance;
  for (c2_i114 = 0; c2_i114 < 30; c2_i114++) {
    c2_u[c2_i114] = c2_cv2[c2_i114];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 30), false);
  for (c2_i115 = 0; c2_i115 < 4; c2_i115++) {
    c2_b_u[c2_i115] = c2_cv3[c2_i115];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    2U, 14, c2_y, 14, c2_b_y));
}

static void c2_d_eml_scalar_eg(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_eml_switch_helper(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_mldivide(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_B[4], real_T c2_Y[4])
{
  int32_T c2_i116;
  int32_T c2_xi;
  int32_T c2_b_xi;
  int32_T c2_ip;
  real_T c2_temp;
  int32_T c2_i117;
  static real_T c2_dv19[16] = { -26870.0, 0.0, 0.0, 0.0, -0.0, -43330.0,
    -0.30371567043618741, -0.14285714285714285, -0.0, 13160.0,
    -236193.10177705978, 0.0028366620149321976, -0.0, 6190.0, -670.0,
    -125523.81372216428 };

  real_T c2_dv20[16];
  int32_T c2_i118;
  real_T c2_dv21[16];
  c2_d_eml_scalar_eg(chartInstance);
  for (c2_i116 = 0; c2_i116 < 4; c2_i116++) {
    c2_Y[c2_i116] = c2_B[c2_i116];
  }

  for (c2_xi = 1; c2_xi < 4; c2_xi++) {
    c2_b_xi = c2_xi;
    if (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)
          c2_b_xi), 1, 4, 1, 0) != c2_b_xi) {
      c2_ip = _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_xi), 1, 4, 1, 0);
      c2_temp = c2_Y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
        ("", (real_T)c2_b_xi), 1, 4, 1, 0) - 1];
      c2_Y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_xi), 1, 4, 1, 0) - 1] = c2_Y[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_ip), 1, 4, 1, 0) - 1];
      c2_Y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_ip), 1, 4, 1, 0) - 1] = c2_temp;
    }
  }

  for (c2_i117 = 0; c2_i117 < 16; c2_i117++) {
    c2_dv20[c2_i117] = c2_dv19[c2_i117];
  }

  c2_c_eml_xtrsm(chartInstance, c2_dv20, c2_Y);
  for (c2_i118 = 0; c2_i118 < 16; c2_i118++) {
    c2_dv21[c2_i118] = c2_dv19[c2_i118];
  }

  c2_d_eml_xtrsm(chartInstance, c2_dv21, c2_Y);
}

static void c2_eml_matlab_zgetrf(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, real_T c2_A[16], real_T c2_b_A[16], int32_T c2_ipiv[4],
  int32_T *c2_info)
{
  int32_T c2_i119;
  for (c2_i119 = 0; c2_i119 < 16; c2_i119++) {
    c2_b_A[c2_i119] = c2_A[c2_i119];
  }

  c2_b_eml_matlab_zgetrf(chartInstance, c2_b_A, c2_ipiv, c2_info);
}

static int32_T c2_eml_ixamax(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, int32_T c2_n, real_T c2_x[16], int32_T c2_ix0)
{
  int32_T c2_idxmax;
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_c_n;
  int32_T c2_c_ix0;
  int32_T c2_ix;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_y;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_b_y;
  real_T c2_smax;
  int32_T c2_d_n;
  int32_T c2_b;
  int32_T c2_b_b;
  boolean_T c2_overflow;
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_a;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_c_y;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_d_y;
  real_T c2_s;
  c2_b_n = c2_n;
  c2_b_ix0 = c2_ix0;
  c2_c_n = c2_b_n;
  c2_c_ix0 = c2_b_ix0;
  if (c2_c_n < 1) {
    c2_idxmax = 0;
  } else {
    c2_idxmax = 1;
    if (c2_c_n > 1) {
      c2_ix = c2_c_ix0;
      c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_ix), 1, 16, 1, 0) - 1];
      c2_c_x = c2_b_x;
      c2_d_x = c2_c_x;
      c2_y = muDoubleScalarAbs(c2_d_x);
      c2_e_x = 0.0;
      c2_f_x = c2_e_x;
      c2_b_y = muDoubleScalarAbs(c2_f_x);
      c2_smax = c2_y + c2_b_y;
      c2_d_n = c2_c_n;
      c2_b = c2_d_n;
      c2_b_b = c2_b;
      if (2 > c2_b_b) {
        c2_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_overflow = (c2_b_b > 2147483646);
      }

      if (c2_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_overflow);
      }

      for (c2_k = 2; c2_k <= c2_d_n; c2_k++) {
        c2_b_k = c2_k;
        c2_a = c2_ix + 1;
        c2_ix = c2_a;
        c2_g_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 16, 1, 0) - 1];
        c2_h_x = c2_g_x;
        c2_i_x = c2_h_x;
        c2_c_y = muDoubleScalarAbs(c2_i_x);
        c2_j_x = 0.0;
        c2_k_x = c2_j_x;
        c2_d_y = muDoubleScalarAbs(c2_k_x);
        c2_s = c2_c_y + c2_d_y;
        if (c2_s > c2_smax) {
          c2_idxmax = c2_b_k;
          c2_smax = c2_s;
        }
      }
    }
  }

  return c2_idxmax;
}

static void c2_check_forloop_overflow_error
  (SFc2_SailingYachtModel2InstanceStruct *chartInstance, boolean_T c2_overflow)
{
  int32_T c2_i120;
  static char_T c2_cv4[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c2_u[34];
  const mxArray *c2_y = NULL;
  int32_T c2_i121;
  static char_T c2_cv5[23] = { 'c', 'o', 'd', 'e', 'r', '.', 'i', 'n', 't', 'e',
    'r', 'n', 'a', 'l', '.', 'i', 'n', 'd', 'e', 'x', 'I', 'n', 't' };

  char_T c2_b_u[23];
  const mxArray *c2_b_y = NULL;
  (void)chartInstance;
  if (!c2_overflow) {
  } else {
    for (c2_i120 = 0; c2_i120 < 34; c2_i120++) {
      c2_u[c2_i120] = c2_cv4[c2_i120];
    }

    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  false);
    for (c2_i121 = 0; c2_i121 < 23; c2_i121++) {
      c2_b_u[c2_i121] = c2_cv5[c2_i121];
    }

    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 23),
                  false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                      sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message",
      1U, 2U, 14, c2_y, 14, c2_b_y));
  }
}

static void c2_b_threshold(SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_eml_xgeru(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  int32_T c2_m, int32_T c2_n, real_T c2_alpha1, int32_T c2_ix0, int32_T c2_iy0,
  real_T c2_A[16], int32_T c2_ia0, real_T c2_b_A[16])
{
  int32_T c2_i122;
  for (c2_i122 = 0; c2_i122 < 16; c2_i122++) {
    c2_b_A[c2_i122] = c2_A[c2_i122];
  }

  c2_b_eml_xgeru(chartInstance, c2_m, c2_n, c2_alpha1, c2_ix0, c2_iy0, c2_b_A,
                 c2_ia0);
}

static void c2_eml_xtrsm(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[4], real_T c2_b_B[4])
{
  int32_T c2_i123;
  int32_T c2_i124;
  real_T c2_b_A[16];
  for (c2_i123 = 0; c2_i123 < 4; c2_i123++) {
    c2_b_B[c2_i123] = c2_B[c2_i123];
  }

  for (c2_i124 = 0; c2_i124 < 16; c2_i124++) {
    c2_b_A[c2_i124] = c2_A[c2_i124];
  }

  c2_c_eml_xtrsm(chartInstance, c2_b_A, c2_b_B);
}

static void c2_c_threshold(SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_scalarEg(SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_eml_xtrsm(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[4], real_T c2_b_B[4])
{
  int32_T c2_i125;
  int32_T c2_i126;
  real_T c2_b_A[16];
  for (c2_i125 = 0; c2_i125 < 4; c2_i125++) {
    c2_b_B[c2_i125] = c2_B[c2_i125];
  }

  for (c2_i126 = 0; c2_i126 < 16; c2_i126++) {
    c2_b_A[c2_i126] = c2_A[c2_i126];
  }

  c2_d_eml_xtrsm(chartInstance, c2_b_A, c2_b_B);
}

static void c2_b_mldivide(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[4], real_T c2_Y[4])
{
  int32_T c2_i127;
  real_T c2_b_A[16];
  int32_T c2_info;
  int32_T c2_ipiv[4];
  int32_T c2_b_info;
  int32_T c2_c_info;
  int32_T c2_d_info;
  int32_T c2_i128;
  int32_T c2_xi;
  int32_T c2_b_xi;
  int32_T c2_ip;
  real_T c2_temp;
  int32_T c2_i129;
  real_T c2_c_A[16];
  int32_T c2_i130;
  real_T c2_d_A[16];
  for (c2_i127 = 0; c2_i127 < 16; c2_i127++) {
    c2_b_A[c2_i127] = c2_A[c2_i127];
  }

  c2_b_eml_matlab_zgetrf(chartInstance, c2_b_A, c2_ipiv, &c2_info);
  c2_b_info = c2_info;
  c2_c_info = c2_b_info;
  c2_d_info = c2_c_info;
  if (c2_d_info > 0) {
    c2_eml_warning(chartInstance);
  }

  c2_d_eml_scalar_eg(chartInstance);
  for (c2_i128 = 0; c2_i128 < 4; c2_i128++) {
    c2_Y[c2_i128] = c2_B[c2_i128];
  }

  for (c2_xi = 1; c2_xi < 4; c2_xi++) {
    c2_b_xi = c2_xi;
    if (c2_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_xi), 1, 4, 1, 0) - 1] != c2_b_xi) {
      c2_ip = c2_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c2_b_xi), 1, 4, 1, 0) - 1];
      c2_temp = c2_Y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
        ("", (real_T)c2_b_xi), 1, 4, 1, 0) - 1];
      c2_Y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_xi), 1, 4, 1, 0) - 1] = c2_Y[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_ip), 1, 4, 1, 0) - 1];
      c2_Y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_ip), 1, 4, 1, 0) - 1] = c2_temp;
    }
  }

  for (c2_i129 = 0; c2_i129 < 16; c2_i129++) {
    c2_c_A[c2_i129] = c2_b_A[c2_i129];
  }

  c2_c_eml_xtrsm(chartInstance, c2_c_A, c2_Y);
  for (c2_i130 = 0; c2_i130 < 16; c2_i130++) {
    c2_d_A[c2_i130] = c2_b_A[c2_i130];
  }

  c2_d_eml_xtrsm(chartInstance, c2_d_A, c2_Y);
}

static void c2_eml_warning(SFc2_SailingYachtModel2InstanceStruct *chartInstance)
{
  int32_T c2_i131;
  static char_T c2_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c2_u[27];
  const mxArray *c2_y = NULL;
  (void)chartInstance;
  for (c2_i131 = 0; c2_i131 < 27; c2_i131++) {
    c2_u[c2_i131] = c2_varargin_1[c2_i131];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 27), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "warning", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c2_y));
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_j_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i132;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i132, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i132;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_k_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_SailingYachtModel2, const
  char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_SailingYachtModel2), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_SailingYachtModel2);
  return c2_y;
}

static uint8_T c2_l_emlrt_marshallIn(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_log(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                     real_T *c2_x)
{
  if (*c2_x < 0.0) {
    c2_eml_error(chartInstance);
  }

  *c2_x = muDoubleScalarLog(*c2_x);
}

static void c2_b_sqrt(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
                      real_T *c2_x)
{
  if (*c2_x < 0.0) {
    c2_b_eml_error(chartInstance);
  }

  *c2_x = muDoubleScalarSqrt(*c2_x);
}

static void c2_b_eml_matlab_zgetrf(SFc2_SailingYachtModel2InstanceStruct
  *chartInstance, real_T c2_A[16], int32_T c2_ipiv[4], int32_T *c2_info)
{
  int32_T c2_i133;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_b_a;
  int32_T c2_jm1;
  int32_T c2_b;
  int32_T c2_b_b;
  int32_T c2_mmj;
  int32_T c2_c_a;
  int32_T c2_d_a;
  int32_T c2_c;
  int32_T c2_c_b;
  int32_T c2_d_b;
  int32_T c2_jj;
  int32_T c2_e_a;
  int32_T c2_f_a;
  int32_T c2_jp1j;
  int32_T c2_g_a;
  int32_T c2_h_a;
  int32_T c2_b_c;
  int32_T c2_i134;
  int32_T c2_i135;
  int32_T c2_i136;
  real_T c2_b_A[16];
  int32_T c2_i_a;
  int32_T c2_j_a;
  int32_T c2_jpiv_offset;
  int32_T c2_k_a;
  int32_T c2_e_b;
  int32_T c2_l_a;
  int32_T c2_f_b;
  int32_T c2_jpiv;
  int32_T c2_m_a;
  int32_T c2_g_b;
  int32_T c2_n_a;
  int32_T c2_h_b;
  int32_T c2_c_c;
  int32_T c2_i_b;
  int32_T c2_j_b;
  int32_T c2_jrow;
  int32_T c2_o_a;
  int32_T c2_k_b;
  int32_T c2_p_a;
  int32_T c2_l_b;
  int32_T c2_jprow;
  int32_T c2_ix0;
  int32_T c2_iy0;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_k;
  real_T c2_temp;
  int32_T c2_q_a;
  int32_T c2_r_a;
  int32_T c2_b_jp1j;
  int32_T c2_s_a;
  int32_T c2_t_a;
  int32_T c2_d_c;
  int32_T c2_u_a;
  int32_T c2_m_b;
  int32_T c2_v_a;
  int32_T c2_n_b;
  int32_T c2_i137;
  int32_T c2_w_a;
  int32_T c2_o_b;
  int32_T c2_x_a;
  int32_T c2_p_b;
  boolean_T c2_overflow;
  int32_T c2_i;
  int32_T c2_b_i;
  real_T c2_x;
  real_T c2_y;
  real_T c2_b_x;
  real_T c2_b_y;
  real_T c2_z;
  int32_T c2_q_b;
  int32_T c2_r_b;
  int32_T c2_e_c;
  int32_T c2_y_a;
  int32_T c2_ab_a;
  int32_T c2_f_c;
  int32_T c2_bb_a;
  int32_T c2_cb_a;
  int32_T c2_g_c;
  real_T c2_d4;
  for (c2_i133 = 0; c2_i133 < 4; c2_i133++) {
    c2_ipiv[c2_i133] = 1 + c2_i133;
  }

  *c2_info = 0;
  for (c2_j = 1; c2_j < 4; c2_j++) {
    c2_b_j = c2_j;
    c2_a = c2_b_j;
    c2_b_a = c2_a - 1;
    c2_jm1 = c2_b_a;
    c2_b = c2_b_j;
    c2_b_b = c2_b;
    c2_mmj = 4 - c2_b_b;
    c2_c_a = c2_jm1;
    c2_d_a = c2_c_a;
    c2_c = c2_d_a * 5;
    c2_c_b = c2_c;
    c2_d_b = c2_c_b + 1;
    c2_jj = c2_d_b;
    c2_e_a = c2_jj;
    c2_f_a = c2_e_a + 1;
    c2_jp1j = c2_f_a;
    c2_g_a = c2_mmj;
    c2_h_a = c2_g_a;
    c2_b_c = c2_h_a;
    c2_i134 = 0;
    for (c2_i135 = 0; c2_i135 < 4; c2_i135++) {
      for (c2_i136 = 0; c2_i136 < 4; c2_i136++) {
        c2_b_A[c2_i136 + c2_i134] = c2_A[c2_i136 + c2_i134];
      }

      c2_i134 += 4;
    }

    c2_i_a = c2_eml_ixamax(chartInstance, c2_b_c + 1, c2_b_A, c2_jj);
    c2_j_a = c2_i_a - 1;
    c2_jpiv_offset = c2_j_a;
    c2_k_a = c2_jj;
    c2_e_b = c2_jpiv_offset;
    c2_l_a = c2_k_a;
    c2_f_b = c2_e_b;
    c2_jpiv = c2_l_a + c2_f_b;
    if (c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_jpiv), 1, 16, 1, 0) - 1] != 0.0) {
      if (c2_jpiv_offset != 0) {
        c2_m_a = c2_b_j;
        c2_g_b = c2_jpiv_offset;
        c2_n_a = c2_m_a;
        c2_h_b = c2_g_b;
        c2_c_c = c2_n_a + c2_h_b;
        c2_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_j), 1, 4, 1, 0) - 1] = c2_c_c;
        c2_i_b = c2_jm1;
        c2_j_b = c2_i_b + 1;
        c2_jrow = c2_j_b;
        c2_o_a = c2_jrow;
        c2_k_b = c2_jpiv_offset;
        c2_p_a = c2_o_a;
        c2_l_b = c2_k_b;
        c2_jprow = c2_p_a + c2_l_b;
        c2_ix0 = c2_jrow;
        c2_iy0 = c2_jprow;
        c2_b_ix0 = c2_ix0;
        c2_b_iy0 = c2_iy0;
        c2_b_threshold(chartInstance);
        c2_c_ix0 = c2_b_ix0;
        c2_c_iy0 = c2_b_iy0;
        c2_ix = c2_c_ix0;
        c2_iy = c2_c_iy0;
        for (c2_k = 1; c2_k < 5; c2_k++) {
          c2_temp = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 16, 1, 0) - 1];
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_ix), 1, 16, 1, 0) - 1] = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK
            ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_iy), 1, 16, 1, 0) -
            1];
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_iy), 1, 16, 1, 0) - 1] = c2_temp;
          c2_q_a = c2_ix + 4;
          c2_ix = c2_q_a;
          c2_r_a = c2_iy + 4;
          c2_iy = c2_r_a;
        }
      }

      c2_b_jp1j = c2_jp1j;
      c2_s_a = c2_mmj;
      c2_t_a = c2_s_a;
      c2_d_c = c2_t_a;
      c2_u_a = c2_jp1j;
      c2_m_b = c2_d_c - 1;
      c2_v_a = c2_u_a;
      c2_n_b = c2_m_b;
      c2_i137 = c2_v_a + c2_n_b;
      c2_w_a = c2_b_jp1j;
      c2_o_b = c2_i137;
      c2_x_a = c2_w_a;
      c2_p_b = c2_o_b;
      if (c2_x_a > c2_p_b) {
        c2_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_overflow = (c2_p_b > 2147483646);
      }

      if (c2_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_overflow);
      }

      for (c2_i = c2_b_jp1j; c2_i <= c2_i137; c2_i++) {
        c2_b_i = c2_i;
        c2_x = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_b_i), 1, 16, 1, 0) - 1];
        c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_jj), 1, 16, 1, 0) - 1];
        c2_b_x = c2_x;
        c2_b_y = c2_y;
        c2_z = c2_b_x / c2_b_y;
        c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_i), 1, 16, 1, 0) - 1] = c2_z;
      }
    } else {
      *c2_info = c2_b_j;
    }

    c2_q_b = c2_b_j;
    c2_r_b = c2_q_b;
    c2_e_c = 4 - c2_r_b;
    c2_y_a = c2_jj;
    c2_ab_a = c2_y_a;
    c2_f_c = c2_ab_a;
    c2_bb_a = c2_jj;
    c2_cb_a = c2_bb_a;
    c2_g_c = c2_cb_a;
    c2_d4 = -1.0;
    c2_b_eml_xgeru(chartInstance, c2_mmj, c2_e_c, c2_d4, c2_jp1j, c2_f_c + 4,
                   c2_A, c2_g_c + 5);
  }

  if (*c2_info == 0) {
    if (!(c2_A[15] != 0.0)) {
      *c2_info = 4;
    }
  }
}

static void c2_b_eml_xgeru(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  int32_T c2_m, int32_T c2_n, real_T c2_alpha1, int32_T c2_ix0, int32_T c2_iy0,
  real_T c2_A[16], int32_T c2_ia0)
{
  int32_T c2_b_m;
  int32_T c2_b_n;
  real_T c2_b_alpha1;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_b_ia0;
  int32_T c2_c_m;
  int32_T c2_c_n;
  real_T c2_c_alpha1;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  int32_T c2_c_ia0;
  int32_T c2_d_m;
  int32_T c2_d_n;
  real_T c2_d_alpha1;
  int32_T c2_d_ix0;
  int32_T c2_d_iy0;
  int32_T c2_d_ia0;
  int32_T c2_e_m;
  int32_T c2_e_n;
  real_T c2_e_alpha1;
  int32_T c2_e_ix0;
  int32_T c2_e_iy0;
  int32_T c2_e_ia0;
  int32_T c2_ixstart;
  int32_T c2_a;
  int32_T c2_jA;
  int32_T c2_jy;
  int32_T c2_f_n;
  int32_T c2_b;
  int32_T c2_b_b;
  boolean_T c2_overflow;
  int32_T c2_j;
  real_T c2_yjy;
  real_T c2_temp;
  int32_T c2_ix;
  int32_T c2_c_b;
  int32_T c2_i138;
  int32_T c2_b_a;
  int32_T c2_d_b;
  int32_T c2_i139;
  int32_T c2_c_a;
  int32_T c2_e_b;
  int32_T c2_d_a;
  int32_T c2_f_b;
  boolean_T c2_b_overflow;
  int32_T c2_ijA;
  int32_T c2_b_ijA;
  int32_T c2_e_a;
  int32_T c2_f_a;
  int32_T c2_g_a;
  c2_b_m = c2_m;
  c2_b_n = c2_n;
  c2_b_alpha1 = c2_alpha1;
  c2_b_ix0 = c2_ix0;
  c2_b_iy0 = c2_iy0;
  c2_b_ia0 = c2_ia0;
  c2_c_m = c2_b_m;
  c2_c_n = c2_b_n;
  c2_c_alpha1 = c2_b_alpha1;
  c2_c_ix0 = c2_b_ix0;
  c2_c_iy0 = c2_b_iy0;
  c2_c_ia0 = c2_b_ia0;
  c2_d_m = c2_c_m;
  c2_d_n = c2_c_n;
  c2_d_alpha1 = c2_c_alpha1;
  c2_d_ix0 = c2_c_ix0;
  c2_d_iy0 = c2_c_iy0;
  c2_d_ia0 = c2_c_ia0;
  c2_e_m = c2_d_m;
  c2_e_n = c2_d_n;
  c2_e_alpha1 = c2_d_alpha1;
  c2_e_ix0 = c2_d_ix0;
  c2_e_iy0 = c2_d_iy0;
  c2_e_ia0 = c2_d_ia0;
  if (c2_e_alpha1 == 0.0) {
  } else {
    c2_ixstart = c2_e_ix0;
    c2_a = c2_e_ia0 - 1;
    c2_jA = c2_a;
    c2_jy = c2_e_iy0;
    c2_f_n = c2_e_n;
    c2_b = c2_f_n;
    c2_b_b = c2_b;
    if (1 > c2_b_b) {
      c2_overflow = false;
    } else {
      c2_eml_switch_helper(chartInstance);
      c2_overflow = (c2_b_b > 2147483646);
    }

    if (c2_overflow) {
      c2_check_forloop_overflow_error(chartInstance, c2_overflow);
    }

    for (c2_j = 1; c2_j <= c2_f_n; c2_j++) {
      c2_yjy = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_jy), 1, 16, 1, 0) - 1];
      if (c2_yjy != 0.0) {
        c2_temp = c2_yjy * c2_e_alpha1;
        c2_ix = c2_ixstart;
        c2_c_b = c2_jA + 1;
        c2_i138 = c2_c_b;
        c2_b_a = c2_e_m;
        c2_d_b = c2_jA;
        c2_i139 = c2_b_a + c2_d_b;
        c2_c_a = c2_i138;
        c2_e_b = c2_i139;
        c2_d_a = c2_c_a;
        c2_f_b = c2_e_b;
        if (c2_d_a > c2_f_b) {
          c2_b_overflow = false;
        } else {
          c2_eml_switch_helper(chartInstance);
          c2_b_overflow = (c2_f_b > 2147483646);
        }

        if (c2_b_overflow) {
          c2_check_forloop_overflow_error(chartInstance, c2_b_overflow);
        }

        for (c2_ijA = c2_i138; c2_ijA <= c2_i139; c2_ijA++) {
          c2_b_ijA = c2_ijA;
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_ijA), 1, 16, 1, 0) - 1] =
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_ijA), 1, 16, 1, 0) - 1] +
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_ix), 1, 16, 1, 0) - 1] * c2_temp;
          c2_e_a = c2_ix + 1;
          c2_ix = c2_e_a;
        }
      }

      c2_f_a = c2_jy + 4;
      c2_jy = c2_f_a;
      c2_g_a = c2_jA + 4;
      c2_jA = c2_g_a;
    }
  }
}

static void c2_c_eml_xtrsm(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[4])
{
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_kAcol;
  int32_T c2_i140;
  int32_T c2_a;
  int32_T c2_b_a;
  boolean_T c2_overflow;
  int32_T c2_i;
  int32_T c2_b_i;
  c2_c_threshold(chartInstance);
  c2_scalarEg(chartInstance);
  for (c2_k = 1; c2_k < 5; c2_k++) {
    c2_b_k = c2_k;
    c2_kAcol = (c2_b_k - 1) << 2;
    if (c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_k), 1, 4, 1, 0) - 1] != 0.0) {
      c2_i140 = c2_b_k + 1;
      c2_a = c2_i140;
      c2_b_a = c2_a;
      if (c2_b_a > 4) {
        c2_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_overflow = false;
      }

      if (c2_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_overflow);
      }

      for (c2_i = c2_i140; c2_i < 5; c2_i++) {
        c2_b_i = c2_i;
        c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_i), 1, 4, 1, 0) - 1] = c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK(
          "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 4, 1, 0) - 1]
          - c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_k), 1, 4, 1, 0) - 1] * c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK(
          "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)(c2_b_i + c2_kAcol)), 1,
          16, 1, 0) - 1];
      }
    }
  }
}

static void c2_d_eml_xtrsm(SFc2_SailingYachtModel2InstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[4])
{
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_kAcol;
  real_T c2_x;
  real_T c2_y;
  real_T c2_b_x;
  real_T c2_b_y;
  real_T c2_c_x;
  real_T c2_c_y;
  real_T c2_z;
  int32_T c2_i141;
  int32_T c2_b;
  int32_T c2_b_b;
  boolean_T c2_overflow;
  int32_T c2_i;
  int32_T c2_b_i;
  c2_c_threshold(chartInstance);
  c2_scalarEg(chartInstance);
  for (c2_k = 4; c2_k > 0; c2_k--) {
    c2_b_k = c2_k;
    c2_kAcol = (c2_b_k - 1) << 2;
    if (c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_k), 1, 4, 1, 0) - 1] != 0.0) {
      c2_x = c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_k), 1, 4, 1, 0) - 1];
      c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)(c2_b_k + c2_kAcol)), 1, 16, 1, 0) - 1];
      c2_b_x = c2_x;
      c2_b_y = c2_y;
      c2_c_x = c2_b_x;
      c2_c_y = c2_b_y;
      c2_z = c2_c_x / c2_c_y;
      c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_b_k), 1, 4, 1, 0) - 1] = c2_z;
      c2_i141 = c2_b_k - 1;
      c2_b = c2_i141;
      c2_b_b = c2_b;
      if (1 > c2_b_b) {
        c2_overflow = false;
      } else {
        c2_eml_switch_helper(chartInstance);
        c2_overflow = (c2_b_b > 2147483646);
      }

      if (c2_overflow) {
        c2_check_forloop_overflow_error(chartInstance, c2_overflow);
      }

      for (c2_i = 1; c2_i <= c2_i141; c2_i++) {
        c2_b_i = c2_i;
        c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_i), 1, 4, 1, 0) - 1] = c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK(
          "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 4, 1, 0) - 1]
          - c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_k), 1, 4, 1, 0) - 1] * c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK(
          "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)(c2_b_i + c2_kAcol)), 1,
          16, 1, 0) - 1];
      }
    }
  }
}

static void init_dsm_address_info(SFc2_SailingYachtModel2InstanceStruct
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

void sf_c2_SailingYachtModel2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1105361732U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3080238435U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3551370147U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3787071811U);
}

mxArray *sf_c2_SailingYachtModel2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("2iNogOqDrlBdlrI8dt8k3C");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,8,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));
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
      pr[0] = (double)(9);
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

mxArray *sf_c2_SailingYachtModel2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_SailingYachtModel2_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_SailingYachtModel2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"X_dot_ext\",},{M[8],M[0],T\"is_active_c2_SailingYachtModel2\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_SailingYachtModel2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_SailingYachtModel2InstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _SailingYachtModel2MachineNumber_,
           2,
           1,
           1,
           0,
           9,
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
          _SFD_SET_DATA_PROPS(1,2,0,1,"X_dot_ext");
          _SFD_SET_DATA_PROPS(2,1,1,0,"sail_coeff1");
          _SFD_SET_DATA_PROPS(3,1,1,0,"sail_coeff2");
          _SFD_SET_DATA_PROPS(4,1,1,0,"rudder_coeff1");
          _SFD_SET_DATA_PROPS(5,1,1,0,"rudder_coeff2");
          _SFD_SET_DATA_PROPS(6,1,1,0,"keel_coeff1");
          _SFD_SET_DATA_PROPS(7,1,1,0,"keel_coeff2");
          _SFD_SET_DATA_PROPS(8,1,1,0,"Frh_coeff");
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
        _SFD_CV_INIT_EML(0,1,1,2,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",618,-1,5007);
        _SFD_CV_INIT_EML_IF(0,1,0,2130,2152,2179,2266);
        _SFD_CV_INIT_EML_IF(0,1,1,2179,2206,2234,2266);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"modeleBoat",0,-1,2259);

        {
          unsigned int dimVector[1];
          dimVector[0]= 11;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 9;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c2_sail_coeff1;
          real_T *c2_sail_coeff2;
          real_T *c2_rudder_coeff1;
          real_T *c2_rudder_coeff2;
          real_T *c2_keel_coeff1;
          real_T *c2_keel_coeff2;
          real_T *c2_Frh_coeff;
          real_T (*c2_u)[11];
          real_T (*c2_X_dot_ext)[9];
          c2_Frh_coeff = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
          c2_keel_coeff2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c2_keel_coeff1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c2_rudder_coeff2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c2_rudder_coeff1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c2_sail_coeff2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c2_sail_coeff1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c2_X_dot_ext = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S,
            1);
          c2_u = (real_T (*)[11])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_u);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_X_dot_ext);
          _SFD_SET_DATA_VALUE_PTR(2U, c2_sail_coeff1);
          _SFD_SET_DATA_VALUE_PTR(3U, c2_sail_coeff2);
          _SFD_SET_DATA_VALUE_PTR(4U, c2_rudder_coeff1);
          _SFD_SET_DATA_VALUE_PTR(5U, c2_rudder_coeff2);
          _SFD_SET_DATA_VALUE_PTR(6U, c2_keel_coeff1);
          _SFD_SET_DATA_VALUE_PTR(7U, c2_keel_coeff2);
          _SFD_SET_DATA_VALUE_PTR(8U, c2_Frh_coeff);
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
  return "w4NXO9dVpMStYiZRNRjsWC";
}

static void sf_opaque_initialize_c2_SailingYachtModel2(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_SailingYachtModel2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_SailingYachtModel2((SFc2_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
  initialize_c2_SailingYachtModel2((SFc2_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_SailingYachtModel2(void *chartInstanceVar)
{
  enable_c2_SailingYachtModel2((SFc2_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_SailingYachtModel2(void *chartInstanceVar)
{
  disable_c2_SailingYachtModel2((SFc2_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_SailingYachtModel2(void *chartInstanceVar)
{
  sf_gateway_c2_SailingYachtModel2((SFc2_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_SailingYachtModel2(SimStruct*
  S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_SailingYachtModel2
    ((SFc2_SailingYachtModel2InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_SailingYachtModel2();/* state var info */
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

extern void sf_internal_set_sim_state_c2_SailingYachtModel2(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c2_SailingYachtModel2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_SailingYachtModel2((SFc2_SailingYachtModel2InstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_SailingYachtModel2(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_SailingYachtModel2(S);
}

static void sf_opaque_set_sim_state_c2_SailingYachtModel2(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_SailingYachtModel2(S, st);
}

static void sf_opaque_terminate_c2_SailingYachtModel2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_SailingYachtModel2InstanceStruct*) chartInstanceVar)
      ->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_SailingYachtModel2_optimization_info();
    }

    finalize_c2_SailingYachtModel2((SFc2_SailingYachtModel2InstanceStruct*)
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
  initSimStructsc2_SailingYachtModel2((SFc2_SailingYachtModel2InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_SailingYachtModel2(SimStruct *S)
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
    initialize_params_c2_SailingYachtModel2
      ((SFc2_SailingYachtModel2InstanceStruct*)(chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_SailingYachtModel2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_SailingYachtModel2_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,8);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 8; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2812765572U));
  ssSetChecksum1(S,(2957533611U));
  ssSetChecksum2(S,(291949086U));
  ssSetChecksum3(S,(3282463045U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_SailingYachtModel2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_SailingYachtModel2(SimStruct *S)
{
  SFc2_SailingYachtModel2InstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_SailingYachtModel2InstanceStruct *)utMalloc(sizeof
    (SFc2_SailingYachtModel2InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_SailingYachtModel2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_SailingYachtModel2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_SailingYachtModel2;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_SailingYachtModel2;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_SailingYachtModel2;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c2_SailingYachtModel2;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_SailingYachtModel2;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_SailingYachtModel2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_SailingYachtModel2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_SailingYachtModel2;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_SailingYachtModel2;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_SailingYachtModel2;
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

void c2_SailingYachtModel2_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_SailingYachtModel2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_SailingYachtModel2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_SailingYachtModel2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_SailingYachtModel2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
