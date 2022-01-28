package com.johnkasun.patch_matcher;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.util.TypedValue;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.constraintlayout.widget.ConstraintLayout;

public class ConnectorView extends View {

    Rect mRect;
    Path mPath;
    Paint mRectPaint;
    Paint mArrowPaint;
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
        mPath = new Path();
        mRectPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        mRectPaint.setColor(Color.BLACK);
        mArrowPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        mArrowPaint.setStyle(Paint.Style.FILL);
        mArrowPaint.setColor(Color.BLACK);

        setPivotX(0f);
        setPivotY(0f);

        mConnectableStart = null;
        mConnectableEnd = null;


        int widthDimensionDp = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 250, getResources().getDisplayMetrics());
        int heightDimensionDp = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 20, getResources().getDisplayMetrics());
        setLayoutParams(new ConstraintLayout.LayoutParams(widthDimensionDp, heightDimensionDp));
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

        int width = getWidth();
        int height = getHeight();

        mRect.left = 0;
        mRect.right = width;
        mRect.top = (height / 2) + 5;
        mRect.bottom = (height / 2) - 5;
        canvas.drawRect(mRect,mRectPaint);

        Path newPath = new Path();
        newPath.moveTo(width / 2, height);
        newPath.lineTo(width / 2 + 50, height / 2);
        newPath.lineTo(width / 2, 0);
        newPath.close();
        canvas.drawPath(newPath, mArrowPaint);

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
