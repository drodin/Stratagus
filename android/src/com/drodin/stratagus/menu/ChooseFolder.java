package com.drodin.stratagus.menu;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

import com.drodin.stratagus.R;

public class ChooseFolder extends ListActivity {

	private String startDir;
	private String sdcardDir = "/sdcard";

	private final static String PARENT_DIR = "..";

	private EditText pathView;

	protected final List<String> currentFiles = new ArrayList<String>();

	private File currentDir = null;

	@Override
	public void onCreate(final Bundle icicle) {
		super.onCreate(icicle);

		setContentView(R.layout.choose_folder);

		pathView = (EditText) findViewById(R.id.file_tv);

		((Button)findViewById(R.id.select_btn)).setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				final String name = pathView.getText().toString();
				setResult(RESULT_OK, new Intent().putExtra("selectedFolder", name));
				finish();
			}
		});

		startDir = getIntent().getStringExtra("startDir");

		try {
			if(startDir != null)
				showDirectory(startDir);
		} catch (NullPointerException e) {
			try {
				showDirectory(sdcardDir);
			} catch (NullPointerException e2) {
				showDirectory("/");
			}
		}

	}

	@Override
	protected void onListItemClick(final ListView l, final View v, final int position, final long id) {
		if (position == 0 && PARENT_DIR.equals(this.currentFiles.get(0))) {
			showDirectory(this.currentDir.getParent());
		} else {
			final File file = new File(this.currentFiles.get(position));
			if (file.isDirectory()) {
				showDirectory(file.getAbsolutePath());
			}
		}
	}

	private void showDirectory(final String path) {

		this.currentFiles.clear();
		this.currentDir = new File(path);

		pathView.setText(currentDir.getAbsolutePath()+"/");

		if (this.currentDir.getParentFile() != null /*&& !path.equals(startDir)*/) {
			this.currentFiles.add(PARENT_DIR);
		}

		final File[] files = this.currentDir.listFiles();
		final Set<String> sortedDirs = new TreeSet<String>();

		for (final File file : files) {
			final String name = file.getAbsolutePath();

			if (file.isDirectory()) {
				sortedDirs.add(name);
			}

		}
		this.currentFiles.addAll(sortedDirs);

		final Context context = this;

		ArrayAdapter<String> filenamesAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_expandable_list_item_1, this.currentFiles) {
			@Override
			public View getView(final int position, final View convertView, final ViewGroup parent) {
				return new ModifiedTextLayout(context, getItem(position), position);
			}
		};

		setListAdapter(filenamesAdapter);
	}

	class ModifiedTextLayout extends LinearLayout {

		public ModifiedTextLayout(final Context context, final String path, final int position) {
			super(context);

			setOrientation(HORIZONTAL);

			final File file = new File(path);

			final TextView textView = new TextView(context);
			textView.setTextAppearance(context, R.style.ListText);

			if (file.isDirectory()) {
				textView.setText("/" + file.getName());
			}

			addView(textView, new LinearLayout.LayoutParams(
					LayoutParams.FILL_PARENT, LayoutParams.WRAP_CONTENT));
		}
	}

}
