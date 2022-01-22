package com.example.patch_matcher;

import android.app.ActionBar;
import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.view.View;

import androidx.annotation.Nullable;

public class ConnectorView extends View {

    Rect mRect;
    Paint mPaint;
    int mColor;
    float mPosX, mPosY;
    int mAngle = 0;
    int mLength;
    Operator operatorA, operatorB;


    public ConnectorView(Context context) {
        super(context);
        init(null);
    }

    public ConnectorView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init(attrs);
    }

    public ConnectorView(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(attrs);
    }

    public void init(AttributeSet set) {
        mRect = new Rect();
        mPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        mColor = Color.BLACK;

        setPivotX(0f);
        setPivotY(0f);

        operatorA = null;
        operatorB = null;
    }

    public void registerOperators(Operator selectedOperator, Operator clickedOperator) {
        operatorA = selectedOperator;
        operatorB = clickedOperator;
        updateOrientation();
    }

    public void updateOrientation() {
        if (operatorA != null && operatorB != null) {
            updatePosition();
            updateAngle();
            updateLength();
            postInvalidate();
        }
    }

    private void updateLength(){
        mLength = getDistance(operatorA, operatorB);
        getLayoutParams().width = mLength;
        requestLayout();
    }

    private int getDistance(Operator operatorA, Operator operatorB){
        float x1 = operatorA.getCenterX();
        float x2 = operatorB.getCenterX();
        float y1 = operatorA.getCenterY();
        float y2 = operatorB.getCenterY();

        float xDiff = x2 - x1;
        float yDiff = y2 - y1;

        int result = (int) Math.sqrt( Math.pow(xDiff,2) + Math.pow(yDiff,2) );
        return result;
    }

    private void updateAngle(){
        float x1 = operatorA.getCenterX();
        float x2 = operatorB.getCenterX();
        float y1 = operatorA.getCenterY();
        float y2 = operatorB.getCenterY();

        float xDiff = x2 - x1;
        float yDiff = y2 - y1;

        mAngle = (int) (Math.atan2(yDiff,xDiff) * 180 / Math.PI);
    }

    private void updatePosition() {
        mPosX = operatorA.getCenterX();
        mPosY = operatorA.getCenterY();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        mPaint.setColor(mColor);

        mRect.left = 0;
        mRect.right = getWidth();
        mRect.top = 0;
        mRect.bottom = getHeight();
        canvas.drawRect(mRect,mPaint);

        setRotation(mAngle);
        setX(mPosX);
        setY(mPosY);
    }
}
