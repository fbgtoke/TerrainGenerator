//
// Created by arnito on 19/08/16.
//

#ifndef SIMPLEX2D_H
#define SIMPLEX2D_H

#include "utils.h"

class Simplex2d {
public:
  Simplex2d(uint64_t seed, float frequency, float min, float max);
  ~Simplex2d();

  float getValue(float x, float y) const;

  static float noise(float x, float y, float f, float min, float max, const int permutations[256*2]);
  float fractal(float x, float y, unsigned int octaves, float lacunarity, float gain);

private:
  static const int grad3[12][3];
  uint64_t mSeed;

  int mPermutations[256*2];
  void generatePermutation();

  float mFrequency;
  float mMin;
  float mMax;

  inline static int fastfloor(const float x);
  inline static float dot(const int* g, const float x, const float y);
};


#endif // SIMPLEX2D_H
