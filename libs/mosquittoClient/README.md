
# Mosquitto Client

 Facade for communication based on the Mosquitto library https://github.com/eclipse/mosquitto 

## Example Usecase

 Communication based on subscribing and publishing messages on topic

## Usage

### Create Client

    rsm::conn::mqtt::MosquittoSetting setting("127.0.0.1");
    auto client = std::make_shared<Client>("client1", setting);

### Subscribe/Unsubscribe

    std::string topic = "test";
    client->subscribeTopic(topic);
    client->unsubscribeTopic(topic);
    
### Publish message

    client->publishMessage(rsm::conn::mqtt::MqttMessage(topic , " Communication is working! "));  

Examples can be found in the tests folder.
