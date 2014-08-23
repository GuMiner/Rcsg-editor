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
`Pre-Alpha: Design in progress`
`Previous step completed: Feasibility verification`

Capabilities
------------
**Warning:** This list may change because *Rcsg-editor* is under active design and development work.
- Graphical design with programmatic elements, allowing the designer to model a spoon and the engineer to model a gear.
- Material-based CSG editor, with photorealistic normal-mapped materials.
- Recursive design, with each part and construction exported as renderable (and 3D-printable) STL files*.
- Multi-platform open-source C++ code utilizing OpenGL 4.0.

*Units are in millimeters.

Author Information
------------------
Gustave Granroth [gus.gran@gmail.com](mailto:gus.gran@gmail.com)

The author is currently employed as a software engineer in the Seattle area, having recently completed
degrees in Nuclear Engineering, Computer Science, and Physics at the University of Wisconsin -- Madison.

For more information, see the author's website at [g-cnp.rhcloud.com](http://g-cnp.rhcloud.com).

Included Libraries
------------------

	* For CSG Support: Carve 1.4 - GNU GPL v2.0 - Tobias Sargeant [website](https://code.google.com/p/carve/)
	* For OpenGL platform support: GLFW 3.0 - zlib\png - Marcus Geelnard|Camilla Berglund [website](http://www.glfw.org/)
	* For OpenGL extension support: GLEW 1.1 - Modified BSD\MIT License - Milan Ikits|Marcelo Magallon|et al. [website](http://glew.sourceforge.net/)
