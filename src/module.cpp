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

    .method( "BasicAck", &RabbitMessage::BasicAck)
    .method( "BasicReject", &RabbitMessage::BasicReject)

    ;
  class_<RabbitClient>( "RabbitClient" )
    .constructor()

    .method( "Connect", &RabbitClient::Connect)
    .method( "IsOpen", &RabbitClient::IsOpen )
    .method( "Subscribe", &RabbitClient::Subscribe)
    .method( "Unsubscribe", &RabbitClient::Unsubscribe)


    .method( "DeclareExchange", &RabbitClient::DeclareExchange)
    .method( "DeleteExchange", &RabbitClient::DeleteExchange)
    .method( "BindExchange", &RabbitClient::BindExchange)
    .method( "UnbindExchange", &RabbitClient::UnbindExchange)

    .method( "DeclareQueue", &RabbitClient::DeclareQueue)
    .method( "DeleteQueue", &RabbitClient::DeleteQueue)
    .method( "BindQueue", &RabbitClient::BindQueue)
    .method( "UnbindQueue", &RabbitClient::UnbindQueue)
    .method( "PurgeQueue", &RabbitClient::PurgeQueue)

    .method( "Publish", &RabbitClient::Publish )
    .method( "Consume", &RabbitClient::Consume )

    ;
}
