//
//  main.cpp
//  nn
//
//  Created by Sergii Poluektov on 12/2/14.
//  Copyright (c) 2014 Sergii Poluektov. All rights reserved.
//

#include <iostream>
#include <string>
#include "fann.h"
#include <math.h>
#include <stdio.h>
using namespace std;

string readString (string message, string def);
int readInt (string message, int def);
bool readBool(string message);
float readFloat(string message, float def);
string readFilename(string message, string mode);

void train();
void test();
void quick();

int main()
{
    int mode;
    if ((mode = readInt("Should the network be created and trained(1) or tested(2)? Training by default", 1)) == 1)
    {
        train();
    }
    else if (mode == 2)
    {
        test();
    }
    else if (mode == 3)
    {
        quick();
    }
}

void train()
{
    const unsigned int num_layers = readInt("Please, enter the number of layers (3, 4 or 5). 3 by default", 3);
    int* neurons_in_layers = new int[num_layers-2];
    switch (num_layers)
    {
        case 3: neurons_in_layers[0] = readInt("Please, enter the number of neurons in the 1 hidden layer. 1 by default", 1);
            break;
        case 4: neurons_in_layers[0] = readInt("Please, enter the number of neurons in the 1 hidden layer. 1 by default", 1);
                neurons_in_layers[1] = readInt("Please, enter the number of neurons in the 2 hidden layer. 1 by default", 1);
            break;
        case 5: neurons_in_layers[0] = readInt("Please, enter the number of neurons in the 1 hidden layer. 1 by default", 1);
                neurons_in_layers[1] = readInt("Please, enter the number of neurons in the 2 hidden layer. 1 by default", 1);
                neurons_in_layers[2] = readInt("Please, enter the number of neurons in the 3 hidden layer. 1 by default", 1);
            break;
    }
    const float desired_error = readFloat("Please, enter the desired error. 0 by default" , 0);
    const unsigned int max_epochs = readInt("Please, enter the maximum number of epochs. 1000 by default", 1000);
    const unsigned int epochs_between_reports = readInt("Please, enter how often the report should be shown. 100 epochs by default", 100);
    
    string train_data_file = readFilename("Please, enter the full path to the file with the training data", "r");
    struct fann_train_data* train_data = fann_read_train_from_file(train_data_file.c_str());
    struct fann* ann;
    switch (num_layers)
    {
        case 3: ann = fann_create_standard(num_layers, train_data->num_input, neurons_in_layers[0], train_data->num_output);
            break;
        case 4: ann = fann_create_standard(num_layers, train_data->num_input, neurons_in_layers[0], neurons_in_layers[1], train_data->num_output);
            break;
        case 5: ann = fann_create_standard(num_layers, train_data->num_input, neurons_in_layers[0], neurons_in_layers[1], neurons_in_layers[2], train_data->num_output);
            break;
    }
    fann_init_weights(ann, train_data);
    
    const unsigned int activation_function_hidden = readInt("Please, specify the activation function for the hidden layers. Default Sigmoid", 3);
    fann_set_activation_function_hidden(ann, static_cast<fann_activationfunc_enum>(activation_function_hidden));
    const unsigned int activation_function_output = readInt("Please, specify the activation function for the output layer. Default Linear", 0);
    fann_set_activation_function_output(ann, static_cast<fann_activationfunc_enum>(activation_function_output));
    const unsigned int training_algorithm = readInt("Please, specify the training algorithm. Default RPROP", 2);
    fann_set_training_algorithm(ann, static_cast<fann_train_enum>(training_algorithm));
    const float new_input_min = readFloat("Please, enter the min value vor the scaled input. -0.5 by default", -0.5);
    const float new_input_max = readFloat("Please, enter the max value vor the scaled input. 0.5 by default", 0.5);
    const float new_output_min = readFloat("Please, enter the min value vor the scaled ouput. -0.5 by default", -0.5);
    const float new_output_max = readFloat("Please, enter the max value vor the scaled output. 0.5 by default", 0.5);
    fann_set_input_scaling_params(ann, train_data, new_input_min, new_input_max);
    fann_set_output_scaling_params(ann, train_data, new_output_min, new_output_max);
    fann_scale_train( ann, train_data );
    
    string save_file = readFilename("Please, enter the name of the output file", "w");
    fann_train_on_data(ann, train_data, max_epochs, epochs_between_reports, desired_error);
    fann_save(ann, save_file.c_str());
    printf("Network saved\n");
    fann_destroy(ann);
    fann_destroy_train(train_data);
    
}
void test()
{
    string net_file = readFilename("Please, enter the name of the file with the network settings", "r");
    string test_data_file = readFilename("Please, enter the full path to the file with the test data", "r");
    struct fann *ann = fann_create_from_file(net_file.c_str());
    struct fann_train_data* test_data = fann_read_train_from_file(test_data_file.c_str());
    
    float* o;
    fann_reset_MSE(ann);
    for(int i = 0; i < fann_length_train_data(test_data); i++)
    {
        fann_scale_input(ann, test_data->input[i]);
        fann_test(ann, test_data->input[i], test_data->output[i]);
        o = fann_run(ann, test_data->input[i]);
        fann_descale_output(ann, o);
        
        cout<<i<<" ";
        for (int k = 0; k < test_data->num_output; k++)
        {
            printf("%f (%f) ", *(o+k), test_data->output[i][k]);
        }
        cout<<endl;
    }
    
    printf("MSE error on test data: %f\n", fann_get_MSE(ann));
    
}

