# Neural Net Weights file format
All integers are Big endian

Header:
Type      Size       Desc.
uint16    2 bytes    Magic number 0x0C40 
size_t    8 bytes    Number of layers
size_t    8 bytes    (C) Number of inputs

The header is followed by the described number of layers.

size_t    8 bytes    (R) Number of output neurons
then,  R*C doubles describing the weights, indexed as [row][column].
each column represents a single neuron in this layer.

Following that, R doubles for the biases of the layer.
C for the next layer is R for the previous layer.