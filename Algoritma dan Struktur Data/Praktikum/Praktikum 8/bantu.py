import time
import os

def clearTerminal():
    os.system('clear')

def isInArray(l,val):
    valid = False
    i = 0
    while i < len(l) and not valid:
        if l[i] == val:
            valid = True
        else:
            i +=1
    return valid

def findPlatIdx(l,val):
    i = 0
    found = False
    while i < len(l) and not found:
        if l[i] == val:
            found = True
        else:
            i +=1
    return i

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

def insertToArraySorted(l,val):
    if(not isFull(l)):
        idx = 0
        found = False
        while idx<elmtCount(l) and not found:
            if l[idx][0] > val[0]:
                found = True
            else:
                idx +=1
        for i in range(elmtCount(l),idx,-1):
            l[i] = l[i-1]
        l[idx] = val

def deleteElmt(l,idx):
    for i in range(idx,len(l)-1):
        l[i] = l[i+1]
    l[len(l)-1] = "*"

def id_ticket(l):
    tiket = 1
    found = False
    i = 0
    while tiket <len(l) and not found:
        if l[i][0] != tiket:
            found = True
        else:
            tiket +=1
            i +=1
    return tiket

def searchTiket(l,plat):
    i = 0
    found = False
    while i < len(l) and not found:
        if l[i][1] == plat:
            found = True
        else:
            i +=1
    return i

def printList(l):
    print("[", end="")
    for i in range(elmtCount(l)):
        if i < elmtCount(l)-1:
            print(f"{l[i]},", end="")
        else:
            print(f"{l[i]}", end="")
    print("]")

parkiran = ["*" for i in range(100)]
tiket = ["*" for i in range(100)]
run = True
noTiket = 1

while run:
    print("MENU APLIKASI PARKIRAN")
    print("Pilih Menu")
    print("1.Masukkan kendaran")
    print("2.Keluarkan kendaraan")
    print("3.Cek Parkiran")
    print("4.Cek Tiket List")
    print("5.Exit Aplikasi")
    tipe = int(input("Masukkan pilihan: "))
    while tipe != 1 and tipe != 2 and tipe != 3 and tipe != 4 and tipe != 5:
        print("Masukkan salah, ulangi input")
        tipe = int(input("Masukkan pilihan: "))
    if tipe == 1:
        clearTerminal()
        plat = input("Masukkan plat nomor anda: ")
        if(isInArray(parkiran, plat)):
            print("Kendaraan anda masih memiliki tiket")
        else:
            if(not isFull(parkiran)):
                insertToArray(parkiran, plat)
                currSec = time.time()
                noTiket = id_ticket(tiket)
                insertToArraySorted(tiket, [noTiket, plat, currSec])
                print(f"Kendaraan anda memiliki no tiket {noTiket}")
            else:
                print("Parkiran penuh")
    if tipe == 2:
        clearTerminal()
        plat = input("Masukkan plat kendaraan anda: ")
        if(isInArray(parkiran,plat)):
            jenis = input("Masukkan jenis kendaraan anda: ")
            while jenis != "Mobil" and jenis != "mobil" and jenis != "Motor" and jenis != "motor":
                print("Masukkan salah, ulangi input")
                jenis = input("Masukkan jenis kendaraan anda: ")
            if jenis == "Mobil" or jenis == "mobil":
                idxTiket = searchTiket(tiket, plat)
                waktuParkir = tiket[idxTiket][2]
                totalDetik = time.time() - waktuParkir
                totalJam = totalDetik // 3600
                harga = 0
                if totalJam<1:
                    harga = 2000
                elif totalJam<2:
                    harga = 4000
                elif totalJam<3:
                    harga = 6000
                elif totalJam<4:
                    harga = 8000
                else:
                    harga = 10000
                print(f"Total biaya parkir anda: {harga}")
                bayar = 0
                while bayar < harga:
                    print(f"Sisa pembayaran anda {harga-bayar}")
                    bayar += int(input("Bayar sisa uang parkir disini: "))
                idxPlat = findPlatIdx(parkiran,plat)
                deleteElmt(parkiran,idxPlat)
                deleteElmt(tiket,idxTiket)
                print("Hati hati dijalan")
            elif jenis == "Motor" or jenis == "motor":
                idxTiket = searchTiket(tiket, plat)
                waktuParkir = tiket[idxTiket][2]
                totalDetik = time.time() - waktuParkir
                totalJam = totalDetik // 3600
                harga = 0
                if totalJam<1:
                    harga = 1000
                else:
                    harga = 2000
                print(f"Total biaya parkir anda: {harga}")
                bayar = 0
                while bayar < harga:
                    print(f"Sisa pembayaran anda {harga-bayar}")
                    bayar += int(input("Bayar sisa uang parkir disini: "))
                print("Hati hati dijalan")
                idxPlat = findPlatIdx(parkiran,plat)
                deleteElmt(parkiran,idxPlat)
                deleteElmt(tiket,idxTiket)
        else:
            print("Kendaraan anda tidak ada di parkiran!!")
    if tipe == 3:
        clearTerminal()
        print("Kondisi parkiran saat ini : ", end="")
        printList(parkiran)
    if tipe == 4:
        clearTerminal()
        print("Kondisi list tiket saat ini : ", end="")
        printList(tiket)
    if tipe == 5:
        run = False
        print("Terima kasih telah menggunakan aplikasi parkir")