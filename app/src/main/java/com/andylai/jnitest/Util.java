package com.andylai.jnitest;

import android.content.Context;
import android.graphics.Bitmap;
import android.util.Log;
import android.widget.Toast;

import java.util.ArrayList;

public class Util {
    Context mContext;

    Util(Context context) {
        mContext = context;
    }

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    //从native获取int类型数据
    public native int getIntFromNative(int javaInt);

    //从native获取double类型数据
    public native double getDoubleFromNative(double javaDouble);

    //从native获取string类型数据
    public native String getStringFromNative(String javaString);

    public native ArrayList<String> getArrayListFromNative(ArrayList<String> javaList);

    public native void nativeCallAndroidToast();

    public native String nativeCallJavaBaseMsg();

    //native获取int类型数据
    public int getIntFromJava(int nativeInt) {
        int javaInt = 100;
        return javaInt + nativeInt;
    }

    //native获取double类型数据
    public double getDoubleFromJava(double nativeDouble) {
        double javaDouble = 100.0;
        return javaDouble + nativeDouble;
    }

    //native获取string类型数据
    public String getStringFromJava(String nativeString) {
        String javaStr = " Java Static String : ";
        String split = " call ";
        return nativeString + split + javaStr;
    }

    //native获取ArrayList<String>类型数据
    public ArrayList<String> getArrayListFromJava(ArrayList<String> nativeList) {
        return null;
    }

    //native 获取静态方法数据
    public static String getStringFromJavaWithStatic(String nativeString) {
        String javaStr = " java static string  ";
        String split = " && ";
        return javaStr + split + nativeString;
    }

    // 提示信息,提供JNI调用
    public void showToast(String msg) {
        Log.d("Andy","msg = " + msg);
    }

    public native Bitmap flipHorizontalBitmapFromJNI(Bitmap bitmap);
    public native Bitmap flipVerticalBitmapFromJNI(Bitmap bitmap);
//    public native String getBitmapString();


}
