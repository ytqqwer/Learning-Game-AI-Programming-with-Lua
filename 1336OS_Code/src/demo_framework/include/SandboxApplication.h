/**
 * Copyright (c) 2013 David Young dayoung@goliathdesigns.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *  claim that you wrote the original software. If you use this software
 *  in a product, an acknowledgment in the product documentation would be
 *  appreciated but is not required.
 *
 *  2. Altered source versions must be plainly marked as such, and must not be
 *  misrepresented as being the original software.
 *
 *  3. This notice may not be removed or altered from any source
 *  distribution.
 */

#ifndef DEMO_FRAMEWORK_SANDBOX_APPLICATION_H
#define DEMO_FRAMEWORK_SANDBOX_APPLICATION_H

#include "demo_framework/include/BaseApplication.h"
#include "ogre3d/include/OgreString.h"
#include "ogre3d/include/OgreTimer.h"

class LuaFileManager;
class Sandbox;

class SandboxApplication : public BaseApplication
{
public:
    SandboxApplication(const Ogre::String& applicationTitle);

    virtual ~SandboxApplication();

    void AddResourceLocation(const Ogre::String& location);

    virtual void Cleanup();

    virtual void CreateSandbox(const Ogre::String& sandboxLuaScript);

    virtual void Draw();

    int GenerateSandboxId();

    virtual Sandbox* GetSandbox();

    virtual void HandleKeyPress(const OIS::KeyCode keycode, unsigned int key);

    virtual void HandleKeyRelease(
        const OIS::KeyCode keycode, unsigned int key);

    virtual void HandleMouseMove(const int width, const int height);

    virtual void HandleMousePress(
        const int width, const int height, const OIS::MouseButtonID button);

    virtual void HandleMouseRelease(
        const int width, const int height, const OIS::MouseButtonID button);

    virtual void Initialize();

    virtual void Update();

private:
    long long lastUpdateTimeInMicro_;
    long long lastUpdateCallTime_;

    LuaFileManager* luaFileManager_;

    Sandbox* sandbox_;
    Ogre::Timer timer_;

    int lastSandboxId_;

    SandboxApplication(const SandboxApplication&);
    SandboxApplication& operator=(const SandboxApplication&);
};

#endif  // DEMO_FRAMEWORK_SANDBOX_APPLICATION_H