void quick()
{
    const unsigned int num_layers = 3;
    const float desired_error = 0.001;
    const unsigned int max_epochs = 3000;
    const unsigned int epochs_between_reports = 200;
    struct fann_train_data* train_data = fann_read_train_from_file("/Users/sergii/cprojects/nn/tsets/with8zero.train");
    struct fann* ann = fann_create_standard(num_layers, train_data->num_input, 10, train_data->num_output);
    fann_set_activation_function_hidden(ann, FANN_SIGMOID);
    fann_set_activation_function_output(ann, FANN_LINEAR);
    fann_set_training_algorithm(ann, FANN_TRAIN_RPROP);
    fann_set_input_scaling_params(ann, train_data, -0.5, 0.5);
    fann_set_output_scaling_params(ann, train_data, -0.5, 0.5);
    fann_set_learning_rate(ann, 0.9);
    fann_set_learning_momentum(ann, 0);
    
    /*
    fann_set_rprop_decrease_factor(ann, 0.5);
    fann_set_rprop_increase_factor(ann, 1.2);
    fann_set_rprop_delta_max(ann, 50);
    fann_set_rprop_delta_min(ann, 0);
     */
    
    //fann_set_activation_steepness(ann, 10, 2, 0);
    //fann_set_activation_steepness(ann, 10, 2, 1);
    fann_set_activation_steepness(ann, 0.1, 2, 2);
    
    struct fann_train_data* test_data = fann_read_train_from_file("/Users/sergii/cprojects/nn/tests/with8zero.test");
    fann_scale_train( ann, train_data );
    
    //for (int j = 0; j < 30; j++)
    //{
        //srand(time(0));
    //fann_randomize_weights(ann, -0.1, 0.1);
        fann_init_weights(ann, train_data);
        //float better = 10000;
        //int eps = 1;
        
        //while (eps < 5000)
        //{
           // fann_train_epoch(ann, train_data);
        //    eps++;
         
            fann_train_on_data(ann, train_data, max_epochs, epochs_between_reports, desired_error);
            fann_save(ann, "/Users/sergii/cprojects/nn/nets/with8zero.net");
            float* o;
            fann_reset_MSE(ann);
    
            for(int i = 0; i < fann_length_train_data(test_data); i++)
            {
                fann_scale_input(ann, test_data->input[i]);
                fann_scale_output(ann, test_data->output[i]);
                fann_test(ann, test_data->input[i], test_data->output[i]);
                o = fann_run(ann, test_data->input[i]);
                fann_descale_output(ann, o);
                fann_descale_output(ann, test_data->output[i]);
        
                cout<<i<<" ";
                for (int k = 0; k < test_data->num_output; k++)
                {
                    printf("%f (%f) ", *(o+k), test_data->output[i][k]);
                }
                cout<<endl;
            }
            //better = better - fann_get_MSE(ann);
            //cout<<fann_get_MSE(ann)<<endl;
        //}
    
        printf("MSE error on test data: %f\n",fann_get_MSE(ann));
//}

}




string readString (string message, string def)
{
    cout<<message<<endl;
    string s;
    getline(cin, s);
    if (s.empty()) {return def;}
        else return s;
}
int readInt (string message, int def)
{
    cout<<message<<endl;
    string s;
    getline(cin, s);
    if (s.empty()) {return def;}
        else {return atoi(s.c_str());}

}
bool readBool(string message)
{
    cout<<message<<endl;
    string s;
    getline(cin, s);
    if ((s.length() == 1) && (s[0] == 'y'))
    {
        return true;
    }
    else if ((s.length() == 1) && (s[0] == 'n'))
    {
        return false;
    }
    else
    {
        return readBool(message);
    }
}
float readFloat(string message, float def)
{
    cout<<message<<endl;
    string s;
    getline(cin, s);
    if (s.empty()) {return def;}
    else {return atof(s.c_str());}
}
string readFilename(string message, string mode)
{
    cout<<message<<endl;
    string s;
    getline(cin, s);
    if (FILE* file = fopen(s.c_str(), mode.c_str()))
    {
        fclose(file);
        return s;
    }
    else
    {
        cout<<"File not found ";
        return readFilename(message, mode.c_str());
    }
    
}
