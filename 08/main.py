#! /usr/bin/env python3
from faker import Faker
import pytest
import cjson
import json
import ujson
from datetime import datetime
from random import randint
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


def test_load_digit():
    faker = Faker()
    json_test = {}
    for _ in range(1000):
        json_test[faker.first_name()] = randint(1, 10)
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



def test_dumps():
    faker = Faker()
    json_test = {}
    for _ in range(1000):
        json_test[faker.first_name()] = faker.last_name()
    #--------------------------------#
    start=datetime.now()
    jj = json.dumps(json_test)
    #--------------------------------#
    start=datetime.now()
    cj = cjson.dumps(json_test)
    #--------------------------------#
    assert cj == jj



def test_digits():
    faker = Faker()
    json_test = {}
    for _ in range(1000):
        json_test[faker.first_name()] = randint(1, 10)
    #--------------------------------#
    start=datetime.now()
    jj = json.dumps(json_test)
    #--------------------------------#
    start=datetime.now()
    cj = cjson.dumps(json_test)
    #--------------------------------#
    assert cj == jj





