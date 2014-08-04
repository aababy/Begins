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
//        calendar.set(Calendar.MONTH,Calendar.JULY);//也可以填数字，0-11,一月为0
//        calendar.set(Calendar.DAY_OF_MONTH, 24);
//        calendar.set(Calendar.HOUR_OF_DAY, 11);
//        calendar.set(Calendar.MINUTE, 51);
//        calendar.set(Calendar.SECOND, 0);
        //设定时间为 2011年6月28日19点50分0秒
        //c.set(2011, 05,28, 19,50, 0);
        //也可以写在一行里
 
        //Intent intent=new Intent(this,AlarmReceiver.class);
        /*Intent intent = new Intent("ELITOR_CLOCK");  
        intent.putExtra("msg","你该打酱油了");    
        
        PendingIntent pi=PendingIntent.getBroadcast(this, 0, intent,0);
        //设置一个PendingIntent对象，发送广播            
        AlarmManager am=(AlarmManager)getSystemService(ALARM_SERVICE);*/
        //获取AlarmManager对象
        //am.set(AlarmManager.RTC_WAKEUP, c.getTimeInMillis(), pi);
        //am.setRepeating(AlarmManager.RTC_WAKEUP,System.currentTimeMillis(),5*1000,pi);  	//这句是OK的.
 
        //时间到时，执行PendingIntent，只执行一次
        //AlarmManager.RTC_WAKEUP休眠时会运行，如果是AlarmManager.RTC,在休眠时不会运行
        //am.setRepeating(AlarmManager.RTC_WAKEUP, c.getTimeInMillis(), 10000, pi);
        //如果需要重复执行，使用上面一行的setRepeating方法，倒数第二参数为间隔时间,单位为毫秒
        
        startTiming();
    }

    //
    public void startTiming() {
    	Intent intent = new Intent(this, AlarmReceiver.class);
        
        PendingIntent pi = PendingIntent.getBroadcast(this, 0, intent, 0);
        //设置一个PendingIntent对象，发送广播            
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
