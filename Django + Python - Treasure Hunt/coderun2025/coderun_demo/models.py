from django.db import models

class MesajContact(models.Model):
    # Definim coloanele tabelului
    nume = models.CharField(max_length=100)
    mesaj = models.TextField()
    
    # Putem adăuga automat data și ora când s-a creat
    data_trimiterii = models.DateTimeField(auto_now_add=True)

    # Asta ajută să vedem numele frumos în panoul de admin, nu "Object 1"
    def __str__(self):
        return f"{self.nume} - {self.data_trimiterii}"