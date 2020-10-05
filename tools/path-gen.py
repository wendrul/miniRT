import numpy as np
import sys
import math as m

def readArguments():
    if (len(sys.argv) != 6):
        return ((0,0,20), 10, 20)
    else:
        return ((float(sys.argv[1]), float(sys.argv[2]), float(sys.argv[3])), float(sys.argv[4]), int(sys.argv[5]))

def getCoordsOnCircle(center, radius, angle):
    return [center[0] + radius * m.cos(angle), 0, center[2] + radius * m.sin(angle)]

def getNormalFromAngle(center, angle):
    (x,y,z) = getCoordsOnCircle(center, 1, angle)
    return (center[0] - x, center[1] - y, center[2] - z)

def main():
    (center, radius, N) = readArguments()
    points = []
    fov = 70
    for i in range(N):
        a = (m.pi / N) * 2 * i
        points.append((getCoordsOnCircle(center, radius, a), getNormalFromAngle(center, a)))
    coords = [points[i][0] for i in range(N)]
    normal = [points[i][1] for i in range(N)]
    for i in range(N):
        print(f"c {coords[i][0]:.2f},{coords[i][1]:.2f},{coords[i][2]:.2f}    {normal[i][0]:.2f},{normal[i][1]:.2f},{normal[i][2]:.2f}, {fov}")

main()
    
