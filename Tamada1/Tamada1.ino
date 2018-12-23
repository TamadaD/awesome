/* coding: utf-8

/*----------------------------------------------------------------------
�@�@�S���̃Z���T�[�������āC�V���A���ʐM
---------------------------------------------------------------------- */
#include <Wire.h>
#include <MHZ19_uart.h>

#define DEV_ADR 0x5c  // AM2320�X���[�u�A�h���X
#define LED 13  //�m�F�pLED

uint8_t data[8];
const int rx_pin = 4;  //Serial rx pin no
const int tx_pin = 5; //Serial tx pin no
int pin2 = 0;
int all = 0;
int val = 4;

MHZ19_uart mhz19;

void setup() {
	Wire.begin();
	mhz19.begin(rx_pin, tx_pin);
	mhz19.setAutoCalibration(false);
	Serial.begin(9600);
	Serial.print("MH-Z19 now warming up...  status:");
	Serial.println(mhz19.getStatus());
	delay(500);
}

void loop() {
	int co2ppm = mhz19.getPPM();
	int temp = mhz19.getTemperature();
	int date[1000];

	// AM2320�Z���T�[�̃E�F�C�N�A�b�v
	Wire.beginTransmission(DEV_ADR);
	Wire.endTransmission();

	// ���x�E���x�f�[�^�擾�v��
	Wire.beginTransmission(DEV_ADR);
	Wire.write(0x03);         // ���W�X�^�ǂݎ��R�}���h
	Wire.write(0x00);         // �ǂݎ��J�n���W�X�^�ԍ�
	Wire.write(0x04);         // �ǂݎ��f�[�^��    
	Wire.endTransmission();

	// �f�[�^�̎擾
	Wire.requestFrom(DEV_ADR, 8);

	for (int del = 0; del < 1000; del++)
	{
		pin2 = analogRead(A0);
		// Serial.println(pin2);   
		date[del] = pin2;
		delay(10);

		all = all + date[del];
	}

	int ir = all / 1000;

	if (Wire.available() >= 8) {
		for (uint8_t i = 0; i < 8; i++)
		{
			data[i] = Wire.read();
		}

		int rh = ((int)data[2] * 256 + data[3]) * 10; // ���x
		int tp = ((int)data[4] * 256 + data[5]) * 10; // ���x

		int valu[val] = { tp,rh,ir,co2ppm };    //���X�g�̐���

		for (int j = 0; j < val; j++)
		{
			int high = (valu[j] >> 7) & 127;
			int low = valu[j] & 127;

			Serial.write(128 + j);�@�@�@�@�@�@�@//raspberry pi �p�̃f�[�^���M
			Serial.write(high);
			Serial.write(low);
		}

	}
	delay(1000);
}
