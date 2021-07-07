FROM alpine:3.13.5

RUN apk add build-base upx

WORKDIR /app
COPY . .

RUN make
RUN upx uzr


FROM alpine:3.13.5

RUN apk add --no-cache libstdc++
COPY --from=0 /app/uzr /app/uzr
COPY src/scripts/* /app/scripts/

ARG UZR_ADMIN_USER=
ARG UZR_ADMIN_PW=

RUN adduser -D $UZR_ADMIN_USER
RUN echo "$UZR_ADMIN_USER:$UZR_ADMIN_PW" | chpasswd

CMD /app/uzr
