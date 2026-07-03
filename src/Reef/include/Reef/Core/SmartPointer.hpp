/*
 * Copyright 2025 Bernhard Rainer.
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

#ifndef REEF_CORE_SMARTPOINTER_HPP
#define REEF_CORE_SMARTPOINTER_HPP

#include <Reef/System.hpp>

#include <Reef/Core/TypeInfo.hpp>

#include <memory>

namespace Reef
{

/// Downcast from U to T if T is an instance of U
template<typename T, std::derived_from<T> U>
T*
dynamicCast(U* ptr)
{
	return T::classType().isSubclassOf(U::classType()) ? static_cast<T*>(ptr) : nullptr;
}


/// Downcast from U to T if T is an instance of U
template<typename T, std::derived_from<T> U>
const T*
dynamicCast(const U* ptr)
{
	return T::classType().isSubclassOf(U::classType()) ? static_cast<const T*>(ptr) : nullptr;
}


/// Downcast from U to T if T is an instance of U
template<typename T, std::derived_from<T> U>
std::shared_ptr<T>
dynamicCast(std::shared_ptr<U> ptr)
{
	return T::classType().isSubclassOf(U::classType()) ? std::static_pointer_cast<T*>(ptr) : nullptr;
}


/// Unconditional downcast from U to T
template<typename T, std::derived_from<T> U>
[[nodiscard]] std::unique_ptr<T>
staticCast(std::unique_ptr<U>&& ptr)
{
	return std::unique_ptr<T>(static_cast<T*>(ptr.release()));
}

} // namespace Reef

#endif // !REEF_CORE_SMARTPOINTER_HPP