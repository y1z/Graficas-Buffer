#pragma once
#include "cBuffer.h"
#include "cFormat.h"

auto GetCoordsBuffer = [](uint32_t &xPos, uint32_t &yPos) ->void {
  std::cout << "Please Enter the X coordinate \n->";
  std::cin >> xPos;

  std::cout << "\nNow enter the Y coordinate \n->";
  std::cin >> yPos;
};

auto getValuesRGBdi = []() {
  std::cout << "give me four space separated values \n->";
  int R, G, B, A;
  std::cin >> R >> G>> B>> A;
  RGBdi result{R,G,B,A};
  return result;
};

auto getValuesRGBdf = []() {
  std::cout << "give me four space separated values \n->";
  double R, G, B, A;
  std::cin >> R >> G>> B>> A;
  RGBdf result{R,G,B,A};
  return result;
};

template<typename DesiredType, class ...VariantTypes>
void PrintValue(const std::variant<VariantTypes ...> &V)
{
  if (auto * Result = std::get_if<DesiredType>(&V))
  {
    std::cout << "The type is : " << typeid(*Result).name() << " = " << *Result << '\n';
  }

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

inline void AskForParamters_LineDraw(cBuffer &buffer)
{
  uint32_t xPos1, yPos1, xPos2, yPos2;
  //beginning
  std::cout << "give me 2 values that represent the beginning of a line (origin) \n  ";
  GetCoordsBuffer(xPos1, yPos1);
  std::cout << "give me 2 values that re represent the ending of a line (end) \n  ";
  GetCoordsBuffer(xPos2, yPos2);

  CVector2D origin(xPos1, yPos1);
  CVector2D end(xPos2, yPos2);

  if (buffer.CheckIsFloat() == false)
  {
    RGBdi value = getValuesRGBdi();
    buffer.drawLine(origin, end, value);
  }
  else
  {
    RGBdf value = getValuesRGBdf();
    buffer.drawLine(origin, end, value);
  }
  //      buffer.drawLine(origin, end);
}

inline void InteractWithBuffer(cBuffer &Buffer)
{
  auto PrintOptions = []() {
    std::cout << R"(
0) Quit 
1) Clear Buffer 
2) Set Value 
3) Get Value
4) Print Values 
5) draw line 
6) draw Circle
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
      GetValueFromBuffer(Buffer);
    }
    else if (Options == 4)
    {
      Buffer.PrintValues();
    }
    else if (Options == 5)
    {
      AskForParamters_LineDraw(Buffer);
    }
    
    else if (Options == 6){
      Buffer.drawCircle();
    }
  }
}
