
def decorator(orig_func, *args):
    def printer(*args):
        print(args)
        return orig_func()
    return printer

@decorator("Haha")
def play():
    print("play")

play()
