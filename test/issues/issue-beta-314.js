var tap = require('../tap');

tap.count(1);

var dict = {};
var a = {len: 1, arr: []};
var b = {len: 1, arr: []};
var c = {len: 1, arr: []};
dict['1'] = b;
dict['2'] = c;
dict['0'] = a;
console.log('#', dict)
console.log('#', Object.keys(dict))
tap.ok(Object.keys(dict).length > 1);
