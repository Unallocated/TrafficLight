#
#import sys    
#sys.path.insert(0, '/usr/lib/python2.7/bridge/') 
#                                                
#from bridgeclient import BridgeClient as bridgeclient
#                                                     
#value = bridgeclient()                              
#                                                     
#value.put('stoplight','valdfgsdfgue') 
#                          
#print value.get('stoplight') 


#!/usr/bin/python

#
#  The Stoplight Server
#
# Crypt0s + Pyr0 for Hackathon0
import pdb
import web
import json as j
import sys
sys.path.insert(0, '/usr/lib/python2.7/bridge/')
from bridgeclient import BridgeClient as bridgeclient

#urls and globals defined below
urls = (
	'/','index'
)
client = bridgeclient()

# handlers for the urls below:
class index:
	def GET(self):
		return "This device expects POST requests!"
	def POST(self):
		data = web.data()
		data = j.loads(data)
		state = data['stoplight']
		state_str = ''
		for x in state:
			state_str = state_str + str(x)
		#pdb.set_trace()
		print state_str
		client.put('stoplight',state_str)
		

# This script expects to be called as main from the command line, like from init.
if __name__ == "__main__":
	app = web.application(urls,globals())
	app.run()
