FROM node:7.8.0

COPY . .

RUN npm install -g bs-platform serve

RUN yarn build

CMD ["serve", "-s", "build", "-p", "8080"]