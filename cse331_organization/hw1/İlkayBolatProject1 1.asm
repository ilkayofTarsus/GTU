.data
    sizeX: .asciiz "X ekseni boyutunu girin: "
    sizeY: .asciiz "Y ekseni boyutunu girin: "
    bombaInputIste: .asciiz "Bombalı haritayı tek satırda girin:\n"
    totalSize: .space 10	# total sizeın kaydedileceği buffer
    newline: .asciiz "\n"	#newline bufferı
    input_buffer:   .space  64  #tek satırda alınacak harita bufferı
    char_bomba: .asciiz "B"	#!!!!!!!!!!!!!!!!!!!!!!! Bombanın temsil edildiği char !!!!!!!!!!!!!!!!!!
    loopIste: .asciiz "Döngü sayısını girin\n"

.text
	.globl main
	
    main:
        # Kullanıcıdan X ekseni boyutunu al
        li $v0, 4          # print_str için syscall numarası
        la $a0, sizeX      # prompt'u ekrana yazdır
        syscall
	li $v0, 5           # read_int için syscall numarası
        syscall
        move $s0, $v0		# s0 = x_boyut
	
	# Kullanıcıdan X ekseni boyutunu al
	li $v0, 4	#prompt yazdırma kodu
	la $a0, sizeY 	#prompt kaydedildi
	syscall 	#syscall
        li $v0, 5	# read_int için syscall numarası
        syscall		#syscall
        move $s1, $v0	# s1 = y_boyut

	# Toplam eleman sayısını hesapla (rows * columns)
        mul $s3, $s0, $s1	#s3 =  totalSize
        
	jal create_matrix	#  bu iki fonksiyon beraber c kodumdaki
	jal generateMap		#  generateMap fonksiyonunu implement ediyor. harita oluşturup * basıyor	
	jal takeInput
	jal create_sayac_matrix	#  bu iki fonksiyon beraber c kodumdaki
	jal generateSayacMap	#  generateSayacMap fonksiyonunu implement ediyor. sayac haritası oluşturup 9 kaydediyor
	jal bombaSayac
	
	li $v0, 4		# prompt yazdırma kodu
	la $a0, loopIste 	# kaçıncı döngüdeki harita isteniyor bulmak için input alma 		
	syscall			#syscall
	li $v0, 5		# integer okuma kodu
        syscall			#syscall
        move $a3, $v0		# döngü sayısı a3 e kaydedildi
	
	add $a2, $zero, $zero
	mainLoop:beq  $a2, $a3, end_mainLoop
		jal sayacSay		# bombaların sayacını azaltacak olan subroutin
		jal printStarMap	# haritanın mevcut durumunu bastıran subroutin
		jal plantBombs		# bomba olmayan yerlere bomba koyan subroutin
		jal bombaSayac		# yeni koyulan bombaların sayacını başlatan subroutin
		addi $a2, $a2, 1 # döngü sayısı arttırıldı
		j mainLoop
	end_mainLoop:		# Çıkış yap
        li $v0, 10      	# exit için syscall numarası
        syscall

printStarMap:
        # Yıldız haritasını bastıran fonksiyon
        # Argüman: $t0 = kullanıcının girdiği sayı (boyut)
	move $t3, $s2		# char mapi t3 pointerına kaydedildi
        li $t1, 0           # Döngü değişkeni: satır sayısı
    outer_loop: 
        bge $t1, $s1, outer_done   # Satır sayısı boyunca döngü
        li $t2, 0           # Döngü değişkeni: sütun sayısı
    inner_loop:
        bge $t2, $s0, inner_done   # Sütun sayısı boyunca döngü
        li $v0, 11          # print_char için syscall numarası
        lb $t4, 0($t3)         # '*' karakterini yazdır
        move $a0, $t4		# karakter yazdırmak için a0 registerı kullanıldı
        syscall			#syscall
        addi $t2, $t2, 1    # Sütun sayısını artır
        addi $t3, $t3, 1    # pointer kaydırıldı
        j inner_loop
    inner_done:
        li $v0, 4           # print_str için syscall numarası
        la $a0, newline     # Yeni satıra geç
        syscall		    #syscall
        addi $t1, $t1, 1    # Satır sayısını artır
        j outer_loop
    outer_done:
    	li $v0, 4           # print_str için syscall numarası
        la $a0, newline     # Yeni satıra geç
        syscall		    #syscall
        li $v0, 4           # print_str için syscall numarası
        la $a0, newline     # Yeni satıra geç
        syscall		    #syscall
        jr $ra

