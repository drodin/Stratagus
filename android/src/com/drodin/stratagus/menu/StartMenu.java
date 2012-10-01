package com.drodin.stratagus.menu;

import java.io.File;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ToggleButton;

import com.drodin.stratagus.MainActivity;
import com.drodin.stratagus.R;

public class StartMenu extends Activity {

	private EditText mFolder = null;
	private String folder = "/sdcard/data.wc2/";
	private String stratagusScript = "/scripts/stratagus.lua";
	private SharedPreferences settings;
	private boolean antialiasing = false; 

	@Override
	public void onCreate(Bundle icicle) {
		super.onCreate(icicle);

		settings = PreferenceManager.getDefaultSharedPreferences(this);
		DefineKeys.loadDefinedKeys(settings);

		antialiasing = settings.getBoolean("antialiasing", false);
		
		folder = settings.getString("dataDir", folder);

		setContentView(R.layout.start_menu);

		mFolder = (EditText)findViewById(R.id.folder);
		mFolder.setText((CharSequence)folder);

		((Button)findViewById(R.id.start_btn)).setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				folder = mFolder.getText().toString();
				File scriptFile = new File(folder + stratagusScript);
				if (scriptFile.exists()) {
					SharedPreferences.Editor editor = settings.edit();
					editor.putString("dataDir", folder);
					editor.commit();
					startActivity(new Intent(v.getContext(), MainActivity.class));
					finish();
				} else {
					new AlertDialog.Builder(v.getContext())
					.setMessage(getString(R.string.nodatadir_msg) + "\n" + folder)
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

		((Button)findViewById(R.id.browse_btn)).setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				folder = mFolder.getText().toString();
				startActivityForResult(new Intent(v.getContext(), ChooseFolder.class).putExtra("startDir", folder), 3);
			}
		});

		((Button)findViewById(R.id.define_keys_btn)).setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				startActivityForResult(new Intent(v.getContext(), DefineKeys.class), 1);
			}
		});

		((Button)findViewById(R.id.reset_keys_btn)).setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				startActivityForResult(new Intent(v.getContext(), Sure.class).putExtra("title", getString(R.string.reset_keys_title)), 2);
			}
		});

		final ToggleButton mAntialiasingButton = (ToggleButton)findViewById(R.id.antialiasing_btn);
		mAntialiasingButton.setChecked(antialiasing);
		mAntialiasingButton.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				antialiasing = !antialiasing;
				SharedPreferences.Editor editor = settings.edit();
				editor.putBoolean("antialiasing", antialiasing);
				editor.commit();
			}
		});

	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (resultCode == RESULT_OK && requestCode == 0) {
			setResult(RESULT_OK, data);
		} 
		else if (requestCode == 1) {
			DefineKeys.saveDefinedKeys(settings);
		}
		else if (resultCode == RESULT_OK && requestCode == 2) {
			DefineKeys.defaultDefinedKeys();
			DefineKeys.saveDefinedKeys(settings);
		}
		else if (resultCode == RESULT_OK && requestCode == 3) {
			final String selectedFolder = data.getStringExtra("selectedFolder");
			if (selectedFolder != null) {
				folder = selectedFolder;
				mFolder.setText((CharSequence)folder);
			}
		}
	}

}
