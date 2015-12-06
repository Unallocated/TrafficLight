//**************************************
//Date: 11/8/2014 - Chris
//Desc: 
//**************************************
//Modified 3/7/2015 - Chris
//Desc:
//**************************************
//Modified 12/5/2015 - Chris
//Desc: 
//**************************************

#include <Bridge.h>
#include <HttpClient.h>
#include <YunServer.h>
#include <YunClient.h>

// Listen on default port 5555, the webserver on the Yún will forward there all the HTTP requests for us.
YunServer server;

//pin order for lights
int pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int LightStatus[8] = {0, 0, 0, 0, 0, 0};

//JSON object  name
char half[4], full[8], pattern[6], *script, done[2];
//if done = "s" or "f" then pull and set done to ""

bool WeAreHere; //space status

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Bridge.begin();
  digitalWrite(13, LOW);
  
  // Listen for incoming connection only from localhost (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
  
  WeAreHere = false; //prevent things from happening before we want
  
  for (int i=0; i<=7; i++)
  {
    pinMode (pins[i], OUTPUT);
    digitalWrite (pins[i], LOW);
  }
}

void loop()
{   
  // Get clients coming from server
  YunClient client = server.accept();
  
  // There is a new client?
  if (client)
  {
    // Process request
    process(client);

    // Close connection and free resources.
    client.stop();
  }
  
  //check for messages from JSON updates from Python
  int y = Bridge.get("done", done, 2);
  
  if (done[0] == 'f')
  {
    int y = Bridge.get("short", half, 4);
    
    Bridge.put ("done","");
  }
  else if (done[0] == 's')
  {
    int y = Bridge.get("full", full, 8);
    
    Bridge.put ("done","");
  }
  else if (done[0] == 'p')
  {
    //how to get pattern name?
  
    Bridge.put ("done","");
  }
  else if (done[0] == 'g')
  {
    //request to get status of all lights

    Bridge.put ("done", GetLightStatus ())
  }

  delay(500);  
}

String GetLightStatus ()
{
  String temp = "";
  for (int i = 0; i <= 7; i++)
  {
    if (LightStatus[i] == 1)
      temp += "1";
    else
      temp += "0";
  }
  return (temp);
}

void QuerrySpaceStatus ()
{
  // Initialize the client library
  HttpClient webclient;
  
  //get status page
  webclient.get("http://www.unallocatedspace.org/status");

  // if there are incoming bytes available from the server, read them and print them:
  if (webclient.available())
  {
    if (webclient.read() == '+') //the first character "+" means the space is open
    WeAreHere = true;
    else
      WeAreHere = false;

    webclient.flush(); //clear the rest of the GET response
  }
}

void process(YunClient client)
{
  // read the command
  String command = client.readStringUntil('/');

  if (command == "s")
   ShortCommand(client);

  if (command == "f")
    FullCommand(client);
  
  if (command == "p")
    PatternCommand(client);
}

void ShortCommand(YunClient client) 
{
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/digital/13/1"
  if (client.read() == '/')
  {
    //asdf
  }
  else
  {
    //asdf
  }
}

void FullCommand(YunClient client) 
{
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/digital/13/1"
  if (client.read() == '/')
  {
    //asdf
  }
  else
  {
    //asdf
  }
}

void PlayScript ()
{
  
  
  
}

void PatternCommand(YunClient client)
{
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/analog/5/120"
  if (client.read() == '/') 
  {
    //asdf
  }
  else
  {
    //asdf 
  }
}

//Patterns
void Up ()
{
  digitalWrite (pins[7], HIGH);
  delay (100);
  digitalWrite (pins[7], LOW);
  delay (100);
  digitalWrite (pins[6], HIGH);
  delay (100);
  digitalWrite (pins[6], LOW);
  delay (100);
  digitalWrite (pins[5], HIGH);
  delay (100);
  digitalWrite (pins[5], LOW);
  delay (100);
  digitalWrite (pins[4], HIGH);
  delay (100);
  digitalWrite (pins[4], LOW);
  delay (100);
  digitalWrite (pins[3], HIGH);
  delay (100);
  digitalWrite (pins[3], LOW);
  delay (100);
  digitalWrite (pins[2], HIGH);
  delay (100);
  digitalWrite (pins[2], LOW);
  delay (100);
  digitalWrite (pins[1], HIGH);
  delay (100);
  digitalWrite (pins[1], LOW);
  delay (100);
  digitalWrite (pins[0], HIGH);
  delay (100);
  digitalWrite (pins[0], LOW);
}

void Down ()
{
  digitalWrite (pins[0], HIGH);
  delay (100);
  digitalWrite (pins[0], LOW);
  delay (100);
  digitalWrite (pins[1], HIGH);
  delay (100);
  digitalWrite (pins[1], LOW);
  delay (100);
  digitalWrite (pins[2], HIGH);
  delay (100);
  digitalWrite (pins[2], LOW);
  delay (100);
  digitalWrite (pins[3], HIGH);
  delay (100);
  digitalWrite (pins[3], LOW);
  delay (100);
  digitalWrite (pins[4], HIGH);
  delay (100);
  digitalWrite (pins[4], LOW);
  delay (100);
  digitalWrite (pins[5], HIGH);
  delay (100);
  digitalWrite (pins[5], LOW);
  delay (100);
  digitalWrite (pins[6], HIGH);
  delay (100);
  digitalWrite (pins[6], LOW);
  delay (100);
  digitalWrite (pins[7], HIGH);
  delay (100);
  digitalWrite (pins[7], LOW);
}

void BlinkAll4 ()
{
  digitalWrite (pins[0], HIGH);
  digitalWrite (pins[1], HIGH);
  digitalWrite (pins[2], HIGH);
  digitalWrite (pins[3], HIGH);
  delay (200);
  digitalWrite (pins[0], LOW);
  digitalWrite (pins[1], LOW);
  digitalWrite (pins[2], LOW);
  digitalWrite (pins[3], LOW);
}

void BlinkAll8 ()
{
  digitalWrite (pins[0], HIGH);
  digitalWrite (pins[1], HIGH);
  digitalWrite (pins[2], HIGH);
  digitalWrite (pins[3], HIGH);
  digitalWrite (pins[4], HIGH);
  digitalWrite (pins[5], HIGH);
  digitalWrite (pins[6], HIGH);
  digitalWrite (pins[7], HIGH);
  delay (200);
  digitalWrite (pins[0], LOW);
  digitalWrite (pins[1], LOW);
  digitalWrite (pins[2], LOW);
  digitalWrite (pins[3], LOW);
  digitalWrite (pins[4], LOW);
  digitalWrite (pins[5], LOW);
  digitalWrite (pins[6], LOW);
  digitalWrite (pins[7], LOW);
}

void BlinkRandom4 ()
{
  int p = random (2, 5);
  digitalWrite( pins[p], HIGH);
  delay (200);
  digitalWrite( pins[p], LOW);
}

void BlinkRandom8 ()
{
  int p = random (2, 9);
  digitalWrite( pins[p], HIGH);
  delay (200);
  digitalWrite( pins[p], LOW);
}
