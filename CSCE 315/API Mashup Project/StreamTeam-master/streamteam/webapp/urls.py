from django.urls import path
from . import views

urlpatterns = [
        path("", views.landing, name="landing"),
        path("register/", views.register, name="register"),
        path("login/", views.login, name="login"),
        path("browse/", views.browse, name="browse"),
        path("search/", views.search, name="search"),
        path("analytics/", views.analytics, name="analytics"),
        path("account/", views.account, name="account"),
        path("retreive/", views.retreive, name="retreive"),
        path("update/", views.update, name="update"),
        path("click/", views.click, name="click"),
        path("recommend/", views.recommend, name="update"),
        path("plot/", views.plot, name="plot"),
        path("deleteAccount/", views.deleteAccount, name="deleteAccount"),
        path("getServices/", views.getServices, name="getServices"),
]