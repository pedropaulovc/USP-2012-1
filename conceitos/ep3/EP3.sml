(******************************************************************************
 * MAC0316 - CONCEITOS DE LINGUAGENS DE PROGRAMAÇÃO
 * EP3: SML - Programação Funcional
 * AUTORES: Arthur Branco Costa      - 7278156
 *          Daniel Paulino Alves     - 7156894
 *          Felipe Yamaguti          - 7295336
 *          Pedro Paulo Vezzá Campos - 7538743
 *          Thiago Tatsuo Nagaoka    - 7289197
 * 
 * Neste arquivo estão implementadas todas as funções necessárias
 * para a utilização da linguagem definida na especificação do EP
 * salvo alterações feitas em função de problemas na sintaxe adotada.
 * 
 * Maiores detalhes a respeito do programa podem ser vitos no relatório
 * entregue em anexo. Ao final do arquivo encontram-se exemplos usáveis
 * da linguagem implementada.
******************************************************************************)

print ("\n\n\n\n");

(* Desabilitando erros de "calling poly equal", devido à 
assunção que todos os testes estão bem definidos *)
Control.polyEqWarn := false;

(* Erros do formato "Not a ...", quando o programa não pode inferir
o tipo de uma expressão passada.*)
exception NotABool;
exception NotAInteger;
exception NotAFunction;
exception UnknowOperator;

print "\n\nDeclaracao de Tipos.\n\n";

(* Para este EP, diferentemente do que foi especificado, consideramos 
que uma letra do alfabeto é um Id da linguagem. Como efeito colateral,
variáveis no programa não podem ter apenas uma letra. *)
datatype Id = a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z;

(* Definição de uma expressão na linguagem LFSimp. Composta por valores
atômicos (Inteiros, Bool e Id) e operações (Aritmética, booleana, If-then-else)
e funções *)
datatype Expressao
	= Valor of int
	| Bool of bool
	| id of Id
	| Conta of Expressao * string * Expressao
	| IfThenElse of string * Expressao * Expressao * Expressao
	| Aplicacao of  DecFuncao * Expressao list

and DecFuncao = funcao of string * Id list * Expressao;

print ("\n\n");

(* Responsável por dado um Valor retornar o valor inteiro armazenado *)
fun arrancaInt (Valor valx) = valx
	| arrancaInt (_) = raise NotAInteger

(* Responsável por dado um Bool retornar o valor booleano armazenado *)
fun arrancaBool (Bool valx) = valx
	| arrancaBool (_) = raise NotABool;

print "\n\nFuncoes de uso a priori\n\n\n";

(* Função principal de redução a priori. Tenta reduzir ao máximo uma expressão dada.

 - Caso seja um valor atômico, retorna ele próprio
 - Caso seja uma conta invoca calcula e retorna seu resultado
 - Caso seja um if-then-else reduz o bloco if e retorna a redução do bloco then ou
 do bloco else dependendo da condição do bloco if. 
 - Caso seja uma função invoca aplicaFuncao *)
fun reduz (Valor vala) = Valor vala
	| reduz (Bool vala) = Bool vala
	| reduz (id vala) = id vala
	| reduz (Conta vala) = calcula (vala)
	| reduz (IfThenElse vala) =
		let
			val (ss, aa, bb, cc) = vala
		in
			if (arrancaBool (reduz (aa)) = true) then reduz bb else reduz cc
		end
	| reduz (Aplicacao vala) = aplicaFuncao (Aplicacao vala)
	
(* Função responsável por realizar todas as contas (lados esquerdo e direito) que puder,
ignorando possiveis Ids encontradas durante a execução. *)
and calcula (id vala, aa, id valc) = Conta (id vala, aa, id valc)
	| calcula (id vala, aa, valc) = Conta (id vala, aa, reduz(valc))
	| calcula (vala, aa, id valc) = Conta (reduz(vala), aa, id valc)
	| calcula (vala, "+", valc) = Valor (arrancaInt (reduz(vala)) + arrancaInt (reduz(valc)))
	| calcula (vala, "-", valc) = Valor (arrancaInt (reduz(vala)) - arrancaInt (reduz(valc)))
	| calcula (vala, "And", valc) = Bool (arrancaBool (reduz(vala)) andalso arrancaBool (reduz(valc)))
	| calcula (vala, "Or", valc) = Bool (arrancaBool (reduz(vala)) orelse arrancaBool (reduz(valc)))
	| calcula (vala, "==", valc) =
		let
			val vali = reduz vala
			val valj = reduz valc
		in
			Bool (vali = valj)
		end
	| calcula (_, _, _) = raise UnknowOperator

