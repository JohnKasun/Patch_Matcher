package com.example.patch_matcher;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class Operator extends androidx.appcompat.widget.AppCompatButton {

    static int numOperators = 0;
    private int ID;
    private float x;
    private float y;

    public Operator(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        numOperators++;
        ID = numOperators;
        setText("operator " + ID);
    }

    protected void finalize() {
        numOperators--;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        x = event.getX();
        y = event.getY();
        if (event.getAction() == MotionEvent.ACTION_MOVE){
            setX(x);
            setY(y);
        }
        return super.onTouchEvent(event);
    }

    public int getID() { return ID; };

}
