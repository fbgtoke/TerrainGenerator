//
// Created by arnito on 19/08/16.
//

#include "Simplex2d.h"

const int Simplex2d::grad3[12][3] = {
  {1,1,0}, {-1,1,0}, {1,-1,0}, {-1,-1,0},
  {1,0,1}, {-1,0,1}, {1,0,-1}, {-1,0,-1},
  {0,1,1}, {0,-1,1}, {0,1,-1}, {0,-1,-1}
};

Simplex2d::Simplex2d(uint64_t seed, float frequency, float min, float max)
  : mSeed(seed), mFrequency(frequency), mMin(min), mMax(max) {
  
  generatePermutation();
}

Simplex2d::~Simplex2d(){}

float Simplex2d::getValue(float x, float y) const {
  return noise(x, y, mFrequency, mMin, mMax, mPermutations);
}

float Simplex2d::noise(float x, float y, float f, float min, float max, const int permutations[256*2]) {
  x = x * f;
  y = y * f;

  // Noise contributions from the three corners
  float n0, n1, n2;

  // Skew the input space to determine which simplex cell we're in
  float F2 = 0.5f * (sqrtf(3.0f) - 1.0f);
  // Hairy factor for 2D
  float s = (x + y) * F2;
  int i = fastfloor( x + s );
  int j = fastfloor( y + s );

  float G2 = (3.0f - sqrtf(3.0f)) / 6.0f;
  float t = (i + j) * G2;
  // Unskew the cell origin back to (x,y) space
  float X0 = i-t;
  float Y0 = j-t;
  // The x,y distances from the cell origin
  float x0 = x-X0;
  float y0 = y-Y0;

  // For the 2D case, the simplex shape is an equilateral triangle.
  // Determine which simplex we are in.
  int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
  if(x0>y0) {i1=1; j1=0;} // lower triangle, XY order: (0,0)->(1,0)->(1,1)
  else {i1=0; j1=1;} // upper triangle, YX order: (0,0)->(0,1)->(1,1)

  // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
  // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
  // c = (3-sqrt(3))/6
  float x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
  float y1 = y0 - j1 + G2;
  float x2 = x0 - 1.0f + 2.0f * G2; // Offsets for last corner in (x,y) unskewed coords
  float y2 = y0 - 1.0f + 2.0f * G2;

  // Work out the hashed gradient indices of the three simplex corners
  int ii = i & 255;
  int jj = j & 255;
  int gi0 = permutations[ii+permutations[jj]] % 12;
  int gi1 = permutations[ii+i1+permutations[jj+j1]] % 12;
  int gi2 = permutations[ii+1+permutations[jj+1]] % 12;

  // Calculate the contribution from the three corners
  float t0 = 0.5f - x0*x0-y0*y0;
  if(t0<0) n0 = 0.0;
  else {
      t0 *= t0;
      n0 = t0 * t0 * dot(grad3[gi0], x0, y0); // (x,y) of grad3 used for 2D gradient
  }

  float t1 = 0.5f - x1*x1-y1*y1;
  if(t1<0) n1 = 0.0;
  else {
      t1 *= t1;
      n1 = t1 * t1 * dot(grad3[gi1], x1, y1);
  }

  float t2 = 0.5f - x2*x2-y2*y2;
  if(t2<0) n2 = 0.0;
  else {
      t2 *= t2;
      n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
  }

  // Add contributions from each corner to get the final noise value.
  // The result is scaled to return values in the interval [-1,1].
  float result = 70.0f * (n0 + n1 + n2);
  //scale the result
  result += 1; //in [0,2]
  result *= 0.5; // in [0,1]
  float difference = max-min;
  return (min + difference * result);
}

float Simplex2d::fractal(float x, float y, unsigned int octaves, float lacunarity, float gain) {
  unsigned int i;

  float value = 0.f;
  float f = mFrequency;
  float a = mMax - mMin;
  for (i = 0; i < octaves; ++i) {
    value += a * noise(x, y, f, 0.f, 1.f, mPermutations);

    f *= lacunarity;
    a *= gain;
  }

  return value;
}

void Simplex2d::generatePermutation() {
  // seed engine
  std::mt19937_64 generator;
  generator.seed(mSeed);
  std::uniform_int_distribution<int> distribution(0,255);

  // reset table of permutations
  memset(&mPermutations[0], 0, 256 * sizeof(int));
  for (int i = 0; i < 256; i++) {
    mPermutations[i] = i;
  }
  
  // generate permutation
  std::shuffle(&mPermutations[0], &mPermutations[255], generator);
  memcpy(&mPermutations[256], &mPermutations[0], 256 * sizeof(int));
}

int Simplex2d::fastfloor( const float x ) { return x > 0 ? (int) x : (int) x - 1; }
float Simplex2d::dot( const int* g, const float x, const float y) { return g[0]*x + g[1]*y; }