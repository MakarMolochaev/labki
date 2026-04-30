import imageio
import os
import sys

# python merge-images.py <dir> <output.mp4>

input_dir = sys[1] if (len(sys.argv) > 1) else './frames'
output_video = sys[2] if (len(sys.argv) > 2) else 'output.mp4'
fps = 24

images = sorted([f for f in os.listdir(input_dir) if f.endswith(('.bmp'))])
writer = imageio.get_writer(output_video, fps=fps)
for img_name in images:
    img = imageio.v2.imread(os.path.join(input_dir, img_name))
    writer.append_data(img)
writer.close()