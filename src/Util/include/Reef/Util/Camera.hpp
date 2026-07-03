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

#ifndef REEF_UTIL_CAMERA_HPP
#define REEF_UTIL_CAMERA_HPP

#include <Reef/Util/Export.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Reef::Util
{

template<typename FLOAT>
class UTIL_API Camera
{
public:

    Camera() = default;

    const glm::uvec2& resolution() const;

    const glm::vec<2, FLOAT>& nearFar() const;

    FLOAT verticalFoV() const;

    FLOAT aspect() const;

    const glm::mat<4, 4, FLOAT>& projectionMatrix() const;

    void set(const glm::uvec2& resolution, const glm::vec<2, FLOAT>& nearFar, FLOAT verticalFoV);

private:

    glm::uvec2 mResolution{ 1920u, 1080u };

    glm::vec<2, FLOAT> mNearFar{ FLOAT(0.01), FLOAT(1000) };

    float mVerticalFoV{ FLOAT(75) };

    glm::mat<4, 4, FLOAT> mProjectionMatrix{ 1.f };
};

using CameraF = Camera<float>;

template<typename FLOAT>
const glm::uvec2&
Camera<FLOAT>::resolution() const
{
    return mResolution;
}


template<typename FLOAT>
const glm::vec<2, FLOAT>&
Camera<FLOAT>::nearFar() const
{
    return mNearFar;
}


template<typename FLOAT>
FLOAT
Camera<FLOAT>::verticalFoV() const
{
    return mVerticalFoV;
}


template<typename FLOAT>
FLOAT
Camera<FLOAT>::aspect() const
{
    return static_cast<FLOAT>(mResolution.x) / mResolution.y;
}


template<typename FLOAT>
const glm::mat<4, 4, FLOAT>&
Camera<FLOAT>::projectionMatrix() const
{
    return mProjectionMatrix;
}


template<typename FLOAT>
void Camera<FLOAT>::set(const glm::uvec2& resolution, const glm::vec<2, FLOAT>& nearFar, FLOAT verticalFoV)
{
    mResolution       = resolution;
    mNearFar          = nearFar;
    mVerticalFoV      = verticalFoV;
    mProjectionMatrix = glm::perspective(glm::radians(mVerticalFoV), aspect(), mNearFar.x, mNearFar.y);
}

} // namespace Reef::Util

#endif // !REEF_UTIL_CAMERA_HPP
