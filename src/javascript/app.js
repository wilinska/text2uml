const http = require("http");
const express = require("express");
const path = require("path");
const bodyParser = require("body-parser");

const { createMainRouteHandler } = require("./routes/mainRoute");
const app = express();

app.set("views", "./src/javascript/views/");
app.set("view engine", "ejs");

app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, "assets")));
app.use(express.urlencoded({ extended: true }));

const Library = require(`./dist/wasm/umd`);
let Text2UML;

(async () => {
  Text2UML = await Library();

  // Funkcje helper dla zarządzania stanem WASM
  const getWasmModule = () => Text2UML;
  const reinitWasm = async () => {
    Text2UML = null;
    if (global.gc) global.gc();
    Text2UML = await Library();
  };

  // Konfiguracja routingu
  app.get("/", createMainRouteHandler(getWasmModule, reinitWasm));

  http.createServer(app).listen(3000);
  console.log("Server listening on port:3000");
})();