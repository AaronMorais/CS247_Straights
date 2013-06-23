#!/usr/bin/env bash

createTestCommands () {
    rm commands
    touch commands
    echo "c" >> commands
    echo "c" >> commands
    echo "c" >> commands
    echo "c" >> commands
}

#create ourOutput file for our code
g++ Straights.cpp -o straights
createTestCommands
./straights ${1} > ourOutput < commands

#create providedOutput file for given binary
ssh -t -t aemorais@linux032.student.cs.uwaterloo.ca << EOF
cd cs247
createTestCommands
./straights ${1} > providedOutput < commands
logout
EOF

#diff both providedOutput and ourOutput file
scp aemorais@linux032.student.cs.uwaterloo.ca:cs247/providedOutput providedOutput
diff ourOutput providedOutput
