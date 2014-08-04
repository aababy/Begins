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
        //String msg = intent.getStringExtra("msg");  		���Դ�intent��ȡ��Ϣ, ����û�б�Ҫ
		
		if(checkMission())
		{
	        Toast.makeText(context, "����Ϣ", Toast.LENGTH_SHORT).show();  
	        
	        //��������
	        player = MediaPlayer.create(context, R.raw.abc);  
	        player.setLooping(false);  
	        player.start(); 
		}
		
        //���ǰ̨, �Ƚ��鷳, �������о�
        //http://blog.sina.com.cn/s/blog_53a8248f0100vd8k.html
//        Intent it = new Intent(context, MainActivity.class);
//        intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
//        context.startActivity(it);
	}
	
	native boolean checkMission();
}
