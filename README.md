Rcsg-editor
===========
A recursive material-with-texture CSG editor.

Short Description
-----------------
Rcsg-editor is a material-based CSG editor capable of designing single parts, combining those parts into a larger
construction, and then saving the large construction as a recursive single model. This design allows the large construction
to be deconstructed at run-time into individual high-quality parts.

For example, a table can consist of the legs, top, and small metal components holding the table together. At a distance, the 
table can be rendered as a single object. At close distances, the table will be deconstructed into the individual parts to 
increase visual quality and allow for physical interaction.

Current Status
--------------
This project is on indefinite hold as the use case I was writing this editor for -- modeling parts to use on a CNC mill or 3d printer -- 
is not significantly improved with this design in comparison to 
[Fusion 360] (http://www.autodesk.com/products/fusion-360/overview) or [OpenSCAD](http://www.openscad.org/).

Included Libraries
------------------

* For CSG Support: Carve 1.4 - GNU GPL v2.0 - Tobias Sargeant [website](https://code.google.com/p/carve/)
* For OpenGL platform support: GLFW 3.0 - zlib\png - Marcus Geelnard|Camilla Berglund [website](http://www.glfw.org/)
* For OpenGL extension support: GLEW 1.1 - Modified BSD\MIT License - Milan Ikits|Marcelo Magallon|et al. [website](http://glew.sourceforge.net/)
