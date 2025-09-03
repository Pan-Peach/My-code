import requests
from bs4 import BeautifulSoup
import pandas as pd
import time
from datetime import datetime

# 目标URL和请求头
url = "https://thwiki.cc/%E4%B8%9C%E6%96%B9%E8%A7%92%E8%89%B2%E6%97%A5%E4%B8%80%E8%A7%88"
headers: dict[str, str] = {  # 显式声明类型（可选）
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36",
    "Referer": "https://cn.bing.com/",
    "Accept-Language": "zh-CN,zh;q=0.9",
    "cookie": "_ga=GA1.2.585610397.1720418707; FCNEC=%5B%5B%22AKsRol9pjQ33N0U6lTxu8Q7lkxvcVsv7_aP5GbdTjz8AeOSK3V-i7H1A9FNwAu11YzqlL2daxw3ISh9dMEyM0Cc1d5B-AI4qlSnD-mHNzT9hUPrunDgJF60TgFlachRfe1_8RBQ7gNTMvjjxTbDeTZguwOZCVFQ0RA%3D%3D%22%5D%5D; _gid=GA1.2.1783642947.1744383584; Hm_lvt_2fdbea59c583f65a8309e976b1e31e23=1744383584,1744451225; HMACCOUNT=19BB790BD98211B6; thwikicc_wikiSidebarHidden=1; _gat=1; Hm_lpvt_2fdbea59c583f65a8309e976b1e31e23=1744451913; __gads=ID=c1921e50f2901887:T=1720418708:RT=1744451913:S=ALNI_MarsOv3WTJNRkXeiIIVbNYbqw60vg; __gpi=UID=00000e86ad4277f5:T=1720418708:RT=1744451913:S=ALNI_MYHJXH2VVQl6FMaZ6OY4CUiSG6ORw; __eoi=ID=e7fc1563e4f6fde4:T=1737983434:RT=1744451913:S=AA-AfjYp4gY8z7Oz3lontVUP5SFk",  # 替换为实际的cookie值
}
# 记录请求时间（确保间隔≥60秒）
last_request_time = 0

def make_request(url):
    global last_request_time
    current_time = time.time()
    if current_time - last_request_time < 60:
        sleep_time = 60 - (current_time - last_request_time)
        print(f"等待 {sleep_time:.1f} 秒以遵守 robots.txt ...")
        time.sleep(sleep_time)
    last_request_time = time.time()
    return requests.get(url, headers=headers)

# 获取页面
response = make_request(url)
soup = BeautifulSoup(response.text, 'html.parser')

# 定位目标表格
table = soup.find("table", {"class": "wikitable sortable"})

# 提取表头和行数据
headers = [th.get_text(strip=True) for th in table.find_all("th")]
rows = []
for tr in table.find_all("tr")[1:]:  # 跳过表头行
    row = [td.get_text(strip=True) for td in tr.find_all(["td", "th"])]
    rows.append(row)

# 转换为DataFrame并清洗数据
df = pd.DataFrame(rows, columns=headers)

# 清洗日期字段（示例：提取 "1月1日" → "01-01"）
df["日期"] = (
    df["日期"]
    .str.extract(r"(\d+月\d+日)")
    .str.replace("月", "-")
    .str.replace("日", "")
    .apply(lambda x: f"{x.split('-')[0].zfill(2)}-{x.split('-')[1].zfill(2)}" if pd.notnull(x) else x)
)

# 保存结果
output_file = f"touhou_character_days_{datetime.now().strftime('%Y%m%d')}.csv"
df.to_csv(output_file, index=False, encoding="utf-8-sig")
print(f"数据已保存到 {output_file}")
print(df.head())