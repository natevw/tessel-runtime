var tap = require('../tap');

tap.count(2);

var foo = 5;
tap.eq(foo.hasOwnProperty('bar'), false);

foo = true;
tap.eq(foo.hasOwnProperty('bar'), false);
