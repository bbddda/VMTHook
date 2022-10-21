#pragma once

#include <Windows.h>

class CVMT
{
private:
    uintptr_t* vmt;
public:
    uintptr_t** vTableAddr     = nullptr;
    uintptr_t* originalAddress = nullptr;
    uint32_t methodCount       = 0;

    // ----------------------------------------------------------------------------------------------------------------------

    CVMT(void* vTableClass)
    {
        this->vTableAddr = reinterpret_cast<uintptr_t**>(vTableClass);

        size_t virtualTableSize = 0;

        // Acquire the amount of data inside the virtual table.
        while (reinterpret_cast<uintptr_t*>(*this->vTableAddr)[virtualTableSize])
            virtualTableSize++;

        // Set the original.
        originalAddress = *this->vTableAddr;

        vmt = new uintptr_t[virtualTableSize + 1];

        // Make a copy of the entire vTable.
        // Set the vTable pointer to our copy.
        memcpy(vmt, &originalAddress[-1], (sizeof(uintptr_t) * virtualTableSize) + sizeof(uintptr_t));
    }

    // ----------------------------------------------------------------------------------------------------------------------

    void Hook(void* detourFunction, size_t methodIndex)
    {
        vmt[methodIndex + 1] = reinterpret_cast<uintptr_t>(detourFunction);
        *this->vTableAddr = &vmt[1];
    }

    // ----------------------------------------------------------------------------------------------------------------------

    void Unhook()
    {
        *this->vTableAddr = originalAddress;
        delete vmt;
    }

    // ----------------------------------------------------------------------------------------------------------------------

    uintptr_t* GetOriginalAddress()
    {
        if (originalAddress)
            return originalAddress;
    }

    // ----------------------------------------------------------------------------------------------------------------------

    template<typename Fn>
    Fn GetOriginalMethod(size_t methodIndex)
    {
        return reinterpret_cast<Fn>(originalAddress[methodIndex]);
    }

    // ----------------------------------------------------------------------------------------------------------------------
};
