cdef extern from "config.hpp":
    pass

cdef extern from "debye_hueckel.hpp":
    ctypedef struct Debye_hueckel_params:
        double kappa
        double r_cut

    Debye_hueckel_params dh_params
    int dh_set_params(double kappa, double r_cut)
