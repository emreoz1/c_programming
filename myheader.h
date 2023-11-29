int Calc_Exam(int Midterm, int Final, int MidtermPercent, int FinalPercent){

    Midterm = Midterm * MidtermPercent / 100;
    Final = Final * FinalPercent / 100;


    int Total = Midterm + Final;

    return Total;

}