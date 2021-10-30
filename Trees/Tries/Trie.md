 Given an array of Strings, find which strings can be combined with other strings in the array so as to make the strings that are present in the array.


 1. map of all words
 2. iterate over words
 3. for each word
    3.1 find wordbreak such that each substring is inside the map


1. make a trie
2. for each word
3. search for a substring, when found start over from root, while increasing the index

