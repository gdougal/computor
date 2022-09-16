//
// Created by as.doynikov on 01.06.2022.
//
#pragma once
#include <iostream>
#include <limits>


template<typename T_ = double >
class complex_number
{
#define COMPLEX_OP_SUBDIVIDE_MULTIPLY(OP)\
    template <typename T>\
    inline complex_number<T_>& operator OP (const T other) {\
        this->mReal = this->mReal  OP static_cast<T_>(other);\
        this->mImage = this->mImage  OP static_cast<T_>(other);\
        return *this; }

#define COMPLEX_OP_PLUS_MINUS(OP)\
    template <typename T>\
    inline complex_number<T_>& operator OP (const T other) {\
        this->mReal = this->mReal  OP static_cast<T_>(other);\
        return *this; }

#define COMPLEX_OP_EQ(OP)\
    template <typename T>\
    inline complex_number<T_>& operator OP##= (const T other) {\
        *this = *this OP static_cast<T_>(other);\
        return *this; }

#define COMPLEX_OP_EQ_OTHER_COMPLEX(OP) template <typename T>\
    inline complex_number<T_>& operator OP##= (const complex_number<T>& other)\
    {\
        if ( !std::is_same<T, T_>::value ) { return (*this = *this OP complex_number<T_>(other)); }\
        else return (*this = *this OP other);\
    }

    T_ mReal;
    T_ mImage; //*i
public:
    COMPLEX_OP_PLUS_MINUS(-);
    COMPLEX_OP_PLUS_MINUS(+);
    COMPLEX_OP_SUBDIVIDE_MULTIPLY(*);
    COMPLEX_OP_SUBDIVIDE_MULTIPLY(/);

    COMPLEX_OP_EQ(-);
    COMPLEX_OP_EQ(+);
    COMPLEX_OP_EQ(*);
    COMPLEX_OP_EQ(/);

    COMPLEX_OP_EQ_OTHER_COMPLEX(-);
    COMPLEX_OP_EQ_OTHER_COMPLEX(+);
    COMPLEX_OP_EQ_OTHER_COMPLEX(*);
    COMPLEX_OP_EQ_OTHER_COMPLEX(/);


    complex_number() = delete;
    template <typename T>
    complex_number(const T R_part = 0, const T Z_part = 0,
                   typename std::enable_if<std::is_arithmetic<T>::value,  T>::type l = 0):
            mReal(static_cast<T_>(R_part)),
            mImage(static_cast<T_>(Z_part)) {};
    complex_number(const complex_number<T_>& other) = default;

    template <typename T>
    explicit complex_number(const complex_number<T>& other) {
        mReal = static_cast<T_>(other.real());
        mImage = static_cast<T_>(other.image());
    };
    complex_number& operator=(const complex_number<T_>& other) = default;
    ~complex_number() = default;

    inline complex_number& operator -(const complex_number& other)
    {
        auto new_real = mReal - other.mReal;
        mImage = mImage - other.mImage;
        mReal = new_real;
        return *this;
    };

    inline complex_number& operator +(const complex_number& other)
    {
        auto new_real = mReal + other.mReal;
        mImage = mImage + other.mImage;
        mReal = new_real;
        return *this;
    };
    inline complex_number<T_>& operator *(const complex_number<T_>& other)
    {
        auto new_real = mReal * other.mReal - mImage * other.mImage;
        mImage = mReal * other.mImage + mImage * other.mReal;
        mReal = new_real;
        return *this;
    };

    inline complex_number<T_>& operator/(const complex_number<T_>& other)
    {
        auto tmp_r = mReal;
        mReal =  ( mReal * other.mReal +  mImage * other.mImage ) / ( other.mReal * other.mReal + other.mImage * other.mImage );
        mImage = ( mImage * other.mReal - tmp_r * other.mImage ) / ( other.mReal * other.mReal + other.mImage * other.mImage );
        return *this;
    };

    inline bool operator ==(const complex_number<T_>&& other)
    {
        if ( std::is_floating_point<T_>::value() )
            return mReal - other.mReal < std::numeric_limits<double>::epsilon() && mImage - other.mImage < std::numeric_limits<double>::epsilon();
        return ( mReal == other.mReal && mImage == other.mImage );
    };

    inline bool operator !=(const complex_number&& other)
    {
        return *this != std::forward<complex_number>(other);
    };

    inline T_ real() const
    {
        return mReal;
    };
    inline T_ image() const
    {
        return mImage;
    };
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const complex_number<T>& f)
{
    out << f.real();
    if ( f.image() != 0 )
        out << ( f.image() > 0 ? "+" : "" ) << f.image() << "*i";
    return out;
}

#define COMPLEX_OPERATOR_OUTSIDE_DEREF(OP)\
template <typename T>\
complex_number<T> operator OP (const T first, complex_number<T> second)\
{\
    return complex_number<T>(first) OP second;\
};

COMPLEX_OPERATOR_OUTSIDE_DEREF(-)
COMPLEX_OPERATOR_OUTSIDE_DEREF(+)
COMPLEX_OPERATOR_OUTSIDE_DEREF(/)
COMPLEX_OPERATOR_OUTSIDE_DEREF(*)
