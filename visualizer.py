#!/usr/bin/env python3

from tkinter import *
import subprocess
import sys

PUSH_SWAP_PATH = "push_swap/push_swap"
inst_set = ("sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr")
D_FORWARD = 1
D_BACKWARD = -1
S_PAUSE = 0
S_PLAY = 1
S_ONE_STEP = 2
MAX_H = 30
MAX_W = 400

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
        # window
        self.win = Tk()
        self.win.resizable(width=False, height=False)
        self.win.title("Push Swap Visualizer")
        # widgets
        self.win.columnconfigure(0)
        self.win.columnconfigure(1)
        self.win.rowconfigure(0)
        self.win.rowconfigure(1)
        self.canvas_h = 800
        self.canvas_w = 500
        self.tool_box = Frame(self.win, bg="white")
        self.left_canvas = Canvas(self.win, bg="black", highlightthickness=0,
                width=self.canvas_w, height=self.canvas_h)
        self.right_canvas = Canvas(self.win, bg="black", highlightthickness=0,
                width=self.canvas_w, height=self.canvas_h)
        self.tool_box.grid(row=0, column=0, columnspan=2)
        self.left_canvas.grid(row=1, column=0)
        self.right_canvas.grid(row=1, column=1)
        # tool_box content
        self.inst_label = []
        for i in range(9):
            self.inst_label.append(Label(self.tool_box, text="___",
                font="Courier", bg="black", fg="white"))
            self.inst_label[i].pack(side=LEFT)
        self.inst_label[4].configure(bg="white", fg="black")
        self.dir_back = Button(self.tool_box, text="<<",
            command=self.set_dir_back)
        self.step_back = Button(self.tool_box, text="<-",
            command=self.step_back)
        self.play_pause_btn = Button(self.tool_box, text=">",
            command=self.play_pause)
        self.step_forward = Button(self.tool_box, text="->",
            command=self.step_forw)
        self.dir_forw = Button(self.tool_box, text=">>",
            command=self.set_dir_forw)
        self.color_mode = Button(self.tool_box, text="C",
            command=self.set_color_mode)
        self.dir_back.pack(side=LEFT)
        self.step_back.pack(side=LEFT)
        self.play_pause_btn.pack(side=LEFT)
        self.step_forward.pack(side=LEFT)
        self.dir_forw.pack(side=LEFT)
        self.color_mode.pack(side=LEFT)
        # window size and position
        self.win_h = 800
        self.win_w = 1000
        x, y = self.get_start_pos()
        self.win.geometry("+" + str(x) + "+" + str(y))
        # visu data
        self.quit = False
        self.step = -1
        self.dir = D_FORWARD
        self.old_dir = None
        self.state = S_PAUSE
        self.color = True
        len_a = len(self.stack_a)
        self.h = MAX_H if self.canvas_h / len_a > MAX_H else self.canvas_h / len_a
        self.w = MAX_W / len_a
        self.stack_a_obj, self.stack_b_obj = self.init_stacks()
        self.update_inst_labels()
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

    def update_inst_labels(self):
        for i in range(9):
            cur = self.step + i - 4
            if cur < 0 or cur > self.inst_len - 1:
                self.inst_label[i].configure(text="___")
            elif len(self.instructions[cur]) == 2:
                self.inst_label[i].configure(text=self.instructions[cur] + "_")
            else:
                self.inst_label[i].configure(text=self.instructions[cur])
    
    def set_color(self, index):
        col = '#%02x%02x%02x' % (int(255 * (index - 0.3) * (index > 0.3)),
            int(255 * index - ((510 * (index - 0.6)) * (index > 0.6))),
            int((255 - 510 * index) * (index < 0.5)))
        return col

    def create_bar(self, side, x1, y1, x2, y2):
        fill_color = self.set_color(x2/MAX_W) if self.color else\
            "white" if side == 'a' else 'black'
        outline_color = "" if self.color else\
            "black" if side == 'a' else 'white'
        can = self.left_canvas if side == 'a' else self.right_canvas
        return can.create_rectangle(x1, y1, x2 + 10, y2,
            fill=fill_color, outline=outline_color)

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
        y = self.h * (len(stack_obj) - 1)
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
        y = self.h * (len(stack_obj) - 1)
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
            if self.dir == D_FORWARD:
                self.push(inst[-1])
            elif self.dir == D_BACKWARD:
                self.push('a' if inst[-1] == 'b' else 'b')
        elif len(inst) == 2:
            if self.dir == D_FORWARD:
                self.rotate(inst[-1])
            elif self.dir == D_BACKWARD:
                self.reverse_rotate(inst[-1])
        else:
            if self.dir == D_FORWARD:
                self.reverse_rotate(inst[-1])
            elif self.dir == D_BACKWARD:
                self.rotate(inst[-1])

    def set_dir_back(self):
        self.dir = D_BACKWARD

    def set_dir_forw(self):
        self.dir = D_FORWARD

    def play_pause(self):
        self.state = S_PLAY if self.state == S_PAUSE else S_PAUSE
        self.play_pause_btn.config(text=">" if self.state == S_PAUSE else "||")

    def step_back(self):
        self.state = S_ONE_STEP
        self.old_dir = self.dir
        self.dir = D_BACKWARD

    def step_forw(self):
        self.state = S_ONE_STEP
        self.old_dir = self.dir
        self.dir = D_FORWARD

    def set_color_mode(self):
        if self.color:
            self.color = False
            self.right_canvas.config(bg="white")
            if len(self.stack_a_obj) > 0:
                for obj in self.stack_a_obj:
                    self.left_canvas.itemconfig(obj, fill="white", outline="black")
            if len(self.stack_b_obj) > 0:
                for obj in self.stack_b_obj:
                    self.right_canvas.itemconfig(obj, fill="black", outline="white")
        else:
            self.color = True
            self.right_canvas.config(bg="black")
            if len(self.stack_a_obj) > 0:
                for obj in self.stack_a_obj:
                    x1, y1, x2, y2 = self.left_canvas.coords(obj)
                    self.left_canvas.itemconfig(obj,
                        fill=self.set_color(x2/MAX_W), outline="")
            if len(self.stack_b_obj) > 0:
                for obj in self.stack_b_obj:
                    x1, y1, x2, y2 = self.right_canvas.coords(obj)
                    self.right_canvas.itemconfig(obj,
                        fill=self.set_color(x2/MAX_W), outline="")

    def mainf(self):
        if self.state == S_PLAY or self.state == S_ONE_STEP:
            if self.dir == D_FORWARD and self.step < self.inst_len - 1:
                self.step += 1
                self.exec_instruction(self.instructions[self.step])
            elif self.dir == D_BACKWARD and self.step > -1:
                self.exec_instruction(self.instructions[self.step])
                self.step -= 1
            if self.state == S_ONE_STEP:
                self.dir = self.old_dir
                self.old_dir = None
                self.state = S_PLAY
                self.play_pause()
            elif self.step == self.inst_len - 1 or self.step == -1:
                self.play_pause()
            self.update_inst_labels()
            self.left_canvas.update()
            self.right_canvas.update()
        self.win.after(1, self.mainf)


numbers = get_input()
v = Visu(numbers)
v.win.mainloop()
