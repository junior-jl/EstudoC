
int solution(int number) {
		// code here
    int soma = 0, i;
    if(number>0){
      for(i=number-1;i>0;i--){
        if((i%3 == 0)||(i%5 == 0)){
          soma = soma + i;
        }
      } 
    }else{
      soma = 0;
    }
    return soma;
}

