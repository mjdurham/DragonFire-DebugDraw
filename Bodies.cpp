#include "Bodies.h"

#include "DragonFireSDK.h"


Bodies::Bodies(b2World* world, int x, int y)
{

	bd.position.Set(x/30.0f, y/30.0f);
	bd.type = b2_dynamicBody;

	int num = Random(3);

	if (num == 0)
	{
		b2CircleShape circle;
		circle.m_radius = Random(30)/30.0f+.3f;
		body = world->CreateBody(&bd);
		body->CreateFixture(&circle, 2.0);
	}
	else if (num == 1)
	{
		b2PolygonShape box;
		box.SetAsBox(Random(30)/30.0f+.3f, Random(30)/30.0f+.3f);
		body = world->CreateBody(&bd);
		body->CreateFixture(&box, 2.0);
	}
	else
	{
		b2PolygonShape triangle;
		b2Vec2 vertices[3];
		vertices[0].Set(0.0f, 1.0f);
		vertices[1].Set(-1.0f, -1.0f);
		vertices[2].Set(Random(30)/30.0f+.3f, -Random(30)/30.0f+.3f);
		triangle.Set(vertices, 3);
		body = world->CreateBody(&bd);
		body->CreateFixture(&triangle, 2.0);
	}
}


Bodies::~Bodies()
{
	body->GetWorld()->DestroyBody(body);
}

bool Bodies::CheckDelete()
{
	return (body->GetPosition().y*30.0 > 480);
}
