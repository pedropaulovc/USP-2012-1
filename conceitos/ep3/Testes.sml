(******************************************************************************
 * MAC0316 - CONCEITOS DE LINGUAGENS DE PROGRAMAcaO
 * EP3: SML - Programacao Funcional
 * AUTORES: Arthur Branco Costa      - 7278156
 *          Daniel Paulino Alves     - 7156894
 *          Felipe Yamaguti          - 7295336
 *          Pedro Paulo Vezzá Campos - 7538743
 *          Thiago Tatsuo Nagaoka    - 7289197
 * 
 * Neste arquivo estao os testes implementados para verificar o funcionamento
 * do interpretador da linguagem LFSimp. Depende do arquivo EP3.sml para 
 * funcionar corretamente.
******************************************************************************)

use "EP3.sml";

print ("\n\n");

print ("=== Declaracao de valores e operacoes aritméticas ===\n");
val aa = Valor 7; 
reduz aa;
reduzDemanda aa;
print ("\n\n");

val bb = Valor 3;
reduz bb;
reduzDemanda bb;
print ("\n\n");

val cc = Conta (aa, "-", bb);
reduz cc;
reduzDemanda cc;
print ("\n\n");

val dd = Conta (cc, "-", cc);
reduz dd;
reduzDemanda dd;
print ("\n\n");

val pp = Conta (Valor 0, "+", Valor 4);
reduz pp;
reduzDemanda pp;
print ("\n\n");

(*****************************************************************************)
print ("=== Declaracao de valores e operacoes booleanos ===\n");
val ee = Bool (true);
reduz ee;
reduzDemanda ee;
print ("\n\n");

val ff = Bool (false);
reduz ff;
reduzDemanda ff;
print ("\n\n");

val gg = Conta (ee, "And", ff);
reduz gg;
reduzDemanda gg;
print ("\n\n");

val hh = Conta (ee, "Or", ff);
reduz hh;
reduzDemanda hh;
print ("\n\n");

val ii = Conta (gg, "==", hh);
reduz ii;
reduzDemanda ii;
print ("\n\n");

(*****************************************************************************)
print ("=== Declaracao de operacoes que usam Ids ===\n");
val mn = Conta (id x, "+", id y);
reduz mn;
reduzDemanda mn;
print ("\n\n");

val pq = Conta (Conta (Valor 9, "-", Valor 9), "+", id x);
reduz pq;
reduzDemanda pq;
print ("\n\n");

(*****************************************************************************)
print ("=== Declaracao de operacoes mais complexas ===\n");
val kk = Conta (Valor 0, "+" , Conta (Conta (Conta (Conta (Valor 5, "+", Valor 2), "-", Valor 2), "+", Valor 4), "-", Valor 1));
reduz kk;
reduzDemanda kk;

val teste5 = Conta (Conta (Valor 7, "-", Valor 8), "-", Conta (Valor 9, "+", Valor 10));
reduz teste5;
reduzDemanda teste5;
print ("\n\n");

val teste4 = Conta (Conta (Bool false, "Or", Bool false), "Or", Conta (Bool true, "And", Bool false));
reduz teste4;
reduzDemanda teste4;
print ("\n\n");

val teste2 = Conta (Bool false, "And", Conta (Bool false, "Or", Bool true));
reduz teste2;
reduzDemanda teste2;
print ("\n\n");


(*****************************************************************************)
print ("=== Declaracao de operacoes que usam IfThenElse ===\n");
val testIf = IfThenElse ("if", Conta (Valor 5, "==", Conta (Valor 2, "+", Valor 3)), Valor 4, Valor 3);
reduz testIf;
reduzDemanda testIf;
print ("\n\n");

val testIfid = IfThenElse ("if", Conta (id a, "==", Conta (Valor 2, "+", id b)), Valor 4, Valor 3);

val teste2If = Conta (Valor 5, "+", IfThenElse ("if", Conta (Valor 5, "==", Valor 4), Valor 5, Valor 0));
reduz teste2If;
reduzDemanda teste2If;
print ("\n\n");

val teste3 = Conta (Bool true, "Or", Conta (Bool true, "And", IfThenElse ("if", Conta (Valor 7, "==", Valor 7), Bool false, Bool false)));
reduz teste3;
reduzDemanda teste3;
print ("\n\n");

(*****************************************************************************)
print ("=== Declaracao de funcoes ===\n");
val func = funcao ("fun", [x, y, z], Conta(id x, "+", id y));
val aplic = Aplicacao (func, [Valor 5, Conta (Valor 3, "+", Valor 3), Conta (Valor 4, "+", Valor 4)]);
reduz  aplic;
reduzDemanda aplic;
print "\n\n";

val func2 = funcao ("fun", [a, b], IfThenElse ("if", Conta (id a, "==", id b), id a, id b));
val aplic2 = funcao ("fun", [a, c, d], Conta (Aplicacao (func2, [id a, Valor 0]), "+", id d));
reduz (Aplicacao (aplic2, [Bool true, Valor 0, Valor 1]));
reduzDemanda (Aplicacao (aplic2, [Bool true, Valor 0, Valor 1]));
print "\n\n";

