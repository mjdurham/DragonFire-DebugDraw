#include "DragonFireSDK.h"
#include <Box2D\Box2D.h>
#include <time.h>

#include "Render.h"
#include "Bodies.h"


b2Vec2 gravity(0.0f, 9.8f);
b2World* m_world = new b2World(gravity);

int positionIterations = 6;
int velocityIterations = 2;
float timeStep = (1.0f/30.0f);

int Draw;
int DebugText;
DebugDraw m_debugDraw;

Bodies* bodies[100];

int OnTouchArea(int id, int event, int x, int y)
{

	// add a new body to the world when the screen is touched
	if (event == 1)
	{
		for (int i=0; i<100; i++)
		{
			if (bodies[i] == NULL)
			{
				bodies[i] = new Bodies(m_world, x, y);
				break;
			}
		}
	}

	return 0;
}
void AppMain()
{
	RandomSetSeed((int)time(0));
	LandscapeMode();
	TouchAdd(0, 0, 480, 320, OnTouchArea, 0);

	// create draw and text handles to pass to the new DebugDraw instance
	Draw = DrawAdd(0, 0, 480, 320);
	int font = FontAdd("Helvetica", "Regular", 12, 0xFFFFFF);
	DebugText = TextAdd(0, 0, "", font);
	m_debugDraw.Setup(Draw, DebugText, 30);

	// setup DebugDraw
	m_world->SetDebugDraw(&m_debugDraw);
	m_debugDraw.SetFlags(b2Draw::e_shapeBit + b2Draw::e_jointBit);

	// create ground floor
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(240.0f/30.0f, 310.0f/30.0f+5.0f);
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(10.0f, 5.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

}

void AppExit()
{
	delete m_world;
}

void OnTimer()
{

	m_world->Step(timeStep, velocityIterations, positionIterations);
	m_world->ClearForces();

	DrawClear(Draw);
	m_world->DrawDebugData();

	m_debugDraw.DrawString(0, 0, "Body Count %i", m_world->GetBodyCount());

	// remove any object that is off screen
	for (int i=0; i<100; i++)
	{
		if (bodies[i] != NULL)
		{
			if (bodies[i]->CheckDelete())
			{
				delete bodies[i];
				bodies[i] = NULL;
			}
		}
	}

}
