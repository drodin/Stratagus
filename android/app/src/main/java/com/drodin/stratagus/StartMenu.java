package com.drodin.stratagus;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ActivityNotFoundException;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.widget.ListView;
import android.widget.Switch;
import android.widget.TextView;

public class StartMenu extends Activity {
    final static String scriptName = "scripts/stratagus.lua";

    TextView gameDataStatus;
    GameAdapter games;

    @Override
    public void onCreate(Bundle icicle) {
        super.onCreate(icicle);

        requestWindowFeature(Window.FEATURE_NO_TITLE);

        SharedPreferences settings = getSharedPreferences("settings", MODE_PRIVATE);

        setContentView(R.layout.start_menu);
        gameDataStatus = findViewById(R.id.game_data_status);

        Switch scaled = findViewById(R.id.scaled_switch);
        scaled.setChecked(settings.getBoolean("scaled", true));

        findViewById(R.id.select_zip).setOnClickListener(v -> {
            Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
            intent.addCategory(Intent.CATEGORY_OPENABLE);
            intent.setType("application/zip");

            try {
                startActivityForResult(intent, 1);
            } catch (ActivityNotFoundException e) {
                if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.Q) {
                    intent = new Intent(this, ActionOpenDocument.class);
                    startActivityForResult(intent, 1);
                } else {
                    alertDialog(getString(R.string.no_file_manager));
                }
            }
        });

        games = new GameAdapter(this);
        ListView gamesList = findViewById(R.id.games_list);
        gamesList.setAdapter(games);
        gamesList.setOnItemClickListener((parent, view, position, id) -> {
            SharedPreferences.Editor editor = settings.edit();
            editor.putBoolean("scaled", scaled.isChecked());
            editor.apply();

            Intent intent = new Intent(this, MySDLActivity.class);
            intent.putExtra("dataDir", games.getItem(position).get("dataDir"));
            intent.putExtra("scaled", scaled.isChecked());
            startActivity(intent);
            finish();
        });
        gamesList.setOnItemLongClickListener((parent, view, position, id) -> {
            new AlertDialog.Builder(this)
                .setMessage(getString(R.string.remove_data))
                .setCancelable(true)
                .setPositiveButton(getString(android.R.string.ok), (dialog, btn_id) -> {
                    File dataDir = new File(games.getItem(position).get("dataDir"));
                    while (!dataDir.getParentFile().equals(getFilesDir()))
                        dataDir = dataDir.getParentFile();
                    FileUtils.deleteRecursive(dataDir);
                    getGames();
                    dialog.dismiss();

                })
                .setNegativeButton(getString(android.R.string.cancel), (dialog, btn_id) -> {
                    dialog.dismiss();
                })
                .show();
            return true;
        });

        getGames();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == 1 && resultCode == RESULT_OK && data != null) {
            Uri uri = data.getData();
            if (uri != null) {
                AlertDialog dialog = alertDialog(getString(R.string.extracting, ""));
                dialog.getButton(DialogInterface.BUTTON_POSITIVE).setEnabled(false);

                new Thread(() -> {
                    String subDir = FileUtils.getNameFromUri(this, uri);
                    subDir = subDir.substring(0, subDir.lastIndexOf('.'));
                    final File destDir = new File(getFilesDir(), subDir);
                    if (destDir.exists())
                        FileUtils.deleteRecursive(destDir);
                    final boolean[] hasEntry = {false};
                    FileUtils.extractArchive(this, uri, destDir, (event, message) -> runOnUiThread(() -> {
                        switch (event) {
                            case PROGRESS:
                                dialog.setMessage(getString(R.string.extracting, message));
                                if (!hasEntry[0] && message.contains(scriptName))
                                    hasEntry[0] = true;
                                break;

                            case SUCCESS:
                                if (hasEntry[0]) {
                                    getGames();
                                    dialog.setMessage(getString(R.string.extract_success));
                                } else {
                                    FileUtils.deleteRecursive(destDir);
                                    dialog.setMessage(getString(R.string.extract_no_data));
                                }
                                dialog.getButton(DialogInterface.BUTTON_POSITIVE).setEnabled(true);
                                break;

                            case FAILURE:
                                FileUtils.deleteRecursive(destDir);
                                dialog.setMessage(getString(R.string.extract_failure, message));
                                dialog.getButton(DialogInterface.BUTTON_POSITIVE).setEnabled(true);
                                break;
                        }
                    }));
                }).start();

            }
        }
    }

    protected boolean getGames() {
        games.clear();
        ArrayList<File> dataDirs = FileUtils.findRecursive (getFilesDir(), scriptName);

        if (dataDirs.isEmpty()) {
            gameDataStatus.setText(R.string.data_missing);
            return false;
        }

        for (File dataDir : dataDirs) {
            Map<String,String> gameInfo = new HashMap<>();
            gameInfo.put("dataDir", dataDir.getPath());
            try {
                BufferedReader reader = new BufferedReader(new FileReader(new File(dataDir, scriptName)));
                String line = reader.readLine();

                Pattern pattern = Pattern.compile(".*?(Name|Version).*?=.*?\"(.*?)\"");
                while (line != null) {
                    Matcher matcher = pattern.matcher(line);
                    if (matcher.find() && gameInfo.get(matcher.group(1)) == null)
                        gameInfo.put(matcher.group(1), matcher.group(2));
                    line = reader.readLine();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }

            File titlePng = new File(dataDir, "graphics/ui/title.png");
            File logoPng = new File(dataDir, "graphics/ui/logo.png");
            if (titlePng.exists())
                gameInfo.put("Icon", titlePng.getPath());
            else if (logoPng.exists())
                gameInfo.put("Icon", logoPng.getPath());

            games.add(gameInfo);
        }

        gameDataStatus.setText(R.string.data_present);
        return true;
    }

    AlertDialog alertDialog(String message) {
        return new AlertDialog.Builder(this)
                .setMessage(message)
                .setCancelable(false)
                .setPositiveButton(getString(android.R.string.ok), (dialog, btn_id) -> {
                    // Action for 'OK' Button
                })
                .show();
    }

}
