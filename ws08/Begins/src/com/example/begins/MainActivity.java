package com.example.begins;

import java.util.Calendar;

import android.app.Activity;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.view.Menu;

public class MainActivity extends Activity {

	MediaPlayer player;  
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
//        Calendar calendar=Calendar.getInstance();
// 
//        calendar.set(Calendar.YEAR,2014);
//        calendar.set(Calendar.MONTH,Calendar.JULY);//Ҳ���������֣�0-11,һ��Ϊ0
//        calendar.set(Calendar.DAY_OF_MONTH, 24);
//        calendar.set(Calendar.HOUR_OF_DAY, 11);
//        calendar.set(Calendar.MINUTE, 51);
//        calendar.set(Calendar.SECOND, 0);
        //�趨ʱ��Ϊ 2011��6��28��19��50��0��
        //c.set(2011, 05,28, 19,50, 0);
        //Ҳ����д��һ����
 
        //Intent intent=new Intent(this,AlarmReceiver.class);
        /*Intent intent = new Intent("ELITOR_CLOCK");  
        intent.putExtra("msg","��ô�����");    
        
        PendingIntent pi=PendingIntent.getBroadcast(this, 0, intent,0);
        //����һ��PendingIntent���󣬷��͹㲥            
        AlarmManager am=(AlarmManager)getSystemService(ALARM_SERVICE);*/
        //��ȡAlarmManager����
        //am.set(AlarmManager.RTC_WAKEUP, c.getTimeInMillis(), pi);
        //am.setRepeating(AlarmManager.RTC_WAKEUP,System.currentTimeMillis(),5*1000,pi);  	//�����OK��.
 
        //ʱ�䵽ʱ��ִ��PendingIntent��ִֻ��һ��
        //AlarmManager.RTC_WAKEUP����ʱ�����У������AlarmManager.RTC,������ʱ��������
        //am.setRepeating(AlarmManager.RTC_WAKEUP, c.getTimeInMillis(), 10000, pi);
        //�����Ҫ�ظ�ִ�У�ʹ������һ�е�setRepeating�����������ڶ�����Ϊ���ʱ��,��λΪ����
        
        startTiming();
    }

    //
    public void startTiming() {
    	Intent intent = new Intent(this, AlarmReceiver.class);
        
        PendingIntent pi = PendingIntent.getBroadcast(this, 0, intent, 0);
        //����һ��PendingIntent���󣬷��͹㲥            
        AlarmManager am = (AlarmManager)getSystemService(ALARM_SERVICE);
        am.setRepeating(AlarmManager.RTC_WAKEUP, System.currentTimeMillis(), 60*1000, pi);
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
