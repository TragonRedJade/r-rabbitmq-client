
#ifndef RRabbitMessage_hpp
#define RRabbitMessage_hpp

#include <stdio.h>
#include <string>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <Rcpp.h>


class RabbitMessage{
private:

public:
    std::string Body;
    Rcpp::List Headers;
    std::string RoutingKey;
    // Rcpp::traits::named_object<std::string> Evan;
    // std::map< Testing;
    // std::map<std::string, std::string> Testing;

};

// template <> SEXP wrap(const BassicMessage &obj) { // insprired from "make_new_object" from Rcpp/Module.h
//   Rcpp::XPtr<A> xp( new BassicMessage(obj), true ) ; // copy and mark as finalizable
//   Function maker=Environment::Rcpp_namespace()[ "cpp_object_maker"];
//   return maker ( typeid(BassicMessage).name() , xp );
// }
//

#endif /* IRRabbitMQ_hpp */
