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
        results (list of tuples): Lista wyników w formacie (num_threads, time, num_divisions).
        filename (str): Nazwa pliku Excela.
    """
    # Tworzymy nowy arkusz Excel
    workbook = openpyxl.Workbook()
    sheet = workbook.active
    sheet.title = "Wyniki"

    # Dodajemy nagłówki
    sheet.append(["Liczba Rdzeni", "Czas Wykonania (s)", "Liczba Podziałów"])

    # Wpisujemy dane
    for num_threads, exec_time, num_divisions in results:
        sheet.append([num_threads, exec_time, num_divisions])

    # Zapisujemy do pliku
    workbook.save(filename)
    print(f"Wyniki zapisane do pliku: {filename}")


def main():
    # Konfiguracja testów
    num_divisions = 1_000_000_000  # Liczba podziałów przedziału całki
    max_threads = 50  # Maksymalna liczba rdzeni (wątków)
    results = []

    for num_threads in range(1, max_threads + 1):
        print(f"Uruchamianie dla {num_threads} rdzeni...")
        exec_time = measure_execution_time(num_divisions, num_threads)
        if exec_time is not None:
            results.append((num_threads, exec_time, num_divisions))
        else:
            print(f"Pomiar dla {num_threads} rdzeni nie powiódł się.")

    # Zapisujemy wyniki do Excela
    save_results_to_excel(results)


if __name__ == "__main__":
    main()
