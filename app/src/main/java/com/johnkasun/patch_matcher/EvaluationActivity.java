package com.johnkasun.patch_matcher;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class EvaluationActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_evaluation);

        Intent intent = getIntent();
        float iEvaluationValue = intent.getFloatExtra("Result", -1);
        TextView scoreView = findViewById(R.id.ScoreView);
        scoreView.setText(""+iEvaluationValue);
    }

    public void restartGame(View view)
    {
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }
}