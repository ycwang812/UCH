package com.example.smartcamdemo;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Bitmap.CompressFormat;
import android.hardware.Camera;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.widget.TextView;

public class MainActivity extends Activity implements SurfaceHolder.Callback, OnClickListener {

	private Camera camera;
	private boolean isPreviewRunning = false;
	private SurfaceView surfaceview;
	private SurfaceHolder surfaceHolder;
	private SensorManager manager;
	private Sensor accelerometer;
	private MySensorListener mListener;
	private TextView output;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		setContentView(R.layout.activity_main);
		
		// 取得SurfaceView元件
		surfaceview = (SurfaceView) findViewById(R.id.cameraview);
		surfaceview.setOnClickListener(this);
		
		surfaceHolder = surfaceview.getHolder();
		surfaceHolder.addCallback(this);
		surfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		
		// 取得感測器的系統服務
		manager = (SensorManager) getSystemService(SENSOR_SERVICE);
		
		// 使用加速感測器
		accelerometer = manager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		
		mListener = new MySensorListener();
		
		// 取得TextView元件
		output = (TextView) findViewById(R.id.output);
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		manager.registerListener(mListener, accelerometer, SensorManager.SENSOR_DELAY_UI);
	}

	@Override
	protected void onPause() {
		super.onPause();
		manager.unregisterListener(mListener);
	}

	@Override
	protected void onStop() {
		manager.unregisterListener(mListener);
		super.onStop();
	}

	// 建立PictureCallback物件
	private Camera.PictureCallback pictureCallback = new Camera.PictureCallback() {
		
		public void onPictureTaken(byte[] imageData, Camera c) {
			if (imageData != null) {
				saveImage(MainActivity.this, imageData, 50);
				// 相片預覽
				camera.startPreview();
			}
		}
	};

	// 實作SurfaceHolder.Callback介面方法
	public void surfaceCreated(SurfaceHolder holder) {
		camera = Camera.open();
	}

	public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
		if (isPreviewRunning) {
			camera.stopPreview(); // 停止預覽
		}
		
		Camera.Parameters p = camera.getParameters();
		p.setPreviewSize(w, h);
		
		camera.setParameters(p);
		
		try {
			camera.setPreviewDisplay(holder);
		} catch (IOException e) {
			Log.e("SmartCamDemo", e.getMessage());
		}
		
		camera.startPreview();
		
		isPreviewRunning = true;
	}

	public void surfaceDestroyed(SurfaceHolder holder) {
		camera.stopPreview();
		isPreviewRunning = false;
		camera.release();
	}

	// 實作OnClickListener介面方法
	public void onClick(View arg0) {
		camera.takePicture(null, pictureCallback, pictureCallback);
	}

	// 儲存JPEG格式的圖片
	public Bitmap saveImage(Context mContext, byte[] imageData, int quality) {
		// 建立File物件的儲存路徑
		File path = new File("/sdcard");
		Bitmap image = null;
		
		try {
			BitmapFactory.Options options = new BitmapFactory.Options();
			options.inSampleSize = 5;
			
			image = BitmapFactory.decodeByteArray(imageData, 0, imageData.length, options);
			
			FileOutputStream fos = new FileOutputStream(path.toString() + "/picture.jpg");
			
			BufferedOutputStream bos = new BufferedOutputStream(fos);
			
			// 圖檔格式JPEG
			image.compress(CompressFormat.JPEG, quality, bos);
			bos.flush();
			bos.close();
		} catch (Exception e) {
			Log.e("SmartCamDemo", e.getMessage());
		}
		
		return image;
	}

	// 實作SensorEventListener介面的類別
	private class MySensorListener implements SensorEventListener {
		
		@Override
		public void onSensorChanged(SensorEvent event) {
			if (event.sensor != accelerometer) {
				return;
			}
			
			if (event.values[0] > 9.4 || event.values[1] > 9.4) {
				output.setText("相機是正的..");
			} else {
				output.setText("相機是歪的..");
			}
		}

		@Override
		public void onAccuracyChanged(Sensor sensor, int accuracy) {
		}
	}

}
