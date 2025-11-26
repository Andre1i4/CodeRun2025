from django.db import models
from django.core.validators import MinValueValidator, MaxValueValidator

class Instruction(models.Model):
    DIRECTION_CHOICES = [
        ('north', 'North'),
        ('north-east', 'North-East'),
        ('east', 'East'),
        ('south-east', 'South-East'),
        ('south', 'South'),
        ('south-west', 'South-West'),
        ('west', 'West'),
        ('north-west', 'North-West'),
        ('none', 'None'), # Adaugat pentru pasul final
    ]

    direction = models.CharField(
        max_length=20,
        choices=DIRECTION_CHOICES,
        help_text="alege directia"
    )

    distance = models.IntegerField(
        validators=[MinValueValidator(0)], # Permitem 0 pentru cufar
        help_text="distanta in mile/km"
    )

    description = models.TextField(
        help_text="descrierea pasului"
    )

    risk_level = models.IntegerField(
        validators=[MinValueValidator(0), MaxValueValidator(100)],
        help_text="cat de periculos e (0-100)",
        default=0 
    )

    previous_instruction = models.OneToOneField(
        'self',
        on_delete=models.SET_NULL,
        null=True,
        blank=True,
        related_name='next_instruction',
        help_text="leaga de pasul anterior"
    )

    def __str__(self):
        return f"{self.get_direction_display()} - {self.description[:30]}..."