#include "atommodel.h"
#include "vectormatrix.h"


AtomModel::AtomModel() :
    qn(1),
    ql(0),
    qm(0),
    probability_density(false) {
}


// Set main quantum number
bool AtomModel::set_n(int n)
{
    if (n < 1)
        return false;
    qn = n;
    return true;
}


// Set orbital quantum number
bool AtomModel::set_l(int l)
{
    if (l < 0 || l > qn-1)
        return false;
    ql = l;
    return true;
}


// Set magnetic quantum number
bool AtomModel::set_m(int m)
{
    if (m < -ql || m > ql)
        return false;
    qm = m;
    return true;
}


// Get main quantum number
int AtomModel::get_n() const
{
    return qn;
}


// Get orbital quantum number
int AtomModel::get_l() const
{
    return ql;
}


// Get magnetic quantum number
int AtomModel::get_m() const
{
    return qm;
}


// Set model type
void AtomModel::setProbabilityDensityStatus(bool prob_dens)
{
    probability_density = prob_dens;
}


// Get model type
bool AtomModel::isProbabilityDensity() const
{
    return probability_density;
}


// Get quantum state in text format
QString AtomModel::getState() const
{
    QString state;
    state.setNum(qn);
    const char lstate[] = "spdfgh";
    if ((unsigned)ql < sizeof(lstate))
        state = state + lstate[ql];
    return state;
}


// Compute graphic model
void AtomModel::modelGraphic(long double *p, int points) {

    long double dr = BOHR_RADIUS * maxRelativeRadius() / points;

// Compute probability or probability density
    if (probability_density) {
        for (int r=0; r<points; r++)
            p[r] = squareRadialComponent(dr * r);
    } else {
        for (int r=0; r<points; r++)
            p[r] = squareRadialComponent(dr * r) * r * r;
    }

// Go to the relative values, dividing all values ​​by the maximum
    long double pmax = 0;
    for (int r=0; r<points; r++)
        if (p[r] > pmax)
            pmax = p[r];
    for (int r=0; r<points; r++)
        p[r] /= pmax;
}


// Compute 2D model
void AtomModel::model2D(long double *p, int width, int height) {

    long double dr = maxRelativeRadius() * BOHR_RADIUS / sqrt(height*height + width*width) * 2;

    for (int yy=0; yy<height; yy++)
        for (int xx=0; xx<width; xx++) {

            // Compute radius and theta
                long double z = height/2 - yy;
                long double xy = xx - width/2;
                long double r = sqrt(z*z + xy*xy);
                long double theta = acos(z / r);
                r *= dr;

            // Compute probability or probability density
                if (probability_density) {
                    p[yy*width + xx] = squareSpherical(r, theta, 0);
                } else {
                    p[yy*width + xx] = squareSpherical(r, theta, 0) * r * r;
                }
        }

// Go to the relative values, dividing all values ​​by the maximum
    long double pmax = 0;
    for (int i=0; i<height*width; i++)
        if (p[i] > pmax)
            pmax = p[i];
    for (int i=0; i<height*width; i++)
        p[i] /= pmax;
}


// Compute 3D model
void AtomModel::model3D(long double *p, int width, int height, long double mov_x, long double mov_y, long double rot_x, long double rot_y) {

    long double dr = maxRelativeRadius() * BOHR_RADIUS;

// Compute camera rotation matrix
    Matrix3x3 yrot = Matrix3x3(cos(rot_y), 0, sin(rot_y),\
                               0, 1, 0,\
                               -sin(rot_y), 0, cos(rot_y));
    Matrix3x3 xrot = Matrix3x3(1, 0, 0,\
                               0, cos(rot_x), -sin(rot_x),\
                               0, sin(rot_x), cos(rot_x));
    Matrix3x3 camera_rotation = xrot * yrot;

// Compute camera position vector
    Vector3D camera_position(0, mov_x, mov_y) ;
    camera_position *= 0.2;

// Per pixel modelling
    long double scale_coeff = 2.0l / sqrt(height*height + width*width);
    for (int yy=0; yy<height; yy++)
        for (int xx=0; xx<width; xx++) {

        // Compute canvas coordinates
            long double cx = (xx - width/2) * scale_coeff;
            long double cy = (height/2 - yy) * scale_coeff;

        // Compute 3D coordinates
            Vector3D xyz = Vector3D(0, cx, cy) - camera_position;
            xyz = camera_rotation * xyz;
            long double x = xyz.x * dr;
            long double y = xyz.y * dr;
            long double z = xyz.z * dr;

        // Compute probability or probability density
            if (probability_density) {
                p[yy*width + xx] = squareCartesian(x, y, z);
            } else {
                p[yy*width + xx] = squareCartesian(x, y, z) * (x*x+y*y+z*z);
            }
        }

// Go to the relative values, dividing all values ​​by the maximum
    long double pmax = 0;
    for (int i=0; i<height*width; i++)
        if (p[i] > pmax)
            pmax = p[i];
   for (int i=0; i<height*width; i++)
        p[i] /= pmax;
}


