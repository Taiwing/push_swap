#!/usr/bin/env python3

from tkinter import *
import subprocess
import sys

PUSH_SWAP_PATH = "push_swap/push_swap"
inst_set = ("sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr")
D_FORWARD = 1
D_BACKWARD = -1

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
        self.inst_len = len(self.instructions)
        self.stack_a = []
        for s in numbers:
            self.stack_a.append(int(s))
        self.stack_b = []
        self.sorted_stack = sorted(self.stack_a)
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
        self.step = -1
        self.dir = D_FORWARD
        len_a = len(self.stack_a)
        self.h = 30 if 800 / len_a > 30 else 800 / len_a
        self.w = 300 / len_a
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

    def create_bar(self, side, x1, y1, x2, y2):
        bar = None
        if side == 'a':
            bar = self.left_canvas.create_rectangle(x1, y1, x2 + 10, y2,
                fill="white", outline="black")
        elif side == 'b':
            bar = self.right_canvas.create_rectangle(x1, y1, x2 + 10, y2,
                fill="black", outline="white")
        return bar

    def init_stacks(self):
        len_a = len(self.stack_a)
        if len_a == 0:
            return None, None
        stack_a_obj = []
        y = 0
        for n in self.stack_a:
            x1, y1 = 0, y * self.h
            x2, y2 = (self.sorted_stack.index(n) + 1) * self.w, y1 + self.h
            bar = self.create_bar('a', x1, y1, x2, y2)
            stack_a_obj.append(bar)
            y += 1
        return stack_a_obj, None

    def swap(self, arg):
        stack = self.stack_a if arg == 'a' else self.stack_b
        stack_obj = self.stack_a_obj if arg == 'a' else self.stack_b_obj
        can = self.left_canvas if arg == 'a' else self.right_canvas
        if len(stack) > 1 and len(stack_obj) > 1:
            stack[0], stack[1] = stack[1], stack[0]
            can.move(self.stack_a_obj[0], 0, self.h)
            can.move(self.stack_a_obj[1], 0, -self.h)
            stack_obj[0], stack_obj[1] = stack_obj[1], stack_obj[0]

    def push_a(self):
        if self.stack_b == None or len(self.stack_b) == 0:
            return
        to_move = self.stack_b.pop(0)
        self.right_canvas.delete(self.stack_b_obj.pop(0))
        if self.stack_b_obj != None:
            for obj in self.stack_b_obj:
                self.right_canvas.move(obj, 0, -self.h)
        if self.stack_a_obj != None:
            for obj in self.stack_a_obj:
                self.left_canvas.move(obj, 0, self.h)
        x2 = (self.sorted_stack.index(to_move) + 1) * self.w
        to_move_obj = self.create_bar('a', 0, 0, x2, self.h)
        if self.stack_a != None and len(self.stack_a) > 0:
            self.stack_a.insert(0, to_move)
            self.stack_a_obj.insert(0, to_move_obj)
        else:
            self.stack_a = [to_move]
            self.stack_a_obj = [to_move_obj]

    def push_b(self):
        if self.stack_a == None or len(self.stack_a) == 0:
            return
        to_move = self.stack_a.pop(0)
        self.left_canvas.delete(self.stack_a_obj.pop(0))
        if self.stack_a_obj != None:
            for obj in self.stack_a_obj:
                self.left_canvas.move(obj, 0, -self.h)
        if self.stack_b_obj != None:
            for obj in self.stack_b_obj:
                self.right_canvas.move(obj, 0, self.h)
        x2 = ((self.sorted_stack.index(to_move) + 1) * self.w)
        to_move_obj = self.create_bar('b', 0, 0, x2, self.h)
        if self.stack_b != None and len(self.stack_b) > 0:
            self.stack_b.insert(0, to_move)
            self.stack_b_obj.insert(0, to_move_obj)
        else:
            self.stack_b = [to_move]
            self.stack_b_obj = [to_move_obj]
    
    def push(self, arg):
        if arg == 'a':
            self.push_a()
        if arg == 'b':
            self.push_b()

    def rotate_internal(self, stack, stack_obj, can):
        first = stack.pop(0)
        y = self.h * (len(stack) - 1)
        x2 = ((self.sorted_stack.index(first) + 1) * self.w)
        stack.append(first)
        first = stack_obj.pop(0)
        for i in range(len(stack_obj)):
            can.move(stack_obj[i], 0, -self.h)
        stack_obj.append(first)
        can.move(first, 0, y)

    def rotate(self, arg):
        if (arg == 'a' or arg == 'r') and len(self.stack_a) > 1:
            self.rotate_internal(self.stack_a,
                self.stack_a_obj, self.left_canvas)
        if (arg == 'b' or arg == 'r') and len(self.stack_b) > 1:
            self.rotate_internal(self.stack_b,
                self.stack_b_obj, self.right_canvas)
    
    def reverse_rotate_internal(self, stack, stack_obj, can):
        last = stack.pop()
        y = self.h * (len(stack) - 1)
        x2 = ((self.sorted_stack.index(last) + 1) * self.w)
        stack.insert(0, last)
        last = stack_obj.pop()
        for i in range(len(stack_obj)):
            can.move(stack_obj[i], 0, self.h)
        stack_obj.insert(0, last)
        can.move(last, 0, -y)

    def reverse_rotate(self, arg):
        if (arg == 'a' or arg == 'r') and len(self.stack_a) > 1:
            self.reverse_rotate_internal(self.stack_a,
                self.stack_a_obj, self.left_canvas)
        if (arg == 'b' or arg == 'r') and len(self.stack_b) > 1:
            self.reverse_rotate_internal(self.stack_b,
                self.stack_b_obj, self.right_canvas)

    def exec_instruction(self, inst):
        if inst[0] == 's':
            self.swap(inst[-1])
        elif inst[0] == 'p':
            self.push(inst[-1])
        elif len(inst) == 2:
            self.rotate(inst[-1])
        else:
            self.reverse_rotate(inst[-1])

    def checker(self):
        if self.stack_b != None:
            return False
        return self.stack_a == sorted(self.stack_a)

    def mainf(self):
        #self.async_actions()
        if self.dir == D_FORWARD and self.step < self.inst_len - 1:
            self.step += 1
            self.exec_instruction(self.instructions[self.step])
        elif self.dir == D_BACKWARD and self.step > -1:
            self.exec_instruction(self.instructions[self.step])
            self.step -= 1
        self.left_canvas.update()
        self.right_canvas.update()
        if self.quit == True:
            self.quit = False
        else:
            self.win.after(1, self.mainf)


numbers = get_input()
v = Visu(numbers)
v.win.mainloop()
