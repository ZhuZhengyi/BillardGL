void LSupdateGL();
void LSidle();

extern GLint CurrentWindow, BallResolution,
	   TextureSize, TableTextureSize, AmbientLighting, 
	   TableLamps, GrueneLamp, Reflections, 
	   DisplayTextureSize, Spiel,
	   LoadingProgress;

extern class Ball Ball[16];
extern class Display Display;
extern class Menu Menu;
extern class Referee Referee;
extern class Lighting Lighting;
extern GLuint ThirteenTexture;
extern GLuint LogoTexture;
