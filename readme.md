# CS331 Optical Character Recognition
This Project aims to use a simple feed-forward neural network to recognize digits using the well-known MNIST dataset. Using a feed-forward neural network allows for the ability to dynamically adjust weights, based on a loss function and back propagation, that our model uses to predict the character of an image using a multi-class output (0-9).  This project has many different use cases, such as identifying a digit (and whole numbers) on handwritten forms in an automated way.

This group project was made for CS 33100 Introduction - C++ and Object Oriented Programming at Purdue University Fort Wayne.

## Background
A neural network is inspired from real biological neurons. Each neuron has inputs, which are floating point numbers, for each input, the neuron also has a weight, which determines how strongly the neuron will react to changes in that input. The weights are multiplied by their inputs and summed, then passed through an activation function (in our case, the sigmoid function) to clamp the neuron’s output between sensible values. In a feed-forward neural network, Neurons are arranged in layers. There’s an input layer, potentially several ‘hidden layers’ and the output layer. In our case, each pixel of the input image is an input neuron, and we have 10 output neurons to represent each digit. We have two hidden layers with 64 and 32 neurons each.

### How do you train a neural net?
The behavior of a neural network is dependent on all its weights and biases. 
In our case, there are 52,650 of them. This makes it a very difficult problem to know which weights to adjust, and how much, to make the network behave how we want. You can assign a cost function to the network based on the difference between its output and the expected output. By finding the derivative of the cost function with respect to every weight, you can find the direction (gradient) that would lower the cost function the most. By doing this repeatedly for different inputs, you can lower the overall cost function of the network and make it behave like you want.

All you have to do is a 52,650 dimension calculus problem, basically. How hard can that be?


## How To use




## Class Structure



## Build Instructions 
This project uses cmake. To build, create a folder for output files. We called this folder 'build'.

run `cmake -S . -B output_folder` to do initial cmake generation for first-time setup, then, to build the project, run `cmake --build output_folder`

Output executables should be found somewhere in output_folder, depending on the build system cmake decided to use.

### Geting Training Data

