// -*- C++ Header -*-
/*
==================================================
Authors: A.Mithran;
Emails: mithran@fias.uni-frankfurt.de
==================================================
*/

#ifndef SIMD_SSE_MASK32_H
#define SIMD_SSE_MASK32_H

#include "../Utils/macros.h"
#include "../Utils/tag.h"
#include "constants.h"

#include <cassert>
#include <string>

namespace KFP {
namespace SIMD {

class Mask32_128
{
public:
    typedef bool value_type;
    typedef __m128i simd_type;
    static constexpr Tag tag{ Tag::SSE };

    friend class Int32_128;
    friend class Float32_128;

    // ------------------------------------------------------
    // Constructors
    // ------------------------------------------------------
    // Default constructor:
    Mask32_128() {
        m_data = _mm_setzero_si128();
    }
    Mask32_128(UninitializeTag) {}
    // Constructor to broadcast the same value into all elements:
    Mask32_128(const Mask32_128& class_simd) = default;

    Mask32_128& operator=(const Mask32_128& class_simd) = default;

    // ------------------------------------------------------
    // Data member accessors
    // ------------------------------------------------------
    KFP_SIMD_INLINE __m128i& simd()
    {
        return m_data;
    }
    KFP_SIMD_INLINE const __m128i& simd() const
    {
        return m_data;
    }
    KFP_SIMD_INLINE __m128 simdf() const
    {
        return _mm_castsi128_ps(m_data);
    }
    KFP_SIMD_INLINE bool operator[](std::size_t index) const
    {
        assert((index >= 0) && ("[Error] (Mask32_128::operator[]): invalid index (" +
               std::to_string(index) + ") given. Negative")
               .data());
        assert((index < SimdLen) &&
               ("[Error] (Mask32_128::operator[]): invalid index (" + std::to_string(index) +
               ") given. Exceeds maximum")
               .data());
        alignas(SimdSize) int
        data[SimdLen]{}; // Helper array
        _mm_store_si128(reinterpret_cast<__m128i*>(data), m_data);
        return data[index];
    }

    // ------------------------------------------------------
    // Print I/O
    // ------------------------------------------------------
    // TODO

    // ------------------------------------------------------
    // Basic Arithmetic
    // ------------------------------------------------------
    KFP_SIMD_INLINE bool isFull() const
    {
        return _mm_testc_si128(m_data, _mm_set1_epi32(-1));
    }
    KFP_SIMD_INLINE bool isEmpty() const
    {
        return _mm_testz_si128(m_data, m_data);
    }

    friend Mask32_128 operator!(const Mask32_128& a)
    {
        Mask32_128 result;
        result.m_data = _mm_xor_si128(_mm_set1_epi32(-1), a.m_data);
        return result;
    }
    friend Mask32_128 operator^(const Mask32_128& a, const Mask32_128& b)
    {
        Mask32_128 result;
        result.m_data = _mm_xor_si128(a.m_data, b.m_data);
        return result;
    }
    friend Mask32_128 operator&&(const Mask32_128& a, const Mask32_128& b)
    {
        Mask32_128 result;
        result.m_data = _mm_and_si128(a.m_data, b.m_data);
        return result;
    }
    friend Mask32_128 operator||(const Mask32_128& a, const Mask32_128& b)
    {
        Mask32_128 result;
        result.m_data = _mm_or_si128(a.m_data, b.m_data);
        return result;
    }

private:
    alignas(SimdSize) __m128i m_data;
};

} // namespace SIMD
} // namespace KFP

#endif // !SIMD_SSE_MASK32_H
