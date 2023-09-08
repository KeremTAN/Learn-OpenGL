#  <b> Learn OpenGL </b>
* [Aim of This Repository](#aim)
* [Summary Information About OpenGL and Auxiliary Libs](#siao)
* [How to Work OpenGL - OpenGL Pipeline](#hwopengl)
    * [Step 1 - Vertex Specification](#step1)
    * [Step 2 - Vertex Processing](#step2)
        * [Step 2.1 - Vertex Shader](#step21)
        * [Step 2.2 - Tessellation](#step22)
        * [Step 2.3 - Geometry Shader](#step23)
    * [Step 3 - Vertex Post-Processing](#step3)
    * [Step 4 - Primitive Assembly](#step4)
    * [Step 5 - Rasterization](#step5)
    * [Step 6 - Fragment Shader](#step6)
    * [Step 7 - Per-Sample Operations](#step7)
<!-- * [Some Functions and Their Definitions](#sfatd) -->

<a name="aim"></a>

## <b> Aim of This Repository </b>
&nbsp; The aim of this project is to study how 3D computations and linear algebra are implemented in computer science with the OpenGL library.

<!--
&nbsp; While I work on the OpenGL library, I do mainly benefit from the OpenGL library introductory training series of Mr. Kayhan AYAR, which can be found in the link here https://www.youtube.com/watch?v=_MhmHNbnhSs&list=PLIM5iw4GHbNW2nleNK5XIvyhZzGiaiBfp. </br>
Also, the code example belong to Mr. Kayhan AYAR.
-->
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

### Step 1 - Vertex Specification
&nbsp; The programmer <b>can not</b> do <b>any</b> changing or interventions in Vertex Specification.  <p>
&nbsp; For example, we want to draw a triangle on the monitor. </br>
&nbsp; Each corner point of the triangle to be drawn is called <b>a vertex</b> and <b>each vertex</b> has x, y and z coordinates data in the drawing area.</br>

&nbsp; Simple shapes drawn using vertices are called <b>primitives</b>.</br>
&nbsp; The triangle shape which wanted to draw that is <b>a primitive</b> in this  example. </br>

&nbsp; <b> The vertices data are set for the primitive/primitives can be rendered in Vertex Specification</b>. </br>

<a name="step2"></a>

### Step 2 - Vertex Processing

&nbsp; Points called vertex in the previous step begin to be processed for rendering in this step. <p>

&nbsp; This step consists of several sub-steps. Technically, some other steps contain several sub-steps, but the their sub-steps will not be explained separately. The reason for explaining the sub-steps in this step is that programmers can directly change or intervene to processing with the sub-steps in here.</br>

<a name="step21"></a>

#### Step 2.1 - Vertex Shader

&nbsp; The programmer <b>can</b> do <b>some</b> changings or interventions in Vertex Shader. <p> 

&nbsp; <b>The aim of Vertex Shader</b> is to geometrically calculate the position and features of the 2D/3D model to be created by using vertices. </br>
&nbsp; Some interventions are made using with <b>GLSL commands</b> in this step.</br>
&nbsp; The vertex data sent from previous step to this step comes as <b>bit data</b>.</br>
&nbsp; The type of the bit data <b>can be labeled</b> when writing GLSL commands in this step.</br>
&nbsp; For example, <b><i>layout(location=0)</i></b> command is used to indicate that the vertex data received in the previous step is <b>a location data</b>.</br> 

&nbsp; Moreover, the vector sent in the previous step that <b>is transformed from a 3-element vector (x, y, z coordinates) to a 4-element vector</b> in this step. To do this transformation, 1 is added to the end of the vertex data.  </br>
&nbsp; In this way, the new vector is converted to <b>[x, y, z, 1]</b>.</br>

&nbsp; <b>The purpose of this vector transformation is so that the matrix multiplication can be done correctly </b> in the next steps. </br>

&nbsp; The reason for adding 1 to end of the vertices data which is that <b>the number 1 is an ineffective element in the multiplication process</b>.  </br>

&nbsp; <b>In other words, the purpose is that the matrix multiplications in the next steps can be done without distorting the original data</b>.  </br>

<a name="step22"></a>

#### Step 2.2 - Tessellation

&nbsp; The programmer <b>can</b> do <b>some</b> changings or interventions in Tessellation.<p> 

&nbsp; The data sent from previous step can be <b>converted into smaller primitives</b> in this step because <b> more detail and complexity can be added </b> dynamically to 3D surfaces by breaking the primitives into smaller pieces. </br>
&nbsp; <b>The model/shape</b> which wanted to create that can be <b>converted more realistic</b> in this way. </br>

<a name="step23"></a>

#### Step 2.3 - Geometry Shader

&nbsp; The programmer <b>can</b> do <b>some</b> changings or interventions in Geometry Shader.<p> 

&nbsp; Geometry Shader is <b>logically similar</b> to Vertex Shader. </br>
&nbsp; <b>More complex and new primitives are created by using the primitives</b> sent from the previous step <b> in the Geometry Shader</b>, just like that geometric shapes are created by using vertices in the Vertex Shader. </br>

&nbsp; For example, a hexagon are created by using triangle shapes. </br>

<a name="step3"></a>

### Step 3 - Vertex Post-Processing

&nbsp; The programmer <b>can not</b> do <b>any</b> changing or interventions in Vertex Post-Processing.<p>

&nbsp; <b>Values calculated in Vertex and Geometry Shader can be saved</b> in this step if wish.<p>
&nbsp; In addition, <b>clipping processing</b> is done in here. </br>
&nbsp; <b>The drawing area</b> which contains the shape wanted to create <b>can be larger than the monitor</b> on which the shape will be displayed. </br>
&nbsp; Unnecessary calculations are prevented by removing primitives that cannot be displayed on the monitor from the drawing screen in this step.</br>

<a name="step4"></a>

### Step 4 - Primitive Assembly

&nbsp; The programmer <b>can not</b> do <b>any</b> changing or interventions in Primitive Assembly.<p>

&nbsp; Vertices are processed as a series and new shapes are rendered from these series in this step.</br>
&nbsp; For example, drawing 3 triangles from a 9-element vertex series.</br>

&nbsp; In addition, <b>Face Culling</b> is done in this step. </br>
&nbsp; <b>Face Culling processing means that</b> invisible or too far to be seen in perspective primitives are in our drawing area removed from the drawing area.</br>

<a name="step5"></a>

### Step 5 - Rasterization

&nbsp; The programmer <b>can not</b> do <b>any</b> changing or interventions in Rasterization.<p>

&nbsp; Geometric shapes created in the previous step <b>are converted into pixels </b> called <b>fragment data</b> in this step.

&nbsp; <b>Information such as the color and depth of each pixel</b> of the shape/model to be wanted drawing is stored <b>in the fragment data</b> for the next step.

<a name="step6"></a>

### Step 6 - Fragment Shader

&nbsp; The programmer <b>can</b> do <b>some</b> changings or interventions in Fragment Shader.<p> 

&nbsp; <b>Pixels named as fragment data</b> in the previous step are processed in this step. In particular, <b> the coloring of each pixel </b> of the created shape/model is done at this stage.

&nbsp; In addition to coloring the pixels in this step, operations such as shading and lighting of each pixel are also processed.

<a name="step7"></a>

### Step 7 - Per-Sample Operations

&nbsp; The programmer <b>can not</b> do <b>any</b> changing or interventions in  Per-Sample Operations.<p>

&nbsp;  First of all, <b>Depth Test</b> is performed in this step. <b>The Depth Test</b> is the stage of whether the fragment data to be wanted drawing <b>will draw or not.</b></br>
&nbsp; For example; If there is another fragment data in front of the fragment data to be wanted drawing, the fragment data to be drawn will fail for the depth test.

&nbsp; Moreover, <b>Color Blending</b> is performed in this step. Using the operations described in the previous steps, the colors in the fragment data are mixed with each other and interact with overlapping fragments in this stage.

&nbsp; <b>As a result of all these steps, the rendering process of the 2D/3D scene is completed and the final shape/model is created</b>.

<a name="sfatd"></a>

<!-- ##  <b> Some Functions and Their Definitions </b> -->