from django.urls import path
from . import views

urlpatterns = [
    path('compass/', views.compass, name='compass'),
    path('instructions/<int:pk>/', views.instruction_detail, name='instruction_detail'),
    path('oracle/', views.oracle_hunt, name='oracle_hunt'),
]