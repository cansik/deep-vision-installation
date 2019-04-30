class DeepVisionMCU extends MicroControllerUnit implements Runnable
{
  volatile boolean running = false;

  Thread thread;

  public DeepVisionMCU(PApplet parent, String portName)
  {
    super(parent, portName);
  }

  void start()
  {
    running = true;

    thread = new Thread(this);
    thread.setDaemon(true);
    thread.start();
  }

  void stop()
  {
    running = false;

    try
    {
      thread.join(5000);
    }
    catch(Exception ex) 
    {
      ex.printStackTrace();
    }
  }

  void run()
  {
    while (running)
    {
      try
      {
        Thread.sleep(1);
        readScanData();
      }
      catch(Exception ex) 
      {
        ex.printStackTrace();
      }
    }
  }

  void readScanData()
  {
    if (!isAttached())
      return;

    String raw = readData();

    if (debug && raw != null && !raw.startsWith("TST") && !raw.trim().equals(""))
    {
      println("MCU: " + raw.trim());
    }

    if (raw == null || !raw.startsWith("TST"))
      return;

    // relevant data
    String[] data = raw.split(":");
    try
    {
      String header = data[0].trim();
      String cmd = data[1].trim();

      if (cmd.equals("SLR")) {
        // map data
        float x = parseFloat(data[2].trim());

        println("DATA: " + raw.trim());
      }
    }
    catch(Exception ex)
    {
    }
  }
}
