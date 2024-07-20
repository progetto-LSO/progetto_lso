#!/bin/bash

clear;

docker compose -f docker-compose.yml down;
docker compose -f docker-compose.yml down -v;
docker compose -f docker-compose.yml up --build --remove-orphans;