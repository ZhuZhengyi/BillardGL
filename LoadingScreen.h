void LSupdateGL();
void LSidle();

extern GLint CurrentWindow, BallResolution,
	   TextureSize, TableTextureSize, AmbientLighting, 
	   TableLamps, GreenLamp, Reflections, 
       DisplayTextureSize, GameType,
	   LoadingProgress;

extern class Ball Ball[16];
extern class Display Display;
extern class Menu Menu;
extern class Judge Judge;
extern class Lighting Lighting;
extern GLuint ThirteenTexture;
extern GLuint LogoTexture;
