#include "JniHelper.h"
#include <jni.h>
#include <android/sensor.h>
#include "base/CCDirector.h"
#include "base/CCEvent.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventDeviceMotion.h"
#include "base/ccTypes.h"

using namespace cocos2d;

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxMotionSensor_onSensorChanged(JNIEnv*  env, jobject thiz, jint sensorType, jfloatArray sensorValues, jlong timeStamp) {
        jsize len = env->GetArrayLength(sensorValues);
        jfloat *values = env->GetFloatArrayElements(sensorValues, 0);
        DeviceMotion motion;
        motion.values.insert(motion.values.end(), &values[0], &values[len]);
        motion.sensorType = static_cast<SensorType>(sensorType);
        motion.timestamp = (double)timeStamp;

        //EventDeviceMotion event((Event::Type)sensorType, motion);
        EventDeviceMotion event(motion);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
        env->ReleaseFloatArrayElements(sensorValues, values, 0);
    }
}

//ASENSOR_TYPE_ACCELEROMETER
