#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include "recouple.h"
#include "config.h"

typedef struct _HAMILTON_ {
  int pj;
  int dim;
  int n_basis;
  int hsize;
  int msize;
  int dim0;
  int n_basis0;
  int hsize0;
  int msize0;
  int lwork;
  int liwork;
  int *basis;
  double *hamilton;
  double *mixing;
  double *work;
  int *iwork;
  double *heff;
} HAMILTON;

typedef struct _SHAMILTON_ {
  int pj;
  int nbasis, nlevs;
  STATE **basis;
  unsigned char closed[MBCLOSE];
} SHAMILTON;

typedef struct _LEVEL_ {
  int pj;
  int iham, ilev;
  int n_basis;
  int pb;
  int kpb[NPRINCIPLE];
  int ibase;
  int *basis;
  short *ibasis;
  double *mixing;
  double energy;
} LEVEL;

typedef struct _LEVEL_ION_ {
  int imin;
  int imax;
} LEVEL_ION;

typedef struct _ANGZ_DATUM_ {
  int ns;
  int *nz;
  void **angz;
  double **mk;
} ANGZ_DATUM;

typedef struct _ANGULAR_ZMIX_ {
  double coeff;
  short k;
  short k0;
  short k1;
} ANGULAR_ZMIX;

typedef struct _ANGULAR_ZFB_ {
  double coeff;
  short kb;
} ANGULAR_ZFB;

typedef struct _ANGULAR_ZxZMIX_ {
  double coeff;
  short k;
  short k0;
  short k1;
  short k2;
  short k3;
} ANGULAR_ZxZMIX;

typedef struct _ANGULAR_FROZEN_ {
  int nts, ncs;
  int *ts, *cs;
  int *nz, *nzfb, *nzxzfb;
  ANGULAR_ZMIX **z;
  ANGULAR_ZFB **zfb;
  ANGULAR_ZxZMIX **zxzfb;
} ANGULAR_FROZEN;

typedef struct _ECORRECTION_ {
  int iref;
  int ilev;
  double e;
  int nmin;
  STATE *s;
} ECORRECTION;

typedef struct _TRANSITION_ {
    int nup;
    int nlo;
    LEVEL *lup;
    LEVEL *llo;
    double e;
} TRANSITION;

#ifdef PERFORM_STATISTICS
typedef struct _STRUCT_TIMING_ {
  double angz_mix;
  double angzxz_mix;
  double angz_fb;
  double angzxz_fb;
  double angz_states;
  double angz_states_load;
  long n_angz_states;
  long n_angz_states_load;
  double angzfb_states;
  double angzxzfb_states;
  double add_angz;
  double add_angzxz;
  double diag_ham;
  double set_ham;
} STRUCT_TIMING;
int GetStructTiming(STRUCT_TIMING *t);
#endif

void SetMaxKMBPT(int m);
int GetMaxKMBPT(void);
int SortUnique(int n, int *a);
int CompareInt(const void *a1, const void *a2);
int ConstructHamilton(HAMILTON *h,
    int isym, int k0, int k, int *kg, int kp, int *kgp, int md);
int ConstructHamiltonDiagonal(HAMILTON *h, int isym, int k, int *kg, int m);
int ValidBasis(STATE *s, int k, int *kg, int n);
int ConstructHamiltonFrozen(HAMILTON *h,
    int isym, int k, int *kg, int n, int nc, int *kc);
void HamiltonElement1E2E(int isym, int isi, int isj, double *r1, double *r2);
double HamiltonElement(int isym, int isi, int isj);
double HamiltonElementFrozen(int isym, int isi, int isj);
double HamiltonElementFB(int isym, int isi, int isj);
double Hamilton2E2(int n_shells, SHELL_STATE *sbra, 
		   SHELL_STATE *sket,INTERACT_SHELL *s);
double Hamilton2E(int n_shells, SHELL_STATE *sbra, 
		  SHELL_STATE *sket,INTERACT_SHELL *s);
double Hamilton1E(int n_shells, SHELL_STATE *sbra, 
		  SHELL_STATE *sket,INTERACT_SHELL *s);
