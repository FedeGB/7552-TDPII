import requests
import unittest

class TestAPI(unittest.TestCase):
    def __init__(self, *args, **kwargs):
        super(TestAPI, self).__init__(*args, **kwargs)
        self.apiURL = "http://localhost:8003"
        self.loginURL = "/login"
        self.usersURL = "/users"



    def test_createUser(self):
        dictDelete = "{\"username\":\"juanmahid\"}"
        r = requests.delete(self.apiURL+self.usersURL, data=dictDelete)
	print r.json()
        dict = "{\"username\" : \"juanmahid\", \"password\" : \"hola\", \"name\" : \"juanmahid\", \"sex\": \"M\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        json = r.json()
	print json
        self.assertEqual("Registered" , json["message"])
        r = requests.delete(self.apiURL+self.usersURL, data=dictDelete)
        json = r.json()

    def test_deleteUser(self):
        dict = "{\"username\" : \"juanma\", \"password\" : \"hola\", \"name\" : \"juanma\", \"sex\": \"M\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        dict = "{\"username\":\"juanma\"}"
        r = requests.delete(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        self.assertEqual("Deleted" , json["message"])

    def test_updateUser(self):
        dict = "{\"username\" : \"juanmahid\", \"password\" : \"hola\", \"name\" : \"juanmahid\", \"sex\": \"M\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        r = requests.get(self.apiURL + "/users/login", headers={'Authorization': 'Basic anVhbm1haGlkOmhvbGE='})
        json = r.json()
        self.assertEqual("OK" , json["payload"]["result"])
	token = json["payload"]["token"]
        dict = "{\"username\": \"juanmahid\", \"password\" : \"holaa\"}"
        r = requests.put(self.apiURL+self.usersURL+"/juanmahid", data=dict, 
	headers={'Token': token})
        json = r.json()
        self.assertEqual("Modified" , json["message"])

    def test_login(self):
        dict = "{\"username\" : \"juanmahid\", \"password\" : \"hola\", \"name\" : \"juanmahid\", \"sex\": \"M\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        r = requests.get(self.apiURL + "/users/login", headers={'Authorization': 'Basic anVhbm1haGlkOmhvbGE='})
        json = r.json()
        self.assertEqual("OK" , json["payload"]["result"])

    def test_getAllUsers(self):
        dict = "{\"username\" : \"juanma\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
        dict = "{\"username\" : \"carlos\", \"password\" : \"hola\", \"name\" : \"carlos\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
	dict = "{\"username\" : \"jose\", \"password\" : \"hola\", \"name\" : \"jose\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
        dict = "{\"username\" : \"alberto\", \"password\" : \"hola\", \"name\" : \"alberto\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
        r = requests.get(self.apiURL + self.usersURL)
        json = r.json()
        self.assertGreater(json["payload"]["Users"].__len__() , 3)



if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestAPI)
    unittest.TextTestRunner(verbosity=2).run(suite)
