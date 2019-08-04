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

#ifndef IT_H
#define IT_H

static void (*sendStringFunc)(string stringToSend);

inline void itToClient(string signalName, double data, double timeStamp){
	sendStringFunc(signalName);
	sendStringFunc();
}

/*inline boolean fromClient(byte buf[], int len){
	if(Serial1.available() >= len+1){
		if(Serial1.read() == ET_OUTPUT_ID){
			int n;
			for(n=0; n<len; n++){
				buf[n] = Serial1.read();		
			}
			return true;
		}
	}
	return false;
}*/

#endif //IT_H
