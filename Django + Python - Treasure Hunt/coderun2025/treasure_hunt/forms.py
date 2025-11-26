from django import forms
from .models import Instruction

class InstructionForm(forms.ModelForm):
    class Meta:
        model = Instruction
        fields = ['direction', 'distance', 'description', 'risk_level', 'previous_instruction']
        labels = {
            'direction': 'Direction',
            'distance': 'Distance (NM)',
            'description': 'Description',
            'risk_level': 'Risk Level',
            'previous_instruction': 'Linked to Previous Step'
        }
        widgets = {
            'description': forms.Textarea(attrs={'rows': 3}),
            'risk_level': forms.NumberInput(attrs={'min': 0, 'max': 100}),
            'distance': forms.NumberInput(attrs={'min': 0}),
        }

class OracleForm(forms.Form):
    instruction_id = forms.CharField(
        label='Instruction ID / Code',
        max_length=200,
        widget=forms.TextInput(attrs={'placeholder': 'e.g. strong-winds'})
    )

# --- FORMULARUL PENTRU LACAT (4 CIFRE) ---
class TreasureChestForm(forms.Form):
    digit1 = forms.CharField(max_length=1, widget=forms.TextInput(attrs={'class': 'digit-input', 'autocomplete': 'off'}))
    digit2 = forms.CharField(max_length=1, widget=forms.TextInput(attrs={'class': 'digit-input', 'autocomplete': 'off'}))
    digit3 = forms.CharField(max_length=1, widget=forms.TextInput(attrs={'class': 'digit-input', 'autocomplete': 'off'}))
    digit4 = forms.CharField(max_length=1, widget=forms.TextInput(attrs={'class': 'digit-input', 'autocomplete': 'off'}))