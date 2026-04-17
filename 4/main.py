import sys
from PIL import Image

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print('use: python main.py <input img 1> <input img 2> <output img>')
        exit(1)

    img1, img2, result_image = None, None, None

    try:
        img1 = Image.open(sys.argv[1])
        img2 = Image.open(sys.argv[2])

        new_width = int(img2.width * (img1.height / img2.height))

        img2 = img2.resize((new_width, img1.height))

        result_image = Image.new("RGB", (img1.width + new_width, img1.height), "black")
        result_image.paste(img1, (0, 0))
        result_image.paste(img2, (img1.width, 0))

        result_image.save(sys.argv[3])
    except FileNotFoundError:
        print("file not found")
        sys.exit(1)
    except Exception as e:
        print(f"error: {e}")
        sys.exit(1)
    finally:
        img1.close()
        img2.close()
        result_image.close()