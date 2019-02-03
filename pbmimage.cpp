#include <cstdio>
#include <cassert>
#include "pbmimage.hpp"

using uint = unsigned int;

PBMImage::PBMImage(uint W, uint H, color c) : W(W), H(H) {
  assert(W>0 && H>0);
  L = (W+7)>>3;
  M = new uint[L*H];
  uint c0 = (c ? 255 : 0);
  for (uint y=0; y<H; ++y)
    for (uint x=0; x<L; ++x) M[x+y*L] = c0;
}

PBMImage::~PBMImage() {
  delete M;
}

uint PBMImage::width() const {
  return W;
}

uint PBMImage::height() const {
  return H;
}

void PBMImage::set_pixel(uint x, uint y, color c) {
  //assert(0<=x && x<W && 0<=y && y<H);
  if (get_pixel(x,y)!=c) M[(x>>3)+y*L] ^= 1<<(7-(x&7));
}

PBMImage::color PBMImage::get_pixel(uint x, uint y) const {
  assert(0<=x && x<W && 0<=y && y<H);
  return (M[(x>>3)+y*L]>>(7-(x&7)))&1;
}

void PBMImage::save(const char *fname) const {
  FILE *F = fopen(fname, "w");
  fprintf(F, "P4\n%d %d\n", W, H);
  for (uint y=0; y<H; ++y)
    for (uint x=0; x<L; ++x)
      fprintf(F, "%c", M[x+y*L]);
  fclose(F);
}

void PBMImage::save_ascii(const char *fname) const {
  FILE *F = fopen(fname, "w");
  fprintf(F, "P1\n%d %d\n", W, H);
  for (uint y=0; y<H; ++y)
    for (uint x=0; x<W; ++x)
      fprintf(F, "%d%c", (M[(x>>3)+y*L]>>(7-(x&7)))&1, (x+1==W ? '\n' : ' '));
  fclose(F);
}
