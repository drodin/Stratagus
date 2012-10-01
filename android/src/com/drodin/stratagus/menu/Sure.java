package com.drodin.stratagus.menu;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.drodin.stratagus.R;

public class Sure extends Activity {

	@Override
	public void onCreate(Bundle icicle) {
		super.onCreate(icicle);

		String title = getIntent().getStringExtra("title");
		setTitle(title);

		final TextView messageView = new TextView(this) {
			{
				setText(getString(R.string.sure_message));
				setPadding(10, 0, 10, 10);
			}
		};

		
		final Button yesButton = new Button(this) {
			{
				setText(R.string.sure_btn_yes);
				setOnClickListener(new View.OnClickListener() {
					public void onClick(View v) {
						setResult(RESULT_OK, new Intent());
						finish();
					}
				});
			}
		};
		final Button noButton = new Button(this) {
			{
				setText(R.string.sure_btn_no);
				setOnClickListener(new View.OnClickListener() {
					public void onClick(View v) {
						setResult(RESULT_CANCELED, new Intent());
						finish();
					}
				});
			}
		};

		final LinearLayout parentContainer = new LinearLayout(this) {
			{
				setOrientation(LinearLayout.VERTICAL);
				addView(messageView);
				addView(yesButton);
				addView(noButton);
			}
		};

		setContentView(parentContainer, new LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.WRAP_CONTENT));

	}

}
