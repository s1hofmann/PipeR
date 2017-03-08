#!/usr/bin/env python

import cv2
import numpy as np
import xml.etree.ElementTree as ET
from os.path import join, split, splitext, abspath
from sys import argv
from argparse import ArgumentParser

class VersionInfo(object):
    @staticmethod
    def major():
        return int(cv2.__version__.split('.')[0])

    @staticmethod
    def minor():
        return int(cv2.__version__.split('.')[1])

    @staticmethod
    def patch():
        return int(cv2.__version__.split('.')[2])


class Rect(object):
    def __init__(self, x, y, width, height):
        self._x = x
        self._y = y
        self._width = width
        self._height = height

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    @property
    def width(self):
        return self._width

    @property
    def height(self):
        return self._height

    @property
    def shape(self):
        return [self._x, self._y, self._width, self._height]

    def __str__(self):
        return "".join(["[", ",".join([str(self._x), str(self._y), str(self._width), str(self.height)]), "]"])


class AnnotationObject(object):
    def __init__(self, filename):
        self._filename = filename
        self._bounding_boxes = []

    def add_box(self, x, y, width, height):
        self._bounding_boxes.append(Rect(x, y, width, height))

    @property
    def filename(self):
        return self._filename

    @property
    def bounding_boxes(self):
        return self._bounding_boxes

    @property
    def empty(self):
        return len(self._bounding_boxes) == 0

    @property
    def size(self):
        return len(self._bounding_boxes)


class AnnotationFile(object):
    def __init__(self, annotation_file):
        self._tree = ET.parse(annotation_file)
        self._root = self._tree.getroot()
        self._annotation_objects = []
        version = VersionInfo.major()

        for elem in self._root.iter('file'):
            ao = AnnotationObject(elem.attrib['filename'])
            for o in elem.iter('object'):
                for box in o.findall('bbox'):
                    coords = box.text.split(",")
                    ao.add_box(float(coords[0]), float(coords[1]), float(coords[2]), float(coords[3]))
                for poly in o.findall('fixpoints'):
                    coords = []
                    points = poly.text.split(",")
                    if version == 2:
                        for idx in range(0, len(points) - 1, 2):
                            coords.append([[float(points[idx]), float(points[idx + 1])]])
                    elif version == 3:
                        for idx in range(0, len(points) - 1, 2):
                            coords.append([float(points[idx]), float(points[idx + 1])])
                    rect = cv2.boundingRect(np.array(coords, dtype=np.float32))
                    ao.add_box(rect[0], rect[1], rect[2], rect[3])
            if not ao.empty:
                self._annotation_objects.append(ao)

    @property
    def size(self):
        return len(self._annotation_objects)

    @property
    def annotation_objects(self):
        return self._annotation_objects


