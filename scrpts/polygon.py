import cv2
import numpy as np

# 画像を読み込む
image = cv2.imread('badapple.jpg', cv2.IMREAD_GRAYSCALE)

# 二値化
_, thresh = cv2.threshold(image, 128, 255, cv2.THRESH_BINARY)

# 輪郭を抽出
contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# ポリゴンの座標をSVG形式に変換
svg_polygons = []
for contour in contours:
    polygon = cv2.approxPolyDP(contour, epsilon=1, closed=True)
    points = " ".join([f"{p[0][0]},{p[0][1]}" for p in polygon])
    svg_polygons.append(f"<polygon points='{points}' fill='black' />")

# SVGファイルの作成
svg_content = "<svg xmlns='http://www.w3.org/2000/svg'>\n" + "\n".join(svg_polygons) + "\n</svg>"
with open('badapple.svg', 'w') as f:
    f.write(svg_content)
