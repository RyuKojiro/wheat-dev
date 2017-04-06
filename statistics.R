#!/usr/bin/Rscript

data = read.table("send_statistics.txt")
colnames(data) <- c("time","addresss", "rate")
start = data$time[1]
Adjust <- function(x) ((x - start)/1000)
normalized = data.frame(apply(data['time'],2,Adjust), data$address, data$rate)
plot(normalized$time, data$rate, main="Rate over Time", xlab="Time (sec)", ylab="Rate (bytes/sec)")
plot(data$address, data$rate, main="Rate over Address", xlab="Address (bytes)", ylab="Rate (bytes/sec)")
plot(normalized$time, data$address, main="Progress over Time", xlab="Time (sec)", ylab="Address (bytes)")
