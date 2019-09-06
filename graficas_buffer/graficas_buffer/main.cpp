// graficas_buffer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "cBuffer.h"

template<typename DesiredType, class ...VariantTypes>
void PrintValue(const std::variant<VariantTypes ...> &V)
{
  if (auto * Result = std::get_if<DesiredType>(&V))
  {
    std::cout << "The type is : " << typeid(*Result).name() << " = " << *Result << '\n';
  }

}


int main()
{
  {
    cBuffer Buffer;
    Buffer.Init(5, 5, Types::Floating64);
    // Buffer.Set(1, 1, 300);
    // Buffer.Set(2, 2, 20);
    // Buffer.Set(3, 3, 40);
    // Buffer.Set(4, 4, 99);
    // Buffer.Set(5, 5, 88);

    Buffer.Set(1, 1, 50.34);
    Buffer.Set(2, 2, 50.53);
    Buffer.Set(3, 3, 435.76);
    Buffer.Set(4, 4, 345.621);
    Buffer.Set(5, 5, 909.131);
    auto Value = Buffer.Get(1, 1);

    PrintValue<int>(Value);
    PrintValue<float>(Value);
    PrintValue<double>(Value);
    PrintValue<int64_t>(Value);

    Buffer.PrintValues();

    Buffer.Clear();

    Buffer.PrintValues();
  }


  std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
