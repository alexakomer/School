from django.shortcuts import render, redirect
from django.http import JsonResponse
from django.contrib import auth

# from StreamTeam.streamteam.webapp.forms import MyForm
from webapp.forms import MyForm
from .scripts import search as api
from .scripts import user
from webapp.models import User

allPlatforms = ['netflix', 'prime', 'hulu', 'disney', 'hbo', 'peacock', 'paramount', 'starz', 'showtime', 'apple', 'mubi'] # add all supported platforms

# Create your views here.

def browse(request):
    return render(request, "webapp/browse.html")

def search(request):
    return render(request, "webapp/search.html")

def analytics(request):
    return render(request, "webapp/analytics.html")

def plot(request):
    if request.method == 'GET' and request.GET:
        usr = request.GET.get('username').replace('\"', '')
        context = {'statistics': {'netflixHits':User.objects.filter(username=usr)[0].netflixHits,
        'primeHits':User.objects.filter(username=usr)[0].primeHits,
        'huluHits':User.objects.filter(username=usr)[0].huluHits,
        'disneyHits':User.objects.filter(username=usr)[0].disneyHits,
        'hboHits':User.objects.filter(username=usr)[0].hboHits,
        'peacockHits':User.objects.filter(username=usr)[0].peacockHits,
        'paramountHits':User.objects.filter(username=usr)[0].paramountHits,
        'starzHits':User.objects.filter(username=usr)[0].starzHits,
        'showtimeHits':User.objects.filter(username=usr)[0].showtimeHits,
        'appleHits':User.objects.filter(username=usr)[0].appleHits,
        'mubiHits':User.objects.filter(username=usr)[0].mubiHits,
        'netflixClicks':User.objects.filter(username=usr)[0].netflixClicks,
        'primeClicks':User.objects.filter(username=usr)[0].primeClicks,
        'huluClicks':User.objects.filter(username=usr)[0].huluClicks,
        'disneyClicks':User.objects.filter(username=usr)[0].disneyClicks,
        'hboClicks':User.objects.filter(username=usr)[0].hboClicks,
        'peacockClicks':User.objects.filter(username=usr)[0].peacockClicks,
        'paramountClicks':User.objects.filter(username=usr)[0].paramountClicks,
        'starzClicks':User.objects.filter(username=usr)[0].starzClicks,
        'showtimeClicks':User.objects.filter(username=usr)[0].showtimeClicks,
        'appleClicks':User.objects.filter(username=usr)[0].appleClicks,
        'mubiClicks':User.objects.filter(username=usr)[0].mubiClicks
        }, 'services': {'userServices':User.objects.filter(username=usr)[0].services}}
        return JsonResponse(context)
    else:
        return JsonResponse({'status' : "failure"})

def recommend(request): #TODO: pages
    if request.method == 'GET' and request.GET:
        usr = request.GET['username'].replace('\"', '')
        lastWatched = User.objects.filter(username=usr)[0].lastWatched
        services = User.objects.filter(username=usr)[0].services
        context = {'userServices':services, 'topMovies':None, 'topShows':api.getTopShows(int(request.GET['pageTS'])), 'topByGenre':None, 'moreLikeThis':api.moreLikeThis(lastWatched,int(request.GET['pageLT']))}
        return JsonResponse(context)


def retreive(request):
    if request.method == 'GET' and request.GET:
        usr = request.GET['username'].replace('\"', '')
        services = User.objects.filter(username=usr)[0].services
        results, pages = api.searchCatalog(keyword=request.GET['keyword'], page=int(request.GET['page']))
        context = {'searchInput': request.GET['keyword'], 'page': request.GET['page'], 'searchResults': results, 'userServices':services, 'totalPages': pages}  
        return JsonResponse(context)
    
