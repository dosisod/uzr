# Uzr

A very small user management service built on [cpp-httplib](https://github.com/yhirose/cpp-httplib).

# Installing, Building, and Running

Requires cmake >= 3.21.3, and a compiler which supports C++20.

To run manually:

```
$ git clone https://github.com/dosisod/uzr
$ cd uzr
$ mkdir build && cd build
$ cmake .. && cmake --build .
$ ./uzr
```

Via `docker-compose`:

```
$ docker-compose up --build
```
