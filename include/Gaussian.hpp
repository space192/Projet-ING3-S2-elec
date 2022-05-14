#ifndef GAUSSIAN_HPP_INCLUDED
#define GAUSSIAN_HPP_INCLUDED
#include "lib.hpp"
class Gaussian
{
public:
  Gaussian(double u, double sigma, double weight)
  {
    this->u = u;
    this->sigma = sigma;
    this->weight = weight;
  }
  Gaussian() {}
  double getu() { return this->u; }
  double getsigma() { return this->sigma; }
  double getWeight() { return this->weight; }
  void setu(double u) { this->u = u; }
  void setsigma(double sigma) { this->sigma = sigma; }
  void setweight(double weight) { this->weight = weight; }

private:
  double u;     //
  double sigma; // sigma^2
  double weight;
};

//byte BhattacharyyaDistance(Gaussian *g);
byte KullbackLeiblerDivergence(Gaussian *g);
void findMaximums(double *t, uint8_t *tab2, int k);
double GaussianCalculus(Gaussian gauss, double x);
double TGaussianCalculus(Gaussian gaussT[], Gaussian gauss, double x);
void GMM_ALGORITHM(double tab[SAMPLES], Gaussian Gresult[K]);
#endif