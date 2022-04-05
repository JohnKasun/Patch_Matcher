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
import java.util.Vector;

public class TutorialActivity extends GameActivity
{

    enum Scene {
        Scene0,
        Scene1,
        Scene2,
        Scene3,
        Scene4
    }

    TextView infoTitle, infoBody;
    Button infoPreviousButton, infoNextButton;
    Scene mCurrentScene = Scene.Scene0;
    int mCurrentPage;
    Vector<String> mPages;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_tutorial);

        init();

        infoTitle = findViewById(R.id.infoTitle);
        infoBody = findViewById(R.id.infoBody);

        infoNextButton = findViewById(R.id.InfoNextButton);
        infoPreviousButton = findViewById(R.id.InfoPrevButton);

        setScene(mCurrentScene);
    }

    public void setPages(Vector<String> pages)
    {
        mCurrentPage = 0;
        mPages = pages;
    }

    public void onNextButtonClicked(View view)
    {
        mCurrentPage++;
        if (mCurrentPage < mPages.size()) {
            infoBody.setText(mPages.get(mCurrentPage));
            if ((mCurrentPage + 1) >= mPages.size()) {
                infoNextButton.setEnabled(false);
                infoPreviousButton.setEnabled(true);
            }
        }


    }

    public void onBackButtonClicked(View view)
    {

        mCurrentPage--;
        if (mCurrentPage >= 0) {
            infoBody.setText(mPages.get(mCurrentPage));
            if ((mCurrentPage - 1) < 0) {
                infoNextButton.setEnabled(true);
                infoPreviousButton.setEnabled(false);
            }
        }


    }

    protected void setScene(Scene scene)
    {
        switch (scene)
        {
            case Scene0:
                setScene0();
                break;
            case Scene1:
                setScene1();
                break;
            case Scene2:
                setScene2();
                break;
            case Scene3:
                setScene3();
                break;
            case Scene4:
                setScene4();
                break;
            default:

        }
        mCurrentScene = scene;
    }

    private void setScene0()
    {
        infoTitle.setText("Welcome!");
        infoBody.setText("Double Tap in the middle of the screen to begin...");
        infoNextButton.setEnabled(false);
        infoPreviousButton.setEnabled(false);
        maxOperators = 1;
    }

    private void setScene1()
    {
        String body1 = "Well done -- You just created an Operator!";
        String body2 = "An Operator is a building block for FM synthesis.";
        Vector<String> pages = new Vector<>();
        pages.add(body1);
        pages.add(body2);
        setPages(pages);

        infoTitle.setText("Intro");
        infoBody.setText(body1);
        infoNextButton.setEnabled(true);
        infoPreviousButton.setEnabled(false);
    }

    private void setScene2()
    {

    }

    private void setScene3()
    {

    }

    private void setScene4()
    {

    }

    @Override
    public void generateOperator(MotionEvent e)
    {
        super.generateOperator(e);
        if (mCurrentScene == Scene.Scene0)
            setScene(Scene.Scene1);
    }

}