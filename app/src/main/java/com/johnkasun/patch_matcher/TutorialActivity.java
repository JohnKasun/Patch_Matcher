package com.johnkasun.patch_matcher;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;

import android.annotation.SuppressLint;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;


import java.util.ArrayList;

public class TutorialActivity extends GameActivity
{

    TextView infoTitle, infoBody;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tutorial);

        init();

        infoTitle = findViewById(R.id.infoTitle);
        infoBody = findViewById(R.id.infoBody);

        infoTitle.setText("Welcome!");
        infoBody.setText("Double tap in the middle of the screen to begin the tutorial...");
    }


}