#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const int CHUNK_SIZE = 500;

/*
 * CS3305 - Assignment 4
 *
 * Created by Salman Shaikh on 2021-11-02
 * Student Number mshaik52 - 250959996
 */


int main() {
    char *strToken;

    //open file
    FILE *filePointer;
    filePointer = fopen("rr_input.txt", "r");

    //make sure file is populated with data
    if (filePointer == NULL) {
        printf("File name invalid, could not open file");
        return 0;
    }
    char testCase[5000];

    //go over file line by line - each line represents test case
    while (!feof(filePointer)) {
        //put the line in testCase variable
        fgets(testCase, 5000, filePointer);

        //get the first string token
        strToken = strtok(testCase, " ");

        int arrivalTimes[CHUNK_SIZE];
        int burstTimes[CHUNK_SIZE];
        int remainingBurst[CHUNK_SIZE];
        int timeQuantum;

        int lineOffSet = 0;
        int numProcesses = -1;

        while (strToken != NULL) {
            //process name
            if (strToken[0] == 'p' || strToken[0] == 'P') {
                numProcesses++;
                lineOffSet = 0;
            }

            //arrival time
            if (lineOffSet == 1) {
                arrivalTimes[numProcesses] = atoi(strToken);
            }

            //burst time
            if (lineOffSet == 2) {
                burstTimes[numProcesses] = atoi(strToken);
                remainingBurst[numProcesses] = atoi(strToken);
            }

            //time quantum - output step
            if (lineOffSet == 3) {
                timeQuantum = atoi(strToken);

                //determine time calculations here
                int correctNumProcesses = numProcesses+1;
                int sumTurnAroundTime=0;
                int totalWaitTime=0;
                float avgWaitTime;
                float avgTurnAroundTime;
                int waitingTimes[correctNumProcesses];
                int turnAroundTimes[correctNumProcesses];
                int i = 0;
                int sum = 0;
                int n = 0;
                bool flag = false;

                //for every process in the test case
                while ( n <correctNumProcesses) {
                    if (remainingBurst[i] <= timeQuantum && remainingBurst[i] > 0) {
                        sum = sum + remainingBurst[i];
                        remainingBurst[i] = 0;
                        flag=true;

                    } else if (remainingBurst[i] > 0) {
                        remainingBurst[i] = remainingBurst[i] - timeQuantum;
                        sum = sum + timeQuantum;
                    }
                    //process complete
                    if (remainingBurst[i] == 0 && flag == true) {

                        waitingTimes[i] = sum - arrivalTimes[i]-burstTimes[i];
                        turnAroundTimes[i] = sum - arrivalTimes[i];

                        flag=false;
                        n++;
                    }
                    if(i == numProcesses) {
                        i=0;
                    } else if(arrivalTimes[i+1] <= sum) {
                        i++;
                    }else {
                        i=0;
                    }
                }

                //output for each process in order
                for(int i =0; i < numProcesses+1; i++){
                    printf("Process: P%d Arrival Time: %d Burst time: %d Waiting Time: %d Turnaround Time: %d\n",i + 1, arrivalTimes[i], burstTimes[i],waitingTimes[i], turnAroundTimes[i]);
                    sumTurnAroundTime = (sumTurnAroundTime + turnAroundTimes[i]);
                    totalWaitTime = (totalWaitTime + waitingTimes[i]);
                }

                //convert to floating point for calculations
                float numProcessForCalculation =correctNumProcesses;

                //output totals and averages
                printf("\nTotal Turnaround Time: %d", sumTurnAroundTime);

                avgWaitTime = totalWaitTime / numProcessForCalculation;
                printf("\nAverage waiting time: %.2f", avgWaitTime);

                avgTurnAroundTime = sumTurnAroundTime  /numProcessForCalculation;
                printf("\nAverage turnaround time: %.2f\n\n", avgTurnAroundTime);
            }
            //next token increase offset by one
            strToken = strtok(NULL, " ");
            lineOffSet++;
        }
    }

    //end of program close file pointer and file
    fclose(filePointer);

    return 0;
}
