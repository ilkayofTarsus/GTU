.data
    sizeX: .asciiz "X ekseni boyutunu girin: "
    sizeY: .asciiz "Y ekseni boyutunu girin: "
    bombaInputIste: .asciiz "Bombal� haritay� tek sat�rda girin:\n"
    totalSize: .space 10	# total size�n kaydedilece�i buffer
    newline: .asciiz "\n"	#newline buffer�
    input_buffer:   .space  64  #tek sat�rda al�nacak harita buffer�
    char_bomba: .asciiz "B"	#!!!!!!!!!!!!!!!!!!!!!!! Bomban�n temsil edildi�i char !!!!!!!!!!!!!!!!!!
    loopIste: .asciiz "D�ng� say�s�n� girin\n"

.text
	.globl main
	
    main:
        # Kullan�c�dan X ekseni boyutunu al
        li $v0, 4          # print_str i�in syscall numaras�
        la $a0, sizeX      # prompt'u ekrana yazd�r
        syscall
	li $v0, 5           # read_int i�in syscall numaras�
        syscall
        move $s0, $v0		# s0 = x_boyut
	
	# Kullan�c�dan X ekseni boyutunu al
	li $v0, 4	#prompt yazd�rma kodu
	la $a0, sizeY 	#prompt kaydedildi
	syscall 	#syscall
        li $v0, 5	# read_int i�in syscall numaras�
        syscall		#syscall
        move $s1, $v0	# s1 = y_boyut

	# Toplam eleman say�s�n� hesapla (rows * columns)
        mul $s3, $s0, $s1	#s3 =  totalSize
        
	jal create_matrix	#  bu iki fonksiyon beraber c kodumdaki
	jal generateMap		#  generateMap fonksiyonunu implement ediyor. harita olu�turup * bas�yor	
	jal takeInput
	jal create_sayac_matrix	#  bu iki fonksiyon beraber c kodumdaki
	jal generateSayacMap	#  generateSayacMap fonksiyonunu implement ediyor. sayac haritas� olu�turup 9 kaydediyor
	jal bombaSayac
	
	li $v0, 4		# prompt yazd�rma kodu
	la $a0, loopIste 	# ka��nc� d�ng�deki harita isteniyor bulmak i�in input alma 		
	syscall			#syscall
	li $v0, 5		# integer okuma kodu
        syscall			#syscall
        move $a3, $v0		# d�ng� say�s� a3 e kaydedildi
	
	add $a2, $zero, $zero
	mainLoop:beq  $a2, $a3, end_mainLoop
		jal sayacSay		# bombalar�n sayac�n� azaltacak olan subroutin
		jal printStarMap	# haritan�n mevcut durumunu bast�ran subroutin
		jal plantBombs		# bomba olmayan yerlere bomba koyan subroutin
		jal bombaSayac		# yeni koyulan bombalar�n sayac�n� ba�latan subroutin
		addi $a2, $a2, 1 # d�ng� say�s� artt�r�ld�
		j mainLoop
	end_mainLoop:		# ��k�� yap
        li $v0, 10      	# exit i�in syscall numaras�
        syscall

printStarMap:
        # Y�ld�z haritas�n� bast�ran fonksiyon
        # Arg�man: $t0 = kullan�c�n�n girdi�i say� (boyut)
	move $t3, $s2		# char mapi t3 pointer�na kaydedildi
        li $t1, 0           # D�ng� de�i�keni: sat�r say�s�
    outer_loop: 
        bge $t1, $s1, outer_done   # Sat�r say�s� boyunca d�ng�
        li $t2, 0           # D�ng� de�i�keni: s�tun say�s�
    inner_loop:
        bge $t2, $s0, inner_done   # S�tun say�s� boyunca d�ng�
        li $v0, 11          # print_char i�in syscall numaras�
        lb $t4, 0($t3)         # '*' karakterini yazd�r
        move $a0, $t4		# karakter yazd�rmak i�in a0 register� kullan�ld�
        syscall			#syscall
        addi $t2, $t2, 1    # S�tun say�s�n� art�r
        addi $t3, $t3, 1    # pointer kayd�r�ld�
        j inner_loop
    inner_done:
        li $v0, 4           # print_str i�in syscall numaras�
        la $a0, newline     # Yeni sat�ra ge�
        syscall		    #syscall
        addi $t1, $t1, 1    # Sat�r say�s�n� art�r
        j outer_loop
    outer_done:
    	li $v0, 4           # print_str i�in syscall numaras�
        la $a0, newline     # Yeni sat�ra ge�
        syscall		    #syscall
        li $v0, 4           # print_str i�in syscall numaras�
        la $a0, newline     # Yeni sat�ra ge�
        syscall		    #syscall
        jr $ra

