#pragma once
#include <cstdint>
//! this help to identify the
enum class Types : int8_t
{
  sInterger64 = -8,
  sInterger32 = -4,
  sInterger16 = -2,
  sInterger8 = -1,
  NONE = 0,
  Interger8 = 1,
  Interger16 = 2,
  Interger32 = 4,
  Interger64 = 8,

  Floating32 = 3,
  Floating64 = 7
};
//! This help identify which Channel the cChannel class belongs to
enum class ChannelSpecifier : uint8_t
{
  NONE = 0,
  R = 1,
  G = 2,
  B = 3,
  A = 4
};
