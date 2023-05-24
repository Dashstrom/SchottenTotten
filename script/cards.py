"""
Script for generate dummy card.
"""
import pathlib
from PIL import Image, ImageDraw

COLOR = {
    "red": (255, 0, 0),
    "green": (0, 255, 0),
    "blue": (0, 0, 255),
    "yellow": (255, 255, 0),
    "purple": (128, 0, 128),
    "brown": (165, 42, 42),
}
DEST = pathlib.Path(__file__).parent.parent / "resources" / "cards"


def generate_cards() -> None:
    rx, ry = 3.5, 2.5
    size = 16
    DEST.mkdir(parents=True, exist_ok=True)
    for base, color in COLOR.items():
        for number in range(1, 10):
            im = Image.new("RGBA", (int(ry * size), int(rx * size)), color)
            draw = ImageDraw.Draw(im)
            draw.text((10, 10), str(number), (0, 0, 0))
            im.save(DEST / f"{base}-{number}.png")


if __name__ == "__main__":
    generate_cards()
