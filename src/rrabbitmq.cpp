#include "rrabbitmq.hpp"
#include <string>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <Rcpp.h>
#include <R.h>

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
    .method( "Rabbit.Connect", &RRabbitMQ::Connect )
    .method( "Rabbit.Subscribe", &RRabbitMQ::Subscribe )
    .method( "Rabbit.Publish", &RRabbitMQ::Publish )
    .method( "Rabbit.Consume", &RRabbitMQ::Consume )
    ;
}