// Return maximum radius value (relative), when abs(psi(r))^2 >> 0
long double AtomModel::maxRelativeRadius() {
    long double rr = qn * qn;
    if (isProbabilityDensity())
        rr /= 2;
    return rr * 10 / log(qn+7);
}


// Get square of psi-function in cartesian coordinates
long double AtomModel::squareCartesian(long double x, long double y, long double z)
{
// Go to spherical coordinates
    long double r = sqrt(x*x + y*y + z*z);
    long double theta = acos(z / r);
    long double phi = atan2(y, x);
// Compute square of psi-function in spherical coordinates
    return squareSpherical(r, theta, phi);
}


// Get square of psi-function in spherical coordinates
long double AtomModel::squareSpherical(long double r, long double theta, long double phi)
{
    // phi(r,theta,phi) = R(r) * O(theta) * F(phi) = R(r) * Y(theta, phi)
    return squareRadialComponent(r) * squareAngularComponent(theta, phi);
}


// Compute square of radial component
long double AtomModel::squareRadialComponent(long double r) {

    long double q = 2 * r / BOHR_RADIUS / qn;
    long double R = sqrt(1.0l * factor(qn-ql-1) / (2*qn) / factor(qn+ql));
    R *= pow(2 / BOHR_RADIUS / qn, 1.5 + ql);
    R *= pow(r, ql);
    R *= exp(-q * 0.5);
    R *= LaguerrePoly(q);

// Return square of radial component
    return R * R;
}


// Compute square of angular component
long double AtomModel::squareAngularComponent(long double theta, long double phi) {

    long double Y = sqrt( 1.0l * (2*ql+1) * factor(ql-abs(qm)) / (4*M_PI * factor(ql + abs(qm))) );
    Y *= LegendrePoly(cos(theta));

// Return square of angular component
    return Y*Y;
}


// Compute associated Legendre polynomial
long double AtomModel::LegendrePoly(long double x) {

// Compute associated Legendre indexes
    int n = ql;
    int m = abs(qm);

// Use formula
    long double P = 0;
    for (int i=m; i<=n; i++) {
        long double cur = 1.0l * factor(n+m) / factor(i) / factor(n-i);
        cur *= factor(n) / factor(i-m) * binpow(x-1, i-m);
        cur *= factor(n) / factor(n-i) * binpow(x+1, n-i);
        P += cur;
    }
    P *= pow(1 - x*x, 0.5*m) / pow(2, n) / factor(n);

    return P;
}


// Compute associated Laguerre polynomial
long double AtomModel::LaguerrePoly(long double x) {

// Compute associated Laguerre polynomial indexes
    int a = 2*ql+1;
    int n = qn-ql-1;

// Use reccurent formula
    long double L[n+2];
    L[0] = 1;
    L[1] = 1 + a - x;
    for (int i=1; i<n; i++)
        L[i+1] = ( (2*i+1-a-x) * L[i] - (i+a) * L[i-1] ) / (i+1);

    return L[n];
}


// Compute n factorial
long long AtomModel::factor(int n) {
    const long long factorials[] = {\
        1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800,\
        39916800, 479001600, 6227020800, 87178291200, 1307674368000, 20922789888000,\
        355687428096000, 6402373705728000, 121645100408832000, 2432902008176640000,\
    };
    if (n >= 0 && n <= 20)
        return factorials[n];
    return 0;
}


// Compute x^n, n - integer
long double AtomModel::binpow(long double x, int n) {
    if (n < 0)
        return 1 / binpow(x, -n);
    long double y = 1;
    while (n > 0) {
        if (n & 1)
            y *= x;
        x *= x;
        n /= 2;
    }
    return y;
}
