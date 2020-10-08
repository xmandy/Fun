import my
import hello_ext

def add(x, y):
    print my.show()
    print hello_ext.greet()
    print 'add', x, y
    return x + y
