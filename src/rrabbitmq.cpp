/*
**  RRabbitMQ.cpp
**  RabbitTest
**
**  Created by Evan Lemke on 9/19/16.
**  Copyright © 2016 Evan Lemke. All rights reserved.
*/

#include "RRabbitMQ.hpp"
#include <string>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <Rcpp.h>
#include <R.h>


//using namespace Rcpp;
using namespace std;
using namespace AmqpClient;
using namespace Rcpp;

bool RRabbitMQ::Connect(string host){
    Channel = Channel::Create(host);
    return true;

}

bool RRabbitMQ::Publish(string queue, string value)
{
    BasicMessage::ptr_t message = BasicMessage::Create(value);
    Channel->BasicPublish("", queue, message);
    return true;
}

bool RRabbitMQ::Subscribe(string queue){

    ConsumerTag = Channel->BasicConsume(queue, "", true, false);

    return true;
}

string RRabbitMQ::Consume()
{
    Envelope::ptr_t envelope = Channel->BasicConsumeMessage(ConsumerTag);
    string message = envelope->Message()->Body();
    Channel->BasicAck(envelope);
    return message;
}


RCPP_MODULE(unif_module) {
    class_<RRabbitMQ>( "RasicallyRabbit" )
    .constructor()
//    .field( "Rabbit.channel", &RRabbitMQ::Channel )
    .method( "Rabbit.Connect", &RRabbitMQ::Connect )
    .method( "Rabbit.Subscribe", &RRabbitMQ::Subscribe )
    .method( "Rabbit.Publish", &RRabbitMQ::Publish )
    .method( "Rabbit.Consume", &RRabbitMQ::Consume )
    ;
}




//// [[Rcpp::export]]
//string Recieve(string key){
//    return key;
//}
//


//// [[Rcpp::export]]
//Channel::ptr_t Connect(const string &host = "127.0.0.1", int port = 5672,
//                       const string &username = "guest", const string &password = "guest",
//                       const string &vhost = "/", int frame_max = 131072){
//
//    Channel::ptr_t channel = AmqpClient::Channel::Create(host,port,username,password,vhost,frame_max);
//
//    return channel;
//}



//class RRabbitMQ{
//public :
//
//    Channel::ptr_t Channel;
//    string QueueName;
//
//    bool Connect(string host, string queue){
//
//        Channel = Channel::Create(host);
//        QueueName = queue;
//        return true;
//    }
//
//
//    bool Publish(string value)
//    {
//        BasicMessage::ptr_t message = BasicMessage::Create(value);
//        Channel->BasicPublish("", QueueName, message);
//
//        return true;
//    }
//
//
//};
