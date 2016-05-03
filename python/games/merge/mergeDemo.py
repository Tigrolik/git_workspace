
"""
Merge function for 2048 game.
"""


def merge(line):
    """
    Function that merges a single row or column in 2048.
    """

    # remember the length of a row (column): number of elements
    num_el = len(line)

    # initialize new list as zeros
    new_list = [0] * num_el

    # control the index value of the new list
    idx = 0

    # cycle through elements of the original line
    for elem in range(num_el):
        a = line[elem]
        # ignore zero values
        if a != 0:
            # if the value has already been added then double it and move the
            # index of the new list by one, otherwise add the new value
            if a == new_list[idx]:
                new_list[idx] *= 2
                idx += 1
            else:
                if new_list[idx] != 0:
                    idx += 1
                new_list[idx] = a

    return new_list


line = [2, 0, 2, 4]
print merge(line)
line = [8, 16, 16, 8]
print merge(line)
