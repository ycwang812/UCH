package tw.edu.uch;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.os.Environment;
import android.os.IBinder;
import android.util.Log;

public class MusicService extends Service {

	private MediaPlayer player;
	private String musicFile = Environment.getExternalStorageDirectory().getPath() + "/Kalimba.mp3";
	private String musicUrl = "http://.Mp3";
	
	@Override
	public void onCreate() {
		player = new MediaPlayer();
		
		try {
			player.setDataSource(musicFile);

			player.setOnCompletionListener(new OnCompletionListener() {
				
				@Override
				public void onCompletion(MediaPlayer mp) {
					try {
						player.stop();
						player.prepare();
					} catch (Exception e) {
						Log.d("MusicService, onCompletion()", e.getMessage());
					}
				}
			});
			
			player.prepare();
		} catch (Exception e) {
			Log.d("MusicService, onCreate()", e.getMessage());
		}
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Boolean isPause = intent.getBooleanExtra("ISPAUSE", true);
		
		try {
			if (isPause == true) {
				if (player.isPlaying() == true) {
					player.pause();
				}
			} else {
				player.start();
			}
		} catch (Exception e) {
			Log.d("MusicService, onStartCommand()", e.getMessage());
		}
		
		return START_STICKY;
	}

	@Override
	public void onDestroy() {
		try {
			player.stop();
			player.prepare();
		} catch (Exception e) {
			Log.d("MusicService, onDestroy()", e.getMessage());
		}
	}

	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}

}
