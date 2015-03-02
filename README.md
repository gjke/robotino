### General information

This project was developed during the Bachelor thesis at the Hochschule Mannheim. 
Main idea is to navigate the robot "Robotino" produced by Festo Didactic in an 
unknown environment.It should follow an object with the given properties and try to 
avoid the obstacles on its way. Instead of using directly the Robotino API custom function 
blocks for the program "Robotino View" have been developed.

Image processing is being done using the OpenCV library. The controlling of the robot is
accomplished with a simple feed forward neural network using the FANN (Fast Artificial Neural Netowrk) library.

<img src = "http://www.ros.org/news/assets_c/2010/06/Robotino_Imagefoto-thumb-640x501-98.jpg">

### Links to the documentation

Here is a short guide how to get the openCV library work in Windows and make it accessable in Visual Studio 2010</br>
<a href="https://github.com/gjke/robotino/wiki/New-Function-Block-for-RobotinoView-2-with-openCV">Install and use OpenCV</a>

Here is a short guide how to get the FANN library work in Windows and make it accessable in Visual Studio 2010</br>
<a href="https://github.com/gjke/robotino/wiki/New-Function-Block-for-RobotinoView-2-with-FANN">Install and use FANN</a>

Here one can find the information about the data sets, test sets and network training
<a href="https://github.com/gjke/robotino/wiki/Network-training">Train and test a neural network</a>

### Todo List
- [ ] FB NN. Setting of the path to the configuration file through the FB gui.

- [ ] FB WriteTrainingSet. Setting of the path to the training set through the FB gui.

- [ ] FB CombineIntoVector. Fix the bug with the last output being 0 if the last input is empty.