printSayacMap:
        # Yıldız haritasını bastıran fonksiyon
        # Argüman: $t0 = kullanıcının girdiği sayı (boyut)
	move $t3, $s4	    # sayac mapi adresi kaydedildi
        li $t1, 0           # Döngü değişkeni: satır sayısı
    outer_loop22:
        bge $t1, $s1, outer_done22   # Satır sayısı boyunca döngü
        li $t2, 0           # Döngü değişkeni: sütun sayısı
    inner_loop22:
        bge $t2, $s0, inner_done22   # Sütun sayısı boyunca döngü
        li $v0, 1          # print_int için syscall numarası
        lw $t4, 0($t3)         # '*' karakterini yazdır
        move $a0, $t4	    # t4 içeriği yazdırılacak
        syscall		    #syscall
        addi $t2, $t2, 1    # Sütun sayısını artır
        addi $t3, $t3, 4    # integer mapindeki pointer kaydırma
        j inner_loop22	
    inner_done22:
        li $v0, 4           # print_str için syscall numarası
        la $a0, newline     # Yeni satıra geç
        syscall	            #syscall
        addi $t1, $t1, 1    # Satır sayısını artır
        j outer_loop22
    outer_done22:
        jr $ra


create_matrix:

    	# Hafızada gerekli alanı ayrıla
    	li $v0, 9             # sbrk syscall (heap'ten bellek ayırma)
    	move $a0, $s3         # $a0 register'ına toplam eleman sayısını yükle
    	syscall
    	move $s2, $v0         # $s2 register'ına ayrılan bellek adresini kopyala
    
    	jr $ra               # Fonksiyondan dön
    
generateMap:
	move $t3, $s2		# char mapi t3 pointerına atandı
        li $t1, 0           # Döngü değişkeni: satır sayısı
    outer_loop1:
        bge $t1, $s1, outer_done1   # Satır sayısı boyunca döngü
        li $t2, 0           # Döngü değişkeni: sütun sayısı
    inner_loop1:
        bge $t2, $s0, inner_done1  # Sütun sayısı boyunca döngü
        li $t4, '*'	# * charı haritaya kaydedilmek üzere t4 e atandı
        sb $t4, ($t3)        # atama yapıldı
        addi $t2, $t2, 1    # Sütun sayısını artır
        addi $t3, $t3, 1    # pointer kaydırıldı
        j inner_loop1
    inner_done1:
        addi $t1, $t1, 1    # Satır sayısını artır
        j outer_loop1
    outer_done1:
        jr $ra

create_sayac_matrix:
	move $t0, $s0         # $t0 register'ına satır sayısını kopyala
	move $t1, $s1         # $t1 register'ına sütun sayısını kopyala
	li $t3, 4		# integer mapı oluşturmak için gereken alan
	mul $t2, $s3, $t3	# gereken alan hesaplandı
    	# Hafızada gerekli alanı ayrıla
    	li $v0, 9             # sbrk syscall (heap'ten bellek ayırma)
    	move $a0, $t2         # $a0 register'ına toplam eleman sayısını yükle
    	syscall			#syscall
    	move $s4, $v0         # $s4 register'ına ayrılan bellek adresini kopyala
    
    	jr $ra               # Fonksiyondan dön
