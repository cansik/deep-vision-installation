import peasy.PeasyCam;

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress mcuAddress;

String mcuPath = "/dev/tty.SLAB_USBtoUART";
boolean isMcuAvailable = false;

DeepVisionMCU mcu = new DeepVisionMCU(this, mcuPath);

PeasyCam cam;

boolean debug = true;

void setup()
{
  frameRate(60);
  size(1280, 800, P3D);
  pixelDensity(2);
  surface.setTitle("Deep Vision Debug Monitor");

  cam = new PeasyCam(this, 0, 0, 0, 400);

  // try to attach
  checkDevices();
  if (isMcuAvailable)
    mcu.attach();

  mcu.start();
}

void draw()
{
  if (oscP5 == null)
  {
    // osc
    oscP5 = new OscP5(this, 9000);
    mcuAddress = new NetAddress("192.168.4.1", 8000);
  }

  checkDevices();

  background(0);

  showInfo();
}

void showDebug(String text)
{
  cam.beginHUD();
  fill(0, 255, 0);
  textSize(14);
  text("Debug \"" + text + "\"", 20, height - 50);
  cam.endHUD();
}

void showInfo()
{
  cam.beginHUD();
  fill(255);
  textSize(14);
  text("MCU detected: " + isMcuAvailable 
    + "\nattached: " + (mcu.isAttached()) 
    + "\nFPS: " + round(frameRate), 20, 20);
  cam.endHUD();
}

void keyPressed()
{
  if (key == ' ')
  {
    // try to connect
    if (isMcuAvailable)
      mcu.attach();
    else
      println("No MCU detected!");
  }

  if (key == 'i')
  {
    int seed = (int)random(0, 10000);
    randomSeed(seed);

    println("Seed: " + seed);
  }
}

void checkDevices()
{
  isMcuAvailable = new File(mcuPath).exists();
}

void oscEvent(OscMessage theOscMessage) {
}
