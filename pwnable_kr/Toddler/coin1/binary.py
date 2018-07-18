from pwn import *
from time import sleep


def start(script):
    return process(script)

def parse_coins_chances(line):
    def parse_num(tok):
        print "Tok:", tok
        return int(tok.split("=")[1])

    nc = line.splitlines()[-1].split(' ')
    print "nc: ", nc
    n = parse_num(nc[0])
    c = parse_num(nc[1])
    return n,c

def request(interval, game):
    def parse_weight(s):
        return int(s[:-1])
    a,b = interval
    idx = [str(n) for n in range(a,b+1)]
    msg = " ".join(idx)
    print "Requesting interval:", interval
    game.sendline(msg)
    #sleep(1)
    resp = game.recv(timeout=6000)
    print "Response to request: ", resp
    w = parse_weight(resp)
    print "Weight of interval: ", w 
    return w

def answer(idx, game):
    idx = str(idx)
    print "Sending answer:",idx 
    game.sendline(idx)
    #sleep(1)
    ans = game.recvline(timeout=6000)
    return ans

def split_side(side):
    a,b = side
    length = b - a + 1
    if length == 2:
        left_side = (a,a)
        right_side = (b,b)
    else:
        middle = a + length/2
        left_side = (a, middle)
        right_side = (middle+1,b)
    print "Split side:", side, "into:", left_side, right_side
    return (left_side,right_side)


def play(num_coins,chances, game):
    
    chance_left = chances
    a,b = 0, num_coins-1
    

    left_side, right_side = split_side((0, num_coins-1))
    side = left_side
    while chance_left:
        print "Left side: ", left_side, "Right side:", right_side
        side = left_side
        weight = request(side, game)
        if weight % 10 == 0:
            side = right_side

        splits = split_side(side)
        left_side = splits[0]
        right_side = splits[1]
           
        chance_left-=1
    return answer(side[0], game)

def run(game):
    found = 0
    
    welcome = game.recv()
    nc_line = welcome.splitlines()[-1]
    while True:
        num_coins, chances = parse_coins_chances(nc_line)
        reply = play(num_coins, chances,game)
        print "Reply to answer: ", reply
        if "Correct" in reply:
            found+=1
            print "Score: ", found
        nc_line = game.recvline(timeout=6000)




if __name__ == "__main__":
    game = start('./game.sh')
    sleep(5)
    run(game)

