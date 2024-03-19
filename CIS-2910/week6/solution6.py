
# takes in nAggressive, nPassive >= 0
# returns the number of possible arrangements of dogs
# Examples:
# |  Input  |  Output  |
# |---------|----------|
# |   0,0   |     1    |
# |---------|----------|
# |   1,1   |     2    |
# |---------|----------|
# |   0,2   |     0    |
# |---------|----------|
# |   2,2   |    12    |
# |---------|----------|

results = {}

def check_results(previous_was_aggressive: bool, nPassive, nAggressive, num_of_ps, num_of_as):
    if (previous_was_aggressive, nPassive, nAggressive, num_of_ps, num_of_as) in results:
        return results[(previous_was_aggressive, nPassive, nAggressive, num_of_ps, num_of_as)]
    else

def dogArrangementsRunner(previous_was_aggressive: bool, nPassive, nAggressive, num_of_ps, num_of_as):
    if nPassive == 0 and nAggressive == 1 and not previous_was_aggressive:
        return max(num_of_ps * (num_of_as + 1), 1)
    elif nPassive == 1 and nAggressive == 0:
        return max((num_of_ps + 1) * num_of_as, 1)

    if previous_was_aggressive:
        if nPassive == 0:
            return 0
        else:
            return dogArrangementsRunner(False, nPassive - 1, nAggressive, num_of_ps + 1, num_of_as)
    else:
        if nPassive == 0:
            return dogArrangementsRunner(True, nPassive, nAggressive - 1, num_of_ps, num_of_as + 1)
        elif nAggressive == 0:
            return dogArrangementsRunner(False, nPassive - 1, nAggressive, num_of_p + 1, num_of_as)
        else:
            return dogArrangementsRunner(False, nPassive - 1, nAggressive, num_of_ps + 1, num_of_as) + dogArrangementsRunner(True, nPassive, nAggressive - 1, num_of_ps, num_of_as + 1)


def dogArrangements( nPassive, nAggressive ):
    arr = [False] * (nPassive * nAggressive)
    
    if nPassive == 0 and nAggressive == 0:
        return 1
    return dogArrangementsRunner(False, nPassive, nAggressive, 0, 0)

# Testing code provided in main():
def main():
    testArgs = [[0,0,1],[1,1,2],[0,2,0],[2,2,12]]
    for arg in testArgs:
        passive, aggressive, answer = arg
        result = dogArrangements(passive,aggressive)
        if result != answer:
            print(f"Failed dogArrangements test with args nPassive={passive} nAggressive={aggressive}.\nExpected: {answer}, Got: {result}")
        else:
            print(f"Passed dogArrangements test with args nPassive={passive} nAggressive={aggressive}.")
    return 0

if __name__ == '__main__':
    main()
