client = new(RabbitClient)

message="mooo"
queue_name="rabbit_client_tests"
exchange_name="rabbit_client_tests_exchange"
routing_key="rabbit_client_routing_key"

###########################
# SETUP
###########################
expect_that(client$Connect(Sys.getenv("RABBITMQ_SERVICE_HOST"), as.integer(Sys.getenv("RABBITMQ_SERVICE_PORT")), Sys.getenv("RABBITMQ_USER"), Sys.getenv("RABBITMQ_PASSWORD")), equals(TRUE))
# expect_that(client$IsOpen(), equals(TRUE))

############################
# Test for failure handling
############################
expect_error(client$Connect("non_existent_rabbit_host", 5672, "guest", "guest"), ".*")
expect_error(client$Publish("non_existent_queue", "", message, NULL), ".*")
expect_error(client$Subscribe("non_existent_queue", "", FALSE, TRUE, 1), ".*")
expect_error(client$Consume(), ".*")

############################
# Test for success
############################
expect_that(client$DeclareExchange(exchange_name, "direct", FALSE, FALSE, FALSE), equals(TRUE))
expect_that(client$BindExchange(exchange_name, exchange_name, ""), equals(TRUE))
expect_that(client$UnbindExchange(exchange_name, exchange_name, ""), equals(TRUE))

expect_that(client$DeclareQueue(queue_name, FALSE, FALSE, FALSE, FALSE), equals(TRUE))
expect_that(client$BindQueue(queue_name, exchange_name, routing_key), equals(TRUE))
expect_that(client$Publish(exchange_name, routing_key, message, NULL), equals(TRUE))
expect_that(client$Subscribe(queue_name, "RABBITMQ_CLIENT_UNIT_TESTS", FALSE, TRUE, 1),equals(TRUE))

response = client$Consume()
expect_that(response$BasicReject(TRUE, FALSE),equals(TRUE))
response = client$Consume()
expect_that(response$BasicAck(),equals(TRUE))
expect_that(response$Body,equals(message))
expect_that(response$RoutingKey, equals(routing_key))
expect_that(length(response$Headers),equals(0))

# ############################
# # Clean-up
# ############################
expect_that(client$Unsubscribe(),equals(TRUE))
expect_that(client$PurgeQueue(queue_name), equals(TRUE))
expect_that(client$UnbindQueue(queue_name, exchange_name, ""), equals(TRUE))
expect_that(client$DeleteQueue(queue_name, FALSE, FALSE), equals(TRUE))
expect_that(client$DeleteExchange(exchange_name, FALSE), equals(TRUE))


#
# #tasdf thies dfasdf
