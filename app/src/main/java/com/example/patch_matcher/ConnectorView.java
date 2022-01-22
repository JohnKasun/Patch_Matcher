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
    private Connectable mConnectableStart, mConnectableEnd;


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

        mConnectableStart = null;
        mConnectableEnd = null;
    }

    public void registerConnectables(Connectable connectableStart, Connectable connectableEnd) {
        mConnectableStart = connectableStart;
        mConnectableEnd = connectableEnd;
        updateOrientation();
    }

    public void updateOrientation() {
        if (mConnectableStart != null && mConnectableEnd != null) {
            updatePosition();
            updateAngle();
            updateLength();
            postInvalidate();
        }
    }

    private void updateLength(){
        mLength = getDistance();
        getLayoutParams().width = mLength;
        requestLayout();
    }

    private int getDistance(){
        float x1 = getCenterX(mConnectableStart);
        float x2 = getCenterX(mConnectableEnd);
        float y1 = getCenterY(mConnectableStart);
        float y2 = getCenterY(mConnectableEnd);

        float xDiff = x2 - x1;
        float yDiff = y2 - y1;

        int result = (int) Math.sqrt( Math.pow(xDiff,2) + Math.pow(yDiff,2) );
        return result;
    }

    private void updateAngle(){
        float x1 = getCenterX(mConnectableStart);
        float x2 = getCenterX(mConnectableEnd);
        float y1 = getCenterY(mConnectableStart);
        float y2 = getCenterY(mConnectableEnd);

        float xDiff = x2 - x1;
        float yDiff = y2 - y1;

        mAngle = (int) (Math.atan2(yDiff,xDiff) * 180 / Math.PI);
    }

    private void updatePosition() {
        mPosX = getCenterX(mConnectableStart);
        mPosY = getCenterY(mConnectableStart);
    }

    public float getCenterX(Connectable connectable) {
        return connectable.getX() + (connectable.getWidth() / 2f);
    }

    public float getCenterY(Connectable connectable) {
        return connectable.getY() + (connectable.getHeight() / 2f);
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

    public Connectable getStartConnectable() {
        return mConnectableStart;
    }

    public Connectable getEndConnectable() {
        return mConnectableEnd;
    }

    public boolean isEqualTo(ConnectorView newConnector) {
        if (mConnectableStart == newConnector.getStartConnectable() && mConnectableEnd == newConnector.getEndConnectable())
            return true;
        return false;
    }

    public boolean isReverseOf(ConnectorView newConnector) {
        if (mConnectableStart == newConnector.getEndConnectable() && mConnectableEnd == newConnector.getStartConnectable())
            return true;
        return false;
    }
}
