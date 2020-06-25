import csv

global benchmark

with open('benchmark.txt') as f:
   reader = csv.reader(f)
   benchmark = list(reader)

def get_data(type, algo):
   data_1 = filter(lambda x: x[0] == type and x[1] == algo, benchmark)
   data = map(lambda x: (x[2], x[3]), data_1)
   with open('data-%s-%s.txt' % (type.replace(' ', '_'), algo), 'w') as f:
      for e in data:
         f.write("%s %s\n" % e)

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

algo = ['heapsort', 'shellsort', 'parallel_quicksort']

for t in types:
   for a in algo:
      get_data(t, a)