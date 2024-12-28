import openpyxl
import time

# Funkcja zapisująca dane do pliku Excel
def save_to_excel(data, filename="wyniki.xlsx"):
    # Tworzymy nowy skoroszyt
    wb = openpyxl.Workbook()
    ws = wb.active
    ws.title = "Wyniki"

    # Dodajemy nagłówki
    ws.append(["Ilość wątków", "Czas wykonania (sekundy)", "Liczba podziałów"])

    # Dodajemy dane
    for row in data:
        ws.append(row)

    # Zapisujemy plik Excel
    wb.save(filename)

# Przykładowe dane (ilość wątków, czas wykonania, liczba podziałów)
# Zmienna 'data' będzie przechowywać dane, które później zapisujemy do pliku Excel
data = []

# Testowanie różnych ilości wątków
for num_threads in range(1, 6):  # Testujemy od 1 do 5 wątków
    num_divisions = 1000000000  # Liczba podziałów przedziału całki
    
    # Mierzymy czas obliczeń
    start_time = time.time()

    # Wywołanie programu C++ (tutaj wstawiamy czasowo symulację obliczeń)
    # Zakładając, że `PI::computePI()` działa w ciągu 1 sekundy na jeden wątek
    # W rzeczywistości wywołać C++ program w sposób zintegrowany, np. poprzez subprocess
    
    # Symulacja
    time.sleep(0.5 * num_threads)  # symulacja opóźnienia w zależności od liczby wątków
    
    end_time = time.time()
    execution_time = end_time - start_time

    # Dodajemy dane do listy
    data.append([num_threads, execution_time, num_divisions])

# Zapisujemy dane do pliku Excel
save_to_excel(data)
print("Dane zostały zapisane do pliku wyniki.xlsx")