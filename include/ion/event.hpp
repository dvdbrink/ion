#pragma once

#include <functional>
#include <vector>

namespace ion
{
    template <typename T>
    struct ConnectionTraits : public ConnectionTraits<decltype(&T::operator())> {};

    template <typename C, typename R, typename A>
    struct ConnectionTraits<R(C::*)(const A&) const>
    {
        typedef A type;
    };

    template <typename Event>
    class EventBroadcaster
    {
    public:
        typedef std::function<void(const Event&)> Connection;

    public:
        virtual ~EventBroadcaster() {}

        void connect(Connection&& connection)
        {
            _connections.push_back(std::move(connection));
        }

        void signal(const Event& event)
        {
            for (const auto& connection : _connections)
            {
                connection(event);
            }
        }

    private:
        std::vector<Connection> _connections;
    };

    template <typename... Events>
    class EventsBroadcaster : EventBroadcaster<Events>...
    {
    public:
        virtual ~EventsBroadcaster() {}

        template <typename Connection>
        void connect(Connection&& connection)
        {
            typedef typename ConnectionTraits<Connection>::type Event;
            EventBroadcaster<Event>& impl = *this;
            impl.connect(std::move(connection));
        }

        template <typename Event>
        void signal(const Event& event)
        {
            EventBroadcaster<Event>& impl = *this;
            impl.signal(event);
        }
    };
}