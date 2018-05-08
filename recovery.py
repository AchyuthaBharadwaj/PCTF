#!/usr/bin/python

import sys, os
from pwn import *
import time



if __name__ == '__main__':

	while True:	

		# service port need to adjust based on the PCTF setup
		r1=remote('localhost', 20001, timeout=1)
		if (not r1.can_recv(timeout=1)):
			print "Copy recovery file"
			# os.system('rm ~/babymarvel/ro/patched')
 			os.system('cp ~/serviceRecovery/rop_keyboard ~/rop_keyboard/ro/rop_keyboard')
			os.system('chmod 750 ~/rop_keyboard/ro/rop_keyboard')
			os.system('chown ctf:ctf_rop_keyboard ~/rop_keyboard/ro/rop_keyboard')
		r1.close()


		#configure all services
		r2=remote('localhost', 20002, timeout=1)
		if (not r2.can_recv(timeout=1)):
			print "Copy recovery file"
			# os.system('rm ~/babymarvel/ro/patched')
 			os.system('cp ~/serviceRecovery/securedb.php ~/securedb/www/securedb.php')
			os.system('chmod 750 ~/securedb/www/securedb.php')
			os.system('chown ctf:ctf_securedb ~/securedb/www/securedb.php')
		r2.close()


		r3=remote('localhost', 20003, timeout=1)
		if (not r3.can_recv(timeout=1)):
			print "Copy recovery file"
			# os.system('rm ~/babymarvel/ro/patched')
 			os.system('cp ~/serviceRecovery/backup-child ~/backup-child/ro/backup-child')
			os.system('chmod 750 ~/backup-child/ro/backup-child')
			os.system('chown ctf:ctf_backup-child ~/backup-child/ro/backup-child')
		r3.close()	
		
		
		#r4=remote('localhost', 20004) 



		time.sleep(30)
	
	
