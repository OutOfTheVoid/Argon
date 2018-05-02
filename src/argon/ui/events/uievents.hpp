#ifndef ARGON_UI_EVENTS_UIEVENTS_HPP
#define ARGON_UI_EVENTS_UIEVENTS_HPP

#include <argon/events/events.hpp>
#include <argon/events/event.hpp>

#include <argon/rendering/context.hpp>

namespace Argon::UI
{
	
	class GUIWindow;
	
}

namespace Argon::Rendering
{
	
	class Context;
	
}

namespace Argon::UI::Events
{
	
	using Argon::Events::Event;
	using Argon::Events::EventDefinition;
	
	using Argon::Rendering::Context;
	
	class WindowEvent : public Event
	{
	public:
		
		static const EventDefinition kevent_will_close;
		
		WindowEvent ( const EventDefinition * definition, GUIWindow * source_window );
		virtual ~WindowEvent ();
		
		GUIWindow * get_source_window ();
		const GUIWindow * get_source_window () const;
		
	private:
		
		GUIWindow * source_window;
		
	};
	
	class WindowShouldCloseEvent : public WindowEvent
	{
	public:
		
		static const EventDefinition kevent_should_close;
		
		WindowShouldCloseEvent ( GUIWindow * source_window );
		~WindowShouldCloseEvent ();
		
		void cancel_close ();
		
		bool was_close_cancelled () const;
		
	private:
		
		bool close_canceled;
		
	};
	
	class RenderEvent : public WindowEvent
	{
	public:
		
		static const EventDefinition kevent_render;
		
		RenderEvent ( GUIWindow * source_window, Context * source_context );
		~RenderEvent ();
		
		const Context * get_source_context () const;
		Context * get_source_context ();
		
	private:
		
		GUIWindow * source_window;
		Context * source_context;
		
	};
	
}

#endif
