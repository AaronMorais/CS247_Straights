#!/bin/bash
make clean
rsync -r -a -v -e ssh ~/se/cs247/p1 cs:~/CS247Project
ssh -X cs "cd CS247Project/p1; make; ./straights"
