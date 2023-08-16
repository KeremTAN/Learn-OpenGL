#  <b> Learn OpenGL </b>
* [Aim of This Repository](#aim)
* [Summary Information About OpenGL and Auxiliary Libs](#siao)
* [How to Work OpenGL - OpenGL Pipeline](#hwopengl)
    * [Step 1 - Vertex Specification](#step1)
    * [Step 2 - Vertex Shader](#step2)
    * [Step 3 - Tessellation](#step3)
    * [Step 4 - Geometry Shader](#step4)
    * [Step 5 - Vertex Post-Processing](#step5)
    * [Step 6 - Primitive Assembly](#step6)
    * [Step 7 - Rasterization](#step7)
    * [Step 8 - Fragment Shader](#step8)
    * [Step 9 - Per-Sample Operations](#step9)
* [Some Functions and Their Definitions](#sfatd)

<a name="aim"></a>

## <b> Aim of This Repository </b>
&nbsp; The aim of this project is to study how 3D computations and linear algebra are implemented in computer science with the OpenGL library.

&nbsp; While I work on the OpenGL library, I do mainly benefit from the OpenGL library introductory training series of Mr. Kayhan AYAR, which can be found in the link here https://www.youtube.com/watch?v=_MhmHNbnhSs&list=PLIM5iw4GHbNW2nleNK5XIvyhZzGiaiBfp. </br>
Also, the code example belong to Mr. Kayhan AYAR.

&nbsp; For example; How to use theory of light in OpenGL or what are the functions used in OpenGL and OpenGL auxiliary libraries and what they do, etc.

<a name="siao"></a>

##  <b> Summary Information About OpenGL and Auxiliary Libs </b>
&nbsp; <b>OpenGL</b> is a cross platform library that communicates for us with the graphics card. The operations needed 2D and 3D graphics requirements such as video games, simulations, visual effects can be performed thanks to this library that can work independently on different operating systems and video cards. 

&nbsp; <b>GLFW</b> is the cross platform library of the OpenGL's auxiliary libraries. The GLFW library communicates between OpenGL and the operating system, it helps us that to manage windows, control input-output operations and similar process in OpenGL.

&nbsp; <b>GLAD</b> and <b>GLEW</b> are cross platform libraries of the OpenGL's auxiliary libraries. 

&nbsp; Programs that using OpenGL need to connect with OpenGL's dynamic library in the background while they run. OpenGL uses dynamic loading method for the programs can connect its dynamic library. The <b>GLAD</b> and <b>GLEW</b> libraries help us here. In order to connect with the OpenGL dynamic library, it is enough to use only one of the two libraries.

&nbsp; The working way of <b>GLAD</b>, the programmer tells to GLAD the function it needs instead of directly capturing the needed function addresses in OpenGL's dynamic library, and GLAD gives the address of the function needed for the programmer.

&nbsp; The working way of <b>GLEW</b>, giving programmers an easier-to-use interface by wrapping functions in the OpenGL dynamic library.


<a name="hwopengl"></a>

##  <b> How to Work OpenGL - OpenGL Pipeline </b>
* Certain steps have to be followed when drawing a shape with OpenGL.
* These certain steps are called the <b>OpenGL pipeline</b>.
* <b>A program object</b> contains these steps which called <b>OpenGL pipeline</b> in OpenGL.
* Thus, we can manage the OpenGL pipeline thanks to a program object and we can program some specific steps as we want. </br></br>

&nbsp; The steps of OpenGL pipeline which the contained in a program object for us to be able to draw a shape with OpenGL are briefly described at below.

<a name="step1"></a>

#### Step 1 - Vertex Specification

<a name="step2"></a>

#### Step 2 - Vertex Shader

<a name="step3"></a>

#### Step 3 - Tessellation

<a name="step4"></a>

#### Step 4 - Geometry Shader

<a name="step5"></a>

#### Step 5 - Vertex Post-Processing

<a name="step6"></a>

#### Step 6 - Primitive Assembly

<a name="step7"></a>

#### Step 7 - Rasterization

<a name="step8"></a>

#### Step 8 - Fragment Shader

<a name="step9"></a>

#### Step 9 - Per-Sample Operations

<a name="sfatd"></a>

##  <b> Some Functions and Their Definitions </b>







