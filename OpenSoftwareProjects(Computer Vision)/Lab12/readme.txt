*UNet.py*
1. def conv(in_channels, out_channels)
: convolutional network consists of two 3x3 convolutions, each followed by a ReLU and 2x2 max pooling operation
parameters
-in_channels: # of input channels
-out_channels: # of output channels

2. class Unet(nn.Module)
: UNet 모델 정의

1) def __init__(self, in_channels, out_channel)
: initializes convolutions, maxpooling, and upsampling
parameters
-in_channels: # of input channels
-out_channels: # of output channels

2) def forward(self, x)
: forward pass method
parameters
-x: input image file
return value: output segmentation map


*resnet_encoder_unet.py*
1. def conv1x1(in_channels, out_channels, stride, padding)
: 1x1 convolution method
parameters
-in_channels: input channel size
-out_channels: output channel size
-stride: stride size
-padding: zero padding size

2. def conv3x3(in_channels, out_channels, stride, padding)
: 3x3 convolution method
parameters
-in_channels: input channel size
-out_channels: output channel size
-stride: stride size
-padding: zero padding size

3. class ResidualBlock(nn.Module)
: this class implements bottle neck building block

1) def __init__(self, in_channels, middle_channels, out_channels, downsample=False)
: initializes the residual block
paramters
-in_channels: input channel size
-middle_channels: 중간 단계의 channel size
-out_channels: output channel size
-downsample: downsampling 여부

2) def forward(self, x)
:  forward pass method
parameters
-x: input data of residual block
-> return value: out+x

4. def conv(in_channels, out_channels)
: convolutional network consists of two 3x3 convolutions, each followed by a ReLU and 2x2 max pooling operation
parameters
-in_channels: # of input channels
-out_channels: # of output channels

5. class UNetWithResnet50Encoder(nn.Module)
: U-Net with ResNet encoder 모델 정의

1) def __init__(self, n_classes=22)
: this method implements Layers from self.layer1 to self.layer3 using ResidualBlock classes 
/ define convolutions of decoder part(UNet)
parameters
-num_classes: # of classes in dataset. defualt value is 22.

2) def forward(self, x, with_output_feature_map=False)
: foward pass method
parameters
-x: input of total architechture (input image file)
return value: total output of U-Net with ResNet encoder


*modules.py*
1. def train_model(trainloader, model, criterion, optimizer,scheduler, device)
: Implement the train/test module
parameters
-trainloader: loaded training datas
-model: model we will use
-criterion: cross entropy loss
-optimizer: adam optimizer
-scheduler: scheduler we will use
-device: cpu or gpu

2. def accuracy_check(label, pred)
: accuracy checking method
-label: label of image
-pred: ith element of preds
return value: accuracy

3. def accuracy_check_for_batch(labels, preds, batch_size)
:accuracy checking method for batch
-label: label of image
-pred: argmax of input
-batch_size: batch size of data
return value: total accuracy per batch size


4. def get_loss_train(model, trainloader, criterion, device)
: computing total loss and total accuracy
-model: model we will use
-trainloader: loaded training datas
-criterion: cross entropy loss
-device: cpu or gpu
return value: total loss and total accuracy

5. def val_model(model, valloader, criterion, device, dir)
: validating model data
-model: model we will use
-valloader: loaded data of valid sets
-criterion: cross entropy loss
-device: cpu or gpu
-dir: directory of results
return value: total valid loss and total valid accuracy

*main.py*
1. Initialize the model
1) UNet: model = Unet()
2) resnet_encoder_unet: model = UNetWithResnet50Encoder()
2. load the model parameter
1) UNet: model.load_state_dict(torch.load('./trained_model/UNet_trained_model.pth'))
2) resnet_encoder_unet: model.load_state_dict(torch.load('./trained_model/resnet_encoder_unet.pth'))

*datasets.py*
1. class Loader(Dataset)
: dataset
1) def _check_exists(self)
: check if data exists

2) def VOCdataloader(self, index)
: Loda Pascal VOC data


3) def __init__(self, VOC2012_dir, flag, resize, transforms)
: test and train data

4) def __len__(self):
return length of imagenames

5) def __getitem__(self, index)
: return image and masks