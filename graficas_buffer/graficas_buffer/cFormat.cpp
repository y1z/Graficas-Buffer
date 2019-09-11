#include "cFormat.h"
#include <cassert>
cFormat::cFormat()
  :m_ActiveChannels(1),
  IsFloatFormat(false)
{}

cFormat::cFormat(uint8_t ActiveChannels, std::string_view StrView)
  : m_ActiveChannels(ActiveChannels),
  IsFloatFormat(false)
{
  this->ParseFormat(StrView);
}

void cFormat::ParseFormat(const std::string_view &StrView)
{
  static std::string Spcifiers = "RGBArgba";

  auto CheckForSpcifier = [&](const char PossibleMatch) ->bool {
    for (const char &chr : Spcifiers)
    {
      if (PossibleMatch == chr)
      { return true; }
    }
    return false;
  };

  std::size_t Indeces = 0;
  uint8_t InitilzedChannels = 0;
  // for when the values are floating point 
  if (StrView[0] == 'f' || StrView[0] == 'F')
  {
    this->IsFloatFormat = true;
    Indeces++;
  }

  while (Indeces < StrView.size())
  {
    if (CheckForSpcifier(StrView[Indeces]))
    {
      auto Test = StrView[Indeces];
      ChannelSpecifier Spec = this->GetSpecifier(Test);
      Types Type;
      Indeces++;
      if (Indeces < StrView.size())
      {
        Type = FindType(StrView, Indeces);
        m_Channels[InitilzedChannels].SetChannelSpecifier(Spec);
        m_Channels[InitilzedChannels].SetChannelType(Type);
      }
      else { break; }
    }
    else { break; }
    ++InitilzedChannels;
  }
  this->m_ActiveChannels = InitilzedChannels;
}

const cChannel &cFormat::GetChannel(uint8_t Index) const
{
  if ( Index <= 3 )
  {
    return  m_Channels[Index];
  }
  return m_Channels[0];
}

bool cFormat::CheckIsFloating() const
{
  return this->IsFloatFormat;
}

uint8_t cFormat::GetChannelCount() const
{
  return this->m_ActiveChannels;
}

ChannelSpecifier cFormat::GetSpecifier(char Channel)
{
  ChannelSpecifier result = ChannelSpecifier::NONE;

  switch (Channel)
  {
    // red channel
    case('r'):
    case('R'):
      result = ChannelSpecifier::R;
      break;
      // blue channel
    case('b'):
    case('B'):
      result = ChannelSpecifier::B;
      break;
      // Green channel
    case('g'):
    case('G'):
      result = ChannelSpecifier::G;
      break;
      // Alpha channel
    case('a'):
    case('A'):
      result = ChannelSpecifier::A;
      break;
    default:
      assert(result != ChannelSpecifier::NONE);
      return result;
      break;
  }


  return result;
}

Types cFormat::FindType(const std::string_view &StrView, std::size_t &Indeces)
{
  // the sizes the data can be in bits
  static const std::string DataSizes[] = {{"8"},{"16"},{"32"},{"64"}};
  //check for 8 bit value
  if (this->IsFloatFormat == false)
  {

    std::string Possible8Bits{StrView[Indeces]};
    if (!DataSizes[0].compare(Possible8Bits))
    {
      Indeces++;
      return Types::Interger8;
    }
    //find a matching 
    std::string PossibleMatch{StrView[Indeces], StrView[++Indeces]};
    // check the rest of the values
    if (Indeces + 1 <= StrView.size())
    {
      if (!DataSizes[1].compare(PossibleMatch)) { Indeces++; return Types::Interger16; }
      else if (!DataSizes[2].compare(PossibleMatch)) { Indeces++; return Types::Interger32; }
      else if (!DataSizes[3].compare(PossibleMatch)) { Indeces++; return Types::Interger64; }
    }
  }
  else
  {
    std::string PossibleMatch{StrView[Indeces], StrView[++Indeces]};

    if (!DataSizes[2].compare(PossibleMatch)) { Indeces++; return Types::Floating32; }
    else if (!DataSizes[3].compare(PossibleMatch)) { Indeces++; return Types::Floating64; }
  }
  return  Types::NONE;
}

