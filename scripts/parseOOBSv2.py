#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 2 10:43:48 2022

@author: Ted
"""

import pandas as pd
import tkinter.filedialog as fd
from tkinter import Tk
import matplotlib as plt
import numpy as np

# %% load the data
root = Tk()
filenames = fd.askopenfilenames()
root.destroy()

#check for valid header on each file and record serial numbers
snList = []
goodFileList = []
for f in filenames:
    with open(f) as fOpen:
        headerLines = fOpen.readlines(100)
        if ('OpenOBS SN:' in headerLines[2]):
            #found the correct header in this file.
            snPosition = headerLines[2].find(':')+1
            snList.append(int(headerLines[2][snPosition:-1]))
            goodFileList.append(f)
        else:
            print('\nWARNING: missing header from file \"{filename}\"\n'.format(filename=f))
            continue
    
#check if we have matching serial numbers
nUniqueSN = len(set(snList))
if  nUniqueSN == 0:
    raise SystemExit('ERROR: No valid files found')
if nUniqueSN > 1:
    raise SystemExit(f'ERROR: Multiple SNs found: {snList}')

#read all the data into one dataframe
df = pd.concat((pd.read_csv(f,header=3) for f in goodFileList))



df.columns = ['unixTime','background','reading']
df['time'] = pd.to_datetime(df['unixTime'],unit='s')



# %% save and plot
#save the data
# savepath = fd.asksaveasfilename()
# if savepath:
#     if not savepath.endswith('.csv'): savepath+='.csv' 
#     df_burst.to_csv(savepath)
# else:
#     print('\nData not saved to file\n')


df.plot('time','reading')

    