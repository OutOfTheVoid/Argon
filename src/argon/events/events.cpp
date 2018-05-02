#include <argon/events/events.hpp>

uint32_t Argon::Events::event_id_hash ( const String & event_id )
{
	
	uint32_t hash = 0;
	const Vector<char32_t> & event_id_chars = event_id.get_chars ();
	uint32_t count = event_id_chars.get_count ();
	
	for ( int i = 0; i < count; i ++ )
	{
		
		uint32_t char_val = static_cast<uint32_t> ( event_id_chars [ i ] );
		char_val |= char_val >> 16;
		char_val |= char_val >> 8;
		hash ^= char_val;
		hash *= ( hash + 1 );
		
	}
	
	return hash % EVENT_ID_HASH_MAX;
	
}
