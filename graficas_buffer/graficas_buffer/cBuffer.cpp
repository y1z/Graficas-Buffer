#include "cBuffer.h"
#include <iostream>
#include <memory>

auto GetSizeOfType = [](Types Type) -> uint32_t {
  switch (Type)
  {
    case Types::sInterger64:
      return sizeof(int64_t);
    case Types::sInterger32:
      return  sizeof(int32_t);
    case Types::sInterger16:
      return  sizeof(int16_t);
    case Types::sInterger8:
      return  sizeof(int8_t);
    case Types::NONE:
      return 0;
    case Types::Interger8:
      return  sizeof(uint8_t);
    case Types::Interger16:
      return  sizeof(uint16_t);
    case Types::Interger32:
      return  sizeof(uint32_t);
    case Types::Interger64:
      return sizeof(uint64_t);
    case Types::Floating32:
      return sizeof(float);
    case Types::Floating64:
      return sizeof(double);
    default:
      return 0;
  }
};

cBuffer::cBuffer()
  :mptr_Beginning(nullptr),
  mptr_ActivePointer(nullptr),
  mptr_End(nullptr),
  m_Type(Types::Interger8),
  m_Pitch(0),
  m_Width(0),
  m_Height(0),
  m_DataSize(0)
{}

cBuffer::~cBuffer()
{
  mptr_ActivePointer = ( char *) mptr_Beginning;
  mptr_Beginning = nullptr;
  mptr_End = nullptr;

  if (mptr_ActivePointer != nullptr)
  {
    std::free(mptr_ActivePointer);
  }
}

void cBuffer::Init(uint32_t width, uint32_t height, Types type)
{
  m_Width = width;
  m_Height = height;
  m_Type = type;

  if (m_Type != Types::Floating32 && m_Type != Types::Floating64)
  {
    mptr_Beginning = std::malloc(width * height * static_cast<int8_t>(type));
  }
  else
  {
    uint8_t SizeData = static_cast<int8_t>(type) + 1;
    mptr_Beginning = std::malloc(width * height * SizeData);
  }

  mptr_ActivePointer = static_cast<char *>(mptr_Beginning);

  if (m_Type != Types::Floating32 && m_Type != Types::Floating64)
  {
    m_Pitch = width * static_cast<int8_t>(type);
  }
  else
  {
    uint8_t SizeData = static_cast<int8_t>(type) + 1;
    m_Pitch = width * SizeData;
  }
  mptr_End = static_cast<char *>(mptr_Beginning) + (m_Pitch * m_Height);
  // for making sure all value start as a zero 
  this->Clear();
}

void cBuffer::Init(uint32_t width, uint32_t height, const cFormat &Format)
{
  m_Width = width;
  m_Height = height;
  IsFloat = Format.CheckIsFloating();
  for (uint32_t i = 0; i < Format.GetChannelCount(); ++i)
  {
    this->m_DataSize += GetSizeOfType(Format.GetChannel(i).GetChannelType());
  }

  m_Pitch = m_Width * m_DataSize;
  mptr_Beginning = std::malloc(width * height * m_DataSize);

  mptr_ActivePointer = static_cast<char *>(mptr_Beginning);

  mptr_End = static_cast<char *> (mptr_Beginning) + (m_Pitch * m_Height);
  m_Format = Format;
  this->Clear();
}

void cBuffer::Clear()
{
  while (mptr_ActivePointer != mptr_End)
  {
    std::memset(mptr_ActivePointer, 0, sizeof(char));
    mptr_ActivePointer++;
  }
  ResetActivePointer();
}

void cBuffer::PrintValues()
{
  // this will help me tell when to put a '\n' char in the output
  uint32_t IterationCount = 0;
  // this will be used to know which channel to access
  uint64_t ChannelCount = 0;

  while (mptr_ActivePointer < mptr_End)
  {
    Types type = m_Format.GetChannel(ChannelCount % 4).GetChannelType();
    if (ChannelCount % 4 == 0) { std::cout << "<"; }
    PrintByTypeAndMove(type);
    if (ChannelCount % 4 == 3) { std::cout << "> "; }

    if (IterationCount == m_Width * m_Format.GetChannelCount())
    {
      std::cout << std::endl;
      IterationCount = 0;
    }
    else
    {
      IterationCount++;
    }
    ChannelCount++;
  }
  std::cout << "\n-----------------------------------------------------\n";
  ResetActivePointer();
}

void cBuffer::FormatSet(uint32_t xPos, uint32_t yPos, int ValR, int ValG, int ValB, int ValA)
{
  if (MoveToPos(xPos, yPos))
  {
    for (int i = 0; i < m_Format.GetChannelCount(); ++i)
    {
      // set the individual r.g.b values 
      if (i == 0)
      { Set(m_Format.GetChannel(i).GetChannelType(), ValR); }
      else if (i == 1)
      { Set(m_Format.GetChannel(i).GetChannelType(), ValG); }
      else if (i == 2)
      { Set(m_Format.GetChannel(i).GetChannelType(), ValB); }
      else if (i == 3)
      { Set(m_Format.GetChannel(i).GetChannelType(), ValA); }
    }
  }
  ResetActivePointer();
}

void cBuffer::FormatSet(uint32_t xPos, uint32_t yPos, double ValR, double ValG, double  ValB, double ValA)
{
  if (MoveToPos(xPos, yPos))
  {
    for (int i = 0; i < m_Format.GetChannelCount(); ++i)
    {
      // set the individual r.g.b values 
      if (i == 0)
      { Set(m_Format.GetChannel(i).GetChannelType(), ValR); }
      else if (i == 1)
      { Set(m_Format.GetChannel(i).GetChannelType(), ValG); }
      else if (i == 2)
      { Set(m_Format.GetChannel(i).GetChannelType(), ValB); }
      else if (i == 3)
      { Set(m_Format.GetChannel(i).GetChannelType(), ValA); }
    }
  }
  ResetActivePointer();
}


