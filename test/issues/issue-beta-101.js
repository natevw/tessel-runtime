var tap = require('../tap');

tap.count(2);

var arr =  [ 0, 13, 2, 1, 21, 0, 0, 0, 0, 0, 6, 104, 105, 32, 106, 111, 110 ];
var val = new Buffer(arr).slice(7);

tap.eq(val.length, 10);
console.log('#', val);
tap.eq(new Buffer('hello').toString(), 'hello');
console.log('#', new Buffer('hello').toString())