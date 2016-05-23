import random
import sys
import time

#---------------------------------------
# MODIFY THESE VALUES:

# Number of checks to generate 
count = 12000000

# Output file name
fileName = 'test11-12000000.txt'
#---------------------------------------

bid = []
aid = []
chk = []

print 'Generating checks'
start = time.time()

for i in range(0,count):
	
	if count > 10000:
		if i == int(count/4):
			print '25% of checks generated'
			clock = time.time() - start
			print 'Approx {} seconds left'.format(int(clock*3))
		elif i == int(count/2):
			print '50% of checks generated'
			clock = time.time() - start
			print 'Approx {} seconds left'.format(int(clock))
		elif i == int(count - (count/4)):
			print '75% of checks generated'
			clock = time.time() - start
			print 'Approx {} seconds left'.format(int(clock/3))
		elif i == int(count - (count/10)):
			print '90% of checks generate'
			clock = time.time() - start
			print 'Approx {} seconds left'.format(int(clock/9))
	
	#BANK ID NUMBER
	num = ''
	digits = int(random.random()*8)+1
	leadZeros = True
	newDigit = 0
	for j in range (0,digits):
		if leadZeros:
			newDigit = int(random.random()*8)+1
			leadZeros = False
		else:
			newDigit = int(random.random()*9.9)
		num = num + str(newDigit)
	bid.append(num)	
	
	#ACCOUNT ID NUMBER
	num = ''
	digits = int(random.random()*8)+1
	leadZeros = True
	newDigit = 0
	for j in range (0,digits):
		if leadZeros:
			newDigit = int(random.random()*8)+1
			leadZeros = False
		else:
			newDigit = int(random.random()*9.9)
		num = num + str(newDigit)
	aid.append(num)
	
	#CHECK NUMBER
	num = ''
	digits = 3
	leadZeros = True
	newDigit = 0
	for j in range (0,digits):
		if leadZeros:
			newDigit = int(random.random()*8)+1
			leadZeros = False
		else:
			newDigit = int(random.random()*9.9)
		num = num + str(newDigit)
	chk.append(num)

print 'Check data generated'
print 'Writing check data to file now'
	
# PRINT OUT DATA TO FILE	
f = open(fileName, 'w')
for i in range(0,count):
	f.write(bid[i]+' '+aid[i]+' '+chk[i]+'\n');
	
	if count > 10000:
		if i == int(count/4):
			print '25% of data written to file'
		elif i == int(count/2):
			print '50% of data written to file'
		elif i == int(count - (count/4)):
			print '75% of data written to file'
		elif i == int(count - (count/10)):
			print '90% of data written to file'