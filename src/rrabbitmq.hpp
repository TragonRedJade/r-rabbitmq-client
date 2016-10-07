//
//  RRabbitMQ.hpp
//
//  Created by Evan Lemke on 9/19/16.
//  Copyright © 2016 Evan Lemke. All rights reserved.
//

#ifndef RRabbitMQ_hpp
#define RRabbitMQ_hpp

#include <stdio.h>
#include <string>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

class RRabbitMQ{
private:
    AmqpClient::Channel::ptr_t Channel;
    std::string ConsumerTag;

public:
    bool Connect(std::string host);
    bool Publish(std::string queue, std::string message);
    bool Subscribe(std::string queue);
    std::string Consume();
};

#endif /* IRRabbitMQ_hpp */
