# Mini-project #6 - Blackjack

import simplegui
import random

WIDTH = 600
HEIGHT = 600
# load card sprite - 936x384 - source: jfitz.com
CARD_SIZE = (72, 96)
CARD_CENTER = (36, 48)

card_images = simplegui.load_image("http://storage.googleapis.com/codeskulptor-assets/cards_jfitz.png")

CARD_BACK_SIZE = (72, 96)
CARD_BACK_CENTER = (36, 48)
card_back = simplegui.load_image("http://storage.googleapis.com/codeskulptor-assets/card_jfitz_back.png")

# initialize some useful global variables
deck = []
dealer_hand = []
player_hand = []
in_play = False
outcome = ''
score = 0

# define globals for cards
SUITS = ('C', 'S', 'H', 'D')
RANKS = ('A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K')
VALUES = {'A': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, 'T': 10, 'J': 10, 'Q': 10, 'K': 10}


# define card class
class Card:
    def __init__(self, suit, rank):
        if (suit in SUITS) and (rank in RANKS):
            self.suit = suit
            self.rank = rank
        else:
            self.suit = None
            self.rank = None
            print "Invalid card: ", suit, rank

    def __str__(self):
        return self.suit + self.rank

    def get_suit(self):
        return self.suit

    def get_rank(self):
        return self.rank

    def draw(self, canvas, pos):
        card_loc = (CARD_CENTER[0] + CARD_SIZE[0] * RANKS.index(self.rank),
                    CARD_CENTER[1] + CARD_SIZE[1] * SUITS.index(self.suit))
        canvas.draw_image(card_images, card_loc, CARD_SIZE, [pos[0] + CARD_CENTER[0], pos[1] + CARD_CENTER[1]], CARD_SIZE)


# define hand class
class Hand:
    def __init__(self):
        self.cards = []

    def __str__(self):
        s = 'Hand contains'
        for i in range(len(self.cards)):
            c = self.cards[i]
            s += ' ' + c.get_suit() + c.get_rank()
        return s + ' ' + str(self.get_value())

    def add_card(self, card):
        self.cards.append(card)

    def get_value(self):
        v = 0
        c = self.cards
        n = range(len(c))
        for i in n:
            r = c[i].get_rank()
            v += VALUES[r]
        for i in n:
            r = c[i].get_rank()
            if (r == 'A') and (v + 10 < 22):
                v += 10
        return v

    def draw(self, canvas, pos):
        for i in range(len(self.cards)):
            c = self.cards[i]
            c.draw(canvas, [pos[0] + i * CARD_SIZE[0], pos[1]])


# define deck class
class Deck:
    def __init__(self):
        self.cards = [Card(x, y) for x in SUITS for y in RANKS]

    def shuffle(self):
        random.shuffle(self.cards)

    def deal_card(self):
        return self.cards.pop()

    def __str__(self):
        s = 'Deck contains'
        for i in range(len(self.cards)):
            c = self.cards[i]
            s += ' ' + c.get_suit() + c.get_rank()
        return s


# define event handlers for buttons
def deal():
    global outcome, score, in_play, deck, dealer_hand, player_hand

    outcome = ''

    if in_play:
        score -= 1
        outcome = 'You have lost'
        in_play = False
    else:
        deck = Deck()
        deck.shuffle()

        player_hand = Hand()
        dealer_hand = Hand()

        for i in range(2):
            dealer_hand.add_card(deck.deal_card())
            player_hand.add_card(deck.deal_card())

        in_play = True


def hit():
    global outcome, in_play, deck, player_hand, score

    if in_play:
        player_hand.add_card(deck.deal_card())
        if player_hand.get_value() > 21:
            score -= 1
            outcome = 'You have busted'
            in_play = False


def stand():
    global outcome, in_play, deck, dealer_hand, player_hand, score

    if in_play:

        while dealer_hand.get_value() < 17:
            dealer_hand.add_card(deck.deal_card())

        dv = dealer_hand.get_value()
        if (dv < 22) and (player_hand.get_value() <= dv):
            score -= 1
            outcome = 'You have lost'
        else:
            score += 1
            outcome = 'You have won!'

        in_play = False


# draw handler
def draw(canvas):
    global dealer_hand, player_hand, in_play, outcome, score

    font_size = 24
    canvas.draw_text('BLACKJACK', [WIDTH * 0.1, HEIGHT * 0.1], font_size, 'Gold')
    canvas.draw_text('Dealer', [WIDTH * 0.1, HEIGHT * 0.2], font_size, 'Gold')
    canvas.draw_text('Player', [WIDTH * 0.1, HEIGHT * 0.7], font_size, 'Gold')
    canvas.draw_text(outcome, [WIDTH * 0.5, HEIGHT * 0.2], font_size, 'Gold')
    canvas.draw_text('Score ' + str(score), [WIDTH * 0.5, HEIGHT * 0.1], font_size, 'Gold')

    player_hand.draw(canvas, [WIDTH * 0.1, HEIGHT * 0.75])
    dealer_hand.draw(canvas, [WIDTH * 0.1, HEIGHT * 0.25])

    if in_play:
        canvas.draw_text('Hit or stand?', [WIDTH * 0.5, HEIGHT * 0.7], font_size, 'Gold')
        canvas.draw_image(card_back, CARD_BACK_CENTER, CARD_BACK_SIZE,
                          [WIDTH * 0.1 + CARD_BACK_CENTER[0], HEIGHT * 0.25 + CARD_BACK_CENTER[1]],
                          CARD_BACK_SIZE)
    else:
        canvas.draw_text('New deal?', [WIDTH * 0.5, HEIGHT * 0.7], font_size, 'Gold')


# initialization frame
frame = simplegui.create_frame("Blackjack", 600, 600)
frame.set_canvas_background("Green")

# create buttons and canvas callback
frame.add_button("Deal", deal, 200)
frame.add_button("Hit",  hit, 200)
frame.add_button("Stand", stand, 200)
frame.set_draw_handler(draw)


# get things rolling
deal()
frame.start()
