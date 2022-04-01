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
        Intent resetGameIntent = new Intent("finish_activity");
        sendBroadcast(resetGameIntent);

        Intent intent = new Intent(this, MenuActivity.class);
        startActivity(intent);
        finish();
    }

    public void onRegenerateButtonPressed(View view)
    {
        Intent regenerateIntent = new Intent("regenerate");
        sendBroadcast(regenerateIntent);
        finish();
    }

    public void onShowValuesButtonPressed(View view)
    {
        Intent showValuesIntent = new Intent("show_values");
        sendBroadcast(showValuesIntent);
        finish();
    }
}