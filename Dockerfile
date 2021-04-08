# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    DockerFile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 16:17:30 by fgalaup           #+#    #+#              #
#    Updated: 2021/04/08 16:17:31 by fgalaup          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

FROM debian:buster-slim
RUN apt-get update && apt-get -y upgrade && apt-get install -y git build-essential clang valgrind \
    && mkdir -m 666 /project
WORKDIR /project