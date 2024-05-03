file = open("conv2.txt","r")
liste = []
for ligne in file:
    liste.append(ligne.strip())

liste2 = []
for elem in liste:
    l = elem.split('/')
    tuple = (int(l[0]),int(l[1],16))
    liste2.append(tuple)

liste2.sort(key =lambda x : x[1])


sortie=open("conCONVERTI.txt","w")
compteur = 0
j=0
while (j<len(liste2)):
    if liste2[j][1]==compteur:
        tmp = liste2[j][0]
        nb = len(str(tmp))
        tmp = str(tmp)
        sortie.write("{")
        sortie.write(str(nb)+",")
        for i in range(nb-1):
            sortie.write(tmp[i])
            sortie.write(",")
        sortie.write((tmp[-1]))
        sortie.write("}")
        sortie.write(",")
        compteur = compteur + 1
        j = j + 1
    else:
        compteur = compteur + 1
        sortie.write("{")
        sortie.write("0},")
