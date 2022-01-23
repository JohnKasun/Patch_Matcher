package com.example.patch_matcher;

import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;

import android.annotation.SuppressLint;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Bundle;
import android.util.TypedValue;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;


import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

import com.example.patch_matcher.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity implements RotaryKnobView.RotaryKnobListener, OutputTerminalView.OutputTerminalListener {

    static {
        System.loadLibrary("patch_matcher");
    }

    private ActivityMainBinding binding;
    OperatorView clickedOperator, selectedOperator;
    OutputTerminalView outputTerminal;
    TextView textView1, textView2, textView3;
    RotaryKnobView knob, knob2, knob3;
    ImageButton trashCan, playButton, stopButton;
    List<ConnectorView> connectorList;
    List<OperatorView> operatorList;
    Queue<Integer> idBacklog;
    ConstraintLayout background;
    float xOffset, yOffset;
    int numOperators = 0;
    final int maxOperators = 6;
    boolean deleteModeEnabled = false;

    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(R.layout.activity_main);

        knob = findViewById(R.id.knob);
        knob2 = findViewById(R.id.knob2);
        knob3 = findViewById(R.id.knob3);
        textView1 = findViewById(R.id.textView1);
        textView2 = findViewById(R.id.textView2);
        textView3 = findViewById(R.id.textView3);
        outputTerminal = findViewById(R.id.outputTerminalView);
        outputTerminal.listener = this;
        knob.listener = this;
        knob2.listener = this;
        knob3.listener = this;
        clickedOperator = null;
        selectedOperator = null;
        connectorList = new ArrayList<ConnectorView>();
        operatorList = new ArrayList<OperatorView>();
        idBacklog = new PriorityQueue<Integer>();
        trashCan = findViewById(R.id.imageButton);
        trashCan.setOnTouchListener((v, event) -> {
            switch (event.getActionMasked()){
                case MotionEvent.ACTION_DOWN:
                    toggleDeleteMode();
                    break;
            }
            return false;
        });
        background = findViewById(R.id.background);
        background.setOnTouchListener(new View.OnTouchListener() {

            GestureDetector gestureDetectorBackground = new GestureDetector(getApplicationContext(), new GestureDetector.SimpleOnGestureListener() {
                @Override
                public boolean onSingleTapConfirmed(MotionEvent e) {
                    deselectAll();
                    return super.onSingleTapConfirmed(e);
                }

                @Override
                public boolean onDoubleTap(MotionEvent e) {
                    if (!deleteModeEnabled)
                        generateOperator(e);
                    return super.onDoubleTap(e);
                }
            });

            @Override
            public boolean onTouch(View v, MotionEvent event) {
                gestureDetectorBackground.onTouchEvent(event);
                return true;
            }
        });
        playButton = findViewById(R.id.PlayButton);
        stopButton = findViewById(R.id.StopButton);
        playButton.setOnClickListener(v -> onPlayButtonPress());
        stopButton.setOnClickListener(v -> onStopButtonPress());
    }

    public void deselectAll() {
        if (selectedOperator != null && clickedOperator != null) {
            clickedOperator.deselect();
            selectedOperator.deselect();
            selectedOperator = null;
            clickedOperator = null;
        }
    }

    public void generateConnector(Connectable connectableStart, Connectable connectableEnd) {
        ConnectorView newConnector = new ConnectorView(MainActivity.this);
        newConnector.registerConnectables(connectableStart, connectableEnd);
        for (int i = 0; i < connectorList.size(); i++) {
            ConnectorView currentConnector = connectorList.get(i);
            if (newConnector.isEqualTo(currentConnector)){
                deleteConnector(currentConnector);
                return;
            } else if (newConnector.isReverseOf(currentConnector)){
                Toast.makeText(getApplicationContext(), "Connection already exists", Toast.LENGTH_SHORT).show();
                return;
            }
        }
        //connectOperators(operatorA.getIdentifier(), operatorB.getIdentifier());
        Toast.makeText(getApplicationContext(), "Operator " + connectableStart.getIdentifier() + " connected to Operator " + connectableEnd.getIdentifier(), Toast.LENGTH_SHORT).show();
        background.addView(newConnector);
        connectorList.add(newConnector);
        connectableStart.bringToFront();
        connectableEnd.bringToFront();
    }

    public void updateConnectorOrientations(){
        for (int i = 0; i < connectorList.size(); i++)
            connectorList.get(i).updateOrientation();
    }

    @SuppressLint("ClickableViewAccessibility")
    public void generateOperator(MotionEvent e) {

        if (numOperators >= maxOperators)
            Toast.makeText(getApplicationContext(), "Max Operator Limit Reached", Toast.LENGTH_SHORT).show();
        else {
            numOperators++;
            OperatorView newOperator = new OperatorView(MainActivity.this);
            int dimensionDp = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 70, getResources().getDisplayMetrics());
            newOperator.setLayoutParams(new ConstraintLayout.LayoutParams(dimensionDp, dimensionDp));
            newOperator.setX(e.getX());
            newOperator.setY(e.getY());
            newOperator.setOnTouchListener(new View.OnTouchListener() {
                GestureDetector gestureDetectorOperator = new GestureDetector(getApplicationContext(), new GestureDetector.SimpleOnGestureListener() {

                    @Override
                    public boolean onDoubleTap(MotionEvent e) {
                        if (!deleteModeEnabled)
                            generateConnector(selectedOperator, clickedOperator);
                        return super.onDoubleTap(e);
                    }

                    @Override
                    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
                        clickedOperator.setX(e2.getRawX() + xOffset);
                        clickedOperator.setY(e2.getRawY() + yOffset);
                        updateConnectorOrientations();
                        return super.onScroll(e1, e2, distanceX, distanceY);
                    }

                    @Override
                    public boolean onDown(MotionEvent event) {
                        xOffset = clickedOperator.getX() - event.getRawX();
                        yOffset = clickedOperator.getY() - event.getRawY();
                        return super.onDown(event);
                    }

                    @Override
                    public boolean onSingleTapConfirmed(MotionEvent e) {
                        if (!deleteModeEnabled)
                            selectOperator(clickedOperator);
                        else
                            deleteOperator(clickedOperator);
                        return super.onSingleTapConfirmed(e);
                    }
                });

                @Override
                public boolean onTouch(View v, MotionEvent event) {
                    clickedOperator = (OperatorView) v;
                    gestureDetectorOperator.onTouchEvent(event);
                    return false;
                }
            });

            if (idBacklog.isEmpty())
                newOperator.setIdentifier(numOperators);
            else
                newOperator.setIdentifier(idBacklog.remove());
            background.addView(newOperator);
            operatorList.add(newOperator);
            Toast.makeText(getApplicationContext(), "Created Operator " + newOperator.getIdentifier(), Toast.LENGTH_SHORT).show();
        }
    }

    public void toggleDeleteMode() {
        deselectAll();
        deleteModeEnabled = !deleteModeEnabled;
        int trashCanColor;
        int operatorColor;
        if (deleteModeEnabled) {
            trashCanColor = Color.RED;
            operatorColor = Color.RED;
        } else {
            trashCanColor = Color.LTGRAY;
            operatorColor = Color.BLACK;
        }
        trashCan.setBackgroundTintList(ColorStateList.valueOf(trashCanColor));
        for (int i = 0; i < operatorList.size(); i++)
            operatorList.get(i).setColor(operatorColor);
    }

    public void deleteOperator(OperatorView operatorToDelete) {
        idBacklog.add(operatorToDelete.getIdentifier());
        operatorList.remove(operatorToDelete);
        background.removeView(operatorToDelete);
        for (int i = 0; i < connectorList.size(); i++){
            ConnectorView currentConnector = connectorList.get(i);
            if (currentConnector.getStartConnectable() == operatorToDelete) {
                connectorList.remove(currentConnector);
                background.removeView(currentConnector);
                //disconnectOperators(operatorToDelete.getIdentifier(), currentConnector.getEndConnectable().getIdentifier());
                i--;
            } else if (currentConnector.getEndConnectable() == operatorToDelete) {
                connectorList.remove(currentConnector);
                background.removeView(currentConnector);
                //disconnectOperators(currentConnector.getStartConnectable().getIdentifier(), operatorToDelete.getIdentifier());
                i--;
            }
        }
        numOperators--;
    }

    public void deleteConnector(ConnectorView connectorToDelete) {
        background.removeView(connectorToDelete);
        connectorList.remove(connectorToDelete);
        String connectionInfo = "Operator " + connectorToDelete.getStartConnectable().getIdentifier() + " removed from Operator " + connectorToDelete.getEndConnectable().getIdentifier();
        //disconnectOperators(operatorA.getIdentifier(), operatorB.getIdentifier());
        Toast.makeText(getApplicationContext(), connectionInfo, Toast.LENGTH_SHORT).show();
    }

    public void selectOperator(OperatorView operatorToSelect) {
        if (selectedOperator != operatorToSelect) {
            if (selectedOperator != null)
                selectedOperator.deselect();
            operatorToSelect.select();
            selectedOperator = operatorToSelect;
        }
    }

    @Override
    public void onRotate(int identifier, int value) {
        switch (identifier){
            case 1:
                textView1.setText(""+value);
                break;
            case 2:
                textView2.setText(""+value);
                break;
            case 3:
                textView3.setText(""+value);
                break;
        }
    }

    @Override
    public void connectToOutputTerminal() {
        if (selectedOperator != null) {
            //connectOperatorToOutput(selectedOperator.getIdentifier());
            Toast.makeText(getApplicationContext(), "Operator " + selectedOperator.getIdentifier() + " connected to Output Terminal", Toast.LENGTH_SHORT).show();
            generateConnector(selectedOperator, outputTerminal);
        }
    }

    public native void onPlayButtonPress();
    public native void onStopButtonPress();
    public native void connectOperators(int operatorA, int operatorB);
    public native void disconnectOperators(int operatorA, int operatorB);
    public native void connectOperatorToOutput(int selectedOperator);

}