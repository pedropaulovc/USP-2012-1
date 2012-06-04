(*
(
	(''fun'', [x,y], (x,''+'',y)), [5,(3,''+'',3)]	
)
*)

fun ExpBool (exp1, oper, exp2) = 
	if oper = "And" 
	then exp1 andalso exp2 
	else exp1 orelse exp2;

fun IgualdadeNum (exp1, oper, exp2) = 
	exp1 = exp2;

fun IfThenElse (oper, expbool, exp1, exp2) = 
	if expbool
	then exp1
	else exp2;

fun Calcula x = x
	| Calcula (x, y, z) = x + y + z;
	
Fun([x, y], Expr(x, "+", y), 
