#!/bin/bash
make clean
cd ../
scp -r P1 cs:CS247Project
ssh -X cs "cd CS247Project; make; ./straights"
