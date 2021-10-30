# Internship


## Situation

During my summer internship last year, i interned at citibank pune as a summer analyst. 

## Tasks

i was assigned a project which aimed at building a user informative tool for processing bank transactions data related queries.

now during my time at the internship, there was never a dearth of challenges. the mentors gave new feature reqs every week and adding those functionalities to the system was my task

my first challenge was to decide an interactive system which provide a good ux could handle 2 imp factors which include: 

Classify the intent of the query
Extract imp info from the query

## Actions

for this i decided to use a chatbot system, Through this chatbot system my intent classification and NER were both automated, also it added an intelligent dialogflow for conversations.

next i was asked to make this bot dyanamic such that, whenever the user adds some data, training should be automated in the backend and the user should be able to query in realtime, the bot fetches the response from the db and replies to the user.


so for this i designed a pipeline, it starts with the input of data, followed by making a table for this data in the db, and training the bot on this data.

i also added features like a sound input, speech2text api and the multilingual data input.


## Result

