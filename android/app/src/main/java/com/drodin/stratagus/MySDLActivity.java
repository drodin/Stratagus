package com.drodin.stratagus;

import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.os.Build;
import android.view.Display;
import android.graphics.Point;

import org.libsdl.app.SDLActivity;

public class MySDLActivity extends SDLActivity {
    public static int scaledHeight = 512;

    @Override
    protected String[] getLibraries() {
        return new String[] {
                "stratagus"
        };
    }

    @Override
    protected String[] getArguments() {
        SharedPreferences settings = PreferenceManager.getDefaultSharedPreferences(this);
        String dataDir = settings.getString("dataDir", StartMenu.dataDir);
        boolean scaled = settings.getBoolean("scaled", StartMenu.scaled);

        Display display = getWindowManager().getDefaultDisplay();
        Point size = new Point();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
            display.getRealSize(size);
        } else {
            display.getSize(size);
        }
        int displayWidth = size.x;
        int displayHeight = size.y;

        String videoMode = displayWidth + "x" + displayHeight;
        if (scaled) {
            int scaledWidth = displayWidth * scaledHeight / displayHeight;
            videoMode = scaledWidth + "x" + scaledHeight;
        }

        return new String[] {
                "-d",
                dataDir,
                "-v",
                videoMode,
                "-F" // Full screen video mode
        };
    }
}
