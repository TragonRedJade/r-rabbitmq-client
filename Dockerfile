FROM r-base

# install all the dependancies for SimpleAmqpClient
RUN apt-get update \
  && apt-get install -y git-core libboost-all-dev librabbitmq-dev cmake \
  && rm -rf /var/lib/apt/lists/*


# compile & install SimpleAmqpClient
RUN mkdir /code \
  && cd /code \
  && git clone https://github.com/alanxz/simpleamqpclient.git \
  && cd simpleamqpclient \
  && mkdir simpleamqpclient-build \
  && cd simpleamqpclient-build \
  && cmake .. \
  && make install
ENV LD_LIBRARY_PATH /usr/local/lib/


# install the R dependancies
RUN R -e "install.packages('Rcpp', repos='http://cran.rstudio.com/')"

# copy the code
RUN mkdir /app
WORKDIR /app
COPY . ./
