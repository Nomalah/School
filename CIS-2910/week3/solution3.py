import numpy as np
from PIL import Image
import copy


# constraints: 
#     1 <= groups <= 256
#     0 <= all integers in img <= 255
def quantize(groups, val):
    groupSize = 256 // groups
    groupNum = val // groupSize
    low = groupNum * groupSize
    quantized = low + groupSize // 2
    return quantized


# Inputs:
#     img: m by n by 3 array of integers representing the color values of a photo
#     rGroups: integer representing the number of groups of red color values
#     gGroups: integer representing the number of groups of green color values
#     bGroups: integer representing the number of groups of blue color values
# constraints: 
#     1 <= rGroups, gGroups, bGroups <= 256
#     0 <= all integers in img <= 255
# Output: returns an m by n by 3 (same dimensions as input img array), 
#         with its color values quantized according to the specified group parameters


def colorQuantize( img, rGroups, gGroups, bGroups ):
    for m in range(len(img)):
        for n in range(len(img[m])):
            img[m][n][0] = quantize(rGroups, img[m][n][0])
            img[m][n][1] = quantize(gGroups, img[m][n][1])
            img[m][n][2] = quantize(bGroups, img[m][n][2])

    return img

# Testing and starter code provided in main(): 
def main():
    testFiles = [
        # "3by3.png",
        # "dog.png",
        "cat.png"
    ]
    testArgs = [
        # [[1, 1, 1], [3, 4, 5], [11, 13, 15], [256, 256, 256]], # 3by3 test args
        # [[2, 2, 2], [2, 8, 8], [2, 16, 2], [4, 4, 4], [16, 16, 16],], # dog test args
        [[1, 1, 1], [7, 1, 9], [7, 11, 9], [256, 256, 256]]  # cat test args
    ]
    testDir = "tests/" # update this path with the path to your tests directory!

    # Change the path in .open() to the file that you want to read in
    img = Image.open('tests/3by3.png').convert('RGB')
    arr = np.array(img)
    outArr = colorQuantize( arr, 256, 256, 256 )

    # Change testing to be True to test against files
    # SET testDir var above
    testing = True
    if testing:
        for idx, testFile in enumerate(testFiles): #iterates over test files
            testImg = Image.open(testDir + testFile).convert('RGB')
            testImgArr = np.array(testImg)
            for testSet in testArgs[idx]: #iterates over args for given file
                print(f"{testDir}{testFile[:-4]}_{testSet[0]}_{testSet[1]}_{testSet[2]}.png: ", end='')
                outArr = colorQuantize( copy.deepcopy(testImgArr), testSet[0], testSet[1], testSet[2] )
                testImg = Image.open(f"{testDir}{testFile[:-4]}_{testSet[0]}_{testSet[1]}_{testSet[2]}.png").convert('RGB')
                testArr = np.array(testImg)
                for row in range(len(testArr)):
                    for col in range(len(testArr[0])):
                        if outArr[row][col][0] != testArr[row][col][0]:
                            print("red color mismatch at row: " + str(row) + " col: " + str(col))
                            print(outArr[row][col][0], testArr[row][col][0])
                            return
                        if outArr[row][col][1] != testArr[row][col][1]:
                            print("green color mismatch at row: " + str(row) + " col: " + str(col))
                            return
                        if outArr[row][col][2] != testArr[row][col][2]:
                            print("blue color mismatch at row: " + str(row) + " col: " + str(col))
                            return
                print("Passed")

    # Set saveFile to save your image,
    # e.g. saveFile = "myIMG.png" would save the image as the file "myIMG.png" in the directory where this code runs
    saveFile = ""
    if saveFile != "":
        outIMG = Image.fromarray(outArr)
        outIMG.save(saveFile)
    return 0

if __name__ == '__main__':
    main()

##########################################
# DO NOT LEAVE ANY CODE OUTSIDE ROUTINES #
# IT CAN CAUSE THE AUTOGRADER TO CRASH   #
##########################################


