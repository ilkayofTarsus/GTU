(defun kelimelereAyir (bosluk input)	  	;; inputu separator'a(bosluk inputu) gelen kelimelere ayırır
  (let ((result '())				;; bu durumda separatorumuz boşluk karakteri
        (current '())
        (bosluk-length (length bosluk)))	;; length'in boşluğunu alıyor o da bir'e eşit
    (dotimes (i (length input))			;; gelen inputun char olarak uzunluğu kadar döngü oluşturdum
      (let ((char (char input i)))		;; inputtaki her charı char adındaki değişkene atıyor 
        (if (string= bosluk (subseq input i (+ i bosluk-length)))	;; mevcut charın bosluk olup olmadığını kontrol ediyor eğer boşluksa yeni bir kelime olarak result'a depolalıyor
            (progn
              (push (coerce (nreverse current) 'string) result)		;; bosluğu gorene kadar currente attığı keliemeyi ters dondurerek result'a kaydediyor
              (setq current '()))					;; current sıfırlanıyor
            (push char current))))					;; if sağlanmazsa olan charları currente atıyor
    (push (coerce (nreverse current) 'string) result)			;; son kelimeyi de resulta kaydeder
    (nreverse result)))


(defparameter KW_DEF "def")			;; Global değişken olarak atanmış tokenlar
(defparameter KW_IF "if")
(defparameter KW_ELSE "else")
(defparameter KW_AND "and")
(defparameter KW_OR "or")
(defparameter KW_NOT "not")
(defparameter KW_EQUAL "equal")
(defparameter KW_LESS "less")
(defparameter KW_NILL "nill")
(defparameter KW_APPEND "append")
(defparameter KW_CONCAT "concat")
(defparameter OP_SUM "+")
(defparameter OP_MIN "-")
(defparameter OP_MUL "*")
(defparameter OP_DIV "/")
(defparameter KW_SET "set")
(defparameter KW_FOR "for")
(defparameter KW_EXIT "exit")
(defparameter KW_LOAD "load")
(defparameter KW_DISPLAY "display")
(defparameter KW_TRUE "true")
(defparameter KW_FALSE "false")
(defparameter OP_OP "(")
(defparameter OP_CP ")")
(defparameter OP_COMMA ",")
(defparameter IDENTIFIER "IDENTIFIER")
(defparameter VALUEF "valuef")
(defparameter ERROR-T "error")
(defparameter EXP "EXP")

(defvar *func-table* (make-hash-table)) ;; fonksiyonların tutulacağı hash-table

(defun add-to-hash-table (key value)
  (setf (gethash key *func-table*) value))

(defun get-from-hash-table (key)
  (gethash key *func-table*))



(defparameter *ops*			;; token-list adında global bir list tokenları tutar
	(list
		(list 'OP_SUM "+")
		(list 'OP_MIN "-")
		(list 'OP_MUL "*")
		(list 'OP_DIV "/")
	)
)
(defparameter *token-list*			;; token-list adında global bir list tokenları tutar
  (list
    (list 'KW_DEF "def")
    (list 'KW_IF "if")
    (list 'KW_ELSE "else")
    (list 'KW_AND "and")
    (list 'KW_OR "or")
    (list 'KW_NOT "not")
    (list 'KW_EQUAL "equal")
    (list 'KW_LESS "less")
    (list 'KW_NILL "nill")
    (list 'KW_APPEND "append")
    (list 'KW_CONCAT "concat")
    (list 'OP_SUM "+")
    (list 'OP_MIN "-")
    (list 'OP_MUL "*")
    (list 'OP_DIV "/")
    (list 'KW_SET "set")
    (list 'KW_FOR "for")
    (list 'KW_EXIT "exit")
    (list 'KW_LOAD "load")
    (list 'KW_DISPLAY "display")
    (list 'KW_TRUE "true")
    (list 'KW_FALSE "false")
    (list 'OP_OP "(")
    (list 'OP_CP ")")
    (list 'OP_COMMA ",")
  )
)

					;; CFG  CONTEXT FREE GRAMMAR ;; 
(defparameter *EXP*
	(list
		(list "OP_OP" "OP_SUM" "EXP" "EXP" "OP_CP")
		(list "OP_OP" "OP_MIN" "EXP" "EXP" "OP_CP")
		(list "OP_OP" "OP_MUL" "EXP" "EXP" "OP_CP")
		(list "OP_OP" "OP_DIV" "EXP" "EXP" "OP_CP")
		(list "OP_OP" "IDENTIFIER" "OP_CP")
		(list "OP_OP" "IDENTIFIER" "EXP" "OP_CP")
		(list "OP_OP" "IDENTIFIER" "EXP" "EXP" "OP_CP")
		(list "valuef")
	)
)
(defparameter *FUNCTION*
	(list
		(list "OP_OP" "def" "IDENTIFIER" "EXP" "OP_CP")
		(list "OP_OP" "def" "IDENTIFIER" "EXP" "EXP" "OP_CP")
		(list "OP_OP" "def" "IDENTIFIER" "EXP" "EXP" "EXP" "OP_CP")
	)
)


						;; BU ÖDEVİN LEXER'I ;;
(defun lexer2 (user-input)
	(let ((words (kelimelereAyir " " user-input))  (token-series '()))
		(loop for word in words do
			(cond
			    	((string= KW_IF word) (push KW_IF token-series))
			    	((string= KW_ELSE word) (push KW_ELSE token-series))
			    	((string= KW_AND word) (push KW_AND token-series))
			    	((string= KW_OR word) (push KW_OR token-series))
			    	((string= KW_NOT word) (push KW_NOT token-series))
			    	((string= KW_EQUAL word) (push KW_EQUAL token-series))
			    	((string= KW_LESS word) (push KW_LESS token-series))
			    	((string= KW_NILL word) (push KW_NILL token-series))
			    	((string= KW_APPEND word) (push KW_APPEND token-series))
			    	((string= KW_CONCAT word) (push KW_CONCAT token-series))
			    	((string= KW_SET word) (push KW_SET token-series))
			    	((string= KW_FOR word) (push KW_FOR token-series))
			    	((string= KW_EXIT word) (push KW_EXIT token-series))
			    	((string= KW_DEF word) (push KW_DEF token-series))
			    	((string= KW_LOAD word) (push KW_LOAD token-series))
			    	((string= KW_DISPLAY word) (push KW_DISPLAY token-series))
			    	((string= KW_TRUE word) (push KW_TRUE token-series))
			    	((string= KW_FALSE word) (push KW_FALSE token-series))
			    	((string= OP_OP word) (push "OP_OP" token-series))
			    	((string= OP_CP word) (push "OP_CP" token-series))
			    	((string= OP_SUM word) (push "OP_SUM" token-series))
			    	((string= OP_MUL word) (push "OP_MUL" token-series))
			    	((string= OP_MIN word) (push "OP_MIN" token-series))
			    	((string= OP_COMMA word) (push "OP_COMMA" token-series))
			    	((string= OP_DIV word) (push "OP_DIV" token-series))
			    	((string= EXP word) (push "EXP" token-series))
			   	((is-identifier word) (push IDENTIFIER token-series))	
			   	((not(= (is-valuef word) -1)) (push VALUEF token-series))
			   	((push ERROR-T token-series))
			)
		)
(nreverse token-series)	)
)
					;; BİR ÖNCEKİ ÖDEVDEKİ LEXER ;;
(defun lexer(user-input)
  (let ((words (kelimelereAyir " " user-input)))
    (format t "Girilen komutlar:~%")
    (loop for word in words do
      (cond
    	((string= KW_IF word) (format t "KW_IF~%"))
    	((string= KW_ELSE word) (format t "KW_ELSE~%"))
    	((string= KW_AND word) (format t "KW_AND~%"))
    	((string= KW_OR word) (format t "KW_OR ~%"))
    	((string= KW_NOT word) (format t "KW_NOT ~%"))
    	((string= KW_EQUAL word) (format t "KW_EQUAL ~%"))
    	((string= KW_LESS word) (format t "KW_LESS~%"))
    	((string= KW_NILL word) (format t "KW_NILL ~%"))
    	((string= KW_APPEND word) (format t "KW_APPEND ~%"))
    	((string= KW_CONCAT word) (format t "KW_CONCAT~%"))
    	((string= KW_SET word) (format t "KW_SET~%"))
    	((string= KW_FOR word) (format t "KW_FOR~%"))
    	((string= KW_EXIT word) (format t "KW_EXIT ~%"))
    	((string= KW_DEF word) (format t "KW_DEF ~%"))
    	((string= KW_LOAD word) (format t "KW_LOAD~%"))
    	((string= KW_DISPLAY word) (format t "KW_DISPLAY~%"))
    	((string= KW_TRUE word) (format t "KW_TRUE~%"))
    	((string= KW_FALSE word) (format t "KW_FALSE~%"))
    	((string= OP_OP word) (format t "OP_OP~%"))
    	((string= OP_CP word) (format t "OP_CP~%"))
    	((string= OP_SUM word) (format t "OP_SUM~%"))
    	((string= OP_MUL word) (format t "OP_MUL~%"))
    	((string= OP_MIN word) (format t "OP_MIN~%"))
    	((string= OP_COMMA word) (format t "OP_COMMA ~%"))
    	((string= OP_DIV word) (format t "OP_DIV ~%"))
    	((string= IDENTIFIER word) (format t "IDENTIFIER ~%"))
	(t (format t "Syntax Error: ~a ~%"word))))))
	
(defun create-valuef (input)
	(setq pos-b (is-valuef input))
	(setq pos-b-1 (+ 1 pos-b))
	(if ( = pos-b -1) (return))
	(let* ((before (subseq input 0 pos-b))
		(after (subseq input pos-b-1 ))
		(before-merged (parse-integer before))
		(after-merged (parse-integer after)))
	(list before-merged after-merged))
)

(defun is-valuef (input)
  (let ((position-b -1) (index 0))
    (loop for char in (coerce input 'list) do
          (if (and (not (char= char #\b)) (not (digit-char-p char)))
              (return))
          (if (char= char #\b)
              (setq position-b index))
          (incf index))
    position-b))

(defun is-identifier (input )
	(let 	((first-char (elt input 0))
		(ret-val T))
		(if (alpha-char-p first-char)
			(progn
				  (setq sub-string (subseq input 1 (length input)))
				  (do* ((index 0 (1+ index))
					(char (elt sub-string index) (elt sub-string index)))
				       ((>= index ( - (length sub-string) 1)))
				    )
		
			)
		(setq ret-val nil)
		)
	ret-val
	)
)

(defun is-EXP (input)
	(let ((ret-val nil))
		(if (member (lexer2 input) *EXP* :test #'equal)
			(setq ret-val T)
		)
	ret-val
	)
)	


(defun is-legal (input)
	(let ((ret-val nil))
		(lexer2 input) 
		(if (or (is-EXP input) (is-FUNCTION input))
			(setq ret-val T)
		)
	ret-val)
)

(defun is-appr-grammer(input)				;; iç içe expressionları tamamen sadeleştirir ve bu uygun bir grammer mi bunu dondurur
	(setq tokens (lexer2 input))	
	(let((is-same nil))
		(loop :do
			(if (not is-same) 
			(progn 
				(setq tokens-t (in-exp tokens))
				(if (equal tokens-t tokens) 
					(setq is-same T)
				)	
			)
			(return)
			)
		(setq tokens tokens-t)
		)
	(equal tokens (list "EXP")))
)

(defun in-exp(exp)				;; iç içe expressionları bir basamak sadeleştirir
	(loop for a from 0 below (length exp) do
		(let ((sub-list '()))
		(loop for b from a below (length exp) do
			(setq sub-list (nreverse sub-list) )
			(push (nth b exp) sub-list)
			(setq sub-list (nreverse sub-list) )
			(if (member sub-list *EXP* :test #'equal)
				(progn
					(setq first-part (subseq exp 0 a))
					(setq second-part (subseq exp  (+ 1 b) (length exp)))
					(setq first-part (append first-part (list "EXP")))
					(setq exp (append first-part second-part))
				)
			)			
		)
	))
	exp
)

(defun evaluate(input)							;; Fonkyıon cagrısı ve diğer expressionların kontrol edildiği bölge işlem yapar sonucu döndğrğr
	(let ((sonuc 0) (index 1))
	(if (is-appr-grammer input)
		(progn
			(if (not  (or  (equal 0 (func-call input)) (equal 1 (func-call input)) (equal 2 (func-call input)) (equal 3 (func-call input)) (equal -1 (func-call input))))		;; fonskyıon cagrısı ise buraya girer
				(progn
					(setq func-type (func-call input))
					(setq func-id (nth 1 (kelimelereAyir " " input)))
					(setq sonuc (evaluate (gethash-func func-id)))
				)
				(progn
					(setq hesaplanacak (kelimelereAyir " " input))
					(if (= -1 (is-valuef (nth 2 hesaplanacak)))				;; ilk değeri iç içe bir expression ise buraya girer
						(progn
							(setq kontrol-c (char (nth 2 hesaplanacak) 0))
							(loop for index from 1 below (length input)

							      for char = (char input index)
							      until (char= char kontrol-c)
							      finally (when (char= char kontrol-c)
									(progn
										(setq yeni-input1 (subseq input 0 index))
										(loop for index1 from ( - (length input) 2 ) downto 1
										      for char = (char input index1)
										      until (char= char #\))
										      finally (when (char= char #\) )
												(progn
												(setq ilk-cp index1)	
												)									
											)
										)
										(setq yeni-input2 (subseq input ( + 1 ilk-cp) (length input) ))
										(setq yerine-koy (evaluate (subseq input index ( + 1 ilk-cp) ) ))

										(setq yeni-valuef (make-valuef yerine-koy))
										(setq result (concatenate 'string yeni-input1 yeni-valuef  yeni-input2 ))
										(setq sonuc (evaluate result))
									)									
								)
								(incf index)					
							)
						)
						(progn
							(if (= -1 (is-valuef (nth 3 hesaplanacak)))				;; ikinci değeri iç içe expression ise buraya grer
								(progn
									(setq kontrol-c (char (nth 3 hesaplanacak) 0))
									(loop for index from 1 below (length input)
									      for char = (char input index)
									      until (char= char kontrol-c)
									      finally (when (char= char kontrol-c)
											(progn
												(setq yerine-koy (evaluate (subseq input index (- (length input) 2) )))
												(setq yeni-input1 (subseq input 0 index))
												(setq yeni-input2 (subseq input (- (length input) 1)))
												(setq yeni-valuef (make-valuef yerine-koy))
												(setq result (concatenate 'string yeni-input1 yeni-valuef " " yeni-input2 ))
												(setq sonuc (evaluate result))
											)									
										)
										(incf index)					
									)
								)
								(progn
									(setq sonuc (calculate hesaplanacak))			;; düz expressionlar buraya girer
								)	
							)
						)
					)
				)
			)
		)
		(progn
			(format t "~%Syntax Error: ~%")	
			(setq sonuc (list -1 0))
		)
	)
	sonuc
	)
)

(defun calculate(input)
	(let((result 0) )
		(setq op (nth 1 input))
		(cond
			((equal op "+") (f-topla (nth 2 input) (nth 3 input))) 
			((equal op "-") (f-cikart (nth 2 input) (nth 3 input) ) )
			((equal op "*") (f-carp (nth 2 input) (nth 3 input)) ) 
			((equal op "/") (f-bol (nth 2 input) (nth 3 input)) ) 		
		)
	)
)

(defun f-topla (first second)
	
	(let ( (first-values (create-valuef first)) (second-values (create-valuef second))  (num 0 ) (denum 0 ))
		(setq first-num  (nth 0 first-values))
		(setq first-denum  (nth 1 first-values))
		(setq second-num (nth 0 second-values))
		(setq second-denum  (nth 1 second-values))
		(setq num (+ (* first-num second-denum) (* first-denum second-num) ) )	
		(setq denum (* first-denum second-denum))
	(list num denum)
	)
)

(defun f-cikart (first second)
	(let ( (first-values (create-valuef first)) (second-values (create-valuef second))  (num 0 ) (denum 0 ))
		(setq first-num  (nth 0 first-values))
		(setq first-denum  (nth 1 first-values))
		(setq second-num (nth 0 second-values))
		(setq second-denum  (nth 1 second-values))
		(setq num (- (* first-num second-denum) (* first-denum second-num) ) )	
		(setq denum (* first-denum second-denum))
	(list num denum)
	)
)
(defun f-carp (first second)
	
	(let ( (first-values (create-valuef first)) (second-values (create-valuef second))  (num 0 ) (denum 0 ))
		(setq first-num  (nth 0 first-values))
		(setq first-denum  (nth 1 first-values))
		(setq second-num (nth 0 second-values))
		(setq second-denum  (nth 1 second-values))
		(setq num (* first-num second-num)   )	
		(setq denum (* first-denum second-denum))
	(list num denum)
	)
)
(defun f-bol (first second)
	
	(let ( (first-values (create-valuef first)) (second-values (create-valuef second))  (num 0 ) (denum 0 ))
		(setq first-num  (nth 0 first-values))
		(setq first-denum  (nth 1 first-values))
		(setq second-num (nth 0 second-values))
		(setq second-denum  (nth 1 second-values))
		(setq num  (* first-num second-denum))	
		(setq denum (* first-denum second-num))
	(list num denum)
	)
)

(defun make-valuef (input)
	(let ((result "33"))
	(setq result (format nil "~Ab~A" (first input) (second input)))
	)
)

(defun start (file-path)					;; kodu baslatan main fonksıyon
	
	(if (not ( not file-path) )
		(progn
			(setq lines (read-lines file-path))
			(dolist (input-t lines)
				(format t "Received input: ~a" input-t)
				
				(if (or (equal input-t nil) (equal input-t "exit") )
					(progn
						(print "exiting ..." ) 
					(return)
					)
				)
				(if (is-FUNCTION input-t)
					(progn
						(create-function input-t)
						(format t "~%#function ~%")
					)
					(progn
						(setq sonuc (make-valuef (evaluate input-t)))
						(if (equal "-1b0" sonuc) 
							(progn
								(print "exiting ..." ) 
								(return)
							)
							(progn
								(format t "~t~t result == ~d~% "sonuc)
							)
						)
					)	
				)
			
			
			)
	 
		)
		(loop
			(format t "~%Enter input: ")
			(finish-output) 
			(let ((input-t (read-line *standard-input* nil)))
				(format t "Received input: ~a" input-t)
				
				(if (or (equal input-t nil) (equal input-t "( exit )") )
					(progn
						(print "exiting ..." ) 
					(return)
					)
				)
				(if (is-FUNCTION input-t)
					(progn
						(create-function input-t)
						(print "#function")
					)
					(progn
						(setq sonuc (make-valuef (evaluate input-t)))
						(if (equal "-1b0" sonuc) 
							(progn
								(print "exiting ..." ) 
								(return)
							)
							(progn
								(format t "~t~t result == ~d "sonuc)
							)
						)
					)	
				)
			)
		)
	)
)

  
(defun create-function (input1)						;; id ve expressionı hash-table a kaydeder

	(setq func-div (kelimelereAyir " " input1 ))
					
					(loop for index from 1 below (length input1)
					      for char = (char input1 index)
					      until (char= char #\()
					      finally (when (char= char #\()
							(progn
								(setq result (subseq input1 index (- (length input1) 2)))							
							)									
						)
						(incf index)					
					)	
	(add-to-hash-table (nth 2 func-div)  result)
)
  
(defun use-function (input)
	(make-valuef(evaluate (gethash-func input)))
)
  
(defun gethash-func (input-key)					;; fonksıyonun ıd'sine göre hangi expressiona sahipse onu donduruyor
	(let ((result nil))
		(maphash
			(lambda (key value)
			(when (equal input-key key)
				(setq result value))
		)
	*func-table*)
	result)
)

(defun is-FUNCTION (input)				;; fonksıyon yaratıyor mu kontrol ediliyor T veya nill döndürüyor
	(setq d-index 0)
	(setq d-tokens " ")
	(setq tokens " ")
	(loop for index from 1 below (length input)
	      for char = (char input index)
	      until (char= char #\()
	      finally (when (char= char #\()
			(progn
				(setq result (subseq input index (- (length input) 2)))							
				(setq tokens (lexer2 result))	
				(let((is-same nil))
					(loop :do
						(if (not is-same) 
						(progn 
							(setq tokens-t (in-exp tokens))
							(if (equal tokens-t tokens) 
								(setq is-same T)
							)	
						)
						(return)
						)
					(setq tokens tokens-t)
				))
			)	
		)
		(incf index)
		(setq d-index index)					
		(setq d-tokens tokens)
	)
	
	(if (equal tokens " ") (return-from is-FUNCTION nil))
	
	(setq st1 (subseq input 0 (- d-index 1 )))
	(setq st2 (subseq input (- (length input) 2)))

	(setq tokens (format nil "~A" tokens))
	(setq tokens (subseq tokens 1 ( - (length tokens)1)))
	(setq res-f (concatenate 'string st1 (string tokens) st2))
	(setq res-f (lexer2 res-f))	
	(let ((ret-val nil))
		(if (member res-f *FUNCTION* :test #'equal)
			(setq ret-val T)
		)
	ret-val
	)
)

(defun func-call (input)					;; fonksıyon cagrısı mı değil mi kontrol eder ve fonksyıon cagrısı ise kaçıncı tip bir çağrı olduğunu döndürür
	(let ( (ret-val -1) (pos -1) )
		(setq tokens (lexer2 input))
		(let((is-same nil))
		(loop :do
			(if (not is-same) 
			(progn 
				(if (not (equal nil (position tokens *EXP* :test #'equal)))
					(progn
						(setq pos (position tokens *EXP* :test #'equal))
					)	
				
				)
				(setq tokens-t (in-exp tokens))
				(if (equal tokens-t tokens) 
					(setq is-same T)
				)	
			)
			(return)
			)
		(setq tokens tokens-t)
		))
		pos
	)
)

(defun read-lines (&optional (file-path nil))
	(if file-path
		(with-open-file (stream file-path :direction :input)
		(loop for line = (read-line stream nil)
		      while line
		      collect line))
		;; Dosya adı verilmediyse terminalden oku
		(loop for line = (read-line *query-io* nil)
	    while line
	    collect line)))

(let ((file-path (if (not (null *args*)) (first *args*) nil)))

(start file-path))

	
	
	