(* Dada uma lista de expressões retorna uma lista contendo as respectivas reduções *)
and resolveLista (nil) = nil
	| resolveLista (ll::L) = (reduz(ll) :: resolveLista L)

(* Troca todas as ocorrencias do identificador pp  na expressao xx por ee.

Quando o operando da função troca for uma aplicação, a função trocaLista é chamada;
acarretando em uma substituição de todos os parâmetros da lista por seus respectivos
valores *)
and troca (pp, id xx, ee) =
		if (pp = xx) then ee
		else id xx
	| troca (pp, Conta xx, ee) =

	let
		val (aa, bb, cc) = xx
	in
		Conta (troca (pp, aa, ee), bb, troca (pp, cc, ee))	
	end

	| troca (pp, IfThenElse ii, ee) =
	let
		val (ss, aa, bb, cc) = ii
	in
		IfThenElse (ss, troca (pp, aa, ee), troca (pp, bb, ee), troca (pp, cc, ee))
	end
	| troca (pp, Valor aa, xx) = Valor aa
	| troca (pp, Bool aa, xx) = Bool aa
	| troca (pp, Aplicacao aa, xx) =
		let
			val (func, expList) = aa
		in
			Aplicacao (func, trocaLista (pp, expList, xx))
		end

(* Função característica de avaliação a priori: Para cada Id encontrada na declaração
ele é substituído pelos seu respectivo valor, previamente analisado. *)
and trocaLista (pp, [], xx) = nil
	| trocaLista (pp, exp::expList, xx) =
		if (id pp = exp) then xx::trocaLista (pp, expList, xx)
					  else exp::trocaLista (pp, expList, xx)

(* Responsável por substituir todos os parâmetros da declaração da função por
seus respectivos valores, que serão obtidos a partir da função resolveLista; isso ocorre,
através de sucessivas chamadas da função troca *)
and trocaTudo ([], func, E) = func
	| trocaTudo (P, func, []) = func
	| trocaTudo (pp::P, func, ee::E) = trocaTudo (P, troca (pp, func, ee), E)

(* É um sinônimo para trocaTudo, que antes, minimiza todas as expressões contidas
na lista de parâmetros, através da chamada da função resolveLista. *)
and evalParametros (P, E, L:Expressao list) = trocaTudo  (P, E, resolveLista L)

(* Função responsável por desmembrar uma aplicação, preparando os parâmetros para
serem entregues à função evalParametros. *)
and aplicaFuncao (Aplicacao (funcao aa, bb : Expressao list)) =
	let
		val (cc, par, ee) = aa
	in
		reduz (evalParametros (par, ee, bb))
	end
	| aplicaFuncao (_) = raise NotAFunction;


print ("\n\n");
print "\n\nFuncoes de uso sob demanda\n\n\n";

(* Função principal de redução sob demanda. Segue o mesmo comportamento de reduz,
diferenciando-se pela forma do cálculo de dados do tipo Conta e Aplicacao que
são reduzidos através das funções calculaDemanda e aplicaFuncaoDemanda. *)
fun reduzDemanda (Valor vala) = Valor vala
	| reduzDemanda (Bool vala) = Bool vala
	| reduzDemanda (id vala) = id vala
	| reduzDemanda (Conta vala) = calculaDemanda (vala)
	| reduzDemanda (IfThenElse vala) =
		let
			val (ss, aa, bb, cc) = vala
		in
			if (arrancaBool (reduzDemanda aa) = true) then reduzDemanda bb else reduzDemanda cc
		end
	| reduzDemanda (Aplicacao vala) = aplicaFuncaoDemanda (Aplicacao vala)

