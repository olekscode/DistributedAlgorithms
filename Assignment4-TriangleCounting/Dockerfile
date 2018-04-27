FROM p7hb/docker-spark

MAINTAINER <oleks@ucu.edu.ua>

COPY target/TriangleCounting-0.0.1-jar-with-dependencies.jar /etc/TriangleCounting.jar
COPY src/main/resources/followers.txt /etc/followers.txt
COPY run.sh /etc/run.sh

RUN chmod -R 700 /etc

ENTRYPOINT ["/etc/run.sh"] 