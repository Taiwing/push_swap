#!/usr/bin/env python3

from tkinter import *
import subprocess
import sys

PUSH_SWAP_PATH="push_swap/push_swap"
inst_set = ("sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr")

def get_input():
    numbers = []
    if len(sys.argv) > 1:
        i = 1
        while i < len(sys.argv):
           numbers += sys.argv[i].split() 
           i += 1
    return numbers

class Visu:
    def __init__(self, numbers):
        # game data
        self.instructions = self.launch_push_swap(numbers)
        self.stack_a = []
        for s in numbers:
            self.stack_a.append(int(s))
        self.stack_b = []
        # window data
        self.win = Tk()
        self.win_h = 800
        self.win_w = 1000
        x, y = self.get_start_pos()
        self.win.geometry(str(self.win_w) + "x" + str(self.win_h) + "+"\
            + str(x) + "+" + str(y))
        self.win.resizable(width=False, height=False)
        # widgets
        self.left_canvas = Canvas(self.win, bg="black")
        self.right_canvas = Canvas(self.win, bg="white")
        self.left_canvas.pack(side=LEFT, expand=True, fill=BOTH)
        self.right_canvas.pack(side=RIGHT, expand=True, fill=BOTH)
        # visu data
        self.quit = False
        self.step = 0
        self.stack_a_obj, self.stack_b_obj = self.init_stacks()
        # launch mainf
        self.win.after(0, self.mainf)

    def launch_push_swap(self, numbers):
        inst = subprocess.check_output([PUSH_SWAP_PATH] + numbers,
            stderr=subprocess.STDOUT, timeout=12).splitlines()
        for i in range(len(inst)):
            inst[i] = inst[i].decode("UTF-8")
            if inst[i] not in inst_set:
                print("Error: invalid instructions", file=sys.stderr)
                exit(1)
        return inst

    def get_start_pos(self):
        x = (self.win.winfo_screenwidth() / 2) - (self.win_w / 2)
        y = (self.win.winfo_screenheight() / 2) - (self.win_h / 2)
        return int(x), int(y)

    def init_stacks(self):
        len_a = len(self.stack_a)
        if len_a == 0:
            return None, None
        stack_a_obj = []
        sorted_stack_a = sorted(self.stack_a)
        h = 30 if 800 / len_a > 30 else 800 / len_a
        w = 300 / len_a
        y = 0
        for n in self.stack_a:
            x1, y1 = 0, y * h
            x2, y2 = (sorted_stack_a.index(n) + 1) * w, y1 + h
            bar = self.left_canvas.create_rectangle(x1, y1, x2, y2, fill="white")
            stack_a_obj.append(bar)
            y += 1
        return stack_a_obj, None

    def checker(self):
        if self.stack_b != None:
            return False
        return self.stack_a == sorted(self.stack_a)

    def mainf(self):
        #self.async_actions()
        if self.quit == True:
            self.quit = False
        else:
            self.win.after(1, self.mainf)


numbers = get_input()
v = Visu(numbers)
v.win.mainloop()
