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

public:
    bool Connect(std::string host, int port, std::string username, std::string password);
    bool Subscribe(std::string queue_name, std::string consumer_tag, bool no_ack, bool exclusive, boost::uint16_t message_prefetch_count);
    bool Unsubscribe();

    bool IsOpen();

    //exchanges
    bool DeclareExchange(std::string exchange_name, std::string exchange_type, bool passive, bool durable, bool auto_delete);
    bool DeleteExchange(std::string exchange_name, bool if_unused);
    bool BindExchange(std::string destination, std::string source, std::string routing_key);
    bool UnbindExchange(std::string destination, std::string source, std::string routing_key);
    //exchanges

    //queues
    bool DeclareQueue(std::string queue_name, bool passive, bool durable, bool exclusive, bool auto_delete);
    bool DeleteQueue(std::string queue_name, bool if_unused, bool if_empty);
    bool BindQueue(std::string queue_name, std::string exchange_name, std::string routing_key);
    bool UnbindQueue(std::string queue_name, std::string exchange_name, std::string routing_key);
    bool PurgeQueue(std::string queue_name);
    //queues


    bool Publish(std::string exchange_name, std::string routing_key, std::string message, Rcpp::List headers);
    RabbitMessage Consume();
};

#endif /* IRRabbitMQ_hpp */
