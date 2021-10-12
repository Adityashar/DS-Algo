# Low light image enhancement


## Major Project


## Situation

It was the start of my 8th semester, and as a part of each college's curriculum, we are supposed to do a research thesis and in our college grade allocation is based on the type of conf or journal the paper is published in. 



## Task

now the task was to develop a novel method for low-light image enhancement which outperforms the results of current sota methods 

given the timeframe and deadline of three months along with a perputual college routine of classes and exams, this was a real challenging task. Also, the requirement of publishing the paper in a scopus indexed or international conf/journal makes it even more challenging.


## Action

I can divide my work into stages: 

First, i did the LR, and i studied the classical, conventional and current approaches.

Next, i reproduced the results of some of the prev methods on our dataset. I used the predicted normal light images to calculate different metrics like niqe and brisque.

These scores was used for the evaluation and comparison of our method with them. 


Also, in our method, since this was an i to i translation task we chose to go with an unsupervised cycle consistent network. So in this network, i played with the gen and disc nets, added diff losses and performed an ablation study. 

gen - resnet, unet, unet++;

disc - patchgan -> pix2pixGan


## Result

Once the paper was written, we published it at scopus indexed national level conf.

reminiscing this situation, i feel did follow some of the AMLP

invent & Simp
learn & Cur
Frugality
High standards
think big


Training is computationally heavy, res were scarce, (colab), it 2-3 days. and running it repeatedly with diff config which i used to perform an ablation study consumed a lot of time and i did miss my deadline of march beg.

The architecture work was complete gen performing better than my exp, TV improved to the quality of results, but my evalutions and experiments with prev were still remaining.

The task was huge and hence i missed my deadline of march start, rather was completed by april, and then getting the paper published in a months time was a real worry given evaluations were to happen in may


our mentor wasnt actually impressed because we wanted a journal paper, given the time frame before the may eval, we decided on conf

journals takes time, are exp. reimbursements are also very rare.





CNN, special type of NNs which were designed to work on image and video related spatial data. Each convolution layer has a filter. These filters or kernels are used for pattern recognition by the network.



GANs, which were intended to perform the task of generation as the name says.

Gen and disc subnetworks combination. the generator, which generates new samples statistically similar to the input set, and the discriminator which classifies the output from the generator as either real (could be part of input data set) or fake (generated). Both these networks are then trained together in a zero-sum game until the generator starts generating plausible samples which are capable of fooling the discriminator. 