printSayacMap:
        # Y�ld�z haritas�n� bast�ran fonksiyon
        # Arg�man: $t0 = kullan�c�n�n girdi�i say� (boyut)
	move $t3, $s4	    # sayac mapi adresi kaydedildi
        li $t1, 0           # D�ng� de�i�keni: sat�r say�s�
    outer_loop22:
        bge $t1, $s1, outer_done22   # Sat�r say�s� boyunca d�ng�
        li $t2, 0           # D�ng� de�i�keni: s�tun say�s�
    inner_loop22:
        bge $t2, $s0, inner_done22   # S�tun say�s� boyunca d�ng�
        li $v0, 1          # print_int i�in syscall numaras�
        lw $t4, 0($t3)         # '*' karakterini yazd�r
        move $a0, $t4	    # t4 i�eri�i yazd�r�lacak
        syscall		    #syscall
        addi $t2, $t2, 1    # S�tun say�s�n� art�r
        addi $t3, $t3, 4    # integer mapindeki pointer kayd�rma
        j inner_loop22	
    inner_done22:
        li $v0, 4           # print_str i�in syscall numaras�
        la $a0, newline     # Yeni sat�ra ge�
        syscall	            #syscall
        addi $t1, $t1, 1    # Sat�r say�s�n� art�r
        j outer_loop22
    outer_done22:
        jr $ra


create_matrix:

    	# Haf�zada gerekli alan� ayr�la
    	li $v0, 9             # sbrk syscall (heap'ten bellek ay�rma)
    	move $a0, $s3         # $a0 register'�na toplam eleman say�s�n� y�kle
    	syscall
    	move $s2, $v0         # $s2 register'�na ayr�lan bellek adresini kopyala
    
    	jr $ra               # Fonksiyondan d�n
    
generateMap:
	move $t3, $s2		# char mapi t3 pointer�na atand�
        li $t1, 0           # D�ng� de�i�keni: sat�r say�s�
    outer_loop1:
        bge $t1, $s1, outer_done1   # Sat�r say�s� boyunca d�ng�
        li $t2, 0           # D�ng� de�i�keni: s�tun say�s�
    inner_loop1:
        bge $t2, $s0, inner_done1  # S�tun say�s� boyunca d�ng�
        li $t4, '*'	# * char� haritaya kaydedilmek �zere t4 e atand�
        sb $t4, ($t3)        # atama yap�ld�
        addi $t2, $t2, 1    # S�tun say�s�n� art�r
        addi $t3, $t3, 1    # pointer kayd�r�ld�
        j inner_loop1
    inner_done1:
        addi $t1, $t1, 1    # Sat�r say�s�n� art�r
        j outer_loop1
    outer_done1:
        jr $ra

create_sayac_matrix:
	move $t0, $s0         # $t0 register'�na sat�r say�s�n� kopyala
	move $t1, $s1         # $t1 register'�na s�tun say�s�n� kopyala
	li $t3, 4		# integer map� olu�turmak i�in gereken alan
	mul $t2, $s3, $t3	# gereken alan hesapland�
    	# Haf�zada gerekli alan� ayr�la
    	li $v0, 9             # sbrk syscall (heap'ten bellek ay�rma)
    	move $a0, $t2         # $a0 register'�na toplam eleman say�s�n� y�kle
    	syscall			#syscall
    	move $s4, $v0         # $s4 register'�na ayr�lan bellek adresini kopyala
    
    	jr $ra               # Fonksiyondan d�n
