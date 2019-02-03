#include <cstdio>
#include <complex>
#include <cmath>
#include "pbmimage.hpp"
#include "pgmimage.hpp"
#include "ppmimage.hpp"
using namespace std;

using cpx = complex<double>;

PBMImage feigenbaum_b(int S, int Itr=500) {
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

PGMImage julia_g(const cpx &c, int S, int Itr=200) {
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

PPMImage julia_p(const cpx &c, int S, int Itr=500) {
  PPMImage Img(S,S,RGB(255,255,255));
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
      int v = 255-255*k/Itr;
      Img.set_pixel(i,S-1-j,RGB((int)(abs(sin(6*M_PI*k/Itr))*v),(int)(abs(cos(7*M_PI*k/Itr))*v),(int)(abs(sin(8*M_PI*k/Itr+0.5))*v)));
    }
  }
  return Img;
}

int main() {
  PBMImage ImgB = feigenbaum_b(1000);
  ImgB.save("ex1_out.pbm");
  
  PGMImage ImgG = julia_g(cpx(-0.4,0.6),1000);
  ImgG.save("ex2_out.pgm");
  
  PPMImage ImgP = julia_p(cpx(-0.4,0.6),1000);
  ImgP.save("ex3_out.ppm");
  
  return 0;
}
