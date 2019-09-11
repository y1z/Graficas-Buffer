#include "cChannel.h"

cChannel::cChannel()
  :m_Specifier(ChannelSpecifier::NONE),
  m_ChannelType(Types::NONE),
  IsUsed(true)
{}

cChannel::cChannel(const Types Type, const ChannelSpecifier Specifier, bool GoingToUse)
  :m_Specifier(Specifier),
  m_ChannelType(Type),
  IsUsed(GoingToUse)
{}

void cChannel::SetChannelSpecifier(const ChannelSpecifier Specifier)
{
  this->m_Specifier = Specifier;
}

void cChannel::SetChannelType(const Types Type)
{ this->m_ChannelType = Type; }

void cChannel::SetIsBeingUsed(const bool IsBeingUsed)
{ this->IsUsed = IsBeingUsed; }

ChannelSpecifier cChannel::GetSpecifier() const
{
  return  m_Specifier;
}

bool cChannel::IsChannelUsed() const
{
  return IsUsed;
}

Types cChannel::GetChannelType() const
{
  return this->m_ChannelType;
}
