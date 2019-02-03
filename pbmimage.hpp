#ifndef PBM_IMAGE_H
#define PBM_IMAGE_H

using uint = unsigned int;

class PBMImage {
public:
  typedef bool color;
  
  PBMImage(uint, uint, color=0);
  ~PBMImage();
  
  uint width() const;
  uint height() const;
  
  void set_pixel(uint, uint, color=1);
  color get_pixel(uint, uint) const;
  
  void save(const char*) const;
  void save_ascii(const char*) const;
  
private:
  uint W, H, L, *M;
};

#endif
