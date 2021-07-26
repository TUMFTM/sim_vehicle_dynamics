cdef extern from "TireModel.h":
    void testinput(struct TireState* tirestate, const double *fz, const double *kappa, const double *alpha);
    void calcTirestatus(Parameters_dtm *param_dtm, struct TireState *tirestate, const double *vx, const double *vy, const double *psidot);
    void magicFormula52(struct Tireparameters *tire_param, struct TireState* tirestate, const double *gamma, const double *vx);
