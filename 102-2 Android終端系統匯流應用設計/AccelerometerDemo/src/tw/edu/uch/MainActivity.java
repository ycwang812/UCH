package tw.edu.uch;

import java.util.List;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;
import android.app.Activity;
import android.content.Context;

public class MainActivity extends Activity {
	
	private SensorManager sensorManager;
	private boolean accelerometerPresent;
	private Sensor accelerometerSensor;
	private TextView textInfo, textX, textY, textZ;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		textInfo = (TextView) findViewById(R.id.info);
		textX = (TextView) findViewById(R.id.textx);
		textY = (TextView) findViewById(R.id.texty);
		textZ = (TextView) findViewById(R.id.textz);

		sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		List<Sensor> sensorList = sensorManager.getSensorList(Sensor.TYPE_ACCELEROMETER);

		if (sensorList.size() > 0) {
			accelerometerPresent = true;
			accelerometerSensor = sensorList.get(0);
	       
			StringBuilder sb = new StringBuilder();
			sb.append("Name: ").append(accelerometerSensor.getName()).append("\n");
			sb.append("Version: ").append(accelerometerSensor.getVersion()).append("\n");
			sb.append("Vendor: ").append(accelerometerSensor.getVendor()).append("\n");
			sb.append("Type: ").append(accelerometerSensor.getType()).append("\n");
			sb.append("Max: ").append(accelerometerSensor.getMaximumRange()).append("\n");
			sb.append("Resolution: ").append(accelerometerSensor.getResolution()).append("\n");
			sb.append("Power: ").append(accelerometerSensor.getPower()).append("\n");
			sb.append("Class: ").append(accelerometerSensor.getClass().toString());
			textInfo.setText("tets");
			textInfo.setText(sb.toString());
		} else {
			accelerometerPresent = false;
		}
	}
	
	@Override
	protected void onResume() {
		super.onResume();

		if (accelerometerPresent) {
			sensorManager.registerListener(accelerometerListener, accelerometerSensor, SensorManager.SENSOR_DELAY_NORMAL);
			Toast.makeText(this, "Register accelerometerListener", Toast.LENGTH_LONG).show();
		}
	}

	@Override
	protected void onStop() {
		super.onStop();
		
		if (accelerometerPresent) {
			sensorManager.unregisterListener(accelerometerListener);
			Toast.makeText(this, "Unregister accelerometerListener", Toast.LENGTH_LONG).show();
		}
	}
	
	private SensorEventListener accelerometerListener = new SensorEventListener() {

		@Override
		public void onAccuracyChanged(Sensor arg0, int arg1) {
		}

		@Override
		public void onSensorChanged(SensorEvent event) {
			textX.setText(String.valueOf(event.values[0]));
			textY.setText(String.valueOf(event.values[1]));
			textZ.setText(String.valueOf(event.values[2]));
		}
		
	};

}
