# Stopwatch: The Game
import simplegui

# global variables
# define canvas size values and font size of the text for more
# convenient management of text positioning inside the canvas
canvas_w   = 300
canvas_h   = 200
font_size  = 30
# time step of the timer in milliseconds (100ms = 0.1s)
interval   = 100
# keep the track of total running time
run_time   = 0
# count for successful stops (full seconds) and total stops
win_count  = 0
tot_count  = 0

# define helper function format that converts time
# in tenths of seconds into formatted string A:BC.D
def format(t):
    '''
        function format(t) takes number of milliseconds and converts it
        into a string 'minutes:seconds:tenthsOfSeconds'
    '''
    # one tenth of a second is 100 milliseconds and from now on
    # the parameter t will represent tenths of a second
    t = t // 100;
    # get the full seconds (from 0 to 59) and convert to string
    secs = str(t // 10 % 60)
    # if seconds are within 0 and 9 then add a zero character
    if (len(secs) < 2):
        # str(n // 600) return the string of minutes and
        # str(t % 10) displays the single digit of milliseconds
        return str(t // 600) + ':0' + secs + '.' + str(t % 10)
    # the seconds must always be shown as two characters
else:
    return str(t // 600) + ':' + secs + '.' + str(t % 10)

# define event handlers for buttons; "Start", "Stop", "Reset"
def handle_start():
    '''
        handler for the start button: start the timer
    '''
    # built-in handler (found in Docs)
    if not timer.is_running():
        timer.start()

def handle_stop():
    '''
        handler for the stop button: stop the timer and update
        counters
    '''
    # refer to global variables to keep them changed
    global tot_count, win_count
    # update the count of total and successful clicks only if
    # the timer was stopped while running
    # using built-in handler to check if the timer is running
    if timer.is_running():
        # check if the number of seconds is full, i.e. tenths
        # of a second is equal to zero
        if (run_time % 1000 == 0):
            # update the successful clicks count
            win_count += 1
        # update the total clicks count
        tot_count += 1
        # stop the timer
        timer.stop()

def handle_reset():
    '''
        handler for the reset button: stop the timer, sets the
        flag that the timer is not started and set the counters
        to zero
    '''
    # refer to global variables to reinitialize them
    global run_time, tot_count, win_count
    # the timer is to be reset (stop)
    # run_time will start from the beginning as well as the counters
    # for total clicks and successful clicks
    run_time   = 0
    tot_count  = 0
    win_count  = 0
    # built-in handler
    if timer.is_running():
        # stop the timer
        timer.stop()

# define event handler for timer with 0.1 sec interval
def timer_handler():
    '''
        handler for keeping track of time changes
    '''
    global run_time
    # increment the running time of the timer by the interval step
    run_time += interval

# define draw handler
def draw(canvas):
    '''
        handler for drawing text inside the canvas
    '''
    # store text in a variable
    s = format(run_time)
    # try to calculate the position of text in order to put it in the center
    # of the canvas. Using built-in frame.get_canvas_textwidth(s, font_size)
    # to get the width of text and put it in the middle of x-axis
    # For y-axis trying to use the font size and seemed working if to put the
    # text in the middle of y-axis (canvas / 2) and add one fourth of the font
    # size (font_size / 4)
    # Then, just for fun, played with the colours a little
    canvas.draw_text(s, [(canvas_w - frame.get_canvas_textwidth(s, font_size)) * 0.5,
        (canvas_h  + font_size * 0.5) * 0.5], font_size, 'Gold')

    # string for displaying number of successful stops and total stops
    s = str(win_count) + '/' + str(tot_count)
    # put the text in the top-right corner. Here we subtract 10 in order to have the
    # text nicely put in the corner (in other words, avoiding "touching" the canvas
    # border). For y-axis using the font-size and it seems to work nicely
    canvas.draw_text(s, [canvas_w - frame.get_canvas_textwidth(s, font_size) - 10,
        font_size], font_size, 'LawnGreen')

# create frame and timer for the game
frame = simplegui.create_frame('Stopwatch Game', canvas_w, canvas_h)
timer = simplegui.create_timer(interval, timer_handler)
# just for fun and practice, using different HTML colour names
frame.set_canvas_background('Indigo')

# create three buttons with button width specified in a variable
# also empty labels are added to have a bit of space between the buttons
button_w 	 = 100
start_button = frame.add_button('Start', handle_start, button_w)
frame.add_label('')
stop_button  = frame.add_button('Stop', handle_stop, button_w)
frame.add_label('')
reset_button = frame.add_button('Reset', handle_reset, button_w)

# event handler for drawing
frame.set_draw_handler(draw)

# start the frame
frame.start()
