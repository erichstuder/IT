/* IT - Internal Tracer
 * Copyright (C) 2019 Erich Studer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//Board: Arduino Leonardo

//enable debugging with IT
#define IT_ENABLED

#include "app/app.h"
#include "app/app.cpp"
#include "it/it.h"
#include "it/it.cpp"

boolean timerEvent;
struct appIn_T appIn;
struct appOut_T appOut;

enum LedState{
  On, Off
};

void setup(){
	timerSetup();

	//debugging infrastructure
	Serial.begin(9600);
	itSetup(writeBytesToUart);
}

void loop(){
	if(!timerEvent){
		setBuiltinLed(Off);
		return;
	}
	setBuiltinLed(On);
 
	timerEvent=false;
	appIn.millis_ms = millis();
	appTick(appIn, &appOut);

  #ifdef IT_ENABLED
    itSendToClient("squareMillis", appOut.squareMillis, millis());
    itSendToClient("sqrtMillis", appOut.sqrtMillis, millis());
  #endif
}

void setBuiltinLed(LedState ledState){
  pinMode(LED_BUILTIN, OUTPUT);
  if(ledState == On){
    digitalWrite(LED_BUILTIN, HIGH);    
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void timerSetup(){
	timerEvent=false;
	#if APP_SAMPLETIME==1
		TCCR1A = 0; //for any reason, this must be done!!
		TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10); //match on value of OCR1A and divide clock by 1024
		OCR1A = 15625; //1000ms
		TIMSK1 = _BV(OCIE1A); //enable interrupt
	#else
		#error APP_SAMPLETIME not supported
	#endif
}

boolean timerEventPending(){
	return timerEvent;
}

ISR(TIMER1_COMPA_vect){
	timerEvent=true;
}

ItError writeBytesToUart(const byte* buf, unsigned int bufLen){
	if(!Serial){
		return ClientUnavailable;
	}
	if(Serial.write(buf, bufLen) != bufLen){
		return ClientWriteError;
	}
	return NoError;
}
