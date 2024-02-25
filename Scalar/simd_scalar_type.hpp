// -*- C++ Header -*-
/*
==================================================
Authors: A.Mithran;
Emails: mithran@fias.uni-frankfurt.de
==================================================
*/

#ifndef SIMD_SCALAR_TYPE_H
#define SIMD_SCALAR_TYPE_H

#include "../Base/simd_data.hpp"
#include "../Base/simd_mask.hpp"
#include "../Base/simd_index.hpp"
#include "../Base/simd_class.hpp"

#include <type_traits>

namespace KFP {
namespace SIMD {

using SimdDataI = SimdData<int, Tag::Scalar>::simd_type;
using SimdDataF = SimdData<float, Tag::Scalar>::simd_type;

using ValueDataI = int;
using ValueDataF = float;

using SimdMask = SimdMaskBase<Tag::Scalar>;
using SimdIndex = SimdIndexBase<Tag::Scalar>;

using SimdF = SimdBaseClass<float, Tag::Scalar>;
static_assert(std::is_same<SimdDataF, ValueDataF>::value,
              "[Error]: Invalid simd type for Scalar float SimdClass.");
static_assert(std::is_same<ValueDataF, float>::value,
              "[Error]: Invalid value type for Scalar float SimdClass.");

using SimdI = SimdBaseClass<int, Tag::Scalar>;
static_assert(std::is_same<SimdDataI, ValueDataI>::value,
              "[Error]: Invalid simd type for Scalar int SimdClass.");
static_assert(std::is_same<ValueDataI, int>::value,
              "[Error]: Invalid value type for Scalar int SimdClass.");

} // namespace SIMD
} // namespace KFP

#endif
