package com.johnkasun.patch_matcher;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class CampaignActivity extends GameActivity {

    private final int mMaxLevel = 10;
    private int mCurrentLevel = 1;
    private Button mNextLevelButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_campaign);

        init();

        mNextLevelButton = findViewById(R.id.NextLevelButton);

        setLevel(mCurrentLevel);
    }

    public void onNextLevelButtonClicked(View view)
    {
        if (mCurrentLevel + 1 <= mMaxLevel)
            setLevel(++mCurrentLevel);
    }

    public void setLevel(int level)
    {
        resetActivity();
        //mNextLevelButton.setEnabled(false);
        ai_setLevel(level);
    }

    public native void ai_setLevel(int level);

}