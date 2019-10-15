#!/usr/bin/env python

"""
Command line utility for plotting MAP-Elites maps
"""

import argparse
import csv
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import numpy as np
import os.path
import re


def _search_directory(directory):
    """Helper function to recursively traverse directory searching for
    MAP-Elites CSV files"""
    result = []
    for root, _, files in os.walk(directory):
        for fil in files:
            if fil.endswith('.csv'):
                result.append(os.path.join(root, fil))
    return result


def _check_map_csv(files):
    """Helper function to ensure that the given list CSV file is most likely a
    MAP-Elites map"""
    checked = []
    for fil in files:
        if re.search('map_generation_[0-9]+', fil):
            checked.append(fil)
    return checked


def _parse_map(fil):
    """Read 'fil' and create numpy array with data"""
    with open(fil, 'r') as csvfile:
        reader = csv.reader(csvfile)
        _ = next(reader)
        map_dict = {}
        size_x = 0
        size_y = 0
        for row in reader:
            if row:
                x = int(row[0])
                y = int(row[1])
                fitness = float(row[2])
                if fitness != -1:
                    map_dict[(x, y)] = fitness
                    size_x = max(x, size_x)
                    size_y = max(y, size_y)
    data = np.zeros((size_x + 1, size_y + 1))
    for (x, y), fit in map_dict.items():
        data[x, y] = fit
    return data


def _plot_map(data, title=None):
    """Plot map"""
    im = plt.imshow(data.T, origin='lower')
    im.set_interpolation('nearest')
    plt.colorbar()
    if title:
        plt.title(title)
    return im


if __name__ == '__main__':
    # Parse command line arguments
    parser = argparse.ArgumentParser(description="MAP-Elites plotting utility")
    parser.add_argument('file', nargs='+',
                        help="File to convert or folder to search")
    parser.add_argument('--interactive', '-i', action='store_true',
                        help="Plot to screen instead of to file")
    parser.add_argument('--format', choices=['pdf', 'svg', 'png', 'jpeg'],
                        default='pdf', help="Image format when saving")
    args = parser.parse_args()
    # Create an overview of files to convert
    files = []
    for fil in args.file:
        if os.path.isfile(fil) and fil.endswith('.csv'):
            # It looks like a CSV file, simply add it
            files.append(fil)
        elif os.path.isdir(fil):
            # Search directory for files
            files.extend(_search_directory(fil))
        else:
            print("'{!s}' does not seem to be a folder nor a CSV file"
                  .format(fil))
    # Check all files to ensure that we can read maps in CSV style from them
    files = _check_map_csv(files)
    # For each file create PDF output with matplotlib
    for fil in files:
        # Parse and create data to plot
        map_array = _parse_map(fil)
        data = np.ma.masked_where(map_array == 0, map_array)
        # Create new filename
        name, _ = os.path.splitext(fil)
        generation = re.search('map_generation_([0-9]+)',
                               os.path.basename(name)).group(1)
        title = "Generation {}".format(generation) if generation else None
        # Plot to file
        fig = plt.figure()
        _plot_map(data, title)
        if args.interactive:
            plt.show()
        else:
            plt.savefig(name + '.' + args.format, format=args.format)
