exception Erro;

datatype ty = IntTy | BoolTy;

datatype exp
	= True
	| False
	| Int of int
	| Add of exp * exp
	| Sub of exp * exp
	| And of exp * exp
	| Eq of exp * exp
	| Or of exp * exp
	| If of exp * exp * exp



fun Tipo (True) = BoolTy
| Tipo (False) = BoolTy
| Tipo (Int _) = IntTy
| Tipo (Add (e1, e2)) = 
	 if (Tipo e1 = IntTy) andalso (Tipo e2 = IntTy) then IntTy else raise Erro
|Tipo (Sub (e1, e2)) = 
	 if (Tipo e1 = IntTy) andalso (Tipo e2 = IntTy) then IntTy else raise Erro
| Tipo (Eq (e1, e2)) =
	 if (Tipo e1 = BoolTy) andalso (Tipo e2 = BoolTy) then BoolTy else raise Erro
| Tipo (Or (e1, e2)) =
	 if (Tipo e1 = BoolTy) andalso (Tipo e2 = BoolTy) then BoolTy else raise Erro
| Tipo (And (e1, e2)) =
	 if (Tipo e1 = BoolTy) andalso (Tipo e2 = BoolTy) then BoolTy else raise Erro
| Tipo (If (e1, e2, e3)) = 
	 if Tipo e1 <> BoolTy then raise Erro
	 else if Tipo e2 <> Tipo e3 then raise Erro
	 else Tipo e2



fun eval (True) = True
| eval (False) = False

| eval (Int n) = Int n

| eval (Add (e1, e2)) =
	 if (Tipo(eval e1) <> IntTy orelse Tipo (eval e2) <> IntTy) then raise Erro
	 else let
	 val (Int n1) = eval e1
	 val (Int n2) = eval e2
	 in
		 Int (n1 + n2)
	 end

| eval (Sub (e1, e2)) =
	 if (Tipo(eval e1) <> IntTy orelse Tipo (eval e2) <> IntTy) then raise Erro
	 else let
	 val (Int n1) = eval e1
	 val (Int n2) = eval e2
	 in
	 	Int (n1 - n2)
	 end

| eval (Eq (e1, e2)) = 
	 if (Tipo(eval e1)) <> (Tipo (eval e2)) then raise Erro
	 else if (eval e1 = eval e2) then True else False

| eval (And (e1, e2)) =
	 if (Tipo(eval e1)) <> BoolTy orelse (Tipo (eval e2)) <> BoolTy then raise Erro
	 else if (eval e1 = True) andalso (eval e2 = True) then True
	 else False

| eval (Or (e1, e2)) =
	 if (Tipo(eval e1)) <> BoolTy orelse (Tipo (eval e2)) <> BoolTy then raise Erro
	 else if (eval e1 = False) andalso (eval e2 = False) then False
	 else True

| eval (If (e1, e2, e3)) = 
	 if (Tipo (eval e1) <> BoolTy) then raise Erro
	 else if eval e1 = True then eval e2 else eval e3

