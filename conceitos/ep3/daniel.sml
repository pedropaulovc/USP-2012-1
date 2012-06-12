(* Resolve programa atrav�s do calculo da Aplica��o dada *)
Duas op��es: a priori e sob demanda,
fun resolve (f : DecFuncao, l : ListaExp) = apriori (f, l);
	ou
fun resolve (f : DecFuncao, l : ListaExp) = sobDemanda (f, l);

	
	fun apriori (f : DecFuncao, l : ListaExp) = reducao(aplicacao(f, l));
	
     
	fun sobDemanda (...) = S� Jesus! \_O_/


	(* Devolve a express�o resultante da substitui��o dos par�metros pelos seus respectivos argumentos *)
	fun aplicacao ("fun", 	[], abstracao : Expressao, expressoes : ListaExp) = abstracao
		| aplicacao ("fun", x :: params : ListaParam, abstracao : Expressao, e :: exps : ListaExp) = aplicacao ("fun", params, substitui (x, abstracao, e), exps);


		(* Substitui exp nas ocorr�ncias de i em abstra��o *)
		fun substitui (i : Id, Valor abstracao, exp : Expressao) =  abstracao
			| substitui (i : Id, ExpBinaria abstracao, exp : Expressao) = substituiExpBinaria(i, abstracao, exp)

			fun substituiExpBinaria (i : Id, a : Expressao, operador, b : Expressao, exp : Expressao) = (substitui(i,) , operador, substitui)
		.
		.
		.
		.
		.
			=> onde vai if (i = x) then substitui x por exp??? de que tipo � a vari�vel x? o.�




	(* Avalia Expressao x *)
	fun reducao (Valor x) = x (* Caso base *)
		| reducao (ExpBinaria x) = reducaoBinaria(x)
		| reducao (IfThenElse x) = reducaoCondicional(x)
		| reducao (Aplicacao x) = resolve(x);


		(* Avalia Expressao Binaria x *)
		fun reducaoBinaria (ExpAritm x) = reducao Aritm(x) | reducaoBinaria (ExpBool x) = reducaoBool(x);
	
			(* Avalia Expressao Aritm�tica a op b *)
			fun reducaoAritm (a : Expressao, "+", b : Expressao) = reducao(a) + reducao(b)
				| reducaoAritm (a : Expressao, "-", b : Expressao) = reducao(a) - reducao(b);

		      (***********************************************************************************************************
						OBS: SUPUS QUE A MENINA DEFINIU EXPBOOL ERRADO!!!
			pra mim, ExpBool = (ExpBool, "And", ExpBool) | (ExpBool, "Or", ExpBool) | (Expressao, "==", Expressao), 
			pois n�o faz sentindo algum usar comparadores l�gicos para dados aritm�ticos o__�. Ou seja, ou o programa
			trabalha com inteiros e faz contas, ou trabalha com booleanos e avalia predicados. 
		      ************************************************************************************************************)
	
			(* Avalia Expressao Booleana a op b *)
			fun reducaoBool (a : ExpBool, "And", b : ExpBool) = if (reducaoBool(a) andalso reducaoBool(b)) then true else false
				| reducaoBool (a : ExpBool, "Or", b : ExpBool) = if (reducaoBool(a)) then true else if (reducaoBool(b)) then true else false
				| reducaoBool (a : Expressao, "==", b : Expressao) = if (reducao(a) = reducao(b)) then true else false;

	
		(* Avalia comando IfThenElse x *)
		fun reducaoCondicional("if", condicao : ExpBool, a : Expressao, b : Expressao) = if (reducaoBool(condicao)) then reducao(a) else reducao(b);
