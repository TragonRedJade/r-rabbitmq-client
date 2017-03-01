
#ifndef RabbitMessage_hpp
#define RabbitMessage_hpp

#include <stdio.h>
#include <string>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <Rcpp.h>


class RabbitMessage{
private:
    AmqpClient::Envelope::ptr_t SourceMessage;
    AmqpClient::Channel::ptr_t Channel;

public:
    RabbitMessage();
    RabbitMessage(AmqpClient::Channel::ptr_t channel, AmqpClient::Envelope::ptr_t source_message);

    std::string Body;
    Rcpp::List Headers;
    std::string RoutingKey;

    bool BasicAck();
    bool BasicReject(bool requeue, bool multiple);

};


#endif
