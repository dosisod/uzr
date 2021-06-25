FROM alpine:3.13.5

RUN apk add build-base

WORKDIR /app
COPY . .

RUN make


FROM alpine:3.13.5

RUN apk add --no-cache libstdc++
COPY --from=0 /app/uzr /app/uzr

CMD /app/uzr
