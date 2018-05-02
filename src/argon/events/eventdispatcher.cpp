#include <argon/events/eventdispatcher.hpp>

Argon::Events::EventDispatcher::EventDispatcher ():
	handler_event_map ( nullptr, & handler_event_map_finalizer )
{
};

Argon::Events::EventDispatcher::~EventDispatcher ()
{
};

void Argon::Events::EventDispatcher::add_event_listener ( const EventDefinition * definition, EventHandlerFn event_handler, void * event_handler_data, int index )
{
	
	Vector<HandlerInfo> ** handler_info_list_ptr_ptr = handler_event_map.get_element_ref_temp ( definition, true );
	
	if ( * handler_info_list_ptr_ptr == nullptr )
		* handler_info_list_ptr_ptr = new Vector <HandlerInfo> ();
		
	Vector<HandlerInfo> & handler_info_list = ( ** handler_info_list_ptr_ptr );
		
	if ( index == kevent_index_end )
		handler_info_list.push ( { event_handler, event_handler_data } );
	else
		handler_info_list.add_at ( { event_handler, event_handler_data }, index );
	
};

void Argon::Events::EventDispatcher::remove_event_listeners ( const EventDefinition * definition, int count )
{
	
	if ( count < 0 )
	{
		
		handler_event_map.delete_mapping ( definition );
		return;
		
	}
	
	Vector<HandlerInfo> ** handler_info_list_ptr_ptr = handler_event_map.get_element_ref_temp ( definition, false );
	
	if ( * handler_info_list_ptr_ptr == nullptr )
		return;
	
	Vector<HandlerInfo> & handler_info_list = ( ** handler_info_list_ptr_ptr );
	
	int list_count = handler_info_list.get_count ();
	
	if ( list_count == 0 )
		return;
		
	if ( count > list_count )
		count = list_count;
		
	handler_info_list.remove ( list_count - count, list_count );
	
};

void Argon::Events::EventDispatcher::remove_event_listener_fn ( const EventDefinition * definition, EventHandlerFn event_handler, int count )
{
	
	Vector<HandlerInfo> ** handler_info_list_ptr_ptr = handler_event_map.get_element_ref_temp ( definition, false );
	
	if ( * handler_info_list_ptr_ptr == nullptr )
		return;
	
	Vector<HandlerInfo> & handler_info_list = ( ** handler_info_list_ptr_ptr );
	
	size_t list_count = handler_info_list.get_count ();
	
	if ( list_count == 0 )
		return;
	
	if ( count < 0 )
	{
		
		size_t i = list_count;
		
		do
		{
			
			i --;
			
			if ( handler_info_list [ i ].event_handler == event_handler )
				handler_info_list.remove ( i, 1 );
			
		}
		while ( i != 0 );
		
		return;
		
	}
	
	size_t i = 0;
	
	while ( count > 0 )
	{
			
		for ( ; i < list_count; i ++ )
		{
			
			if ( handler_info_list [ i ].event_handler == event_handler )
			{
				
				handler_info_list.remove ( i, 1 );
				
				i --;
				list_count --;
				count --;
				
				break;
				
			}
			
		}
		
		if ( i == list_count )
			return;
		
	}
	
};

void Argon::Events::EventDispatcher::remove_event_listener_specific ( const EventDefinition * definition, EventHandlerFn event_handler, void * event_handler_data, int count )
{
	
	Vector<HandlerInfo> ** handler_info_list_ptr_ptr = handler_event_map.get_element_ref_temp ( definition, false );
	
	if ( * handler_info_list_ptr_ptr == nullptr )
		return;
	
	Vector<HandlerInfo> & handler_info_list = ( ** handler_info_list_ptr_ptr );
	
	size_t list_count = handler_info_list.get_count ();
	
	if ( list_count == 0 )
		return;
	
	if ( count < 0 )
	{
		
		size_t i = list_count;
		
		do
		{
			
			i --;
			
			if ( ( handler_info_list [ i ].event_handler == event_handler ) && ( handler_info_list [ i ].event_handler_data == event_handler_data ) )
				handler_info_list.remove ( i, 1 );
			
		}
		while ( i != 0 );
		
		return;
		
	}
	
	size_t i = 0;
	
	while ( count > 0 )
	{
			
		for ( ; i < list_count; i ++ )
		{
			
			if ( ( handler_info_list [ i ].event_handler == event_handler ) && ( handler_info_list [ i ].event_handler_data == event_handler_data ) )
			{
				
				handler_info_list.remove ( i, 1 );
				
				i --;
				list_count --;
				count --;
				
				break;
				
			}
			
		}
		
		if ( i == list_count )
			return;
		
	}
	
};

void Argon::Events::EventDispatcher::remove_event_listener_matching ( const EventDefinition * definition, EventHandlerFn event_handler, void * event_handler_data, EventHandlerMatchFn compare_function, int count )
{
	
	Vector<HandlerInfo> ** handler_info_list_ptr_ptr = handler_event_map.get_element_ref_temp ( definition, false );
	
	if ( * handler_info_list_ptr_ptr == nullptr )
		return;
	
	Vector<HandlerInfo> & handler_info_list = ( ** handler_info_list_ptr_ptr );
	
	size_t list_count = handler_info_list.get_count ();
	
	if ( list_count == 0 )
		return;
	
	if ( count < 0 )
	{
		
		size_t i = list_count;
		
		do
		{
			
			i --;
			
			if ( compare_function ( handler_info_list [ i ].event_handler, event_handler, handler_info_list [ i ].event_handler_data, event_handler_data ) )
				handler_info_list.remove ( i, 1 );
			
		}
		while ( i != 0 );
		
		return;
		
	}
	
	size_t i = 0;
	
	while ( count > 0 )
	{
			
		for ( ; i < list_count; i ++ )
		{
			
			if ( compare_function ( handler_info_list [ i ].event_handler, event_handler, handler_info_list [ i ].event_handler_data, event_handler_data ) )
			{
				
				handler_info_list.remove ( i, 1 );
				
				i --;
				list_count --;
				count --;
				
				break;
				
			}
			
		}
		
		if ( i == list_count )
			return;
		
	}
	
};

void Argon::Events::EventDispatcher::dispatch_event ( Event * event )
{
	
	Vector<HandlerInfo> ** handler_info_list_ptr_ptr = handler_event_map.get_element_ref_temp ( event -> get_event_definition (), false );
	
	if ( ( handler_info_list_ptr_ptr == nullptr ) || ( * handler_info_list_ptr_ptr == nullptr ) )
		return;
	
	Vector<HandlerInfo> & handler_info_list = ( ** handler_info_list_ptr_ptr );
	
	size_t count = handler_info_list.get_count ();
	
	for ( int i = 0; i < count; i ++ )
		handler_info_list [ i ].event_handler ( event, handler_info_list [ i ].event_handler_data );
	
};

void Argon::Events::EventDispatcher::handler_event_map_finalizer ( Vector<HandlerInfo> ** handler_info_list_ptr_ptr )
{
	
	if ( * handler_info_list_ptr_ptr == nullptr )
		return;
	
	delete ( * handler_info_list_ptr_ptr );
	
};
