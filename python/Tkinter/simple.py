#!/usr/bin/python
# -*- coding: utf-8 -*-
from Tkinter import Tk, BOTH
from ttk import Frame, Button, Style


class Example(Frame):
    def __init__(self, parent):
        Frame.__init__(self, parent)
        self.parent = parent
        self.initUI()

    def initUI(self):
        self.parent.title('Simple')
        self.style = Style()
        self.style.theme_use('default')
        self.pack(fill=BOTH, expand=1)
        # self.centerWindow()
        quitButton = Button(self, text='Quit', command=self.quit)
        quitButton.place(x=50, y=50)

'''
    def centerWindow(self):
        w = 290
        h = 150

        sw = self.parent.winfo_screenwidth()
        sh = self.parent.winfo_screenheight()

        x = (sw - w) >> 1
        y = (sh - h) >> 1

        self.parent.geometry('%dx%d+%d+%d' % (w, h, x, y))
'''


def main():
    root = Tk()
    root.geometry('250x150+300+300')
    Example(root)
    root.mainloop()

if __name__ == '__main__':
    main()
