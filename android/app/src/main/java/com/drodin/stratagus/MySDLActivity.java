package com.drodin.stratagus;

import android.content.SharedPreferences;
import android.preference.PreferenceManager;

import org.libsdl.app.SDLActivity;

public class MySDLActivity extends SDLActivity {
    public static int scaledHeight = 512;

    @Override
    protected String[] getLibraries() {
        String hidapi = "hidapi";
        if (BuildConfig.DEBUG)
            hidapi += "d";
        return new String[] {
                hidapi,
                "stratagus"
        };
    }

    @Override
    protected String[] getArguments() {
        SharedPreferences settings = PreferenceManager.getDefaultSharedPreferences(this);
        String dataDir = settings.getString("dataDir", StartMenu.dataDir);
        boolean scaled = settings.getBoolean("scaled", StartMenu.scaled);

        int displayWidth = getWindowManager().getDefaultDisplay().getWidth();
        int displayHeight = getWindowManager().getDefaultDisplay().getHeight();

        String videoMode = displayWidth + "x" + displayHeight;
        if (scaled) {
            int scaledWidth = Math.round(displayWidth * scaledHeight / displayHeight);
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
