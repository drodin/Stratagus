package com.drodin.stratagus;

import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.provider.OpenableColumns;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

public class FileUtils {

    interface FileUtilsCallback {
        enum Event {
            PROGRESS,
            SUCCESS,
            FAILURE
        }
        void event(Event event, String message);
    }

    public static void extractArchive(Context context, Uri uri, File destDir, FileUtilsCallback callback) {
        byte[] buffer = new byte[8192];
        try {
            InputStream inputStream = context.getContentResolver().openInputStream(uri);
            ZipInputStream zipInputStream = new ZipInputStream(inputStream);
            ZipEntry zipEntry = zipInputStream.getNextEntry();
            while (zipEntry != null) {
                File newFile = new File(destDir, zipEntry.getName());
                if (zipEntry.isDirectory()) {
                    if (!newFile.isDirectory() && !newFile.mkdirs()) {
                        throw new IOException("Failed to create directory " + newFile);
                    }
                } else {
                    // fix for Windows-created archives
                    File parent = newFile.getParentFile();
                    if (parent == null || (!parent.isDirectory() && !parent.mkdirs())) {
                        throw new IOException("Failed to create directory " + parent);
                    }

                    if (callback != null)
                        callback.event(FileUtilsCallback.Event.PROGRESS, zipEntry.getName());

                    // write file content
                    FileOutputStream fos = new FileOutputStream(newFile);
                    int len;
                    while ((len = zipInputStream.read(buffer)) > 0) {
                        fos.write(buffer, 0, len);
                    }
                    fos.close();
                }
                zipEntry = zipInputStream.getNextEntry();
            }
            zipInputStream.closeEntry();
            zipInputStream.close();
            inputStream.close();

            if (callback != null)
                callback.event(FileUtilsCallback.Event.SUCCESS, null);
        } catch (IOException e) {
            e.printStackTrace();

            if (callback != null)
                callback.event(FileUtilsCallback.Event.FAILURE, e.getMessage());
        }
    }

    public static boolean deleteRecursive(File fileOrDirectory) {
        if (!fileOrDirectory.exists())
            return true;

        if (fileOrDirectory.isDirectory()) {
            File[] files = fileOrDirectory.listFiles();
            if (files != null)
                for (File file : files)
                    deleteRecursive(file);
        }

        return fileOrDirectory.delete();
    }

    private static ArrayList<File> foundList = new ArrayList<>();
    public static ArrayList<File> findRecursive(File startDir, String fileName) {
        foundList.clear();
        findRecursiveInner(startDir, fileName);
        return foundList;
    }
    private static void findRecursiveInner(File startDir, String fileName) {
        File file = new File(startDir, fileName);
        if (file.exists() && file.isFile())
            foundList.add(startDir);

        File[] dirs = startDir.listFiles(File::isDirectory);
        if (dirs != null)
            for (File dir : dirs)
                findRecursiveInner(dir, fileName);
    }

    public static String getNameFromUri(Context context, Uri uri) {
        String name = uri.getLastPathSegment();
        if (uri.getScheme().equals("content")) {
            Cursor cursor =  context.getContentResolver().query(uri, null, null, null, null);
            try {
                if (cursor != null && cursor.moveToFirst()) {
                    name = cursor.getString(cursor.getColumnIndex(OpenableColumns.DISPLAY_NAME));
                }
            } finally {
                cursor.close();
            }
        }
        return name;
    }
}
