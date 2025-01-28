#include "PDU.h"

int sendPDU(int clientSocket, uint8_t * dataBuffer, int lengthOfData) {
    int netOrder_PDULength = htons(lengthOfData + 2), hostOrder_PDULength = ntohs(lengthOfData + 2);
    uint8_t PDU[lengthOfData + 2];

    memcpy(PDU, &netOrder_PDULength, 2);                                //Copy PDU length into PDU's header (2 bytes)
    memcpy(PDU + 2, dataBuffer, lengthOfData);                          //Copy data into the PDU's payload

    return (safeSend(clientSocket, PDU, hostOrder_PDULength, 0) - 2);   //Returns the # of bytes sent excluding header
}

int recvPDU(int socketNumber, uint8_t * dataBuffer, int bufferSize){
    int PDULength, hostOrder_payloadLength, 
        bytesReceived = safeRecv(socketNumber, dataBuffer, 2, MSG_WAITALL);

    /// Parse PDU ///
    if (bytesReceived == 0) {                               //Return 0 if connection is closed
        printf("Client has closed their connection\n");
        return 0;

    } else if (bytesReceived > 0) {                         //Parse payload length within dataBuffer
        memcpy(&PDULength, dataBuffer, 2);                  //Copy header into PDULength
        
        if (bufferSize < ntohs(PDULength)) {                //Exit if buffer is not large enough to receive PDU
            perror("Buffer size < PDU length");
            return -1;

        }
        
        hostOrder_payloadLength = ntohs(PDULength) - 2;                                         //Payload length = PDU length - header
        return safeRecv(socketNumber, dataBuffer + 2, hostOrder_payloadLength, MSG_WAITALL);    //Returns the # of bytes received excluding header
    
    } else {                                                //Exit if bytesReceived < 0
        perror("Reached default value for recvPDU()");
        return -1;

    }
}