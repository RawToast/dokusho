FROM node:8.9.4

RUN npm install -g serve react-scripts

COPY package.json yarn.lock bsconfig.json  ./

RUN yarn

COPY public ./public

COPY src ./src

RUN yarn && npm link bs-platform && yarn build

CMD ["serve", "-s", "build", "-p", "3000"]
