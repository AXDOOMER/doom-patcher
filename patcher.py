#### Alexandre-Xavier labonte-Lamoureux

# Imports
import sys
import os

# Patches
SENS = [
	[0x00064972, 0x0A, 0x11],
	[0x00064C8F, 0x09, 0x7F],
	[0x00064E14, 0x8D, 0x66],
	[0x00064E15, 0x34, 0x81],
	[0x00064E16, 0xF5, 0xFD],
	[0x00064E17, 0x00, 0x85],
	[0x00064E19, 0x00, 0x75],
	[0x00064E1A, 0x00, 0x4F],
	[0x00064E6B, 0x80, 0x34],
	[0x00064E6C, 0x00, 0xF5],
	[0x00064E70, 0x8D, 0x00],
	[0x00064E71, 0x54, 0xEB],
	[0x00064E72, 0x22, 0xA8],
	[0x00064E73, 0x00, 0x90]
]

HEAP = [
	[0x0005CCA8, 0x80, 0x00],
	[0x0005CCA9, 0x00, 0x02],
	[0x0005CCAF, 0x80, 0x00],
	[0x0005CCB0, 0x00, 0x02]
]

MEDI = [
	[0x0006BE7B, 0x19, 0x32]
]

# Global constants
MENU = [
	['1', "Mouse sensitivity hack", SENS],
	['2', "Heapsize hack", HEAP],
	['3', "Medikit that you REALLY need", MEDI],
	['q', "Quit/exit program", None]
]
MAXLENGTH = 30
DOOMSIZE = 709905
EXENAME = "DOOM2.EXE"

# Fills the end of a string with spaces. The magic number
# must be increased if the strings used get longer.
def fill(str):
	str += (" " * (MAXLENGTH - len(str)))
	return str

# Returns a string [ PATCHED ], [ VANILLA ] or [ UNKNOWN ]
# This indicates if the EXE file has had the patch applied
def checkpatched(f, array):
	if array == None:
		return "[ INVALID ]"

	vanilla = True
	for pos in range(len(array)):
		f.seek(array[pos][0]) 
		if ord(f.read(1)) != array[pos][1]:
			vanilla = False

	patched = True
	for pos in range(len(array)):
		f.seek(array[pos][0])
		if ord(f.read(1)) != array[pos][2]:
			patched = False

	if not vanilla and not patched:
		return "[ UNKNOWN ]"
	if vanilla == True:
		return "[ VANILLA ]"
	if patched == True:
		return "[ PATCHED ]"
		
		#print(hex(ord(f.read(1))))

	return "[ PATCHED ]"

# This function will only patch a valid EXE file
def dopatch(f, array):
	if checkpatched(f, array) == "[ VANILLA ]":
		for pos in range(len(array)):
			f.seek(array[pos][0]) 
			f.write(bytearray([array[pos][2]]))
		return

	if checkpatched(f, array) == "[ PATCHED ]":
		for pos in range(len(array)):
			f.seek(array[pos][0]) 
			f.write(bytearray([array[pos][1]]))

	return

# Main program
def main(argv):
	print("===================================================");
	print("    Vanilla Doom patcher")
	print("    Hacks for Doom2 v1.9")
	print("===================================================");

	try:
		if os.stat(EXENAME).st_size == DOOMSIZE:

			f = open(EXENAME, "r+b")

			choice = 0

			while choice != 9:
				for item in range(len(MENU)):
					print(MENU[item][0] + ".\t" + fill(MENU[item][1]) + "\t" + checkpatched(f, MENU[item][2])) #str(MENU[item][2])

				choice = raw_input("Please, enter your choice: ")

				if choice == 'q' or choice == 'Q':
					print("\nHave a nice day!  :-)\n")
					quit()

				for item in range(len(MENU)):
					if MENU[item][0] == choice:
						if MENU[item][2] != None:
							dopatch(f, MENU[item][2])

				print("")

			f.close()
		else:
			print(EXENAME + " is not " + DOOMSIZE + " bytes.");
	except (OSError, IOError) as e:
		print(e)
	pass

if __name__ == "__main__":
	main(sys.argv)


