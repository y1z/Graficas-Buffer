#include "cBuffer.h"

cBuffer::cBuffer( )
{
  mptr_Beginning = nullptr;
  mptr_ActivePointer = nullptr;
  mptr_End = nullptr;
}

cBuffer::~cBuffer( )
{
  mptr_ActivePointer = mptr_Beginning;
  mptr_Beginning = nullptr;
  mptr_End = nullptr;
  if (mptr_ActivePointer != nullptr)
  {
    std::free(mptr_ActivePointer);
  }
}
