#include "foundation/stdneb.h"
#include "util/stringatom.h"
#include "Components.h"

__ImplementClass(GameEntity, 'GEnt', Core::RefCounted);

GameEntity::GameEntity()
{

}

GameEntity::~GameEntity()
{
	for (int i = 0; i < Components.size(); i++)
	{
		//Components[i]->~BaseComponent();
		delete Components[i];
	}
}


void GameEntity::Update()
{
	for (int i = 0; i < Components.size(); i++)
	{
		Components[i]->Update();
	}
}

void GameEntity::Send(Message TheMessage)
{
	for (int i = 0; i < Components.size(); i++)
	{
		Components[i]->Send(TheMessage);
	}
}

void GameEntity::OnLoad()
{
	for (int i = 0; i < Components.size(); i++)
	{
		Components[i]->OnLoad();
	}
}

/*void GameEntity::AddComponent(BaseComponent* New)
{
	//TransformComponent* Saken = new TransformComponent(this);
	
	Components.push_back(New);
}*/

void GameEntity::RegisterVariable(Util::StringAtom NewVariable, VariableType Value)
{
	if (Dictionary.find(NewVariable) == Dictionary.end())
	{
		Dictionary[NewVariable] = Value;
	}
}

/*
GameEntity::VariableType GameEntity::GetVariable(Util::StringAtom VariableKey)
{
	if (Dictionary.find(VariableKey) != Dictionary.end())
	{
		return Dictionary[VariableKey];
	}
	return {int(NULL)};
}
*/

Math::matrix44 GameEntity::GetMatrix(Util::StringAtom VariableKey)
{
	if (this->Dictionary.find(VariableKey) != this->Dictionary.end())
	{
		return *this->Dictionary[VariableKey].Matrix;
	}

	return Math::matrix44();
}

Graphics::GraphicsEntityId GameEntity::GetGraphicsEntity(Util::StringAtom VariableKey)
{
	if (this->Dictionary.find(VariableKey) != this->Dictionary.end())
	{
		return this->Dictionary[VariableKey].GraphicsID;
	}

	return Graphics::GraphicsEntityId();
}

void GameEntity::SetVariable(Util::StringAtom VariableKey, VariableType NewVariable)
{
	if (this->Dictionary.find(VariableKey) != this->Dictionary.end())
	{
		if (NewVariable.Data_Type == this->Dictionary[VariableKey].Data_Type)
		{
			this->Dictionary[VariableKey] = NewVariable;
		}
	}
}


GameEntity::VariableType::VariableType()
{
	//Empty
}

GameEntity::VariableType::VariableType(int i)
{
	this->Data_Type = INTEGER;
	this->Integer = i;
}

GameEntity::VariableType::VariableType(float f)
{
	this->Data_Type = FLOAT;
	this->Float = f;
}

GameEntity::VariableType::VariableType(Math::matrix44 m)
{
	this->Data_Type = MATRIX44;
	this->Matrix = n_new(Math::matrix44(m));
	//this->Matrix = n_new(Math::matrix44);
	//this->Matrix = &m;
}

GameEntity::VariableType::VariableType(Util::StringAtom sa)
{
	this->Data_Type = STRINGATOM;
	this->StringAtom = n_new(Util::StringAtom(sa));
}

GameEntity::VariableType::VariableType(Graphics::GraphicsEntityId ID)
{
	this->Data_Type = GRAPHICSID;
	this->GraphicsID = ID;
}

GameEntity::VariableType::VariableType(const VariableType& rhs)
{
	this->Copy(rhs);
}


GameEntity::VariableType::~VariableType()
{
	this->Delete();
}

void GameEntity::VariableType::Delete()
{
	if (this->Data_Type == MATRIX44)
	{
		n_delete(this->Matrix);
		this->Matrix = 0;

	}
	else if (this->Data_Type == STRINGATOM)
	{
		n_assert(this->StringAtom);
		n_delete(this->StringAtom);
		this->StringAtom = 0;
	}
}

void GameEntity::VariableType::Copy(const GameEntity::VariableType& VT)
{
	this->Data_Type = VT.Data_Type;

	//Math::matrix44 Svamp;
	//Util::StringAtom Svampen;

	switch (VT.Data_Type)
	{
		case INTEGER:
			this->Integer = VT.Integer;
			break;

		case FLOAT:
			this->Float = VT.Float;
			break;

		case MATRIX44:
			this->Matrix = n_new(Math::matrix44(*VT.Matrix));
			//Math::matrix44 Svamp;
			//this->Matrix = n_new(Math::matrix44(Svamp));
			break;

		case STRINGATOM:
			this->Matrix = n_new(Math::matrix44(*VT.Matrix));
			//Util::StringAtom Svampen;
			//this->StringAtom = n_new(Util::StringAtom(Svampen));
			break;

		case GRAPHICSID:
			this->GraphicsID = VT.GraphicsID;
			break;
	}
}

/*void GameEntity::VariableType::operator=(const Math::matrix44& m)
{

}*/

void GameEntity::VariableType::operator=(const GameEntity::VariableType& VT)
{
	this->Delete();
	this->Copy(VT);
}