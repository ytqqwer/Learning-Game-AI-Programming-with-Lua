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

#ifndef DEMO_FRAMEWORK_BASE_APPLICATION_H
#define DEMO_FRAMEWORK_BASE_APPLICATION_H

#include "ogre3d/include/OgreFrameListener.h"
#include "ogre3d/include/OgreString.h"
#include "ogre3d/include/OgreWindowEventUtilities.h"
#include "ois/include/OISKeyboard.h"
#include "ois/include/OISMouse.h"

class DebugDrawer;
class ObfuscatedZipFactory;

namespace Ogre
{
    class Camera;
    class RenderWindow;
    class Root;
    class SceneManager;
}

namespace OgreBites
{
    class SdkCameraMan;
}

namespace OIS
{
    class InputManager;
}

#define APPLICATION_LOG_DEBUG           "Sandbox_d.log"
#define APPLICATION_LOG_RELEASE         "Sandbox.log"
#define APPLICATION_CONFIG_DEBUG        "Sandbox_d.cfg"
#define APPLICATION_CONFIG_RELEASE      "Sandbox.cfg"
#define APPLICATION_RESOURCES_DEBUG     "SandboxResources_d.cfg"
#define APPLICATION_RESOURCES_RELEASE   "SandboxResources.cfg"

class BaseApplication :
    public Ogre::FrameListener,
    public Ogre::WindowEventListener,
    public OIS::KeyListener,
    public OIS::MouseListener
{
public:
    BaseApplication(const Ogre::String& applicationTitle = "");

    virtual ~BaseApplication();

    virtual void Cleanup();

    virtual void Draw();

    Ogre::Camera* GetCamera();

    Ogre::SceneManager* GetSceneManager();

    Ogre::RenderWindow* GetRenderWindow();

    virtual void HandleKeyPress(const OIS::KeyCode keycode, unsigned int key);

    virtual void HandleKeyRelease(
        const OIS::KeyCode keycode, unsigned int key);

    virtual void HandleMouseMove(const int width, const int height);

    virtual void HandleMousePress(
        const int width, const int height, const OIS::MouseButtonID button);

    virtual void HandleMouseRelease(
        const int width, const int height, const OIS::MouseButtonID button);

    virtual void Initialize();

    void Run();

    void SetShutdown(const bool shutdown);

    virtual void Update();

private:
    DebugDrawer* debugDrawer_;
    ObfuscatedZipFactory* obfuscatedZipFactory_;

    Ogre::String applicationTitle_;
    Ogre::Root* root_;
    Ogre::Camera* camera_;
    Ogre::SceneManager* sceneManager_;
    Ogre::RenderWindow* renderWindow_;
    Ogre::String resourceConfig_;
    bool shutdown_;

    void ChooseSceneManager();
    bool Configure();
    void CreateCamera();
    void CreateFrameListener();
    void CreateResourceListener();
    void CreateViewports();
    void LoadResources();
    bool Setup();
    void SetupResources();

    // Ogre::FrameListener
    virtual bool frameEnded(const Ogre::FrameEvent& event);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& event);
    virtual bool frameStarted(const Ogre::FrameEvent& event);

    // OIS::KeyListener
    virtual bool keyPressed(const OIS::KeyEvent &event);
    virtual bool keyReleased(const OIS::KeyEvent &event);

    // OIS::MouseListener
    virtual bool mouseMoved(const OIS::MouseEvent &event);
    virtual bool mousePressed(
        const OIS::MouseEvent &event, OIS::MouseButtonID id);
    virtual bool mouseReleased(
        const OIS::MouseEvent &event, OIS::MouseButtonID id);

    // Ogre::WindowEventListener
    virtual void windowResized(Ogre::RenderWindow* renderWindow);
    virtual void windowClosed(Ogre::RenderWindow* renderWindow);

    // OgreBites
    OgreBites::SdkCameraMan* cameraMan_;       // basic camera controller

    //OIS Input devices
    OIS::InputManager* inputManager_;
    OIS::Mouse* mouse_;
    OIS::Keyboard* keyboard_;
};  // class BaseApplication

#endif  // DEMO_FRAMEWORK_BASE_APPLICATION_H
