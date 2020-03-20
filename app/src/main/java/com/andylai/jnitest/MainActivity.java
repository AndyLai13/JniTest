package com.andylai.jnitest;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    Util util;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Bitmap originalBmp = BitmapFactory.decodeResource(getResources(), R.drawable.w3c_home);

        ImageView imageView = findViewById(R.id.image_view);
        imageView.setImageBitmap(originalBmp);

//        tv.setText(nativeCallJavaBaseMsg());
        util = new Util(getApplicationContext());
//        util.nativeCallAndroidToast();

        Bitmap flipHoriBmp = util.flipHorizontalBitmapFromJNI(originalBmp);
        Bitmap flipVertBmp = util.flipVerticalBitmapFromJNI(originalBmp);
//
        findViewById(R.id.original).setOnClickListener(v -> imageView.setImageBitmap(originalBmp));
        findViewById(R.id.flip_hori).setOnClickListener(v -> imageView.setImageBitmap(flipHoriBmp));
        findViewById(R.id.flip_vert).setOnClickListener(v -> imageView.setImageBitmap(flipVertBmp));
    }
}
