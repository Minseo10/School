*vgg16_full.py*
1. class VGG(nn.Module): VGG 모델 정의
1) def __init__(self, features)
: initializes weights and classifiers of VGGnet
parameters
-features: CPU or GPU

2) def forward(self, x)
: forward pass method
parameters
-x: input data of block of layers

2. def make_layers(cfg, batch_norm=False)
: this method makes layers of VGGnet and return the sequence of layers
parameters
-cfg: this shows the layers in VGG-16. 
       If a layer is a max pooling layer, then 'M', and if not, then it shows the kernel size.
-batch_norm: if true, then implement batch normalization using BatchNorm2d(), 
                  and if false, then don't perform batch normalization

3. def vgg16()
: This method defines the layers in VGG-16 (save them in 'cfg') and retrn the VGG class

*resnet50_skeleton.py*
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

4. class ResNet50_layer4(nn.Module)
: ResNet-50 with 4 big Layers(Layer1~Layer4)

1) def __init__(self, num_classes=10)
: this method implements Layers from self.layer1 to self.layer4 using ResidualBlock classes
parameters
-num_classes: # of classes in CIFAR-10 dataset. defualt value is 10.

2) def forward(self, x)
:  forward pass method
parameters
-x: input data of ResNet-50
-> return value: total output if ResNet-50


*main.py*
1. Choose model
1) when implementing ResNet50
model = ResNet50_layer4().to(device)
#PATH = './resnet50_epoch285.ckpt'
2) when implementing VGG16
model = vgg16().to(device)
PATH = './vgg16_epoch250.ckpt'


2. def update_lr(optimizer, lr)
: this method updates the learning rate
parameters
-optimizer: adam optimizer
-lr: learning rate
