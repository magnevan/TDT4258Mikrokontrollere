import Image
from glob import glob

def printline(val, w):
    line = [' ']*w
    for i in xrange(w):
        if val & (1<<i) > 0:
            line[i] = 'o'
    print ''.join(line)

with open('pictures.txt', 'w') as outf:
    for filename in glob('*.png'):
        i = Image.open(filename)
        w,h = i.size

        outf.write('%s\n' % filename)
        for y in xrange(h):
            val = 0
            for x in xrange(w):
                #print i.getpixel((x,y))
                if i.getpixel((x,y))[3] > 128:
                    val |= 1 << (w-x-1)

            outf.write('%d,\n' % val)
        outf.write('\n\n')
