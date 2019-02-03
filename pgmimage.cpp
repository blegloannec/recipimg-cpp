#include <cstdio>
#include <cassert>
#include "pgmimage.hpp"

using uint = unsigned int;

PGMImage::PGMImage(uint W, uint H, color c, color max_color) : W(W), H(H), max_color(max_color) {
  assert(W>0 && H>0);
  assert(c<=max_color);
  M = new color[W*H];
  for (uint y=0; y<H; ++y)
    for (uint x=0; x<W; ++x) M[x+y*W] = c;
}

PGMImage::~PGMImage() {
  delete M;
}

uint PGMImage::width() const {
  return W;
}

uint PGMImage::height() const {
  return H;
}

void PGMImage::set_pixel(uint x, uint y, color c) {
  assert(0<=x && x<W && 0<=y && y<H);
  assert(c<=max_color);
  M[x+y*W] = c;
}

PGMImage::color PGMImage::get_pixel(uint x, uint y) const {
  assert(0<=x && x<W && 0<=y && y<H);
  return M[x+y*W];
}

void PGMImage::save(const char *fname) const {
  FILE *F = fopen(fname, "w");
  fprintf(F, "P5\n%d %d\n%d\n", W, H, max_color);
  for (uint y=0; y<H; ++y)
    for (uint x=0; x<W; ++x)
      fprintf(F, "%c", M[x+y*W]);
  fclose(F);
}

void PGMImage::save_ascii(const char *fname) const {
  FILE *F = fopen(fname, "w");
  fprintf(F, "P2\n%d %d\n%d\n", W, H, max_color);
  for (uint y=0; y<H; ++y)
    for (uint x=0; x<W; ++x)
      fprintf(F, "%d%c", M[x+y*W], (x+1==W ? '\n' : ' '));
  fclose(F);
}
