class Slice
{
  PApplet parent;
  PImage texture;

  String textureName;

  float brightness = 255;

  public Slice(PApplet parent, String textureName)
  {
    this.parent = parent;
    this.textureName = textureName;
  }

  public void setup() {
    texture = loadImage(textureName);
    texture.filter(INVERT);
  }

  private void renderPlate(PGraphics g, int index)
  {
    float centerPos = getPlateZ(index);
    float textZ = (plateThickness / 2f) + 0.01;

    g.push();
    g.translate(0, 0, centerPos);

    g.strokeWeight(0.5f);
    g.stroke(255, 100);
    g.fill(255, 3);

    // add acrylic glass
    g.hint(DISABLE_DEPTH_TEST);
    g.box(plateWidth, plateHeight, plateThickness);

    // add engraving
    float htw = texture.width / 2f;
    float hth = texture.height / 2f;
    g.noFill();
    g.beginShape();
    g.tint(brightness);
    g.texture(texture);
    g.vertex(-htw, -hth, textZ, 0, 0);
    g.vertex(htw, -hth, textZ, texture.width, 0);
    g.vertex(htw, hth, textZ, texture.width, texture.height);
    g.vertex(-htw, hth, textZ, 0, texture.height);
    g.endShape(CLOSE);  

    g.hint(ENABLE_DEPTH_TEST);

    g.pop();
  }
}
