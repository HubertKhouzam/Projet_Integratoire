path = "map_R2.txt"
binfile = ""


with open(path, 'r') as file:
    text = file.read()  # Lit tout le contenu du fichier texte
    numbers_str = text.split()  # Sépare le texte en utilisant les espaces
    numbers = [int(num_str) for num_str in numbers_str]  # Convertit les chaînes en entiers

if('1' in path): binfile = "map_R1.bin"
else: binfile = "map_R2.bin"


with open(binfile, 'wb') as file:
    for number in numbers:
        file.write(number.to_bytes(1, byteorder='little'))  # Convertit le nombre en un octet et l'écrit dans le fichier
        if (number == 10 or number == 32):
            for i in range(2):
                temp = 0 
                file.write(temp.to_bytes(1,byteorder='little'))