(* Função responsável por reordenar a expressão passada, de maneira a permitir o cálculo dos
valores assim que tornam-se disponíveis. *)
and calculaDemanda (id vala, aa, id valc) = Conta (id vala, aa, id valc)
	| calculaDemanda (id vala, aa, valc) = Conta (id vala, aa, reduzDemanda(valc))
	| calculaDemanda (vala, aa, id valc) = Conta (reduzDemanda(vala), aa, id valc)

	(* If else *)
	| calculaDemanda (vala, aa, IfThenElse valc) =
		let
			val (ss, xx, yy, zz) = valc
		in
			if (arrancaBool (reduzDemanda xx) = true) then reduzDemanda (Conta (vala, aa, yy)) else reduzDemanda (Conta(vala, aa, zz))
		end
	| calculaDemanda (IfThenElse vala, aa, valc) = 
		let
			val (ss, xx, yy, zz) = vala
		in
			if (arrancaBool (reduzDemanda xx) = true) then reduzDemanda (Conta (yy, aa, valc)) else reduzDemanda (Conta(zz, aa, valc))
		end

	(* + *)
	| calculaDemanda (Valor vala, "+", Valor valc) = Valor (vala + valc)
	| calculaDemanda (Valor vala, "+", Conta valc) = 
		let
			val (aa,bb,cc) = valc
		in
			reduzDemanda (Conta (reduzDemanda (Conta (Valor vala, "+", aa)), bb, cc))
		end
	| calculaDemanda (Conta vala, "+", Valor valc) =
		let
			val (aa,bb,cc) = vala
		in
			reduzDemanda (Conta (aa, bb, Conta (cc, "+", reduzDemanda(Valor valc))))
		end
	| calculaDemanda (Conta vala, "+", Conta valc) =
		reduzDemanda (Conta (reduzDemanda (Conta vala), "+", Conta valc))
	
	(* - *)
	| calculaDemanda (Valor vala, "-", Valor valc) = Valor (vala - valc)
	| calculaDemanda (Valor vala, "-", Conta valc) = 
		let
			val (aa,bb,cc) = valc
		in
			if (bb = "-") then
				reduzDemanda (Conta (reduzDemanda (Conta (Valor vala, "-", aa)), "+", cc))
			else
				reduzDemanda (Conta (reduzDemanda (Conta (Valor vala, "-", aa)), "-", cc))
		end
	| calculaDemanda (Conta vala, "-", Valor valc) =
		let val (aa,bb,cc) = vala
		in
			reduzDemanda (Conta (aa, bb, Conta (cc, "-", reduzDemanda(Valor valc))))
		end
	| calculaDemanda (Conta vala, "-", Conta valc) =
		reduzDemanda (Conta (reduzDemanda (Conta vala), "-", Conta valc))

	(* And *)
	| calculaDemanda (vala, "And", valc) = Bool (arrancaBool (reduzDemanda(vala)) andalso arrancaBool (reduzDemanda(valc)))
	(* Or  *)
	| calculaDemanda (vala, "Or", valc) = Bool (arrancaBool (reduzDemanda(vala)) orelse arrancaBool (reduzDemanda(valc)))
	(* Eq *)
	| calculaDemanda (vala, "==", valc) =
		let
			val vali = reduzDemanda vala
			val valj = reduzDemanda valc
		in
			Bool (vali = valj)
		end
		
	(* Aplicacao *)
	| calculaDemanda (Aplicacao vala, aa, Aplicacao valc)
		= reduzDemanda (Conta (reduzDemanda (Aplicacao vala), aa, reduzDemanda (Aplicacao valc)))
	| calculaDemanda (Aplicacao vala, aa, valc) = reduzDemanda (Conta(reduzDemanda (Aplicacao vala), aa, valc))
	| calculaDemanda (vala, aa, Aplicacao valc) = reduzDemanda (Conta(vala, aa, reduzDemanda (Aplicacao valc)))
	
	| calculaDemanda (_, _, _) = raise UnknowOperator

(* Função responsável por desmembrar a aplicação, preparando os parâme-
tros para serem entregues à função trocaTudo.

Observação: Diferentemente da versão a priori, esta versão não invoca resolveLista
para a lista de parâmetros, como consequência a aplicação após a chamada de
trocaTudo não estará minimizada, abrindo margem para a função calculaDemanda
poder calcular os valores sod demanda, apenas nos momentos necessários, ou seja,
quando eles serão de fato utilizados. *)
and aplicaFuncaoDemanda (Aplicacao (funcao aa, bb : Expressao list)) =
	let
		val (cc, dd, ee) = aa
	in
		reduzDemanda (trocaTudo (dd, ee, bb))
	end
	| aplicaFuncaoDemanda (_) = raise NotAFunction;


