#!/usr/bin/env bash

createTestCommands () {
    rm commands
    touch commands
	if [ ${1} == "All_Computer" ]
	then
	    echo "c" >> commands
	    echo "c" >> commands
	    echo "c" >> commands
	    echo "c" >> commands
	fi
	if [ ${1} == "Deck_Ragequit" ]
	then
	    echo "h" >> commands
	    echo "c" >> commands
	    echo "c" >> commands
	    echo "c" >> commands
	    echo "deck" >> commands
	    echo "ragequit" >> commands
	fi
}

runTest() {
#create ourOutput file for our code
g++ Straights.cpp -o straights
createTestCommands ${2}
./straights ${1} > ourOutput < commands

scp commands aemorais@linux032.student.cs.uwaterloo.ca:cs247/commands
#create providedOutput file for given binary
ssh -t -t aemorais@linux032.student.cs.uwaterloo.ca << EOF
cd cs247
./straights ${1} > providedOutput < commands
logout
EOF

#diff both providedOutput and ourOutput file
scp aemorais@linux032.student.cs.uwaterloo.ca:cs247/providedOutput providedOutput
diff ourOutput providedOutput >> testResults
}

for number in {1..10000}
do
	rm testResults
	touch testResults
	runTest number "All_Computer"
	runTest number "Deck_Ragequit"
done