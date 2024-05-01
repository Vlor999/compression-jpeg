file = open("conv2.txt","r")
liste = []
for ligne in file:
    liste.append(ligne.strip())

liste2 = []
for elem in liste:
    l = elem.split('/')
    tuple = (int(l[0]),int(l[1],16))
    print(tuple)
    liste2.append(tuple)

liste2.sort(key =lambda x : x[1])


sortie=open("conCONVERTI.txt","w")
for elem in liste2:
    tmp = elem[0]
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
