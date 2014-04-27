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

        outf.write('CASE %s:\n' % filename)
        outf.write('return {\n')
        outf.write('pic[0] = 0;\n')
        outf.write('pic[1] = 0;\n')
        for y in xrange(h):
            val = 0
            for x in xrange(w):
                #print i.getpixel((x,y))
                if i.getpixel((x,y))[3] > 128:
                    val |= 1 << (w-x-1)

            outf.write('pic[%d] = %d;\n' % (y+2, val<<2))
        outf.write('pic[28] = 0;\n')
        outf.write('pic[29] = 0;\n')
        outf.write('};\n')
        outf.write('\n\n')
