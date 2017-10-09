API_PASSWORD = 'YOUR_PASSWORD'
URL = 'http://192.168.0.5:8123/api/states/'
ENTITY = 'relais.piscine'
TIMEOUT = 60
PIN = 5

def get_data():
    import urequests
    url = '{}{}'.format(URL, ENTITY)
    headers = {'x-ha-access': API_PASSWORD,
               'content-type': 'application/json'}
    resp = urequests.get(URL, headers=headers)
    return resp.json()['prog']

def main():
    import machine
    import time
    rtc = machine.RTC()
    pin = machine.Pin(PIN, machine.Pin.OUT)
    while True:
        try:
            if ()
            rtc.init((2014, 5, 1, 4, 13, 0, 0, 0))
            print(rtc.now())
            
            if int(get_data()) >= 20:
                pin.high()
            else:
                pin.low()
        except TypeError:
            pass
        time.sleep(TIMEOUT)

if __name__ == '__main__':
    print('Get the state of {}'.format(ENTITY))
    main()
