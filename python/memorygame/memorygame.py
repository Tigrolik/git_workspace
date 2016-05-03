# implementation of card game - Memory
import simplegui
from random import shuffle

width     = 800
height    = 100
list_len  = 16 # number of cards
font_size = 60
card_w    = width / list_len # width for card

# helper function to initialize globals
def new_game():
    global text_w, num_list, state, card_num, exposed, idx1, idx2, turns
    # remember text width for nice displaying
    text_w   = frame.get_canvas_textwidth('0', font_size)
    # arranged list of pairs of numbers
    num_list = range(list_len // 2) * 2
    # state, indices of two current cards and number of turns
    state    = idx1 = idx2 = turns = 0
    # list of indices of exposed cards
    exposed  = [False] * list_len
    shuffle(num_list) # shuffled list

# define event handlers
def mouseclick(pos):
    global state, card_num, exposed, idx1, idx2, turns
    # use cursor coordinates to get card's index in the list
    card_pos = pos[0] // card_w
    # process only non-exposed cards
    if not exposed[card_pos]:
        if state == 0:
            # remember the first card of the pair
            idx1  = card_pos
            state = 1
            # set the card as exposed
            exposed[idx1] = True
        elif state == 1:
            # remember the second card of the pair
            idx2  = card_pos
            state = 2
            exposed[idx2] = True
        else:
            # check if the cards match
            if num_list[idx1] != num_list[idx2]:
                exposed[idx1] = exposed[idx2] = False
            idx1    = card_pos
            state   = 1
            turns  += 1 # number of turns
            exposed[idx1] = True

# cards are logically 50x100 pixels in size
def draw(canvas):
    global num_list, exposed
    for i in range(len(num_list)):
        # x is used to calculate x position for text
        x = card_w * (i + 0.5)
        if exposed[i]:
            canvas.draw_text(str(num_list[i]), [x - text_w * 0.5,
                                                height * 0.5 + font_size * 0.25], font_size, 'White')
        else:
            canvas.draw_line((x, 0), (x, height), card_w, 'Green')
    label.set_text('Turns = ' + str(turns)) # change label


# create frame and add a button and labels
frame = simplegui.create_frame('Memory', width, height)
label = frame.add_label('Turns = 0')
frame.add_button('Reset', new_game, 100)

# register event handlers
frame.set_mouseclick_handler(mouseclick)
frame.set_draw_handler(draw)

# get things rolling
new_game()
frame.start()
