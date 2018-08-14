package com.drodin.stratagus;

import java.io.File;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.EditText;
import android.widget.ToggleButton;

public class StartMenu extends Activity {
    public static String dataDir = "/sdcard/Stratagus";
    public static boolean scaled = true;

    String stratagusScript = "/scripts/stratagus.lua";

    SharedPreferences settings;
	EditText mFolder = null;

	@Override
	public void onCreate(Bundle icicle) {
		super.onCreate(icicle);

        settings = PreferenceManager.getDefaultSharedPreferences(this);

		scaled = settings.getBoolean("scaled", scaled);
		dataDir = settings.getString("dataDir", dataDir);

		setContentView(R.layout.start_menu);

		mFolder = findViewById(R.id.folder);
		mFolder.setText(dataDir);

		(findViewById(R.id.start_btn)).setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				dataDir = mFolder.getText().toString();
				File scriptFile = new File(dataDir + stratagusScript);
				if (scriptFile.exists()) {
					SharedPreferences.Editor editor = settings.edit();
					editor.putString("dataDir", dataDir);
					editor.commit();
					startActivity(new Intent(v.getContext(), MySDLActivity.class));
					finish();
				} else {
					new AlertDialog.Builder(v.getContext())
					.setMessage(getString(R.string.nodatadir_msg) + "\n" + dataDir)
					.setCancelable(false)
					.setPositiveButton(getString(R.string.nodatadir_btn), new DialogInterface.OnClickListener() {
						public void onClick(DialogInterface dialog, int id) {
							// Action for 'OK' Button
						}
					})
					.show();
				}
			}
		});

		(findViewById(R.id.browse_btn)).setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				dataDir = mFolder.getText().toString();
				startActivityForResult(new Intent(v.getContext(), ChooseFolder.class).putExtra("startDir", dataDir), 1);
			}
		});

		final ToggleButton mScaledButton = findViewById(R.id.scaled_btn);
		mScaledButton.setChecked(scaled);
		mScaledButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				scaled = !scaled;
				SharedPreferences.Editor editor = settings.edit();
				editor.putBoolean("scaled", scaled);
				editor.commit();
			}
		});

        if (Build.VERSION.SDK_INT >= 23 &&
                checkSelfPermission(android.Manifest.permission.WRITE_EXTERNAL_STORAGE)
                        != PackageManager.PERMISSION_GRANTED) {
            requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
        }
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (resultCode == RESULT_OK && requestCode == 0) {
			setResult(RESULT_OK, data);
		} 
		else if (resultCode == RESULT_OK && requestCode == 1) {
			final String selectedFolder = data.getStringExtra("selectedFolder");
			if (selectedFolder != null) {
				dataDir = selectedFolder;
				mFolder.setText(dataDir);
			}
		}
	}

}
