#include <jni.h>
#include <string>
#include <sstream>

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
    jmethodID j_method_id2 = env->GetStaticMethodID(j_class, "getStringFromJavaWithStatic", "(Ljava/lang/String;)Ljava/lang/String;");

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
