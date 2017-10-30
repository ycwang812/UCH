package tw.edu.uch;

import android.support.v7.app.ActionBarActivity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends ActionBarActivity {
	
	private TextView output;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        output = (TextView) findViewById(R.id.output);
    }

    public void startOnClick(View view) {
    	Intent intent = new Intent(MainActivity.this, MusicService.class);
    	intent.putExtra("ISPAUSE", false);
    	
    	startService(intent);
    	output.setText("音樂播放中...");
    }
    
    public void pauseOnClick(View view) {
    	Intent intent = new Intent(MainActivity.this, MusicService.class);
    	intent.putExtra("ISPAUSE", true);
    	
    	startService(intent);
    	output.setText("音樂暫停...");
    }

    public void stopOnClick(View view) {
    	Intent intent = new Intent(MainActivity.this, MusicService.class);
    	
    	stopService(intent);
    	output.setText("音樂停止...");
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
