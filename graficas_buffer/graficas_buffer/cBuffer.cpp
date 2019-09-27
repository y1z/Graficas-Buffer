#include "cBuffer.h"
#include <iostream>
#include <memory>
#include <algorithm>

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

auto calculateAverageVector = [](const CVector2D &lowerVec, const CVector2D &upperVec) {
  float averageX = (lowerVec.GetX() + upperVec.GetX()) / 2;
  float averageY = (lowerVec.GetY() + upperVec.GetY()) / 2;
  return CVector2D(averageX, averageY);
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

  while (mptr_ActivePointer < mptr_End)
  {
    std::cout << "<";
    for (int i = 0; i < m_Format.GetChannelCount(); ++i)
    {
      Types type = m_Format.GetChannel(i).GetChannelType();
      PrintByTypeAndMove(type);
    }
    std::cout << "> ";
    IterationCount++;

    if (IterationCount == m_Width)
    {
      std::cout << std::endl;
      IterationCount = 0;
    }
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
  if (type == Types::Interger8)
  {
    *mptr_ActivePointer = Val;
    mptr_ActivePointer++;
  }
  else if (type == Types::Interger16)
  {
    int16_t *Temp = ( int16_t *) mptr_ActivePointer;
    *Temp = Val;
    mptr_ActivePointer += sizeof(int16_t);
  }
  else if (type == Types::Interger32)
  {
    int32_t *Temp = ( int32_t *) mptr_ActivePointer;
    *Temp = Val;
    mptr_ActivePointer += sizeof(int32_t);
  }
  else if (type == Types::Interger64)
  {
    int64_t *Temp = ( int64_t *) mptr_ActivePointer;
    *Temp = ( int64_t) Val;
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

std::variant<int, float, double, int64_t> cBuffer::GetValueByType(Types type)
{
  std::variant<int, float, double, int64_t> Result;

  if (type == Types::Interger8)
  {
    Result = *mptr_ActivePointer;
  }
  else if (type == Types::Interger16)
  {
    int16_t *Temp = ( int16_t *) mptr_ActivePointer;
    Result = *Temp;
  }
  else if (type == Types::Interger32)
  {
    int32_t *Temp = ( int32_t *) mptr_ActivePointer;
    Result = *Temp;
  }
  else if (type == Types::Interger64)
  {
    int64_t *Temp = ( int64_t *) mptr_ActivePointer;
    Result = *Temp;
  }
  else if (type == Types::Floating32)
  {
    float *Temp = ( float *) mptr_ActivePointer;
    Result = *Temp;
  }
  else if (type == Types::Floating64)
  {
    double *Temp = ( double *) mptr_ActivePointer;
    Result = *Temp;
  }

  return Result;
}

RGBdf cBuffer::GetValues(uint32_t xPos, uint32_t yPos)
{
  RGBdf Result;
  if (MoveToPos(xPos, yPos))
  {
    for (int i = 0; i < m_Format.GetChannelCount(); ++i)
    {
      std::variant<int, float, double, int64_t>  Temp = GetValueByType(m_Format.GetChannel(i).GetChannelType());

      if (auto * Val = std::get_if<int>(&Temp))
      { Result.colorChannels[i] = *Val; }

      else if (auto * Val = std::get_if<int64_t>(&Temp))
      { Result.colorChannels[i] = *Val; }

      else if (auto * Val = std::get_if<float>(&Temp))
      { Result.colorChannels[i] = *Val; }

      else if (auto * Val = std::get_if<double>(&Temp))
      { Result.colorChannels[i] = *Val; }

      MoveByChannel(i);
    }

  }

  Result.usedChannels = m_Format.GetChannelCount();

  ResetActivePointer();
  return Result;
}

bool cBuffer::CheckIsFloat() const
{
  return IsFloat;
}

void cBuffer::drawLine(CVector2D &originPoint, CVector2D &endPoint, RGBdf Value)
{

  float deltaX = endPoint.GetX() - originPoint.GetX();
  float deltaY = endPoint.GetY() - originPoint.GetY();
  //  determines how when to move in Y  
  float pendentForY = deltaX / deltaY;

  //the following 2 values are for always drawing the line left to right  
  uint32_t smallestX = std::min(originPoint.GetX(), endPoint.GetX());
  uint32_t biggestX = std::max(originPoint.GetX(), endPoint.GetX());

  // going up in y 
  if (pendentForY > 0.0f)
  {
    uint32_t  BufferYpos = std::min(originPoint.GetY(), endPoint.GetY());
    float currentYPosInSegment = 0.0f;

    for (size_t i = smallestX; i <= biggestX; ++i)
    {
      if (currentYPosInSegment > 0.998f)
      {
        BufferYpos += static_cast<uint32_t>(currentYPosInSegment);
        currentYPosInSegment = 0.0f;
      }
      currentYPosInSegment += pendentForY;
      this->FormatSet(i, BufferYpos,
                      Value.colorChannels[0], Value.colorChannels[1],
                      Value.colorChannels[2], Value.colorChannels[3]);
    }
  }
  // going down in y 
  else
  {
    uint32_t  BufferYpos = std::max(originPoint.GetY(), endPoint.GetY());
    float currentYPosInSegment = 0.0f;

    for (size_t i = smallestX; i <= biggestX; ++i)
    {
      if (currentYPosInSegment < -0.998f)
      {
        BufferYpos += static_cast<uint32_t>(currentYPosInSegment);
        currentYPosInSegment = 0.0f;
      }
      currentYPosInSegment += pendentForY;
      this->FormatSet(i, BufferYpos,
                      Value.colorChannels[0], Value.colorChannels[1],
                      Value.colorChannels[2], Value.colorChannels[3]);
    }
  }
}

void cBuffer::drawLine(CVector2D &originPoint, CVector2D &endPoint, RGBdi Value)
{
  float deltaX = endPoint.GetX() - originPoint.GetX();
  float deltaY = endPoint.GetY() - originPoint.GetY();
  //  determines how when to move in Y  
  float pendentForY = deltaX / deltaY;

  //the following 2 values are for always drawing the line left to right  
  uint32_t smallestX = std::min(originPoint.GetX(), endPoint.GetX());
  uint32_t biggestX = std::max(originPoint.GetX(), endPoint.GetX());

  // going up in y 
  if (pendentForY > 0.0f)
  {
    uint32_t  BufferYpos = std::min(originPoint.GetY(), endPoint.GetY());
    float currentYPosInSegment = 0.0f;

    for (size_t i = smallestX; i <= biggestX; ++i)
    {
      if (currentYPosInSegment > 0.998f)
      {
        BufferYpos += static_cast<uint32_t>(currentYPosInSegment);
        currentYPosInSegment = 0.0f;
      }
      currentYPosInSegment += pendentForY;
      this->FormatSet(i, BufferYpos,
                      Value.colorChannels[0], Value.colorChannels[1],
                      Value.colorChannels[2], Value.colorChannels[3]);
    }
  }
  // going down in y 
  else
  {
    uint32_t  BufferYpos = std::max(originPoint.GetY(), endPoint.GetY());
    float currentYPosInSegment = 0.0f;

    for (size_t i = smallestX; i <= biggestX; ++i)
    {
      if (currentYPosInSegment < -0.998f)
      {
        BufferYpos += static_cast<uint32_t>(currentYPosInSegment);
        currentYPosInSegment = 0.0f;
      }
      currentYPosInSegment += pendentForY;
      this->FormatSet(i, BufferYpos,
                      Value.colorChannels[0], Value.colorChannels[1],
                      Value.colorChannels[2], Value.colorChannels[3]);
    }
  }
}

void cBuffer::drawCircle(RGBdi Value)
{

  this->FormatSet(m_Width, m_Height / 2,
                  Value.colorChannels[0], Value.colorChannels[1],
                  Value.colorChannels[2], Value.colorChannels[3]);

  CVector2D middlePoint(m_Width / 2, m_Height / 2);


  // the same as 20 degrees
  const float angleStep = 20.0f;

  for (int i = 1; i < 18; ++i)
  {

    MoveToPos(m_Width / 2, m_Height / 2);

    float Deg = angleStep * i;
    float Rad = Deg *= (3.1415926 / 180);
    float X = middlePoint.GetX() + ((m_Width / 2) * cosf(Rad));
    float Y = middlePoint.GetY() + ((m_Height/ 2) * sinf(Rad));

    CircleMoveToPos(X, Y);

    if (this->CheckIsFloat() == true)
    {
      CircleFormatSet(
        Value.colorChannels[0], Value.colorChannels[1],
        Value.colorChannels[2], Value.colorChannels[3]);
    }
    else
    {
      CircleFormatSet(
        Value.colorChannels[0], Value.colorChannels[1],
        Value.colorChannels[2], Value.colorChannels[3]);
    }

    ResetActivePointer();
  }

  ResetActivePointer();
}

void cBuffer::PrintByTypeAndMove(Types Type)
{
  if (Type == Types::Interger8)
  {
    std::cout << '|' << static_cast<int>(*mptr_ActivePointer) << "|";
    mptr_ActivePointer++;
  }
  else if (Type == Types::Interger16)
  {
    int16_t *Temp = ( int16_t *) mptr_ActivePointer;
    std::cout << '|' << static_cast<int16_t>(*Temp) << "|";
    mptr_ActivePointer += sizeof(int16_t);
  }
  else if (Type == Types::Interger32)
  {
    int32_t *Temp = ( int32_t *) mptr_ActivePointer;
    std::cout << '|' << static_cast<int32_t>(*Temp) << "|";
    mptr_ActivePointer += sizeof(int32_t);
  }
  else if (Type == Types::Interger64)
  {
    int64_t *Temp = ( int64_t *) mptr_ActivePointer;
    std::cout << '|' << static_cast<int64_t>(*Temp) << "|";
    mptr_ActivePointer += sizeof(int64_t);
  }

  else if (Type == Types::Floating32)
  {
    float *Temp = ( float *) mptr_ActivePointer;
    std::cout << '|' << static_cast<float>(*Temp) << "|";
    mptr_ActivePointer += sizeof(float);
  }
  else if (Type == Types::Floating64)
  {
    double *Temp = ( double *) mptr_ActivePointer;
    std::cout << '|' << static_cast<double>(*Temp) << "|";
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

void cBuffer::CircleMoveToPos(int32_t xPos, int32_t yPos)
{
  int32_t DestY;
  int32_t DestX;

  // for moving backwards 
  if (yPos < 0)
  {
    DestY = yPos * m_Pitch;
  }
  else
  {
    DestY = (yPos - 1) * m_Pitch;
  }

  if (xPos < 0)
  {
    DestX = xPos * m_DataSize;
  }
  else
  {
    DestX = (xPos - 1) * m_DataSize;
  }


  mptr_ActivePointer += DestX + DestY;
}

void cBuffer::CircleFormatSet(float r, float g, float b, float a)
{

  for (int i = 0; i < m_Format.GetChannelCount(); ++i)
  {
    // set the individual r.g.b values 
    if (i == 0)
    { Set(m_Format.GetChannel(i).GetChannelType(), r); }
    else if (i == 1)
    { Set(m_Format.GetChannel(i).GetChannelType(), g); }
    else if (i == 2)
    { Set(m_Format.GetChannel(i).GetChannelType(), b); }
    else if (i == 3)
    { Set(m_Format.GetChannel(i).GetChannelType(), a); }
  }
}

void cBuffer::CircleFormatSet(int r, int g, int b, int a)
{

  for (int i = 0; i < m_Format.GetChannelCount(); ++i)
  {
    // set the individual r.g.b values 
    if (i == 0)
    { Set(m_Format.GetChannel(i).GetChannelType(), r); }
    else if (i == 1)
    { Set(m_Format.GetChannel(i).GetChannelType(), g); }
    else if (i == 2)
    { Set(m_Format.GetChannel(i).GetChannelType(), b); }
    else if (i == 3)
    { Set(m_Format.GetChannel(i).GetChannelType(), a); }
  }
}

void cBuffer::MoveByChannel(int Channel)
{
  if (m_Format.GetChannel(Channel).GetChannelType() == Types::Interger8 ||
      m_Format.GetChannel(Channel).GetChannelType() == Types::sInterger8)
  {
    mptr_ActivePointer++;
  }
  else if (m_Format.GetChannel(Channel).GetChannelType() == Types::Interger16 ||
           m_Format.GetChannel(Channel).GetChannelType() == Types::sInterger16)
  {
    mptr_ActivePointer += sizeof(uint16_t);
  }
  else if (m_Format.GetChannel(Channel).GetChannelType() == Types::Interger32 ||
           m_Format.GetChannel(Channel).GetChannelType() == Types::sInterger32)
  {
    mptr_ActivePointer += sizeof(uint32_t);
  }
  else if (m_Format.GetChannel(Channel).GetChannelType() == Types::Interger64 ||
           m_Format.GetChannel(Channel).GetChannelType() == Types::sInterger64)
  {
    mptr_ActivePointer += sizeof(uint64_t);
  }

  else if (m_Format.GetChannel(Channel).GetChannelType() == Types::Floating32)
  {
    mptr_ActivePointer += sizeof(float);
  }
  else if (m_Format.GetChannel(Channel).GetChannelType() == Types::Floating64)
  {
    mptr_ActivePointer += sizeof(double);
  }
}