generateSayacMap:
	move $t3, $s4
        li $t1, 0           # Döngü değişkeni: satır sayısı
    outer_loop11:
        bge $t1, $s1, outer_done11   # Satır sayısı boyunca döngü
        li $t2, 0           # Döngü değişkeni: sütun sayısı
    inner_loop11:
        bge $t2, $s0, inner_done11  # Sütun sayısı boyunca döngü
        addi $t4, $zero, 9
        sb $t4, ($t3)        
        addi $t2, $t2, 1    # Sütun sayısını artır
        addi $t3, $t3, 4
        j inner_loop11
    inner_done11:
        addi $t1, $t1, 1    # Satır sayısını artır
        j outer_loop11
    outer_done11:
        jr $ra
 


takeInput:
	li $v0, 4           # print_str için syscall numarası
        la $a0, bombaInputIste      # prompt'u ekrana yazdır
        syscall
	
	li $v0, 8                # 8 numaralı syscall: String oku
	la $a0, input_buffer     # Giriş buffer'ının adresini $a0'e yükle
	li $a1, 64               # Maksimum karakter sayısını $a1'e yükle
	syscall
	
	la $t1, ($s3)		# t1 pointerına toplam eleman sayısı atandı
	la $t4, input_buffer	#input_buffer etiketindekinin adresi kaydedildi
	la $t3, ($s2)		# t3 pointerına char mapinin adresi atandı
	add $t0, $zero, $zero
	inner_loop2:
		beq $t1, $t0, inner_done2
		lb $t5, 0($t4)		# input_bufferdaki charı t5 e kaydediyoy
		sb $t5,0($t3)		# input_bufferdan aldığı charı arraydeki mevcut indexe atıyor
				
		addi $t4, $t4, 1	# bufferda gezinen pointer
		addi $t3, $t3, 1	# haritada gezinen pointer 
		addi $t0, $t0, 1	# döngü sayısı
		j inner_loop2
	inner_done2:
		jr $ra
    
bombaSayac:
	move $t0, $s2 # haritayı t0 a attı
	move $t1, $s4 # sayac haritasını t1 a attı
	add $t3, $zero, $zero # dongu için sayac atandı
	li $t4, 9
	la $t5, char_bomba	# "B" charının adresi t5 e atandı
	lb $t6, 0($t5)		# "B" vharı t6 ya atandı
	li $t7, 3		# kontrol edebilmek amacıyla 3 değeri t7 ye atandı
	loop1:	beq $t3, $s3, end_loop1	
		lb $t2, 0($t0)		#harita pointerı vasıtasıyla mevcut değer t2 ye atandı
		bne $t2, $t6, case1	#if(map[a][b] == 'B' && sayacMap[a][b] == 9){
		lw $t2, 0($t1)		# sayac mapi pointerı vasıtasıyla mevcut sayı t2 ye kaydedildi
		bne $t2, $t4, case1	# iki eşitlik kontrolü sayesinde üstteki if kontrolü sağlandı
		sw $t7, ($t1) 		# İki tane bne'den geçtiyse char haritasındaki mevcut index B ye eşit ve aynı zamanda sayac haritasındaki indexteki değer ise 9 a eşit
		case1:
		addi $t0, $t0, 1	#sayac kontrol için arttırıldı
		addi $t1, $t1, 4	#integer mapinde bir sonraki adrese erişim için adres arttırıldı
		addi $t3, $t3, 1	#char mapinde bir sonraki adrese erişim
		j loop1
	end_loop1: jr $ra	
		
			
sayacSay:
	add $t0, $zero, $zero # sayac
	li $t1, 9
	move $t2, $s2 # haritayı t2 a attı
	move $t3, $s4 # sayac haritasını t3 a attı
	sayacLoop: beq $t0, $s3, endSayacLoop # eleman sayısına eşitse bitir
		lw $t4, 0($t3)	# t4 sayac haritasındaki indexteki mevcut sayı
		beq  $t4, $t1, sayacCase1	# sayac haritasındaki 9 olan tum registerlar esgeçildi
		subi $t4, $t4, 1	#sayacMap[a][b] = sayacMap[a][b] -1 ; // bombaların sayacı eksiltiliyor
		sw $t4, 0($t3)		# guncellenen sayac haritaya eklendı
		bnez  $t4, sayacCase1 	# bomba sayacı 0 olduysa patlatma fonksyıonuna yonlendirildi
		j patlat
		sayacCase1:
			addi $t3, $t3, 4	# int arrayi sonraki elemana geçti
			addi $t2, $t2, 1	# char arrayi sonraki elemana geçti
			addi $t0, $t0, 1	# sayac arttırıldı
		j sayacLoop
	endSayacLoop:
		jr $ra
