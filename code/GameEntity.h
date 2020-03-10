#pragma once
#include "BaseComponent.h"
//#include "Components.h"
//#include <vector>
#include <map>
//#include <iostream>
//#include "exampleapp.h"

class GameEntity : public Core::RefCounted
{
	__DeclareClass(GameEntity);

public:

	//struct UnionStruct
	struct VariableType
	{
		enum DATA_TYPE { INTEGER, FLOAT, MATRIX44, STRINGATOM, GRAPHICSID };
		DATA_TYPE Data_Type;

		union
		{
			int Integer;
			float Float;
			//Math::float4 Float4;
			Math::matrix44* Matrix;
			Util::StringAtom* StringAtom;
			Graphics::GraphicsEntityId GraphicsID;
		};

		VariableType();
		VariableType(int i);
		VariableType(float f);
		VariableType(Math::matrix44 m);
		VariableType(Util::StringAtom sa);
		VariableType(Graphics::GraphicsEntityId ID);
		
		VariableType(const VariableType& rhs);

		~VariableType();
		void Delete();
		void Copy(const VariableType& VT);

		void operator=(const VariableType& VT);
		//void operator=(const VariableType VT);


		//void operator=(const Math::matrix44& m);
	};

	GameEntity();
	~GameEntity();
	void Update();

	std::vector<BaseComponent*> Components;
	std::map<Util::StringAtom, VariableType> Dictionary;

	void Send(Message);
	void OnLoad();
	//void AddComponent(BaseComponent*);
	//void AddComponent(BaseComponent* New);
	void RegisterVariable(Util::StringAtom, VariableType);

	//VariableType GetVariable(Util::StringAtom);
	Math::matrix44 GetMatrix(Util::StringAtom);
	Graphics::GraphicsEntityId GetGraphicsEntity(Util::StringAtom);

	void SetVariable(Util::StringAtom, VariableType);
};