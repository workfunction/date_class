#include <iostream>
#include "Date.h"

// Driver Program to check your implementation
int main()
{
    /* test printMonthCalendar() for all month in 2016 */
    Date date1(29, 2, 2016);
    for(int m=1; m<=12; m++) {
        date1.setMonth(m);
        date1.printMonthCalendar();
    }
    
    return 0;
}