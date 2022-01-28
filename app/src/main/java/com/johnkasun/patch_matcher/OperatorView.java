package com.johnkasun.patch_matcher;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.util.TypedValue;
import android.view.GestureDetector;
import android.view.MotionEvent;

import androidx.annotation.Nullable;
import androidx.constraintlayout.widget.ConstraintLayout;

import java.util.PriorityQueue;
import java.util.Queue;

public class OperatorView extends Connectable {

    private int mColor;
    private Paint paint;
    private Rect rect;
    private float xOffset = 0, yOffset = 0;
    private int freqValue = 0, gainValue = 0;
    private GestureDetector gestureDetector;
    public OperatorViewListener listener = null;
    static private boolean deleteModeEnabled = false;
    static private OperatorView selectedOperator = null;
    static private int numOperators = 0;
    static private Queue<Integer> idBacklog = new PriorityQueue<Integer>();

    public OperatorView(Context context) {
        super(context);
        init(null);
    }

    public OperatorView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(attrs);
    }

    public OperatorView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(attrs);
    }

    private void init(@Nullable AttributeSet set){

        numOperators++;
        if (idBacklog.isEmpty())
            setIdentifier(numOperators);
        else
            setIdentifier(idBacklog.remove());
        paint = new Paint(Paint.ANTI_ALIAS_FLAG);
        rect = new Rect();
        mColor = Color.BLACK;

        int dimensionDp = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 70, getResources().getDisplayMetrics());
        setLayoutParams(new ConstraintLayout.LayoutParams(dimensionDp, dimensionDp));

        gestureDetector = new GestureDetector(getContext(), new GestureDetector.SimpleOnGestureListener() {

            @Override
            public boolean onDoubleTap(MotionEvent e) {
                if (!deleteModeEnabled)
                    listener.onMakeConnection(selectedOperator, OperatorView.this);
                return super.onDoubleTap(e);
            }

            @Override
            public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
                setX(e2.getRawX() + xOffset);
                setY(e2.getRawY() + yOffset);
                listener.onMoveOperator();
                return super.onScroll(e1, e2, distanceX, distanceY);
            }

            @Override
            public boolean onDown(MotionEvent event) {
                xOffset = getX() - event.getRawX();
                yOffset = getY() - event.getRawY();
                return true;
            }

            @Override
            public boolean onSingleTapConfirmed(MotionEvent e) {
                if (!deleteModeEnabled)
                    select();
                else
                    delete();
                return super.onSingleTapConfirmed(e);
            }
        });

    }

    public static void setDeleteModeEnabled(boolean deleteMode){
        deleteModeEnabled = deleteMode;
    }

    public static void setSelectedOperator(OperatorView newSelectedOperator){
        selectedOperator = newSelectedOperator;
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        paint.setColor(mColor);
        rect.left = 0;
        rect.right = getWidth();
        rect.top = 0;
        rect.bottom = getHeight();
        canvas.drawRect(rect, paint);

    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return gestureDetector.onTouchEvent(event);
    }

    public void deselect() {
        setColor(Color.BLACK);
    }

    public void setDeleteMode(){
        if (deleteModeEnabled)
            setColor(Color.RED);
        else
            setColor(Color.BLACK);
    }

    private void setColor(int newColor){
        mColor = newColor;
        postInvalidate();
    }

    private void setIdentifier(int newIdentifier){ identifier = newIdentifier; }

    private void select() {
        if (selectedOperator != this) {
            if (selectedOperator != null)
                selectedOperator.deselect();
            setColor(Color.YELLOW);
            selectedOperator = this;
            listener.onSelectOperator(selectedOperator);
        }
    }

    private void delete() {
        idBacklog.add(identifier);
        numOperators--;
        listener.onDeleteOperator(this);
    }

    public int getFreqValue() { return freqValue; };
    public int getGainValue() { return gainValue; };
    public void setFreqValue(int newFreqValue) { freqValue = newFreqValue; };
    public void setGainValue(int newGainValue) { gainValue = newGainValue; };

    interface OperatorViewListener {
        void onSelectOperator(OperatorView selectedOperator);
        void onDeleteOperator(OperatorView operatorToDelete);
        void onMoveOperator();
        void onMakeConnection(Connectable connectorStart, Connectable connectorEnd);
    }


}
