================
 itoa benchmark
================

In this benchmark we are trying to find the fastest implementation of
`itoa(uint64_t, char *buf)`


Compiling
=========

::

    $ mkdir build
    $ cd build
    $ cmake -DCMAKE_BUILD_TYPE=Release ..
    $ make

Running Benchmarks
==================

To run benchmarking script you need to install `R language
<http://www.r-project.org/>`_ and `ggplot2 <http://ggplot2.org/>`_.

Make sure that you `set cpu frequency
<https://wiki.archlinux.org/index.php/CPU_Frequency_Scaling>`_ to
fixed value and disable any turbo mode, so the results of the
benchmark should be more accurate.

And then you can run the benchmark. It will generate .png files in the
current directory.

::

    $ cd scripts
    $ ./benchmark.sh


Benchmark details
=================

Each algorithm is compiled in its own benchmarking application and
testing application.

Benchmarking application support positional arguments:

 - inner loop counter [default=1]
 - number of digits [default=iterate through all possible values]

Testing application can be launched in two modes: simple testing and
random testing. For simple testing, just launch the application, and
for random testing launch application with an integer argument, it
will be used as a seed for random number generator.

benchmark.sh
++++++++++++

This script run benchmarks in two modes(cold, hot) and collect data
from it.

In the cold mode, it runs benchmark application for 10 times with
arguments (inner loop counter=1, digits=<all
values for current integer size>).

In the hot mode, it runs benchmark application for 100 times with
arguments (inner loop counter=100).

And then generates graphical representation of the collected data. As
a time value it uses median of all time values for each (benchmark,
digits).

Benchmarking results
====================

Linux, gcc 4.7.2 (core i5-3570k)
++++++++++++++++++++++++++++++++

Cold
----

.. image:: https://raw.github.com/localvoid/cxx-benchmark-itoa/master/results/linux/gcc_4_7/i5_3570k/cold.png

Hot
---

.. image:: https://raw.github.com/localvoid/cxx-benchmark-itoa/master/results/linux/gcc_4_7/i5_3570k/hot.png

