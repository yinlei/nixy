/*
    The Nixy Library
    Code covered by the MIT License

    Author: mutouyun (http://darkc.at)
*/

#pragma once

#include "nixycore/general/general.h"
#include "nixycore/typemanip/typemanip.h"
#include "nixycore/preprocessor/preprocessor.h"

//////////////////////////////////////////////////////////////////////////
NX_BEG
//////////////////////////////////////////////////////////////////////////

/*
    Operators
*/

template <typename T, typename Base_ = empty_t>
struct Unequal : Base_
{
    // Need operator==
    friend bool operator!=(const T& x, const T& y) { return (!static_cast<bool>(x == y)); }
};

template <typename T, typename Base_ = empty_t>
struct Alike : Base_
{
    // Need operator<
    friend bool operator!=(const T& x, const T& y) { return (static_cast<bool>(x < y) && static_cast<bool>(y < x)); }
    friend bool operator==(const T& x, const T& y) { return !(x != y); }
};

template <typename T, typename Base_ = empty_t>
struct Comparable : Base_
{
    // Need operator<
    friend bool operator> (const T& x, const T& y) { return ( static_cast<bool>(y < x)); }
    friend bool operator<=(const T& x, const T& y) { return (!static_cast<bool>(x > y)); }
    friend bool operator>=(const T& x, const T& y) { return (!static_cast<bool>(x < y)); }
};

namespace private_operable
{
    template <typename T, typename V, typename Base_>
    struct detail : Base_
    {
        friend T& operator-=(T& x, const V& v) { return x += (-v); }

        friend T& operator+ (T& x, const V& v) { return x += v; }
        friend T& operator+ (const V& v, T& x) { return x += v; }
        friend T& operator- (T& x, const V& v) { return x -= v; }
        friend T& operator- (const V& v, T& x) { return x -= v; }
    };

    template <typename T, typename Base_>
    struct detail<T, T, Base_> : Base_
    {
        friend T operator+ (const T& x, const T& v)
        {
            T t(x);
            return t += v;
        }
        friend T operator- (const T& x, const T& v)
        {
            T t(x);
            return t -= v;
        }
    };
}

template <typename T, typename V = int, typename Base_ = empty_t>
struct Operable : private_operable::detail<T, V, Base_>
{
    /*
        Must be the end of the nx_operator's parameters, 
        or you need explicitly specify the V parameter manually
    */

    // Need operator+=
    friend T& operator++(T& x)             { return x += 1; }
    friend T  operator++(T& x, int)        { T nrv(x); ++x; return nrv; }
    friend T& operator--(T& x)             { return x -= 1; }
    friend T  operator--(T& x, int)        { T nrv(x); --x; return nrv; }
};

/*
    nx_operator macro

    nx_operator(T, nx::Unequal, nx::Comparable, nx::Operable)
    -->
    nx::Unequal<T, nx::Comparable<T, nx::Operable<T > > >

    nx_operatorex(T, double, nx::Unequal, nx::Comparable, nx::Operable)
    -->
    nx::Unequal<T, nx::Comparable<T, nx::Operable<T, double > > >
*/

#define NX_OPERATOR_1(data, ...)        NX_PP_A2(data)<NX_PP_A1(data), __VA_ARGS__ >
#define NX_OPERATOR_2(data)             NX_PP_A2(data)<NX_PP_A1(data) >
#define NX_OPERATOR_3(...)              NX_PP_A1(__VA_ARGS__), NX_PP_B2(__VA_ARGS__)
#define nx_operator(T, ...) \
    NX_PP_NEST(NX_PP_COUNT(__VA_ARGS__), NX_OPERATOR_1, NX_OPERATOR_2, NX_OPERATOR_3, T, __VA_ARGS__)

#define NX_OPERATOREX_1(data, ...)      NX_PP_A3(data)<NX_PP_A1(data), __VA_ARGS__ >
#define NX_OPERATOREX_2(data)           NX_PP_A3(data)<NX_PP_A1(data), NX_PP_A2(data) >
#define NX_OPERATOREX_3(...)            NX_PP_A1(__VA_ARGS__), NX_PP_A2(__VA_ARGS__), NX_PP_B3(__VA_ARGS__)
#define nx_operatorex(T, P, ...) \
    NX_PP_NEST(NX_PP_COUNT(__VA_ARGS__), NX_OPERATOREX_1, NX_OPERATOREX_2, NX_OPERATOREX_3, T, P, __VA_ARGS__)

//////////////////////////////////////////////////////////////////////////
NX_END
//////////////////////////////////////////////////////////////////////////
