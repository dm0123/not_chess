#pragma once

#include <functional>
#include <mutex>
#include <atomic>
#include <algorithm>
#include <vector>

namespace not_chess::core
{
/**
 * \brief EventHandler is a single handler for an Event.
 */
template <typename... Args>
class EventHandler
{
public:
   using handler_func = std::function<void(Args...)>;

   EventHandler(const handler_func& func) : m_handler_func(func)
   {
       m_id = ++id_counter;
   }

   EventHandler(const EventHandler& rhs) : m_handler_func(rhs.m_handler_func), m_id(rhs.m_id)
   {
   }

   EventHandler(EventHandler&& rhs) : m_handler_func(std::move(rhs.m_handler_func)), m_id(std::move(rhs.m_id))
   {
   }

   void operator =(EventHandler&& rhs)
   {
       m_id = ++id_counter;
       m_handler_func = std::move(rhs);
   }
   bool operator ==(const EventHandler& rhs)
   {
        return m_handler_func == rhs.m_handler_func;
   }

   ~EventHandler() = default;

   void operator ()(Args... params) const
   {
      if(m_handler_func)
          m_handler_func(params...);
   }

   uint32_t id() const { return m_id; }
private:
   handler_func m_handler_func;
   uint32_t m_id;
   // This is counter for all handlers
   static std::atomic_uint32_t id_counter;
};

template<typename... Args>
std::atomic_uint32_t EventHandler<Args...>::id_counter = 0;

/**
 * \brief Event is a representations of event on which multiple
 * EventHandlers could be added and called when an event is called
 */
template<typename... Args>
class Event
{
public:
   using HandlerT = EventHandler<Args...>;
   using Handlers = std::vector<HandlerT>;

   Event() = default;
   ~Event() = default;

   Event(Event&& rhs) : m_handlers(std::move(rhs.m_handlers))
   {
   }

   void operator =(Event&& rhs)
   {
       m_handlers = std::move(rhs.m_handlers);
   }

   void Call(Args... args)
   {
       Handlers handlers;
       {
           std::unique_lock<std::mutex> lock(m_events_mtx);
           handlers = MakeHandlersCopy();
       }

       for(auto& handler : m_handlers)
           handler(args...);
   }

   uint32_t Add(HandlerT handler)
   {
       std::unique_lock<std::mutex> lock(m_events_mtx);
       m_handlers.push_back(std::move(handler));
       return handler.id();
   }

   uint32_t Add(typename HandlerT::handler_func func)
   {
       return Add(Event<Args...>::HandlerT(std::move(func)));
   }

   void Remove(HandlerT const& handler)
   {
       std::unique_lock<std::mutex> lock(m_events_mtx);
       auto it = std::find(m_handlers.begin(), m_handlers.end(), handler);
       if(it != m_handlers.end())
           m_handlers.erase(it);
   }

   void Remove(const uint32_t id)
   {
       std::unique_lock<std::mutex> lock(m_events_mtx);
       auto it = std::find_if(m_handlers.begin(), m_handlers.end(), [&id](const Event<Args...>::HandlerT& handler)
       {
           return handler.m_id == id;
       });
       if(it != m_handlers.end())
           m_handlers.erase(it);
   }

   inline uint32_t operator +=(HandlerT handler)
   {
       return Add(std::move(handler));
   }

   inline uint32_t operator +=(typename HandlerT::handler_func func)
   {
       return Add(std::move(func));
   }

   void operator()(Args... args)
   {
       Call(args...);
   }

   Handlers MakeHandlersCopy()
   {
       return m_handlers;
   }
private:
   Handlers m_handlers;
   mutable std::mutex m_events_mtx;
};
} // namespace not_chess::core
