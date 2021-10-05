# ZPG

Expecting directory structure:
ZPG/lib
   /solution

Project - Properties:
c++/General/Add. inc. dirs.
..\..\libs\glm;..\..\libs\glfw-3.3.4.bin.WIN32\include;..\..\libs\glew-2.1.0\include;%(AdditionalIncludeDirectories)

linker/General/Add. Lib. dirs.
..\..\libs\glew-2.1.0\lib\Release\Win32;..\..\libs\glfw-3.3.4.bin.WIN32\lib-vc2019;%(AdditionalLibraryDirectories)

linker/Input/Add. dep.
opengl32.lib;glu32.lib;glfw3.lib;glew32.lib;%(AdditionalDependencies)
