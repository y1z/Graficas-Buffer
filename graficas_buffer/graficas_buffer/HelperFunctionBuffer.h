#pragma once
#include "cBuffer.h"
#include "cFormat.h"

auto GetCoordsBuffer = [](uint32_t &xPos, uint32_t &yPos) ->void {
  std::cout << "Please Enter the X coordinate of where you what to set Or get your value in the buffer \n->";
  std::cin >> xPos;

  std::cout << "\nNow enter the Y coordinate of where you what to set Or get your value in the buffer \n->";
  std::cin >> yPos;
};

template<typename DesiredType, class ...VariantTypes>
void PrintValue(const std::variant<VariantTypes ...> &V)
{
  if (auto * Result = std::get_if<DesiredType>(&V))
  {
    std::cout << "The type is : " << typeid(*Result).name() << " = " << *Result << '\n';
  }

}
//
//inline void SetBufferValue(cBuffer &Buffer, const Types &Type)
//{
//  uint32_t xPos = 0;
//  uint32_t yPos = 0;
//
//  GetCoordsBuffer(xPos, yPos);
//
//  std::cout << "Now Pleas enter which value you what to set \n->";
//  if (Type != Types::Floating32 && Type != Types::Floating64)
//  {
//    int Value = 0;
//    std::cin >> Value;
//    Buffer.Set(xPos, yPos, Value);
//  }
//  else if (Type == Types::Floating32)
//  {
//    float Value = 0.0f;
//    std::cin >> Value;
//    Buffer.Set(xPos, yPos, Value);
//  }
//  else if (Type == Types::Floating64)
//  {
//    double Value = 0.0;
//    std::cin >> Value;
//    Buffer.Set(xPos, yPos, Value);
//  }
//}

inline void GetBufferValue(cBuffer &Buffer)
{
  uint32_t xPos = 0;
  uint32_t yPos = 0;

  GetCoordsBuffer(xPos, yPos);

  //auto Variant = Buffer.Get(xPos, yPos);

  //if (int *ValuePtr = std::get_if<int>(&Variant))
  //{
  //  std::cout << "Here is the Value " << *ValuePtr << '\n';
  //}
  //else if (float *ValuePtr = std::get_if<float>(&Variant))
  //{
  //  std::cout << "here is the Value " << *ValuePtr << '\n';
  //}
  //else if (double *ValuePtr = std::get_if<double>(&Variant))
  //{
  //  std::cout << "here is the Value " << *ValuePtr << '\n';
  //}
  //else if (int64_t * ValuePtr = std::get_if<int64_t>(&Variant))
  //{
  //  std::cout << "here is the Value " << *ValuePtr << '\n';
  //}

}

//! ask the user on some characteristics they want from the buffer 
inline cFormat GetFormat(bool Floating)
{
  auto ChannelSpcefics = [&](char Channel, std::string &FormatString) {
    std::cout << "how many bit do you want for Channel " << Channel << std::endl;
    FormatString += Channel;
    int16_t Options;
    if (Floating == false)
    {
      std::cout << "1) 8 bits \n 2) 16 \n3) 32 \n4)64\n->";
      std::cin >> Options;
      if (Options == 1) { FormatString += '8'; }
      else if (Options == 2) { FormatString += "16"; }
      else if (Options == 3) { FormatString += "32"; }
      else if (Options == 4) { FormatString += "64"; }
    }
    else
    {
      std::cout << "1) 32 bits \n 2) 64 bits \n->";
      std::cin >> Options;
      if (Options == 1) { FormatString += "32"; }
      else if (Options == 2) { FormatString += "64"; }
    }
  };

  cFormat Result;
  // this determines what the final format is going to be  
  std::string FormatString("");
  // this is to indicate in the string that the values a floats  
  if (Floating) { FormatString += 'f'; }
  uint16_t Options;
  const char Channels[] = "rgba";

  std::cout << R"( How many channels do you what you can chose up to 4
-> )";
  std::cin >> Options;

  if (Options <= 4)
  {
    for (uint8_t i = 0; i < Options; ++i)
    {
      ChannelSpcefics(Channels[i], FormatString);
    }
  }

  Result.ParseFormat(FormatString);
  return Result;
}

inline void GetValueFromBuffer(cBuffer &Buffer)
{

  uint32_t xPos;
  uint32_t yPos;
  std::cout << "Give me a X Coordinate \n";
  std::cin >> xPos;
  std::cout << "Give me a Y Coordinate \n";
  std::cin >> yPos;

  auto Values = Buffer.GetValues(xPos, yPos);

  for (int i = 0; i < Values.usedChannels; ++i)
  {
    std::cout << " | " << Values.colorChannels[i] << " | ";
  }
  std::cout << "\n\n";
}

inline void AskForParmeters_Set(cBuffer &Buffer)
{
  uint32_t xPos;
  uint32_t yPos;
  std::cout << "Give me a X Coordinate \n";
  std::cin >> xPos;
  std::cout << "Give me a Y Coordinate \n";
  std::cin >> yPos;
  std::cout << "Give me 4 values separated by spaces \n";
  if (Buffer.CheckIsFloat())
  {
    float VarR, VarG, VarB, VarA;
    std::cin >> VarR >> VarG >> VarB >> VarA;
    Buffer.FormatSet(xPos, yPos, VarR, VarG, VarB, VarA);
  }
  else
  {
    int VarR, VarG, VarB, VarA;
    std::cin >> VarR >> VarG >> VarB >> VarA;
    Buffer.FormatSet(xPos, yPos, VarR, VarG, VarB, VarA);
  }

}


inline void InteractWithBuffer(cBuffer &Buffer)
{
  auto PrintOptions = []() {
    std::cout << R"(
0) Quit 
1) Clear Buffer 
2)Set Value 
3)Get Value
4)Print Values 
-> )";
  };

  cBuffer secondBuffer;
  cFormat secondBufferFormat;
  secondBufferFormat.ParseFormat("r32g32b32a32");
  secondBuffer.Init(10, 9, secondBufferFormat);

  uint16_t Options{0};
  while (true)
  {
    PrintOptions();
    std::cin >> Options;
    if (Options == 0) { break; }
    else if (Options == 1)
    {
      Buffer.Clear();
    }
    else if (Options == 2)
    {
      AskForParmeters_Set(Buffer);
    }
    else if (Options == 3)
    {

    }
    else if (Options == 4)
    {
      Buffer.PrintValues();
    }
  }

}
