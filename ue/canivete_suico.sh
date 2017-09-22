#!/bin/bash
v=0;
while [ $v -ne 5 ];  do
	echo "1 - Calculadora"
	echo "2 - Texto"
	echo "3 - Operações"
	echo "4 - Processo"
	echo "5 - Sair"
	echo "Digite sua opção: ";
	read v;
	case $v in
		1)
			./calc
			;;
		2)
			echo "Digite uma palavra: "
			read palavra
			./vog "$palavra"
			;;
		3)
			echo "Digite a primeira operação: "
			read op1
			echo "Digite a segunda operação: "
			read op2
			echo "Digite a terceira operação: "
			read op3
			./op "$op1" "$op2" "$op3"
			echo "Obrigado!"
			date
			;;
		4)
			./proc
			;;
		5)
			echo "Adeus!"
			;;
		*)
			echo "Entrada inválida."
			;;
	esac
done
exit 0
