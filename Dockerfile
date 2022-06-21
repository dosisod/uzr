FROM alpine:3.16.0 AS build

RUN apk add build-base util-linux-dev upx cmake

WORKDIR /app
COPY . .

RUN mkdir build && \
	cd build && \
	cmake .. && \
	cmake --build . && \
	upx uzr

RUN ./build/uzr_migrate


FROM alpine:3.16.0

RUN apk add --no-cache libstdc++ libuuid
COPY --from=build /app/build/uzr /app/uzr

ARG UZR_ADMIN_USER=
ARG UZR_ADMIN_PW=

RUN adduser -D $UZR_ADMIN_USER && echo "$UZR_ADMIN_USER:$UZR_ADMIN_PW" | chpasswd

COPY --from=build /etc/uzr_db.db3 /app/
ENV DB_FILENAME=/app/uzr_db.db3

CMD ["/app/uzr"]
