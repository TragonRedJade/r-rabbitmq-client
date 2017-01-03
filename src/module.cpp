#include "rabbitclient.hpp"
#include "rabbitmessage.hpp"

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <Rcpp.h>
#include <R.h>

using namespace Rcpp;


RCPP_EXPOSED_CLASS(RabbitMessage)

RCPP_MODULE(RabbitClient) {
  class_<RabbitMessage>( "RabbitMessage" )
    .constructor()

    .field( "Body", &RabbitMessage::Body)
    .field( "Headers", &RabbitMessage::Headers)
    .field( "RoutingKey", &RabbitMessage::RoutingKey)

    ;
  class_<RabbitClient>( "RabbitClient" )
    .constructor()

    .field( "DefaultExchange", &RabbitClient::DefaultExchange)

    .method( "Connect", &RabbitClient::Connect)
       //,List::create( _["host"]="localhost", _["port"] = 5672, _["username"] = "guest", _["password"] = "guest", _["vhost"] = "/", _["frame_max"] = 131072)
    .method( "DeclareQueue", &RabbitClient::DeclareQueue)
      // ,List::create( _["queue_name"], _["passive"] = false, _["durable"] = false, _["exclusive"] = true, _["auto_delete"] = true))
    .method( "Subscribe", &RabbitClient::Subscribe)
      // ,List::create(_["queue_name"] = "poop")
    .method( "Publish", &RabbitClient::Publish )
    .method( "Consume", &RabbitClient::Consume )
    ;
}
