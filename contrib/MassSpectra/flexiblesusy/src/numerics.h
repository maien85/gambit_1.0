
/** \file numerics.h
   - Project:     SOFTSUSY 
   - Author:      Ben Allanach 
   - Manual:      hep-ph/0104145, Comp. Phys. Comm. 143 (2002) 305 
   - Webpage:     http://hepforge.cedar.ac.uk/softsusy/

   \brief numerical routines - differential equation solver, differentiator
   and function minimiser for instance
*/

#ifndef NUMERICS_H
#define NUMERICS_H

/// Comment if you want default softsusy behaviour
// #define USE_LOOPTOOLS

#include "utils.h"
#include "mycomplex.h"
#include <iostream>
#include "def.h"
#include "linalg.h"

#define DoubleMatrix softsusy::DoubleMatrix

/// calculates root(1+x), where x<<1 accurately
double accurateSqrt1Plusx(double x);

/// Calculates log likelihood of a Poisson with k observed events, expecting
/// lambda>0. 
double lnLPoisson(unsigned k, double lambda);

/// Calculates likelihood of a Poisson with k observed events, expecting
/// lambda>0. 
double LPoisson(unsigned k, double lambda);

/// func is user-supplied, h is an estimate of what step-size to start with
/// and err returns error flags
double calcDerivative(double (*func)(double), 
		     double x, double h, double *err);

/// f is user-defined function, minimum value returned in xmin. Based on a
/// golden section search
double findMinimum(double ax, double bx, double cx, double (*f)(double),
		   double tol, double *xmin);

void shft2(double & a, double & b, double & c); ///< a=b and b=c
/// a=b, b=c and c=d
void shft3(double & a, double & b, double & c, double & d); 

/// For calculation of PV functions
double integrandThreshbn(double x);
/// For calculation of PV functions
double integrandThreshbnr(double x, int n1, double p, double m1, double m2, double mt);
/// Returns real part of b function, less accurate than analytic expressions
double bIntegral(int n, double p, double m1, double m2, double mt);
/// Returns real part of b function, less accurate than analytic expressions (thread-save version)
double bIntegral_threadsave(int n, double p, double m1, double m2, double mt);
// CHECK: is this function to be public?
// DoubleVector dd(double x, const DoubleVector & y);

/// Passarino-Veltman function definition
double b0(double p, double m1, double m2, double q);
double b0_fast(double p, double m1, double m2, double q);
/// Passarino-Veltman function definition
double b1(double p, double m1, double m2, double q);
/// Passarino-Veltman function definition
double b22(double p,  double m1, double m2, double q);
/// Passarino-Veltman function definition
double c0(double m1, double m2, double m3);
/// Passarino-Veltman function definition
double d27(double m1, double m2, double m3, double m4);
/// Passarino-Veltman function definition
double d0(double m1, double m2, double m3, double m4);

// inlined PV functions
inline double a0(double m, double q) {
   using std::fabs;
   using std::log;
  if (fabs(m) < softsusy::EPSTOL) return 0.;
  return sqr(m) * (1.0 - 2. * log(abs(m / q)));
}

inline double ffn(double p, double m1, double m2, double q) {
  return a0(m1, q) - 2.0 * a0(m2, q) - 
    (2.0 * sqr(p) + 2.0 * sqr(m1) - sqr(m2)) * 
    b0(p, m1, m2, q);
}

inline double gfn(double p, double m1, double m2, double q) {
  return (sqr(p) - sqr(m1) - sqr(m2)) * b0(p, m1, m2, q) - a0(m1, q) 
    - a0(m2, q); 
}

inline double hfn(double p, double m1, double m2, double q) {
  return 4.0 * b22(p, m1, m2, q) + gfn(p, m1, m2, q);
}

inline double b22bar(double p, double m1, double m2, double q) {
  return b22(p, m1, m2, q) - 0.25 * a0(m1, q) - 0.25 * a0(m2, q);
}

double fB(const softsusy::Complex & x);

double dilog(double x);

