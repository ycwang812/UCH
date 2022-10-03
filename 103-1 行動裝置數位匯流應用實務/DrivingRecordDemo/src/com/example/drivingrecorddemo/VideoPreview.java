package com.example.drivingrecorddemo;

import android.content.Context;
import android.media.MediaRecorder;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView;

public class VideoPreview extends SurfaceView implements Callback {

	private SurfaceHolder holder;
	private MediaRecorder recorder;

	public VideoPreview(Context context, MediaRecorder recorder) {
		super(context);
		
		this.recorder = recorder;
		
		holder = getHolder();
		holder.addCallback(this);
		holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
	}

	public Surface getSurface() {
		return holder.getSurface();
	}

	// 實作SurfaceHolder.Callback介面方法
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		// 指定輸出檔案路徑
		recorder.setOutputFile("/sdcard/myVideo.3gp");
		// 指定預覽檢視
		recorder.setPreviewDisplay(holder.getSurface());
		
		try {
			recorder.prepare(); // 準備錄影
		} catch (Exception e) {
			Log.e("DrivingRecordDemo", e.getMessage());
			recorder.release();
			recorder = null;
		}
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		if (recorder != null) {
			// 釋放MediaRecorder物件佔用的資源
			recorder.release();
			recorder = null;
		}
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
	}

}
