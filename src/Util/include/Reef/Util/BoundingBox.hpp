/*
 * Copyright 2026 Bernhard Rainer.
 *
 * Licensed under the MIT License (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://opensource.org/licenses/MIT
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef REEF_UTIL_BOUNDINGBOX_HPP
#define REEF_UTIL_BOUNDINGBOX_HPP

#include <Reef/Util/Export.hpp>

#include <glm/glm.hpp>

#include <span>

namespace Reef::Util
{

template<size_t S, typename FLOAT>
class UTIL_API BoundingBox
{
public:
    using Vector = glm::vec<S, FLOAT, glm::packed_highp>;

    BoundingBox() = default;

    BoundingBox(const Vector& min, const Vector& max);

    Vector min() const;

    Vector max() const;

    Vector center() const;

    Vector size() const;

    void add(const Vector& p);

    void add(std::span<const Vector> ps);

    void add(const BoundingBox<S, FLOAT>& box);

    BoundingBox& operator+=(const BoundingBox& rhs);

    BoundingBox& operator+=(const Vector& rhs);

private:

    bool mValid{ false };

    Vector mMin{ FLOAT(0), FLOAT(0), FLOAT(0) };

    Vector mMax{ FLOAT(0), FLOAT(0), FLOAT(0) };

}; // class BoundingBox

template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT> operator+(const BoundingBox<S, FLOAT>& lhs, const BoundingBox<S, FLOAT>& rhs);

template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT> operator+(const BoundingBox<S, FLOAT>& lhs, const typename BoundingBox<S, FLOAT>::Vector& rhs);

template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT> operator+(const typename BoundingBox<S, FLOAT>::Vector& lhs, const BoundingBox<S, FLOAT>& rhs);


using BoundingBox2D = BoundingBox<2, float>;

using BoundingBox3D = BoundingBox<3, float>;


template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT>::BoundingBox(const BoundingBox<S, FLOAT>::Vector& min,
                                   const BoundingBox<S, FLOAT>::Vector& max)
{
    add(min);
    add(max);
}


template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT>::Vector
BoundingBox<S, FLOAT>::min() const
{
    return mMin;
}


template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT>::Vector
BoundingBox<S, FLOAT>::max() const
{
    return mMax;
}


template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT>::Vector
BoundingBox<S, FLOAT>::center() const
{
    return (mMin + mMax) / FLOAT(2);
}


template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT>::Vector
BoundingBox<S, FLOAT>::size() const
{
    return mMax - mMin;
}


template<size_t S, typename FLOAT>
void
BoundingBox<S, FLOAT>::add(const BoundingBox<S, FLOAT>::Vector& p)
{
    if (!mValid)
    {
        mMin = p;
        mMax = p;
    }
    else
    {
        mMin = glm::min(mMin, p);
        mMax = glm::max(mMax, p);
    }

    mValid = true;
}

template<size_t S, typename FLOAT>
void
BoundingBox<S, FLOAT>::add(std::span<const Vector> ps)
{
    for (auto p : ps)
    {
        add(p);
    }
}


template<size_t S, typename FLOAT>
void
BoundingBox<S, FLOAT>::add(const BoundingBox<S, FLOAT>& box)
{
    if (box.mValid)
    {
        add(box.min());
        add(box.max());
    }
}


template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT>&
BoundingBox<S, FLOAT>::operator+=(const BoundingBox<S, FLOAT>& rhs)
{
    add(rhs);
    return *this;
}


template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT>&
BoundingBox<S, FLOAT>::operator+=(const BoundingBox<S, FLOAT>::Vector& value)
{
    add(value);
    return *this;
}


template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT>
operator+(const BoundingBox<S, FLOAT>& lhs, const BoundingBox<S, FLOAT>& rhs)
{
    BoundingBox3D result = lhs;
    result.add(rhs);
    return result;
}


template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT>
operator+(const BoundingBox<S, FLOAT>& lhs, const typename BoundingBox<S, FLOAT>::Vector& rhs)
{
    BoundingBox3D result = lhs;
    result.add(rhs);
    return result;
}


template<size_t S, typename FLOAT>
BoundingBox<S, FLOAT>
operator+(const typename BoundingBox<S, FLOAT>::Vector& lhs, const BoundingBox<S, FLOAT>& rhs)
{
    BoundingBox3D result = rhs;
    result.add(lhs);
    return result;
}

} // namespace Reef::Util

#endif !REEF_UTIL_BOUNDINGBOX_HPP
