import requests

def searchCatalog(keyword, page=1, limit=5):
    searchResults = []
    try:
        items = getIdsByTitle(keyword)["Search"]
    except Exception:
        return None, 0
        
    startIndex = (page-1) * limit
    endIndex = page * limit
    for i in range(startIndex, endIndex):
        try:
            result = getDataById(items[i]['imdbID'])
            if result is not None:
                searchResults.append(result)
        except IndexError:
            break
    totalPages = int(len(items) / limit)
    if not len(items) % page == 0:
        totalPages += 1
    return searchResults, totalPages

def getIdsByTitle(keyword):
    url = "https://movie-database-alternative.p.rapidapi.com/"
    querystring = {"s":keyword,"r":"json","page":"1"}
    headers = {
        "X-RapidAPI-Host": "movie-database-alternative.p.rapidapi.com",
        "X-RapidAPI-Key": "5e375b1da5msh1063e8883a75934p11c018jsn97bed210a83e"
    }
    response = requests.request("GET", url, headers=headers, params=querystring)
    return response.json()

def getDataById(imdbid):
    url = "https://streaming-availability.p.rapidapi.com/get/basic"
    querystring = {"country":"us","imdb_id":imdbid,"output_language":"en"}
    headers = {
        "X-RapidAPI-Host": "streaming-availability.p.rapidapi.com",
        "X-RapidAPI-Key": "30feb48197mshf15c94b53837ed9p10ae86jsn4672ebcc0ebd"
    }
    response = requests.request("GET", url, headers=headers, params=querystring)
    if response.status_code == 200:
        return response.json()
    else:
        return None
    
def getTopMovies(page):
    url = "https://online-movie-database.p.rapidapi.com/title/get-most-popular-movies"

    querystring = {"currentCountry":"US","purchaseCountry":"US","homeCountry":"US"}

    headers = {
        "X-RapidAPI-Host": "online-movie-database.p.rapidapi.com",
        "X-RapidAPI-Key": "194e17b2e6msh5614b4bbdae75b3p163d97jsn99a3379434c5"
    }

    response = requests.request("GET", url, headers=headers, params=querystring)
    json_response = response.json()
    json_data = []
    for x in range((page-1)*5,page*5):
        try:
            json_data.append(getDataById(json_response[x][7:-1]))
        except:
            break
    return json_data

def getTopMoviesByGenre():
    url = "https://online-movie-database.p.rapidapi.com/title/v2/get-popular-movies-by-genre"

    querystring = {"genre":"adventure","limit":"100"}

    headers = {
        "X-RapidAPI-Host": "online-movie-database.p.rapidapi.com",
        "X-RapidAPI-Key": "194e17b2e6msh5614b4bbdae75b3p163d97jsn99a3379434c5"
    }

    response = requests.request("GET", url, headers=headers, params=querystring)
    return response.json()

def getTopShows(page):
    url = "https://online-movie-database.p.rapidapi.com/title/get-most-popular-tv-shows"

    querystring = {"currentCountry":"US","purchaseCountry":"US","homeCountry":"US"}

    headers = {
        "X-RapidAPI-Host": "online-movie-database.p.rapidapi.com",
        "X-RapidAPI-Key": "194e17b2e6msh5614b4bbdae75b3p163d97jsn99a3379434c5"
    }

    response = requests.request("GET", url, headers=headers, params=querystring)
    json_response = response.json()
    json_data = []
    for x in range((page-1)*5,page*5):
        try:
            json_data.append(getDataById(json_response[x][7:-1]))
        except:
            break
    return json_data

def moreLikeThis(imdbid,page):
    url = "https://online-movie-database.p.rapidapi.com/title/get-more-like-this"

    querystring = {"tconst":imdbid,"currentCountry":"US","purchaseCountry":"US"}

    headers = {
        "X-RapidAPI-Host": "online-movie-database.p.rapidapi.com",
        "X-RapidAPI-Key": "194e17b2e6msh5614b4bbdae75b3p163d97jsn99a3379434c5"
    }

    response = requests.request("GET", url, headers=headers, params=querystring)
    json_response = response.json()
    json_data = []
    for x in range((page-1)*5,page*5):
        try:
            json_data.append(getDataById(json_response[x][7:-1]))
        except:
            break
    return json_data

    