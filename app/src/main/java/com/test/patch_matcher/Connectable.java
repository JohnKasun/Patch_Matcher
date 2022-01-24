package com.test.patch_matcher;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;

import androidx.annotation.Nullable;

public class Connectable extends androidx.appcompat.widget.AppCompatImageButton {

    protected int identifier;

    public Connectable(Context context) {
        super(context);
    }

    public Connectable(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public Connectable(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public int getIdentifier() {
        return identifier;
    }

}