HAMILTON *GetHamilton(void);
SHAMILTON *GetSHamilton(int *n);
int DiagnolizeHamilton(HAMILTON *h);
int AddToLevels(HAMILTON *h, int ng, int *kg);
int AddECorrection(int kref, int k, double e, int nmin);
LEVEL *GetLevel(int k);
LEVEL *GetEBLevel(int k);
int LevelTotalJ(int k);
int GetNumEBLevels(void);
int GetNumLevels(void);
int GetNumElectrons(int k);
int SortMixing(int start, int n, LEVEL *lev, SYMMETRY *sym);
int GetPrincipleBasis(double *mix, int d, int *kpb);
int CompareLevels(LEVEL *lev1, LEVEL *lev2);
int SortLevels(int start, int n, int m);
int GetBaseJ(STATE *s);
void AngularFrozen(int nts, int *ts, int ncs, int *cs);
void ClearAngularFrozen(void);
int PrepAngular(int n1, int *is1, int n2, int *is2);
int AngularZMix(ANGULAR_ZMIX **ang, int lower, int upper, int mink, int maxk,
		int *nmk, double **mbk);
int CompareAngularZMix(const void *c1, const void *c2);
int CompareAngularZxZMix(const void *c1, const void *c2);
int CompareAngularZFB(const void *c1, const void *c2);
int PackAngularZxZMix(int *n, ANGULAR_ZxZMIX **ang, int nz);
int PackAngularZMix(int *n, ANGULAR_ZMIX **ang, int nz);
int PackAngularZFB(int *n, ANGULAR_ZFB **ang, int nz);
int AngularZFreeBound(ANGULAR_ZFB **ang, int lower, int upper);
int AngularZMixStates(ANGZ_DATUM **ad, int ih1, int ih2);
int AngZSwapBraKet(int nz, ANGULAR_ZMIX *ang, int p);
int AngularZFreeBoundStates(ANGZ_DATUM **ad, int ih1, int ih2);
int AngularZxZMixStates(ANGZ_DATUM **ad, int ih1, int ih2);
int AngularZxZFreeBoundStates(ANGZ_DATUM **ad, int ih1, int ih2);
int AddToAngularZxZ(int *n, int *nz, ANGULAR_ZxZMIX **ang, 
		    int n_shells, int phase, SHELL_STATE *sbra, 
		    SHELL_STATE *sket, INTERACT_SHELL *s, int m);
int AddToAngularZxZMix(int *n, int *nz, ANGULAR_ZxZMIX **ang, 
		       int k, int k0, int k1, int k2, int k3, double coeff);
int AddToAngularZMix(int *n, int *nz, ANGULAR_ZMIX **ang,
		     int k, int k0, int k1, double coeff);
int AddToAngularZFB(int *n, int *nz, ANGULAR_ZFB **ang,
		    int kb, double coeff);
int AngularZxZFreeBound(ANGULAR_ZxZMIX **ang, int lower, int upper);
int GetBasisTable(char *fn, int m);
int ConstructLevelName(char *name, char *sname, char *nc, 
		       int *vnl, STATE *basis);
int GetTransition(int nlo, int nup, TRANSITION *tr, int *swapped);
int SaveLevels(char *fn, int m, int n);
int SaveEBLevels(char *fn, int m, int n);
int SetAngZOptions(int n, double mc, double c);
int SetAngZCut(double c);
int SetCILevel(int m);
int SetMixCut(double c, double c2);
int FreeAngZArray(void);
int InitAngZArray(void);
void ClearRMatrixLevels(int n);
int ClearLevelTable(void);
int InitStructure(void);
int ReinitStructure(int m);
int TestHamilton(void);
int ShellDegeneracy(int g, int nq);
void SetSymmetry(int p, int n, int *j);
int *GetSymmetrySet(int *p, int *nj);
int ZerothEnergyConfigSym(int n, int *s0, double **e);
void CutMixing(int nlev, int *ilev, int n, int *kg, double c);
void FlagClosed(SHAMILTON *h);
int IsClosedShell(int ih, int p);
int AllocHamMem(HAMILTON *h, int hdim, int nbasis);
void SetFields(double b, double e, double a, int m);
void GetFields(double *b, double *e, double *a);
int CodeBasisEB(int s, int m);
void DecodeBasisEB(int k, int *s, int *m);
int ConstructHamiltonEB(HAMILTON *h, int n, int *ilev);
void StructureEB(HAMILTON *h, char *fn, int n, int *ilev);
double HamiltonElementEB(int i, int j);

int SlaterCoeff(char *fn, int nlevs, int *ilevs, int na, SHELL *sa, 
		int nb, SHELL *sb);
void AddSlaterCoeff(double *c, double a, int n_shells, 
		    SHELL_STATE *sbra, SHELL_STATE *sket, 
		    INTERACT_SHELL *s, int na, SHELL *sa, 
		    int nb, SHELL *sb);

#endif



