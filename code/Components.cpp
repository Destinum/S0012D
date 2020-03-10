#include "foundation/stdneb.h"
#include "Components.h"

#include "models/modelcontext.h"
#include "visibility/visibilitycontext.h"
#include "characters/charactercontext.h"

__ImplementClass(BaseComponent, 'BCmp', Core::RefCounted);
__ImplementClass(TransformComponent, 'TCmp', BaseComponent);
__ImplementClass(GraphicsComponent, 'GCmp', BaseComponent);

BaseComponent::BaseComponent(){}
BaseComponent::~BaseComponent(){}
void BaseComponent::Update(){}
void BaseComponent::Init(){}
void BaseComponent::OnLoad(){}
void BaseComponent::Send(Message ThisMessage) {}


void TransformComponent::Init()
{
	Math::matrix44 Test;
	//Test.setrow0(Math::float4(23,12,5,7));
	Test = Test.translation(Math::point(5, 0, 0));
	Parent->RegisterVariable("Transform", GameEntity::VariableType(Test));


	//Parent->RegisterVariable("Transform", GameEntity::VariableType(Math::matrix44()));
}

void TransformComponent::Update()
{

}

void TransformComponent::Send(Message ThisMessage)
{
	if (ThisMessage.TheMessage == "Move")
	{
		Math::float4 NewCoordinates = Parent->Dictionary["Transform"].Matrix->getrow3() + Math::float4(0, 0.01, 0, 0);
		GameEntity::VariableType NewTranslation(Math::matrix44::translation(NewCoordinates));
		Parent->SetVariable("Transform", NewTranslation);
		//Parent->Dictionary["Transform"].Matrix = &(Math::matrix44::translation(NewCoordinates));
	}
}

void GraphicsComponent::Init()
{
	Graphics::GraphicsEntityId animatedEntity = Graphics::CreateEntity();

	
	// The CharacterContext holds skinned, animated entites and takes care of playing animations etc.
	Graphics::RegisterEntity<Models::ModelContext, Visibility::ObservableContext, Characters::CharacterContext>(animatedEntity);
	// create model and move it to the front
	Models::ModelContext::Setup(animatedEntity, "mdl:Units/Unit_Footman.n3", "Examples");
	//Models::ModelContext::SetTransform(animatedEntity, Math::matrix44::translation(Math::point(5, 0, 0)));
	Visibility::ObservableContext::Setup(animatedEntity, Visibility::VisibilityEntityType::Model);
	// Setup the character context instance.
	// nsk3 is the skeleton resource, nax3 is the animation resource. nax3 files can contain multiple animation clips
	Characters::CharacterContext::Setup(animatedEntity, "ske:Units/Unit_Footman.nsk3", "ani:Units/Unit_Footman.nax3", "Examples");
	Characters::CharacterContext::PlayClip(animatedEntity, nullptr, 0, 0, Characters::Append, 1.0f, 1, Math::n_rand() * 100.0f, 0.0f, 0.0f, Math::n_rand() * 100.0f);
	

	Parent->RegisterVariable("GraphicsEntity", GameEntity::VariableType(animatedEntity));
}

void GraphicsComponent::Update()
{
	if (Parent->Dictionary.find("Transform") != Parent->Dictionary.end())
	{
		Models::ModelContext::SetTransform(Parent->GetGraphicsEntity("GraphicsEntity"), Parent->GetMatrix("Transform"));
		//Models::ModelContext::SetTransform(Parent->GetGraphicsEntity("GraphicsEntity"), Math::matrix44::translation(Math::point(5, 0, 0)));
	}
}

void GraphicsComponent::OnLoad()
{
	if (Parent->Dictionary.find("Transform") != Parent->Dictionary.end())
	{
		Models::ModelContext::SetTransform(Parent->GetGraphicsEntity("GraphicsEntity"), Parent->GetMatrix("Transform"));
		//Models::ModelContext::SetTransform(Parent->GetGraphicsEntity("GraphicsEntity"), Math::matrix44::translation(Math::point(5, 0, 0)));
	}
}

void GraphicsComponent::Send(Message ThisMessage)
{

}