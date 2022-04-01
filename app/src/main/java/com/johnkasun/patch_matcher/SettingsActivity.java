package com.johnkasun.patch_matcher;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.Window;

public class SettingsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        this.setFinishOnTouchOutside(false);
    }

    public void onMenuButtonPressed(View view)
    {
        Intent intent = new Intent(this, MenuActivity.class);
        startActivity(intent);
        finish();
    }

    public void onRegenerateButtonPressed(View view)
    {

    }

    public void onShowValuesButtonPressed(View view)
    {

    }
}