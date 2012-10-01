package com.drodin.stratagus;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.os.Build;
import android.util.Log;
import android.view.SurfaceHolder;

public class NativeThread extends Thread {

	static {
		if (Build.VERSION.SDK_INT < Build.VERSION_CODES.FROYO)
			System.loadLibrary("jnigraphics");
		System.loadLibrary("application");
	}
	public static native void nativeThread(String dataDir, Bitmap  bitmap);

	private static SurfaceHolder myThreadSurfaceHolder;

	public NativeThread(SurfaceHolder surfaceHolder) {
		myThreadSurfaceHolder = surfaceHolder;
	}

	//static long oldtime;
	public static void blitBitmap() {
		if (myThreadRun){
			Canvas canvas = null;
			try {
				canvas = myThreadSurfaceHolder.lockCanvas();
				synchronized (myThreadSurfaceHolder) {
					if (MainView.needScale)
						canvas.drawBitmap(MainView.mBitmap, MainView.sRect, MainView.dRect, MainView.mPaint);
					else
						canvas.drawBitmap(MainView.mBitmap, 0, 0, null);
				}
			} finally {
				if (canvas != null) {
					myThreadSurfaceHolder.unlockCanvasAndPost(canvas);
				}
			}
		}
		//Log.i("Stratagus", "fps: "+1000/(oldtime-SystemClock.currentThreadTimeMillis()));
		//oldtime = SystemClock.currentThreadTimeMillis();
	}

	public static int getKey() {
		if (MainView.keyQueue.size()!=0)
			return MainView.keyQueue.remove(0).state;
		else
			return -1;
	}

	public static int getTouch() {
		if (MainView.touchQueue.size()!=0)
			return MainView.touchQueue.remove(0).state;
		else
			return -1;
	}

	private static boolean myThreadRun = false;
	private static boolean myNativeRun = false;

	public void setRunning(boolean b) {
		myThreadRun = b;
	}

	public boolean isNativeRunning() {
		return myNativeRun;
	}

	@Override
	public void run() {
		myNativeRun = true;
		nativeThread(MainActivity.dataDir, MainView.mBitmap);
		Log.i("Stratagus", "Native Exit");
		System.gc();
		System.exit(0);
	}

}
