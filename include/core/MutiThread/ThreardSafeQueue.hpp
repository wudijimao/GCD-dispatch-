//
//  ThreardSafeQueue.hpp
//  XDUILib
//
//  Created by ximiao on 16/6/6.
//  Copyright © 2016年 wudijimao. All rights reserved.
//

#pragma once
#include "../stdafx.hpp"


class SIMPLEDIRECTUI_API SingleRWSafeQueue
{
public:
    SingleRWSafeQueue(int nSize);
    virtual ~SingleRWSafeQueue();
    
    bool Initialize();
    
    unsigned int Put(const unsigned char *pBuffer, unsigned int nLen);
    unsigned int Get(unsigned char *pBuffer, unsigned int nLen);
    
    inline void Clean() { m_nIn = m_nOut = 0; }
    inline unsigned int GetDataLen() const { return  m_nIn - m_nOut; }
    
private:
    inline bool is_power_of_2(unsigned long n) { return (n != 0 && ((n & (n - 1)) == 0)); };
    inline unsigned long roundup_power_of_two(unsigned long val);
    
private:
    unsigned char *m_pBuffer;    /* the buffer holding the data */
    unsigned int   m_nSize;        /* the size of the allocated buffer */
    unsigned int   m_nIn;        /* data is added at offset (in % size) */
    unsigned int   m_nOut;        /* data is extracted from off. (out % size) */
};
