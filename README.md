# ZPG

Expecting directory structure: <br />
ZPG/lib <br />
   /solution <br />

Project - Properties: <br />
c++/General/Add. inc. dirs. <br />
..\..\libs\glm;..\..\libs\glfw-3.3.4.bin.WIN32\include;..\..\libs\glew-2.1.0\include;%(AdditionalIncludeDirectories) <br />

linker/General/Add. Lib. dirs. <br />
..\..\libs\glew-2.1.0\lib\Release\Win32;..\..\libs\glfw-3.3.4.bin.WIN32\lib-vc2019;%(AdditionalLibraryDirectories) <br />

linker/Input/Add. dep. <br />
opengl32.lib;glu32.lib;glfw3.lib;glew32.lib;%(AdditionalDependencies) <br />