print "\n\n";

(* Função principal de avaliação de expressões de maneira a priori. Alias para reduz. *)
fun apriori (xx:Expressao) = reduz xx;

(* Função principal de avaliação de expressões de maneira sob demanda. Alias para reduzDemanda. *)
fun sobdemanda (xx:Expressao) = reduzDemanda xx;

print "\n\n";


(* variaveis de teste *)
(*
print ("\n\n");
val aa = Valor 7; 
val bb = Valor 3;
val cc = Conta (aa, "-", bb);
val dd = Conta (cc, "-", cc);
val ee = Bool (true);
val ff = Bool (false);
val gg = Conta (ee, "And", ff);
val hh = Conta (ee, "Or", ff);
val ii = Conta (gg, "==", hh);
val pp = Conta (Valor 0, "+", Valor 4);
val mn = Conta (id x, "+", id y);
val pq = Conta (Conta (Valor 9, "-", Valor 9), "+", id x);
val kk = Conta (Valor 0, "+" , Conta (Conta (Conta (Conta (Valor 5, "+", Valor 2), "-", Valor 2), "+", Valor 4), "-", Valor 1));
val testIf = IfThenElse ("if", Conta (Valor 5, "==", Conta (Valor 2, "+", Valor 3)), Valor 4, Valor 3);
val testIfid = IfThenElse ("if", Conta (id a, "==", Conta (Valor 2, "+", id b)), Valor 4, Valor 3);
val teste2If = Conta (Valor 5, "+", IfThenElse ("if", Conta (Valor 5, "==", Valor 4), Valor 5, Valor 0));
val teste5 = Conta (Conta (Valor 7, "-", Valor 8), "-", Conta (Valor 9, "+", Valor 10));
val teste3 = Conta (Bool true, "Or", Conta (Bool true, "And", IfThenElse ("if", Conta (Valor 7, "==", Valor 7), Bool false, Bool false)));
val teste4 = Conta (Conta (Bool false, "Or", Bool false), "Or", Conta (Bool true, "And", Bool false));
val teste2 = Conta (Bool false, "And", Conta (Bool false, "Or", Bool true));


reduz cc;
reduzDemanda cc;
print ("\n\n");
reduz aa;
reduzDemanda aa;
print ("\n\n");
reduz dd;
reduzDemanda dd;
print ("\n\n");
reduz gg;
reduzDemanda gg;
print ("\n\n");
reduz mn;
reduzDemanda mn;
print ("\n\n");
reduz kk;
reduzDemanda kk;

print ("\n\nNovos testes\n\n");

reduz teste5;
reduzDemanda teste5;
print ("\n\n");
reduz teste3;
reduzDemanda teste3;
print ("\n\n");
reduz teste4;
reduzDemanda teste4;
print ("\n\n");
and calcula (id vala, aa, id valc) = Conta (id vala, aa, id valc)
	| calcula (id vala, aa, valc) = Conta (id vala, aa, reduz(valc))
	| calcula (vala, aa, id valc) = Conta (reduz(vala), aa, id valc)
reduz teste2;
reduzDemanda teste2;

print ("\n\nTestes mais novos!\n\n");


val func = funcao ("fun", [x, y, z], Conta(id x, "+", id y));
val aplic = Aplicacao (func, [Valor 5, Conta (Valor 3, "+", Valor 3), Conta (Valor 4, "+", Valor 4)]);

print "\n\n";
reduz  aplic;
reduzDemanda aplic;
print "\n\n";

val bla = funcao ("fun", [a, b], IfThenElse ("if", Conta (id a, "==", id b), id a, id b));
val ble = funcao ("fun", [a, c, d], Conta (Aplicacao (bla, [id a, Valor 0]), "+", id d));

reduz (Aplicacao (ble, [Bool true, Valor 0, Valor 1]));
reduzDemanda (Aplicacao (ble, [Bool true, Valor 0, Valor 1]));

print "\n\n";
*)
