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

    def __init__(self):
        self.word_array = []
        with open(CONST_FILENAME) as infile:
            for line in infile:
                self.word_array.append(line.rstrip('\n'))
        self.word_array = (self.word_array)
        random.shuffle(self.word_array)
        self.word_array.sort(key=len)
        #self.split_list(self.word_array)
        print("First Length IS!!!:")
        print(self.locate_first_length(5))

    def print_list(self):
        for i in range(0, len(self.word_array)):
            print(self.word_array[i])
            print(i)

    def split_list(self, list):
        self.number_of_lengths = len(list[len(list)-1]) - len(list[0])
        self.smallest_length = len(list[0])
        self.index_locations = []
        for x in range (0, self.smallest_length):
            self.index_locations.append(0)

        for x in range (1, self.number_of_lengths):
            pass

    def check_if_first(self, index, requested_length):
        if len(self.word_array[index]) != requested_length:
            return False
        return len(self.word_array[index]) != len(self.word_array[index-1])

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
            delta = math.ceil(delta/2)

        return index

    def request_word(size):
        pass

if __name__ == '__main__':
    tester = WordGenerator()
    #tester.print_list()
