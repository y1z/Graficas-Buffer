// graficas_buffer.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include "cBuffer.h"
#include "cFormat.h"
#include "HelperFunctionBuffer.h"

void Start();
/*! lets the user select the buffer width and height*/
std::pair<uint32_t, uint32_t> SelectBufferHeightAndWidth();
/*! This function give the user the ability to interact with the buffer */
void InteractWithBuffer(cBuffer &Buffer);
/*! this present the options the user has */
void PresentOptions();

int main()
{
  Start();
}

void Start()
{
  int32_t Options{0};
  bool IsFloat = false;
  std::cout << "do you want a floating-point buffer or integer buffer \n";
  std::cout << "1) float \n2) integer \n->";
  std::cin >> Options;
  if (Options == 1) { IsFloat = true; }
  cFormat BufferFormat = GetFormat(IsFloat);
  cBuffer Buffer;
 // Types TypeOfBuffer;
//  SelectChannelType(TypeOfBuffer,Format.CheckIsFloating());
  std::pair<uint32_t, uint32_t> HeightAndWidth = SelectBufferHeightAndWidth();

  Buffer.Init(HeightAndWidth.first, HeightAndWidth.second, BufferFormat);
  InteractWithBuffer(Buffer);
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


void PresentOptions()
{
  std::cout << R"??(0) Exit
1) Set Value in the buffer
2) Get Value in the buffer
3) Clear all value in the buffer
4) Print all values in the buffer
->)??";
}
