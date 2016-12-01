client = new(RabbitClient)

message="mooo"
queue_name="calcs_queue"

###########################
# SETUP
###########################
expect_that(client$DefaultExchange, equals(""))
expect_that(client$Connect("rabbitmq",5672,"guest","guest"), equals(TRUE))



############################
#Test for failure handling
############################
expect_error(client$Connect("non_existent_rabbit_host",5672,"guest","guest"), ".*")
expect_error(client$Publish("non_existent_queue", message), ".*")
expect_error(client$Subscribe("non_existent_queue"), ".*")
expect_error(client$Consume(), ".*")


############################
#Test for success
############################
expect_that(client$DeclareQueue(queue_name, TRUE, FALSE, TRUE, TRUE), equals(TRUE))
expect_that(client$Publish(queue_name, message), equals(TRUE))
expect_that(client$Subscribe(queue_name),equals(TRUE))
expect_that(client$Consume(), equals(message))
#tasdf thies dfasdf
