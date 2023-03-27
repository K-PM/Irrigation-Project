import express from 'express';
import Logs from './model.mjs';
import { Server } from 'socket.io';
import http from 'http';

const port = 80;

const app = express();
const server = http.createServer(app)
const io = new Server(server)

const users = {}

const __dirname__ = process.cwd()

console.log(__dirname__)

app.post("/data/:humA/:humD/:riego", (req, res) => {
    Logs.create({
        humA: req.params.humA,
        humD: req.params.humD,
        riego: req.params.riego,

    })
    for (const key in users) {
        console.log(key)
        users[key].emit("updateData", {
            humA: req.params.humA,
            humD: req.params.humD,
            riego: req.params.riego,
        })
    }
    res.send("Info received")
})

app.use(express.static(`${__dirname__}/public`))

app.get("/", (req, res) => {
    res.sendFile(`${__dirname__}/public/index.html`)
})

io.on("connect", (socket) => {
    users[socket.id] = socket;
    socket.on('disconnect', () => {
        delete users[socket.id]
    })
})

server.listen(port, () => {
    console.log(`Server listening on port ${port}`)
})