import io
from math import ceil
from PIL import Image, ImageDraw, ImageFont
import os
import pathlib
from typing import List

DIRECTORY = pathlib.Path(__file__).parent.parent / "resources" / "bases"
OUTPUT = pathlib.Path(__file__).parent.parent / "resources" / "cards"
W, H = 644, 900


def numbering(directory: pathlib.Path, output: pathlib.Path) -> None:
    """Numbering each card."""
    output.mkdir(parents=True, exist_ok=True)
    paths: List[pathlib.Path] = []
    for pattern in ("**/*.png", "**/*.jpeg", "**/*.jpg"):
        paths.extend(directory.glob(pattern))
    paths.sort()
    for path in paths:
        image_name_parts = path.stem.split("-")
        color = image_name_parts[0]
        number = image_name_parts[-1]

        with Image.open(path) as image, io.BytesIO() as stream:
            if image.mode == "RGBA":
                image = image.convert("RGB")

            width, height = image.size
            if width != W or height != H:
                image.thumbnail((W, H), Image.LANCZOS)
                new_image = Image.new("RGB", (W, H), (255, 255, 255))
                new_image.paste(
                    image, ((W - image.width) // 2, (H - image.height) // 2)
                )
                image = new_image
                width, height = image.size
                print(width, height)

            draw = ImageDraw.Draw(image)
            font_size = min(width, height) // 6
            font = ImageFont.truetype("arial.ttf", font_size)
            x1, y1, x2, y2 = draw.textbbox((5, 5), number, font)
            text_width, text_height = x2 - x1, y2 - y1
            colors = {
                "purple": (128, 0, 128),
                "green": (0, 128, 0),
                "red": (255, 0, 0),
                "orange": (255, 165, 0),
                "yellow": (255, 255, 0),
                "blue": (0, 0, 255),
            }
            text_color = colors.get(color)
            if text_color is None:
                continue
            border_width = max(1, ceil(font_size * 0.08))
            margin = max(1, ceil(font_size * 0.15))
            for box in (
                (margin, margin),
                (width - text_width - margin, margin),
                (margin, height - text_height - margin * 3),
                (
                    width - text_width - margin,
                    height - text_height - margin * 3,
                ),
            ):
                draw.text(
                    box,
                    number,
                    font=font,
                    fill=text_color,
                    stroke_width=border_width,
                    stroke_fill=(0, 0, 0),
                )

            output_path = output / path.with_suffix(".jpg").name
            image.save(output_path)

            print(f"L'image {path.name} a été convertie en {output_path.name}")


if __name__ == "__main__":
    numbering(DIRECTORY, OUTPUT)
