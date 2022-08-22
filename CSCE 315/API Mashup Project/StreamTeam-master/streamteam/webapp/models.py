from statistics import mode
from django.db import models

# Create your models here.
class User(models.Model):
    username = models.CharField(max_length = 30, primary_key = True, unique = True)
    password = models.CharField(max_length = 30)
    services = models.CharField(max_length = 100, blank = True)
    lastWatched = models.CharField(max_length = 100, blank = True)

    netflixHits = models.IntegerField(default = 0, blank = True)
    primeHits = models.IntegerField(default = 0, blank = True)
    huluHits = models.IntegerField(default = 0, blank = True)
    disneyHits = models.IntegerField(default = 0, blank = True)
    hboHits = models.IntegerField(default = 0, blank = True)
    peacockHits = models.IntegerField(default = 0, blank = True)
    paramountHits = models.IntegerField(default = 0, blank = True)
    starzHits = models.IntegerField(default = 0, blank = True)
    showtimeHits = models.IntegerField(default = 0, blank = True)
    appleHits = models.IntegerField(default = 0, blank = True)
    mubiHits = models.IntegerField(default = 0, blank = True)

    netflixClicks = models.IntegerField(default = 0, blank = True)
    primeClicks = models.IntegerField(default = 0, blank = True)
    huluClicks = models.IntegerField(default = 0, blank = True)
    disneyClicks = models.IntegerField(default = 0, blank = True)
    hboClicks = models.IntegerField(default = 0, blank = True)
    peacockClicks = models.IntegerField(default = 0, blank = True)
    paramountClicks = models.IntegerField(default = 0, blank = True)
    starzClicks = models.IntegerField(default = 0, blank = True)
    showtimeClicks = models.IntegerField(default = 0, blank = True)
    appleClicks = models.IntegerField(default = 0, blank = True)
    mubiClicks = models.IntegerField(default = 0, blank = True)