generateSayacMap:
	move $t3, $s4
        li $t1, 0           # D�ng� de�i�keni: sat�r say�s�
    outer_loop11:
        bge $t1, $s1, outer_done11   # Sat�r say�s� boyunca d�ng�
        li $t2, 0           # D�ng� de�i�keni: s�tun say�s�
    inner_loop11:
        bge $t2, $s0, inner_done11  # S�tun say�s� boyunca d�ng�
        addi $t4, $zero, 9
        sb $t4, ($t3)        
        addi $t2, $t2, 1    # S�tun say�s�n� art�r
        addi $t3, $t3, 4
        j inner_loop11
    inner_done11:
        addi $t1, $t1, 1    # Sat�r say�s�n� art�r
        j outer_loop11
    outer_done11:
        jr $ra
 


takeInput:
	li $v0, 4           # print_str i�in syscall numaras�
        la $a0, bombaInputIste      # prompt'u ekrana yazd�r
        syscall
	
	li $v0, 8                # 8 numaral� syscall: String oku
	la $a0, input_buffer     # Giri� buffer'�n�n adresini $a0'e y�kle
	li $a1, 64               # Maksimum karakter say�s�n� $a1'e y�kle
	syscall
	
	la $t1, ($s3)		# t1 pointer�na toplam eleman say�s� atand�
	la $t4, input_buffer	#input_buffer etiketindekinin adresi kaydedildi
	la $t3, ($s2)		# t3 pointer�na char mapinin adresi atand�
	add $t0, $zero, $zero
	inner_loop2:
		beq $t1, $t0, inner_done2
		lb $t5, 0($t4)		# input_bufferdaki char� t5 e kaydediyoy
		sb $t5,0($t3)		# input_bufferdan ald��� char� arraydeki mevcut indexe at�yor
				
		addi $t4, $t4, 1	# bufferda gezinen pointer
		addi $t3, $t3, 1	# haritada gezinen pointer 
		addi $t0, $t0, 1	# d�ng� say�s�
		j inner_loop2
	inner_done2:
		jr $ra
    
bombaSayac:
	move $t0, $s2 # haritay� t0 a att�
	move $t1, $s4 # sayac haritas�n� t1 a att�
	add $t3, $zero, $zero # dongu i�in sayac atand�
	li $t4, 9
	la $t5, char_bomba	# "B" char�n�n adresi t5 e atand�
	lb $t6, 0($t5)		# "B" vhar� t6 ya atand�
	li $t7, 3		# kontrol edebilmek amac�yla 3 de�eri t7 ye atand�
	loop1:	beq $t3, $s3, end_loop1	
		lb $t2, 0($t0)		#harita pointer� vas�tas�yla mevcut de�er t2 ye atand�
		bne $t2, $t6, case1	#if(map[a][b] == 'B' && sayacMap[a][b] == 9){
		lw $t2, 0($t1)		# sayac mapi pointer� vas�tas�yla mevcut say� t2 ye kaydedildi
		bne $t2, $t4, case1	# iki e�itlik kontrol� sayesinde �stteki if kontrol� sa�land�
		sw $t7, ($t1) 		# �ki tane bne'den ge�tiyse char haritas�ndaki mevcut index B ye e�it ve ayn� zamanda sayac haritas�ndaki indexteki de�er ise 9 a e�it
		case1:
		addi $t0, $t0, 1	#sayac kontrol i�in artt�r�ld�
		addi $t1, $t1, 4	#integer mapinde bir sonraki adrese eri�im i�in adres artt�r�ld�
		addi $t3, $t3, 1	#char mapinde bir sonraki adrese eri�im
		j loop1
	end_loop1: jr $ra	
		
			
sayacSay:
	add $t0, $zero, $zero # sayac
	li $t1, 9
	move $t2, $s2 # haritay� t2 a att�
	move $t3, $s4 # sayac haritas�n� t3 a att�
	sayacLoop: beq $t0, $s3, endSayacLoop # eleman say�s�na e�itse bitir
		lw $t4, 0($t3)	# t4 sayac haritas�ndaki indexteki mevcut say�
		beq  $t4, $t1, sayacCase1	# sayac haritas�ndaki 9 olan tum registerlar esge�ildi
		subi $t4, $t4, 1	#sayacMap[a][b] = sayacMap[a][b] -1 ; // bombalar�n sayac� eksiltiliyor
		sw $t4, 0($t3)		# guncellenen sayac haritaya eklend�
		bnez  $t4, sayacCase1 	# bomba sayac� 0 olduysa patlatma fonksy�onuna yonlendirildi
		j patlat
		sayacCase1:
			addi $t3, $t3, 4	# int arrayi sonraki elemana ge�ti
			addi $t2, $t2, 1	# char arrayi sonraki elemana ge�ti
			addi $t0, $t0, 1	# sayac artt�r�ld�
		j sayacLoop
	endSayacLoop:
		jr $ra
