package com.example.drivingrecorddemo;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.net.Uri;
import android.os.Bundle;
import android.view.Window;
import android.widget.MediaController;
import android.widget.VideoView;

public class VideoPlayer extends Activity {

	private VideoView videoView;

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		// 沒有標題文字
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		
		// 橫向顯示
		setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
		setContentView(R.layout.videoplayer);
		
		// 取得VideoView元件
		videoView = (VideoView) this.findViewById(R.id.video);
		
		// 建立MediaController物件
		MediaController mc = new MediaController(this);
		
		videoView.setMediaController(mc); // 指定控制物件
		// 指定媒體檔案的播放路徑的URI
		videoView.setVideoURI(Uri.parse("/sdcard/myVideo.3gp"));
		// 指定元件取得焦點
		videoView.requestFocus();
	}

}
