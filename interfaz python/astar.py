import pygame
import math
from queue import PriorityQueue

WIDTH = 800
WIN = pygame.display.set_mode((WIDTH, WIDTH))
pygame.display.set_caption(" Práctica IA: A* Path Finding algoritmo")

# COLORES para el camino y la interfaz en sí
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 255, 0)
YELLOW = (255, 255, 0)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
PURPLE = (128, 0, 128)
ORANGE = (255, 165 ,0)
GREY = (128, 128, 128)
TURQUOISE = (64, 224, 208)

class Spot:
	def __init__(self, row, col, width, total_rows):
		self.row = row
		self.col = col          # ahora determinamos las posiciones de cada punto
		self.x = row * width
		self.y = col * width
		self.color = WHITE      # por defecto el color será blanco
		self.vecino = []
		self.width = width
		self.total_rows = total_rows

	def get_pos(self):
		return self.row, self.col

	def is_closed(self):
		return self.color == RED

	def is_open(self):
		return self.color == GREEN

	def is_obstaculo(self):
		return self.color == BLACK

	def is_start(self):
		return self.color == ORANGE

	def is_end(self):
		return self.color == TURQUOISE

                        # Devolvemos los colores
	def reset(self):
		self.color = WHITE

	def make_crear(self):
		self.color = ORANGE

	def make_leido(self):
		self.color = RED

	def make_leer(self):
		self.color = GREEN

	def make_obstaculo(self):
		self.color = BLACK

	def make_fin(self):
		self.color = TURQUOISE

	def crear_camino(self):
		self.color = PURPLE

	def draw(self, win):        # donde dibujar la interfaz
		pygame.draw.rect(win, self.color, (self.x, self.y, self.width, self.width))

	def update_vecino(self, grid):		# En este caso el movimiento es en 4-way
		self.vecino = []
		if self.row < self.total_rows - 1 and not grid[self.row + 1][self.col].is_obstaculo(): 	# Haremos que vaya hacia abajo en caso de que pueda
			self.vecino.append(grid[self.row + 1][self.col])

		if self.row > 0 and not grid[self.row - 1][self.col].is_obstaculo(): 						# Haremos que vaya hacia arriba en caso de que pueda
			self.vecino.append(grid[self.row - 1][self.col])

		if self.col < self.total_rows - 1 and not grid[self.row][self.col + 1].is_obstaculo(): 	# Haremos que vaya hacia la derecha en caso de que pueda
			self.vecino.append(grid[self.row][self.col + 1])

		if self.col > 0 and not grid[self.row][self.col - 1].is_obstaculo(): 						# Haremos que vaya hacia la izquierda en caso de que pueda
			self.vecino.append(grid[self.row][self.col - 1])

    # compara un spot con otro cualquiera
	def __lt__(self, other):
		return False


def h(p1, p2):
    # serán los componentes de la función h
    x1, y1 = p1
    x2, y2 = p2
    return abs(x1 - x2) + abs(y1 - y2)


def reconstruir_camino(came_from, current, draw):		# Recorreremos el camino desde el final (current) hasta el inicio
	while current in came_from:							# Si current está en la tabla que revisa de donde vino cada nodo
		current = came_from[current]					# Current será el último nodo (punto final)
		current.crear_camino()							# Construimos el camino
		draw()											# Pintamos el camino


def algoritmo(draw, grid, start, end):
	count = 0
	open_set = PriorityQueue()										# Pillaremos el elemento más pequeño del queue, es bastante eficiente
	open_set.put((0, count, start))  								# Ponemos las celdas en una queue para por así decirlo nombrarlas como "leídas"
	came_from = {}													# Guardará de donde vino cada celda
	g_score = {spot: float("inf") for row in grid for spot in row}  # Es un for row for spot hasta el infinito
	g_score[start] = 0    											# El coste inicial es 0
	f_score = {spot: float("inf") for row in grid for spot in row}
	f_score[start] = h(start.get_pos(), end.get_pos())   			# La distancia h desde el punto final hasta el inicial, es decir, la heurística

	open_set_hash = {start}											# Revisamos que los valores de PriorityQueue al guardarlos en la hash

	while not open_set.empty():   									# Si no encontramos el camino, entonces no hay camino
		for event in pygame.event.get():
			if event.type == pygame.QUIT:  							# Damos la opción de poder darle a la X
				pygame.quit()

		current = open_set.get()[2]  					# Pillamos el node del menor coste de la queue
		open_set_hash.remove(current)   				# Revisamos que no esté duplicado

		if current == end:              				# Si el de menor coste es el final, reconstruimos el camin
			reconstruir_camino(came_from, end, draw)  	# Dibujamos el camino óptimo
			end.make_fin()								# Si no lo ponemos, dibujaría encima del punto final
			return True									# Retornamos que hubo camino

		for neighbor in current.vecino:
			temp_g_score = g_score[current] + 1			# Asumimos que asumimos que todos los ejes son 1,
														# pues añadidmos 1 porque estamos a 1 nodo masde distancia

			if temp_g_score < g_score[neighbor]:											# Intentamos determinar el mejor camino desde cada nodo
				came_from[neighbor] = current
				g_score[neighbor] = temp_g_score											# Calculamos el coste temporal
				f_score[neighbor] = temp_g_score + h(neighbor.get_pos(), end.get_pos()) 	# Actualizamos el camino porque tiene menos coste
				if neighbor not in open_set_hash:											# Revisamos si el vecino está en la hash
					count += 1
					open_set.put((f_score[neighbor], count, neighbor))
					open_set_hash.add(neighbor)
					neighbor.make_leer()													# Guardaremos el vecino del recorrido

		draw()

		if current != start:						# Si el nodo que acabamos de mirar no es el punto de inicio, no lo consideramos
			current.make_leido()

	return False									# Retornamos que no encontramos el camino


