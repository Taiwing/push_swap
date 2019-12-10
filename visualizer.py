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
        self.instructions = self.launch_push_swap(numbers)
        self.stack_a = []
        for s in numbers:
            self.stack_a.append(int(s))
        print(self.instructions)
        print(self.stack_a)
        self.stack_b = []
        self.win = Tk()
        self.win_h = 800
        self.win_w = 1000
        x, y = self.get_start_pos()
        self.win.geometry(str(self.win_w) + "x" + str(self.win_h) + "+"\
            + str(x) + "+" + str(y))
        self.win.resizable(width=False, height=False)
        self.left_frame = Frame(self.win, bg="black")
        self.right_frame = Frame(self.win, bg="white")
        self.left_frame.pack(side=LEFT, expand=True, fill=BOTH)
        self.right_frame.pack(side=RIGHT, expand=True, fill=BOTH)

    def get_start_pos(self):
        x = (self.win.winfo_screenwidth() / 2) - (self.win_w / 2)
        y = (self.win.winfo_screenheight() / 2) - (self.win_h / 2)
        return int(x), int(y)

    def launch_push_swap(self, numbers):
        inst = subprocess.check_output([PUSH_SWAP_PATH] + numbers,
            stderr=subprocess.STDOUT, timeout=12).splitlines()
        for i in range(len(inst)):
            inst[i] = inst[i].decode("UTF-8")
            if inst[i] not in inst_set:
                print("Error: invalid instructions", file=sys.stderr)
                exit(1)
        return inst

    def checker(self):
        if self.stack_b != None:
            return False
        return self.stack_a == sorted(self.stack_a)


numbers = get_input()
#if numbers == None:
#    exit(1)
v = Visu(numbers)
v.win.mainloop()
