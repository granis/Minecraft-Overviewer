#!/usr/bin/env python3
"""
Outputs a list of missing/un-implemented blocks and biomes.
"""
import sys, os
# incantation to be able to import overviewer_core
if not hasattr(sys, "frozen"):
    sys.path.insert(0, os.path.abspath(os.path.join(os.path.split(__file__)[0], '..')))

import argparse
from pathlib import Path
from pkgutil import get_data
import requests
from overviewer_core.world import RegionSet

BASEPATH = "https://raw.githubusercontent.com/PrismarineJS/minecraft-data/master/data"


def get_json(path):
    print(f"fetching {path}")
    r = requests.get(path)
    return r.json()


def check_missing(gamedata, existing, ver, what):

    notfound = 0
    numwhat = len(gamedata)
    
    for item in gamedata:
        tmp = f"minecraft:{item['name']}"
        if tmp not in existing:
            notfound += 1
            print(f"{tmp} is not added yet.")

    percent = 100 - (round((notfound / numwhat), 2)*100)
    print(f"\nOverviewer is missing {notfound} {what} from a total of {numwhat}.")
    print(f"Overviewer covers {percent}% of {what} from {ver}.\n")


def main(args):
    ver :str = args.clientversion
    paths = get_json(f"{BASEPATH}/dataPaths.json")
    rg = RegionSet(regiondir="", rel="")

    if ver not in paths["pc"]:
        print(f"Version {ver} was not found in {BASEPATH}/dataPaths.json")
        return
    
    blocks = get_json(f"{BASEPATH}/{paths['pc'][ver]['blocks']}/blocks.json")
    biomes = get_json(f"{BASEPATH}/{paths['pc'][ver]['biomes']}/biomes.json")

    check_missing(blocks, list(rg._blockmap.keys()), ver, "blocks")
    check_missing(biomes, rg._biomemap, ver, "biomes")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("-c", "--client-version",
                        action="store", type=str, dest="clientversion", required=True,
                        help="the minecraft client-version to compare with, for example: 1.19")
    args = parser.parse_args()
    main(args)
