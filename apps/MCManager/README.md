# MCManager

Mosquitto Comunication Manager is an aplication witch is using Mosquitto Client facade for manage multiple clients 
and also is using IPC layer to communicate with other aplications.

## Example Usecase

-Create Mosquitto Client
-Subscribe specific topic 
-Unsubscribe specific topic 
-Publish message to topic

## Create Client

For create client at MC Manager, is needed to create  MC New Client Request and call method addClient at manager.

Request contains:
   - pointer to void function, which will be use for sending received data back to your application
   - ID - /Uint32_t/ - Identification number 
   - ExternID - /std::string/ - Identification extern ID for Mosquitto
   - Requester - /std::string/ - Name of application, which is requesting for new Client
   - IPAddress - /std::string/ - Address where client will be connected
   - Topic - /std::string/ - Topic where client will be connected
   - Direction - /Enum DirectionType/ - IN, OUT, BOTH - Direction of communication 
   - CleanSession - /bool/ - TRUE - default value, FALSE - In this mode the broker will store subscription information, and undelivered messages for the client
   - Port - /int/ - 1883 - default value for Port
   - QOS - /int/ - 0 - default value - Quality of service  
   - KeepAlive - /int/ - 60 - default value - Keep Alive

    rsm::msq::com::MCNewClientRequest request([this](const std::string & m){this->receiveFromBackend(m);},ID, ExternID, Requester, IPAddress, Topic, direction, CleanSession, Port, QOS, KeepAlive);
    MCRequestAck ack = m_manager.addClient(request);

## Subscribe/Unsubscribe topic

For Subscribe/Unsubscribe, is needed to create MC Operation Request and call method runClient at manager.

Request contains:
   - ID - /Uint32_t/ - Identification number 
   - Requester - /std::string/ - Name of application, which is requesting for Subscribe/Unsubscribe
   - Operation - /Enum OperationRequestType/ - Subscribe/Unsubscribe

    MCOperationRequest request(ID, Requester, OperationRequestType::Subscribe);
    MCRequestAck ack = m_manager.runClient(request);

    
## Publish message

For Publish Message, is needed create MC Message and call method publish at manager. 

MC Message contains: 
  - ID - /Uint32_t/ - Identification number 
  - Topic - /std::string/ - Topic where client will publish message
  - Requester - /std::string/ - Name of application, which is requesting for publish message
  - PayloadMsg - /std::string/ - Message 

    MCMessage m(ID, Topic, Requester, PayloadMsg);
    MCRequestAck ack = m_manager.publish(m);
    
## Generic Interface

MCManager also offer Generic Interface which can be use for connecting your application to MCManager via ICL(Internal communication layer). 
   There is a generator a documentation at ICL/gen which you could use for generate mirrored generic interface for your aplication.
 
Generic Interface at MCManager implements this methods:
  
    void receiveCreateClientMsg(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& ExternID, const std::string& Requester, const std::string& IPAddress, const std::string& Topic, uint8_t Direction, bool CleanSession, int Port, int QOS, int KeepAlive);
    void receiveOperationMsg(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& Requester, uint8_t Operation) ;
    void receivePublishMsg(std::shared_ptr<GenericClient::Header> header, uint32_t ID, const std::string& Topic, const std::string& Requester, const std::string& PayloadMsg);
 
    void sendRequestAckMsg(std::shared_ptr<GenericClient::Header> header,uint32_t ID, uint8_t RequestAck);
    void sendBackMsg(std::shared_ptr<GenericClient::Header> header,uint32_t ID, const std::string& PayloadMsg);

Better example you can find at folder apps/tests/example.cpp - 
  - Class IPCInterface - generated generic interface for aplications
  - Class GenericClient - provides methods to serialization/ deserialization generic messages
  - Class Sender - Create Client and publish messages at specific topic
  - Class Monitor - Create Client, subscribe at specific topic and wait for messages
