#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

        int lineOffSet =0;
        int numProcesses =-1;

        while (strToken != NULL) {
            //process name
            if (strToken[0] == 'p' || strToken[0] == 'P') {
                printf("%s\n",strToken);
                numProcesses++;
                lineOffSet=0;
            }

            //arrival time
            if(lineOffSet == 1) {
                printf("%s\n",strToken);
                arrivalTimes[numProcesses]= atoi(strToken);
            }

            //burst time
            if(lineOffSet == 2) {
                printf("%s\n",strToken);
                burstTimes[numProcesses] = atoi(strToken);
            }

            //time quantum
            if(lineOffSet == 3) {
                printf("%s\n",strToken);
                timeQuantum = atoi(strToken);
                printf("\n");
                //determine time calculations here

                int limit =0;
                int sum=0;
                //for every process in the test case
                while (limit < numProcesses) {
                    if(burstTimes[limit] <= timeQuantum && burstTimes[limit] > 0) {
                        sum = sum + burstTimes[limit];
                        remainingBurst[limit] =0;


                    } else if(burstTimes[limit] > 0 ) {
                        remainingBurst[limit] = burstTimes[limit] - timeQuantum;
                        sum = sum + timeQuantum;
                    }
                }

                if(remainingBurst[limit]==0) {
                    printf()
                }


            }
            strToken=strtok(NULL," ");
            lineOffSet++;
        }
    }

    fclose(filePointer);

    return 0;
}
