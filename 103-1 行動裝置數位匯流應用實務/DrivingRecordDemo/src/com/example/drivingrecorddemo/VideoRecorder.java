package com.example.drivingrecorddemo;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

public class VideoRecorder extends Activity {

	// 宣告MediaRecorder和Preview物件變數
	private MediaRecorder recorder;
	private VideoPreview preview;
	// 是否是錄影中
	private boolean isRecording = false;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		// 建立MediaRecorder物件
		recorder = new MediaRecorder();
		// 指定錄影的參數
		recorder.setVideoSource(MediaRecorder.VideoSource.DEFAULT);
		recorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
		recorder.setVideoEncoder(MediaRecorder.VideoEncoder.MPEG_4_SP);
		
		// 建立錄影預覽的VideoPreview物件
		preview = new VideoPreview(this, recorder);
		
		// 橫向顯示
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		setContentView(preview); // 指定活動的使用介面
	}

	// 建立選項選單
	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {
		super.onPrepareOptionsMenu(menu);
		
		menu.clear();
		
		// 新增選項
		menu.add(0, 0, 0, "開始錄影");
		menu.add(1, 1, 0, "停止錄影");
		
		// 預設指定選項為不可見
		menu.setGroupVisible(0, false);
		menu.setGroupVisible(1, false);
		
		if (isRecording == false) {
			menu.setGroupVisible(0, true); // 開始錄影
		} else {
			menu.setGroupVisible(1, true); // 停止錄影
		}
		
		return true;
	}

	// 處理選項選單的選項
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
			case 0: // 開始錄影
				recorder.start();
				isRecording = true;
				break;
			case 1: // 停止錄影
				recorder.stop();
				// 釋放MediaRecorder物件佔用的資源
				recorder.release();
				recorder = null;
				isRecording = false;
				break;
		}
		
		return super.onOptionsItemSelected(item);
	}

}
