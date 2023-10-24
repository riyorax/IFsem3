import time
import random

def isInArray(l,val):
    valid = False
    i = 0
    while i < len(l):
        if l[i] == val:
            valid = True
        else:
            i +=1
    return valid

def elmtCount(l):
    count = 0
    mark = False
    while count < len(l) and not mark:
        if l[count] == "*":
            mark = True
        else:
            count +=1
    return count

def isEmpty(l):
    return(elmtCount(l) == 0)

def isFull(l):
    return(elmtCount(l) == len(l))

def insertToArray(l,val):
    idx = elmtCount(l)
    l[idx] = val

def findTicket(l,val):
    tiket = 0
    for i in range(len(l)):
        if 


parkiran = ["*" for i in range(100)]
tiket = ["*" for i in range(100)]
run = True
noTiket = 1

while run:
    print("MENU APLIKASI PARKIRAN")
    print("Pilih Menu")
    print("1.Masukkan kendaran")
    print("2.Keluarkan kendaraan")
    tipe = int(input("Masukkan pilihan: "))
    while tipe != 1 or tipe != 2:
        print("Masukkan salah, ulangi input")
        tipe = int(input("Masukkan pilihan: "))
    if tipe == 1:
        plat = "Masukkan plat nomor anda: "
        if(isInArray(parkiran, plat)):
            print("Kendaraan anda masih memiliki tiket")
        else:
            if(not isFull(parkiran)):
                insertToArray(parkiran, plat)
                currSec = time.time()
                insertToArray(tiket, [noTiket, currSec])
                print(f"Kendaraan anda memiliki no tiket {}")
            else:
                print("Parkiran penuh")
            
            