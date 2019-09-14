#pragma once
#include  <cinttypes> 
//Used to contain all possible values 
template<class T> 
struct RGBAvalues
{
  T colorChannels[4];

  uint32_t usedChannels{0};
};

using RGBf = RGBAvalues<float>;
using RGBdf = RGBAvalues<double>;
using RGBdi = RGBAvalues<int>;
using RGBdi64 = RGBAvalues<int64_t>;
using RGBdui64 = RGBAvalues<uint64_t>; 