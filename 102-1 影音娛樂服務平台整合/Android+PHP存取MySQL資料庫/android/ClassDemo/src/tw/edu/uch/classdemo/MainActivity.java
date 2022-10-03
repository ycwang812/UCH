package tw.edu.uch.classdemo;

import java.util.ArrayList;
import java.util.List;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.protocol.HTTP;
import org.apache.http.util.EntityUtils;
import org.json.JSONArray;
import org.json.JSONObject;
import android.os.Bundle;
import android.os.StrictMode;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
	
	private String url = "http://192.168.0.186/";
	
	@SuppressLint("NewApi")
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
		StrictMode.setThreadPolicy(policy);
		
		final EditText name = (EditText) findViewById(R.id.name);
		final EditText number = (EditText) findViewById(R.id.number);
		final TextView output = (TextView) findViewById(R.id.output);
		
		Button claerBtn = (Button) findViewById(R.id.clearBtn);
		claerBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				name.setText("");
				number.setText("");
				output.setText("");
			}
		});
		
		Button saveBtn = (Button) findViewById(R.id.saveBtn);
		saveBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				try {
					List<NameValuePair> params = new ArrayList<NameValuePair>();
					params.add(new BasicNameValuePair("name", name.getText().toString()));
					params.add(new BasicNameValuePair("number", number.getText().toString()));
					
					HttpPost post = new HttpPost(url + "test/androidSave.php");
					post.setEntity(new UrlEncodedFormEntity(params, HTTP.UTF_8));
					HttpResponse response = new DefaultHttpClient().execute(post);
					
					if (response.getStatusLine( ).getStatusCode( ) == 200) {
						Toast.makeText(MainActivity.this, "Save successful!", Toast.LENGTH_SHORT).show();
					}
				} catch (Exception e) {
					Log.e("Save error!", e.getMessage());
					Toast.makeText(MainActivity.this, "Save error!", Toast.LENGTH_SHORT).show();
				}
			}
		});
		
		Button queryBtn = (Button) findViewById(R.id.queryBtn);
		queryBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
			    try {
					HttpResponse response = new DefaultHttpClient().execute(new HttpGet(url + "test/androidQuery.php"));

					if (response.getStatusLine( ).getStatusCode( ) == 200) {
						String json = EntityUtils.toString(response.getEntity());
						JSONObject responseJson = new JSONObject(json);
						JSONArray array = responseJson.getJSONArray("class");
						
						StringBuilder sb = new StringBuilder();
						sb.append("姓名\t學號\n");
						
						for (int i = 0; i < array.length(); i++) {
			                JSONObject object = array.getJSONObject(i);
			                
			                sb.append(object.getString("name")).append("\t");
			                sb.append(object.getString("number")).append("\n");
			            }
						
						output.setText(sb.toString());
					}
				} catch (Exception e) {
					Log.e("Query error!", e.getMessage());
					Toast.makeText(MainActivity.this, "Query error!", Toast.LENGTH_SHORT).show();
				}
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
