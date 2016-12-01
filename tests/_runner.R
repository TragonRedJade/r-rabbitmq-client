# asdfa123
library('testthat')
library('devtools')
library('Rcpp')
library('methods')
library('utils')

load_all("/r-rabbitmq")

test_dir('tests', reporter = 'Summary')
