package com.drodin.stratagus;

import android.os.Build;
import android.view.Display;
import android.graphics.Point;

import org.libsdl.app.SDLActivity;

import java.io.File;
import java.util.ArrayList;

public class MySDLActivity extends SDLActivity {
    final int scaledHeight = 512;

    @Override
    protected String[] getLibraries() {
        return new String[] {
                "stratagus"
        };
    }

    @Override
    protected String[] getArguments() {
        String dataDir = getIntent().getStringExtra("dataDir");
        if (dataDir == null || dataDir.isEmpty()) {
            ArrayList<File> dataDirs = FileUtils.findRecursive(getFilesDir(), StartMenu.scriptName);
            if (!dataDirs.isEmpty())
                dataDir = dataDirs.get(0).getPath();
            else
                finish();
        }

        boolean scaled = getIntent().getBooleanExtra("scaled", true);

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
                "-u",
                getFilesDir().getPath(),
                "-v",
                videoMode,
                "-F" // Full screen video mode
        };
    }
}
