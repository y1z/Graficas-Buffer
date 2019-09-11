#pragma once
#include "EnumsHeader.h"
#include "cChannel.h"
#include <string_view>

class cFormat
{
public:// constructors
  cFormat();
  /*! \param ActiveChannels tell me the amount of channels this format has
  \param StrView is the string I'm going to parse to find out the format*/
  cFormat(uint8_t ActiveChannels, std::string_view StrView);
public: // functions
  void ParseFormat(const std::string_view &StrView);
//! To get the channels 
  const cChannel &GetChannel(uint8_t Index) const;
//! used to know if the format uses floating point values 
  bool CheckIsFloating() const;
  
  uint8_t GetChannelCount() const;

private:
  ChannelSpecifier GetSpecifier(char Channel);
  Types FindType(const std::string_view &StrView, std::size_t &Indeces);
  cChannel m_Channels[4];
  //! used to how many channels where dealing with.
  uint8_t m_ActiveChannels{1};
  bool IsFloatFormat;
};

