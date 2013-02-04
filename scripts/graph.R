#!/usr/bin/env Rscript

require(ggplot2)
require(plyr)

out <- commandArgs(trailingOnly = TRUE)[1]

raw_data <- read.csv("stdin")
d <- ddply(raw_data, .(Name, Digits), summarize,
           Time = median(Time))

png(filename=paste0(out, ".png"), width=800, height=600)

p <- ggplot(d, aes(x=Digits, y=Time, colour=Name)) +
       geom_line() +
       scale_x_discrete() +
       theme_bw()
print(p)

dev.off()