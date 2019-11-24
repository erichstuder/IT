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
#include <string.h>

#include "app.h"
#include "squareWave.h"
#include "controller.h"
#include "plant.h"
#include "it.h"

static char itCmdBuffer[IT_CMD_BUFFER_SIZE];
static unsigned char itCmdBufferIndex = 0;
static bool itCmdBufferFull = false;

static ItError_t itCmdHandler(double* result);
static ItError_t itCmdBufferAppend(const char letter);

void appInit(WriteBytesToClient_t writeBytesToClient, ReadByteFromClient_t readByteFromClient){
	setSquareWaveTickTime(1e-3);
	setSquareWaveFrequency(0.2);
	setSquareWaveLevels(2, 10);

	setControllerKp(1);
	setControllerKi(1);

	itInit(writeBytesToClient, readByteFromClient, itCmdHandler, itCmdBufferAppend);
}

void appTick(void){
	setControllerDesiredValue( getSquareWaveSignal() );
	setControllerActualValue( getPlantOut() );
	setPlantIn( getControllerSignal() );

	squareWaveTick();
	controllerTick();
	plantTick();
	itTick();
}

static ItError_t itCmdHandler(double* result){
	//note: strncmp is used as the itCmdBuffer is not terminated by '\0'
	if(strncmp(itCmdBuffer, "d", strlen("d")) == 0){
		*result = (double)getSquareWaveSignal();
	}else{
		return InvalidCommand;
	}
	itCmdBufferIndex = 0;
	itCmdBufferFull = false;
	return NoError;
}

static ItError_t itCmdBufferAppend(const char letter){
	if(itCmdBufferFull == true){
		return BufferFull;
	}
	itCmdBuffer[itCmdBufferIndex] = letter;
	if(itCmdBufferIndex < IT_CMD_BUFFER_SIZE-1){
		itCmdBufferIndex++;
	}else{
		itCmdBufferFull = true;
	}
	return NoError;
}
