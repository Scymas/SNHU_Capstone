#Schyler Enneman
# CS-499
# Python Authentication System - Unit Testing

# Note: Shows invalid password (continuation of program); though tests come back equal
# Testing is primarily to ensure password is converted into hexadecimal correctly

import unittest
import MD5Conversion


#Testing for MD5 conversions - Using different passwords , ensures the MD5 conversion is correct
class MD5Test(unittest.TestCase):
    def test_MD5Conversion1(self):

        userType = ""
        userPassword = "Apples"
        compareString = "92446c031dbe789c917c6da0d7ab44b9"

        testPass = MD5Conversion.MD5ConversionFunc(userPassword, userType)

        self.assertEqual(testPass, compareString)

    def test_MD5Conversion2(self):

        userType = ""
        userPassword = "Cats"
        compareString = "6839d672141795d0959700017e3cdec4"

        testPass = MD5Conversion.MD5ConversionFunc(userPassword, userType)

        self.assertEqual(testPass, compareString)



if __name__ == "__main__":
    unittest.main()