patlat:

	li $t6, '*'	# patlat�lan yerler s�f�rlan�yor
        sb $t6, ($t2)	 # char haritas�ndaki mevcut char * yap�ld� yani reset at�ld�
		
	li $t6, 9	# patlat�lan yerler s�f�rlan�yor
	sw $t6, 0($t3) # sayac haritas�ndaki mevcut de�er 9 yap�ld� yani reset at�ld�	

			#�stteki sat�rlar
			#map[y][x] = '*';
			#sayacMap[y][x] = 9;

	move $t5, $t0												
	div $t5, $s0 	# mevcut indexi x ekseninin boyutuna b�l�p mod al�yor
	mfhi $t7	# moda g�re bir �nceki alan� patlat�p patlatmamaya karar verecek
	subi $t8, $s0, 1# sat�r sonu indeksini tutuyor
	
	#if(x > 0){
	#	map[y][x-1] = '*';
	#	sayacMap[y][x-1] = 9;
	#}
	beqz $t7, patlatCase1	# t7 == 0 burdan devam etme (t7 bir sonraki moda kadar x ekseninde ka��nc� index onu tutuyor)
	subi $t2, $t2, 1	
	li $t6, '*'		#t6 = *
	sb $t6, ($t2)	 	# char haritas�ndaki mevcut char * yap�ld� yani reset at�ld�
	addi $t2, $t2, 1	# t2 indeksi tekrar eski yerine getirildi
	
	subi $t3, $t3, 4	# pointer bir �nceki adrese kayd�	
	li $t6, 9		# 9 at�larak * oldu�u belli edildi
	sw $t6, 0($t3)	 	# sayac haritas�ndaki mevcut de�er 9 yap�ld� yani reset at�ld�
	addi $t3, $t3, 4	# t3 indeksi tekrar eski yerine getirildi
	
	patlatCase1:
	#if(x < sizeX-1){
	#	if(sayacMap[y][x+1] != 1){
	#		map[y][x+1] = '*';
	#		sayacMap[y][x+1] = 9;
	#	}
	#}
	
	beq $t7, $t8, patlatCase2# t7 == t8 burdan devam etme (t8 son index)

	addi $t3, $t3, 4	 	# pointer bir sonraki adrese kayd�r�ld�
	lw $t6, 0($t3)			# t6 = *t3
	li $t9, 1			# t9 = 1
	beq $t6, $t9, bombaKontrol	#bombaKontrol etiketi sayesinde o tur patlayacak ba�ka bombay� engelleme i�i ��z�l�yor
	li $t6, 9		# 9 at�larak * oldu�u belli edildi
	sw $t6, 0($t3)	 	# sayac haritas�ndaki mevcut de�er 9 yap�ld� yani reset at�ld�
	

	addi $t2, $t2, 1	# pointer bir sonraki adrese kayd�r�ld�
	li $t6, '*'		#t6 = '*'
	sb $t6, ($t2)	 	# char haritas�ndaki mevcut char * yap�ld� yani reset at�ld�
	subi $t2, $t2, 1	# t2 indeksi tekrar eski yerine getirildi
	

	
	bombaKontrol:
	subi $t3, $t3, 4	# t3 indeksi tekrar eski yerine getirildi
	patlatCase2:
	add $t7, $zero, $zero	# y eksenindeki kontroller i�in t7 s�f�rland�
	move $t5, $t0		# t5 tekrardan t0 a atand�.Garanti olsun diye
	div $t7, $t5, $s0 	# x ekseninin boyutuna b�l�p sonucu kaydediyor t7 = t5/s0
				# sonuca g�re yukat� indexi patlat�p patlatmamaya karar verecek
	subi $t8, $s1, 1# s�tun sonu indeksini tutuyor
	
	
	#if(y > 0){
	#	map[y-1][x] = '*';
	#	sayacMap[y-1][x] = 9;
	#}
	beqz $t7, patlatCase3	# t7 == 0 burdan devam  etme (t7 y ekseninde ka��nc� index onu tutuyor)
	mul $t9, $s0, 4		# 2 boyutlu d���nd�l�nce bir alt adrese eri�mek i�in x ekseni kadar sonraya gitmek i�in t9 atand�
	sub $t3, $t3, $t9	# y+1 deki indexe eri�im
	li $t6, 9		# 9 at�larak * oldu�u belli edildi
	sw $t6, 0($t3)	 	# sayac haritas�ndaki mevcut de�er 9 yap�ld� yani reset at�ld�
	add $t3, $t3, $t9	# pointer eski yerine getirildi
	
	sub $t2, $t2, $s0	# 2 boyutlu d���nd�l�nce bir alt adrese eri�mek i�in x ekseni kadar sonraya gitmek i�in t9 atand�
	li $t6, '*'
	sb $t6, ($t2)	 	# char haritas�ndaki mevcut char * yap�ld� yani reset at�ld�
	add $t2, $t2, $s0	# pointer eski yerine getirildi

	patlatCase3:
	
	#if(y < sizeY-1){
	#	if(sayacMap[y+1][x] != 1){
	#		map[y+1][x] = '*';
	#		sayacMap[y+1][x] = 9;
	#	}
	#}
	beq $t7, $t8, patlatCase4# t7 == t8 burdan devam etme(t8 son index)
	mul $t9, $s0, 4		 # t9 a x ekseninin boyutunun 4 kat� atand�. tek boyutlu haritay� 2 boyutlu d���nebilmek i�in
	add $t3, $t3, $t9	 # pointer bir a�a�� adrese kayd�r�ld�
	
	lw $t6, 0($t3)			#bir alttaki bomba bu tur patlayacaksa onu ellememesi i�in bir kontrol
	li $s7, 1			# sonraki bomba bu tur patlayacak m�		
	beq $t6, $s7, bombaKontrol2	#patlayacak olan bombadan gelen sonra bu tur patlayacak olan bomba varsa esge�ildi
	li $t6, 9		# 9 at�larak * oldu�u belli edildi
	sw $t6, 0($t3)	 	# sayac haritas�ndaki mevcut de�er 9 yap�ld� yani reset at�ld�
	add $t2, $t2, $s0	# pointer y+1 indexteki elemana eri�mek i�in x ekseni boyutu kadar ilerledi
	li $t6, '*'		# char'� mape kaydedebilmek i�in t6 register�na "*" kaydedildi
	sb $t6, ($t2)	 	# char haritas�ndaki mevcut char * yap�ld� yani reset at�ld�
	sub $t2, $t2, $s0	# pointer eski yerine getirildi
	bombaKontrol2:
	sub $t3, $t3, $t9	# pointer eski yerine getirildi	
	patlatCase4:
		j sayacCase1

