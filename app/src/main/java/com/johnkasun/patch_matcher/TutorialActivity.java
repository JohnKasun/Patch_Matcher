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
        Scene4,
        Scene5,
        Scene6,
        Scene7,
        Scene8,
        Scene9,
        Scene10
    }

    ImageView controlPanelView, outputTerminalView, similarityScoreView;
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
        similarityScoreView = findViewById(R.id.SimilarityScoreView);
        controlPanelView.setVisibility(View.INVISIBLE);
        outputTerminalView.setVisibility(View.INVISIBLE);
        similarityScoreView.setVisibility(View.INVISIBLE);

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

    public void onProceedButtonClicked(View view)
    {
        if (mCurrentScene == Scene.Scene8)
            setScene(Scene.Scene9);
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
            case Scene5:
                setScene5();
                break;
            case Scene6:
                setScene6();
                break;
            case Scene7:
                setScene7();
                break;
            case Scene8:
                setScene8();
                break;
            case Scene9:
                setScene9();
                break;
            case Scene10:
                setScene10();
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
    }

    private void setScene4()
    {
        String body1 = "Now, let's discuss FM synthesis!";
        String body2 = "FM is short for frequency modulation, which is a type of synthesis where a sinusoid's "
                + "frequency is being changed by another sinusoid.";
        String body3 = "Doing so creates sidebands in the frequency domain, which can lead to very interesting and complex timbres";
        String body4 = "Let's create an FM patch of our own!";
        String body5 = "Create another Operator by double clicking anywhere on screen...";
        Vector<String> pages = new Vector<String>();
        pages.add(body1);
        pages.add(body2);
        pages.add(body3);
        pages.add(body4);
        pages.add(body5);
        setPages(pages);

        infoTitle.setText("FM");

        maxOperators = 2;
    }


    private void setScene5()
    {
        String body1 = "Great!\n\nSelect this new Operator and set its frequency to half of Operator 1's frequency and set its gain to 100.";
        String body2 = "Then, Double click on Operator1...";
        Vector<String> pages = new Vector<String>();
        pages.add(body1);
        pages.add(body2);
        setPages(pages);
    }

    private void setScene6()
    {
        String body1 = "You just created a connection from Operator 2 to Operator 1!\n\n";
        String body2 = "You would verbalize this setup as: Operator 2 is modulating Operator 1.";
        String body3 = "- Operator 1 is considered a CARRIER\n\n- Operator 2 is considered a MODULATOR";
        String body4 = "On a mathematical level, the output values of Operator 2 are being added to the frequency of Operator 1";
        String body5 = "If you haven't already, press the RIGHT Play button again and listen to the result\n\n"
                + "The Timbre is almost horn-like";
        String body6 = "FM works best when connected Operators' frequencies are integer multiples of each other...";
        String body7 = "...But it doesn't have to be that way!\n\nLet's make a vibrato. Create another Operator to proceed...";
        Vector<String> pages = new Vector<String>();
        pages.add(body1);
        pages.add(body2);
        pages.add(body3);
        pages.add(body4);
        pages.add(body5);
        pages.add(body6);
        pages.add(body7);
        setPages(pages);

        maxOperators = 3;
    }

    private void setScene7()
    {
        String body1 = "Set this Operator's gain to 100% and its frequency to a value between 1Hz and 5Hz";
        String body2 = "Now, connect this Operator to Operator 1...";
        Vector<String> pages = new Vector<>();
        pages.add(body1);
        pages.add(body2);
        setPages(pages);
    }

    private void setScene8()
    {
        String body1 = "You should now hear a vibrato applied to the sound you had before";
        String body2 = "Experiment with different parameter values for each Operator and see how the outputting sound is affected.";
        String body3 = "Don't forget about the Feedback and Waveform parameters as they can have drastic effects!";
        String body4 = "When you'd like to continue, click the Proceed button...";
        Vector<String> pages = new Vector<>();
        pages.add(body1);
        pages.add(body2);
        pages.add(body3);
        pages.add(body4);
        setPages(pages);
    }

    private void setScene9()
    {
        infoTitle.setText("The Game");

        String body1 = "The goal of Patch Matcher is for you to try to replicate a generated sound using FM synthesis.";
        String body2 = "Press the LEFT play button...";
        Vector<String> pages = new Vector<>();
        pages.add(body1);
        pages.add(body2);
        setPages(pages);
    }

    private void setScene10()
    {
        String body1 = "This is the sound that you must match!\n\nLet's call this the Target Patch";
        String body2 = "You can toggle between hearing your on-screen patch or the Target Patch by clicking the appropriate play button.";
        String body3 = "The percentage value in the top right of the screen is your Similarity Score.";
        String body4 = "This updates live as you work and represents how close your patch is to the Target Patch.";
        Vector<String> pages = new Vector<>();
        pages.add(body1);
        pages.add(body2);
        pages.add(body3);
        pages.add(body4);
        setPages(pages);

        similarityScoreView.setVisibility(View.VISIBLE);
    }

    @Override
    public void generateOperator(MotionEvent e)
    {
        super.generateOperator(e);
        if (mCurrentScene == Scene.Scene0)
            setScene(Scene.Scene1);
        else if (mCurrentScene == Scene.Scene4)
            setScene(Scene.Scene5);
        else if (mCurrentScene == Scene.Scene6)
            setScene(Scene.Scene7);
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
        else if (mCurrentScene == Scene.Scene5)
            setScene(Scene.Scene6);
        else if (mCurrentScene == Scene.Scene7)
            setScene(Scene.Scene8);
    }

    @Override
    public void onPlayButtonClicked(PlayButtonView playButtonView)
    {
        super.onPlayButtonClicked(playButtonView);
        if (mCurrentScene == Scene.Scene3 && playButtonView == playButtonUser)
            setScene(Scene.Scene4);
        else if (mCurrentScene == Scene.Scene9 && playButtonView == playButtonTarget)
            setScene(Scene.Scene10);
    }

}