FROM nodered/node-red
COPY package.json .
COPY Administrador/flows_Administrador.json /data
RUN npm install --unsafe-perm --no-update-notifier --no-fund --only=production