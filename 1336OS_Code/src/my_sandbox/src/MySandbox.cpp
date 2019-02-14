#include "my_sandbox/include/MySandBox.h"
#include "demo_framework/include/LuaScriptUtilities.h"

MySandBox::MySandBox(void) : SandboxApplication("My Sandbox")
{
}

MySandBox::~MySandBox(void)
{
}

void MySandBox::Initialize()
{
	SandboxApplication::Initialize();
	AddResourceLocation("../../../src/my_sandbox/script");

	CreateSandbox("Sandbox.lua");
}

void MySandBox::Update()
{  
	SandboxApplication::Update();
}
