package com.pluusystem.breakpadjavacall;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import butterknife.ButterKnife;
import butterknife.OnClick;

/**
 * Created by PLUUSYSTEM on 2015-06-11.
 */
public class MainActivity extends AppCompatActivity {

	static {
		System.loadLibrary("test_google_breakpad");
	}

	native void initNative(String path);
	native void crashService();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		ButterKnife.inject(this);

		// Save Dump Path
		initNative(getExternalCacheDir().getAbsolutePath());
	}

	@OnClick(R.id.button)
	public void clickNativeCrash() {
		crashService();
	}

}
