"""
IT - Internal Tracer
Copyright (C) 2019 Erich Studer

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
"""

import time
import serial  # install pyserial to gain access
import sys
import queue
from ComPortHandler import ComPortHandler
import threading

"""
def handleComPortInput(data):
    try:
        print(data.decode("utf-8"), end='')
    except UnicodeDecodeError:
        print('')
        print("Not utf-8: ", end='')
        print(data)
"""


def __inputReaderWorker():
    while True:
        inputQueue.put(input())


inputQueue = queue.Queue()

"""
comPortReceiver = ComPortReceiver(port='COM6', baudrate=9600)
comPortReceiver.setOnConnecting(lambda: print('comPortReceiver connecting'))
comPortReceiver.setOnConnected(lambda: print('comPortReceiver connected'))
comPortReceiver.setOnReceived(handleComPortInput)
comPortReceiver.setOnError(lambda e: print('comPortReceiver error: ' + e))
comPortReceiver.setOnErrorNoExit(lambda: print('comPortReceiver errorNoExit'))
comPortReceiver.start()
"""
threading.Thread(target=__inputReaderWorker).start()
comPortHandler = ComPortHandler(port='COM6', baudrate=9600)
while True:
    while not inputQueue.empty():
        inputData = inputQueue.get(block=False)
        print(inputData)
        comPortHandler.write(inputData)
    print(comPortHandler.read().decode('utf-8'), end='')
    time.sleep(0.01)

    """
    cmd = input()
    if cmd == 'exit':
        print('goodbye ...')
        sys.stdout.flush()
        time.sleep(2)
        break
    else:
        # serialPort = serial.Serial(port='COM6', exclusive=False)
        # serialPort.baudrate = 9600
        # serialPort.write(cmd)
        print(cmd)
    """

    """
    elif cmd == 'status':
        print('status not yet implemented')
    elif cmd == 'start':
        print('start not yet implemented')
    elif cmd == 'stop':
        print('stop not yet implemented')
    else:
        print(cmd)
    """
