FROM nodered/node-red
COPY package.json .
COPY Experimentador/flows_Experimentador.json /data
RUN npm install --unsafe-perm --no-update-notifier --no-fund --only=production