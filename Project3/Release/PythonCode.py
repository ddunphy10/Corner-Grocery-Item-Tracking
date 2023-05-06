import re
import string
from collections import Counter

#Takes a text file as a parameter and displays the items and associated quantity in that file.
def itemAndQuantity(textFile):                 #https://www.kite.com/python/answers/how-to-convert-each-line-in-a-text-file-into-a-list-in-python
    myList = []
    myDict = {}

    myFile = open(textFile, 'r')
    for line in myFile:
        strippedLine = line.strip()
        lineList = strippedLine.split()
        for word in lineList:
            myList.append(word)
     
    myDict = Counter(myList)          #https://www.hackerrank.com/challenges/collections-counter/problem
    for k,v in myDict.items():
        print(k, v)
    myFile.close()
    return 0

    #Displays a single item's quantity as long as it is in the list. The item to display is recieved from the user input. 
def singleItemQuantity(singleItem):
    myList = []
    myDict = {}

    myFile = open('TextFile.txt', 'r')
    for line in myFile:
        strippedLine = line.strip()
        lineList = strippedLine.split()
        for word in lineList:
            myList.append(word)
     
    myDict = Counter(myList)          #https://www.hackerrank.com/challenges/collections-counter/problem
    for k,v in myDict.items():
        if k == singleItem:
            
            myFile.close()
            return v

    print("That item is not on the list.")
    return 0

#Displays each item in the list and the associated quantity represented by *'s.
def textHistogram(file):
    myList = []
    myDict = {}

    myFile = open('TextFile.txt', 'r')
    for line in myFile:
        strippedLine = line.strip()
        lineList = strippedLine.split()
        for word in lineList:
            myList.append(word)
    
    myFile2 = open("frequency.dat", 'w')
    myDict = Counter(myList)          #https://www.hackerrank.com/challenges/collections-counter/problem
    for k,v in myDict.items():
        myFile2.write(k + " " + str(v) + " " + "\n")
    myFile.close()
    myFile2.close()
    return 0

