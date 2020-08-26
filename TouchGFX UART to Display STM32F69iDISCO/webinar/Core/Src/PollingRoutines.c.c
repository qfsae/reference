#include "main.h"
#include "PollingRoutines.h"
#include "string.h"
#include "cmsis_os.h"

extern UART_HandleTypeDef huart1;
extern osSemaphoreId_t binarySemUartMsgHandle;

uint8_t uartMsgBuf[UART_BUF_SIZE];
uint8_t uartMsgData[2];
uint8_t msgIndex = 0;
uint8_t msgRdyFlag = 0;

void PollingInit() {
	HAL_UART_Receive_IT(&huart1, uartMsgData, 1);
}

void PollingRoutine() {
	if (msgRdyFlag) {
		osSemaphoreRelease(binarySemUartMsgHandle);
		msgRdyFlag = 0;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	msgRdyFlag = 1;
	HAL_UART_Receive_IT(&huart1, uartMsgData, 1);
}
