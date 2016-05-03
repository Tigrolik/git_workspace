"""
Clone of 2048 game.
"""

import random

# import poc_2048_gui

# Directions, DO NOT MODIFY
UP = 1
DOWN = 2
LEFT = 3
RIGHT = 4

# Offsets for computing tile indices in each direction.
# DO NOT MODIFY this dictionary.
OFFSETS = {UP: (1, 0),
           DOWN: (-1, 0),
           LEFT: (0, 1),
           RIGHT: (0, -1)}


def merge(line):
    """
    Helper function that merges a single row or column in 2048
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


class TwentyFortyEight:
    """
    Class to run the game logic.
    """

    def __init__(self, grid_height, grid_width):
        # replace with your code
        pass

    def reset(self):
        """
        Reset the game so the grid is empty except for two
        initial tiles.
        """
        self.grid = [[0] * self.height for dummy_col in range(self.width)]
        pass

    def __str__(self):
        """
        Return a string representation of the grid for debugging.
        """
        # replace with your code
        return ""

    def get_grid_height(self):
        """
        Get the height of the board.
        """
        # replace with your code
        return 0

    def get_grid_width(self):
        """
        Get the width of the board.
        """
        # replace with your code
        return 0

    def move(self, direction):
        """
        Move all tiles in the given direction and add
        a new tile if any tiles moved.
        """
        # replace with your code
        pass

    def new_tile(self):
        """
        Create a new tile in a randomly selected empty
        square.  The tile should be 2 90% of the time and
        4 10% of the time.
        """
        # store indices of empty cells in a list of lists
        idx_list = []
        for row in range(self.width):
            for col in range(self.height):
                if self.grid[row][col] == 0:
                    idx_list.append([row, col])
        if len(idx_list) > 0:
            # randomly choose among empty cells
            idx_rc = random.choice(idx_list)
            self.grid[idx_rc[0]][idx_rc[1]] = random.choice([2] * 9 + [4])

    def set_tile(self, row, col, value):
        """
        Set the tile at position row, col to have the given value.
        """
        # replace with your code
        pass

    def get_tile(self, row, col):
        """
        Return the value of the tile at position row, col.
        """
        # replace with your code
        return 0


# poc_2048_gui.run_gui(TwentyFortyEight(4, 4))
grid = [[0] * 4 for y in range(4)]
grid[2][3] = 7
idx_list = []
for row in range(4):
    for col in range(4):
        if grid[row][col] == 0:
            idx_list.append([row, col])
print idx_list
print len(idx_list)
print random.choice(idx_list)


# line = [2, 0, 2, 4]
# print merge(line)
# line = [8, 16, 16, 8]
# print merge(line)
