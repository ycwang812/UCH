from tkinter import *

class App(Frame):
    
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.pack()
        self.createWidgets()

    def createWidgets(self):
        self.hi_there = Button(self)
        self.hi_there["text"] = "Hello World\n(click me)"
        self.hi_there["command"] = self.say_hi
        self.hi_there.pack(side="top")

        self.QUIT = Button(self, text="QUIT", fg="red", command=root.destroy)
        self.QUIT.pack(side="bottom")

    def say_hi(self):
        print("hi there, everyone!")
        

root = Tk()

some = Label(root, text="Tk GUI Test!!!", width="30", height="5")
some.pack()

myapp = App(master=root)
myapp.master.title("My App")
myapp.master.maxsize(1000, 400)

myapp.mainloop()
