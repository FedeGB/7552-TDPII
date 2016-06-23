import requests
import unittest

class TestAPI(unittest.TestCase):
    def __init__(self, *args, **kwargs):
        super(TestAPI, self).__init__(*args, **kwargs)
        self.apiURL = "http://localhost:8003"
        self.loginURL = "/login"
        self.usersURL = "/users"
	self.messagesURL = "/messages"
	self.conversationsURL = "/conversations"
	self.likesURL = "/likes"


    def test_createUser(self):
        dictDelete = "{\"username\":\"juanmahid\"}"
        r = requests.delete(self.apiURL+self.usersURL, data=dictDelete)
        dict = "{\"username\" : \"juanmahid\", \"password\" : \"hola\", \"name\" : \"juanmahid\", \"sex\": \"M\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        json = r.json()
        self.assertEqual("Registered" , json["message"])
        r = requests.delete(self.apiURL+self.usersURL, data=dictDelete)
        json = r.json()

    def test_getUser(self):
        dict = "{\"username\" : \"juanmahid\", \"password\" : \"hola\", \"name\" : \"juanmahid\", \"sex\": \"M\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
        json = r.json()
	r = requests.get(self.apiURL+self.usersURL + "/juanmahid") 
	json = r.json()
	self.assertEqual("juanma", json["payload"]["name"])
	self.assertEqual("juanma", json["payload"]["alias"])
	self.assertEqual("juanmahid", json["payload"]["username"])
	self.assertEqual("juanmahid", json["payload"]["email"])
	self.assertEqual(12, json["payload"].__len__())

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

    def test_saveMessage(self):
        dict = "{\"username\" : \"juanmahid\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
	dict = "{\"username\":\"pepe\",\"password\":\"hola\",\"name\":\"pepe\"}"
        requests.post(self.apiURL+self.usersURL, data=dict)
	message = "{\"user1\":\"juanmahid\", \"user2\":\"pepe\", \"data\":\"holapepe\" } "
	r = requests.get(self.apiURL + "/users/login", headers={'Authorization': 'Basic anVhbm1haGlkOmhvbGE='})
        json = r.json()
        self.assertEqual("OK" , json["payload"]["result"])
	token = json["payload"]["token"]
	r = requests.post(self.apiURL + self.messagesURL , data=message, headers={'Token': token})
	json = r.json()
	self.assertEqual("Message Saved" , json["message"])

    def test_getAllMessages(self):
        dict = "{\"username\" : \"juanmahid\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
	dict = "{\"username\":\"pepe\",\"password\":\"hola\",\"name\":\"pepe\"}"
        requests.post(self.apiURL+self.usersURL, data=dict)
	message = "{\"user1\":\"juanmahid\", \"user2\":\"pepe\", \"data\":\"holapepe\" } "
	r = requests.get(self.apiURL + "/users/login", headers={'Authorization': 'Basic anVhbm1haGlkOmhvbGE='})
        json = r.json()
        self.assertEqual("OK" , json["payload"]["result"])
	token = json["payload"]["token"]
	r = requests.post(self.apiURL + self.messagesURL , data=message, headers={'Token': token})
	message = "{\"user1\":\"juanmahid\", \"user2\":\"pepe\", \"data\":\"como andas?\" } "
	r = requests.post(self.apiURL + self.messagesURL , data=message, headers={'Token': token})
	message = "{\"user1\":\"juanmahid\", \"user2\":\"pepe\", \"data\":\"yo todo bien\" } "
	r = requests.post(self.apiURL + self.messagesURL , data=message, headers={'Token': token})
	message = "{\"user1\":\"juanmahid\", \"user2\":\"pepe\", \"data\":\"chau\" } "
	r = requests.post(self.apiURL + self.messagesURL , data=message, headers={'Token': token})
	json = r.json()
	self.assertEqual("Message Saved" , json["message"])
	r = requests.get(self.apiURL + "/messages", headers={'Token': token})
	json = r.json()
	messages = json["payload"]["messages"]
	self.assertGreater(messages.__len__() , 3)

    def test_getConversation(self):
	dict = "{\"username\" : \"juanmahid\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
	dict = "{\"username\":\"pepe\",\"password\":\"hola\",\"name\":\"pepe\"}"
        requests.post(self.apiURL+self.usersURL, data=dict)
	message = "{\"user1\":\"juanmahid\", \"user2\":\"pepe\", \"data\":\"holapepe\" } "
	r = requests.get(self.apiURL + "/users/login", headers={'Authorization': 'Basic anVhbm1haGlkOmhvbGE='})
        json = r.json()
        self.assertEqual("OK" , json["payload"]["result"])
	token = json["payload"]["token"]
	r = requests.post(self.apiURL + self.messagesURL , data=message, headers={'Token': token})
	message = "{\"user1\":\"juanmahid\", \"user2\":\"pepe\", \"data\":\"como andas?\" } "
	r = requests.post(self.apiURL + self.messagesURL , data=message, headers={'Token': token})
	message = "{\"user1\":\"juanmahid\", \"user2\":\"pepe\", \"data\":\"yo todo bien\" } "
	r = requests.post(self.apiURL + self.messagesURL , data=message, headers={'Token': token})
	message = "{\"user1\":\"juanmahid\", \"user2\":\"pepe\", \"data\":\"chau\" } "
	r = requests.post(self.apiURL + self.messagesURL , data=message, headers={'Token': token})
	json = r.json()
	r = requests.get(self.apiURL + "/messages", headers={'Token': token})
	json = r.json()
	dict = "{\"user1\":\"juanmahid\", \"user2\":\"pepe\"}"
	r = requests.get(self.apiURL + self.conversationsURL,data=dict, headers={'Token': token, 'user1' : 'juanmahid', 'user2' : 'pepe'})
	json = r.json()
	messages = json["payload"]["messages"]
	self.assertGreater(messages.__len__() , 3)

    def test_sendLike(self):
	dict = "{\"username\" : \"juanmahid\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
	dict = "{\"username\":\"pepe\",\"password\":\"hola\",\"name\":\"pepe\"}"
        requests.post(self.apiURL+self.usersURL, data=dict)
	r = requests.get(self.apiURL + "/users/login", headers={'Authorization': 'Basic anVhbm1haGlkOmhvbGE='})
        json = r.json()
        self.assertEqual("OK" , json["payload"]["result"])
	token = json["payload"]["token"]
	dict = "{\"user1\":\"juanmahid\",\"user2\":\"pepe\",\"like\": true}"
	r = requests.post(self.apiURL + self.likesURL, data=dict, headers={'Token': token})
	json = r.json()
	self.assertEqual("Like Saved", json["message"])	

    def test_getMatches(self):
	dict = "{\"username\" : \"juanmahid\", \"password\" : \"hola\", \"name\" : \"juanma\" }"
        requests.post(self.apiURL+self.usersURL, data=dict)
	dict = "{\"username\":\"pepe\",\"password\":\"hola\",\"name\":\"pepe\"}"
        requests.post(self.apiURL+self.usersURL, data=dict)
	r = requests.get(self.apiURL + "/users/login", headers={'Authorization': 'Basic anVhbm1haGlkOmhvbGE='})
        json = r.json()
        self.assertEqual("OK" , json["payload"]["result"])
	token = json["payload"]["token"]
	dict = "{\"user1\":\"juanmahid\",\"user2\":\"pepe\",\"like\": true}"
	self.assertEqual("Success", json["message"])	
	r = requests.post(self.apiURL + self.likesURL, data=dict, headers={'Token': token})

	r = requests.get(self.apiURL + "/users/login", headers={'Authorization': 'Basic cGVwZTpob2xh'})
        json = r.json()
        self.assertEqual("OK" , json["payload"]["result"])
	token = json["payload"]["token"]
	dict = "{\"user1\":\"pepe\",\"user2\":\"juanmahid\",\"like\": true}"
	self.assertEqual("Success", json["message"])	
	r = requests.post(self.apiURL + self.likesURL, data=dict, headers={'Token': token})
	r = requests.get(self.apiURL + "/users/pepe/matches", headers={'Token': token} )
	json = r.json()
	self.assertTrue("juanmahid" in json["payload"]["matches"])
	
    def test_getCandidates(self):
        dict = "{\"username\" : \"juanmahid\", \"password\" : \"hola\", \"name\" : \"juanmahid\",\"sex\": \"M\" }"
        r = requests.post(self.apiURL+self.usersURL, data=dict)
	#print r.json()
	r = requests.get(self.apiURL + "/users/login", headers={'Authorization': 'Basic anVhbm1haGlkOmhvbGE='})
	#print r.json()
        json = r.json()
        self.assertEqual("OK" , json["payload"]["result"])
	token = json["payload"]["token"]


	dictInteres = "{\"username\" : \"juanmahid\", \"interests\": \" {\"category\":\"music\",\"value\":\"miranda\"  } \" }"
	r = requests.put(self.apiURL+self.usersURL+"/juanmahid", data=dictInteres, 
	headers={'Token': token})
        json = r.json()
        #self.assertEqual("Modified" , json["message"])

	r = requests.get(self.apiURL + "/candidates/juanmahid", headers={'Token': token})
	json = r.json()


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestAPI)
    unittest.TextTestRunner(verbosity=2).run(suite)
