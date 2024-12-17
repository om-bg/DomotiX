package com.example.domotix;

import android.os.Bundle;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {
    private DatabaseReference database;
    private Button b1, b2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize Firebase
        try {
            database = FirebaseDatabase.getInstance().getReference("LED");
        } catch (Exception e) {
            Toast.makeText(this, "Failed to initialize Firebase: " + e.getMessage(), Toast.LENGTH_LONG).show();
        }

        // Initialize buttons
        b1 = findViewById(R.id.toz);
        b2 = findViewById(R.id.ter);

        // Turn LED ON
        b1.setOnClickListener(v -> updateLedState("ON"));

        // Turn LED OFF
        b2.setOnClickListener(v -> updateLedState("OFF"));

        // Debug Firebase connection
        FirebaseDatabase.getInstance().getReference(".info/connected")
                .addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(DataSnapshot snapshot) {
                        boolean connected = snapshot.getValue(Boolean.class);
                        String message = connected ? "Firebase connected" : "Firebase not connected";
                        Toast.makeText(MainActivity.this, message, Toast.LENGTH_SHORT).show();
                    }

                    @Override
                    public void onCancelled(DatabaseError error) {
                        Toast.makeText(MainActivity.this, "Connection check failed: " + error.getMessage(), Toast.LENGTH_SHORT).show();
                    }
                });
    }

    private void updateLedState(String state) {
        if (database == null) {
            Toast.makeText(this, "Database reference is not initialized", Toast.LENGTH_SHORT).show();
            return;
        }

        database.setValue(state).addOnCompleteListener(task -> {
            String message = task.isSuccessful() ? "LED is " + state : "Failed to turn " + state + " LED";
            Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
        });
    }
}
