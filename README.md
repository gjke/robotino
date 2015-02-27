This project was developed during the Bachelor thesis at the Hochschule Mannheim. 
Main idea is to navigate the robot "Robotino" produced by Festo Didactic in an 
unknown environment.It should follow an object with the given properties and try to 
avoid the obstacles on its way. Instead of using directly the Robotino API custom function 
blocks for the program "Robotino View" have been developed.

Image processing is being done using the OpenCV library. The controlling of the robot is
accomplished with a simple feed forward neural network using the FANN (Fast Artificial Neural Netowrk) library.

<img src = "http://www.ros.org/news/assets_c/2010/06/Robotino_Imagefoto-thumb-640x501-98.jpg">

Here is a short guide how to get the openCV library work in Windows and make it accessable in Visual Studio 2010
<a href="https://github.com/gjke/robotino/wiki/New-Function-Block-for-RobotinoView-2-with-openCV">Install and use OpenCV</a>

Here is a short guide how to get the FANN library work in Windows and make it accessable in Visual Studio 2010
<a href="https://github.com/gjke/robotino/wiki/New-Function-Block-for-RobotinoView-2-with-FANN">Install and use OpenCV</a>
