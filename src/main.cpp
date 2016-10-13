//
//  main.cpp
//  RabbitTest
//
//  Created by Evan Lemke on 9/19/16.
//  Copyright © 2016 Evan Lemke. All rights reserved.
//

#include "rrabbitmq.hpp"
#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

using namespace std;

int main(int argc, const char * argv[]) {

    cout << "Hello, World!\n";

    RRabbitMQ client;
    client.Connect("rabbitmq");

    cout << "connected \n";

    client.Publish("calcs_queue", "poop");
    client.Publish("calcs_queue", "stuff");

    string message;
    client.Subscribe("calcs_queue");
    message = client.Consume();

    cout << "Message: " << message << "\n";
    cout << "Ze End! \n";
    return 0;
}
