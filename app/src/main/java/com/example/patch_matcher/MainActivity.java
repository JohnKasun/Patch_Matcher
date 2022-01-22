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
    List<ConnectorView> connectors;
    List<OperatorView> operators;
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

        knob = (RotaryKnobView)findViewById(R.id.knob);
        knob2 = (RotaryKnobView)findViewById(R.id.knob2);
        knob3 = (RotaryKnobView)findViewById(R.id.knob3);
        textView1 = (TextView) findViewById(R.id.textView1);
        textView2 = (TextView) findViewById(R.id.textView2);
        textView3 = (TextView) findViewById(R.id.textView3);
        outputTerminal = (OutputTerminalView) findViewById(R.id.outputTerminalView);
        outputTerminal.listener = this;
        knob.listener = this;
        knob2.listener = this;
        knob3.listener = this;
        clickedOperator = null;
        selectedOperator = null;
        connectors = new ArrayList<ConnectorView>();
        operators = new ArrayList<OperatorView>();
        idBacklog = new PriorityQueue<Integer>();
        trashCan = (ImageButton) findViewById(R.id.imageButton);
        trashCan.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getActionMasked()){
                    case MotionEvent.ACTION_DOWN:
                        toggleDeleteMode();
                        break;
                }
                return false;
            }
        });
        background = (ConstraintLayout) findViewById(R.id.background);
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
        playButton = (ImageButton) findViewById(R.id.PlayButton);
        stopButton = (ImageButton) findViewById(R.id.StopButton);
        playButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onPlayButtonPress();
            }
        });
        stopButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onStopButtonPress();
            }
        });
    }

    public void deselectAll() {
        if (selectedOperator != null && clickedOperator != null) {
            clickedOperator.deselect();
            selectedOperator.deselect();
            selectedOperator = null;
            clickedOperator = null;
        }
    }

    public void generateConnector(Connectable operatorA, Connectable operatorB){
        if (operatorB != operatorA && operatorA != null) {
            for (int i = 0; i < connectors.size(); i++) {
                ConnectorView currentConnector = connectors.get(i);
                if (operatorA == currentConnector.operatorA && operatorB == currentConnector.operatorB) {
                    background.removeView(currentConnector);
                    connectors.remove(currentConnector);
                    String connectionInfo = "Operator " + operatorA.identifier + " removed from Operator " + operatorB.identifier;
                    disconnectOperators(operatorA.identifier, operatorB.identifier);
                    Toast.makeText(getApplicationContext(), connectionInfo, Toast.LENGTH_SHORT).show();
                    return;
                } else if (operatorA == currentConnector.operatorB && operatorB == currentConnector.operatorA) {
                    Toast.makeText(getApplicationContext(), "Connection already exists", Toast.LENGTH_SHORT).show();
                    return;
                }
            }

            String connectionInfo = "Operator " + operatorA.identifier + " connected to Operator " + operatorB.identifier;
            //connectOperators(operatorA.identifier, operatorB.identifier);
            Toast.makeText(getApplicationContext(), connectionInfo, Toast.LENGTH_SHORT).show();
            ConnectorView newConnector = new ConnectorView(MainActivity.this);
            int widthDimensionDp = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 250, getResources().getDisplayMetrics());
            int heightDimensionDp = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 5, getResources().getDisplayMetrics());
            newConnector.setLayoutParams(new ConstraintLayout.LayoutParams(widthDimensionDp, heightDimensionDp));
            newConnector.registerOperators(operatorA, operatorB);
            background.addView(newConnector);
            connectors.add(newConnector);
        }
    }

    public void updateConnectorOrientations(){
        for (int connector = 0; connector < connectors.size(); connector++)
            connectors.get(connector).updateOrientation();
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
                newOperator.setID(numOperators);
            else
                newOperator.setID(idBacklog.remove());
            background.addView(newOperator);
            operators.add(newOperator);
            Toast.makeText(getApplicationContext(), "Created Operator " + newOperator.identifier, Toast.LENGTH_SHORT).show();
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
        for (int i = 0; i < operators.size(); i++)
            operators.get(i).setColor(operatorColor);
    }

    public void deleteOperator(OperatorView operatorToDelete) {
        idBacklog.add(operatorToDelete.identifier);
        operators.remove(operatorToDelete);
        background.removeView(operatorToDelete);
        for (int i = 0; i < connectors.size(); i++){
            ConnectorView currentConnector = connectors.get(i);
            if (currentConnector.operatorA == operatorToDelete) {
                connectors.remove(currentConnector);
                background.removeView(currentConnector);
                disconnectOperators(operatorToDelete.identifier, currentConnector.operatorB.identifier);
                i--;
            } else if (currentConnector.operatorB == operatorToDelete) {
                connectors.remove(currentConnector);
                background.removeView(currentConnector);
                disconnectOperators(currentConnector.operatorA.identifier, operatorToDelete.identifier);
                i--;
            }
        }
        numOperators--;
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
            connectOperatorToOutput(selectedOperator.identifier);
            Toast.makeText(getApplicationContext(), "Operator " + selectedOperator.identifier + " connected to Output Terminal", Toast.LENGTH_SHORT).show();
            generateConnector(selectedOperator, outputTerminal);
        }
    }

    public native void onPlayButtonPress();
    public native void onStopButtonPress();
    public native void connectOperators(int operatorA, int operatorB);
    public native void disconnectOperators(int operatorA, int operatorB);
    public native void connectOperatorToOutput(int selectedOperator);

}