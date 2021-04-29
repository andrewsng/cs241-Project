bool shutterIsActive = false;
long photosToTake = 0;
long timeInterval = 10000;


void startShutter()
{
  Serial.println("Starting timelapse.");
  shutterIsActive = true;
}


void stopShutter()
{
  Serial.println("Stopping timelapse.");
  shutterIsActive = false;
}


String getCommand()
{
  String cmd = "";
  while (Serial.available() > 0)
  {
    int c = Serial.read();
    if (c < 0)
    {
      break;
    }
    if (c == '\n')
    {
      break;
    }
    else if (c != '\r')
    {
      cmd += (char)c;
    }
  }

  return cmd;
}


bool handleInterval(String cmd)
{
  long inputTime = cmd.toInt();
  if (inputTime > 0)
  {
    timeInterval = inputTime * 1000;
    
    Serial.print("Setting time interval to ");
    Serial.print(inputTime);
    Serial.println(" seconds");
//    Serial.print("timeInterval = ");
//    Serial.println(timeInterval);
    return true;
  }
  return false;
}


bool handlePhotos(String cmd)
{
  long inputPhotoCount = cmd.toInt();
  if (inputPhotoCount > 0)
  {
    photosToTake = inputPhotoCount;
    
    Serial.print("Setting photo count to ");
    Serial.println(inputPhotoCount);
//    Serial.print("photosToTake = ");
//    Serial.println(photosToTake);
    return true;
  }
  return false;
}


void requestInterval()
{
  Serial.print("Enter a time interval in seconds! (Current: ");
  Serial.print(timeInterval / 1000);
  Serial.println(" seconds)");
}


void requestPhotoCount()
{
  Serial.print("Enter the number of photos to take! (Current: ");
  Serial.print(photosToTake);
  Serial.println(")");
}


bool needIntervalValue = false;
bool needPhotoValue = false;
void handleCommand(String cmd)
{
  if (needIntervalValue)
  {
    if (!handleInterval(cmd))
    {
      Serial.print("Invalid interval. ");
      stopShutter();
      requestInterval();
    }
    else
      needIntervalValue = false;
  }
  else if (needPhotoValue)
  {
    if (!handlePhotos(cmd))
    {
      Serial.print("Invalid photo count. ");
      stopShutter();
      requestPhotoCount();
    }
    else
      needPhotoValue = false;
  }
  else if (cmd == "start")
    startShutter();
  else if (cmd == "stop")
    stopShutter();
  else if (cmd == "interval")
  {
    requestInterval();
    needIntervalValue = true;
  }
  else if (cmd == "photos")
  {
    requestPhotoCount();
    needPhotoValue = true;
  }
  else
  {
    Serial.print("Invalid command: ");
    Serial.println(cmd);
  }
}


void setup() {
  Serial.begin(9600);
  Serial.println("Camera Shutter Release!");
  
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
}


String cmd;
void loop()
{
  while (Serial.available() > 0)
  {
    int c = Serial.read();
    if (c < 0)
    {
      break;
    }
    if (c == '\n')
    {
      handleCommand(cmd);
      cmd = "";
    }
    else if (c != '\r')
    {
      cmd += (char)c;
    }
  }
  
//  String cmd = getCommand();
//  if (cmd.length() == 0)
//    return;
//  handleCommand(cmd);

  if (shutterIsActive)
  {
    Serial.print("Photos left: ");
    Serial.println(photosToTake);
//    Serial.println("High!");
    digitalWrite(8, HIGH);
    delay(500);
//    Serial.println("Low!");
    digitalWrite(8, LOW);
    delay(timeInterval);

    --photosToTake;
    if (photosToTake <= 0)
    {
      stopShutter();
    }
  }
}
