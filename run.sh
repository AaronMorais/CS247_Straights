#!/bin/bash
make clean
cd ../
rsync -r -a -v -e ssh --delete ~/se/cs247/p1 cs:~/CS247Project
ssh -X cs "cd CS247Project/p1; make clean; make; ./straights"
