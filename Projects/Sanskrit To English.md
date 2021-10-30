# Machine Translation

## Situation

In the 5th semester of my college time, i was involved in a bit of research based projects for one of the labs at DTU.

So the most challenging, rather i should say, the most enlightening of those projects was related to NLP, to be precise, Machine Translation.

I was doing this project with one of seniors, under mentorship of a CS Profesor at DTU, and the timeline for this project was actually very flexible, considering that covid had hit the world this year and most of the conferences were getting rescheduled.


## Task

As a part of this project, i was supposed to build a sans to eng mt system using different deep learning approaches and compare the performance of each.

Now while doing this i faced a series of hurdles -

Data preparation
1. sans is a low res language, less data, and machine translation - be it nmt, rbmt or pbmt - all are res intensive tasks. So first challenge was accumulating all the available sa-en parallel data, monolingual data for each of the langs.


Data Cleaning and Preprocessing - 

1. For english, the preprocessing pipeline remains almost same for all NLP tasks but for sans i had to research and setup some indic lang based preprocessors.




Model selection
2. Selecting an appropriate DL MT technique for this task.


Quantification
3. Obtaining to a robust, high performance system to code, experiment and improve the quantified results.


## Actions


1. For each lang, we have a strict grammar syntax, sematics, structure, rules, dictionary of words, which have to be followed and obtained before performing any neural task on it. For the data collection, i used historical and cultural texts like ramayana, mahabharata and the vedas. around 6k parallel and 150k monolingual data. enormous amounts of data is needed for learning these relationships

We use the Moses tokenizer for English and
the IndicNLP tokenizer for Hindi

2. DL MT - supervised or unsupervised.

supervised - seq2seq lstms, and the more recent transformers, pretty straight forward MT while using the existing tech. but they require data in millions of phrase and we had in thousands - gave decent results.

my tasks were focussed on unsupervised which are focussed on lang modelling using monolingual data - now for this purpose i had to explore all of the existing tech, dual learning from ms, xlm from facebook, transfer learning approach, backtranslation, reinforcement learning.

i tested the data on each of the above mentioned tech gave results much better than the simple nmt.


word embeddings
positional encodings
Byte Pair encodings


## Result

BLEU Score - ngram matching bw ref and orig
ICON 2020


L and be curious
Frugality
Deep dive
high standards
invent and S



1. How does google translate work?

	

2. Design data preprocessing pipeline

	cleaning data so as to removie noise and unnessary data points that may hamper the training process

		1. sentence based tokenisation, case conversion and removal of special chars
		2. removal of stop words, links, html tags etc
		3. stemming and lemmatization - trimming a word to its root (good, better, best) -> lemmatizer not stemmer

		once done, recurate the old dataset by joining the tokens in the same phrase wise manner

	for the sans, similar pipeline was used but different tools and libs were involved, (moses and nltk) -> IndicNLP Library.


3. Explain ANN, CNN, RNN

	perceptron is the basic unit of a nn which transforms the incoming inputs, weights and biases into an output, the weight & bias which are updated in the backpropagation step.

	ANN -

	multilayered collection of perceptrons, which maps a 1d input to some output - regression / classification through activation functions

	One common problem in all these neural networks is the Vanishing and Exploding Gradient. This problem is associated with the backpropagation algorithm. The weights of a neural network are updated through this backpropagation algorithm by finding the gradients:


	CNN - 

	NNs designed to work with multi dim spatial data. each cnn layer -> kernels or filters responsible for extracting features through the process of convolutions 


	RNN - 

	gated nns Series based or sequential data


4. Unsupervised MT

	depends on the type of data which is focussed upon during the training phase - monolingual corpora hence can be used where parallel data is scarce.

	- backtranslation
	utilize monolingual data of target language
		● Generate pseudo parallel data using MT system in opposite direction 	(target->source)


	- xlm
	masked cross lingual lang model

	- dual learning
	uses reinforcement learning
		.two agent game forward & backward translation step   and  dual learning agent to imporove on the basis of a feedback mech


5. constraints
6. Bert, gpt
	
	transformers consist of an encoder decoder arch with a multi attention head ffnn which can be fine tuned wrt to the task being performed


	each of the nlp model is tested on a bunch of standarized tasks with their own benchmark datasets and metrics for evaluation, glue -  SA, qna, PoS tagging etc


7. Word Embeddings

	used for converting the text input into a numeric data input which is understandable by the comp;

	- solution: Bag of Words - dict of char with keys, sentence rep through a vector of 0 and 1 having length = dict size
	- problem: sparse matrix, large space req, and computationally exp 

	word embeddings like word2vec or glove map these sparse large dim data into low dim vectors using dimensionality reduction tech like pca on the basis of their semantic relationships bw words


8. NLP

	computer system designed to perform tasks related to human lang wth of Machine learning.
	text summarization, MT, Sentiment, QnA

