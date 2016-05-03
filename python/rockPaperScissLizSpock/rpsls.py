# Rock-paper-scissors-lizard-Spock simulation program

# import function for generating random number from module random
from random import randrange

# Functions to assist the simulation code

def name_to_number(name):
    '''
        function name_to_number(name) takes a string as a parameter (name) and, depending on its content, returns an integer:
        'rock'     is assigned to 0
        'Spock'    is assigned to 1
        'paper'    is assigned to 2
        'lizard'   is assigned to 3
        'scissors' is assigned to 4
    '''
    # using if-elif-else structure to get the output
    if name == 'rock':
        return 0
    elif name == 'Spock':
        return 1
    elif name == 'paper':
        return 2
    elif name == 'lizard':
        return 3
    elif name == 'scissors':
        return 4
    else:
        # if the input is not one of 'rock', 'Spock', 'paper', 'lizard' or 'scissors' then print out the corresponding message and return value None
        print 'The input', name, 'is not appropriate'
        return None 

def number_to_name(number):
    '''
        function number_to_name(number) takes an integer value as a parameter (number) and, depending on its value, returns a string:
        0 is assigned to 'rock'
        1 is assigned to 'Spock'
        2 is assigned to 'paper'
        3 is assigned to 'lizard'
        4 is assigned to 'scissors'
    '''
    # using if-elif-else structure to get the output
    if number == 0:
        return 'rock'
    elif number == 1:
        return 'Spock'
    elif number == 2:
        return 'paper'
    elif number == 3:
        return 'lizard'
    elif number == 4:
        return 'scissors'
    else:
        # if the input is not an integer from 0 to 4 (inclusive) then print out the corresponding message and return value None
        print 'The number', number, 'should be an integer in range 0-4'
        return None

def rpsls(player_choice): 
    '''
    Main function: rpsls(player_choice) takes a string as a parameter (player_choice). Function then generates a random number between 0 and 4 (inclusive) for a computer and, depending on the result, displays the message about the winner or if a tie has hapeened
    '''

    # separate game rounds with a blank line
    print ''

    # display player's choice
    print 'Player chooses', player_choice

    # convert player's choice to an integer and store it in variable player_number
    player_number = name_to_number(player_choice)
    # if wrong input has been fed to the function then player_number has a null value (None) and our main function returns None too. The code after the line with the return statement will not implement (and that's what we want, since the input was not appropriate)
    if player_number is None:
        return None

    # generate a computer guess randomly in the range from 0 to 4, using random.randrange(0, 5) function. We feed number five as the upper boundary, because this function generates a number in the range [0, 5), thus excluding the second value (in this case, 5)
    comp_number = randrange(0, 5)

    # convert an integer number stored in variable comp_number to a string and store it in variable comp_choice using the function number_to_name() to later display the computer's choice
    comp_choice = number_to_name(comp_number)
    # if wrong input has been fed to the function then comp_choice has a null value (None) and our main function returns None too. The code after the line with the return statement will not implement (and that's what we want, since the input was not appropriate)
    if comp_choice is None:
        return None

    # display computer's choice
    print 'Computer chooses', comp_choice

    # here we have the main mathematical solution for deciding who won the game:
    # the elements of the game were specifically assigned to the numbers in the order which is presented in this code (0 - rock, 1 - Spock, 2 - paper, 3 - lizard, 4 - scissors). The idea is so, that the number will always lose to the next two consecutive numbers (e.g., 2 (paper) loses to 3 (lizard) and 4 (scissors)) and always wins over two preceding numbers (2 (paper) wins over 1 (Spock) and 0 (rock)). Since some numbers are followed by a smaller number (like 3 is followed by 4 and 0 (0 < 3)) or preceded by bigger number (like 1 is preceded by 0 and 4 (4 > 1)) then we apply the modulus operator to the difference of the two choices (player's and computer's). Then, if the difference is greater than 2 (two) we say that the second player is the winner (in our code that's the player), otherwise (difference less than 2), we say that the first player is the winner (computer). However, we still have to check for a tie (that's when the difference is zero). Therefore, we implement if-elif-else block for checking these 3 conditions

    # get the difference of comp_number and player_number modulo five and store it in variable diff_number
    diff_number = (comp_number - player_number) % 5

    # use if/elif/else to determine the winner and display the corresponding message
    if diff_number > 2:
        print 'Player wins!'
    elif diff_number > 0:
        print 'Computer wins!'
    else: # diff_number == 0
        print 'Player and computer tie!'

    # just make sure that function rpsls(player_choice) returns something
    return 1

# running the script to test the code
rpsls('rock')
rpsls('Spock')
rpsls('paper')
rpsls('lizard')
rpsls('scissors')
