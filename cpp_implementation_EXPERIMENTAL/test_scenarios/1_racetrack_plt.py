import numpy as np
import matplotlib.pyplot as plt
import matplotlib.font_manager

# TUM Colors
TUM_blue = '#3070b3'
TUM_blue_dark = '#003359'
TUM_blue_medium = '#64A0C8'
TUM_blue_light = '#98C6EA'
TUM_grey_dark = '#9a9a9a'
TUM_orange = '#E37222'
TUM_green = '#A2AD00'


# filepath to .csv of RACETRACK:
filename_monte = 'inputs_tracks_monteblanco_2019.csv'
filepath_monte = '/Users/jens/Downloads/' + filename_monte


# Montecarlo Track Data
# get refline
refline_monte = np.genfromtxt(fname=filepath_monte, delimiter=",", skip_header=1, usecols=(0,1))

# get widths right/left
width_right_left_monte = np.genfromtxt(fname=filepath_monte, delimiter=",", skip_header=1, usecols=(2, 3))

# get normized normal vectors
# normvec_normalized_monte = np.genfromtxt(fname=filepath_monte, delimiter=";", skip_header=1, usecols=(4, 5))


# track bounds
# bound1_monte = refline_monte + normvec_normalized_monte * np.expand_dims(width_right_left_monte[:, 0], 1)
# bound2_monte = refline_monte - normvec_normalized_monte * np.expand_dims(width_right_left_monte[:, 1], 1)

# x_monte = list(bound1_monte[:, 0])
# y_monte = list(bound1_monte[:, 1])
# x_monte.append(None)
# y_monte.append(None)
# x_monte.extend(list(bound2_monte[:, 0]))
# y_monte.extend(list(bound2_monte[:, 1]))



# plt.figure(2, figsize=(2.88, 2.88))
# plt.axis('equal')
# plt.plot(x_monte, y_monte, "k-", linewidth=1.4, label="Bounds")
# plt.xticks(fontproperties=font, fontsize=11)
# plt.yticks(fontproperties=font, fontsize=11)
# plt.xlabel('x-Koordinate in m', fontproperties=font, fontsize=11)
# plt.ylabel('y-Koordinate in m', fontproperties=font, fontsize=11)
# plt.title('Monteblanco')
# plt.axis('off')



plt.figure(2, figsize=(4, 4.5))
plt.axis('equal')
plt.xticks(fontproperties='arial', fontsize=11)
plt.yticks(fontproperties='arial', fontsize=11)
plt.xlabel('x-Koordinate in m', fontproperties='arial', fontsize=11)
plt.ylabel('y-Koordinate in m', fontproperties='arial', fontsize=11)
# plt.title('Monteblanco')
plt.plot(refline_monte[:,0], refline_monte[:,1], "k-", linewidth=1.4, label="Bounds", color=TUM_blue)
# plt.plot(refline_monte[:,0]+width_right_left_monte[:,0], refline_monte[:,1]+width_right_left_monte[:,1], "r--")


plt.draw()
plt.show()
