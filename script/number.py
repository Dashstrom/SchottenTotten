from PIL import Image, ImageDraw, ImageFont
import os
import pathlib

def get_image_list(directory):
    image_list = []
    for file_name in os.listdir(directory):
        if file_name.lower().endswith(('.jpg', '.png')):
            image_path = os.path.join(directory, file_name)
            image_list.append(image_path)
    return image_list


def convert_images(image_list):
    for image_path in image_list:
        image_name, image_ext = os.path.splitext(image_path)
        image_name_parts = os.path.basename(image_name).split('-')

        # Récupère la couleur et le numéro à partir du nom du fichier
        color = image_name_parts[0]
        number = image_name_parts[-1]

        image = Image.open(image_path)

        # Conversion en mode RVB si l'image est en mode RGBA
        if image.mode == 'RGBA':
            image = image.convert('RGB')

        width, height = image.size
        draw = ImageDraw.Draw(image)
        font_size = min(width,
                        height) // 10  # Taille de police proportionnelle à la taille de l'image
        font = ImageFont.truetype('arial.ttf', font_size)

        text_width, text_height = draw.textsize(number, font)

        # Détermine la couleur du texte en fonction du nom de fichier
        if color.lower() == 'purple':
            text_color = (128, 0, 128)  # Pourpre (RVB)
        elif color.lower() == 'green':
            text_color = (0, 128, 0)  # Vert (RVB)
        elif color.lower() == 'red':
            text_color = (255, 0, 0)  # Rouge (RVB)
        elif color.lower() == 'orange':
            text_color = (255, 165, 0)  # Orange (RVB)
        elif color.lower() == 'yellow':
            text_color = (255, 255, 0)  # Jaune (RVB)
        elif color.lower() == 'blue':
            text_color = (0, 0, 255)  # Bleu (RVB)
        else:
            text_color = (0, 0, 0)  # Noir (RVB)

        # Écrit le numéro dans chaque coin de l'image avec contour noir et marge proportionnelle
        border_width = max(1,
                           int(font_size * 0.08))  # Largeur du contour proportionnelle à la taille de la police
        margin = max(1,
                     int(font_size * 0.1))  # Marge proportionnelle à la taille de la police
        draw.text((0 + margin, 0 + margin), number, font=font, fill=text_color,
                  stroke_width=border_width, stroke_fill=(0, 0, 0))
        draw.text((width - text_width - margin, 0 + margin), number, font=font,
                  fill=text_color, stroke_width=border_width,
                  stroke_fill=(0, 0, 0))
        draw.text((0 + margin, height - text_height - margin), number,
                  font=font, fill=text_color, stroke_width=border_width,
                  stroke_fill=(0, 0, 0))
        draw.text((width - text_width - margin, height - text_height - margin),
                  number, font=font, fill=text_color,
                  stroke_width=border_width, stroke_fill=(0, 0, 0))

        # Enregistre l'image avec les numéros dans chaque coin
        output_path = f"{image_name}{image_ext}"
        image.save(output_path)

        print(f"L'image {image_path} a été convertie en {output_path}.")

def convert_to_png(directory):
    image_list = [file_name for file_name in os.listdir(directory) if file_name.lower().endswith(('.jpg', '.jpeg'))]
    for image_name in image_list:
        image_path = os.path.join(directory, image_name)
        image = Image.open(image_path)
        image_name_without_ext = os.path.splitext(image_name)[0]
        output_path = os.path.join(directory, f"{image_name_without_ext}.png")
        image.save(output_path, "PNG")
        print(f"L'image {image_path} a été convertie en {output_path}.")

# Liste des images à traiter
image_list = get_image_list("../resources/cards_customs")
print(image_list)

convert_to_png("../resources/cards_customs")
#convert_images(image_list)
