import Image
i = Image.open("bb.png")
w,h = i.size

for y in xrange(h):
    val = 0
    for x in xrange(w):
        print i.getpixel((x,y))
        if i.getpixel((x,y))[3] > 128:
            val &= 1 << (w-x-1)

    print val
