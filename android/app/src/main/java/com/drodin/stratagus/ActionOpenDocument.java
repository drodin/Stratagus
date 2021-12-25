package com.drodin.stratagus;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import android.Manifest;
import android.app.ListActivity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.util.TypedValue;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.MimeTypeMap;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

public class ActionOpenDocument extends ListActivity {
    private ArrayAdapter<File> files;
    private File currentDirectory;

    @Override
    public void onCreate(final Bundle icicle) {
        super.onCreate(icicle);

        getActionBar().setTitle(R.string.select_zip);

        files = new ArrayAdapter<File>(this, 0) {
            @Override
            public View getView(final int position, final View convertView, final ViewGroup parent) {
                final TextView textView = new TextView(getContext());
                textView.setTextSize(TypedValue.COMPLEX_UNIT_SP,20);
                textView.setPadding(10, 20, 10, 20);

                final File file = getItem(position);
                String name = file.getName();
                if (position == 0 && file.equals(currentDirectory.getParentFile()))
                    name = "/..";
                else if (file.isDirectory())
                    name = "/" + name;

                textView.setText(name);

                return textView;
            }
        };

        setListAdapter(files);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M &&
                checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE)
                        != PackageManager.PERMISSION_GRANTED) {
            requestPermissions(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, 0);
        }
    }

    @Override
    public void onResume(){
        super.onResume();

        showDirectory(Environment.getExternalStorageDirectory());
    }

    @Override
    protected void onListItemClick(final ListView l, final View v, final int position, final long id) {
        final File file = files.getItem(position);
        if (file.isDirectory()) {
            showDirectory(file);
        } else {
            setResult(RESULT_OK, new Intent().setData(Uri.fromFile(file)));
            finish();
        }
    }

    private void showDirectory(final File directory) {
        currentDirectory = directory;

        List<File> filesList = new ArrayList<>();

        File parentDirectory = directory.getParentFile();
        if (parentDirectory != null && parentDirectory.listFiles() != null) {
            filesList.add(parentDirectory);
        }

        final Set<File> sortedFiles = new TreeSet<>();
        final File[] listFiles = directory.listFiles();
        if (listFiles != null) {
            for (final File file : listFiles) {
                if ((file.isDirectory() && file.listFiles() != null)
                        || (file.isFile() && file.canRead() && MimeTypeMap.getFileExtensionFromUrl(Uri.fromFile(file).toString()).equals("zip"))) {
                    sortedFiles.add(file);
                }
            }
            filesList.addAll(sortedFiles);
        }

        files.clear();
        files.addAll(filesList);
    }
}