def click(request):
    if request.method == 'GET' and request.GET:
        usr = request.GET.get('username').replace('\"', '')
        service = str(request.GET['clicked'])

        id = request.GET.get('id')
        User.objects.filter(username=usr).update(lastWatched=id)

        if (service == "netflix"):
            res = User.objects.filter(username=usr)[0].netflixClicks
            User.objects.filter(username=usr).update(netflixClicks=int(res) + 1)
        elif (service == "prime"):
            res = User.objects.filter(username=usr)[0].primeClicks
            User.objects.filter(username=usr).update(primeClicks=int(res) + 1)
        elif (service == "hulu"):
            res = User.objects.filter(username=usr)[0].huluClicks
            User.objects.filter(username=usr).update(huluClicks=int(res) + 1)
        elif (service == "disney"):
            res = User.objects.filter(username=usr)[0].disneyClicks
            User.objects.filter(username=usr).update(disneyClicks=int(res) + 1)
        elif (service == "hbo"):
            res = User.objects.filter(username=usr)[0].hboClicks
            User.objects.filter(username=usr).update(hboClicks=int(res) + 1)
        elif (service == "peacock"):
            res = User.objects.filter(username=usr)[0].peacockClicks
            User.objects.filter(username=usr).update(peacockClicks=int(res) + 1)
        elif (service == "paramount"):
            res = User.objects.filter(username=usr)[0].paramountClicks
            User.objects.filter(username=usr).update(paramountClicks=int(res) + 1)
        elif (service == "starz"):
            res = User.objects.filter(username=usr)[0].starzClicks
            User.objects.filter(username=usr).update(starzClicks=int(res) + 1)
        elif (service == "showtime"):
            res = User.objects.filter(username=usr)[0].showtimeClicks
            User.objects.filter(username=usr).update(showtimeClicks=int(res) + 1)
        elif (service == "apple"):
            res = User.objects.filter(username=usr)[0].appleClicks
            User.objects.filter(username=usr).update(appleClicks=int(res) + 1)
        elif (service == "mubi"):
            res = User.objects.filter(username=usr)[0].mubiClicks
            User.objects.filter(username=usr).update(mubiClicks=int(res) + 1)
        else:
            return JsonResponse({'status' : "failure"})
        return JsonResponse({'status' : "success"})
    else:
        return JsonResponse({'status' : "failure"})

def update(request):
    if request.method == 'GET' and request.GET:
        usr = request.GET.get('username').replace('\"', '')

        netflixRes = User.objects.filter(username=usr)[0].netflixHits
        User.objects.filter(username=usr).update(netflixHits=int(netflixRes) + int(request.GET['netflixHits']))

        primeRes = User.objects.filter(username=usr)[0].primeHits
        User.objects.filter(username=usr).update(primeHits=int(primeRes) + int(request.GET['primeHits']))

        huluRes = User.objects.filter(username=usr)[0].huluHits
        User.objects.filter(username=usr).update(huluHits=int(huluRes) + int(request.GET['huluHits']))

        disneyRes = User.objects.filter(username=usr)[0].disneyHits
        User.objects.filter(username=usr).update(disneyHits=int(disneyRes) + int(request.GET['disneyHits']))

        hboRes = User.objects.filter(username=usr)[0].hboHits
        User.objects.filter(username=usr).update(hboHits=int(hboRes) + int(request.GET['hboHits']))

        peacockRes = User.objects.filter(username=usr)[0].peacockHits
        User.objects.filter(username=usr).update(peacockHits=int(peacockRes) + int(request.GET['peacockHits']))

        paramountRes = User.objects.filter(username=usr)[0].paramountHits
        User.objects.filter(username=usr).update(paramountHits=int(paramountRes) + int(request.GET['paramountHits']))

        starzRes = User.objects.filter(username=usr)[0].starzHits
        User.objects.filter(username=usr).update(starzHits=int(starzRes) + int(request.GET['starzHits']))

        showtimeRes = User.objects.filter(username=usr)[0].showtimeHits
        User.objects.filter(username=usr).update(showtimeHits=int(showtimeRes) + int(request.GET['showtimeHits']))

        appleRes = User.objects.filter(username=usr)[0].appleHits
        User.objects.filter(username=usr).update(appleHits=int(appleRes) + int(request.GET['appleHits']))

        mubiRes = User.objects.filter(username=usr)[0].mubiHits
        User.objects.filter(username=usr).update(mubiHits=int(mubiRes) + int(request.GET['mubiHits']))

        return JsonResponse({'status' : "success"})
    else:
        return JsonResponse({'status' : "failure"})

