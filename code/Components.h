#pragma once
//#include "BaseComponent.h"
#include "GameEntity.h"

class TransformComponent : public BaseComponent
{
	__DeclareClass(TransformComponent);

public:
	TransformComponent()
	{

	}

	void Init();
	void Update();
	//void OnLoad();
	void Send(Message);
};

class GraphicsComponent : public BaseComponent
{
	__DeclareClass(GraphicsComponent);

public:
	GraphicsComponent()
	{

	}

	void Init();
	void Update();
	void OnLoad();
	void Send(Message);
};