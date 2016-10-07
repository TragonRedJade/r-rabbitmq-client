
library(Rcpp)
Sys.getenv("LD_LIBRARY_PATH")
Sys.setenv(LD_LIBRARY_PATH = "/usr/local/lib")

sourceCpp("~/Code/rrabbitmq/src/rrabbitmq.cpp")
getwd()

sourceCpp('~/Code/rrabbitmq/src/doubler.cpp')
#double_me(3)

ldd
