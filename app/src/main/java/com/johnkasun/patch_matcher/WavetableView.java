package com.johnkasun.patch_matcher;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class WavetableView extends androidx.appcompat.widget.AppCompatImageButton
{

    private final static int s_numWavetableTypes = 5;
    private Drawable m_dSineDrawable;
    private Drawable m_dSquareDrawable;
    private Drawable m_dCustomDrawable;
    private Drawable m_dTriangleDrawable;
    private Drawable m_dSawtoothDrawable;
    private GestureDetector m_gGestureDetector;
    private OperatorView selectedOperator = null;
    public WavetableViewListener listener = null;


    public WavetableView(@NonNull Context context) {
        super(context);
        init(null);
    }

    public WavetableView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init(attrs);
    }

    public WavetableView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(attrs);
    }

    private void init(AttributeSet set)
    {
        TypedArray ta = getContext().obtainStyledAttributes(set, R.styleable.WavetableView);
        m_dSineDrawable = ta.getDrawable(R.styleable.WavetableView_WavetableView_sineDrawable);
        m_dSquareDrawable = ta.getDrawable(R.styleable.WavetableView_WavetableView_squareDrawable);
        m_dCustomDrawable = ta.getDrawable(R.styleable.WavetableView_WavetableView_customDrawable);
        m_dTriangleDrawable = ta.getDrawable(R.styleable.WavetableView_WavetableView_triangleDrawable);
        m_dSawtoothDrawable = ta.getDrawable(R.styleable.WavetableView_WavetableView_sawtoothDrawable);
        setImageDrawable(m_dSineDrawable);
        ta.recycle();

        m_gGestureDetector = new GestureDetector(getContext(), new GestureDetector.SimpleOnGestureListener() {

            @Override
            public boolean onDown(MotionEvent event) {
                if (selectedOperator != null) {
                    selectedOperator.incrementWavetableType();
                    updateWavetableDrawable(selectedOperator);
                    listener.onWavetableChange(selectedOperator);
                }
                return true;
            }

        });
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return m_gGestureDetector.onTouchEvent(event);
    }

    public void setSelectedOperator(OperatorView newSelectedOperator)
    {
        selectedOperator = newSelectedOperator;
        updateWavetableDrawable(selectedOperator);

    }

    public static int getNumWavetableTypes() { return s_numWavetableTypes; };

    public void updateWavetableDrawable(OperatorView operatorWavetableToDisplay)
    {
        if (operatorWavetableToDisplay == null) {
            setImageDrawable(m_dSineDrawable);
            return;
        }
        switch (operatorWavetableToDisplay.getWavetableType()){
            case 0:
                setImageDrawable(m_dSineDrawable);
                return;
            case 1:
                setImageDrawable(m_dSquareDrawable);
                return;
            case 2:
                setImageDrawable(m_dTriangleDrawable);
                return;
            case 3:
                setImageDrawable(m_dSawtoothDrawable);
                return;
            case 4:
                setImageDrawable(m_dCustomDrawable);
                return;
        }
    }

    interface WavetableViewListener {
        void onWavetableChange(OperatorView operatorToChangeWavetable);
    }


}
