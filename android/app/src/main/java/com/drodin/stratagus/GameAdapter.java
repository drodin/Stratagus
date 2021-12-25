package com.drodin.stratagus;

import android.content.Context;
import android.net.Uri;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.File;
import java.util.Map;

public class GameAdapter extends ArrayAdapter<Map<String,String>> {
    public GameAdapter(Context context) {
        super(context, 0);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        Map<String,String> game = getItem(position);

        if (convertView == null)
            convertView = LayoutInflater.from(getContext())
                    .inflate(R.layout.game, parent, false);

        ((ImageView)convertView.findViewById(R.id.game_icon))
                .setImageURI(Uri.fromFile(new File(game.get("Icon"))));
        if (game.get("Name") != null)
            ((TextView)convertView.findViewById(R.id.game_name)).setText(game.get("Name"));
        if (game.get("Version") != null)
            ((TextView)convertView.findViewById(R.id.game_version))
                    .setText(getContext().getString(R.string.version_number,game.get("Version")));

        return convertView;
    }
}
