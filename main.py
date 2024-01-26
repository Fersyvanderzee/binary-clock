from PIL import Image, ImageDraw

IMG_WIDTH = 1000
IMG_HEIGHT = 500

time_patterns = {
    0: [0, 0, 0, 0],
    1: [0, 0, 1, 0],
    2: [1, 0, 0, 0],
    3: [0, 1, 0, 0],
    4: [0, 0, 0, 1],
    5: [1, 0, 1, 0],
    6: [1, 1, 0, 0],
    7: [0, 1, 0, 1],
    8: [0, 0, 1, 1],
    9: [1, 0, 1, 1],
    10: [1, 1, 1, 0],
    11: [1, 1, 0, 1]
}

image = Image.new('RGB', (IMG_WIDTH, IMG_HEIGHT), '#000000')

draw = ImageDraw.Draw(image)


def ellipse_block(xy: tuple, distance: int, circle_width: int, num_in_time: int):
    if num_in_time > 11:
        num_in_time -= 12

    x, y = xy

    pattern = time_patterns[num_in_time]

    render_points = [
        (x - distance, y - distance),
        (x + distance, y - distance),
        (x - distance, y + distance),
        (x + distance, y + distance)
    ]
    i = 0
    for render_point in render_points:
        on_off = pattern[i]

        if on_off == 0:
            fill = None
            outline = '#fff'
        else:
            fill = '#fff'
            outline = None

        ellipse_xy = (
            (render_point[0] - circle_width / 2, render_point[1] - circle_width / 2),
            (render_point[0] + circle_width / 2, render_point[1] + circle_width / 2)
        )

        draw.ellipse(xy=ellipse_xy, fill=fill, outline=outline, width=1)

        i += 1


def convert_time_stamp(time_stamp):
    converted_time_stamp = []
    time_stamp = time_stamp.split(':')
    hours, minutes = time_stamp

    converted_time_stamp.append(int(hours))
    for num in minutes:
        converted_time_stamp.append(int(num))


    return converted_time_stamp


base_y = IMG_HEIGHT / 2

time_stamp = '10:53'

converted_time = convert_time_stamp(time_stamp)

coords_x = [200, 600, 800]

i = 0
for num in converted_time:
    ellipse_block((coords_x[i], base_y), 50, 50, num)
    i += 1


draw.line(((400, 150), (400, 350)), fill='#fff', width=1)
image.show()
