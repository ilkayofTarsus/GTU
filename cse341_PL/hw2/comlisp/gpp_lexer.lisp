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
(defparameter IDENTIFIER "[a-zA-Z][a-zA-Z0-9]+$")


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
	
	(format t "Komut Satiri girin: ")
(finish-output)

(let ((user-input (read-line)))
(lexer user-input))
	
	
	
