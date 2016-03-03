#ifndef NOISECALLER_HH_
#define NOISECALLER_HH_

#include "Noise.hh"

#include <functional>
#include <vector>

class NoiseCaller {
public:
  NoiseCaller();

  ~NoiseCaller() = default;
  NoiseCaller(const NoiseCaller &other) = default;
  NoiseCaller(NoiseCaller &&other) = default;
  NoiseCaller &operator=(const NoiseCaller &other) = default;
  NoiseCaller &operator=(NoiseCaller &&other) = default;

  void setIdx(int idx);
  int getIdx() const;
  float call(float x, float y, int octaves = 2, float scale = 1,
             float lacunarity = 1, float gain = 0.5);

private:
  Noise noise;
  std::vector<std::function<float(float x, float y, int octaves, float scale,
                                  float lacunarity, float gain)>>
      callers;
  int idx;
};

#endif /* end of include guard: NOISECALLER_HH_ */
