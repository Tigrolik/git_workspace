# Implementation of classic arcade game Pong

import simplegui
from random import randrange

# initialize globals - pos and vel encode vertical info for paddles
WIDTH           = 600
HEIGHT          = 400
BALL_RADIUS     = 20
PAD_WIDTH       = 8
PAD_HEIGHT      = 80
HALF_PAD_WIDTH  = PAD_WIDTH / 2
HALF_PAD_HEIGHT = PAD_HEIGHT / 2
LEFT            = False
RIGHT           = True

# initialize ball_pos and ball_vel for new bal in middle of table
# if direction is RIGHT, the ball's velocity is upper right, else upper left
def spawn_ball(direction):
    global ball_pos, ball_vel # these are vectors stored as lists
    ball_pos    = [WIDTH / 2, HEIGHT / 2]
    x_vel_low   = 120
    x_vel_high  = 240
    y_vel_low   = 60
    y_vel_high  = 180
    rate_to_sec = 0.01
    if direction == RIGHT:
        ball_vel = [randrange(x_vel_low, x_vel_high) * rate_to_sec,
                -randrange(y_vel_low, y_vel_high) * rate_to_sec]
    else: # LEFT
        ball_vel = [-randrange(x_vel_low, x_vel_high) * rate_to_sec,
                -randrange(y_vel_low, y_vel_high) * rate_to_sec]

        # define event handlers
def new_game():
    global paddle1_pos, paddle2_pos, paddle1_vel, paddle2_vel  # these are numbers
    global score1, score2  # these are ints

    score1 		= score2	  = 0
    paddle1_pos = paddle2_pos = HEIGHT / 2
    paddle1_vel = 0
    paddle2_vel = 0
    spawn_ball(RIGHT)

def draw(canvas):
    global score1, score2, paddle1_pos, paddle2_pos
    global paddle1_vel, paddle2_vel, ball_pos, ball_vel


    # draw mid line and gutters
    canvas.draw_line([WIDTH / 2, 0],[WIDTH / 2, HEIGHT], 1, 'White')
    canvas.draw_line([PAD_WIDTH, 0],[PAD_WIDTH, HEIGHT], 1, 'White')
    canvas.draw_line([WIDTH - PAD_WIDTH, 0],[WIDTH - PAD_WIDTH, HEIGHT], 1, 'White')

    # update ball
    if ball_pos[1] + ball_vel[1] < BALL_RADIUS:
        ball_vel[1] = -ball_vel[1]
    elif ball_pos[1] + ball_vel[1] > HEIGHT - BALL_RADIUS:
        ball_vel[1] = -ball_vel[1]

    ball_pos[0] += ball_vel[0]
    ball_pos[1] += ball_vel[1]

    # draw ball
    canvas.draw_circle(ball_pos, BALL_RADIUS, 2, 'Yellow', 'Yellow')

    # update paddle's vertical position, keep paddle on the screen
    if (paddle1_pos + paddle1_vel < HALF_PAD_HEIGHT):
        paddle1_pos = HALF_PAD_HEIGHT
        paddle1_vel = 0
    elif (paddle1_pos + paddle1_vel > HEIGHT - HALF_PAD_HEIGHT):
        paddle1_pos = HEIGHT - HALF_PAD_HEIGHT
        paddle1_vel = 0
    else:
        paddle1_pos += paddle1_vel

    if (paddle2_pos + paddle2_vel < HALF_PAD_HEIGHT):
        paddle2_pos = HALF_PAD_HEIGHT
        paddle2_vel = 0
    if (paddle2_pos + paddle2_vel > HEIGHT - HALF_PAD_HEIGHT):
        paddle2_pos = HEIGHT - HALF_PAD_HEIGHT
        paddle2_vel = 0
    else:
        paddle2_pos += paddle2_vel

    # draw paddles
    canvas.draw_line((HALF_PAD_WIDTH, paddle1_pos - HALF_PAD_HEIGHT),
            (HALF_PAD_WIDTH, paddle1_pos + HALF_PAD_HEIGHT), PAD_WIDTH, 'LimeGreen')
    canvas.draw_line((WIDTH - HALF_PAD_WIDTH, paddle2_pos - HALF_PAD_HEIGHT),
            (WIDTH - HALF_PAD_WIDTH, paddle2_pos + HALF_PAD_HEIGHT), PAD_WIDTH, 'LimeGreen')

    # determine whether paddle and ball collide
    vel_mdf = 1.5
    if ball_pos[0] <= BALL_RADIUS + PAD_WIDTH:
        if (paddle1_pos - HALF_PAD_HEIGHT < ball_pos[1] < paddle1_pos + HALF_PAD_HEIGHT):
            ball_vel[0] *= -vel_mdf
            ball_vel[1] *= vel_mdf
        else:
            score2 += 1
            spawn_ball(RIGHT)
    elif ball_pos[0] >= WIDTH - BALL_RADIUS - PAD_WIDTH:
        if (paddle2_pos - HALF_PAD_HEIGHT < ball_pos[1] < paddle2_pos + HALF_PAD_HEIGHT):
            ball_vel[0] *= -vel_mdf
            ball_vel[1] *= vel_mdf
        else:
            score1 += 1
            spawn_ball(LEFT)
    # draw scores
    font_size = 36
    s = str(score1)
    canvas.draw_text(s, [WIDTH * 0.25, font_size], font_size, 'Gold')
    s = str(score2)
    canvas.draw_text(s, [WIDTH * 0.75, font_size], font_size, 'Gold')

def keydown(key):
    global paddle1_vel, paddle2_vel

    if key == simplegui.KEY_MAP['w']:
        paddle1_vel -= 1
    elif key == simplegui.KEY_MAP['s']:
        paddle1_vel += 1
    elif key == simplegui.KEY_MAP['up']:
        paddle2_vel -= 1
    elif key == simplegui.KEY_MAP['down']:
        paddle2_vel += 1

def keyup(key):
    global paddle1_vel, paddle2_vel


# create frame
frame = simplegui.create_frame('Pong', WIDTH, HEIGHT)
frame.set_draw_handler(draw)
frame.set_keydown_handler(keydown)
frame.set_keyup_handler(keyup)
reset_button = frame.add_button('Restart', new_game, 100)

# start frame
new_game()
frame.start()
