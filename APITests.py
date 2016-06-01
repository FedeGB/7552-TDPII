import requests
import unittest

class TestAPI(unittest.TestCase):
    def __init__(self, *args, **kwargs):
        super(TestAPI, self).__init__(*args, **kwargs)
        self.apiURL = "http://localhost:8000"
        self.loginURL = "/login"
        self.usersURL = "/users"


    def test_login(self):
        dict = "{\"username\" : \"juanma\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        dict = {'user' : "juanma", 'password' : "hola"}
        r = requests.get(self.apiURL + self.loginURL, params=dict)
        json = r.json()
        self.assertEqual("OK" , json["payload"]["result"])

    def test_createUser(self):
        dict = "{\"username\":\"juanma\"}"
        r = requests.delete(self.apiURL+self.usersURL, data=dict)
        dict = "{\"username\" : \"juanma\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        self.assertEqual("Registered" , json["message"])
        r = requests.delete(self.apiURL+self.usersURL, data=dict)
        json = r.json()

    def test_updateUser(self):
        dict = "{\"username\" : \"juanma\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        dict = "{\"username\": \"juanma\", \"password\" : \"holaa\"}"
        r = requests.put(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        self.assertEqual("Modified" , json["message"])

    def test_deleteUser(self):
        dict = "{\"username\" : \"juanma\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        dict = "{\"username\":\"juanma\"}"
        r = requests.delete(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        self.assertEqual("Deleted" , json["message"])

    def test_getAllUsers(self):
        dict = "{\"username\" : \"juanma\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
        dict = "{\"username\" : \"carlos\", \"password\" : \"hola\", \"name\" : \"carlos\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
        r = requests.get(self.apiURL + self.usersURL)
        json = r.json()
        self.assertEqual(json["payload"]["Users"].__len__() , json["message"])

    def test_saveMessage(self):
        user1 = "{\"username\" : \"juanma\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
		user2 = "{\"username\":\"pepe\",\"password\":\"hola\",\"name\":\"pepe\"}"
        requests.post(self.apiURL+self.usersURL, data=dict)

		message = "{ \"user1\":\"juanma\", \"user2\":\"pepe\", \"data\":\"hola pepe\" } "
		r = requests.post(self.__api_base_url + self.__message_url , headers = credentials, data = message)
		json = r.json()
		self.assertEqual("OK", json["result"])
		self.assertEqual("mateobosco" , json["data"]["emisor"])
		self.assertEqual("pepe", json["data"]["receptor"])
		self.assertEqual("mensaje para pepe" , json["data"]["body"])



if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestAPI)
    unittest.TextTestRunner(verbosity=2).run(suite)