def login(request):
    if request.method == 'GET' and request.GET:
        isUser = User.objects.filter(username=request.GET['username'], password = request.GET['password']).exists()
        return JsonResponse({'status': isUser})
    else:
        return render(request, 'webapp/login.html')

def register(request):
    if request.method == 'GET' and request.GET:
        isUser = User.objects.filter(username=request.GET.get('username'), password = request.GET.get('password')).exists()

        newServices = request.GET.get('services')

        x = str(newServices).replace('[', '{')
        x = x.replace(']', '}')
        x = x.replace('\'', '')

        if isUser:
            return redirect('/login')
        else:


            temp = dict(request.GET)
            for i in range (0, len(allPlatforms)):
                if (allPlatforms[i] in temp.keys()):
                    temp.pop(allPlatforms[i])

            temp['services'] = x

            trimUser = str(temp['username'])
            trimUser = trimUser.replace('\'', '')
            trimUser = trimUser.replace('[', '')
            trimUser = trimUser.replace(']', '')
            temp['username'] = trimUser

            trimPass = str(temp['password'])
            trimPass = trimPass.replace('\'', '')
            trimPass = trimPass.replace('[', '')
            trimPass = trimPass.replace(']', '')
            temp['password'] = trimPass

            # setting default values
            temp['netflixHits'] = 0
            temp['primeHits'] = 0
            temp['huluHits'] = 0
            temp['disneyHits'] = 0
            temp['hboHits'] = 0
            temp['peacockHits'] = 0
            temp['paramountHits'] = 0
            temp['starzHits'] = 0
            temp['showtimeHits'] = 0
            temp['appleHits'] = 0
            temp['mubiHits'] = 0

            temp['netflixClicks'] = 0
            temp['primeClicks'] = 0
            temp['huluClicks'] = 0
            temp['disneyClicks'] = 0
            temp['hboClicks'] = 0
            temp['peacockClicks'] = 0
            temp['paramountClicks'] = 0
            temp['starzClicks'] = 0
            temp['showtimeClicks'] = 0
            temp['appleClicks'] = 0
            temp['mubiClicks'] = 0

            temp['lastWatched'] = "tt0298148"

            
            form = MyForm(temp or None)
            if (form.is_valid()):
                form.save()
            else:
                pass
            return redirect('/browse')
    else:
        return render(request, 'webapp/register.html')

def landing(request):
    return render(request, 'webapp/landing.html')

def account(request):
    if request.method == 'GET' and request.GET:

        newServices = request.GET.get('newServices')

        usr = request.GET['username'].replace('\"', '')
        x = str(newServices).replace('[', '{')
        x = x.replace(']', '}')
        x = x.replace('\'', '')
        User.objects.filter(username=usr).update(services=x)
        return JsonResponse({'status':'done'})
        # return redirect('account')
    else:
        return render(request, 'webapp/account.html')

def deleteAccount(request):
    if request.method == 'GET' and request.GET:
        usr = request.GET['username'].replace('\"', '')
        
        User.objects.filter(username=usr).delete()
    return render(request, 'webapp/landing.html')
    
def getServices(request):
    if request.method == 'GET' and request.GET:
        usr = request.GET['username'].replace('\"', '')
        services = User.objects.filter(username=usr)[0].services
        context = {'userServices':services}
    return JsonResponse(context)

