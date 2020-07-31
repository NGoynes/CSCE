import string
import random


def intern(size=5):
    val = string.ascii_uppercase
    rand = ''.join(random.choice(val) for x in range(size))
    return rand
