import cherrypy
from _movie_database import _movie_database
import json


class Movies(object):

	@cherrypy.tools.json_in()
	def __init__(self):
		self.API_KEY = 'AAAAAAAB'
		self.myDB = _movie_database()
		self.myDB.delete_all_ratings()
                self.myDB.load_movies('ml-1m/movies.dat')
                self.myDB.load_users('ml-1m/users.dat')
                self.myDB.load_ratings('ml-1m/ratings.dat')
		self.myDB.load_posters('images.dat')

	
	
	def GET(self,id=None):
		output = {'result':'success'}
		mov = self.myDB.get_movie(id)
		if mov is None:
			output['result'] = 'error'
			output['message'] = 'key not found'
		else:
			output['id'] = id
			output['genres'] = mov[1]
			output['title'] = mov[0]
			output['img'] = self.myDB.get_poster_by_id(id)

		return json.dumps(output,encoding = 'latin-1')

	def PUT(self,id=None):
		output = {'result':'success'}
		v = json.loads(cherrypy.request.body.read())
		if v['apikey'] == self.API_KEY:
			info = []
			info.append(v['title'])
			info.append(v['genres'])
			self.myDB.set_movie(id,info)
		else:
			output['result'] = 'failure'
		return json.dumps(output,encoding = 'latin-1')
	def GET_ALL(self):
		output = {'result':'success'}
		output['movies'] = []
		for key in self.myDB.get_movies():
			mov = self.myDB.get_movie(key)
			if mov is not None:
				info = {}
				info['id'] = int(key)
				info['genres'] = mov[1]
				info['title'] = mov[0]
				info['img'] = self.myDB.get_poster_by_id(key)
				output['movies'].append(info)
		return json.dumps(output,encoding = 'latin-1')

	def POST(self):
		output = {'result':'success'}
		v = json.loads(cherrypy.request.body.read())
		if v['apikey'] == self.API_KEY:
			info = []
			info.append(v['title'])
			info.append(v['genres'])
			id = self.myDB.add_movie(info)
			output['id'] = id
		else:
			output['result'] = 'failure'
		return json.dumps(output,encoding = 'latin-1')


	def DELETE(self,id):
		
		v = json.loads(cherrypy.request.body.fp.read())
		output = {'result':'success'}
		if v['apikey'] == self.API_KEY:
			self.myDB.delete_movie(id)
		else:
			output['result'] = 'failure'
		return json.dumps(output,encoding = 'latin-1')

	def DELETE_ALL(self):
		output = {'result':'success'}

		v = json.loads(cherrypy.request.body.fp.read())
		keys = self.myDB.get_movies()
		if v['apikey'] == self.API_KEY:
			for key in keys:
				self.myDB.delete_movie(key)
		else:
			output['result'] = 'failure'

		return json.dumps(output,encoding = 'latin-1')

	def RESET(self,id):
		v = json.loads(cherrypy.request.body.fp.read())
		output = {'result':'success'}
		if v['apikey'] == self.API_KEY:
			self.myDB.load_movie(id,'ml-1m/movies.dat')
		else:
			output['result'] = 'failure'
		return json.dumps(output,encoding = 'latin-1')
	def RESET_ALL(self):
		v = json.loads(cherrypy.request.body.fp.read())
		output = {'result':'success'}
		if v['apikey'] == self.API_KEY:
			self.myDB.__init__()
			self.myDB.load_posters('images.dat')
			self.myDB.load_movies('ml-1m/movies.dat')
			self.myDB.load_users('ml-1m/users.dat')
			self.myDB.load_ratings('ml-1m/ratings.dat')
		else:
			output['result'] = 'failure'
		return json.dumps(output,encoding = 'latin-1')
		
