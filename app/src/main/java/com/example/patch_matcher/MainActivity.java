package com.example.patch_matcher;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.TextView;

import com.example.patch_matcher.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'patch_matcher' library on application startup.
    static {
        System.loadLibrary("patch_matcher");
    }

    private ActivityMainBinding binding;
    private Button play_button, stop_button, change_button, feedback_button, connect_button;
    private Operator operator1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        play_button = (Button) findViewById(R.id.play_button);
        play_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) { onPlayButtonPress(); }
        });

        stop_button = (Button) findViewById(R.id.stop_button);
        stop_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) { onStopButtonPress(); }
        });

        change_button = (Button) findViewById(R.id.change_button);
        change_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) { onChangeButtonPress(); }
        });

        ImageView Operator1_feedbackArrow = findViewById(R.id.Operator1_feedbackArrow);
        Operator1_feedbackArrow.setVisibility(View.INVISIBLE);
        feedback_button = (Button) findViewById(R.id.FeedbackButton);
        feedback_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (onFeedbackButtonPress()) {
                    Operator1_feedbackArrow.setVisibility(View.VISIBLE);
                    feedback_button.setText("Disable Feedback");
                }
                else {
                    Operator1_feedbackArrow.setVisibility(View.INVISIBLE);
                    feedback_button.setText("Enable Feedback");
                }
            }


        });

        ImageView Operator21_arrow = findViewById(R.id.Operator21_arrow);
        Operator21_arrow.setVisibility(View.INVISIBLE);
        connect_button = (Button) findViewById(R.id.connectButton);
        connect_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (onConnectButtonPress()) {
                    Operator21_arrow.setVisibility(View.VISIBLE);
                    connect_button.setText("Disconnect");
                }
                else {
                    Operator21_arrow.setVisibility(View.INVISIBLE);
                    connect_button.setText("Connect");
                }
            }
        });

       operator1 = (Operator) findViewById(R.id.operator1);


    }

    /**
     * A native method that is implemented by the 'patch_matcher' native library,
     * which is packaged with this application.
     */
    public native void onPlayButtonPress();
    public native void onStopButtonPress();
    public native void onChangeButtonPress();
    public native boolean onFeedbackButtonPress();
    public native boolean onConnectButtonPress();
}