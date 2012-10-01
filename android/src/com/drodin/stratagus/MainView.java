package com.drodin.stratagus;

import java.util.ArrayList;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.drodin.stratagus.menu.DefineKeys;

public class MainView extends SurfaceView implements SurfaceHolder.Callback{
	
	public boolean isPaused = false;

	public static boolean needScale = false;
	public static float xScale = 1.0f;
	public static float yScale = 1.0f;

	public static Rect sRect, dRect;
	public static Bitmap mBitmap;
	public static Paint mPaint;

	public Activity mMainActivity;
	private NativeThread thread;

	public boolean antialiasing = false;
	public void switchAntialiasing() {
		if (antialiasing) {
			mPaint = null;
			antialiasing = false;
		} else {
			mPaint = new Paint(Paint.FILTER_BITMAP_FLAG);
			antialiasing = true;
		}
	}

	public MainView(Activity activity) {
		super(activity);

		mMainActivity = activity;
		
		getHolder().addCallback(this);
		thread = new NativeThread(getHolder());

		setFocusable(true);
		setFocusableInTouchMode(true);
	}

	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
		Log.i("Stratagus", "surfaceChanged");

		if (!thread.isNativeRunning()) {
			if (width>=800 && height>=480)
				sRect = new Rect(0, 0, 800, 480);
			else
				sRect = new Rect(0, 0, 640, 480);

			dRect = new Rect(0, 0, width, height);

			xScale = (float)sRect.width()/dRect.width();
			yScale = (float)sRect.height()/dRect.height();

			//if (xScale>1.0f || yScale>1.0f)
			if(sRect.width() != dRect.width() || sRect.height() != dRect.height())
				needScale = true;

			mBitmap = Bitmap.createBitmap(sRect.width(), sRect.height(), Bitmap.Config.RGB_565);

			antialiasing = !antialiasing;
			switchAntialiasing();

			thread.setPriority(Thread.MAX_PRIORITY);
			thread.start();
		}
		thread.setRunning(true);
	}

	public void surfaceCreated(SurfaceHolder holder) {
		Log.i("Stratagus", "surfaceCreated");
	}

	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.i("Stratagus", "surfaceDestroyed");
		thread.setRunning(false);
	}

	public void onPause() {
		if (!isPaused) {
			keyQueue.add(new KeyState(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_CENTER));
			keyQueue.add(new KeyState(KeyEvent.ACTION_UP, KeyEvent.KEYCODE_DPAD_CENTER));
			isPaused = true;
		}
	}

	public void onResume() {
		if (isPaused) {
			keyQueue.add(new KeyState(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_CENTER));
			keyQueue.add(new KeyState(KeyEvent.ACTION_UP, KeyEvent.KEYCODE_DPAD_CENTER));
			isPaused = false;
		}
	}

	@Override
	public boolean dispatchTouchEvent(MotionEvent ev) {
		if (needScale)
			touchQueue.add(new TouchState(ev.getAction(), Math.round(ev.getX()*xScale), Math.round(ev.getY()*yScale)));
		else
			touchQueue.add(new TouchState(ev.getAction(), Math.round(ev.getX()), Math.round(ev.getY())));
		return true;
	}

	@Override
	public boolean dispatchKeyEventPreIme(KeyEvent event) {
		final int keyCode = event.getKeyCode();
		final int keyAction = event.getAction();

		if (keyCode>=DefineKeys.androidKeys.length)
			return false;

		if (keyCode == KeyEvent.KEYCODE_MENU) {
			if (keyAction == KeyEvent.ACTION_DOWN && event.getRepeatCount() == 0) {
				getKeyDispatcherState().startTracking(event, this);
				return true;
			} else if (keyAction == KeyEvent.ACTION_UP) {
				getKeyDispatcherState().handleUpEvent(event);
				if (event.isTracking() && !event.isCanceled()) {
					mMainActivity.openOptionsMenu();
					return true;
				}
			}
			return super.dispatchKeyEvent(event);
		}

		if (DefineKeys.definiedKeys[keyCode]==DefineKeys.sdlMouseMiddle) {
			castMouseBtn = 3;
			return true;
		}

		if (DefineKeys.definiedKeys[keyCode]==DefineKeys.sdlMouseRight) {
			castMouseBtn = 6;
			return true;
		}

		if (event.getRepeatCount() == 0) {
			keyQueue.add(new KeyState(keyAction, DefineKeys.definiedKeys[keyCode]));
		}
		return true;
	}

	@Override
	public boolean onKeyLongPress(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_MENU) {
			MainActivity.switchKeyboard();
			return true;
		}
		return super.onKeyLongPress(keyCode, event);
	}
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		return true;
	}
	
	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		return true;
	}

	@Override
	public boolean dispatchTrackballEvent(MotionEvent event) {
		if (event.getX()>0.0f) {
			keyQueue.add(new KeyState(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_RIGHT));
			keyQueue.add(new KeyState(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_RIGHT));
			keyQueue.add(new KeyState(KeyEvent.ACTION_UP, KeyEvent.KEYCODE_DPAD_RIGHT));
		}
		if (event.getX()<0.0f) {
			keyQueue.add(new KeyState(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_LEFT));
			keyQueue.add(new KeyState(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_LEFT));
			keyQueue.add(new KeyState(KeyEvent.ACTION_UP, KeyEvent.KEYCODE_DPAD_LEFT));			
		}
		if (event.getY()>0.0f) {
			keyQueue.add(new KeyState(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_DOWN));
			keyQueue.add(new KeyState(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_DOWN));
			keyQueue.add(new KeyState(KeyEvent.ACTION_UP, KeyEvent.KEYCODE_DPAD_DOWN));
		}
		if (event.getY()<0.0f) {
			keyQueue.add(new KeyState(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_UP));
			keyQueue.add(new KeyState(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_DPAD_UP));
			keyQueue.add(new KeyState(KeyEvent.ACTION_UP, KeyEvent.KEYCODE_DPAD_UP));			
		}
		return true;
	}

	public static int castMouseBtn = 0;
	public static ArrayList<KeyState> keyQueue = new ArrayList<KeyState>();
	public static ArrayList<TouchState> touchQueue = new ArrayList<TouchState>();

	static class KeyState {
		int state;
		public KeyState(int keyAction, int keyCode) {
			state = keyAction*1000+keyCode;
		}
	}

	static class TouchState {
		int state;
		public TouchState(int touchAction, int X, int Y) {
			state = (touchAction+castMouseBtn)*1000000+X*1000+Y;
			if (touchAction == MotionEvent.ACTION_UP)
				castMouseBtn=0;
		}
	}

}
