LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/ButtonScene.cpp \
                   ../../Classes/CircleSprite.cpp \
                   ../../Classes/EndScene.cpp \
                   ../../Classes/Enemies.cpp \
                   ../../Classes/Enemy.cpp \
                   ../../Classes/GameData.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/LoseScene.cpp \
                   ../../Classes/MenuScene.cpp \
                   ../../Classes/PauseScene.cpp \
                   ../../Classes/Plankton.cpp \
                   ../../Classes/Planktons.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/ScoreScene.cpp \
                   ../../Classes/Utils.cpp \
                   ../../Classes/WinScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
