import socket


def notify(title, message, duration=5):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.sendto(f"{duration*1000};{title};{message}".encode('utf-8'), ('localhost', 12322))
    sock.close()


def text_progressbar(value:int, total=100):
    proceed = int(value*20/total)
    bar = ''
    for x in range(0, proceed):
        bar += '█'
    for x in range(proceed, 20):
        bar += '■'
    return f'{value}%\n{bar}'


#notify('test', text_progressbar(100), 5)