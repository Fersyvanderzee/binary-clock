import random


def return_random_time():
    hour = random.randint(0, 23)
    minute = random.randint(0, 59)
    time = f'{hour}:{minute}'
    return time
