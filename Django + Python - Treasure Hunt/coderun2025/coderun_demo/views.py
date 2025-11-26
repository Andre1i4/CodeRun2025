from django.shortcuts import render, redirect  # <--- 1. Importă 'redirect' aici
from .forms import ExempluFormular
from .models import MesajContact

def index(request):
    mesaj_primit = None

    if request.method == 'POST':
        form = ExempluFormular(request.POST)
        
        if form.is_valid():
            date = form.cleaned_data
            
            MesajContact.objects.create(
                nume=date['nume'],
                mesaj=date['mesaj']
            )
            
            # <--- 2. AICI ESTE SCHIMBAREA
            # După ce am salvat, "aruncăm" utilizatorul înapoi pe pagina principală (refresh forțat)
            # Asta curăță memoria browserului de datele formularului.
            return redirect('index') 
            
    else:
        form = ExempluFormular()

    # Partea de afișare rămâne la fel
    lista_mesaje = MesajContact.objects.all().order_by('-data_trimiterii')

    return render(request, 'coderun_demo/demo.html', {
        'form': form, 
        'mesaj_succes': mesaj_primit, # Nota: Acesta nu va mai apărea după redirect (e normal)
        'lista_mesaje': lista_mesaje
    })