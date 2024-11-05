import cv2
import ffmpeg
import numpy as np

ffmpeg.input("./badapple.mp4").filter('fps', fps=1).output("./images/badapple_frame_%04d.png", s='240x160').run():

frame = 219

