#pragma once
#include <cstdlib>// for std::malloc
#include <cstdint>// for int8_t int16_t int32_t etc...
#include <variant>// for std::variant
#include "EnumsHeader.h"
#include "cFormat.h"
#include "sRGBA_values.h"
#include "CVector2D.h"

class cBuffer
{
public:// constructor
  cBuffer();
  ~cBuffer();
public:// functions
  //! for initializing the buffer
  void Init(uint32_t width, uint32_t height, Types type = Types::Interger8);
  void Init(uint32_t width, uint32_t height, const cFormat &Format);
  //! for clearing all the memory of the buffer
  void Clear();

  void PrintValues();
  //! this is use set value depending on the format  
  void FormatSet(uint32_t xPos, uint32_t yPos, int ValR, int ValG = 0, int ValB = 0, int ValA = 0);
  //! This is for setting floating-point values 
  void FormatSet(uint32_t xPos, uint32_t yPos, double ValR, double ValG = 0.0, double  ValB = 0.0, double ValA = 0.0);

  //! sets a value inside the buffer
  void Set(Types type, int Val);
  //! the same as Set
  void Set(Types type, double Val);
  //! the same as Set
  void Set(uint32_t xPos, uint32_t yPos, double Val);
  //! return a value in the buffer
  [[nodiscard]] std::variant<int, float, double, int64_t>
    GetValueByType(Types type);

  RGBdf GetValues(uint32_t xPos, uint32_t yPos);

  bool CheckIsFloat() const;

  //! draw a line using vector logic 
  void drawLine(CVector2D &originPoint,
                CVector2D &endPoint,
                RGBdf Value = {1.0,1.22,2.2,1.5});

  void drawLine(CVector2D &originPoint,
                CVector2D &endPoint,
                RGBdi Value = {1,2,3,5});

  void drawCircle(RGBdi Value = {90,1,1,1});
private:
  void PrintByTypeAndMove(Types Type);
  //! for reseting the active pointer to the beginning of the buffer
  void ResetActivePointer();
  //! for moving the active pointer to the desired location
  [[nodiscard]] bool
    MoveToPos(uint32_t xPos, uint32_t yPos);
// meant for drawing a circle 
 void CircleMoveToPos(int32_t xPos,  int32_t yPos);  

 void CircleFormatSet(float r, float g, float b, float a); 

 void CircleFormatSet(int r, int g, int b, int a); 
  void
    MoveByChannel(int Channel);
private:// variables

  //! this is to keep track of how the data is organized 
  cFormat m_Format;
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

  uint32_t m_DataSize;

  bool IsFloat = false;

};

