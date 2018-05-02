#include <argon/events/event.hpp>

Argon::Events::EventDefinition::EventDefinition ( const String & event_id ):
	RefCounted ( 1 ),
	event_id ( event_id )
{
	
	event_id_hash = Events::event_id_hash ( event_id );
	
};

Argon::Events::EventDefinition::~EventDefinition ()
{
};

const Argon::String & Argon::Events::EventDefinition::get_event_id () const
{
	
	return event_id;
	
};

uint32_t Argon::Events::EventDefinition::get_event_id_hash () const
{
	
	return event_id_hash;
	
}

Argon::Events::Event::Event ( const EventDefinition * definition, bool cancelable ):
	RefCounted ( 1 ),
	definition ( definition ),
	cancelable ( cancelable ),
	canceled ( false )
{
};

Argon::Events::Event::Event ( const EventDefinition * definition ):
	RefCounted ( 1 ),
	definition ( definition ),
	cancelable ( false ),
	canceled ( false )
{
	
	definition -> Ref ();
	
};

Argon::Events::Event::~Event ()
{
	
	definition -> Deref ();
	
};

const Argon::String & Argon::Events::Event::get_event_id () const
{
	
	return definition -> get_event_id ();
	
}

bool Argon::Events::Event::cancel ()
{
	
	if ( cancelable )
		canceled = true;
		
	return cancelable;
	
};

bool Argon::Events::Event::is_cancleable () const
{
	
	return cancelable;
	
};

bool Argon::Events::Event::was_canceled () const
{
	
	return canceled;
	
};

const Argon::Events::EventDefinition * Argon::Events::Event::get_event_definition () const
{
	
	return definition;
	
};

