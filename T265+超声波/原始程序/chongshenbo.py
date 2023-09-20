import RPi.GPIO as GPIO
import time


TRIG_pin = 11  # ������ģ��Trig���ƹܽ�, BCM 17 18
ECHO_pin = 12  # ������ģ��Echo���ƹܽ�

# ������ģ���ʼ������
def init_setup():
    GPIO.setmode(GPIO.BOARD)      # ����ʵ�ʵ�����ܽŸ�GPIO��
    GPIO.setwarnings(False)       # ����GPIO����ע�⾯��
    GPIO.setup(TRIG_pin, GPIO.OUT) # Tring����Ϊ���ģʽ
    GPIO.setup(ECHO_pin, GPIO.IN)  # Echo����Ϊ����ģʽ

# ������������뺯��
def distance():
    GPIO.output(TRIG_pin, 0)  # ��ʼ��ʼ
    time.sleep(0.000002)  # ��ʱ2us
    GPIO.output(TRIG_pin, 1)  # �����������źţ���ʱ10us
    time.sleep(0.00001)    # ��������������
    GPIO.output(TRIG_pin, 0)  # ����Ϊ�͵�ƽ

    while GPIO.input(ECHO_pin) == 0: # �ȴ��ش��ź�
        us_a = 0
    us_time1 = time.time()      # ��ȡ��ǰʱ��
    while GPIO.input(ECHO_pin) == 1: # �ش��źŽ�ֹ��Ϣ
        us_a = 1
    us_time2 = time.time()     # ��ȡ��ǰʱ��
    during = us_time2 - us_time1          # ת��΢�뼶��ʱ��

    # �����ڿ����еĴ����ٶ�Ϊ340m/s, ������Ҫ����һ�������źź�һ���ز���Ϣ
    # ���㹫ʽ������ʾ��
    return during * 340 / 2 * 100        # �������

# ѭ������
def loop():
    while True:
        us_dis = distance()   # ��ȡ�������������
        print(us_dis+'cm')       # ��ӡ����������ֵ
        time.sleep(0.3)  # ��ʱ300ms 

# ��Դ�ͷź���
def destroy():
    GPIO.cleanup() # �ͷ���Դ

# �������
if __name__ == "__main__":
    init_setup() # ���ó�ʼ������
    try:
        loop() # ����ѭ������
    except KeyboardInterrupt: # ������Ctrl+Cʱ����ִ��destroy()�ӳ���
        destroy() # �ͷ���Դ
    else:
        pass