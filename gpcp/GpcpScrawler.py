import requests
from bs4 import BeautifulSoup
import threading

base_url = "https://www.ncei.noaa.gov/data/global-precipitation-climatology-project-gpcp-daily/access/"

start_year = 2011


def get_with_retry(url):
    while True:
        try:
            return requests.get(url, timeout=30)
        except:
            pass


def worker(year):
    html_url = base_url + str(year)
    html = get_with_retry(html_url).text
    soup = BeautifulSoup(html, 'html.parser')
    names = [a.attrs['href'] for a in soup.find_all('a')]
    for name in names:
        if name.startswith("gpcp"):
            url = html_url + '/' + name
            print("Downloading " + name + "...")
            open(name, 'wb').write(get_with_retry(url).content)


threads = []

for year in range(start_year, start_year+10):
    t = threading.Thread(target=worker, args=(year,))
    threads.append(t)
    t.start()

for t in threads:
    t.join()
