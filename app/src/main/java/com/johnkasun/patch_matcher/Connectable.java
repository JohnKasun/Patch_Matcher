package com.johnkasun.patch_matcher;

import android.content.Context;
import android.os.Parcel;
import android.os.Parcelable;
import android.util.AttributeSet;

import androidx.annotation.Nullable;

public class Connectable extends androidx.appcompat.widget.AppCompatImageButton implements Parcelable{

    protected int identifier = -1;
    static Connectable connectableContext = null;

    public Connectable(Context context) {
        super(context);
    }

    public Connectable(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public Connectable(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    protected Connectable(Parcel in) {
        super(connectableContext.getContext());
        identifier = in.readInt();
    }

    public static final Creator<Connectable> CREATOR = new Creator<Connectable>() {
        @Override
        public Connectable createFromParcel(Parcel in) {
            return new Connectable(in);
        }

        @Override
        public Connectable[] newArray(int size) {
            return new Connectable[size];
        }
    };

    public int getIdentifier() {
        return identifier;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeInt(identifier);
    }
}
