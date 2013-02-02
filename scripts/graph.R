#!/usr/bin/env Rscript

require(ggplot2)
require(plyr)

out <- commandArgs(trailingOnly = TRUE)[1]

raw_data <- read.csv("stdin")
d <- ddply(raw_data, .(Name, Digits), summarize,
           Time = median(Time))

pdf(file=out)

p <- ggplot(d, aes(x=Digits, y=Time, colour=Name)) +
       geom_line() +
       scale_y_continuous(limits=c(0, max(d$Time))) +
       scale_x_discrete() +
       scale_colour_brewer(palette="Set1") +
       theme_bw()
print(p)

dev.off()