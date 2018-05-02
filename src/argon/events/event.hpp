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
	
	template<typename Element>
	class EventHashMapImpl
	{
	public:	
		
		EventHashMapImpl ( const Element default_value, void ( * element_finalizer ) ( Element * ) ):
			default_value ( default_value ),
			element_finalizer ( element_finalizer )
		{
			
			for ( size_t i = 0; i < EVENT_ID_HASH_MAX; i ++ )
				hash_table [ i ] = nullptr;
			
		};
		
		~EventHashMapImpl ()
		{
			
			for ( size_t i = 0; i < EVENT_ID_HASH_MAX; i ++ )
				delete hash_table [ i ];
			
		};
		
		Element * get_element_ref_temp ( const EventDefinition * event_definition, bool alloc )
		{
			
			uint32_t hash = event_definition -> get_event_id_hash ();
			
			if ( hash_table [ hash ] == nullptr )
			{
				
				if ( ! alloc )
					return nullptr;
				
				hash_table [ hash ] = new HashMapping ( default_value, element_finalizer );
				return hash_table [ hash ] -> get_element_ref_temp ( event_definition, true );
				
			}
			
			return hash_table [ hash ] -> get_element_ref_temp ( event_definition, alloc );
			
		};
		
		void delete_mapping ( const EventDefinition * event_definition )
		{
			
			uint32_t hash = event_definition -> get_event_id_hash ();
			
			if ( hash_table [ hash ] == nullptr )
				return;
			
			hash_table [ hash ] -> delete_mapping ( event_definition );
			
		}
		
	private:
		
		class HashMapping
		{
		public:
			
			HashMapping ( const Element default_value, void ( * element_finalizer ) ( Element * ) ):
				mappings (),
				default_value ( default_value ),
				element_finalizer ( element_finalizer )
			{
			};
			
			~HashMapping ()
			{
				
				size_t mapping_count = mappings.get_count ();
				
				for ( size_t i = 0; i < mapping_count; i ++ )
				{
					
					element_finalizer ( & mappings [ i ].element );
					mappings [ i ].event_definition -> Deref ();
					
				}
				
			};
			
			Element * get_element_ref_temp ( const EventDefinition * event_definition, bool alloc )
			{
				
				size_t mapping_count = mappings.get_count ();
				
				for ( size_t i = 0; i < mapping_count; i ++ )
				{
					
					if ( ( mappings [ i ].event_definition == event_definition ) || ( mappings [ i ].event_definition -> get_event_id () == event_definition -> get_event_id () ) )
						return & mappings [ i ].element;
					
				}
				
				if ( alloc )
				{
					
					mappings.push ( { default_value, event_definition } );
					event_definition -> Ref ();
					
					return & mappings [ mapping_count ].element;
					
				}
				
				return nullptr;
				
			};
			
			void delete_mapping ( const EventDefinition * event_definition )
			{
				
				size_t mapping_count = mappings.get_count ();
				
				for ( size_t i = 0; i < mapping_count; i ++ )
				{
					
					if ( ( mappings [ i ].event_definition == event_definition ) || ( mappings [ i ].event_definition -> get_event_id () == event_definition -> get_event_id () ) )
					{
						
						mappings.remove ( i );
						return;
						
					}
					
				}
				
			};
			
			typedef struct
			{
				
				Element element;
				const EventDefinition * event_definition;
				
			} MappingElement;
			
			const Element default_value;
			
			Vector<MappingElement> mappings;
			
			void ( * element_finalizer ) ( Element * );
			
		};
		
		void ( * element_finalizer ) ( Element * );
		
		const Element default_value;
		
		HashMapping * hash_table [ EVENT_ID_HASH_MAX ];
		
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
