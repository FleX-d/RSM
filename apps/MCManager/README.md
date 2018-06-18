# MCManager

Mosquitto Comunication Manager is aplication witch is using Mosquitto Client facade for manage multiple clients 
and also using IPC layer to communicate with other aplications

## Example Usecase

-Create Mosquitto Client
-Subscribe specific topic 
-Unsubscirbe specific topic 
-Publish message to topic

## Create Client

    rsm::msq::com::MCNewClientRequest request([this](const std::string & m){this->receiveFromBackend(m);},ID, ExternID, Requester, IPAddress, Topic, direction, CleanSession, Port, QOS, KeepAlive);
    MCRequestAck ack = this->addClient(request);

## Subscribe/Unsubscirbe topic

    MCOperationRequest request(ID, Requester, OperationRequestType::Subscribe);
    MCRequestAck ack = this->sendRequest(request);

    
## Publis message

    MCMessage m(ID, Topic, Requester, PayloadMsg);
    MCRequestAck ack = this->publish(m);