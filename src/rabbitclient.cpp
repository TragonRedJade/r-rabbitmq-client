#include "rabbitclient.hpp"
#include <string>
#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

using namespace std;
using namespace AmqpClient;

bool RabbitClient::Connect(string host="localhost", int port=5672, string username="guest", string password="guest") // string vhost="/", int frame_max=131072
{
  // try
  // {
    Channel = Channel::Create(host, port, username, password);
    return true;
  // }
  // catch (exception const& e )
  // {
  //   std::cout << "Connection error: " << e.what() << std::endl;
  //   return false;
  // }
}

bool RabbitClient::DeclareQueue(string queue_name, bool passive=false, bool durable=false, bool exclusive=true, bool auto_delete=true)
{
  // try
  // {
    Channel->DeclareQueue(queue_name, passive, durable, exclusive, auto_delete);
    return true;
  // }
  // catch (exception const& e )
  // {
  //   std::cout << "Queue declare error: " << e.what() << std::endl;
  //   return false;
  // }
}


bool RabbitClient::Publish(string queue_name, string value)
{
  // try
  // {
    BasicMessage::ptr_t message = BasicMessage::Create(value);
    Channel->BasicPublish(DefaultExchange, queue_name, message, true);
    return true;
  // }
  // catch (exception const& e )
  // {
  //   std::cout << "Publish error: " << e.what() << std::endl;
  //   return false;
  // }
}

bool RabbitClient::Subscribe(string queue_name)
{
  // try
  // {
    ConsumerTag = Channel->BasicConsume(queue_name, "", true, false);
    return true;
  // }
  // catch (exception const& e )
  // {
  //   std::cout << "Subscribtion error: " << e.what() << std::endl;
  //   return false;
  // }
}

string RabbitClient::Consume()
{
  // try
  // {
    Envelope::ptr_t envelope = Channel->BasicConsumeMessage(ConsumerTag);
    string message = envelope->Message()->Body();
    Channel->BasicAck(envelope);
    return message;
  // }
  // catch (exception const& e )
  // {
  //   std::cout << "Recieve error: " << e.what() << std::endl;
  //   return "";
  // }
}
