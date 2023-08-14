#  <b> Learn OpenGL </b>
* [Aim of This Repository](#aim)
* [Summary Information About OpenGL and Auxiliary Libs](#siao)
* [Some Functions and Their Definitions](#sfatd)

<a name="aim"></a>

## <b> Aim of This Repository </b>
&nbsp; The aim of this project is to study how 3D computations and linear algebra are implemented in computer science with the OpenGL library.

&nbsp; While I work on the OpenGL library, I do mainly benefit from the OpenGL library introductory training series of Mr. Kayhan AYAR, which can be found in the link here https://www.youtube.com/watch?v=_MhmHNbnhSs&list=PLIM5iw4GHbNW2nleNK5XIvyhZzGiaiBfp.
Also, the code example belong to Mr. Kayhan AYAR.

&nbsp; For example; How to use theory of light in OpenGL or what are the functions used in OpenGL and OpenGL auxiliary libraries and what they do, etc.

<a name="siao"></a>

##  <b> Summary Information About OpenGL and Auxiliary Libs </b>
&nbsp; <b>OpenGL</b> is a cross platform library that communicates for us with the graphics card so that we can do computer graphics operations.

&nbsp; <b>GLFW</b> is the cross platform library of the OpenGL's auxiliary libraries. The GLFW library communicates between OpenGL and the operating system, it helps us that to manage windows, control input-output operations and similar process in OpenGL.

&nbsp; <b>GLAD</b> and <b>GLEW</b> are cross platform libraries of the OpenGL's auxiliary libraries. 

&nbsp; Programs that using OpenGL need to connect with OpenGL's dynamic library in the background while they run. OpenGL uses dynamic loading method for the programs can connect its dynamic library. The <b>GLAD</b> and <b>GLEW</b> libraries help us here. In order to connect with the OpenGL dynamic library, it is enough to use only one of the two libraries.

&nbsp; The working way of <b>GLAD</b>, the programmer tells to GLAD the function it needs instead of directly capturing the needed function addresses in OpenGL's dynamic library, and GLAD gives the address of the function needed for the programmer.

&nbsp; The working way of <b>GLEW</b>, giving programmers an easier-to-use interface by wrapping functions in the OpenGL dynamic library.


<a name="sfatd"></a>

##  <b> Some Functions and Their Definitions </b>







