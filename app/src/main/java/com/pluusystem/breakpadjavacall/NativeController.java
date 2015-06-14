package com.pluusystem.breakpadjavacall;

import android.util.Log;

/**
 * Created by PLUUSYSTEM on 2015-06-11.
 */
public class NativeController {
	public static int NativeCrashCallback(String fileName) {

		Log.d("PluuSystem", "NativeCrashCallback Called");
		Log.d("PluuSystem", "Dump FileName=" + fileName);

		return 0;
	}
}
