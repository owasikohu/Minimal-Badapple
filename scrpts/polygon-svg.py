import cv2
import ffmpeg
import numpy as np

ffmpeg.input("./badapple.mp4").filter('fps', fps=2).output("./images/badapple_frame_%04d.png", s='240x160').run()

frame = 438

for i in range(frame):

    image = cv2.imread(f"images/badapple_frame_{i + 1:04}.png", cv2.IMREAD_GRAYSCALE)
    _, thresh = cv2.threshold(image, 128, 255, cv2.THRESH_BINARY)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    svg_polygons = []
    for contour in contours:
        polygon = cv2.approxPolyDP(contour, epsilon=5, closed=True)
        points = " ".join([f"{p[0][0]},{p[0][1]}" for p in polygon])
        svg_polygons.append(f"<polygon points='{points}' fill='black' />")

    svg_content = "<svg xmlns='http://www.w3.org/2000/svg'>\n" + "\n".join(svg_polygons) + "\n</svg>"
    with open(f"svg/{i + 1}.svg" , 'w') as f:
        f.write(svg_content)
