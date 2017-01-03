//
//  RRabbitMQ.hpp
//
//  Created by Evan Lemke on 9/19/16.
//  Copyright © 2016 Evan Lemke. All rights reserved.
//

#ifndef RRabbitMQ_hpp
#define RRabbitMQ_hpp

#include "rabbitmessage.hpp"

#include <stdio.h>
#include <string>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <Rcpp.h>

class RabbitClient{
private:
    AmqpClient::Channel::ptr_t Channel;
    std::string ConsumerTag;
    AmqpClient::BasicMessage::ptr_t LastMessageConsumed;

public:
    std::string DefaultExchange;

    bool Connect(std::string host, int port, std::string username, std::string password);
    bool DeclareQueue(std::string queue_name, bool passive, bool durable, bool exclusive, bool auto_delete);
    bool Publish(std::string queue_name, std::string message);
    bool Subscribe(std::string queue_name);
    RabbitMessage Consume();
};

#endif /* IRRabbitMQ_hpp */
