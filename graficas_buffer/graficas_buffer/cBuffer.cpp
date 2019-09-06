#include "cBuffer.h"
#include <iostream>
#include <memory>

cBuffer::cBuffer()
  :mptr_Beginning(nullptr),
  mptr_ActivePointer(nullptr),
  mptr_End(nullptr),
  m_Type(Types::Interger8),
  m_Pitch(0),
  m_Width(0),
  m_Height(0)
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
  while (mptr_ActivePointer != mptr_End)
  {
    if (m_Type == Types::Interger8)
    {
      std::cout << '|' << static_cast<int>(*mptr_ActivePointer) << "| ";
      mptr_ActivePointer++;
    }
    else if (m_Type == Types::Interger16)
    {
      int16_t *Temp = ( int16_t *) mptr_ActivePointer;
      std::cout << '|' << static_cast<int16_t>(*Temp) << "| ";
      mptr_ActivePointer += sizeof(int16_t);
    }
    else if (m_Type == Types::Interger32)
    {
      int32_t *Temp = ( int32_t *) mptr_ActivePointer;
      std::cout << '|' << static_cast<int32_t>(*Temp) << "| ";
      mptr_ActivePointer += sizeof(int32_t);
    }
    else if (m_Type == Types::Interger64)
    {
      int64_t *Temp = ( int64_t *) mptr_ActivePointer;
      std::cout << '|' << static_cast<int64_t>(*Temp) << "| ";
      mptr_ActivePointer += sizeof(int64_t);
    }

    else if (m_Type == Types::Floating32)
    {
      float *Temp = ( float *) mptr_ActivePointer;
      std::cout << '|' << static_cast<float>(*Temp) << "| ";
      mptr_ActivePointer += sizeof(float);
    }
    else if(m_Type == Types::Floating64)
    {
      double *Temp = ( double *) mptr_ActivePointer;
      std::cout << '|' << static_cast<double>(*Temp) << "| ";
      mptr_ActivePointer += sizeof(double);
    }

  }
  std::cout << "\n-----------------------------------------------------\n";
  ResetActivePointer();
}

void cBuffer::Set(uint32_t xPos, uint32_t yPos, int Val)
{
  if (this->m_Type == Types::Interger8 && this->MoveToPos(xPos, yPos))
  {
    *mptr_ActivePointer = Val;
  }
  else if (this->m_Type == Types::Interger16 && this->MoveToPos(xPos, yPos))
  {
    int16_t *Temp = ( int16_t *) mptr_ActivePointer;
    *Temp = Val;
  }
  else if (this->m_Type == Types::Interger32 && this->MoveToPos(xPos, yPos))
  {
    int32_t *Temp = ( int32_t *) mptr_ActivePointer;
    *Temp = Val;
  }
  else if (this->m_Type == Types::Interger64 && this->MoveToPos(xPos, yPos))
  {
    int64_t *Temp = ( int64_t *) mptr_ActivePointer;
    *Temp = Val;
  }

  ResetActivePointer();
}

void cBuffer::Set(uint32_t xPos, uint32_t yPos, float Val)
{
  if (this->m_Type == Types::Floating32 && this->MoveToPos(xPos, yPos))
  {
    float *Temp = ( float *) mptr_ActivePointer;
    *Temp = Val;
  }

  ResetActivePointer();
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

void cBuffer::ResetActivePointer()
{
  this->mptr_ActivePointer = static_cast<char *>(this->mptr_Beginning);
}

bool cBuffer::MoveToPos(uint32_t xPos, uint32_t yPos)
{

  if (xPos > m_Width || xPos < 0)
  {
    printf_s("x Position is out of bounds \n");
    return false;
  }
  if (yPos > m_Height || yPos < 0)
  {
    printf_s("y Position is out of bounds \n");
    return false;
  }
  else
  {
    if (m_Type != Types::Floating32 && m_Type != Types::Floating64)
    {
      mptr_ActivePointer += ((yPos - 1) * m_Pitch) + ((xPos - 1) * static_cast<int8_t>(m_Type));
    }
    else
    {
      uint8_t SizeData = static_cast<int8_t>(m_Type) + 1;
      mptr_ActivePointer += ((yPos - 1) * m_Pitch) + ((xPos - 1) * SizeData);
    }
    return true;
  }
}
