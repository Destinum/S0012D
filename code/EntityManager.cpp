#include "foundation/stdneb.h"
#include "EntityManager.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
	for (int i = 0; i < Entities.size(); i++)
	{
		Entities[i]->~GameEntity();
		//delete Entities[i];
	}
}

void EntityManager::Update()
{
	for (int i = 0; i < Entities.size(); i++)
	{
		Entities[i]->Update();
	}
}

/*void EntityManager::AddEntity(GameEntity NewEntity)
{
	Entities.push_back(NewEntity);
}*/


void EntityManager::AddEntity()
{
	//GameEntity* NewEntity = new GameEntity;
	//GameEntity NewEntity;
	//NewEntity.OnLoad();'
	Ptr<GameEntity> NewEntity = GameEntity::Create();
	Entities.push_back(NewEntity);
}

void EntityManager::AddComponent(int EntityIndex, BaseComponent* NewComponent)
{
	NewComponent->Parent = this->Entities[EntityIndex];
	NewComponent->Init();
	this->Entities[EntityIndex]->Components.push_back(NewComponent);
}