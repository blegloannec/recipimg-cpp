#ifndef PPM_IMAGE_H
#define PPM_IMAGE_H

using uint = unsigned int;
using uchar = unsigned char;

struct RGB {
  uchar r,g,b;
  RGB(uchar r, uchar g, uchar b) : r(r), g(g), b(b) {}
};

class PPMImage {
public:
  typedef RGB color;
  
  PPMImage(uint, uint, const color&, uchar=255);
  ~PPMImage();
  
  uint width() const;
  uint height() const;
  
  void set_pixel(uint, uint, const color&);
  color get_pixel(uint, uint) const;
  
  void save(const char*) const;
  void save_ascii(const char*) const;
  
private:
  uint W, H, L;
  uchar max_color, *M;
};

#endif
