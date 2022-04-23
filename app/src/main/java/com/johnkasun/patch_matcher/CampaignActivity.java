package com.johnkasun.patch_matcher;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class CampaignActivity extends GameActivity {

    private final int mMaxLevel = 21;
    private int mCurrentLevel = 1;
    private Button mNextLevelButton;
    private TextView mLevelText;
    private LinearLayout mWinText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_campaign);

        init();

        mNextLevelButton = findViewById(R.id.NextLevelButton);
        mLevelText = findViewById(R.id.levelText);
        mWinText = findViewById(R.id.WinText);
        mWinText.setVisibility(View.INVISIBLE);

        setLevel(mCurrentLevel);
    }

    @Override
    public void onNextLevelButtonClicked(View view)
    {
        mCurrentLevel++;
        if (mCurrentLevel <= mMaxLevel)
        {
            if (mCurrentLevel == mMaxLevel)
            {
                mWinText.setVisibility(View.VISIBLE);
                mLevelText.setVisibility(View.INVISIBLE);
            }
            setLevel(mCurrentLevel);
        }

    }

    public void setLevel(int level)
    {
        resetActivity();
        mLevelText.setText("Level " + level);
        ai_setLevel(level);
    }

    public void onTempNextLevelButtonClicked(View view)
    {
        mCurrentLevel++;
        if (mCurrentLevel <= mMaxLevel)
        {
            if (mCurrentLevel == mMaxLevel)
            {
                mWinText.setVisibility(View.VISIBLE);
                mLevelText.setVisibility(View.INVISIBLE);
            }
            setLevel(mCurrentLevel);
        }
    }

    public native void ai_setLevel(int level);

}