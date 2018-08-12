PROJECT_PATH := $(call my-dir)/../..

include $(PROJECT_PATH)/../SDL/android/jni/Android-static.mk
include $(PROJECT_PATH)/../lua/android/jni/Android-static.mk
include $(PROJECT_PATH)/../toluapp/android/jni/Android-static.mk
include $(PROJECT_PATH)/../libpng/android/jni/Android-static.mk

LOCAL_PATH := $(PROJECT_PATH)

include $(CLEAR_VARS)

LOCAL_MODULE := application

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/src/include \
    $(LOCAL_PATH)/src/guichan/include \
    $(LOCAL_PATH)/../SDL/include \
    $(LOCAL_PATH)/../lua/src \
    $(LOCAL_PATH)/../toluapp/include \
    $(LOCAL_PATH)/../libpng \

LOCAL_CFLAGS := \
    -fsigned-char \
    -D_GNU_SOURCE=1 -D_REENTRANT -DUSE_ZLIB \
    -DUSE_GLES \
    -DDYNAMIC_LOAD \
    -DDEBUG \

STRATAGUS_SRCS := \
    android/jni/wrapper.cpp \
    src/action/*.cpp \
    src/ai/*.cpp \
    src/animation/*.cpp \
    src/editor/*.cpp \
    src/game/*.cpp \
    src/guichan/*.cpp \
    src/guichan/sdl/*.cpp \
    src/guichan/widgets/*.cpp \
    src/map/*.cpp \
    src/missile/*.cpp \
    src/network/*.cpp \
    src/particle/*.cpp \
    src/pathfinder/*.cpp \
    src/sound/*.cpp \
    src/spell/*.cpp \
    src/stratagus/*.cpp \
    src/tolua/*.cpp \
    src/ui/*.cpp \
    src/unit/*.cpp \
    src/video/*.cpp \

LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES := $(foreach F, $(STRATAGUS_SRCS), $(addprefix $(dir $(F)),$(notdir $(wildcard $(LOCAL_PATH)/$(F)))))

LOCAL_STATIC_LIBRARIES := sdl lua toluapp png

LOCAL_LDLIBS := -ljnigraphics -lz -ldl -llog -lGLESv1_CM

include $(BUILD_SHARED_LIBRARY)

