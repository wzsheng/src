#!/bin/env python
# Prepare a list of programs without examples for removing them from the stable version
import os
import rsf.doc
import rsf.prog

progs = rsf.doc.progs
for prog in progs.keys():
    sfprog = rsf.doc.progs[prog]
    if not sfprog.uses:
        if not os.path.dirname(rsfprog.file) in ('system/main','plot/test','plot/main',
                                                 'su/plot','pens/main',
                                                 'user/ivlad','user/jennings'):
            print sfprog.file

