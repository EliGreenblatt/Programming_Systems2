#include "AdptArray.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct AdptArray_
{
    DEL_FUNC del;
    PRINT_FUNC print;
    COPY_FUNC copy;

    PElement* elemArr;
    int arrSize;

} AdptArray_;

PAdptArray CreateAdptArray(COPY_FUNC copy , DEL_FUNC del ,  PRINT_FUNC print)
{
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray_));
    if (pArr == NULL)
    {
        return NULL;
    }
   /* pArr->elemArr = (PElement*)malloc(sizeof(PElement));
    if(pArr->elemArr == NULL)
    {
        free(pArr);
        return NULL;
    }   */
    pArr->elemArr = NULL; 
    pArr->copy = copy;
    pArr->del = del;
    pArr->print = print;
    pArr->arrSize = 0;
    return pArr;
}

void DeleteAdptArray(PAdptArray pAdpt)
{
    if (pAdpt == NULL)
    {
        return;
    }

    if(pAdpt->elemArr == NULL)
    {
        return;
    }

    for (int i = 0; i < pAdpt->arrSize; i++)
    {
        if(pAdpt->elemArr[i] == NULL)
        {
            continue;
        }
        pAdpt->del((pAdpt->elemArr)[i]);
    }
    free(pAdpt->elemArr);
    free(pAdpt);
}


Result SetAdptArrayAt(PAdptArray pAdpt, int size, PElement pElem)
{
    if (pAdpt == NULL)
    {
        return FAIL;
    }

    if(size > pAdpt->arrSize)
    {
       PElement* elemArray = (PElement*) calloc((size + 1), sizeof(PElement));
       if (elemArray == NULL)
       {
            return FAIL;
       }

        for (int i = 0; i < pAdpt->arrSize; i++)
        {
            if(pAdpt->elemArr[i] != NULL)
            {
                elemArray[i] = pAdpt->copy(pAdpt->elemArr[i]);
                pAdpt->del(pAdpt->elemArr[i]);
            }
            pAdpt->elemArr[i] = NULL;
        }
        free(pAdpt->elemArr);
        pAdpt->elemArr = elemArray;
        pAdpt->arrSize = size + 1;        
    }

    pAdpt->elemArr[size] = pAdpt->copy(pElem);
    return SUCCESS;
    
}

PElement GetAdptArrayAt(PAdptArray pAdpt, int index)
{    
    if(index < 0)
    {
        return NULL;
    }
    if (pAdpt == NULL)
    {
        return NULL;
    }

    if(pAdpt->arrSize <= index)
    {
        return NULL;
    }
    if(pAdpt->elemArr[index] == NULL)
    {
        return NULL;
    }
    return pAdpt->copy(pAdpt->elemArr[index]);
}

int GetAdptArraySize(PAdptArray pAdpt)
{
    if (pAdpt == NULL)
    {
        return -1;
    }

    return pAdpt->arrSize;
}

void PrintDB(PAdptArray pAdpt)
{
    if (pAdpt == NULL)
    {
        return;
    }

    for (int i = 1; i < pAdpt->arrSize; i++)
    {
        if(pAdpt->elemArr[i])
        {
            pAdpt->print(pAdpt->elemArr[i]);
        }
        
    }
    
}
