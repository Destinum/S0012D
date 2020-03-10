#pragma once
#include "exampleapp.h"

#include "Message.h"
#include <vector>
#include <iostream>
#include "util/stringatom.h"
//#include "core/refcounted.h"
//#include "math/vector.h"
//#include "math/point.h"
//#include "exampleapp.h"

//using namespace std;

class GameEntity;

class BaseComponent : public Core::RefCounted
{
	__DeclareClass(BaseComponent);

public:

	BaseComponent();
	~BaseComponent();
	virtual void Init();
	virtual void Update();
	virtual void OnLoad();

	virtual void Send(Message);

protected:
	friend class EntityManager;
	GameEntity* Parent;
};