9. AI, ML, DL

	AI can be defined as the ability of a computer system to imitate human intelligence, behaviour or response.

	Eg. Self driving car -> AI but the algorithms making this possible are a part of ML

	ML can be considered as a domain of AI composed statistical / neural based algorithms required for automating learning and predicting a task on the basis of that learning with minimal human interaction.

	Eg. recommendation systems of amazon, voice assistents like alexs, go services, automating supply chains, translation services, text extraction, clustering	

	DL is a subset of ML which focussed solely upon the neural networks, designed to mimic the human brain hence are used for the most complicated of the tasks like nlp or cv and therefore have an eternal resouce requirements for achieving that computation power;


	Pros - 

	- ML -> decision boundaries - limited types and doesnt work on non linear data, relationships cant be defined
	- feature engineering - when using dl this step absolves within the modelling and training phase.

	cons - 

	- high computation, time, resource needs
	- scarce data, cant use
	- opaque - result is unknown untill tested hence not reliable


10. uses of NLP
	
	- autocorrect / autocomplete plugins
	- searching
	- ai assistents
	- MT
	- captioning / summarization
	- classification


11. Design a recommender system

	ML SD can be solved in a stepwise manner->

	1. project setup - knowing goals, performance/res constraints, client exp
	2. data pipeline - curating the dataset, cleaning and preprocessing, representation
	3. model selection & training - modelling, training, validation to prevent overfitting / underfitting
	4. Testing and servicing - 


	Diff types ->

	1. basic -> filter the most stuff which is accessed by the most

	2. ML ->

		- content based filtering
			done on the basis of the type of content user accesses - characteristics
			eg. dark & horror, genre based

		- collaborative filtering
			type of content users who are related to me access
			eg. sitcoms others watching i'll get the recommendations, top content in india

	3. Feedback is imp for improving the quality of recommendations


		1. Profile Generator
		2. Feedback System
		3. User specific DB - 
		4. selecting similar items - items / user db and scoring on basis of choices
		5. filtering the top


12. GRU, LSTM


	batchnorm - normalizes the data batchwise mean is 0 and sd is 1

	dropout - dropping off features whose values are below a certain threshold

	pooling - reducing dimsionality of a feature map to control overfitting - max and avg - 2x2 f, 2 stride

	RNN - nns Series based or sequential data and generate out wrt each hidden state, exp vanishing gradients problem to over come this lstms and grus 

	GRU - gated cell structure with the same baseline as rnn, current state as well as prev hidden state data is transferred to the next hidden state. - reset, update gate

	lstms - gate difference in cell structure - forget and output gate


13. losses - cross entropy, MSE

	activations - tanh, relu, leakyrelu, softmax, sigmoid - non linear mappings or relationships bw in and out

	relu

	prevent vanishing gradient

	Some gradients can be fragile during training and can die. It can cause a weight update which will makes it never activate on any data point again. In other words, ReLu can result in dead neurons.

	In another words, For activations in the region (x<0) of ReLu, gradient will be 0 because of which the weights will not get adjusted during descent. That means, those neurons which go into that state will stop responding to variations in error/ input (simply because gradient is 0, nothing changes). This is called the dying ReLu problem.


	Optimizers - resp for backpropagation and weight updations to improve and increase the acc of ml algo during the training with the help of loss functions controlling everything.



14. Seq2Seq, Transformer
	Sequence-to-Sequence (Seq2Seq) problems is a special class of Sequence Modelling Problems in which both, the input and the output is a sequence consist of an encoder decoder architecture.

	encoder - compression phase, intermediate state - context vector or the sematic info in MT, decoder - expansion phase 

	. as the length of the sentence increases the performance slumps, since rnns arent designed to memorize longer state infos 
	. The sequential nature of RNNs makes it further difficult to take full advantage of modern fast computing devices such as TPUs and GPUs.

	is feed forward nn consisting of an encoder decoder arch with multi self attention heads, attention - mapping the relationships between each of the objects in the data

15. tensor

	 A tensor is a container which can house data in N dimensions. Tensors also include descriptions of the valid linear transformations between tensors. Examples of such transformations, or relations, include the cross product and the dot product


16. MT


	Languages have different ways of expressing meaning
	○ Lexico-Semantic Divergence
	○ Structural Divergence


17. reinforcement learning


	uses a game agent which learns on the basis of trial and error and feedback in the form of rewards from its own actions and results.

	Environment — Physical world in which the agent operates
	State — Current situation of the agent
	Reward — Feedback from the environment
	Policy — Method to map agent’s state to actions
	Value — Future reward that an agent would receive by taking an action in a particular state


	An RL problem can be best explained through games. Let’s take the game of PacMan where the goal of the agent(PacMan) is to eat the food in the grid while avoiding the ghosts on its way. In this case, the grid world is the interactive environment for the agent where it acts. Agent receives a reward for eating food and punishment if it gets killed by the ghost (loses the game). The states are the location of the agent in the grid world and the total cumulative reward is the agent winning the game.
