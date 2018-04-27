FROM p7hb/docker-spark

MAINTAINER <oleks@ucu.edu.ua>

COPY target/projectname-0.0.1-jar-with-dependencies.jar /etc/TriangleCounting.jar 
COPY run.sh /etc/run.sh
ENTRYPOINT ["/etc/run.sh"] 