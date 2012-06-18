#ifndef BODIES_H
#define BODIES_H

#include <Box2D\Box2D.h>

class Bodies
{
public:

	Bodies(b2World* world, int x, int y);
	~Bodies();
	bool CheckDelete();

private:

	b2Body* body;
	b2BodyDef bd;

};

#endif
