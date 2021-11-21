import csv
import math

def main():
    with open('./lights.csv', 'r') as infile, open('./lights.txt', 'w') as outfile:
        reader = csv.reader(infile)

        next(reader, None)

        points = []
        for line in reader:
            for element in line[1:]:
                points.append(element.split(','))

        np = 0
        for point in points:
            outfile.write(f'{point[0]:>2},{point[1]:>2},  ')
            np += 1
            if np % 10 == 0:
                outfile.write("\n")

        outfile.write("\n\n")
        
        np = 0
        for point in points:
            x = int((float(point[0]) /20) * 255)
            y = int((float(point[1]) /31) * 255)
            outfile.write(f'{x:>3},{y:>3},  ')
            np += 1
            if np % 10 == 0:
                outfile.write("\n")

        outfile.write("\n\n")
        np = 0
        for point in points:
            t = calc_angle(point)
            outfile.write(f'{t:>4}, ')
            np += 1
            if np % 10 == 0:
                outfile.write("\n")
    
def calc_angle(point):
    x = -(int(point[0]) - 10)
    y = int(point[1]) - 15
    if x == 0:
        t = 90 if y > 0 else -90
    else:
        t = math.degrees(math.atan2(y, x))
    if t < 0:
        t += 360
    return round(t * 255 / 360)

if __name__ == "__main__":
    main()