double integrandThreshbnr(double x);
softsusy::Complex fnfn(double x);
softsusy::Complex fnfn(double x, int n1, double p, double m1, double m2, double mt);

/// Gaussian deviated random number, mean 0 variance 1. Don't re-set idum once
/// you've initially set it. Initialise with a NEGATIVE integer
double gasdev(long & idum);
/// Gives 1/2 chance of being between 0 and 1 (flat), otherwise, a decreasing
/// Gaussian 
double truncGaussWidthHalf(long & idum);
/// Normally distributed random number between 0 and 1. Don't re-set idum once
/// you've initially set it. Initialise with a NEGATIVE integer
double ran1(long & idum);
/// Cauchy distribution ie 1 / [ pi gamma (1 + x^2/gamma^2) ]. For a width,
/// you must multiply the x coming out by the width. 
double cauchyRan(long & idum);

/// Returns the number of a bin that the data is in: from 1 to numBins in the
/// range (bins other than this range are also possible - you must deal with
/// them outside the function...)
int bin(double data, double start, double end, int numBins);

/// Adds logs of two numbers in a more careful way that avoids underflow
double logOfSum(double a, double b);

/// returns a random direction: total number of dimensions=n
softsusy::DoubleVector getRandomDirection(int n, int & numChanged, long & idum);

/// Calculates the vertical level of confidence level required to contain 
/// a fraction cl of area of the histogrammed binned likelihood l.
/// If err is true, a satisfactory answer could not be found for some reason.
double calcCL(double cl, const softsusy::DoubleVector & l);

/// given a normalised binned likelihood vector l, calculates the fraction of
/// bins with likelihood less than or equal to y as a % of maximum:
/// approximates area OUTSIDE confidence level y
double calc1dFraction(double y, const softsusy::DoubleVector & l);

/// These three functions are for the calculation of 2-loop log pieces of g-2
/// of the muon
double fps(double z);
double fs(double z);
double ffbar(double z);

softsusy::Complex dilog(const softsusy::Complex & x);

/// Trapezoidal function integration to accuracy tol
double trapzd(double (*func)(double), double a, double b, int n, 
	      double tol = 1.0e-3);
/// Driver for integration
double qtrap(double (*func)(double), double a, double b, double tol);
/// Mid point function integration
double midpnt(double (*func)(double), double a, double b, int n);
/// Integrate a function *func which is analytic to precision EPS between a
/// and b 
double qromb(double (*func)(double), double a, double b, double EPS);
/// Identical copy to facilitate double integral
double qromb2(double (*func)(double), double a, double b, double EPS);

/// This sums two exponentials nof the arguments in a way that tries to avoid
/// underflows. 
double sumOfExp(double a, double b);

/// Returns a value of the polynomial (y) and an error estimate (dy), given 
/// a bunch of points (xa) and their y values (ya).
void polint(const softsusy::DoubleVector&  xa, const softsusy::DoubleVector & ya, double x, 
	    double & y, double & dy);

/// Returns a 3 by 3 real mixing matrix. Input angles are standard CKM
/// parameterisation. If the phase d is not zero, the result is only an
/// approximation to the full complex matrix: see SOFTSUSY manual for
/// details. 
DoubleMatrix display3x3RealMixing(double theta12, double theta13, 
				  double theta23, double d);

/// Given a matrix v, determines which angles gave it
void getAngles(const DoubleMatrix & v, double & t12, double & t13, 
	       double & t23, double & d);
/// Evolves the dependent variables xi by one reversible mid-point step of
/// length tStep. Returns true if there is an error.
bool midPtStep(softsusy::DoubleVector & xi, 
	      softsusy::DoubleVector (*derivs)(double t, const softsusy::DoubleVector & v), 
	      double tInitial, double tStep);
/// Reversible integrate with numSteps steps between tInitial and tFinal. 
/// Returns true if there's an error
bool integrateReversibly(softsusy::DoubleVector & xi, 
			 softsusy::DoubleVector (*derivs)(double t, 
						const softsusy::DoubleVector & v), 
			 double tInitial, double tFinal, int numSteps);

