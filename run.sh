#!/bin/bash
make clean
ssh -X cs "rm -r CS247Project"
cd ../
scp -r P1 cs:CS247Project
ssh -X cs "cd CS247Project; make clean; make; ./straights"
