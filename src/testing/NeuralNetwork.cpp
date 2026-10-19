#include <iostream>
#include <cassert>
#include "neural_network/neuralNetwork.h"

void createRandomAndWrite()
{
    std::cout<<"Creating random network...\n";
    ocr::NeuralNetwork<double> nn(4, 3, std::vector<size_t>({2}));
    nn.randomizeNetwork();
    nn.print();
    std::cout<<"Writing to file.\n";
    nn.writeToFile("output/test");
    
    std::cout<<"\n\nReading same network from file...(CHECK THEY ARE THE SAME)\n";
    // no == overload on networks so it's a manual check here.
    ocr::NeuralNetwork<double> nn2("output/test.ocrweights");
    nn2.print();
}

ocr::NeuralNetwork<double>* createTestNetwork()
{
    auto nn = new ocr::NeuralNetwork<double>(4, 3, std::vector<size_t>({2}));
    
    // biases are zero because I'm lazy.
    // test it, though
    nn->setBias(0, 0, 1); 
    assert(nn->getBias(0,0)==1);
    nn->setBias(0,0,0);

    // 
    nn->setWeight(0, 0, 0, 1);
    nn->setWeight(0, 1, 0, -1);
    // zero weights will be ignored

    nn->setWeight(0, 2, 1, -1);
    nn->setWeight(0, 3, 1, 1);

    // Layer 2. 
    nn->setWeight(1, 0, 0, 1);
    nn->setWeight(1, 0, 1, .5);
    nn->setWeight(1, 1, 1, .5);
    nn->setWeight(1, 1, 2, 1);

    assert(nn->getWeight(1, 0, 1)==.5);

    return nn;

}
void evalTest(ocr::NeuralNetwork<double>* nn, std::initializer_list<double> input)
{

    ocr::Vector<double> input1(input);
    std::cout<<"\n\n Eval with input: ";
    input1.visualize();    
    nn->evaluate(input1).visualize();
}

int main(void)
{
    std::cout<<"Hello!\n";
    createRandomAndWrite();
    std::cout<<"\n\nCreating Test network:\n";
    auto nn = createTestNetwork();
    nn->print();

    evalTest(nn, {1, 0, .6, .4});
    evalTest(nn, {.3, .7, 0, 1});
    evalTest(nn, {1, 0, 0, 1});
    evalTest(nn, {0, 1, 1, 0});


    delete nn;


}