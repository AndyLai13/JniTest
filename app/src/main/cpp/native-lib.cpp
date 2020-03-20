#include <jni.h>
#include <string>
#include <sstream>
#include <android/bitmap.h>


jobject createBitmap(JNIEnv *env, uint32_t width, uint32_t height);

extern "C" JNIEXPORT jstring JNICALL
Java_com_andylai_jnitest_Util_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_andylai_jnitest_Util_getIntFromNative(JNIEnv *env, jobject thiz, jint j_int) {
    int result = 50;
    result += j_int;
    return result;
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_andylai_jnitest_Util_getDoubleFromNative(JNIEnv *env, jobject thiz,
                                                  jdouble j_double) {
    double result = 50.0;
    result += j_double;
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_andylai_jnitest_Util_getStringFromNative(JNIEnv *env, jobject thiz,
                                                  jstring java_string) {
    const char *java_str_char = env->GetStringUTFChars(java_string, NULL);
    if (java_str_char == NULL) {
        return NULL;
    }
    char const *native_char = "->Native:";
    char const *split_char = "->call";
    std::string const &temp =
            std::string(java_str_char) + std::string(split_char) + std::string(native_char);
    char const *result = temp.c_str();
    env->ReleaseStringUTFChars(java_string, java_str_char); // release
    return env->NewStringUTF(result);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_andylai_jnitest_Util_nativeCallAndroidToast(JNIEnv *env, jobject thiz) {
    jclass j_class = env->FindClass("com/andylai/jnitest/Util");
    jobject j_object = env->AllocObject(j_class);

    jmethodID j_method_id1 = env->GetMethodID(j_class, "showToast", "(Ljava/lang/String;)V");
    jmethodID j_method_id2 = env->GetStaticMethodID(j_class, "getStringFromJavaWithStatic",
                                                    "(Ljava/lang/String;)Ljava/lang/String;");

    jstring j_string1 = (jstring) env->NewStringUTF("c++ string");
    jstring j_string2 = (jstring) env->CallStaticObjectMethod(j_class, j_method_id2, j_string1);

    env->CallVoidMethod(j_object, j_method_id1, j_string2);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_andylai_jnitest_Util_getArrayListFromNative(JNIEnv *env, jobject thiz,
                                                     jobject java_list) {
    // TODO: implement getArrayListFromNative()
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_andylai_jnitest_Util_nativeCallJavaBaseMsg(JNIEnv *env, jobject thiz) {
    jclass j_class = env->FindClass("com/andylai/jnitest/Util");
    jobject j_object = env->AllocObject(j_class);

    jmethodID j_method_id1 = env->GetMethodID(j_class, "getStringFromJava",
                                              "(Ljava/lang/String;)Ljava/lang/String;");
    jmethodID j_method_id2 = env->GetMethodID(j_class, "getDoubleFromJava", "(D)D");
    jmethodID j_method_id3 = env->GetMethodID(j_class, "getIntFromJava", "(I)I");
    //string
    jstring j_str1 = (jstring) env->NewStringUTF("Native");
    jstring j_str2 = (jstring) env->CallObjectMethod(j_object, j_method_id1, j_str1);
    // double
    jdouble j_double = (jdouble) env->CallDoubleMethod(j_object, j_method_id2, 66.66);
    // int
    jint j_int = (jint) env->CallIntMethod(j_object, j_method_id3, 66);

    std::string j_double_str = std::to_string(j_double);
    std::string j_int_str = std::to_string(j_int);
    std::string tip_int = " int: ";
    std::string tip_double = " double: ";

    const char *result_string_char = env->GetStringUTFChars(j_str2, NULL);//获取java字符串
    std::string result_number_str = tip_int + j_int_str + tip_double + j_double_str;//拼接数字
    std::string result_str = std::string(result_string_char) + result_number_str;//拼接数字和字符串
    const char *result_char = result_str.c_str();//字符串转换为char
    env->ReleaseStringUTFChars(j_str2, result_string_char);//释放
    return env->NewStringUTF(result_char);
}


int flipHori(uint32_t newHeight, uint32_t newWidth, void *bitmapPixels, uint32_t *newBitmapPixels) {
    int whereToGet = 0;
    for (int y = 0; y < newHeight; ++y) {
        for (int x = newWidth - 1; x >= 0; x--) {
            uint32_t pixel = ((uint32_t *) bitmapPixels)[whereToGet++];
            newBitmapPixels[newWidth * y + x] = pixel;
        }
    }
    return 0;
}

int flipVert() {}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_andylai_jnitest_Util_flipHorizontalBitmapFromJNI(JNIEnv *env, jobject thiz,
                                                          jobject bitmap) {
    AndroidBitmapInfo bitmapInfo;
    int ret = NULL;
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &bitmapInfo)) < 0) {
        return NULL;
    }
    void *bitmapPixels;
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &bitmapPixels)) < 0) {
        return NULL;
    }

    uint32_t newWidth = bitmapInfo.width;
    uint32_t newHeight = bitmapInfo.height;
    uint32_t *newBitmapPixels = new uint32_t[newWidth * newHeight];
    int whereToGet = 0;
    for (int y = 0; y < newHeight; ++y) {
        for (int x = newWidth - 1; x >= 0; x--) {
            uint32_t pixel = ((uint32_t *) bitmapPixels)[whereToGet++];
            newBitmapPixels[newWidth * y + x] = pixel;
        }
    }

    jobject newBitmap = createBitmap(env, newWidth, newHeight);
    void *resultBitmapPixels;
    if ((ret = AndroidBitmap_lockPixels(env, newBitmap, &resultBitmapPixels)) < 0) {
        return NULL;
    }
    int pixelsCount = newWidth * newHeight;
    memcpy((uint32_t *) resultBitmapPixels, newBitmapPixels, sizeof(uint32_t) * pixelsCount);

    AndroidBitmap_unlockPixels(env, bitmap);
    AndroidBitmap_unlockPixels(env, newBitmap);

    return newBitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_andylai_jnitest_Util_flipVerticalBitmapFromJNI(JNIEnv *env, jobject thiz, jobject bitmap) {
    AndroidBitmapInfo bitmapInfo;
    int ret = NULL;
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &bitmapInfo)) < 0) {
        return NULL;
    }
    void *bitmapPixels;
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &bitmapPixels)) < 0) {
        return NULL;
    }

    uint32_t newWidth = bitmapInfo.width;
    uint32_t newHeight = bitmapInfo.height;
    uint32_t *newBitmapPixels = new uint32_t[newWidth * newHeight];
    int whereToGet = 0;
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; x++) {
            uint32_t pixel = ((uint32_t *) bitmapPixels)[whereToGet++];
            newBitmapPixels[newWidth * (newHeight - 1 - y) + x] = pixel;
        }
    }

    jobject newBitmap = createBitmap(env, newWidth, newHeight);
    void *resultBitmapPixels;
    if ((ret = AndroidBitmap_lockPixels(env, newBitmap, &resultBitmapPixels)) < 0) {
        return NULL;
    }
    int pixelsCount = newWidth * newHeight;
    memcpy((uint32_t *) resultBitmapPixels, newBitmapPixels, sizeof(uint32_t) * pixelsCount);

    AndroidBitmap_unlockPixels(env, bitmap);
    AndroidBitmap_unlockPixels(env, newBitmap);

    return newBitmap;
}

jobject createBitmap(JNIEnv *env, uint32_t width, uint32_t height) {
    jclass bitmapCls = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmapFunc = env->GetStaticMethodID(bitmapCls,
                                                        "createBitmap",
                                                        "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jstring configName = env->NewStringUTF("ARGB_8888");
    jclass bitmapConfigClass = env->FindClass("android/graphics/Bitmap$Config");
    jmethodID valueOfBitmapConfigFunction = env->GetStaticMethodID(
            bitmapConfigClass, "valueOf",
            "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;");

    jobject bitmapConfig = env->CallStaticObjectMethod(bitmapConfigClass,
                                                       valueOfBitmapConfigFunction,
                                                       configName);

    jobject newBitmap = env->CallStaticObjectMethod(bitmapCls, createBitmapFunc,
                                                    width, height, bitmapConfig);
    return newBitmap;
}
