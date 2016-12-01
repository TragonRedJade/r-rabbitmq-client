#include "rabbitclient.hpp"
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <Rcpp.h>
#include <R.h>

using namespace Rcpp;

double add( double x, double y ) {
  return x+y;
}
RCPP_MODULE(Evan) {
function( "add", &add,
List::create( _["x"], _["y"] = 4.0 ),
"Provides a simple vector norm"
);
}

RCPP_MODULE(RabbitClient) {
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
