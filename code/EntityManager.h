#pragma once
//#include "GameEntity.h"
#include "Components.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	void Update();

	//void AddEntity(GameEntity);
	void AddEntity();
	//void AddEntity(string);
	void AddComponent(int EntityIndex, BaseComponent* NewComponent);

	std::vector<GameEntity*> Entities;
	//map<string, GameEntity> Entities;
};