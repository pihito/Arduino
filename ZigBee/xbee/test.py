import serial



if __name__ == "__main__" : 
	ser = serial.Serial("/dev/ttyUSB0", 9600, timeout=7)
	for i in range(0,30) : 
		sRecv = str(ser.readline());
		values = sRecv.split(';')
		for v in values : 
			print(v)
	ser.close()

