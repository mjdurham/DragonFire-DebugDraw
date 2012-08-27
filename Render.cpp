#include "Render.h"

#include "DragonFireSDK.h"
#include <cstdarg>


void DebugDraw::Setup(int &draw, int &text, int pixels_per_meter_rate)
{
	draw_handle = draw;
	text_handle = text;
	pixels_per_meter = pixels_per_meter_rate;
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	DrawSetColor(draw_handle, ((int)(color.r*255.0) << 16) + ((int)(color.g*255.0) << 8) + (int)(color.b*255.0));
	DrawMoveTo(draw_handle, Round(vertices[0].x*pixels_per_meter), Round(vertices[0].y*pixels_per_meter));
	for (int i=1; i<vertexCount; i++)
	{
		DrawLineTo(draw_handle, Round(vertices[i].x*pixels_per_meter), Round(vertices[i].y*pixels_per_meter));
	}
	DrawLineTo(draw_handle, Round(vertices[0].x*pixels_per_meter), Round(vertices[0].y*pixels_per_meter));
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	// There is no reasonable way to draw a solid polygon
	DrawPolygon(vertices, vertexCount, color);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	DrawSetColor(draw_handle, ((int)(color.r*255.0) << 16) + ((int)(color.g*255.0) << 8) + (int)(color.b*255.0));
	::DrawCircle(draw_handle, Round((center.x-radius)*pixels_per_meter), Round((center.y-radius)*pixels_per_meter), Round(radius*pixels_per_meter*2), Round(radius*pixels_per_meter*2));
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	DrawCircle(center, radius, color);
	b2Vec2 p = center + radius * axis;
	DrawLine(draw_handle, Round(center.x*pixels_per_meter), Round(center.y*pixels_per_meter), Round(p.x*pixels_per_meter), Round(p.y*pixels_per_meter));
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	DrawSetColor(draw_handle, ((int)(color.r*255.0) << 16) + ((int)(color.g*255.0) << 8) + (int)(color.b*255.0));
	DrawLine(draw_handle, Round(p1.x*pixels_per_meter), Round(p1.y*pixels_per_meter), Round(p2.x*pixels_per_meter), Round(p2.y*pixels_per_meter));
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{

#ifdef V212

	b2Vec2 p1 = xf.position, p2;
	const float32 k_axisScale = 0.4f;

	p2 = p1 + k_axisScale * xf.R.col1;
	DrawSetColor(draw_handle, 0xFF0000);
	DrawLine(draw_handle, Round(p1.x*pixels_per_meter), Round(p1.y*pixels_per_meter), Round(p2.x*pixels_per_meter), Round(p2.y*pixels_per_meter));

	p2 = p1 + k_axisScale * xf.R.col2;
	DrawSetColor(draw_handle,0x00FF00);
	DrawLine(draw_handle, Round(p1.x*pixels_per_meter), Round(p1.y*pixels_per_meter), Round(p2.x*pixels_per_meter), Round(p2.y*pixels_per_meter));


#else

	b2Vec2 p1 = xf.p, p2;
	const float32 k_axisScale = 0.4f;
	
	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	DrawSetColor(draw_handle, 0xFF0000);
	DrawLine(draw_handle, Round(p1.x*pixels_per_meter), Round(p1.y*pixels_per_meter), Round(p2.x*pixels_per_meter), Round(p2.y*pixels_per_meter));

	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	DrawSetColor(draw_handle,0x00FF00);
	DrawLine(draw_handle, Round(p1.x*pixels_per_meter), Round(p1.y*pixels_per_meter), Round(p2.x*pixels_per_meter), Round(p2.y*pixels_per_meter));

#endif
}

void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	DrawSetFillColor(draw_handle, ((int)(color.r*255.0) << 16) + ((int)(color.g*255.0) << 8) + (int)(color.b*255.0));
	DrawSquareFill(draw_handle, Round(p.x-size/2.0f), Round(p.y-size/2.0f), (int)size, (int)size);
}

void DebugDraw::DrawString(int x, int y, const char *string, ...)
{
	char buffer[128];

	va_list arg;
	va_start(arg, string);
	vsprintf(buffer, string, arg);
	va_end(arg);

	TextSetxy(text_handle, x, y);
	TextSetText(text_handle, buffer);
}

void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
{
	DrawSetColor(draw_handle, ((int)(c.r*255.0) << 16) + ((int)(c.g*255.0) << 8) + (int)(c.b*255.0));
	DrawMoveTo(draw_handle, Round(aabb->lowerBound.x*pixels_per_meter), Round(aabb->lowerBound.y*pixels_per_meter));
	DrawLineTo(draw_handle, Round(aabb->upperBound.x*pixels_per_meter), Round(aabb->lowerBound.y*pixels_per_meter));
	DrawLineTo(draw_handle, Round(aabb->upperBound.x*pixels_per_meter), Round(aabb->upperBound.y*pixels_per_meter));
	DrawLineTo(draw_handle, Round(aabb->lowerBound.x*pixels_per_meter), Round(aabb->upperBound.y*pixels_per_meter));
	DrawLineTo(draw_handle, Round(aabb->lowerBound.x*pixels_per_meter), Round(aabb->lowerBound.y*pixels_per_meter));
}
