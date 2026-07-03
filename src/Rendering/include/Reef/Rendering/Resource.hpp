#ifndef REEF_RENDERING_RESOURCE_HPP
#define REEF_RENDERING_RESOURCE_HPP

#include <Reef/Rendering/Export.hpp>

#include <mutex>
#include <string>
#include <string_view>

namespace Reef::Rendering
{

class RENDERING_API Resource
{
public:

    Resource();

    virtual ~Resource() = default;

    /*!
     * \brief Get the unique id of the resource
     */
    uint64_t id() const;

    /*!
     * \brief Set the name of the resource
     * \param name The name of the resource
     */
    void setName(std::string_view name);

    /*!
     * \brief Get the name of the resource
     * \return The name of the resource. Valid until the resource is destroyed or the name is changed.
     */
    const std::string& name() const;

    /*!
     * \brief Get the version of the resource
     * \Note: This function is not thread-safe and should only be called from within a locked scope.
     */
    size_t version() const;

    /*!
     * \brief Lock the resource from concurrent access
     * 
     * The returned resource lock must be destroyed before the resource object itself is destroyed.
     * \return Returns a scoped lock that locks the resource from concurrent access.
     */
    [[nodiscard]] std::scoped_lock<std::mutex> lock() const;

    /*!
     * \brief Tries to lock the resource from concurrent access
     * The returned resource lock must be destroyed before the resource object itself is destroyed.
     * 
     * \return Returns a scoped lock that locks the resource from concurrent access
     */
    [[nodiscard]] std::unique_lock<std::mutex> tryLock() const;

protected:

    /*!
     * \brief Mark the resource outdated
     *
     * Calling this function bumps the version number so that consumers of the resource are notified that the resource
     * has changed.
     * \Note: This function is not thread-safe and should only be called from within a locked scope.
     */
    void markOutdated();

private:

    size_t mId;

    mutable bool mOutdated{ true };

    mutable size_t mVersion{ 0 };

    mutable std::mutex mResourceProtection;

    std::string mName;

}; // class Resource

} // namespace Reef::Rendering

#endif // !REEF_RENDERING_RESOURCE_HPP