class SampleGenerator(object):
    def __init__(self, working_dir, width, height, positive_folder, negative_folder, max_per_class=100):
        self._working_dir = working_dir
        self._width = width
        self._height = height
        self._positive_folder = positive_folder
        self._negative_folder = negative_folder
        self._max_per_class = max_per_class

    def process(self, annotation_file):
        af = AnnotationFile(annotation_file)
        print("Processing {} objects.".format(len(af.annotation_objects)))
        idx = 0
        for ao in af.annotation_objects:
            img = cv2.imread(join(self._working_dir, ao.filename))
            file_ext = splitext(ao.filename)[-1]
            if img is not None:
                samples_per_bounding_box = int(self._max_per_class / len(ao.bounding_boxes))
                min_x = 10000
                max_x = -10000
                min_y = 10000
                max_y = -10000
                for bbox in ao.bounding_boxes:
                    for i in range(samples_per_bounding_box):
                        min_x = min(min_x, bbox.x)
                        max_x = max(max_x, bbox.x + bbox.width)
                        min_y = min(min_y, bbox.y)
                        max_y = max(max_y, bbox.y + bbox.height)
                        left = bbox.x
                        right = bbox.x + bbox.width - self._width
                        top = bbox.y
                        bottom = bbox.y + bbox.height - self._height
                        if right <= left or bottom >= top:
                            continue
                        else:
                            x = np.random.randint(left, right)
                            y = np.random.randint(top, bottom)
                            filename = "".join(["_".join(split(annotation_file)[-1].split(".")[:-1]), '_', str(idx), file_ext])
                            cv2.imwrite(join(self._positive_folder, filename), img[x:x+self._width, y:y+self._height])
                            idx += 1

                left_range = min_x - self._width
                right_range = img.shape[0] - max_x - self._width
                top_range = min_y - self._height
                bottom_range = img.shape[1] - max_y - self._height
                step_size = int(left_range > 0) + int(right_range > 0) + int(top_range > 0) + int(bottom_range > 0)
                for i in range(0, self._max_per_class, step_size):
                    if left_range > 0:
                        y = np.random.randint(0, img.shape[1] - self._height)
                        x = np.random.randint(0, left_range)
                        filename = "".join(["_".join(split(annotation_file)[-1].split(".")[:-1]), '_', str(idx), file_ext])
                        snippet = img[x:x+self._width, y:y+self._height]
                        if snippet.size > 0:
                            cv2.imwrite(join(self._negative_folder, filename), snippet)
                            idx+=1
                    if right_range > 0:
                        y = np.random.randint(0, img.shape[1] - self._height)
                        x = np.random.randint(max_x, img.shape[0] - self._width)
                        filename = "".join(["_".join(split(annotation_file)[-1].split(".")[:-1]), '_', str(idx), file_ext])
                        snippet = img[x:x+self._width, y:y+self._height]
                        if snippet.size > 0:
                            cv2.imwrite(join(self._negative_folder, filename), snippet)
                            idx+=1

                    if top_range > 0:
                        y = np.random.randint(0, top_range)
                        x = np.random.randint(0, img.shape[0] - self._width)
                        filename = "".join(["_".join(split(annotation_file)[-1].split(".")[:-1]), '_', str(idx), file_ext])
                        snippet = img[x:x+self._width, y:y+self._height]
                        if snippet.size > 0:
                            cv2.imwrite(join(self._negative_folder, filename), snippet)
                            idx+=1
                    if bottom_range > 0:
                        y = np.random.randint(max_y, img.shape[1] - self._height)
                        x = np.random.randint(0, img.shape[0] - self._width)
                        filename = "".join(["_".join(split(annotation_file)[-1].split(".")[:-1]), '_', str(idx), file_ext])
                        snippet = img[x:x+self._width, y:y+self._height]
                        if snippet.size > 0:
                            cv2.imwrite(join(self._negative_folder, filename), snippet)
                            idx+=1


if __name__ == '__main__':
    parser = ArgumentParser(description='Generate samples.')
    parser.add_argument("--annotation_file", type=str,
                        help="Input file")
    parser.add_argument("--pos_folder", type=str,
                        help="Positive images output folders.")
    parser.add_argument("--neg_folder", type=str,
                        help="Negative images output folders.")
    parser.add_argument("--working_dir", default=".", type=str,
                        help="Working directory.")
    parser.add_argument("--width", type=int,
                        help="Sample width.")
    parser.add_argument("--height", type=int,
                        help="Sample height.")

    args = parser.parse_args()

    if args.annotation_file is None or \
       args.working_dir is None or \
       args.pos_folder is None or \
       args.neg_folder is None or \
       args.width is None or \
       args.height is None:
        parser.print_help()
        exit(-1)

    input_file = abspath(args.annotation_file)
    working_dir = abspath(args.working_dir)
    positives_folder = abspath(args.pos_folder)
    negatives_folder = abspath(args.neg_folder)
    sample_width = args.width
    sample_height = args.height

    sg = SampleGenerator(working_dir, sample_width, sample_height, positives_folder, negatives_folder)
    sg.process(input_file)
