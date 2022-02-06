package com.johnkasun.patch_matcher;

import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;

import android.annotation.SuppressLint;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Bundle;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;


import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity
        implements RotaryKnobView.RotaryKnobListener,
                    OutputTerminalView.OutputTerminalListener,
                    OperatorView.OperatorViewListener,
                    PlayButtonView.PlayButtonListener{

    static {
        System.loadLibrary("patch_matcher");
    }

    enum state {
        notPlaying,
        playingUser,
        playingTarget
    };

    state playState = state.notPlaying;
    OutputTerminalView outputTerminal;
    TextView textView1, textView2, textView3;
    RotaryKnobView knob1, knob2, knob3;
    ImageButton trashCan;
    PlayButtonView playButtonUser, playButtonTarget;
    ConstraintLayout background;
    List<ConnectorView> connectorList = new ArrayList<ConnectorView>();
    List<OperatorView> operatorList = new ArrayList<OperatorView>();
    boolean deleteModeEnabled = false;
    OperatorView selectedOperator = null;
    final int maxOperators = 6;

    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        knob1 = findViewById(R.id.knob1);
        knob2 = findViewById(R.id.knob2);
        knob3 = findViewById(R.id.knob3);
        knob1.listener = this;
        knob2.listener = this;
        knob3.listener = this;

        textView1 = findViewById(R.id.textView1);
        textView2 = findViewById(R.id.textView2);
        textView3 = findViewById(R.id.textView3);

        outputTerminal = findViewById(R.id.outputTerminalView);
        outputTerminal.listener = this;

        trashCan = findViewById(R.id.imageButton);
        trashCan.setOnTouchListener((v, event) -> {
            if (event.getActionMasked() == MotionEvent.ACTION_DOWN)
                toggleDeleteMode();
            return false;
        });

        background = findViewById(R.id.background);
        background.setOnTouchListener(new View.OnTouchListener() {

            GestureDetector gestureDetectorBackground = new GestureDetector(getApplicationContext(), new GestureDetector.SimpleOnGestureListener() {
                @Override
                public boolean onSingleTapConfirmed(MotionEvent e) {
                    deselectAll();
                    disableKnobs();
                    return super.onSingleTapConfirmed(e);
                }

                @Override
                public boolean onDoubleTap(MotionEvent e) {
                    generateOperator(e);
                    return super.onDoubleTap(e);
                }
            });

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (!deleteModeEnabled)
                    gestureDetectorBackground.onTouchEvent(event);
                return true;
            }
        });

        playButtonUser = findViewById(R.id.playButtonUser);
        playButtonTarget = findViewById(R.id.playButtonTarget);
        playButtonUser.listener = this;
        playButtonTarget.listener = this;
    }

    public void deselectAll() {
        selectedOperator = null;
        OperatorView.setSelectedOperator(null);
        OutputTerminalView.setSelectedOperator(null);
        for (int i = 0; i < operatorList.size(); i++)
            operatorList.get(i).deselect();
    }

    public void generateOperator(MotionEvent e) {
        if (operatorList.size() >= maxOperators)
            Toast.makeText(getApplicationContext(), "Max Operator Limit Reached", Toast.LENGTH_SHORT).show();
        else {
            OperatorView newOperator = new OperatorView(MainActivity.this);
            newOperator.listener = this;
            newOperator.setX(e.getX());
            newOperator.setY(e.getY());
            background.addView(newOperator);
            operatorList.add(newOperator);
            Toast.makeText(getApplicationContext(), "Created Operator " + newOperator.getIdentifier(), Toast.LENGTH_SHORT).show();
        }
    }

    public void toggleDeleteMode() {
        deselectAll();
        deleteModeEnabled = !deleteModeEnabled;
        OperatorView.setDeleteModeEnabled(deleteModeEnabled);
        for (int i = 0; i < operatorList.size(); i++)
            operatorList.get(i).setDeleteMode();

        if (deleteModeEnabled)
            trashCan.setBackgroundTintList(ColorStateList.valueOf(Color.RED));
        else
            trashCan.setBackgroundTintList(ColorStateList.valueOf(Color.LTGRAY));
    }

    public void deleteConnector(ConnectorView connectorToDelete) {
        ai_disconnect(connectorToDelete.getStartConnectable().getIdentifier(), connectorToDelete.getEndConnectable().getIdentifier());
        background.removeView(connectorToDelete);
        connectorList.remove(connectorToDelete);
        String connectionInfo = "Operator " + connectorToDelete.getStartConnectable().getIdentifier() + " removed from Operator " + connectorToDelete.getEndConnectable().getIdentifier();
        Toast.makeText(getApplicationContext(), connectionInfo, Toast.LENGTH_SHORT).show();
    }

    public void updateKnobPositions(OperatorView selectedOperator){
        knob1.setKnobPosition(selectedOperator.getFreqValue());
        knob2.setKnobPosition(selectedOperator.getGainValue());
        textView1.setText("" + selectedOperator.getFreqValue());
        textView2.setText("" + selectedOperator.getGainValue());
    }

    public void disableKnobs(){
        knob1.setKnobPosition(0);
        knob2.setKnobPosition(0);
        knob3.setKnobPosition(0);
        textView1.setText("Frequency");
        textView2.setText("Gain");
        textView3.setText("Feedback");
    }


    @Override
    public void onDeleteOperator(OperatorView operatorToDelete) {
        operatorList.remove(operatorToDelete);
        background.removeView(operatorToDelete);
        ai_resetValues(operatorToDelete.getIdentifier());
        for (int i = 0; i < connectorList.size(); i++){
            ConnectorView currentConnector = connectorList.get(i);
            if (currentConnector.getStartConnectable() == operatorToDelete || currentConnector.getEndConnectable() == operatorToDelete) {
                deleteConnector(currentConnector);
                i--;
            }
        }
    }

    @Override
    public void onKnobRotate(int identifier, int value) {
        if (selectedOperator != null) {
            switch (identifier) {
                case 1:
                    textView1.setText("" + value);
                    selectedOperator.setFreqValue(value);
                    ai_onChangeFrequency(selectedOperator.getIdentifier(), value);
                    break;
                case 2:
                    textView2.setText("" + value);
                    selectedOperator.setGainValue(value);
                    ai_onChangeGain(selectedOperator.getIdentifier(), value);
                    break;
                case 3:
                    textView3.setText("" + value);
                    break;
            }
        }
    }

    @Override
    public void onSelectOperator(OperatorView selectedOperator){
        this.selectedOperator = selectedOperator;
        OutputTerminalView.setSelectedOperator(selectedOperator);
        updateKnobPositions(selectedOperator);
    }

    @Override
    public void onMakeConnection(Connectable connectableStart, Connectable connectableEnd) {
        if (connectableStart != connectableEnd && connectableStart != null && connectableEnd != null) {
            ConnectorView newConnector = new ConnectorView(MainActivity.this);
            newConnector.registerConnectables(connectableStart, connectableEnd);
            for (int i = 0; i < connectorList.size(); i++) {
                ConnectorView currentConnector = connectorList.get(i);
                if (newConnector.isEqualTo(currentConnector)) {
                    deleteConnector(currentConnector);
                    return;
                } else if (newConnector.isReverseOf(currentConnector)) {
                    Toast.makeText(getApplicationContext(), "Connection already exists", Toast.LENGTH_SHORT).show();
                    return;
                }
            }
            ai_connect(connectableStart.getIdentifier(), connectableEnd.getIdentifier());
            Toast.makeText(getApplicationContext(), "Operator " + connectableStart.getIdentifier() + " connected to Operator " + connectableEnd.getIdentifier(), Toast.LENGTH_SHORT).show();
            background.addView(newConnector);
            connectorList.add(newConnector);
            connectableStart.bringToFront();
            connectableEnd.bringToFront();
        }
    }

    @Override
    public void onMoveOperator(){
        for (int i = 0; i < connectorList.size(); i++)
            connectorList.get(i).updateOrientation();
    }

    @Override
    public void onPlayButtonClicked(PlayButtonView playButtonView) {
        if (playButtonView == playButtonUser) {
            switch (playState){
                case playingTarget:
                    playButtonTarget.setEnabled(false);
                case notPlaying:
                    ai_onPlayUserAudio();
                    playState = state.playingUser;
                    playButtonUser.setEnabled(true);
                    break;
                case playingUser:
                    ai_onStopAudio();
                    playState = state.notPlaying;
                    playButtonUser.setEnabled(false);
                    break;
            }
        } else {
            switch (playState){
                case playingUser:
                    playButtonUser.setEnabled(false);
                case notPlaying:
                    ai_onPlayTargetAudio();
                    playState = state.playingTarget;
                    playButtonTarget.setEnabled(true);
                    break;
                case playingTarget:
                    ai_onStopAudio();
                    playState = state.notPlaying;
                    playButtonTarget.setEnabled(false);
                    break;
            }
        }
    }

    public native void ai_onStopAudio();
    public native void ai_onChangeFrequency(int operator_id, int value);
    public native void ai_onChangeGain(int operator_id, int value);
    public native void ai_connect(int ConnectableA_id, int ConnectableB_id);
    public native void ai_disconnect(int ConnectableA_id, int ConnectableB_id);
    public native void ai_resetValues(int operator_id);
    public native void ai_onPlayTargetAudio();
    public native void ai_onPlayUserAudio();

}