

# this just tests storing stuff in a file
file = open("TestData3.txt", "a")

four = 4

file.write("This is a test" + ", " + str(four) + ",") 
file.write("To add more lines" + "\n")

file.close()