#! /usr/bin/env python3
from faker import Faker
import pytest
import cjson
import json
import ujson
from pprint import pprint
from random import randint
from datetime import datetime

def test_load():
    faker = Faker()
    json_test = {}
    for _ in range(1000):
        json_test[faker.first_name()] = faker.last_name()
    json_test = ujson.dumps(json_test)
    #---------TEST_VALUE AND TIME--------#
    uj = ujson.loads(json_test)
    #---------------------------------------#
    start=datetime.now()
    jj = json.loads(json_test)
    js_time = datetime.now()-start
    #---------------------------------------#
    start=datetime.now()
    cj = cjson.load(json_test)
    cj_time = datetime.now()-start

    
    assert uj == jj == cj
    assert js_time > cj_time # В 1/10 не пройдет.


