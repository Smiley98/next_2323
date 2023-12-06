//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "Physics.h"
#include "Graphics.h"

// TODO -- turn this into brick break with students?
// TODO -- make an ECS? Physics is a solved problems... Now we need a video game!!!
PhysicsWorld world;
//Particle player;

Particle CreateWall(vec2 position, vec2 normal)
{
	Particle plane;
	plane.collider.shape = PLANE;
	plane.collider.normal = normal;
	plane.collider.dynamic = false;

	plane.pos = position;
	plane.gravityScale = 0.0f;
	plane.invMass = 0.0f;
	plane.friction = 1.0f;
	plane.restitution = 1.0f;

	return plane;
}

void Init()
{
	Particle circle1;
	circle1.collider.shape = CIRCLE;
	circle1.collider.radius = 0.5f;
	circle1.collider.dynamic = true;
	
	circle1.pos = { 5.0f, 5.0f };
	circle1.vel = { -5.0f, 0.0f };
	circle1.friction = 0.0f;
	circle1.restitution = 1.0f;

	Particle circle2;
	circle2.collider.shape = CIRCLE;
	circle2.collider.radius = 0.5f;
	circle2.collider.dynamic = true;

	circle2.pos = { -5.0f, -5.0f };
	circle2.vel = {  5.0f, 0.0f };
	circle2.friction = 0.0f;
	circle2.restitution = 1.0f;

	world.particles.push_back(circle1);
	world.particles.push_back(circle2);

	world.particles.push_back(CreateWall({ 0.0f, 10.0f }, { 0.0f, -1.0f }));	// top
	world.particles.push_back(CreateWall({ 0.0f, -10.0f }, { 0.0f, 1.0f }));	// bottom
	world.particles.push_back(CreateWall({ -10.0f, 0.0f }, { 1.0f, 0.0f }));	// left
	world.particles.push_back(CreateWall({ 10.0f, 0.0f }, { -1.0f, 0.0f }));	// right

	glMatrixMode(GL_PROJECTION);
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);

	Vector3 eye{ 0.0f, 0.0f, 0.5f };
	Vector3 target{ 0.0f, 0.0f, 0.0f };
	Vector3 up{ 0.0f, 1.0f, 0.0f };
	Matrix view = Transpose(LookAt(eye, target, up));

	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf((float*)&view);
}

void Update(float dt)
{
	dt /= 1000.0f;
	world.Update(dt);
}

void Render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	world.Render();
	DrawRect({ 0.0f, 0.0f }, 19.0f, 1.0f, { 1.0f, 0.0f, 0.0f }, true);
}

void Shutdown()
{
	world.particles.resize(0);
}
