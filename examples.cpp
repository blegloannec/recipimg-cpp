#include <cstdio>
#include <complex>
#include <cmath>
#include "pbmimage.hpp"
#include "pgmimage.hpp"
using namespace std;

using cpx = complex<double>;

PBMImage feigenbaum(int S, int Itr=500) {
  PBMImage Img(S,S);
  for (int i=0; i<S; ++i) {
    double mu = 2.*((double)i)/((double)S)+ 2., x = 0.5;
    for (int k=0; k<Itr; ++k) {
      x = mu*x*(1.-x);
      if (2*k>Itr) {
	int j = (int)(x*S);
	Img.set_pixel(i,S-1-j);
      }
    }
  }
  return Img;
}

PGMImage julia(const cpx &c, int S, int Itr=200) {
  PGMImage Img(S,S);
  for (int i=0; i<S; ++i) {
    double x = 3.*((double)i)/((double)S) - 1.5;
    for (int j=0; j<S; ++j) {
      double y = 3.*((double)j)/((double)S) - 1.5;
      cpx z(x,y);
      int k = 0;
      while (k<Itr && abs(z)<=2.) {
	z = z*z + c;
	++k;
      }
      Img.set_pixel(i,S-1-j,255-255*k/Itr);
    }
  }
  return Img;
}

int main() {
  PBMImage ImgB = feigenbaum(1000);
  ImgB.save("ex1_out.pbm");
  
  PGMImage ImgG = julia(cpx(-0.4,0.6),1000);
  ImgG.save("ex2_out.pgm");
  
  return 0;
}
