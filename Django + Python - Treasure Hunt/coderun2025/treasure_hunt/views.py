import requests
from django.shortcuts import render, redirect, get_object_or_404
from .models import Instruction
from .forms import InstructionForm, OracleForm, TreasureChestForm

# 1. COMPASS
def compass(request):
    if request.method == 'POST':
        form = InstructionForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('compass')
    else:
        form = InstructionForm()
    instructions = Instruction.objects.all()
    return render(request, 'treasure_hunt/compass.html', {'form': form, 'instructions': instructions})

# 2. DETAILS
def instruction_detail(request, pk):
    instruction = get_object_or_404(Instruction, pk=pk)
    total_distance = None
    avg_risk = None
    show_summary = False

    if request.GET.get('summary') == 'true':
        show_summary = True
        total_distance = 0
        total_risk = 0
        count = 0
        current = instruction
        while current:
            total_distance += current.distance
            total_risk += current.risk_level
            count += 1
            try:
                current = current.next_instruction
            except Instruction.DoesNotExist:
                current = None
        if count > 0:
            avg_risk = total_risk / count

    return render(request, 'treasure_hunt/detail.html', {
        'instruction': instruction, 'show_summary': show_summary,
        'total_distance': total_distance, 'avg_risk': avg_risk
    })

# 3. ORACLE & BOSS FIGHT
def oracle_hunt(request):
    BASE_URL_DIR = "https://coderum-2025-pirates-baace2h8crd9btg4.canadacentral-01.azurewebsites.net/direction/"
    BASE_URL_CHECK = "https://coderum-2025-pirates-baace2h8crd9btg4.canadacentral-01.azurewebsites.net/check-password/"

    new_instruction = None
    error_message = None
    chest_form = None 
    is_at_treasure = False

    # Verificam daca ultimul pas din DB este comoara
    # Oracolul a zis "Treasure is found" in titlu sau descriere
    last_step = Instruction.objects.last()
    if last_step and ("treasure" in last_step.description.lower() or (hasattr(last_step, 'title') and "treasure" in last_step.title.lower())):
         is_at_treasure = True
         chest_form = TreasureChestForm()

    # Luam istoricul incercarilor de cod (pentru punctaj)
    previous_guesses = Instruction.objects.filter(description__startswith="Code Attempt:").order_by('-id')

    if request.method == 'POST':
        # --- CAZUL 1: SPARGEM LACATUL ---
        if 'digit1' in request.POST:
            chest_form = TreasureChestForm(request.POST)
            if chest_form.is_valid():
                d1 = chest_form.cleaned_data['digit1']
                d2 = chest_form.cleaned_data['digit2']
                d3 = chest_form.cleaned_data['digit3']
                d4 = chest_form.cleaned_data['digit4']
                full_code = f"{d1}{d2}{d3}{d4}"

                try:
                    # Verificam codul (GET request)
                    print(f"🔐 Checking code: {full_code}")
                    response = requests.get(f"{BASE_URL_CHECK}{full_code}", timeout=5)
                    data = response.json()
                    
                    msg = data.get('message', data.get('description', 'No message'))
                    
                    # Salvam incercarea in DB
                    new_instruction = Instruction.objects.create(
                        direction='none',
                        distance=0,
                        description=f"Code Attempt: {full_code} -> Oracle says: {msg}",
                        risk_level=100
                    )
                except Exception as e:
                    error_message = f"Connection error: {e}"

        # --- CAZUL 2: NAVIGARE NORMALA ---
        else:
            form = OracleForm(request.POST)
            if form.is_valid():
                id_sent = form.cleaned_data['instruction_id'].strip()
                TARGET_URL = f"{BASE_URL_DIR}{id_sent}/"
                
                try:
                    response = requests.post(TARGET_URL, json={'id': id_sent}, timeout=5)
                    if response.status_code == 405:
                        response = requests.get(TARGET_URL, params={'id': id_sent}, timeout=5)

                    if response.status_code == 200:
                        data = response.json()
                        desc = data.get('instructionText') or data.get('description') or "Mesaj Oracol"
                        dist = data.get('distanceInMeters') or data.get('distance') or 1
                        direc = data.get('direction', 'north').lower()
                        
                        # Verificam daca AM AJUNS ACUM la comoara
                        if "treasure" in desc.lower() or "found" in desc.lower():
                            is_at_treasure = True
                            chest_form = TreasureChestForm()

                        new_instruction = Instruction.objects.create(
                            direction=direc, 
                            distance=dist,
                            description=desc,
                            risk_level=data.get('risk', 0)
                        )
                    else:
                        error_message = f"Error {response.status_code}"
                except Exception as e:
                    error_message = f"Conn Error: {e}"
    
    # Daca e GET sau reload, initializam formularul
    if chest_form is None and is_at_treasure:
        chest_form = TreasureChestForm()
    
    form = OracleForm()

    return render(request, 'treasure_hunt/oracle.html', {
        'form': form,
        'chest_form': chest_form,
        'is_at_treasure': is_at_treasure,
        'new_instruction': new_instruction,
        'error_message': error_message,
        'previous_guesses': previous_guesses
    })