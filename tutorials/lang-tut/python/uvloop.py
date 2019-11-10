import time
import asyncio
# import uvloop

async def main():
    # Main entry-point.
    while True:
        print("In async main")
        time.sleep(1)



# uvloop.install()
asyncio.run(main())

while True:
    print("In while True loop") 
    time.sleep(1)
    

