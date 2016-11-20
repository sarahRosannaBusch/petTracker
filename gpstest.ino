const int gpsOn = D0; //to give the GPS on/off pin a pulse to turn it on/off

//unsigned int now = 0; //for the current time
//unsigned int lastTime = 0; //to keep track of last publish time
bool runGPS = false; //the gps needs up to 37s after being powered up before it's ready to read the gps data

String txData; //all data is sent as one String in one publish event to minimize data costs

void setup()
{
    Serial1.begin(4800); //default is 8 bits, no parity, 1 stop bit (which seems to be what the GPS sends)
    pinMode(gpsOn, OUTPUT); //giving a pulse to the on/off pin of the nano hornet turns it on/off
    digitalWrite(gpsOn, LOW);
}

void loop()
{
    gpsPulse(); //turn gps on
    //unsigned long runTime = millis();

    //if(runTime > 37000 && runGPS == false) //if it's been longer than 37s (cold start max time) since the device booted (runs only once)
    //{
        //runGPS = true;
        //gpsPulse(); //first attempt at turning gps on
    //}
    //else if(runGPS == true)
    //{
        //now = Time.now(); //current time as seconds since January 1, 1970 ("Unix time" or "epoch time") (not affected by timezone)

        //if(now > lastTime+300) //if it's been longer than 5min=300s since last GPS update
        //{
            //lastTime = now;
            gpsData();
        //}
    //}
    gpsPulse(); //turn gps back off
}

void gpsPulse()
{
    delay(500); //to ensure there is at least 1s between pulses, as recommended by the manufacturer
    digitalWrite(gpsOn, HIGH); //gives the gps module a pulse to turn it on
    delay(100); //100ms as recommended by nano hornet datasheet
    digitalWrite(gpsOn, LOW);
    delay(500);
}

void gpsData()
{
    //if (Serial1.available()) //.available gets the number of bytes that can be read on the serial port (64 bites can be held in the buffer)
    //{
        String buffer = "";
        int bytes = Serial1.available();
        for(int count=0; count < bytes; count++)
        {
            buffer += Serial1.readString();
        }
        //txData = "Bytes: " + String(Serial1.available());
        txData = "Data: " + buffer;
        publish();
    //}
    //else
    //{
        //txData = ":(";
        //publish();
        //gpsPulse(); //give the gps another pulse to try turning it on again
    //}
}

void publish()
{
    bool success;
    success = Particle.publish("trackerData", txData);
    if (!success)
    {
      // if event publish did not work
      //lastTime = 0; //so it will try again
      //publish();
    }
}
