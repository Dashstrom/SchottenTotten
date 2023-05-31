"""Script for croping images."""
import pathlib
from collections import deque
from typing import Iterator, List, Tuple

import click
import cv2
import numpy as np
import numpy.typing as npt


def autocrop(im: npt.NDArray[np.uint8]) -> npt.NDArray[np.uint8]:
    """Crop tranparent border."""
    coords = np.column_stack(np.where(im[:, :, 3] > 0))
    min_: Tuple[int, int] = coords.min(axis=0)
    max_: Tuple[int, int] = coords.max(axis=0)
    return im[min_[0] : max_[0] + 1, min_[1] : max_[1] + 1]


def extract(
    arr: npt.NDArray[np.uint8],
    threshold: int = 32,
    distance: int = 2,
    minpix: int = 10,
) -> Iterator[npt.NDArray[np.uint8]]:
    """Extract all part of an transparent image."""
    rows, cols = arr.shape[:2]
    stack = deque((x, y) for y in range(rows) for x in range(cols))
    explored = np.where(arr[:, :, 3] < threshold, True, False)
    points = list(range(-distance, distance + 1))
    di = [(dx, dy) for dx in points for dy in points if dx != 0 and dy != 0]
    while stack:
        x, y = stack.pop()
        if explored[y, x]:
            continue
        explored[y, x] = True
        area = set()
        active_area = {(x, y)}
        while active_area:
            x, y = active_area.pop()
            area.add((x, y))
            for dx, dy in di:
                ax = x + dx
                ay = y + dy
                if 0 <= ay < rows and 0 <= ax < cols and not explored[ay, ax]:
                    explored[ay, ax] = True
                    active_area.add((ax, ay))
        if len(area) >= minpix:
            sub = np.zeros(arr.shape, dtype=arr.dtype)
            for x, y in area:
                sub[y, x] = arr[y, x]
            yield autocrop(sub)


@click.command()
@click.argument("source", type=click.Path(exists=True))
@click.argument("destination", type=click.Path())
@click.option("-s", "--skip", multiple=True)
def cropping(source: str, destination: str, skip: List[str]) -> None:
    """Extract and crop all sub images in a transparent image."""
    src_path = pathlib.Path(source)
    dst_path = pathlib.Path(destination)
    src = cv2.imread(src_path.as_posix(), cv2.IMREAD_UNCHANGED)
    dst_path.mkdir(parents=True, exist_ok=True)
    counter = 0
    for i, im in enumerate(extract(src)):
        if str(i) in skip:
            continue
        child_path = dst_path / f"{src_path.stem}.{counter}{src_path.suffix}"
        cv2.imwrite(
            child_path.as_posix(),
            im,
            [cv2.IMWRITE_PNG_COMPRESSION, 9],
        )
        counter += 1


if __name__ == "__main__":
    cropping()  # pylint: disable=locally-disabled, no-value-for-parameter
