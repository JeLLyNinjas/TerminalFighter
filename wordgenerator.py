import pygame
import random
import sys
import math
from copy import deepcopy

CONST_FILENAME = "american-english.txt"  

'''
Opens the file CONST_FILENAME and reads entire file to word_array list. Shuffles the array and then sorts according to length
'''
class WordGenerator():
    index_locations = []
    index_prime_locations = []
    word_array = []
    number_of_lengths = 0
    smallest_length = []

    def __init__(self):
        with open(CONST_FILENAME) as infile:
            for line in infile:
                self.word_array.append(line.rstrip('\n'))
        random.shuffle(self.word_array) 
        self.word_array.sort(key=len)
        self.split_list(self.word_array)

    '''
    Will populate the list index_locations on where each new length starts
    For example, index_locations[3] will give you the location of the first word with length 3
    index_locations[4] will give you location of first word with length 4, etc.
    index_prime_locations will be incremented and used to keep track of which words have been given out.
    '''
    def split_list(self, list):
        self.number_of_lengths = len(list[len(list)-1]) - len(list[0]) 
        self.smallest_length = len(list[0])
        #For lengths that are smaller than the smallest word, we point them to index 0 in the array
        for x in range (0, self.smallest_length):
            self.index_locations.append(0)

        for x in range (self.smallest_length, self.number_of_lengths):
            self.index_locations.append(self.locate_first_length(x))


        self.index_prime_locations = deepcopy(self.index_locations)

    '''
    log(n) binary search to find the first length
    '''
    def locate_first_length(self, requested_length):
        found = False
        index = math.ceil(len(self.word_array)/2)
        delta = math.ceil(len(self.word_array)/4)
        while True:
            if self.check_if_first(index, requested_length):
                break
            if len(self.word_array[index]) >= requested_length:
                index -= delta
            else:
                index += delta 
            if index < 0:
                index = 0
            delta = math.ceil(delta/2)
        return index
                
    def check_if_first(self, index, requested_length):
        if len(self.word_array[index]) != requested_length:
            return False
        if index == 0:
            return True
        return len(self.word_array[index]) != len(self.word_array[index-1])

    '''
    If you want words with length 4-6 (inclusive), request_word(4,3)
    If you want words with length of 2, request_word(2,1)
    '''
    def request_word(self, index, number_of_lengths):
        if number_of_lengths != 1:
            index = random.randrange(index, index + number_of_lengths)
        
        if (index + number_of_lengths) > self.number_of_lengths: 
            print("WordGenerator: ERROR: Range you requested was too large, giving you the largest valid range instead.")
            number_of_lengths = self.number_of_lengths - index
            

        index_of_word = self.index_prime_locations[index]
        self.index_prime_locations[index] += 1
        if self.index_prime_locations[index] >= self.index_locations[index+1]:
            print("You have exhuasted the pool of length " + repr(index) + " words, looping back to beginning")
            self.index_prime_locations[index] = self.index_locations[index] 
        return self.word_array[index_of_word]

    def print_list(self):
        for i in range(0, len(self.word_array)):
            print("Index: " + repr(i) + " Word: " + self.word_array[i])


if __name__ == '__main__':
    tester = WordGenerator()
    print("random word: " + tester.request_word(3,20))


    




