client = new(RabbitClient)

message="mooo"
queue_name="rabbit_client_tests"

###########################
# SETUP
###########################
expect_that(client$DefaultExchange, equals(""))
expect_that(client$Connect(Sys.getenv("RABBITMQ_SERVICE_HOST"), as.integer(Sys.getenv("RABBITMQ_SERVICE_PORT")), Sys.getenv("RABBITMQ_USER"), Sys.getenv("RABBITMQ_PASSWORD")), equals(TRUE))


############################
# Test for failure handling
############################
expect_error(client$Connect("non_existent_rabbit_host", 5672, "guest", "guest"), ".*")
expect_error(client$Publish("non_existent_queue", message), ".*")
expect_error(client$Subscribe("non_existent_queue"), ".*")
expect_error(client$Consume(), ".*")


############################
# Test for success
############################
expect_that(client$DeclareQueue(queue_name, FALSE, FALSE, FALSE, TRUE), equals(TRUE))
expect_that(client$Publish(queue_name, message), equals(TRUE))
expect_that(client$IsChannelOpen(), equals(TRUE))
expect_that(client$Subscribe(queue_name),equals(TRUE))

response = client$Consume()
expect_that(response$Body,equals(message))
expect_that(response$RoutingKey, equals(queue_name))
expect_that(length(response$Headers),equals(0))


#tasdf thies dfasdf
