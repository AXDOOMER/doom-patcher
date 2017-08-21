import sys
import os

# Global variables
exename = "DOOM2.EXE"
crkfile = "cracks.crk"
crkname = ""
crklist = []

# Data

class Crack:
	name = ""
	data = []

# Functions

def loadcracks():
	myfile = open(crkfile, "r")

	# Move forward until a blank line (reading the file's title and blah blah)
	while myfile.readline().strip():
		continue

	# Load a crack
	crk = Crack()
	line = myfile.readline().strip()
	crk.name = line
	count = 0

	while line:
		line = myfile.readline().strip()
		# Check line empty
		if not line:
			break
		#print("check " + line.upper())
		if line.upper().find("EXE") > -1:
			continue	# Skip line, add checks later
		crk.data.append([])
		crk.data[count].append(line.split(' '))
		try:
#			crk.data[count][0][0].translate(None, ":")
			crk.data[count][0][0] = crk.data[count][0][0][0:crk.data[count][0][0].index(':')]
		except ValueError:
			print("ok")
		print(crk.data[count])
		count += 1
	#Empty line reached

	# Read the rest...
#	line = "1";
#	while line:
#		line = myfile.readline()
#		print(line.strip())

	return

def patchfile(filename, patchname):
	print("function 'patchfile'")
	f = open(exename, "r+b") # open in read/write binary
	f.seek(0x16A7) # seek to the previously found offset
	f.write(bytearray([0xEB])) # patch the jump
	f.close()
	return

def patchjob(filename, patchname):
	print("function 'patchfile'")
	return

def filesize(filename):
	st = os.stat(filename)
	return st.st_size
	#os.path.getsize(filename)

def main(argv):
	try:
		f = open(crkfile, "r")
		print(f.readline().strip())	#Hacks for Doom2 v1.9
		f.close()
		loadcracks()
	except (OSError, IOError) as e:
		print(str(e))
	pass

if __name__ == "__main__":
	main(sys.argv)
