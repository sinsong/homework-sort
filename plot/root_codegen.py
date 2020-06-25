from string import Template

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

with open('root-draw.C.in', encoding='utf-8') as f:
    code = f.read()

s = Template(code)

for ty in types:
    t = ty.replace(" ", "_")
    with open('root-draw-%s.C' % t, 'w', encoding='utf-8') as f:
        f.write(s.substitute(type=t))