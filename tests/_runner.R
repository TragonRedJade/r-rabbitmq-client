library('testthat')
library('devtools')
library('Rcpp')
library('methods')
library('utils')

load_all(".")

test_dir('tests', reporter = 'Summary')
