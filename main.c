#include <stdio.h>
#include "myheader.h"

int main() {
    int Midterm, Final, MidtermPercent, FinalPercent;

    printf("Enter Midterm Exam Score: ");
    scanf("%d", &Midterm);

    printf("Enter Midterm Exam Percent: ");
    scanf("%d", &MidtermPercent);

    printf("Enter Final Exam Score: ");
    scanf("%d", &Final);

    printf("Enter Final Exam Percent: ");
    scanf("%d", &FinalPercent);

    printf("Total Point: %d", Calc_Exam(Midterm,MidtermPercent,Final,FinalPercent));



    return 0;
}
