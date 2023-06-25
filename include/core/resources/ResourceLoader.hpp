#ifndef __RESOURCE_LOADER_HPP__
#define __RESOURCE_LOADER_HPP__

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

/**
 * Abstract base class for all resource loaders.
 * Unifies the process of loading, retrieving, and freeing local resources from
 * disk.
 * @tparam ResourceT The type of the resource
 */
template <typename ResourceT>
class ResourceLoader
{
public:
    /**
     * A destructor for Resource Loader
     */
    virtual ~ResourceLoader();

    /**
     * Load and parse the data from the file at fileLoc.
     * WARN: Will cause memory leak if you do not pass a deleter to the
     * shared_ptr
     * @param fileLoc The location of the loaded file
     */
    virtual void Load(std::string fileLoc) = 0;

    /**
     * Save the data to the corresponding file (if implemented).
     * @param resource The place we are saving to
     */
    virtual void Save(std::shared_ptr<ResourceT>& resource);

    /**
     * Retrieve the saved copy of a local resource.
     * @param fileLoc The location of the file
     * @return The saved copy of the resource
     */
    std::shared_ptr<ResourceT> Get(std::string fileLoc);

    /**
     * Free the loaded resource from memory.
     * @param resource The resource we are destroying
     */
    void Destroy(std::shared_ptr<ResourceT>& resource);

protected:
    // Protected to emphasize abstract base class
    /**
     * Default Constructor
     */
    ResourceLoader();

    std::unordered_map<std::string, std::shared_ptr<ResourceT>> mResources;

    /**
     * Find the resource in the map by the pointer
     */
    typename std::unordered_map<std::string,
                                std::shared_ptr<ResourceT>>::iterator
    FindByPtr(const std::shared_ptr<ResourceT>& resource);
};

// Templated method definitions

/**
 * Save the data to the corresponding file (if implemented).
 * @tparam ResourceT The type of the resource
 * @param resource The place we are saving to
 */
template <typename ResourceT>
void ResourceLoader<ResourceT>::Save(std::shared_ptr<ResourceT>& resource)
{
    throw std::logic_error(
        "Save functionality has not been implemented for this resource type.");
}

/**
 * Retrieve the saved copy of a local resource.
 * @tparam ResourceT The type of the resource
 * @param fileLoc The location of the file
 * @return The saved copy of the resource
 */
template <typename ResourceT>
std::shared_ptr<ResourceT> ResourceLoader<ResourceT>::Get(std::string fileLoc)
{
    auto resourceIt = mResources.find(fileLoc);
    if (resourceIt == mResources.end())
    {
        return nullptr;
    }
    return resourceIt->second;
}

/**
 * The default constructor
 * @tparam ResourceT The type of the resource
 */
template <typename ResourceT>
ResourceLoader<ResourceT>::ResourceLoader()
{
}

/**
 * The destructor which clears the resources
 * @tparam ResourceT The type of the resource
 */
template <typename ResourceT>
ResourceLoader<ResourceT>::~ResourceLoader()
{
    if (mResources.size() != 0)
    {
        // std::cout << "There were " << m_resources.size() << " non-destroyed
        // resources upon shutdown. Cleaning up...\n";
        mResources.clear();
    }
}

/**
 * Free the loaded resource from memory.
 * @tparam ResourceT The type of the resource
 * @param resource The resource we are destroying
 */
template <typename ResourceT>
void ResourceLoader<ResourceT>::Destroy(std::shared_ptr<ResourceT>& resource)
{
    if (resource.use_count() > 2)
    {
        resource.reset();
        return;
    }

    if (!resource)
    {
        // Pointer was already freed
        return;
    }

    auto resourceIt = FindByPtr(resource);

    if (resourceIt == mResources.end())
    {
        // Resource has already been freed
        return;
    }

    resource.reset();
    // There are no more references to the resource; Free it

    // There is no need to call this because the deleter passed to the
    // shared_ptr will call it when the last reference is destroyed (it is
    // removed from the map).

    // WARN: Will cause memory leak if you do not pass a deleter to the
    // shared_ptr

    mResources.erase(resourceIt->first);
}

/**
 * Find the resource in the map by the pointer
 * @tparam ResourceT The type of the resource
 */
template <typename ResourceT>
typename std::unordered_map<std::string, std::shared_ptr<ResourceT>>::iterator
ResourceLoader<ResourceT>::FindByPtr(const std::shared_ptr<ResourceT>& resource)
{
    auto resourceIt = mResources.begin();
    for (; resourceIt != mResources.end(); ++resourceIt)
    {
        if (resourceIt->second == resource) break;
    }
    return resourceIt;
}

#endif
