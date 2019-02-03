#ifndef PGM_IMAGE_H
#define PGM_IMAGE_H

using uint = unsigned int;

class PGMImage {
public:
  typedef unsigned char color;
  
  PGMImage(uint, uint, color=0, color=255);
  ~PGMImage();
  
  uint width() const;
  uint height() const;
  
  void set_pixel(uint, uint, color);
  color get_pixel(uint, uint) const;
  
  void save(const char*) const;
  void save_ascii(const char*) const;
  
private:
  uint W, H;
  color max_color;
  color *M;  
};

#endif
