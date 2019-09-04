#pragma once
#include <cstdlib>// for std::malloc 

enum class Types
{
  Interger8 = 1,
  Interger16 = 2,
  Interger32 = 4,
  Interger64 = 8,

  Floating32 = 4,
  Floating64 = 8
};

class cBuffer
{
public:// constructor 
  cBuffer( );
  ~cBuffer( );
public:
  //! for initiating the buffer 
  void Init(int width, int height, Types type);




private:// variables 
  //! keeps track of the beginning of the buffer 
  void *mptr_Beginning ;
  //! keeps track of where we are in the buffer 
  void *mptr_ActivePointer;
  //! keeps track of where the buffer ends 
  void *mptr_End;

};

