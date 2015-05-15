#!/usr/bin/python3
from i2clibraries import i2c_hmc5883l

hmc5883l = i2c_hmc5883l.i2c_hmc5883l(1)
hmc5883l.setContinuousMode()
hmc5883l.setDeclination(9,54)
# To scaled axes
while True:

	(degress, minutes) = hmc5883l.getHeading()
	print(str(degress)+" "+str(minutes))

