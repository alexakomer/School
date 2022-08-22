from django import forms
from webapp.models import User

class MyForm(forms.ModelForm):
    username = forms.CharField(error_messages={'required':'Please enter a username'})
    password = forms.CharField(error_messages={'required':'Please enter a password'})
    services = forms.CharField(error_messages={'required':'Please enter services'})
    lastWatched = forms.CharField(error_messages={'required':'Please enter lastWatched'})

    netflixHits = forms.IntegerField()
    primeHits = forms.IntegerField()
    huluHits = forms.IntegerField()
    disneyHits = forms.IntegerField()
    hboHits = forms.IntegerField()
    peacockHits = forms.IntegerField()
    paramountHits = forms.IntegerField()
    starzHits = forms.IntegerField()
    showtimeHits = forms.IntegerField()
    appleHits = forms.IntegerField()
    mubiHits = forms.IntegerField()

    netflixClicks = forms.IntegerField()
    primeClicks = forms.IntegerField()
    huluClicks = forms.IntegerField()
    disneyClicks = forms.IntegerField()
    hboClicks = forms.IntegerField()
    peacockClicks = forms.IntegerField()
    paramountClicks = forms.IntegerField()
    starzClicks = forms.IntegerField()
    showtimeClicks = forms.IntegerField()
    appleClicks = forms.IntegerField()
    mubiClicks = forms.IntegerField()

    class Meta:
        model = User
        fields = ('username', 'password','services', 'lastWatched',
        'netflixHits', 'primeHits', 'huluHits', 'disneyHits', 'hboHits', 'peacockHits', 
        'paramountHits', 'starzHits', 'showtimeHits', 'appleHits', 'mubiHits',
        'netflixClicks', 'primeClicks', 'huluClicks', 'disneyClicks', 'hboClicks', 'peacockClicks', 
        'paramountClicks', 'starzClicks', 'showtimeClicks', 'appleClicks', 'mubiClicks')