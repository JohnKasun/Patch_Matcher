package com.example.patch_matcher;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.widget.Button;
import android.widget.Toast;

import androidx.annotation.Nullable;

public class Operator extends androidx.appcompat.widget.AppCompatButton {

    private int mColor;
    public int ID;
    private Paint paint;
    private Rect rect;

    public Operator(Context context) {
        super(context);
        init(null);
    }

    public Operator(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(attrs);
    }

    public Operator(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(attrs);
    }

    private void init(@Nullable AttributeSet set){
        paint = new Paint(Paint.ANTI_ALIAS_FLAG);
        rect = new Rect();
        mColor = Color.BLACK;
    }

    public void select() {
        mColor = Color.YELLOW;
        postInvalidate();
    }

    public void deselect() {
        mColor = Color.BLACK;
        postInvalidate();
    }

    public void setColor(int newColor){
        mColor = newColor;
        postInvalidate();
    }

    public float getCenterX() {
        return getX() + getWidth() / 2f;
    }

    public float getCenterY() {
        return getY() + getHeight() / 2f;
    }

    public void setID(int newID){ ID = newID; }


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

}
