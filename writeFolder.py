import datetime
import time

while True:
    with open('buffer.txt', 'w') as file:
        file.write(str(datetime.datetime.now()))
    time.sleep(5)
