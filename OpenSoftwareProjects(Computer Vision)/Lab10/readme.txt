*neural_net.py*

1. def __init__(self, input_size, hidden_size, output_size, std=1e-4):
: initializes the model. Weights are initialized to small random values and biases are initialized to zero.

parameters
- input_size:  dimension D of the input data. 
- hidden_size:  number of neurons H in the hidden layer.
- output_size:  number of classes C


2. def loss(self, X, y=None, reg=0.0)
: compute the loss and gradients for a two layer fully connected neural network

parameters
- X: input data of shape (N, D)
- y: vector of training labels -> y[i] is the label for X[i] (0 <= y[i] < C) 
     if this parameter is not passed then we only return scores 
     if it is passed then we return the loss and gradients with scores
- reg: regularization strength

return
If y is None-> return a matrix scores of shape (N, C) 

If y is not None, returns
    - loss: Loss (data loss and regularization loss)
    - grads: gradients of those parameters with respect to the loss function


3. def train(self, X, y, X_val, y_val, learning_rate=1e-3, learning_rate_decay=0.95,
            reg=5e-6, num_iters=100, batch_size=200, verbose=False)
: Train neural network using stochastic gradient descent.

parameters
    - X: array of shape (N, D) giving training data.
    - y: array of shape (N,) giving training labels -> y[i] = c means that
         X[i] has label c
    - X_val: array of shape (N_val, D) giving validation data
    - y_val: array of shape (N_val,) giving validation labels
    - learning_rate: learning rate for optimization.
    - learning_rate_decay: Scalar giving factor used to decay the learning rate
      after each epoch
    - reg: regularization strength.
    - num_iters: # of iterations we should take when optimizing
    - batch_size: # of training examples to use
    - verbose: if true then print progress during optimization.

returns
-loss history, train_acc_history, val_acc_history


4. def predict(self, X)
: Use the trained weights of this two-layer network to predict labels for
data points. For each data point we predict scores for each of the C
classes, and assign each data point to the class with the highest score.

paramters
- X: array of shape (N, D) giving N D-dimensional data points to classify.

Returns   
 - y_pred: array of shape (N,) giving predicted labels for each of the elements of X.
            e.g) y_pred[i] = c means X[i] is predicted to have class c (0 <= c < C)



*two_layer_net.ipynb*

1. def rel_error(x, y)
: returns relative error
parameters
-x,y: we will calculate relative error of x and y

2. def init_toy_model()
: initializes toy model

3. def init_toy_data()
: initializes toy data

4. def get_CIFAR10_data(num_training=19000, num_validation=1000, num_test=1000)
:  loads the CIFAR-10 dataset and perform preprocessing to prepare it for the two-layer neural net classifier.

paramters
-num_training: number of trainging datas
-num_validation: number of validation datas
-num_test: number of test datas

5. def show_net_weights(net)
: visualizes the weights of the network

paramters
-net: network we will visualize
