#pragma once
#include "cBuffer.h"

auto GetCoordsBuffer = [](uint32_t &xPos, uint32_t &yPos) ->void 
{
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

inline void SetBufferValue(cBuffer &Buffer, const Types &Type)
{
  uint32_t xPos = 0;
  uint32_t yPos = 0;

  GetCoordsBuffer(xPos, yPos);

  std::cout << "Now Pleas enter which value you what to set \n->";
  if (Type != Types::Floating32 && Type != Types::Floating64)
  {
    int Value = 0;
    std::cin >> Value;
    Buffer.Set(xPos, yPos, Value);
  }
  else if (Type == Types::Floating32)
  {
    float Value = 0.0f;
    std::cin >> Value;
    Buffer.Set(xPos, yPos, Value);
  }
  else if (Type == Types::Floating64)
  {
    double Value = 0.0;
    std::cin >> Value;
    Buffer.Set(xPos, yPos, Value);
  }
}

inline void GetBufferValue(cBuffer &Buffer)
{
  uint32_t xPos = 0;
  uint32_t yPos = 0;

  GetCoordsBuffer(xPos, yPos);

  auto Variant = Buffer.Get(xPos, yPos);

  if(int *ValuePtr = std::get_if<int>(&Variant))
  {
    std::cout <<"Here is the Value " << *ValuePtr << '\n';
  }
  else if (float *ValuePtr = std::get_if<float>(&Variant))
  {
    std::cout << "here is the Value " << *ValuePtr << '\n';
  }
  else if (double *ValuePtr = std::get_if<double>(&Variant))
  {
    std::cout << "here is the Value " << *ValuePtr<< '\n';
  }
  else if (int64_t *ValuePtr = std::get_if<int64_t>(&Variant))
  {
    std::cout << "here is the Value " << *ValuePtr << '\n';
  }

  
}