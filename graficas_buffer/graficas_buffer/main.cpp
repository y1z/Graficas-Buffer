// graficas_buffer.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include "cBuffer.h"
#include "HelperFunctionBuffer.h"
void Start();
/*! lets the user select the buffer type they desire*/
void SelectBufferType(Types &Type);
/*! lets the user select the buffer width and height*/
std::pair<uint32_t, uint32_t> SelectBufferHeightAndWidth();
/*! This function give the user the ability to interact with the buffer */
void InteractWithBuffer(cBuffer &Buffer, const Types &Type);
/*! this present the options the user has */
void PresentOptions();

int main()
{
  Start();
}

void Start()
{
  Types TypeOfBuffer;
  SelectBufferType(TypeOfBuffer);
  std::pair<uint32_t, uint32_t> HeightAndWidth = SelectBufferHeightAndWidth();

  cBuffer Buffer;
  Buffer.Init(HeightAndWidth.first, HeightAndWidth.second, TypeOfBuffer);
  InteractWithBuffer(Buffer, TypeOfBuffer);
}

void SelectBufferType(Types &TypeOfBuffer)
{
  std::cout << R",,,(Chose the buffer data type 
1) int8 (1 Byte int) 
2) int16 (2 Byte int)
3) int32 (4 Byte int)
4) int64 (8 Byte int)
5) float (4 Byte float)
6) double (8 Byte float) ),,,";

  int16_t Options = 0;
  // will determine the type of buffer 
  std::cin >> Options;
  switch (Options)
  {
    case(1):
      TypeOfBuffer = Types::Interger8;
      break;
    case(2):
      TypeOfBuffer = Types::Interger16;
      break;
    case(3):
      TypeOfBuffer = Types::Interger32;
      break;
    case(4):
      TypeOfBuffer = Types::Interger64;
      break;
    case(5):
      TypeOfBuffer = Types::Floating32;
      break;
    case(6):
      TypeOfBuffer = Types::Floating64;
      break;
    default:
      std::cout << "Invalid Option will use option 1 as default\n";
      TypeOfBuffer = Types::Interger8;
      break;
  }

}

std::pair<uint32_t, uint32_t> SelectBufferHeightAndWidth()
{
  uint32_t Height;
  uint32_t Width;
  std::cout << "\n\n Now I need you to give me the width and height of the buffer \n "
    "First The height \n ->";
  std::cin >> Height;

  std::cout << "\n Good now I just need the Width \n->";
  std::cin >> Width;

  std::pair<uint32_t, uint32_t>Result(Height, Width);
  return Result;
}

void InteractWithBuffer(cBuffer &Buffer, const Types &Type)
{
  int16_t Options;
  bool IsRunning = true;

  while (IsRunning)
  {
    PresentOptions();

    std::cin >> Options;
    switch (Options)
    {
      case(0):
        IsRunning = false;
        break;
      case(1):
        SetBufferValue(Buffer, Type);
        break;
      case(2):
        GetBufferValue(Buffer);
        break;
      case(3):
        Buffer.Clear();
        break;
      case(4):
        Buffer.PrintValues();
        break;
      default:
        std::cout << "invalid option \n";
        break;
    }
  }

}

void PresentOptions()
{
  std::cout << R"??(0) Exit 
1) Set Value in the buffer 
2) Get Value in the buffer 
3) Clear all value in the buffer 
4) Print all values in the buffer
->)??";

}
