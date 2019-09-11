#pragma once
#include "EnumsHeader.h"
/*! this class represent the individual channel in a
R,G,B,A signal */
class cChannel
{
public:// constructors
  cChannel();
  cChannel(const Types Type,const ChannelSpecifier Specifier, bool IsUsed = true );
public:// Functions
   /////////////// Set Functions
  void SetChannelSpecifier(const ChannelSpecifier Specifier);
  void SetChannelType (const Types Type );
  void SetIsBeingUsed(const bool IsBeingUsed);
  /////////////// Get Functions
  //! return the channel the instance of the class represent (R ,G ,B and A)
  ChannelSpecifier GetSpecifier() const;
  //! tell me if the channel is being used
  bool IsChannelUsed() const;
  //! return the data type that the channel represent
  Types GetChannelType() const;
private:// variables

  ChannelSpecifier m_Specifier;
  //! what type of data the channel contains
  Types m_ChannelType;
  //! to now if this channel is being used
  bool IsUsed = false;
};

