FROM nodered/node-red
COPY package.json .
RUN npm install --unsafe-perm --no-update-notifier --no-fund --only=production