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

bool RabbitClient::Subscribe(string queue_name, string consumer_tag, bool no_ack=true, bool exclusive=true, boost::uint16_t message_prefetch_count = 1)
{
    ConsumerTag = Channel->BasicConsume(queue_name, consumer_tag, false, no_ack, exclusive, message_prefetch_count);
    return true;
}

bool RabbitClient::Unsubscribe()
{
    Channel->BasicCancel(ConsumerTag);
    ConsumerTag = "";
    return true;
}

bool RabbitClient::IsOpen()
{
  // new Detail::ChannelImpl Impl;
  // return   Impl->CheckIsConnected(Channel);;//Detail::ChannelImpl::IsChannelOpen(Channel);
  //Channel->CheckIsConnected(); //This will throw an exception if not connected
  return TRUE;
}

bool RabbitClient::DeclareExchange(string exchange_name, string exchange_type="direct", bool passive=false, bool durable=false, bool auto_delete=true)
{
    Channel->DeclareExchange(exchange_name, exchange_type, passive, durable, auto_delete);
    return true;
}

bool RabbitClient::DeleteExchange(string exchange_name, bool if_unused=false)
{
    Channel->DeleteExchange(exchange_name, if_unused);
    return true;
}

bool RabbitClient::BindExchange(string destination, string source, string routing_key="")
{
    Channel->BindExchange(destination, source, routing_key);
    return true;
}

bool RabbitClient::UnbindExchange(string destination, string source, string routing_key="")
{
    Channel->UnbindExchange(destination, source, routing_key);
    return true;
}

bool RabbitClient::DeclareQueue(string queue_name, bool passive=false, bool durable=false, bool exclusive=true, bool auto_delete=true)
{
    Channel->DeclareQueue(queue_name, passive, durable, exclusive, auto_delete);
    return true;
}

bool RabbitClient::DeleteQueue(string queue_name, bool if_unused=false, bool if_empty=false)
{
  Channel->DeleteQueue(queue_name, if_unused, if_empty);
  return true;
}

bool RabbitClient::BindQueue(string queue_name, string exchange_name, string routing_key="")
{
  Channel->BindQueue(queue_name, exchange_name, routing_key);
  return true;
}

bool RabbitClient::UnbindQueue(string queue_name, string exchange_name, string routing_key="")
{
  Channel->UnbindQueue(queue_name, exchange_name, routing_key);
  return true;
}

bool RabbitClient::PurgeQueue(string queue_name)
{
  Channel->PurgeQueue(queue_name);
  return true;
}

bool RabbitClient::Publish(string exchange_name, string routing_key, string message, Rcpp::List headers)
{
    BasicMessage::ptr_t basic_message = BasicMessage::Create(message);
    Channel->BasicPublish(exchange_name, routing_key, basic_message, true, false);
    return true;
}

RabbitMessage RabbitClient::Consume()
{
    Envelope::ptr_t envelope = Channel->BasicConsumeMessage(ConsumerTag);
    RabbitMessage message(Channel, envelope);

    message.Body = envelope->Message()->Body();
    message.RoutingKey = envelope->RoutingKey();
    Table headers = envelope->Message()->HeaderTable();

    for (auto& row : headers) {
        message.Headers[row.first] = row.second.GetString();
    }

    // Channel->BasicAck(envelope);
    return message;
}
