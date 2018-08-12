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

package com.drodin.stratagus;

import android.content.Context;
import android.inputmethodservice.Keyboard;
import android.inputmethodservice.KeyboardView;
import android.util.AttributeSet;
import android.view.KeyEvent;


public class SoftControls extends KeyboardView implements KeyboardView.OnKeyboardActionListener {

	public Keyboard mControl;

	public SoftControls(Context context, AttributeSet attr) {
		super(context, attr);

		setPreviewEnabled(false);

		setOnKeyboardActionListener(this);

		mControl = new Keyboard(getContext(), R.drawable.keyboard);

		setKeyboard(mControl);

	}

	public void onKey(int primaryCode, int[] keyCodes) {
	}

	public void onPress(final int primaryCode) {
		MainView.keyQueue.add(new MainView.KeyState(KeyEvent.ACTION_DOWN, primaryCode));
	}

	public void onRelease(final int primaryCode) {
		MainView.keyQueue.add(new MainView.KeyState(KeyEvent.ACTION_UP, primaryCode));
		if (primaryCode==KeyEvent.KEYCODE_ENTER)
			MainActivity.switchKeyboard();
	}

	public void onText(CharSequence text) {
	}

	@Override
	public void swipeDown() {
	}

	@Override
	public void swipeLeft() {
	}

	@Override
	public void swipeRight() {
	}

	@Override
	public void swipeUp() {
	}


}
