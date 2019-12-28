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

#ifndef APP_H
#define APP_H

#define APP_SAMPLETIME 1 //s

enum class AppError {
	NoError,
	UartUnavailable,
	NoDataAvailable,
	UartWriteError
};

typedef unsigned long (*GetCurrentMillis_t) (void);
typedef bool (*ByteFromUartAvailable_t) (void);
typedef AppError (*ReadByteFromUart_t) (char* const data);
typedef AppError (*WriteByteToUart_t) (const unsigned char data);

typedef struct {
	ByteFromUartAvailable_t byteFromUartAvailable;
	ReadByteFromUart_t readByteFromUart;
	WriteByteToUart_t writeByteToUart;
	GetCurrentMillis_t getCurrentMillis;
} AppCallbacks_t;

extern void (*appInit)(AppCallbacks_t callbacks);
extern void (*appTick)(void);

#endif
