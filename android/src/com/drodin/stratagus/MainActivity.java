package com.drodin.stratagus;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.WindowManager;
import android.widget.FrameLayout;

import com.drodin.stratagus.menu.DefineKeys;
import com.drodin.stratagus.menu.Sure;

public class MainActivity extends Activity{
	
	private static FrameLayout mFrameLayout = null;

	public static boolean onScreenKeyboard = false;
	public static View mControlsView = null;
	public static SoftControls mSoftControls = null;
	
	public MainView mMainView = null;
	public SharedPreferences settings;
	
	public static String dataDir = "/sdcard/Stratagus";

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		getWindow().setFlags(
				WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS, 
				WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS); 

		getWindow().setFlags(
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
				WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		settings = PreferenceManager.getDefaultSharedPreferences(this);
		
		dataDir = settings.getString("dataDir", dataDir);

		DefineKeys.loadDefinedKeys(settings);
		
		mFrameLayout = new FrameLayout(getApplicationContext());
		
		mControlsView = getLayoutInflater().inflate(R.layout.controls, null);
		mSoftControls = (SoftControls) mControlsView.findViewById(R.id.keyboardView);
		
		mControlsView.setVisibility(View.INVISIBLE);

		mMainView = new MainView(this);
		mMainView.antialiasing = settings.getBoolean("antialiasing", false);
		
		mFrameLayout.addView(mMainView,
				new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
		mFrameLayout.addView(mControlsView,
				new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));

		setContentView(mFrameLayout,
				new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
	}

	@Override
	protected void onResume() {
		mMainView.onResume();
		super.onResume();
	}

	@Override
	protected void onPause() {
		mMainView.onPause();
		super.onPause();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.main_menu, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle item selection
		switch (item.getItemId()) {
		case R.id.antialiasing:
			if (mMainView!=null && MainView.needScale) {
				mMainView.switchAntialiasing();
			}
			SharedPreferences.Editor editor = settings.edit();
			editor.putBoolean("antialiasing", mMainView.antialiasing);
			editor.commit();
			return true;
		case R.id.define_keys:
			if (mMainView!=null) {
				startActivityForResult(new Intent(this, DefineKeys.class), 1);
			}
			return true;
		case R.id.reset_keys:
			if (mMainView!=null) {
				startActivityForResult(new Intent(this, Sure.class).putExtra("title", getString(R.string.reset_keys_title)), 2);
			}
			return true;
		case R.id.keyboard:
			if (mMainView!=null && mControlsView!=null) {
				switchKeyboard();
			}
		default:
			return super.onOptionsItemSelected(item);
		}
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
	}
	
	public static void switchKeyboard() {
		if (onScreenKeyboard) {
			mControlsView.setVisibility(View.INVISIBLE);
			onScreenKeyboard = false;
		} else {
			mControlsView.setVisibility(View.VISIBLE);
			onScreenKeyboard = true;
		}
	}
	
}
