FROM resin/rpi-raspbian:stretch-20180815
ENTRYPOINT []

# Configure the main working directory. This is the base
# directory used in any further RUN, COPY, and ENTRYPOINT
# commands.
WORKDIR /app

RUN apt-get update && \
    apt-get -qy install git build-essential gcc make cmake cmake-gui cmake-curses-gui libssl-dev \
       libcurl4-gnutls-dev dh-autoreconf wget

RUN cd /usr/local/src && \
    git clone https://github.com/eclipse/paho.mqtt.c.git && \
    cd paho.mqtt.c && \
    git checkout v1.2.1 && \
    make && \
    make install

RUN cd /usr/local/src && \
    git clone https://github.com/eclipse/paho.mqtt.cpp.git && \
    cd paho.mqtt.cpp && \
    git checkout v1.0.0 && \
    make

# Install paho C++ libraries (no make install)
RUN cd /usr/local/src/paho.mqtt.cpp && \
    install -m 644 lib/libpaho-mqttpp3.so.1.0.0 /usr/local/lib/ && \
    /sbin/ldconfig /usr/local/lib && \
    cd /usr/local/lib && \
    ln -s libpaho-mqttpp3.so.1 libpaho-mqttpp3.so && \
    cp -r /usr/local/src/paho.mqtt.cpp/src/mqtt /usr/local/include && \
    chmod 644 /usr/local/include/mqtt/* && \
    echo '/usr/local/lib' | tee /etc/ld.so.conf.d/mqttpp.conf && \
    /sbin/ldconfig

RUN cd /usr/local/src && \
    git clone https://github.com/BioBoost/wiringPi.git && \
    cd wiringPi && git checkout 69b90a0964c0996469e399824c9d63707ff1e497 && \
    ./build

RUN cd /usr/local/include/ && \
    wget https://raw.githubusercontent.com/nlohmann/json/v3.2.0/single_include/nlohmann/json.hpp

RUN cd /usr/local/src && \
    git clone https://github.com/BioBoost/thread_safe.git && \
    cd thread_safe && git checkout v1.0.0 && \
    cp -r include/thread_safe /usr/local/include

# Doesnt seem like hes using tags like he should
RUN cd /usr/local/src && \
    git clone https://github.com/mrtazz/restclient-cpp.git && \
    cd restclient-cpp && \
    git checkout bdf5335cae8b879a8116cb8053828aff5d9544d2 && \
    ./autogen.sh && \
    ./configure && \
    make install

RUN cd /usr/local/src && \
    git clone https://github.com/BioBoost/bios_logger.git && \
    cd bios_logger && \
    git checkout v1.1.1 && \
    make && \
    make install

RUN cd /usr/local/src && \
    git clone https://github.com/BioBoost/simple_mqtt_client.git && \
    cd simple_mqtt_client && \
    git checkout v1.0.0 && \
    make && \
    make install

# Copy the current version of the main application
# COPY . .

# Ur get the latest stable version of master branch
RUN git clone https://github.com/BioBoost/home_automator_rpi.git .
RUN make clean && make

CMD ./bin/home_automator