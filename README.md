# Oil Spill Detector
This is an underwater oil spill detector which uses 2 light dependent resistors to compare the light intensity in each sensors. The sensor reading values vary when an unidentified object obstructs light which is directed to the light dependent resistor.

The sensor data is sent to Firebase Realtime Database and can be viewed through web, iOS, and Android. For more information about Google Firebase, visit this link:

[Google Firebase](https://firebase.google.com/)

This project uses NodeMCU v1.0, 2 light dependent resistors, and an additional 4051 multiplexer IC.

![alt-text](http://i66.tinypic.com/28la0at.jpg)

The controller unit compares two sensor values. One sensor is normalized (placed above water surface), and the other one will be the actual sensor which detects whether there's an obstruction in light or not (placed underwater). The controller unit can be programmed to have a certain threshold until it can detect light obstruction. You might want to experiment with the sensors yourself to fit your conditions and find the right threshold value.

Below is the circuit of this project:

![alt-text](http://i67.tinypic.com/2rd88dd.jpg)