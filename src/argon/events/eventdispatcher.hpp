#ifndef ARGON_EVENTS_EVENTDISPATCHER_HPP
#define ARGON_EVENTS_EVENTDISPATCHER_HPP

#include <argon/events/event.hpp>
#include <argon/events/eventhashmapimpl.hpp>

namespace Argon::Events
{
	
	typedef void ( * EventHandlerFn ) ( Event *, void * );
	typedef bool ( * EventHandlerMatchFn ) ( EventHandlerFn event_handler_a, EventHandlerFn event_handler_b, void * data_a, void * data_b );
	
	class IEventDispatcher
	{
	public:
		
		static const int kevent_count_all = - 1;
		static const int kevent_index_end = - 1;
		
		// add an event listener for <definition>, placing it at <index> for that event, or at the end if <index> < 0.
		virtual void add_event_listener ( const EventDefinition * definition, EventHandlerFn event_handler, void * event_handler_data, int index = - 1 ) = 0;
		
		// remove the last <count> listeners for <definition>, or all if <count> < 1
		virtual void remove_event_listeners ( const EventDefinition * definition, int count = - 1 ) = 0;
		
		// remove the first <count> event listeners for <definition> which match the same function address <event_handler>, or all matching if <count> < 0
		virtual void remove_event_listener_fn ( const EventDefinition * definition, EventHandlerFn event_handler, int count = 1 ) = 0;
		
		// remove the first <count> listeners for the event <definition> with a specified function address <event_handler> and handler data pointer <event_handler_data>, or all matching if <count> < 0
		virtual void remove_event_listener_specific ( const EventDefinition * definition, EventHandlerFn event_handler, void * event_handler_data, int count = 1 ) = 0;
		
		// remove the first <count> listeners for the event <definition> with a specified function address <event_handler> and handler data pointer <event_handler_data>, using the compare function <compare_function> to test for equality, or all matching if <count> < 0.
		virtual void remove_event_listener_matching ( const EventDefinition * definition, EventHandlerFn event_handler, void * event_handler_data, EventHandlerMatchFn compare_function, int count = 1 ) = 0;
		
	};
	
	class EventDispatcher : public virtual IEventDispatcher
	{
	public:
		
		virtual void add_event_listener ( const EventDefinition * definition, EventHandlerFn event_handler, void * event_handler_data, int index = - 1 );
		virtual void remove_event_listeners ( const EventDefinition * definition, int count = - 1 );
		virtual void remove_event_listener_fn ( const EventDefinition * definition, EventHandlerFn event_handler, int count = 1 );
		virtual void remove_event_listener_specific ( const EventDefinition * definition, EventHandlerFn event_handler, void * event_handler_data, int count = 1 );
		virtual void remove_event_listener_matching ( const EventDefinition * definition, EventHandlerFn event_handler, void * event_handler_data, EventHandlerMatchFn compare_function, int count = 1 );
		
	protected:
		
		EventDispatcher ();
		~EventDispatcher ();
		
		void dispatch_event ( Event * event );
		
	private:
		
		typedef struct
		{
			
			EventHandlerFn event_handler;
			void * event_handler_data;
			
		} HandlerInfo;
		
		static void handler_event_map_finalizer ( Vector<HandlerInfo> ** handler_info_list_ptr_ptr );
		
		EventHashMapImpl<Vector<HandlerInfo> *> handler_event_map;
		
	};
	
}

#endif
