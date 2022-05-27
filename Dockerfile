FROM alpine:3.15.2 AS build

RUN apk add build-base upx cmake

WORKDIR /app
COPY . .

RUN mkdir build && \
	cd build && \
	cmake .. && \
	cmake --build . && \
	upx uzr && \
	cp uzr ..


FROM alpine:3.15.2

RUN apk add --no-cache libstdc++
COPY --from=build /app/uzr /app/uzr
COPY src/scripts/* /app/src/scripts/

ARG UZR_ADMIN_USER=
ARG UZR_ADMIN_PW=

RUN adduser -D $UZR_ADMIN_USER && echo "$UZR_ADMIN_USER:$UZR_ADMIN_PW" | chpasswd

CMD ["/app/uzr"]
