package org.cocos2dx.cpp;

import com.luoxp.begins.R;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.media.MediaPlayer;
import android.widget.Toast;
 
public class AlarmReceiver extends BroadcastReceiver {
	MediaPlayer player;  
 
	@Override
	public void onReceive(Context context, Intent intent) {
        //String msg = intent.getStringExtra("msg");  		可以从intent获取消息, 但是没有必要
		
		if(checkMission())
		{
	        Toast.makeText(context, "新消息", Toast.LENGTH_SHORT).show();  
	        
	        //播放声音
	        player = MediaPlayer.create(context, R.raw.abc);  
	        player.setLooping(false);  
	        player.start(); 
		}
		
        //激活到前台, 比较麻烦, 后期再研究
        //http://blog.sina.com.cn/s/blog_53a8248f0100vd8k.html
//        Intent it = new Intent(context, MainActivity.class);
//        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
//        context.startActivity(it);
	}
	
	native boolean checkMission();
}
