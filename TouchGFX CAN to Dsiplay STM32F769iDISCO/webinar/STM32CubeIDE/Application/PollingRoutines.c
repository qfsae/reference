#include "main.h"
#include "PollingRoutines.h"
#include "string.h"
#include "cmsis_os.h"

extern UART_HandleTypeDef huart1;
extern CAN_HandleTypeDef hcan1;
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
	char *message = "Received CHAR!\n";
	HAL_UART_Transmit(&huart1, message, strlen(message), 10);
	HAL_UART_Receive_IT(&huart1, uartMsgData, 1);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
	// based Rx
	CAN_RxHeaderTypeDef RxHeader;
	uint8_t recvMessage[8];

	if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, recvMessage) != HAL_OK) {
		Error_Handler();
	}
	//uint8_t *successMsg = "received CAN MSG!\n";
	//HAL_UART_Transmit(&huart1, successMsg, strlen(successMsg), 10);

	// Now print message contents
	HAL_UART_Transmit(&huart1, recvMessage, strlen(recvMessage), 10);
	uartMsgData[0] = recvMessage[msgIndex++];
	if (msgIndex == 8) {
		msgIndex = 0;
	}
	msgRdyFlag = 1;
}
