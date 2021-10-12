# Machine Translation

## Situation

In the 5th semester of my college time, i was involved in a bit of research based projects for one of the labs at DTU.

So the most challenging, rather i should say, the most enlightening of those projects was related to NLP, to be precise, Machine Translation.

I was doing this project with one of seniors, under mentorship of a CS Profesor at DTU, and the timeline for this project was actually very flexible, considering that covid had hit the world this year and most of the conferences were getting rescheduled.


## Task

As a part of this project, i was supposed to build a sans to eng mt system using different deep learning approaches and compare the performance of each.

Now while doing this i faced a series of challenges -

Data preparation
1. sans is a low res language, less data, and machine translation - be it nmt, rbmt or pbmt - all are res intensive tasks. So first challenge was accumulating all the available sa-en parallel data, monolingual data for each of the langs.


Data Cleaning and Preprocessing - 

1. For english, the preprocessing pipeline remains almost same for all NLP tasks but for sans i had to research and setup some indic lang based preprocessors.




Model selection
2. Selecting an appropriate DL MT technique for this task.


Quantification
3. Obtaining to a robust, high performance system to code, experiment and improve the quantified results.


## Actions


1. For each lang, we have a strict grammar syntax, sematics, structure, rules, dictionary of words, which have to be followed and obtained before performing any neural task on it. For the data collection, i used historical and cultural texts like ramayana, mahabharata and the vedas. around 6k parallel and 150k monolingual data.

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

	for the sans, similar pipeline was used but different tools and libs were involved, (moses and nltk) -> IndicNLP Library.


3. Explain ANN, CNN, RNN, LSTM, SEQ2SEQ, TRANSFORMERS, BLEU
4. Unsupervised NLP
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


