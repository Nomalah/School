const express = require("express");
const fs = require("fs");
const app = express();

app.use((req, res, next) => {
    res.append('Access-Control-Allow-Origin', ['*']);
    res.append('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.append('Access-Control-Allow-Headers', 'Content-Type');
    next();
});

app.get("/nodes.json", (req, res) => {
    console.log("requested nodes.json");
    fs.readFile("nodes.json", (err, data) => {
        res.send(data);
    });
});

app.get("/edges.json", (req, res) => {
    console.log("requested edges.json");
    fs.readFile("edges.json", (err, data) => {
        res.send(data);
    });
});

app.listen(3000, () => {
    console.log("listening on 3000");
});