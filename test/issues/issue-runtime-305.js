var tap = require('../tap')

tap.count(1)

tap.eq(global._G && global._G._HSMATCH, null, '_HSMATCH object should not be accessible');
