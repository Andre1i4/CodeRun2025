from django import forms

class ExempluFormular(forms.Form):
    nume = forms.CharField(label='Numele tau', max_length=100)
    mesaj = forms.CharField(label='Mesaj', widget=forms.Textarea)