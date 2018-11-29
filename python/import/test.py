#a = 1
print globals()

spam = __import__('spam', globals(), locals(), [], -1)
print spam

spam = __import__('spam.ham', globals(), locals(), [], -1)
print spam

spam = __import__('spam.ham', None, None, ["a", "egg"], -1)
print spam.__dict__

aaa = 3

spam = __import__('spam.ham', globals(), locals(), ["a", "egg"], -1)
print '**************'
print spam.__dict__

#print globals()
#print a
#print egg
