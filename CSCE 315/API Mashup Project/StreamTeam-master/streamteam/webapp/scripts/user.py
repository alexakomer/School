class User:
    username = ""
    services = []
    searchHits = {'netflix':0, 'prime':0, 'hulu':0, 'disney':0, 'hbo':0, 'peacock':0, 'paramount':0, 'starz':0, 'showtime':0, 'apple':0, 'mubi':0}
    searchClicks = {'netflix':0, 'prime':0, 'hulu':0, 'disney':0, 'hbo':0, 'peacock':0, 'paramount':0, 'starz':0, 'showtime':0, 'apple':0, 'mubi':0}

    def setUserName(self, username):
        self.username = username

    def setServices(self, services):
        self.services = services

    def getUserName(self):
        return self.username

    def getServices(self):
        res = ""
        for i in range(len(self.services)):
            res += self.services[i] + "\n"
        return res

    def incrementHit(self, service, num):
        self.searchHits[service] += num

    def incrementClick(self, service):
        self.searchClicks[service] += 1