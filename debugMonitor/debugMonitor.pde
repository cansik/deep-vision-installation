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

int sliceCount = 7;

Slice[] slices = new Slice[sliceCount];

float plateThickness = 4;
float plateSpace = 150;
float plateWidth = 10;
float plateHeight = 10;

float minBrightness = 100;
float maxBrightness = 255;

void setup()
{
  frameRate(60);
  size(1280, 800, P3D);
  pixelDensity(2);
  surface.setTitle("Deep Vision Debug Monitor");

  cam = new PeasyCam(this, 0, 0, 0, 2000);

  for (int i = 0; i < slices.length; i++) {
    Slice s = new Slice(this, "slice_" + i + ".png");
    s.setup();
    
    plateWidth = s.texture.width;
    plateHeight = s.texture.height;
    
    slices[i] = s;
  }

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

  renderSlices();

  showInfo();
}

void renderSlices() {
  for (int i = 0; i < slices.length; i++) {
    push();
    Slice s = slices[i];
    s.renderPlate(this.g, i);
    pop();
  }
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

float getPlateZ(int index) {
  return (index * (plateSpace + plateThickness)) - ((slices.length * (plateSpace + plateThickness)) / 2f);
}
