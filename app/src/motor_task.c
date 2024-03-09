// void CAN_Transmit(void const *argument)
// {
//     CAN_Tx_Pack_t can_tx_pack;
//     for (;;)
//     {
//         // Wait for the message to be received
//         xQueueReceive(can_tx_queueHandle, &can_tx_pack, portMAX_DELAY);
//         CAN_HandleTypeDef *hcanx = (can_tx_pack.can_bus == 1) ? &hcan1 : &hcan2;
//         // Wait for available mailbox
//         while (HAL_CAN_GetTxMailboxesFreeLevel(&hcanx) == 0);
//         HAL_CAN_AddTxMessage(&hcanx, &can_tx_pack.tx_header, can_tx_pack.data, (uint32_t *)CAN_TX_MAILBOX0);
//     }
// }