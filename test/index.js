const cherver = require("bindings")("cherver");

const PORT = 8000;

const http_server = cherver.create_server();
http_server.listen(PORT, function (req, res) {
  if (req.url === "/") res.write_head(200);
  else res.write_head(404);
});
