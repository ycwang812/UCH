package com.example.recorddemo;

import java.io.File;

import android.media.MediaRecorder;
import android.os.Bundle;
import android.os.Environment;
import android.app.Activity;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

	private MediaRecorder recorder;
    private Button startBtn, stopBtn;
    private TextView output;
    private File path;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		// 取得Button元件
		startBtn = (Button) findViewById(R.id.startBtn);
		startBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				output.setText("開始錄音....");
				
		    	try {
		    		recorder.start(); // 開始錄音
		    		
		    		// 設定按鈕狀態
		    		startBtn.setEnabled(false);
		    		stopBtn.setEnabled(true);    		
		    	} catch (Exception ex) {
		    		Log.d("RecordDemo", "startBtnClick: " + ex.getMessage());
		    	}
			}
		});
		
		stopBtn = (Button) findViewById(R.id.stopBtn);
		stopBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				output.setText("停止錄音....");
				
		    	recorder.stop(); // 停止錄音
				// 設定按鈕狀態
		    	startBtn.setEnabled(true);
		    	stopBtn.setEnabled(false); 
			}
		});
		
		output = (TextView) findViewById(R.id.output);
		recorder = new MediaRecorder();
		path = new File(Environment.getExternalStorageDirectory(), "myrecord.3gp");
		
		resetRecorder();
	}
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		recorder.release();
	}
	
	// 重設錄音機
	private void resetRecorder() {
		recorder.setAudioSource(MediaRecorder.AudioSource.MIC);
		recorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
		recorder.setAudioEncoder(MediaRecorder.AudioEncoder.DEFAULT);
		recorder.setOutputFile(path.getAbsolutePath());
		
		try {
			recorder.prepare();
			output.setText("錄音程序準備完成....");
			startBtn.setEnabled(true);
		} catch (Exception ex) {
			Log.d("RecordDemo", "resetRecorder: " + ex.getMessage());
		}
	}

}
