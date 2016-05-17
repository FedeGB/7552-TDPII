import requests
import unittest

class TestAPI(unittest.TestCase):
    def __init__(self, *args, **kwargs):
        super(TestAPI, self).__init__(*args, **kwargs)
        self.apiURL = "http://localhost:8000"
        self.loginURL = "/login"

    def test_login(self):
        credentials = {"username":"juan","password":"hola"}
        dict = {'user' : "gustavito", 'password' : "hola"}
        r = requests.get(self.apiURL + self.loginURL, params=dict)
        json = r.json()
        print json
        #self.assertEqual("ERROR" , json["result"])
        #self.assertEqual(1 , json["code"])

if __name__ == '__main__':
    unittest.main()
