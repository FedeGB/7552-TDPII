import requests
import unittest

class TestAPI(unittest.TestCase):
    def __init__(self, *args, **kwargs):
        super(TestAPI, self).__init__(*args, **kwargs)
        self.apiURL = "http://localhost:8000"
        self.loginURL = "/login"
        self.usersURL = "/users"


    def test_login(self):
        dict = {'user' : "gustavito", 'password' : "hola"}
        r = requests.get(self.apiURL + self.loginURL, params=dict)
        json = r.json()
        self.assertEqual("OK" , json["payload"]["result"])

    def test_createUser(self):
        dict = "{\"username\" : \"juanmita\", \"password\" : \"hola\", \"name\" : \"juanmita\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        self.assertEqual("Registered" , json["message"])

    def test_updateUser(self):
        dict = "{\"username\" : \"juanmita\", \"password\" : \"hola\", \"name\" : \"juanmita\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        dict = "{\"password\" : \"holaa\"}"
        r = requests.put(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        self.assertEqual("Modified" , json["message"])

    def test_deleteUser(self):
        dict = "{\"username\":\"juanmita\"}"
        r = requests.delete(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        self.assertEqual("Deleted" , json["message"])


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestAPI)
    unittest.TextTestRunner(verbosity=2).run(suite)
