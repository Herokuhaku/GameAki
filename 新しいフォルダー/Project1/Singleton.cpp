#include "Singleton.h"
#include <DxLib.h>

void Singleton::OutputLife()
{
	char str[32];
	sprintf_s(str,32,"life=%d\n",life_);
	++life_;
}

Singleton::Singleton()
{
	life_ = 0;
}

Singleton::~Singleton()
{
}