patlat:

	li $t6, '*'	# patlatılan yerler sıfırlanıyor
        sb $t6, ($t2)	 # char haritasındaki mevcut char * yapıldı yani reset atıldı
		
	li $t6, 9	# patlatılan yerler sıfırlanıyor
	sw $t6, 0($t3) # sayac haritasındaki mevcut değer 9 yapıldı yani reset atıldı	

			#üstteki satırlar
			#map[y][x] = '*';
			#sayacMap[y][x] = 9;

	move $t5, $t0												
	div $t5, $s0 	# mevcut indexi x ekseninin boyutuna bölüp mod alıyor
	mfhi $t7	# moda göre bir önceki alanı patlatıp patlatmamaya karar verecek
	subi $t8, $s0, 1# satır sonu indeksini tutuyor
	
	#if(x > 0){
	#	map[y][x-1] = '*';
	#	sayacMap[y][x-1] = 9;
	#}
	beqz $t7, patlatCase1	# t7 == 0 burdan devam etme (t7 bir sonraki moda kadar x ekseninde kaçıncı index onu tutuyor)
	subi $t2, $t2, 1	
	li $t6, '*'		#t6 = *
	sb $t6, ($t2)	 	# char haritasındaki mevcut char * yapıldı yani reset atıldı
	addi $t2, $t2, 1	# t2 indeksi tekrar eski yerine getirildi
	
	subi $t3, $t3, 4	# pointer bir önceki adrese kaydı	
	li $t6, 9		# 9 atılarak * olduğu belli edildi
	sw $t6, 0($t3)	 	# sayac haritasındaki mevcut değer 9 yapıldı yani reset atıldı
	addi $t3, $t3, 4	# t3 indeksi tekrar eski yerine getirildi
	
	patlatCase1:
	#if(x < sizeX-1){
	#	if(sayacMap[y][x+1] != 1){
	#		map[y][x+1] = '*';
	#		sayacMap[y][x+1] = 9;
	#	}
	#}
	
	beq $t7, $t8, patlatCase2# t7 == t8 burdan devam etme (t8 son index)

	addi $t3, $t3, 4	 	# pointer bir sonraki adrese kaydırıldı
	lw $t6, 0($t3)			# t6 = *t3
	li $t9, 1			# t9 = 1
	beq $t6, $t9, bombaKontrol	#bombaKontrol etiketi sayesinde o tur patlayacak başka bombayı engelleme işi çözülüyor
	li $t6, 9		# 9 atılarak * olduğu belli edildi
	sw $t6, 0($t3)	 	# sayac haritasındaki mevcut değer 9 yapıldı yani reset atıldı
	

	addi $t2, $t2, 1	# pointer bir sonraki adrese kaydırıldı
	li $t6, '*'		#t6 = '*'
	sb $t6, ($t2)	 	# char haritasındaki mevcut char * yapıldı yani reset atıldı
	subi $t2, $t2, 1	# t2 indeksi tekrar eski yerine getirildi
	

	
	bombaKontrol:
	subi $t3, $t3, 4	# t3 indeksi tekrar eski yerine getirildi
	patlatCase2:
	add $t7, $zero, $zero	# y eksenindeki kontroller için t7 sıfırlandı
	move $t5, $t0		# t5 tekrardan t0 a atandı.Garanti olsun diye
	div $t7, $t5, $s0 	# x ekseninin boyutuna bölüp sonucu kaydediyor t7 = t5/s0
				# sonuca göre yukatı indexi patlatıp patlatmamaya karar verecek
	subi $t8, $s1, 1# sütun sonu indeksini tutuyor
	
	
	#if(y > 0){
	#	map[y-1][x] = '*';
	#	sayacMap[y-1][x] = 9;
	#}
	beqz $t7, patlatCase3	# t7 == 0 burdan devam  etme (t7 y ekseninde kaçıncı index onu tutuyor)
	mul $t9, $s0, 4		# 2 boyutlu düşündülünce bir alt adrese erişmek için x ekseni kadar sonraya gitmek için t9 atandı
	sub $t3, $t3, $t9	# y+1 deki indexe erişim
	li $t6, 9		# 9 atılarak * olduğu belli edildi
	sw $t6, 0($t3)	 	# sayac haritasındaki mevcut değer 9 yapıldı yani reset atıldı
	add $t3, $t3, $t9	# pointer eski yerine getirildi
	
	sub $t2, $t2, $s0	# 2 boyutlu düşündülünce bir alt adrese erişmek için x ekseni kadar sonraya gitmek için t9 atandı
	li $t6, '*'
	sb $t6, ($t2)	 	# char haritasındaki mevcut char * yapıldı yani reset atıldı
	add $t2, $t2, $s0	# pointer eski yerine getirildi

	patlatCase3:
	
	#if(y < sizeY-1){
	#	if(sayacMap[y+1][x] != 1){
	#		map[y+1][x] = '*';
	#		sayacMap[y+1][x] = 9;
	#	}
	#}
	beq $t7, $t8, patlatCase4# t7 == t8 burdan devam etme(t8 son index)
	mul $t9, $s0, 4		 # t9 a x ekseninin boyutunun 4 katı atandı. tek boyutlu haritayı 2 boyutlu düşünebilmek için
	add $t3, $t3, $t9	 # pointer bir aşağı adrese kaydırıldı
	
	lw $t6, 0($t3)			#bir alttaki bomba bu tur patlayacaksa onu ellememesi için bir kontrol
	li $s7, 1			# sonraki bomba bu tur patlayacak mı		
	beq $t6, $s7, bombaKontrol2	#patlayacak olan bombadan gelen sonra bu tur patlayacak olan bomba varsa esgeçildi
	li $t6, 9		# 9 atılarak * olduğu belli edildi
	sw $t6, 0($t3)	 	# sayac haritasındaki mevcut değer 9 yapıldı yani reset atıldı
	add $t2, $t2, $s0	# pointer y+1 indexteki elemana erişmek için x ekseni boyutu kadar ilerledi
	li $t6, '*'		# char'ı mape kaydedebilmek için t6 registerına "*" kaydedildi
	sb $t6, ($t2)	 	# char haritasındaki mevcut char * yapıldı yani reset atıldı
	sub $t2, $t2, $s0	# pointer eski yerine getirildi
	bombaKontrol2:
	sub $t3, $t3, $t9	# pointer eski yerine getirildi	
	patlatCase4:
		j sayacCase1

