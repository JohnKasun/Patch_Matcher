package com.example.patch_matcher;

import androidx.appcompat.app.AppCompatActivity;

import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Switch;
import android.widget.TextView;

import com.example.patch_matcher.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'patch_matcher' library on application startup.
    static {
        System.loadLibrary("patch_matcher");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        Button play_button = (Button) findViewById(R.id.play_button);
        play_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onPlayButtonPress();
            }
        });

        Button stop_button = (Button) findViewById(R.id.stop_button);
        stop_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onStopButtonPress();
            }
        });

        Button change_button = (Button) findViewById(R.id.change_button);
        change_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onChangeButtonPress();
            }
        });

        Button feedback_button = (Button) findViewById(R.id.FeedbackButton);
        feedback_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) { onFeedbackEnable(); }
        });

        Button connect_button = (Button) findViewById(R.id.connectButton);
        connect_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onConnectButtonPress();
            }
        });
       
    }

    /**
     * A native method that is implemented by the 'patch_matcher' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native void onPlayButtonPress();
    public native void onStopButtonPress();
    public native void onChangeButtonPress();
    public native void onFeedbackEnable();
    public native void onConnectButtonPress();
}