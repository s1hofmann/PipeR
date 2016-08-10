#!/usr/bin/env python
# encoding: utf-8

from os import listdir, remove
from os.path import isfile, isdir, exists, abspath, join
from sys import exit
from argparse import ArgumentParser

def mixed_folder(output_file, input_dir, negative_prefix):
    """ Append to a label file for training of an SVM
        from a single folder containing positives and negatives
    """

    with open(output_file, 'a') as label_file: 
        for f in listdir(input_dir):
            for pre in negative_prefix:
                if(f.startswith(pre)):
                    label_file.write(join(abspath(input_dir), f) + " -1\n")
                else:
                    label_file.write(join(abspath(input_dir), f) + " 1\n")

def single_folder(output_file, input_dir, negative=False):
    """ Append files to a label file for training of an SVM
        from a folder containing only positives or negatives
    """

    with open(output_file, 'a') as label_file:
        for f in listdir(input_dir):
            if negative:
                label_file.write(join(abspath(input_dir), f) + " -1\n")
            else:
                label_file.write(join(abspath(input_dir), f) + " 1\n")

if __name__ == "__main__":
    parser = ArgumentParser(description='Generate labelfiles.')
    parser.add_argument("output", default="./labels.dat", type=str, nargs=1)
    parser.add_argument("--positives", default=[], type=str, nargs='+',
                    help="Positive image folders.")
    parser.add_argument("--negatives", default=[], type=str, nargs='+',
                    help="Negative image folders.")
    parser.add_argument("--folders", default=[], type=str, nargs='+', help="Mixed input folders.")
    parser.add_argument("--prefix", default="neg", type=str, nargs=1, help="Prefix of negative samples.")
    parser.add_argument("-f", default=False, action='store_true', help="Force output.")

    args = parser.parse_args()

    output_file = abspath(args.output[0])

    if exists(output_file):
        if args.f:
            remove(output_file)
        else:
            print("Output file exists. Force overwrite by passing option -f.")
            print("Aborting.")
            exit(-1)

    if len(args.positives) and len(args.negatives):
        for pos_dir in args.positives:
            single_folder(output_file, pos_dir, False)
        for neg_dir in args.negatives:
            single_folder(output_file, neg_dir, True)
    elif len(args.folders):
        for input_dir in args.folders:
            mixed_folder(output_file, input_dir, args.prefix)
    else:
        print("No input folder(s) given. Aborting.")
        exit(-1)
