//
// Created by JohnK on 2/5/2022.
//

#ifndef PATCH_MATCHER_COPERATORLIST_H
#define PATCH_MATCHER_COPERATORLIST_H

#include <assert.h>

#include "Operator.h"

class Operator;

class COperatorList{
public:
    COperatorList(int iMaxOperators) :
        m_pOperatorList(0),
        m_iBufferSize(iMaxOperators),
        m_iWriteIdx(0),
        m_iNumOperatorsInBuffer(0)
    {
        m_pOperatorList = new Operator*[iMaxOperators]{0};
    }

    ~COperatorList()
    {
        delete m_pOperatorList;
        m_pOperatorList = 0;
    }

    void push_back(Operator* pOperatorToAdd)
    {
        assert(m_iWriteIdx < m_iBufferSize);
        m_pOperatorList[m_iWriteIdx] = pOperatorToAdd;
        m_iWriteIdx++;
        m_iNumOperatorsInBuffer++;
    }

    void remove(Operator* pOperatorToRemove)
    {
        for (int i = 0; i < m_iNumOperatorsInBuffer; i++)
        {
            Operator* pCurrentOperator = get(i);
            if (pOperatorToRemove == pCurrentOperator)
            {
                pCurrentOperator = nullptr;
                shiftOperatorsLeft(i);
                m_iWriteIdx--;
                m_iNumOperatorsInBuffer--;
                break;
            }
        }
    }

    Operator* get(int iIndex) const
    {
        assert(iIndex >= 0 && iIndex < m_iNumOperatorsInBuffer);
        return m_pOperatorList[iIndex];
    }

    int getSize() const
    {
        return m_iNumOperatorsInBuffer;
    }

private:

    void shiftOperatorsLeft(int iStartingIndex)
    {
        for (int i = iStartingIndex; i < m_iNumOperatorsInBuffer - 1; i++)
        {
            swapPositions(i, i+1);
        }
    }

    void swapPositions(int iIndexLeft, int iIndexRight )
    {
        Operator* temp = get(iIndexRight);
        m_pOperatorList[iIndexRight] = m_pOperatorList[iIndexLeft];
        m_pOperatorList[iIndexLeft] = temp;
    }

    Operator** m_pOperatorList;
    int m_iBufferSize;
    int m_iWriteIdx;
    int m_iNumOperatorsInBuffer;
};


#endif //PATCH_MATCHER_COPERATORLIST_H
