/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "base/CCEventListenerDeviceMotion.h"
#include "base/CCEventDeviceMotion.h"
#include "base/CCConsole.h"

NS_CC_BEGIN

const std::string EventListenerDeviceMotion::LISTENER_ID =
  "__cc_magnetic_field";

EventListenerDeviceMotion::EventListenerDeviceMotion()
{

}

EventListenerDeviceMotion::~EventListenerDeviceMotion()
{
    CCLOGINFO("In the destructor of DeviceMotionEventListener. %p", this);
}

EventListenerDeviceMotion* EventListenerDeviceMotion::create(
  const std::function<void(DeviceMotion*, Event*)>& callback)
{
    EventListenerDeviceMotion* ret =
      new (std::nothrow) EventListenerDeviceMotion();
    if (ret && ret->init(callback))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool EventListenerDeviceMotion::init(
  const std::function<void(DeviceMotion*, Event* event)>& callback)
{
    auto listener = [this](Event* event){
        auto motEvent = static_cast<EventDeviceMotion*>(event);
        this->onDeviceMotionEvent(&motEvent->_mot, event);
    };

    if (EventListener::init(Type::DEVICE_MOTION, LISTENER_ID, listener))
    {
        onDeviceMotionEvent = callback;
        return true;
    }

    return false;
}

EventListenerDeviceMotion* EventListenerDeviceMotion::clone()
{
    auto ret = new (std::nothrow) EventListenerDeviceMotion();

    if (ret && ret->init(onDeviceMotionEvent))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

bool EventListenerDeviceMotion::checkAvailable()
{
    CCASSERT(onDeviceMotionEvent, "onDeviceMotionEvent can't be nullptr!");

    return true;
}

NS_CC_END
