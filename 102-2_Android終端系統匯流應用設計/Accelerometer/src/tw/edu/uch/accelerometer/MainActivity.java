package tw.edu.uch.accelerometer;

import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Toast;
import android.app.Activity;

public class MainActivity extends Activity implements SensorEventListener {

	private SensorManager sensorManager;
	private boolean color = false;
	private View view;
	private long lastUpdate;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		view = findViewById(R.id.textView);
		view.setBackgroundColor(Color.GREEN);

		sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
		lastUpdate = System.currentTimeMillis();
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		// register this class as a listener for the orientation and
		// accelerometer sensors
		sensorManager.registerListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_NORMAL);
	}

	@Override
	protected void onPause() {
		// unregister listener
		super.onPause();
		sensorManager.unregisterListener(this);
	}

	@Override
	public void onSensorChanged(SensorEvent event) {
		if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
			getAccelerometer(event);
		}
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
	}
	
	private void getAccelerometer(SensorEvent event) {
		float[] values = event.values;
		// Movement
		float x = values[0];
		float y = values[1];
		float z = values[2];

		float accelationSquareRoot = (x * x + y * y + z * z) / (SensorManager.GRAVITY_EARTH * SensorManager.GRAVITY_EARTH);
		long actualTime = System.currentTimeMillis();
		
		if (accelationSquareRoot >= 2) {
			if (actualTime - lastUpdate < 200) {
				return;
			}
			
			lastUpdate = actualTime;
			Toast.makeText(this, "Device was shuffed", Toast.LENGTH_SHORT).show();
			
			if (color) {
				view.setBackgroundColor(Color.GREEN);

			} else {
				view.setBackgroundColor(Color.RED);
			}
			
			color = !color;
		}
	}

}
