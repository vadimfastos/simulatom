#ifndef ATOMMODEL_H
#define ATOMMODEL_H


#include <QString>


#define BOHR_RADIUS 0.52917720859e-10l


class AtomModel {

// Quantum numbers
    int qn, ql, qm;

// Type of model
    bool probability_density;

// Compute square of psi-function
    long double squareCartesian(long double x, long double y, long double z);
    long double squareSpherical(long double r, long double theta, long double phi);

// Get square of psi-function components
    long double squareRadialComponent(long double r);
    long double squareAngularComponent(long double theta, long double phi);

// Auxiliary functions
    long double LegendrePoly(long double x);
    long double LaguerrePoly(long double x);
    long long factor(int n);
    long double binpow(long double x, int n);

public:

// Set n=1, l=0, m=0, probability_density = false
    AtomModel();

// Set / get quantum numbers
    bool set_n(int n);
    bool set_l(int l);
    bool set_m(int m);
    int get_n() const;
    int get_l() const;
    int get_m() const;

// Set / get model type
    void setProbabilityDensityStatus(bool prob_dens);
    bool isProbabilityDensity() const;

// Get quantum state in text format
    QString getState() const;

// Return maximum radius value (relative), when abs(psi(r))^2 >> 0
    long double maxRelativeRadius();

// Compute models
    void modelGraphic(long double *p, int points);
    void model2D(long double *p, int width, int height);
    void model3D(long double *p, int width, int height, long double mov_x, long double mov_y, long double rot_x, long double rot_y);

};

#endif // ATOMMODEL_H
