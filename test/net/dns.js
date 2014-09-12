var tap = require('../tap');

tap.count(2);

var dns = require('dns');

dns.resolve('graph.facebook.com', function (err, ip) {
	tap.ok(!err);
	tap.ok(ip == null || Array.isArray(ip));
	console.log('#', ip);
})