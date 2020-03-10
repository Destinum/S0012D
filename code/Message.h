#pragma once
//#include "Components.h"
#include "util/stringatom.h"

class Message
{
public:
	Message(Util::StringAtom);

	Util::StringAtom TheMessage;
};