plantBombs:

	li $t0, 0	# sayac
	li $t2, 'B'	#Bomba char�
	move $t3, $s2	#char arrayi t3 e kopyaland�
	move $t4, $s4	#sayac arrayi t4 e kopyaland�
	plantBombOuterLoop: beq $t0, $s1,plantBombOuterLoopDone	#for(int a=0; a < y; a++){
		li $t1, 0					# �nner loop sayac�
		plantBombInnerLoop: beq $t1, $s0 ,plantBombInnerLoopDone #for(int b=0; b < x; b++){
			lw $t5, 0($t4)			# sayac haritas� pointer� ile mevcut say� t5 e kaydedildi
			lb $t6, ($t3)			#if(map[a][b] != 'B') map[a][b] = 'B';
			beq $t2, $t6, plantCase 	#Mevcut indexte "B" i�ermeyen
			sb $t2, ($t3)			# her char "B" yap�l�yor
			plantCase:		
			addi $t1, $t1, 1		#inner loop sayac� art�r�ld�
			addi $t3, $t3, 1		#pointer adresi artt�r�ld�
			addi $t4, $t4, 4		#integer pointer� artt�r�ld�
			j plantBombInnerLoop
		plantBombInnerLoopDone:
		add $t0, $t0, 1				# d�� loop sayac� artt�r�ld�
		j plantBombOuterLoop
	plantBombOuterLoopDone:
		jr $ra
