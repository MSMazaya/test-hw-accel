# Python code to convert from Binary
# to Hexadecimal using int() and hex()
def binToHexa(n):

	# convert binary to int
	num = int(n, 2)
	
	# convert int to hexadecimal
	hex_num = hex(num)
	return(hex_num)
	
def hex_to_bin(hex_string):
    decimal_number = int(hex_string, 16)
    binary_number = bin(decimal_number)[2:]
    # Pad with zeros to make it 32-bit
    binary_number = binary_number.zfill(32)
    # Insert space every 4 bits
    binary_number_with_spaces = ' '.join(binary_number[i:i+4] for i in range(0, len(binary_number), 4))
    return binary_number_with_spaces


while (True):
    print(binToHexa(input("> ")))