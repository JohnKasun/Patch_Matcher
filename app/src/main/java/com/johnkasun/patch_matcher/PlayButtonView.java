package com.johnkasun.patch_matcher;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.widget.ImageButton;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.view.GestureDetectorCompat;


public class PlayButtonView extends androidx.appcompat.widget.AppCompatImageView {

    private Drawable playingDrawable;
    private Drawable stoppedDrawable;
    private GestureDetectorCompat gestureDetector;
    public PlayButtonListener listener;
    private boolean isEnabled = false;

    public PlayButtonView(@NonNull Context context) {
        super(context);
        init(null);
    }

    public PlayButtonView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        init(attrs);
    }

    public PlayButtonView(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(attrs);
    }

    private void init(AttributeSet set) {

        TypedArray ta = getContext().obtainStyledAttributes(set, R.styleable.PlayButtonView);
        playingDrawable = ta.getDrawable(R.styleable.PlayButtonView_PlayButtonView_stopDrawable);
        stoppedDrawable = ta.getDrawable(R.styleable.PlayButtonView_PlayButtonView_playDrawable);
        setImageDrawable(stoppedDrawable);

        gestureDetector = new GestureDetectorCompat(getContext(), new GestureDetector.SimpleOnGestureListener(){
            @Override
            public boolean onDown(MotionEvent e) {
                return true;
            }

            @Override
            public boolean onSingleTapUp(MotionEvent e) {
                listener.onPlayButtonClicked(PlayButtonView.this);
                return super.onSingleTapUp(e);
            }
        });

    }

    public void setEnabled(boolean shouldEnable) {
        isEnabled = shouldEnable;
        if (isEnabled)
            setImageDrawable(playingDrawable);
        else
            setImageDrawable(stoppedDrawable);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return gestureDetector.onTouchEvent(event);
    }



    interface PlayButtonListener {
        void onPlayButtonClicked(PlayButtonView playButtonView);
    }
}
