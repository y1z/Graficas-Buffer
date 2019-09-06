#pragma once
#include <cstdlib>// for std::malloc 
#include <cstdint>// for int8_t int16_t int32_t etc...
#include <variant>// for std::variant 

enum class Types : int8_t
{
  Interger8 = 1,
  Interger16 = 2,
  Interger32 = 4,
  Interger64 = 8,

  Floating32 = 3,
  Floating64 = 7
};

class cBuffer
{
public:// constructor 
  cBuffer();
  ~cBuffer();
public:// functions 
  //! for initializing the buffer 
  void Init(uint32_t width, uint32_t height, Types type = Types::Interger8);
  //! for clearing all the memory of the buffer
  void Clear();

  void PrintValues();
  //! sets a value inside the buffer 
  void Set(uint32_t xPos, uint32_t yPos, int Val);
  //! the same as Set 
  void Set(uint32_t xPos, uint32_t yPos, float Val);
  //! the same as Set 
  void Set(uint32_t xPos, uint32_t yPos, double Val);
  //! return a value in the buffer 
  [[nodiscard]] std::variant<int, float,double, int64_t>
    Get(uint32_t xPos, uint32_t yPos);

private:
  //! for reseting the active pointer to the beginning of the buffer 
  void ResetActivePointer();
  //! for moving the active pointer to the desired location 
  [[nodiscard]] bool
  MoveToPos(uint32_t xPos, uint32_t yPos);

private:// variables 
  //! keeps track of the beginning of the buffer 
  void *mptr_Beginning;
  //! keeps track of where we are in the buffer 
  char *mptr_ActivePointer;
  //! keeps track of where the buffer ends 
  void *mptr_End;
  //! keeps track of what type the buffer consist of 
  Types m_Type;
  //! keeps track of how many bytes a row in the buffer consist of 
  uint32_t m_Pitch;
  //! keeps track of how many rows there are per column 
  uint32_t m_Width;
  //! keeps track of how many columns there are per row 
  uint32_t m_Height;

};

