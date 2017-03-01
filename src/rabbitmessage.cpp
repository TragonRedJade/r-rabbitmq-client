#include "rabbitmessage.hpp"
#include <string>
#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

using namespace std;
using namespace AmqpClient;

RabbitMessage::RabbitMessage()
{
  Channel = NULL;
  SourceMessage = NULL;
}

RabbitMessage::RabbitMessage(Channel::ptr_t channel, Envelope::ptr_t source_message)
{
  Channel = channel;
  SourceMessage = source_message;
}

bool RabbitMessage::BasicAck()
{
    Channel->BasicAck(SourceMessage);
    return true;
}

bool RabbitMessage::BasicReject(bool requeue, bool multiple=false)
{
    Channel->BasicReject(SourceMessage, requeue, multiple);
    return true;
}
