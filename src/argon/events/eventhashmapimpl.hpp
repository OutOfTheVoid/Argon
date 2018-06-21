#ifndef ARGON_EVENTS_EVENTHASHMAPIMPL_HPP
#define ARGON_EVENTS_EVENTHASHMAPIMPL_HPP

namespace Argon::Events
{
	
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
					mappings [ i ].event_definition -> deref ();
					
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
					
					MappingElement mapping { default_value, event_definition };
					
					mappings.push ( mapping );
					event_definition -> ref ();
					
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
	
}

#endif
