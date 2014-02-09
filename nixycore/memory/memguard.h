/*
    The Nixy Library
    Code covered by the MIT License

    Author: mutouyun (http://darkc.at)
*/

#pragma once

#include "nixycore/memory/alloc.h"

#include "nixycore/delegate/functor.h"
#include "nixycore/finalizer/scopeguard.h"

#include "nixycore/general/general.h"
#include "nixycore/typemanip/typemanip.h"

//////////////////////////////////////////////////////////////////////////
NX_BEG
//////////////////////////////////////////////////////////////////////////

/*
    memory scope guard
*/

namespace private_memory_guard
{
    template <typename T>
    struct free_fr
    {
        T mm_;
        free_fr(T mm) : mm_(mm) {}
        void operator()(void) { nx::free(mm_); }
    };
}

template <typename T>
inline typename enable_if<is_pointer<T>::value,
functor<void()> >::type_t make_destructor(T& r)
{
    return private_memory_guard::free_fr<T>(r);
}

//////////////////////////////////////////////////////////////////////////
NX_END
//////////////////////////////////////////////////////////////////////////
