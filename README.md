# Home Automator for RPi 3

Home Automator MQTT service for the RPi

## Docker

Check out [Installing Docker on the RPi](docs/docker.md) for setting up Docker on the RPi.

### Building the image

Clone the git repo on the RPi and build the image

```shell
cd && git clone https://github.com/BioBoost/home_automator_rpi.git
cd home_automator_rpi
docker build -t home_automator .
```

You can force a rebuild using the command below
```shell
docker build --no-cache -t home_automator .
```

### Running the docker image

By passing the `privileged` we give the docker image access to GPIO and I2C
```shell
docker run -d --privileged --restart unless-stopped --name automator home_automator
```

### Development with Docker-compose

To get a development build environment fire the docker container up as follows:

```shell
docker-compose run build /bin/bash
```

Now you get a bash shell to start building using make. Once finished and you wish to start the container normally:

```shell
docker-compose -d up
```