#from PyQt5.QtWidgets import QApplication, QPushButton, QMainWindow
#from PyQt5.QtGui import QPainter, QFont, QBrush, QPen
#from PyQt5.QtCore import QRect

from PyQt5.QtCore import * 
from PyQt5.QtGui import * 
from PyQt5.QtWidgets import *

import sys
import time
import threading

import serial
ser = serial.Serial("COM5", 115200)


def set_interval(func, sec):
    def func_wrapper():
        set_interval(func, sec)
        func()
    t = threading.Timer(sec, func_wrapper)
    t.start()
    return t

class MyWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setGeometry(200,200,1100,600)
        self.setWindowTitle("Supervisório Sinaleira")
        self.meuBotao = QPushButton("ALERTA On/Off", self)
        self.meuBotao.setGeometry(775, 475, 180, 80)
        self.meuBotao.clicked.connect(self.estadoAtencao)
        #TODOS OS SINAIS
        self.s1vermelho     = 0
        self.s1amarelo      = 0
        self.s1verde        = 0
        self.s2vermelho     = 0
        self.s2amarelo      = 0
        self.s2verde        = 0
        self.s3vermelho     = 0
        self.s3amarelo      = 0
        self.s3verde        = 0
        self.s4vermelho     = 0
        self.s4amarelo      = 0
        self.s4verde        = 0
        self.s5vermelho     = 0
        self.s5amarelo      = 0
        self.s5verde        = 0
        self.chavePedestre  = 0
        set_interval(self.leSerial, 1)

    def estadoAtencao(self):
        #self.s2vermelho = 0
        #self.s1amarelo = 1
        #self.repaint()
        ser.write(b'i') 


    def paintEvent(self, paintEvent):
        self.painter = QPainter(self)
        self.desenhaUmaSinaleira(self.painter, 150, 100, self.s1vermelho, self.s1amarelo, self.s1verde, "s1")
        self.desenhaUmaSinaleira(self.painter, 325, 100, self.s2vermelho, self.s2amarelo, self.s2verde, "s2")
        self.desenhaUmaSinaleira(self.painter, 500, 100, self.s3vermelho, self.s3amarelo, self.s3verde, "s3")
        self.desenhaUmaSinaleira(self.painter, 675, 100, self.s4vermelho, self.s4amarelo, self.s4verde, "s4")
        self.desenhaUmaSinaleira(self.painter, 850, 100, self.s5vermelho, self.s5amarelo, self.s5verde, "s5")
        self.desenhaChavePedestre(self.painter, self.chavePedestre)
        print("REDESENHANDO")
        self.painter.end()

    def desenhaChavePedestre(self, painter, chave):
        self.painter.setFont(QFont("Arial", 40))
        self.minhaPen = QPen(Qt.black, 2)
        self.painter.setPen(self.minhaPen)
        self.painter.drawText(QPoint(150,550), "Chave pedestre:")

        if (chave == 1): 
            self.myBrush = QBrush(Qt.red)
            self.minhaPen = QPen(Qt.red, 3, Qt.DotLine)
            self.painter.setBrush(self.myBrush)
            self.painter.setPen(self.minhaPen)
            self.painter.drawEllipse(QPoint(670,530), 25, 25)
            self.myBrush = QBrush()
            self.minhaPen = QPen(Qt.green, 3, Qt.DotLine)
            self.painter.setBrush(self.myBrush)
            self.painter.setPen(self.minhaPen)
            self.painter.drawEllipse(QPoint(735,530), 25, 25)
            self.painter.setFont(QFont("Arial", 10))
            self.minhaPen = QPen(Qt.black, 1)
            self.painter.setPen(self.minhaPen)
            self.painter.drawText(QPoint(660,535), "off")
        else:
            self.myBrush = QBrush()
            self.minhaPen = QPen(Qt.red, 3, Qt.DotLine)
            self.painter.setBrush(self.myBrush)
            self.painter.setPen(self.minhaPen)
            self.painter.drawEllipse(QPoint(670,530), 25, 25)
            self.myBrush = QBrush(Qt.green)
            self.minhaPen = QPen(Qt.green, 3, Qt.DotLine)
            self.painter.setBrush(self.myBrush)
            self.painter.setPen(self.minhaPen)
            self.painter.drawEllipse(QPoint(735,530), 25, 25)
            self.painter.setFont(QFont("Arial", 10))
            self.minhaPen = QPen(Qt.black, 1)
            self.painter.setPen(self.minhaPen)
            self.painter.drawText(QPoint(725,535), "on")


    def desenhaUmaSinaleira(self, painter, x, y, vermelho, amarelo, verde, semaforo):
        self.painter.setFont(QFont("Arial", 40))
        self.minhaPen = QPen(Qt.black, 2)
        self.painter.setPen(self.minhaPen)
        self.painter.drawText(QPoint(x+25,y-10), semaforo)

        self.myBrush = QBrush()
        self.painter.setBrush(self.myBrush)
        self.painter.drawRect(x,y,100,350)

        if (vermelho == 1): self.myBrush = QBrush(Qt.red)
        else: self.myBrush = QBrush()
        self.minhaPen = QPen(Qt.red, 5)
        self.painter.setBrush(self.myBrush)
        self.painter.setPen(self.minhaPen)
        self.painter.drawEllipse(QPoint(x+50,y+50), 50, 50)

        if (amarelo == 1): self.myBrush = QBrush(Qt.yellow)
        else: self.myBrush = QBrush()
        self.minhaPen = QPen(Qt.yellow, 5)
        self.painter.setBrush(self.myBrush)
        self.painter.setPen(self.minhaPen)
        self.painter.drawEllipse(QPoint(x+50,y+175), 50, 50)

        if (verde == 1): self.myBrush = QBrush(Qt.green)
        else: self.myBrush = QBrush()
        self.minhaPen = QPen(Qt.green, 5)
        self.painter.setBrush(self.myBrush)
        self.painter.setPen(self.minhaPen)
        self.painter.drawEllipse(QPoint(x+50,y+300), 50, 50)

    def leSerial(self):
        listaComValores = []
        texto = ""
        #LE TUDO DE UMA VEZ. NO COMECO, TEM UNS LOADS, ENTRY, MODE DEVIDO AO RESET DO ESP
        while ser.in_waiting:
            texto = ser.readline().decode("utf-8").replace("\r\n", "") #converte byte em string
            listaComValores = texto.split(" ")
            print(listaComValores)
            print("Tamanho: ")
            print(len(listaComValores))
            if (listaComValores[0] == "botaoapertado"): 
                self.chavePedestre = 0
                self.update()
        if (len(listaComValores) != 16): return; #SE NAO FOR UMA MENSAGEM SERIAL COM OS 15 VALORES, NAO EXECUTAR O RESTO DA FUNCAO
        if (listaComValores[0] == "1"): self.s1vermelho = 1
        else: self.s1vermelho = 0
        if (listaComValores[1] == "1"): self.s1amarelo = 1
        else: self.s1amarelo = 0
        if (listaComValores[2] == "1"): self.s1verde = 1
        else: self.s1verde = 0

        if (listaComValores[3] == "1"): self.s2vermelho = 1
        else: self.s2vermelho = 0
        if (listaComValores[4] == "1"): self.s2amarelo = 1
        else: self.s2amarelo = 0
        if (listaComValores[5] == "1"): self.s2verde = 1
        else: self.s2verde = 0

        if (listaComValores[6] == "1"): self.s3vermelho = 1
        else: self.s3vermelho = 0
        if (listaComValores[7] == "1"): self.s3amarelo = 1
        else: self.s3amarelo = 0
        if (listaComValores[8] == "1"): self.s3verde = 1
        else: self.s3verde = 0

        if (listaComValores[9] == "1"): self.s4vermelho = 1
        else: self.s4vermelho = 0
        if (listaComValores[10] == "1"): self.s4amarelo = 1
        else: self.s4amarelo = 0
        if (listaComValores[11] == "1"): self.s4verde = 1
        else: self.s4verde = 0

        if (listaComValores[12] == "1"): self.s5vermelho = 1
        else: self.s5vermelho = 0
        if (listaComValores[13] == "1"): self.s5amarelo = 1
        else: self.s5amarelo = 0
        if (listaComValores[14] == "1"): self.s5verde = 1
        else: self.s5verde = 0

        if (listaComValores[15] == "1"): self.chavePedestre = 1
        else: self.chavePedestre = 0
            
        self.update()
      
app = QApplication(sys.argv)
window = MyWindow()
window.show() 
app.exec()
