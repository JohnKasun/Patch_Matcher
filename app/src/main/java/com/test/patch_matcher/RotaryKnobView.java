package com.test.patch_matcher;

import android.content.Context;
import android.content.res.TypedArray;
import android.gesture.Gesture;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.view.GestureDetectorCompat;

public class RotaryKnobView extends androidx.appcompat.widget.AppCompatImageView {

    private GestureDetectorCompat gestureDetector;
    private int maxValue;
    private int minValue;
    private int identifier;
    private boolean enhancedPrecision = false;
    public RotaryKnobListener listener;
    float storedPosition, newPosition;
    Drawable knobDrawable;
    Drawable knobEnhancedDrawable;
    float radius;
    float maxPosition;
    float conversionFactor;
    float conversionFactorFlipped;
    final float kTwoPi = (float) (2f * Math.PI);

    public RotaryKnobView(@NonNull Context context) {
        super(context);
        init(null);
    }

    public RotaryKnobView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init(attrs);
    }

    public RotaryKnobView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(attrs);
    }


    private void init(AttributeSet set){

        TypedArray ta = getContext().obtainStyledAttributes(set, R.styleable.RotaryKnobView);
        minValue = ta.getInt(R.styleable.RotaryKnobView_minValue, 0);
        maxValue = ta.getInt(R.styleable.RotaryKnobView_maxValue, 0);
        identifier = ta.getInteger(R.styleable.RotaryKnobView_identifier, -1);
        conversionFactor = maxValue / 270f;
        conversionFactorFlipped = 1.0f / conversionFactor;
        storedPosition = ta.getInt(R.styleable.RotaryKnobView_initialValue, 0);
        knobDrawable = ta.getDrawable(R.styleable.RotaryKnobView_knobDrawable);
        knobEnhancedDrawable = ta.getDrawable(R.styleable.RotaryKnobView_knobEnhancedDrawable);
        setImageDrawable(knobDrawable);
        ta.recycle();

        gestureDetector = new GestureDetectorCompat(getContext(), new GestureDetector.SimpleOnGestureListener() {

            @Override
            public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
                float currentDisplacement = e2.getRawX() - e1.getRawX();
                if (enhancedPrecision)
                    currentDisplacement *= 0.01f;
                newPosition = storedPosition + currentDisplacement;
                if (newPosition > maxPosition)
                    newPosition = maxPosition;
                if (newPosition < 0)
                    newPosition = minValue;
                float angle = calculateAngle(newPosition);
                int value = calculateValue(angle);
                setRotation(angle);
                listener.onKnobRotate(identifier, value);
                return true;
            }

            @Override
            public boolean onDown(MotionEvent e) {
                radius = (float) getLayoutParams().width / 2.0f;
                maxPosition = kTwoPi*radius*0.75f;
                return true;
            }

            @Override
            public boolean onDoubleTap(MotionEvent e) {
                toggleEnhancedMode();
                return super.onDoubleTap(e);
            }

        });
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (event.getActionMasked() == MotionEvent.ACTION_UP)
            storedPosition = newPosition;
        if (gestureDetector.onTouchEvent(event))
            return true;
        else
            return super.onTouchEvent(event);
    }

    private float calculateAngle(float newPosition) {
        float angle = (float) ((360.0 * newPosition) / (kTwoPi * radius));
        return angle;
    }

    private int calculateValue(float angle){
        return (int) (angle * conversionFactor);
    }
    private int convertValueToAngle(int value) { return (int) (value * conversionFactorFlipped);};
    private int convertAngleToPosition(float angle) {
        int position = (int) (kTwoPi * radius * angle / 360.0);
        return position;
    }
    public void setKnobPosition(int value) {
        float newAngle = convertValueToAngle(value);
        setRotation(newAngle);
        storedPosition = convertAngleToPosition(newAngle);
    }

    private void toggleEnhancedMode() {
        enhancedPrecision = !enhancedPrecision;
        if (enhancedPrecision)
            setImageDrawable(knobEnhancedDrawable);
        else
            setImageDrawable(knobDrawable);
    }

    interface RotaryKnobListener {
        void onKnobRotate(int identifier, int value);
    }
}

