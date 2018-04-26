#ifndef ARGON_GEOMETRY_GEOMETRY_H
#define ARGON_GEOMETRY_GEOMETRY_H

#include <cmath>

namespace Argon::Geometry
{
	
	class Vec2F32;
	class RectF32;
	
	typedef RectF32 Rect;
	typedef Vec2F32 Vec2;
	
	class Vec2F32
	{
	public:
		
		float x;
		float y;
		
		Vec2F32 ( float x = 0.0f, float y = 0.0f ):
			x ( x ),
			y ( y )
		{
		};
		
		Vec2F32 ( const Vec2F32 & copy_from ):
			x ( copy_from.x ),
			y ( copy_from.y )
		{
		};
		
		Vec2F32 ( Vec2F32 && moved ):
			x ( moved.x ),
			y ( moved.y )
		{	
		};
		
		enum DIRECTION_AND_MAGNITUDE
		{
			
			DirAndMag
			
		};
		
		Vec2F32 ( DIRECTION_AND_MAGNITUDE _, float direction, float magnitude ):
			x ( cosf ( direction ) * magnitude ),
			y ( sinf ( direction ) * magnitude )
		{
		};
		
		~Vec2F32 ()
		{
		}
		
		static const Vec2F32 Zero;
		static const Vec2F32 One;
		static const Vec2F32 Left;
		static const Vec2F32 Right;
		static const Vec2F32 Up;
		static const Vec2F32 Down;
		
	};
	
	class RectF32
	{
	public:
			
		Vec2F32 origin;
		Vec2F32 size;
		
		RectF32 ():
			origin ( Vec2F32::Zero ),
			size ( Vec2F32::Zero )
		{
		};
		
		RectF32 ( Vec2F32 origin, Vec2F32 size ):
			origin ( origin ),
			size ( size )
		{
		};
		
		RectF32 ( float x, float y, float width, float height ):
			origin ( x, y ),
			size ( width, height )
		{
		};
		
		RectF32 ( const RectF32 & copy_from ):
			origin ( copy_from.origin ),
			size ( copy_from.size )
		{
		};
		
		RectF32 ( RectF32 && moved ):
			origin ( moved.origin ),
			size ( moved.size )
		{
		};
		
		~RectF32 ()
		{
		}
		
	};
	
}

#endif
