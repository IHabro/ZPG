# ZPG

Expecting directory structure: <br />
ZPG/lib <br />
ZPG/solution <br />

Project - Properties: <br />
c++/General/Add. inc. dirs. <br />
..\..\libs\soil\include;..\..\libs\glm;..\..\libs\glfw-3.3.4.bin.WIN32\include;..\..\libs\glew-2.1.0\include;%(AdditionalIncludeDirectories) <br />

linker/General/Add. Lib. dirs. <br />
..\..\libs\glew-2.1.0\lib\Release\Win32;..\..\libs\glfw-3.3.4.bin.WIN32\lib-vc2019;..\..\libs\soil\lib;%(AdditionalLibraryDirectories) <br />

linker/Input/Add. dep. <br />
opengl32.lib;glu32.lib;glfw3.lib;glew32.lib;SOIL.lib;%(AdditionalDependencies) <br />

Add contents of Models & Shaders Dirs <br />

After project build add glew32.dll to Debug Dir <br />

