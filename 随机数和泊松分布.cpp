double uniform()
{
    double t;
    seed = (2045*(seed)+15)%1048576;
    t=(seed)/1048576.0;
    return(t);
}
int poisson(double lambda) 
{ 
    int i,x; 
    double a,b,u; 
    a=exp(-lambda); 
    i=0; 
    b=1.0; 
    do { 
        u=uniform(); 
        b*=u; 
        i++; 
    } while(b>=a); 
    x=i-1; 
    return(x); 
} 

