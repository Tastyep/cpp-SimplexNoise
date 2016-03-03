#include "NoiseCaller.hh"

NoiseCaller::NoiseCaller() : idx(0) {
  callers = {[this](float x, float y, int octaves, float scale,
                    float lacunarity, float gain) -> float {
               return this->noise.fbm(x, y, octaves, scale, lacunarity, gain);
             },
             [this](float x, float y, int octaves, float scale,
                    float lacunarity, float gain) -> float {
               return this->noise.ridgedMf(x, y, octaves, scale, lacunarity,
                                           gain);
             }};
}

void NoiseCaller::setIdx(int idx) {
  this->idx = idx;
  if (this->idx < 0)
    this->idx = 0;
  else if (this->idx >= this->callers.size())
    this->idx = this->callers.size() - 1;
};

int NoiseCaller::getIdx() const { return this->idx; }

float NoiseCaller::call(float x, float y, int octaves, float scale,
                        float lacunarity, float gain) {
  return this->callers[this->idx](x, y, octaves, scale, lacunarity, gain);
}