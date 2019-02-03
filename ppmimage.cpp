#include <cstdio>
#include <cassert>
#include "ppmimage.hpp"

using uint = unsigned int;
using uchar = unsigned char;

PPMImage::PPMImage(uint W, uint H, const color &C, uchar max_color) : W(W), H(H), max_color(max_color) {
  assert(W>0 && H>0);
  L = 3*W;
  M = new uchar[L*H];
  for (uint y=0; y<H; ++y)
    for (uint x=0; x<W; ++x) set_pixel(x,y,C);
}

PPMImage::~PPMImage() {
  delete M;
}

uint PPMImage::width() const {
  return W;
}

uint PPMImage::height() const {
  return H;
}

void PPMImage::set_pixel(uint x, uint y, const color &C) {
  assert(0<=x && x<W && 0<=y && y<H);
  M[3*x   + y*L] = C.r;
  M[3*x+1 + y*L] = C.g;
  M[3*x+2 + y*L] = C.b;
}

PPMImage::color PPMImage::get_pixel(uint x, uint y) const {
  assert(0<=x && x<W && 0<=y && y<H);
  return RGB(M[3*x+y*L], M[3*x+1+y*L], M[3*x+2+y*L]);
}

void PPMImage::save(const char *fname) const {
  FILE *F = fopen(fname, "w");
  fprintf(F, "P6\n%d %d\n%d\n", W, H, max_color);
  for (uint y=0; y<H; ++y)
    for (uint x=0; x<L; ++x)
      fprintf(F, "%c", M[x+y*L]);
  fclose(F);
}

void PPMImage::save_ascii(const char *fname) const {
  FILE *F = fopen(fname, "w");
  fprintf(F, "P3\n%d %d\n%d\n", W, H, max_color);
  for (uint y=0; y<H; ++y)
    for (uint x=0; x<L; ++x)
      fprintf(F, "%d%c", M[x+y*L], (x+1==L ? '\n' : ' '));
  fclose(F);
}
