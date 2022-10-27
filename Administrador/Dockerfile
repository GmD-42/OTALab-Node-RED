FROM nodered/node-red
COPY package.json .
COPY Administrador/flows_Administrador.json /data/flows.json
RUN npm install --unsafe-perm --no-update-notifier --no-fund --only=production