package com.johnkasun.patch_matcher;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.util.TypedValue;
import android.view.GestureDetector;
import android.view.MotionEvent;


import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.view.GestureDetectorCompat;


public class RotaryKnobView extends androidx.appcompat.widget.AppCompatImageView {

    private MotionEvent lastAction;
    private GestureDetectorCompat gestureDetector;
    private int maxValue;
    private int minValue;
    private int identifier;
    private boolean enhancedPrecision = false;
    public RotaryKnobListener listener;
    private float storedPosition, newPosition;
    private Drawable knobDrawable;
    private Drawable knobEnhancedDrawable;
    private float conversionFactor;
    private float conversionFactorFlipped;
    private float enhancedPrecisionFactor;
    private final float kTwoPi = (float) (2f * Math.PI);
    private final float m_fWidth = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 80, getResources().getDisplayMetrics());
    private final float m_fRadius = m_fWidth / 2.0f;
    private final float maxPosition = kTwoPi * m_fRadius * 0.75f;
    private final float POS_TO_ANGLE = (360.0f) / (kTwoPi * m_fRadius);
    private final float ANGLE_TO_POS = 1.0f / POS_TO_ANGLE;

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
        enhancedPrecisionFactor = 10.0f / maxValue;
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
                    currentDisplacement *= enhancedPrecisionFactor;
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
        {
            storedPosition = newPosition;
            listener.onKnobUp(identifier);
        }
        lastAction = event;
        if (gestureDetector.onTouchEvent(event))
            return true;
        else
            return super.onTouchEvent(event);
    }

    private float calculateAngle(float newPosition) {
        float angle = POS_TO_ANGLE * newPosition;
        return angle;
    }

    private int calculateValue(float angle){
        return (int) (angle * conversionFactor);
    }
    private int convertValueToAngle(int value) { return (int) (value * conversionFactorFlipped);};
    private int convertAngleToPosition(float angle) {
        int position = (int) (ANGLE_TO_POS * angle);
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

    public int getMaxValue() { return maxValue; };

    interface RotaryKnobListener {
        void onKnobRotate(int identifier, int value);
        void onKnobUp(int identifier);
    }
}

