<br />
<p align="center">
  <a href="">
    <img src="readme/logo.png" alt="Logo" width="100" height="100">
  </a>
  <h3 align="center">MeshViewer</h3>
   <p align="center">
      A simple mesh viewer made with Qt
      <br> <br>
      <a href="#features">Features</a>
      ·
      <a href="#controls">Controls</a>
      ·
      <a href="#installation">Installation</a>
    </p>
</p>
<hr height="1">
<p align="center">
This is a basic mesh viewer made with Qt on C++ that allows you to display 3D meshes.
  <p align="center">
    <img src="readme/spin.gif" alt="Face only">
  </p>
</p>

## Features
<p align="center">
MeshViewer allows you to display 3D objects of .ply, .obj & .stl formats. You can adjust various color properties of the object. You can set the lighting, diffuse, ambient and specular colors. MeshViewer allows you to render 3D objects in "Face only", "Face + Wireframe" and "Wireframe" mods, with modifiable wireframe line width & color:
  <p align="center">
    <img src="readme/modes-face.png" alt="Face only" width="300" height="250">
    <img src="readme/modes-facewf.png" alt="Face + Wireframe" width="300" height="250">
    <img src="readme/modes-wf.png" alt="Wireframe only" width="300" height="250">    
  </p>
  <p align="center">
    <img src="readme/linewidth.gif" alt="Face only" width="420" height="300">
  </p>
  <p>
  MeshViewer has an option for you to change between flat and smooth shading modes with adjustable light intensity. This is achieved via computing normals  in slightly different ways in the fragment shader 
  </p>
    <p align="center">
      <img src="readme/shading-flat.png" alt="Face only" width="300" height="250">
      <img src="readme/shading-smooth.png" alt="Face + Wireframe" width="300" height="250">
    </p>
  <p>
  This project uses Qt 5.12 for user interface, and OpenGL for graphical effects. MeshViewer includes the custom camera controller class, a mesh class with custom material, and GLSL shaders for custom effects (wireframe + flat shading). Custom features were implemented for the sake of better flexibility of the program. In the "test-meshes" directory you can find some basic models that you can display in the program, but anything of the .ply, .obj, and .stl format will be ok as well. 
  </p>
</p>

## Controls
<p align="center">
  <p>Left Mouse Button : Rotate mesh</p>
  <p>W/S || ⇧/⇩	: Rotate mesh (z axis)</p>
  <p>A/D || ⇦/⇨	: Rotate mesh (x axis)</p>
  <p>Mouse Wheel	: Zoom in/out</p>
  <p>Ctrl + N	  : New empty scene</p>
  <p>Ctrl + O	  : Open new file</p>
  <p>Ctrl + Q	  : Quit</p>
</p>

## Installation
