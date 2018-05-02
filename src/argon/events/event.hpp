#ifndef ARGON_EVENTS_EVENT_HPP
#define ARGON_EVENTS_EVENT_HPP

#include <argon/events/events.hpp>
#include <argon/memory/refcounted.hpp>

namespace Argon::Events
{
	
	class EventDefinition : public Memory::RefCounted
	{
	public:
		
		EventDefinition ( const String & event_id );
		
		~EventDefinition ();
		
		const String & get_event_id () const;
		uint32_t get_event_id_hash () const;
		
	private:
		
		const String event_id;
		uint32_t event_id_hash;
		
	};
	
	class Event : public Memory::RefCounted
	{
	public:
		
		Event ( const EventDefinition * definition );
		Event ( const EventDefinition * definition, bool cancleable );
		
		~Event ();
		
		const String & get_event_id () const;
		const EventDefinition * get_event_definition () const;
		
		bool cancel ();
		bool is_cancleable () const;
		bool was_canceled () const;
		
	protected:
		
		const EventDefinition * definition;
		
		const bool cancelable;
		bool canceled;
		
	};
	
}

#endif
