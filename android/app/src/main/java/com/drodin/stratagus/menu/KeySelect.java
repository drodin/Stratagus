/*

   Copyright (c) 2010 Dmitry Rodin

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

   Author contact information:

   E-mail: rodin.dmitry@gmail.com

*/

package com.drodin.stratagus.menu;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.drodin.stratagus.R;

public class KeySelect extends Activity {

	private int sdlKeyCode;

	@Override
	public void onCreate(Bundle icicle) {
		super.onCreate(icicle);

		sdlKeyCode = getIntent().getIntExtra("sdlKeyCode", 0);
		setTitle(getString(R.string.df_title, DefineKeys.sdlKeys[sdlKeyCode]));

		final TextView messageView = new TextView(this) {
			{
				setText(getString(R.string.df_message));
				setPadding(10, 0, 10, 10);
			}
		};

		final Button chancelButton = new Button(this) {
			{
				setText(R.string.df_btn_cancel);
				setOnClickListener(new View.OnClickListener() {
					public void onClick(View v) {
						setResult(RESULT_CANCELED, new Intent());
						finish();
					}
				});
			}
		};
		
		final Button clearButton = new Button(this) {
			{
				setText(R.string.df_btn_clear);
				setOnClickListener(new View.OnClickListener() {
					public void onClick(View v) {
						setResult(RESULT_OK, new Intent().putExtra("androidKeyCode",  0));
						finish();
					}
				});
			}
		};

		final View primaryView = new View(this) {
			{
				setLayoutParams(new LayoutParams(LayoutParams.FILL_PARENT, 1));
				setFocusable(true);
				setFocusableInTouchMode(true);
				requestFocus();
			}

			@Override
			public boolean onKeyPreIme (int keyCode, KeyEvent event) {
				if (event.getRepeatCount() == 0 && keyCode > 0 && keyCode < DefineKeys.androidKeys.length) {
						setResult(RESULT_OK, new Intent().putExtra("androidKeyCode", keyCode));
						finish();
						return true;
				} else
					return true;

			}
		};

		final LinearLayout parentContainer = new LinearLayout(this) {
			{
				setOrientation(LinearLayout.VERTICAL);
				addView(messageView);
				addView(chancelButton);
				addView(clearButton);
				addView(primaryView);
			}
		};

		setContentView(parentContainer, new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.WRAP_CONTENT));

	}

}