void cBuffer::Set(Types type, int Val)
{
  if (this->m_Type == Types::Interger8)
  {
    *mptr_ActivePointer = Val;
    mptr_ActivePointer++;
  }
  else if (this->m_Type == Types::Interger16)
  {
    int16_t *Temp = ( int16_t *) mptr_ActivePointer;
    *Temp = Val;
    mptr_ActivePointer += sizeof(int16_t);
  }
  else if (this->m_Type == Types::Interger32)
  {
    int32_t *Temp = ( int32_t *) mptr_ActivePointer;
    *Temp = Val;
    mptr_ActivePointer += sizeof(int32_t);
  }
  else if (this->m_Type == Types::Interger64)
  {
    int64_t *Temp = ( int64_t *) mptr_ActivePointer;
    *Temp = Val;
    mptr_ActivePointer += sizeof(int64_t);
  }
}

void cBuffer::Set(Types type, double Val)
{
  if (type == Types::Floating32)
  {
    float *Temp = ( float *) mptr_ActivePointer;
    *Temp = ( float) Val;
    mptr_ActivePointer += sizeof(float);
  }
  else
  {
    double *Temp = ( double *) mptr_ActivePointer;
    *Temp = ( double) Val;
    mptr_ActivePointer += sizeof(double);
  }

}

void cBuffer::Set(uint32_t xPos, uint32_t yPos, double Val)
{
  if (this->m_Type == Types::Floating64 && this->MoveToPos(xPos, yPos))
  {
    double *Temp = ( double *) mptr_ActivePointer;
    *Temp = Val;
  }

  ResetActivePointer();
}

std::variant<int, float, double, int64_t>cBuffer::Get(uint32_t xPos, uint32_t yPos)
{
  std::variant<int, float, double, int64_t> Result;

  if (m_Type == Types::Interger8 && MoveToPos(xPos, yPos))
  {
    Result = *mptr_ActivePointer;
  }
  else if (this->m_Type == Types::Interger16 && this->MoveToPos(xPos, yPos))
  {
    int16_t *Temp = ( int16_t *) mptr_ActivePointer;
    Result = *Temp;
  }
  else if (this->m_Type == Types::Interger32 && this->MoveToPos(xPos, yPos))
  {
    int32_t *Temp = ( int32_t *) mptr_ActivePointer;
    Result = *Temp;
  }
  else if (this->m_Type == Types::Interger64 && this->MoveToPos(xPos, yPos))
  {
    int64_t *Temp = ( int64_t *) mptr_ActivePointer;
    Result = *Temp;
  }
  else if (this->m_Type == Types::Floating32 && this->MoveToPos(xPos, yPos))
  {
    float *Temp = ( float *) mptr_ActivePointer;
    Result = *Temp;
  }
  else if (this->m_Type == Types::Floating64 && this->MoveToPos(xPos, yPos))
  {
    double *Temp = ( double *) mptr_ActivePointer;
    Result = *Temp;
  }

  ResetActivePointer();
  return Result;
}

bool cBuffer::CheckIsFloat() const
{
  return IsFloat;
}

void cBuffer::PrintByTypeAndMove(Types Type)
{
  if (Type == Types::Interger8)
  {
    std::cout << '|' << static_cast<int>(*mptr_ActivePointer) << "| ";
    mptr_ActivePointer++;
  }
  else if (Type == Types::Interger16)
  {
    int16_t *Temp = ( int16_t *) mptr_ActivePointer;
    std::cout << '|' << static_cast<int16_t>(*Temp) << "| ";
    mptr_ActivePointer += sizeof(int16_t);
  }
  else if (Type == Types::Interger32)
  {
    int32_t *Temp = ( int32_t *) mptr_ActivePointer;
    std::cout << '|' << static_cast<int32_t>(*Temp) << "| ";
    mptr_ActivePointer += sizeof(int32_t);
  }
  else if (Type == Types::Interger64)
  {
    int64_t *Temp = ( int64_t *) mptr_ActivePointer;
    std::cout << '|' << static_cast<int64_t>(*Temp) << "| ";
    mptr_ActivePointer += sizeof(int64_t);
  }

  else if (Type == Types::Floating32)
  {
    float *Temp = ( float *) mptr_ActivePointer;
    std::cout << '|' << static_cast<float>(*Temp) << "| ";
    mptr_ActivePointer += sizeof(float);
  }
  else if (Type == Types::Floating64)
  {
    double *Temp = ( double *) mptr_ActivePointer;
    std::cout << '|' << static_cast<double>(*Temp) << "| ";
    mptr_ActivePointer += sizeof(double);
  }
}

void cBuffer::ResetActivePointer()
{
  this->mptr_ActivePointer = static_cast<char *>(this->mptr_Beginning);
}

bool cBuffer::MoveToPos(uint32_t xPos, uint32_t yPos)
{

  if (xPos > m_Width || xPos < 0)
  {
    printf_s("=================> x Position is out of bounds <==================\n");
    return false;
  }
  if (yPos > m_Height || yPos < 0)
  {
    printf_s("=================> y Position is out of bounds <==================\n");
    return false;
  }
  else
  {
    mptr_ActivePointer += ((yPos - 1) * m_Pitch) + ((xPos - 1) * (m_DataSize));
    return true;
  }
}
//!TODO : add function that move the pointer depending on the channel 
void cBuffer::MoveByChannel(int Channel)
{}
