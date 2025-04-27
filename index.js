const cherver = require('bindings')('cherver');

module.exports.create_server = function(){
    cherver.create_server();
}
