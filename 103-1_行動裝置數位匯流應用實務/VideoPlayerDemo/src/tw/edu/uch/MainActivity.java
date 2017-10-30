package tw.edu.uch;

import android.app.Activity;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.widget.MediaController;
import android.widget.VideoView;

public class MainActivity extends Activity {

	private String videoFile = "file:///" + Environment.getExternalStorageDirectory().getPath() + "/sample.3gp";
	private String videoUrl = "http://172.18.110.250/UCH/sample.mp4";
	private VideoView video;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		video = (VideoView) findViewById(R.id.videoView1);
		video.setVideoURI(Uri.parse(videoUrl));
		video.setMediaController(new MediaController(this));
		video.start();
	}
	
	@Override
	protected void onPause() {
		super.onPause();
		
		video.stopPlayback();
	}

}
