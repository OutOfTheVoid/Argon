#include <argon/rendering/vertexspecification.hpp>
#include <argon/rendering/context.hpp>

Argon::Rendering::VertexSpecification::VertexSpecification ( GLuint name, Context * source_context ):
	RefCounted ( 1 ),
	name ( name ),
	source_context ( source_context )
{
	
	source_context -> ref ();
	
}

Argon::Rendering::VertexSpecification::~VertexSpecification ()
{
	
	source_context -> deref ();
	
}
