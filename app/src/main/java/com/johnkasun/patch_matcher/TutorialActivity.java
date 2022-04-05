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
import android.widget.ImageView;
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

    ImageView controlPanelView, outputTerminalView;
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

        controlPanelView = findViewById(R.id.ControlPanelLabel);
        outputTerminalView = findViewById(R.id.OutputTerminalLabel);
        controlPanelView.setVisibility(View.INVISIBLE);
        outputTerminalView.setVisibility(View.INVISIBLE);

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

        trashCan.setEnabled(false);
        playButtonUser.setEnabled(false);
        playButtonTarget.setEnabled(false);
    }

    private void setScene1()
    {
        String body1 = "Well done -- You just created an Operator!\n\n"
                + "These will be the building blocks of our FM synthesis!";

        String body2 = "Tap on the Operator that you just created to proceed...";
        Vector<String> pages = new Vector<String>();
        pages.add(body1);
        pages.add(body2);
        setPages(pages);

        infoTitle.setText("Operators");
        infoBody.setText(body1);
        infoNextButton.setEnabled(true);

    }

    private void setScene2()
    {
        String body1 = "You just selected an Operator for editting.\n\n"
                + "You can now adjust its parameters as well as connect it to other Operators.";
        String body2 = "Use the control panel to adjust the Operator's frequency, gain, feedback percentage, and waveform.";
        String body3 = "To proceed, set the Operator's frequency to 440Hz and its gain to 100."
                + "  Then, Double tap on the Output Terminal...";
        Vector<String> pages = new Vector<String>();
        pages.add(body1);
        pages.add(body2);
        pages.add(body3);
        setPages(pages);

        infoTitle.setText("Operators");
        infoBody.setText(body1);
        infoNextButton.setEnabled(true);
        infoPreviousButton.setEnabled(false);

        controlPanelView.setVisibility(View.VISIBLE);
        outputTerminalView.setVisibility(View.VISIBLE);
    }

    private void setScene3()
    {
        controlPanelView.setVisibility(View.INVISIBLE);
        outputTerminalView.setVisibility(View.INVISIBLE);
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

    @Override
    public void onSelectOperator(OperatorView selectedOperator)
    {
        super.onSelectOperator(selectedOperator);
        if (mCurrentScene == Scene.Scene1)
            setScene(Scene.Scene2);
    }

}