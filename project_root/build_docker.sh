#!/bin/bash

clear;

docker compose down -v;
docker compose --build --remove-orphans;