plantBombs:

	li $t0, 0	# sayac
	li $t2, 'B'	#Bomba charı
	move $t3, $s2	#char arrayi t3 e kopyalandı
	move $t4, $s4	#sayac arrayi t4 e kopyalandı
	plantBombOuterLoop: beq $t0, $s1,plantBombOuterLoopDone	#for(int a=0; a < y; a++){
		li $t1, 0					# ınner loop sayacı
		plantBombInnerLoop: beq $t1, $s0 ,plantBombInnerLoopDone #for(int b=0; b < x; b++){
			lw $t5, 0($t4)			# sayac haritası pointerı ile mevcut sayı t5 e kaydedildi
			lb $t6, ($t3)			#if(map[a][b] != 'B') map[a][b] = 'B';
			beq $t2, $t6, plantCase 	#Mevcut indexte "B" içermeyen
			sb $t2, ($t3)			# her char "B" yapılıyor
			plantCase:		
			addi $t1, $t1, 1		#inner loop sayacı artırıldı
			addi $t3, $t3, 1		#pointer adresi arttırıldı
			addi $t4, $t4, 4		#integer pointerı arttırıldı
			j plantBombInnerLoop
		plantBombInnerLoopDone:
		add $t0, $t0, 1				# dış loop sayacı arttırıldı
		j plantBombOuterLoop
	plantBombOuterLoopDone:
		jr $ra
