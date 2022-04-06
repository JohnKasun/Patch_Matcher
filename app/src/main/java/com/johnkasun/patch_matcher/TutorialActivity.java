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
    TextView tempFreqLabel, tempGainLabel, tempFeedbackLabel, tempWaveLabel;
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

        tempFreqLabel = findViewById(R.id.tempFrequencyLabel);
        tempGainLabel = findViewById(R.id.tempGainLabel);
        tempFeedbackLabel = findViewById(R.id.tempFeedback);
        tempWaveLabel = findViewById(R.id.tempWaveformLabel);

        tempFreqLabel.setVisibility(View.INVISIBLE);
        tempGainLabel.setVisibility(View.INVISIBLE);
        tempFeedbackLabel.setVisibility(View.INVISIBLE);
        tempWaveLabel.setVisibility(View.INVISIBLE);

        setScene(mCurrentScene);
    }

    public void setPages(Vector<String> pages)
    {
        mCurrentPage = 0;
        mPages = pages;
        if (mPages.size() > 1)
            infoNextButton.setEnabled(true);
        else
            infoNextButton.setEnabled(false);
        infoPreviousButton.setEnabled(false);
        infoBody.setText(mPages.get(0));
    }

    public void onNextButtonClicked(View view)
    {
        mCurrentPage++;
        if (mCurrentPage < mPages.size()) {
            infoBody.setText(mPages.get(mCurrentPage));
            infoPreviousButton.setEnabled(true);
        }
        if ((mCurrentPage + 1) >= mPages.size()) {
            infoNextButton.setEnabled(false);
        }

    }

    public void onBackButtonClicked(View view)
    {

        mCurrentPage--;
        if (mCurrentPage >= 0) {
            infoBody.setText(mPages.get(mCurrentPage));
            infoNextButton.setEnabled(true);
        }
        if ((mCurrentPage - 1) < 0) {
            infoPreviousButton.setEnabled(false);
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
        String body1 = "Double Tap in the middle of the screen to begin...";
        Vector<String> pages = new Vector<>();
        pages.add(body1);
        setPages(pages);

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

    }

    private void setScene2()
    {
        String body1 = "You just selected an Operator for editting.\n\n"
                + "You can now adjust its parameters as well as connect it to other Operators."
                + "\n\nLet's discuss the parameters...";
        String body2 = "Use the control panel to adjust the Operator's frequency, gain, feedback, and waveform.";
        String body3 = "Frequency is the pitch of the Operator.";
        String body4 = "Gain is the volume of the Operator.";
        String body5 = "Feedback determines by how much the current Operator's output is being used to modulate its own frequency.";
        String body6 = "Waveform is the shape of the audio signal being created\n\n"
                + "To change this, simply tap on the waveform icon";
        String body7 = "TIP:\nDouble Tap on any knob toggle between Enhanced Precision or Normal mode";
        String body8 = "To proceed, set the Operator's frequency to 440Hz and its gain to 100."
                + "  Then, Double tap on the Output Terminal...";
        Vector<String> pages = new Vector<String>();
        pages.add(body1);
        pages.add(body2);
        pages.add(body3);
        pages.add(body4);
        pages.add(body5);
        pages.add(body6);
        pages.add(body7);
        pages.add(body8);
        setPages(pages);

        infoTitle.setText("Parameters");

        controlPanelView.setVisibility(View.VISIBLE);
        outputTerminalView.setVisibility(View.VISIBLE);
        tempFreqLabel.setVisibility(View.VISIBLE);
        tempGainLabel.setVisibility(View.VISIBLE);
        tempFeedbackLabel.setVisibility(View.VISIBLE);
        tempWaveLabel.setVisibility(View.VISIBLE);

    }

    private void setScene3()
    {

        String body1 = "Great! Your Operator will now generate audio output."
                + "Turn up your phone volume and press the RIGHT play button to hear it...";
        Vector<String> pages = new Vector<String>();
        pages.add(body1);
        setPages(pages);

        infoTitle.setText("Operators");

        controlPanelView.setVisibility(View.INVISIBLE);
        outputTerminalView.setVisibility(View.INVISIBLE);
        tempFreqLabel.setVisibility(View.INVISIBLE);
        tempGainLabel.setVisibility(View.INVISIBLE);
        tempFeedbackLabel.setVisibility(View.INVISIBLE);
        tempWaveLabel.setVisibility(View.INVISIBLE);
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

    @Override
    public void onMakeConnection(Connectable connectableStart, Connectable connectableEnd)
    {
        super.onMakeConnection(connectableStart, connectableEnd);
        if (mCurrentScene == Scene.Scene2)
            setScene(Scene.Scene3);
    }

    @Override
    public void onPlayButtonClicked(PlayButtonView playButtonView)
    {
        super.onPlayButtonClicked(playButtonView);
        if (mCurrentScene == Scene.Scene3)
            setScene(Scene.Scene4);
    }

}