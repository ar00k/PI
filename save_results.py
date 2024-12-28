import subprocess
import time
import openpyxl
import platform

def measure_execution_time(num_divisions, num_threads):
    """
    Uruchamia program w C++ i mierzy czas wykonania.

    Args:
        num_divisions (int): Liczba podziałów przedziału całki.
        num_threads (int): Liczba rdzeni (wątków).

    Returns:
        float: Czas wykonania programu w sekundach.
    """
    try:
        # Ustalanie nazwy pliku wykonywalnego w zależności od systemu operacyjnego
        exe_name = "output.exe" if platform.system() == "Windows" else "./output.out"

        # Uruchamianie programu w C++ z odpowiednimi argumentami
        start_time = time.time()
        result = subprocess.run(
            [exe_name, str(num_divisions), str(num_threads)],
            capture_output=True,
            text=True
        )
        end_time = time.time()
        
        # Sprawdzamy, czy program wykonał się poprawnie
        if result.returncode != 0:
            print(f"Błąd wykonania programu dla {num_threads} rdzeni.")
            print("Szczegóły błędu:", result.stderr)
            return None
        
        # Wyświetlamy wyjście programu (opcjonalnie)
        print(result.stdout)

        # Zwracamy czas wykonania
        return end_time - start_time
    except Exception as e:
        print(f"Błąd podczas uruchamiania programu: {e}")
        return None


def save_results_to_excel(results, filename="results.xlsx"):
    """
    Zapisuje wyniki do pliku Excel.

    Args:
        results (list of tuples): Lista wyników w formacie (num_threads, time_100m, time_1b, time_3b).
        filename (str): Nazwa pliku Excela.
    """
    # Tworzymy nowy arkusz Excel
    workbook = openpyxl.Workbook()
    sheet = workbook.active
    sheet.title = "Wyniki"

    # Dodajemy nagłówki
    sheet.append(["Liczba Rdzeni", "Liczba Podziałów 100000000", "Liczba Podziałów 1000000000", "Liczba Podziałów 3000000000"])

    # Wpisujemy dane z precyzją do 4 miejsc po przecinku
    for num_threads, time_100m, time_1b, time_3b in results:
        sheet.append([num_threads, 
                      round(time_100m, 4) if time_100m is not None else None,
                      round(time_1b, 4) if time_1b is not None else None,
                      round(time_3b, 4) if time_3b is not None else None])

    # Zapisujemy do pliku
    workbook.save(filename)
    print(f"Wyniki zapisane do pliku: {filename}")


def main():
    # Konfiguracja testów
    divisions_list = [100000000, 1000000000, 3000000000]  # Lista różnych ilości podziałów
    max_threads = 12  # Maksymalna liczba rdzeni (wątków)
    results = []

    # Testujemy dla różnych ilości podziałów
    for num_threads in range(1, max_threads + 1):
        print(f"Uruchamianie dla {num_threads} rdzeni...")

        # Zbieramy czas wykonania dla każdej liczby podziałów
        times = []
        for num_divisions in divisions_list:
            exec_time = measure_execution_time(num_divisions, num_threads)
            if exec_time is not None:
                times.append(exec_time)
            else:
                print(f"Pomiar dla {num_threads} rdzeni i {num_divisions} podziałów nie powiódł się.")
                times.append(None)

        # Dodajemy dane do wyników (num_threads i czasy dla różnych podziałów)
        results.append((num_threads, *times))

    # Zapisujemy wyniki do Excela
    save_results_to_excel(results)


if __name__ == "__main__":
    main()
