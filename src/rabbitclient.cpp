#include "rabbitclient.hpp"
#include "rabbitmessage.hpp"
#include <string>
#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

using namespace std;
using namespace AmqpClient;

bool RabbitClient::Connect(string host="localhost", int port=5672, string username="guest", string password="guest") // string vhost="/", int frame_max=131072
{
    Channel = Channel::Create(host, port, username, password);
    return true;
}

bool RabbitClient::DeclareQueue(string queue_name, bool passive=false, bool durable=false, bool exclusive=true, bool auto_delete=true)
{
    Channel->DeclareQueue(queue_name, passive, durable, exclusive, auto_delete);
    return true;
}


bool RabbitClient::Publish(string queue_name, string value)
{
    BasicMessage::ptr_t message = BasicMessage::Create(value);
    Channel->BasicPublish(DefaultExchange, queue_name, message, true);
    return true;
}

bool RabbitClient::Subscribe(string queue_name)
{
    ConsumerTag = Channel->BasicConsume(queue_name, "", true, false);
    return true;
}

RabbitMessage RabbitClient::Consume()
{
    Envelope::ptr_t envelope = Channel->BasicConsumeMessage(ConsumerTag);
    RabbitMessage message;
    message.Body = envelope->Message()->Body();
    Table headers = envelope->Message()->HeaderTable();
    //headers.size()
    for(int x=0; x<headers.size(); x++)
    {    
        message.Headers["evan"] = "mooo";
    }
    Channel->BasicAck(envelope);
    return message;
}
