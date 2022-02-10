package com.johnkasun.patch_matcher;

import android.content.Context;
import android.os.Parcel;
import android.os.Parcelable;
import android.util.AttributeSet;

import androidx.annotation.Nullable;

public class Connectable extends androidx.appcompat.widget.AppCompatImageButton{

    protected int identifier = -1;

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
