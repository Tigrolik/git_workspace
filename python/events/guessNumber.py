# "Guess the number" mini-project
# import necessary libraries
import simplegui, random, math

# initialize global variables:
# secret_number: a number to be guessed
secret_number = 0
# max number: upper limit for guess interval
max_number = 100;
# maximum number of guesses to achieve the goal
number_of_guesses = 7


# helper function to start and restart the game
def new_game():
    '''
        function new_game() generates a new secret number and
        calculates the maximum number of guesses
    '''
    # global variables to be modified
    global secret_number
    global number_of_guesses

    # use string concatenation to display the interval nicely
    print 'New game. Range is [0,', str(max_number) + ')'

    # obtain the secret_number value randomly
    secret_number = random.randrange(0, max_number)

    # evaluate the maximum number of steps to guess correctly
    # the formula is taken for the binary search algorithm
    number_of_guesses = int(math.floor(math.log(max_number, 2)) + 1)
    print 'Number of remaining guesses is', number_of_guesses, '\n'


# define event handlers for control panel
def range100():
    '''
        this function-handler reacts on pressing the
        corresponding button and sets the upper limit
        of the guess interval to 100 and starts the new game
    '''
    global max_number
    max_number = 100;
    new_game();

def range1000():
    '''
        this function-handler reacts on pressing the
        corresponding button and sets the upper limit
        of the guess interval to 1000 and starts the new game
    '''
    global max_number
    max_number = 1000;
    new_game();

def input_guess(guess):
    '''
        this function-handler reacts on the input text in the
        corresponding text field (followed by pressing the Enter
        button), reduces the number of allowed attempts, compares
        the entered (guessed) value with the secret_number and
        prints messages accordingly
    '''

    # the number of guesses will decrease
    global number_of_guesses

    # convert the entered string number into an integer
    guess_number = int(guess)
    print 'Guess was', guess_number

    # reduce the number of allowed attempts
    number_of_guesses -= 1
    print 'Number of remaining guesses is', number_of_guesses

    # compare the guessed value and the secret number
    # check as well if guesses are yet allowed
    if (secret_number > guess_number):
        if (number_of_guesses == 0):
            print 'You ran out of guesses. The number was', secret_number, '\n'
            new_game()
        else:
            print 'Higher!\n'
    elif (secret_number < guess_number):
        if (number_of_guesses == 0):
            print 'You ran out of guesses. The number was', secret_number, '\n'
            new_game()
        else:
            print 'Lower!\n'
    else:
        print 'Correct!\n'
        new_game()

    return guess_number

# create frame
frame = simplegui.create_frame('Guess the number', 200, 200, 0)

# register event handlers for control elements and start frame
frame.add_input('Input guess', input_guess, 50)
frame.add_button('Range is [0,100)', range100)
frame.add_button('Range is [0,1000)', range1000)

# call new_game
new_game()
