import numpy as np

numbers = np.linspace(100, 1000000, 500)

def gen_tester_by_ty(ty):
    with open('code.cpp', 'a') as f:
       for n in numbers:
            f.write('tester<%s, %d>();\n' % (ty, n))

types = [
    'char',
    'short',
    'int',
    'long',
    'float',
    'double',
    '__int64',
    'long double'
]

for ty in types:
    gen_tester_by_ty(ty)