/// useful for 2-loop mb/mt corrections
double fin(double mm1, double mm2);
double den(double a, int b); /// 1/a^b
/// This function DOESNT WORK YET!!!
double log1minusx(double x);
/// sign of inputs
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
/// returns a root of function func between x1 and x2 to accuracy xacc (x1 and
/// x2 MUST bracket a root)
double zriddr(double (*func)(double), double x1, double x2, double xacc);
/// Forward difference approximation to Jacobian matrix. On input, x is the
/// point to be evaluated, fvec is the vector of function values at the point,
/// and  vecfunc(n, x, f) is the Jacobian array
void fdjac(int n, softsusy::DoubleVector x, const softsusy::DoubleVector & fvec, DoubleMatrix & df,
	   void (*vecfunc)(const softsusy::DoubleVector &, softsusy::DoubleVector &));
/// These are experimental things for trying the shooting method - returns
/// F.F/2 evaluated at x. Boolean value on return is error flag
bool lnsrch(const softsusy::DoubleVector & xold, double fold, const softsusy::DoubleVector & g, 
	    softsusy::DoubleVector & p, 
	    softsusy::DoubleVector & x, double & f, double stpmax, 
	    void (*vecfunc)(const softsusy::DoubleVector &, softsusy::DoubleVector &), 
	    softsusy::DoubleVector & fvec);
/* allocate an int vector with subscript range v[nl..nh] */
int *ivector(long nl, long nh);
/* free an int vector allocated with ivector() */
void free_ivector(int *v, long nl, long nh);
void lubksb(const DoubleMatrix & a, int n, int *indx, softsusy::DoubleVector & b);
/// Multi-dimensional globally convergent multi-dimensional root solver for n
/// variables. adjusts x so that f(x)=0, where f is the last function provided
/// by vecfunc, given vector input x. If false on output, there is no
/// error. If returns 1, a local minimum or saddle-point has been found
/// (df/dx=0). The length of x should be equal to the number of parameters to
/// vary AND the number of constraints ie the length of the vector in vecfunc.
bool newt(softsusy::DoubleVector & x, 
	  void (*vecfunc)(const softsusy::DoubleVector &, softsusy::DoubleVector &));
/// calculates the n-vector y, given freely specifiable values v(1..n2) at x1
void load(float x, const softsusy::DoubleVector & v, softsusy::DoubleVector & y);
/// Gives a discrepancy vector f[1..n2] from ending boundary conditions at
/// endpoint x2 given values for y there
void score(float x, const softsusy::DoubleVector & y, softsusy::DoubleVector & f);
/// QR decomposition of the matrix a. A = Q.R. Upper triangular matrix R is
/// returned in upper triangle of a, except for diagonal elements which are
/// returned in d. Orthog matrix Q is given as a product of n-1 Houselholder
/// matrices $Q_1 \ldots Q_{n-1}$ where $Q_j=1-u_j \otimes u_j/c_j$. 
/// sing returns true (1) if singularity is encountered (but decomposition is
/// still completed) otherwise false (0).
void qrdcmp(DoubleMatrix & a, int n, softsusy::DoubleVector & c, softsusy::DoubleVector & d, 
	    int & sing);
void qrupdt(DoubleMatrix & r, DoubleMatrix & qt, int n, 
	    softsusy::DoubleVector & u, softsusy::DoubleVector & v);
/// Given r and qt, carry out a Jacobi rotation on rows i and i+1 of each
/// matrix. a and b are parameters of the rotation: $\cos
/// \theta=a/\sqrt{a^2+b^2}, \sin \theta = b / \sqrt{a^2 + b^2}$.
void rotate(DoubleMatrix & r, DoubleMatrix & qt, int n, int i, float a, 
	    float b);
void rsolv(const DoubleMatrix & a, int n, const softsusy::DoubleVector & d, 
	   softsusy::DoubleVector & b);

#undef DoubleMatrix

#endif

