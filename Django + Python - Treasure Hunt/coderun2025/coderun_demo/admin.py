from django.contrib import admin
from .models import MesajContact

# Asta face ca tabelul să apară în interfața de admin
admin.site.register(MesajContact)