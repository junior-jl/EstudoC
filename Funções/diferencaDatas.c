enum meses { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

int diferencaDatas(int dia1, int mes1, int dia2, int mes2)
{
    while (mes1 != mes2)
    {
        --mes2;
        if(mes2 == JAN || mes2 == MAR || mes2 == MAY || mes2 == JUL || mes2 == AUG || mes2 == OCT || mes2 == DEC)
        {
            dia2 += 31;
        }
        else if(mes2 == APR || mes2 == JUN || mes2 == SEP || mes2 == NOV)
        {
            dia2 += 30;
        }
        else
        {
            dia2 += 28;
        }
    }
    dia2 -= dia1;
    return dia2;
}
