package com.example.patch_matcher;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;

import androidx.annotation.Nullable;

public class OutputTerminalView extends Connectable {

    GestureDetector gestureDetector;
    OutputTerminalListener listener;
    Drawable outputTerminalDrawable;

    public OutputTerminalView(Context context) {
        super(context);
        init(null);
    }

    public OutputTerminalView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init(attrs);
    }

    public OutputTerminalView(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(attrs);
    }

    private void init(AttributeSet set){

        TypedArray ta = getContext().obtainStyledAttributes(set, R.styleable.OutputTerminalView);
        outputTerminalDrawable = ta.getDrawable(R.styleable.OutputTerminalView_OutputTerminalDrawable);
        identifier = ta.getInteger(R.styleable.OutputTerminalView_OutputTerminalIdentifier, -1);
        setImageDrawable(outputTerminalDrawable);

        gestureDetector = new GestureDetector(getContext(), new GestureDetector.SimpleOnGestureListener() {
            @Override
            public boolean onDown(MotionEvent e) {
                return true;
            }

            @Override
            public boolean onDoubleTap(MotionEvent e) {
                listener.connectToOutputTerminal();
                return super.onDoubleTap(e);
            }
        });
    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return gestureDetector.onTouchEvent(event);
    }

    interface OutputTerminalListener {
        void connectToOutputTerminal();
    }
}