def make_grid(rows, width): 				# Estructura de datos para manipular el grid
    grid = []
    gap = width // rows  					# Definimos el ancho que debería de tener cada gap
    for i in range(rows):
        grid.append([])
        for j in range(rows):
            spot = Spot(i, j, gap, rows)  	# Ahora que creamos el spot, lo añadimos al grid
            grid[i].append(spot)

    return grid


def dibujar_grid(win, rows, width):
    gap = width // rows
    for i in range(rows):													# Por cada row dibujaremos una linea horizontal
        pygame.draw.line(win, GREY, (0, i * gap), (width, i * gap)) 		# De esta manera dibujará lineas horizontales hacia abajo
        for j in range(rows):
            pygame.draw.line(win, GREY, (j * gap, 0), (j * gap, width)) 	# De esta manera hacemos lo mismo pero en vertical


def dibujar(win, grid, rows, width):
	win.fill(WHITE)                					# No es muy eficiente pero al menos funciona

	for row in grid:
		for spot in row:
			spot.draw(win)         					# Va por todas las row y grid y dibuja todos los spots

	dibujar_grid(win, rows, width)
	pygame.display.update()       					# Que recoja lo que hicimos y que lo implemente en la interfaz


def get_clicked_pos(pos, rows, width):
	gap = width // rows
	y, x = pos     							# Pillamos la posicion que sea de x e y

											# La dividimos por la anchura de la celda
	row = y // gap
	col = x // gap

	return row, col


def main(win, width):
	ROWS = 100
	grid = make_grid(ROWS, width)  			# Creamos la interfaz 2D

	start = None  							# Trackeamos el start y la posicion
	end = None

	run = True   							# Para que se active
	while run:
		dibujar(win, grid, ROWS, width)
		for event in pygame.event.get():  	# Chequeamos las condiciones
			if event.type == pygame.QUIT: 	# Si presionamos la X, cerramos
				run = False

			if pygame.mouse.get_pressed()[0]: 						# Click izquierdo
				pos = pygame.mouse.get_pos()  						# Guardamos la posición seleccionada
				row, col = get_clicked_pos(pos, ROWS, width) 		# Obtenemos la fila y col de la posición
				spot = grid[row][col]             					# Lo guardamos en el Spot
				if not start and spot != end:						# Si presionamos el botón izquierdo y no hay punto inicial, lo colocamos
					start = spot
					start.make_crear()

				elif not end and spot != start:						# Si presionamos el botón izquierdo y no hay punto final, lo colocamos
					end = spot
					end.make_fin()

				elif spot != end and spot != start:					# Si presionamos el botón izquierdo y no hay obstáculo, lo colocamos
					spot.make_obstaculo()

			elif pygame.mouse.get_pressed()[2]: 					# Si presionamos el botón derecho, eliminamos lo que hayamos colocado
				pos = pygame.mouse.get_pos()
				row, col = get_clicked_pos(pos, ROWS, width)
				spot = grid[row][col]
				spot.reset()
				if spot == start:
					start = None
				elif spot == end:
					end = None

			if event.type == pygame.KEYDOWN:   							# Haremos que si le damos al espacio, empieza la ejecución
				if event.key == pygame.K_SPACE and start and end:		# Aseguramos que tenemos punto inicial, punto fianl y le damos al espacio
					for row in grid:
						for spot in row:
							spot.update_vecino(grid)  							 		# Va a ir recorriendo la s celdas vecinas del Spot

					algoritmo(lambda: dibujar(win, grid, ROWS, width), grid, start, end) 		# Una vez la recorre llamamos al algoritmo
				if event.key == pygame.K_c:													# Reseteamos el grid si le damos a la c
					start = None
					end = None
					grid = make_grid(ROWS, width)											# Lo reseteamos en blanco

	pygame.quit()

main(WIN, WIDTH)