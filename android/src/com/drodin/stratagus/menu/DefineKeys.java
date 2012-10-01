package com.drodin.stratagus.menu;

import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

import com.drodin.stratagus.R;

public class DefineKeys extends ListActivity {

	private int sdlKeyCode = 0;

	@Override
	public void onCreate(Bundle icicle) {
		super.onCreate(icicle);

		drawListAdapter();

	}

	private void drawListAdapter() {
		final Context context = this;

		ArrayAdapter<String> keyLabelsAdapter = new ArrayAdapter<String>(
				this, android.R.layout.simple_list_item_1, sdlKeys) {
			@Override
			public View getView(final int position, final View convertView, final ViewGroup parent) {
				return new Modified(context, getItem(position), position);
			}
		};

		setListAdapter(keyLabelsAdapter);		
	}

	@Override
	public void onListItemClick(ListView parent, View v, int position, long id) {
		sdlKeyCode = position;
		startActivityForResult(new Intent(this, KeySelect.class).putExtra("sdlKeyCode", sdlKeyCode), 0);
	}

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (resultCode == RESULT_OK && requestCode == 0) {
			int androidKeyCode = data.getIntExtra("androidKeyCode", 0);
			if (androidKeyCode!=KeyEvent.KEYCODE_MENU) {
				for (int i=0; i<definiedKeys.length; i++)
					if (definiedKeys[i] == sdlKeyCode)
						definiedKeys[i] = 0;
				if (androidKeyCode!=0)
					definiedKeys[androidKeyCode] = sdlKeyCode;
			}
			drawListAdapter();
		}
	}

	class Modified extends LinearLayout {

		public Modified(final Context context, final String keyLabel, final int position) {
			super(context);

			if (keyLabel!=null) { 

				setOrientation(HORIZONTAL);

				final TextView textView = new TextView(context);
				textView.setTextAppearance(context, R.style.ListText);

				final TextView textView2 = new TextView(context);
				textView2.setTextAppearance(context, R.style.ListTextSmall);

				textView.setText(keyLabel);
				textView.setPadding(10, 0, 0, 0);

				textView2.setText("?");
				for (int i=1; i<definiedKeys.length; i++)
					if (definiedKeys[i]==position) {
						textView2.setText("ANDROID_" + androidKeys[i]);
						continue;
					}
				textView2.setGravity(Gravity.RIGHT);
				textView2.setPadding(0, 0, 10, 0);

				addView(textView, new LinearLayout.LayoutParams(
						LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
				addView(textView2, new LinearLayout.LayoutParams(
						LayoutParams.FILL_PARENT, LayoutParams.WRAP_CONTENT));

			} else {

				final View hiddenView = new View(context);
				hiddenView.setVisibility(INVISIBLE);
				addView(hiddenView, new LinearLayout.LayoutParams(0,0));

			}

		}

	}

	public static final String[] androidKeys = {
		"UNKNOWN", "SOFT_LEFT", "SOFT_RIGHT", "HOME", "BACK", "CALL", "ENDCALL",
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		"STAR", "POUND", "DPAD_UP", "DPAD_DOWN", "DPAD_LEFT", "DPAD_RIGHT",
		"DPAD_CENTER", "VOLUME_UP", "VOLUME_DOWN", "POWER", "CAMERA", "CLEAR",
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
		"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
		"COMMA", "PERIOD", "ALT_LEFT", "ALT_RIGHT", "SHIFT_LEFT", "SHIFT_RIGHT",
		"TAB", "SPACE", "SYM", "EXPLORER", "ENVELOPE", "ENTER", "DEL", "GRAVE",
		"MINUS", "EQUALS", "LEFT_BRACKET", "RIGHT_BRACKET", "BACKSLASH", "SEMICOLON",
		"APOSTROPHE", "SLASH", "AT", "NUM", "HEADSETHOOK", "FOCUS", "PLUS", "MENU",
		"NOTIFICATION", "SEARCH", "MEDIA_PLAY_PAUSE", "MEDIA_STOP", "MEDIA_NEXT",
		"MEDIA_PREVIOUS", "MEDIA_REWIND", "MEDIA_FAST_FORWARD", "MUTE"
	};

	public static final String[] sdlKeys = {
		null, "F1", "F2", "HOME", "ESCAPE", "MOUSE MIDDLE", "MOUSE RIGHT",
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		"GRAY *", "GRAY /", "UP", "DOWN", "LEFT", "RIGHT",
		"PAUSE", "PAGE UP", "PAGE DOWN", "END", "PRINT SCREEN", "DELETE",
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
		"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
		",", ".", "LEFT ALT", "RIGHT ALT", "LEFT SHIFT", "RIGHT SHIFT",
		"TAB", "SPACE", "CAPS LOCK", "F3", "F4", "ENTER", "BACKSPACE", "`",
		"-", "=", "[", "]", "\\", ";",
		"'", "/", "INSERT", "NUM LOCK", "GRAY -", "F12", "+", null,
		"GRAY +", "SPECIAL", "F5", "F6", "F7",
		"F8", "F9", "F10", "F11"
	};

	public static int sdlMouseMiddle = 5;
	public static int sdlMouseRight = 6;

	public static int[] definiedKeys = new int[androidKeys.length];

	public static void defaultDefinedKeys() {
		for (int i=0;i<androidKeys.length;i++)
			definiedKeys[i]=i;
	}

	public static void saveDefinedKeys(SharedPreferences settings) {
		SharedPreferences.Editor editor = settings.edit();
		String definedKeysStr = "";
		for (int i=0; i<definiedKeys.length; i++)
			definedKeysStr += i+":"+definiedKeys[i]+";";
		editor.putString("definedKeys", definedKeysStr);
		editor.commit();
	}

	public static void loadDefinedKeys(SharedPreferences settings) {
		final String definedKeysStr = settings.getString("definedKeys", "");
		if (definedKeysStr.contains(";")) {
			final String[] keyPairs = definedKeysStr.split(";");
			for (int i=0; i<keyPairs.length; i++)
				definiedKeys[Integer.parseInt(keyPairs[i].split(":")[0])]
				                        = Integer.parseInt(keyPairs[i].split(":")[1]);
		} else {
			defaultDefinedKeys();
		}
	}

}

