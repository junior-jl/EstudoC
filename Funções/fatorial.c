long int fatorial(int n)
{
    long int aux = n;
    if(n > 1)
    {
       while(aux > 1)
        {
        n *= (aux - 1);
        aux--;
        }
        return n;
    }
    else if(n == 0 || n == 1)
        return 1;
    else
        return -1;
}
