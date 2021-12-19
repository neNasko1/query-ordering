from hilbertcurve.hilbertcurve import HilbertCurve

def get_points(xy, order):
    offset = (xy[2] - xy[0]) / pow(2, order)

    hilbert_curve = HilbertCurve(order, 2)
    distances = list(range(pow(2, 2 * order)))
    points = hilbert_curve.points_from_distances(distances)

    ret = []
    for p in points:
        ret.append([xy[0] + p[0] * offset + offset / 2, xy[1] + p[1] * offset + offset / 2])

    return ret

def draw_curve(xy, order, rot = 0, shift=None):
    points = get_points(xy, order)
    if rot == 1:
        points = map(lambda x : [x[1] - xy[1] + xy[0], x[0] - xy[0] + xy[1]], points)
    elif rot == 2:
        points = map(lambda x : [xy[3] - x[1] + xy[0], xy[2] - x[0] + xy[1]], points)        

    print('\\draw [-stealth' + ('' if shift == None else (',xshift='+str(shift[0])+'cm,yshift='+str(shift[1]))+'cm') + ']', end = ' ')
    for ind, p in enumerate(points):
        if ind == 0:
            print('(', p[0], ',', p[1], ')', end='', sep='')
        else:
            print('--(', p[0], ',', p[1], ')', end='', sep='')
    print(';')
    
    '''
    for ind, p in enumerate(points):
        print('\\node[align=center] at (' + str(p[0] + (0 if shift == None else shift[0])) + ',' +  str(p[1] + (0 if shift == None else shift[1])) + ') {' + str(ind) + '};')
    '''
    offset = (xy[2] - xy[0]) / pow(2, order)
    print('\\draw [step=', offset, 'cm, black' + ('' if shift == None else (',xshift='+str(shift[0])+'cm,yshift='+str(shift[1]))+'cm') + '] (', xy[0], ',', xy[1], ') grid (', xy[2], ',', xy[3], ');', sep='')


def draw_hilbertian(xy, N, points, shift = None):
    offset = (xy[2] - xy[0]) / N
    points = [[xy[0] + p[0] * offset + offset / 2, xy[1] + p[1] * offset + offset / 2] for p in points]

    print('\\draw [-stealth' + ('' if shift == None else (',xshift='+str(shift[0])+'cm,yshift='+str(shift[1]))+'cm') + ']', end = ' ')
    for ind, p in enumerate(points):
        if ind == 0:
            print('(', p[0], ',', p[1], ')', end='', sep='')
        else:
            print('--(', p[0], ',', p[1], ')', end='', sep='')
    print(';')

    print('\\draw [step=', offset, 'cm, black' + ('' if shift == None else (',xshift='+str(shift[0])+'cm,yshift='+str(shift[1]))+'cm') + '] (', xy[0], ',', xy[1], ') grid (', xy[2], ',', xy[3], ');', sep='')    

beg = """
\\documentclass{article}
\\usepackage[utf8]{inputenc}
\\usepackage{tikz}

\\begin{document}

\\begin{figure}
\\begin{tikzpicture}[scale=0.75]
"""

end = """
\\end{tikzpicture}
\\end{figure}
\\end{document}
"""

print(beg)
draw_hilbertian([0, 0, 5, 5], 6, [[0,0],[1,0],[2,0],[2,1],[2,2],[1,2],[1,1],[0,1],[0,2],[0,3],[0,4],[0,5],[1,5],[2,5],[2,4],[1,4],[1,3],[2,3],[3,3],[3,4],[3,5],[4,5],[5,5],[5,4],[4,4],[4,3],[5,3],[5,2],[4,2],[3,2],[3,1],[3,0],[4,0],[4,1],[5,1],[5,0]], shift=[7.5,-5.5])
print(end)