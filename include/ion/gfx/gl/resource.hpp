#pragma once

#include <cassert>
#include <functional>
#include <unordered_map>

namespace ion { namespace gfx { namespace gl
{
    template <typename T>
    class Resource
    {
    public:
        typedef std::function<void(int, unsigned int*)> CreateResource;
        typedef std::function<void(int, unsigned int*)> DeleteResource;
        typedef std::function<void(unsigned int)> DeleteResourceId;

    public:
        Resource(CreateResource&& c, DeleteResource&& d) :
                create_(std::move(c)),
                delete_(std::move(d)),
                delete_id_(nullptr),
                id_(0)
        {
            create();
        }

        Resource(unsigned int id, DeleteResourceId&& d2) :
                create_(nullptr),
                delete_(nullptr),
                delete_id_(std::move(d2)),
                id_(0)
        {
            create(id);
        }

        Resource(const Resource& copy) :
                create_(copy.create_),
                delete_(copy.delete_),
                delete_id_(copy.delete_id_),
                id_(0)
        {
            create();
        }

        virtual ~Resource()
        {
            destroy();
        }

        Resource& operator=(const Resource& copy)
        {
            destroy();
            create(copy.id_);
            return *this;
        }

        unsigned int id() const
        {
            return id_;
        }

    private:
        void create()
        {
            assert(create_);
            create_(1, &id_);
            refs.insert(std::make_pair(id_, 1));
        }

        void create(unsigned int id)
        {
            id_ = id;
            if (refs.count(id_) > 0)
            {
                refs[id_]++;
            }
            else
            {
                refs.insert(std::make_pair(id_, 1));
            }
        }

        void destroy()
        {
            assert(delete_ || delete_id_);
            if (--refs[id_] == 0)
            {
                if (delete_)
                {
                    delete_(1, &id_);
                }
                else if (delete_id_)
                {
                    delete_id_(id_);
                }
            }
        }

    private:
        CreateResource create_;
        DeleteResource delete_;
        DeleteResourceId delete_id_;
        unsigned int id_;

    private:
        static std::unordered_map<unsigned int, unsigned int> refs;
    };

    template <typename T>
    std::unordered_map<unsigned int, unsigned int> Resource<T>::refs;
}}}