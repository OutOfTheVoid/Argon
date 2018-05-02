#ifndef ARGON_EVENTS_EVENTS_HPP
#define ARGON_EVENTS_EVENTS_HPP

#include <argon/argon.hpp>

#define EVENT_ID_HASH_MAX 0x1F

namespace Argon::Events
{
	
	uint32_t event_id_hash ( const String & event_id );
	
}

#endif
