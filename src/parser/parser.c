#include <raycaster.h>
#include <parser.h>
#include <fcntl.h>
#include <ft_string.h>
#include <ft_libft.h>
#include <ft_stdio/ft_printf.h>
#include <unistd.h>
#include <ft_memory.h>

void 	parseWalls(char *line, t_level *level) {
	if (ft_strncmp(line, "path=", 5) == 0) {
		for (int i = 0; i < WALL_TEXTURES; i++) {
			if (!level->wall[i].path) {
				level->wall[i].path = (line + 5);
				break;
			}
		}
	}
	else if (ft_strncmp(line, "id=", 3) == 0) {
		for (int i = 0; i < WALL_TEXTURES; i++) {
			if (!level->wall[i].id) {
				level->wall[i].id = line[3];
				break;
			}
		}
	}
}


void	parseSettings(char *data, t_level *level) {
	char **elements = ft_split(data, '\n');
//	free(data);
	if (!elements) {
		ERROR("Malloc fail!\n");
		return; // TODO proper cleanup
	}
	int index = 0;
	while (elements[index]) {
		if (ft_strcmp(elements[index], "@wall") == 0) {
			index++;
			while (elements[index] && ft_strcmp(elements[index], "@end") != 0) {
				parseWalls(elements[index], level);
				index++;
			}
		}
//		else if (ft_strcmp(elements[index], "@weapon") == 0) {
//			index++;
//			while (elements[index] && ft_strcmp(elements[index], "@end") == 0) {
//				parseWeapons(&elements[index]);
//				index++;
//			}
//		}
//		else if (ft_strcmp(elements[index], "@ammo") == 0) {
//			index++;
//			while (elements[index] && ft_strcmp(elements[index], "@end") == 0) {
//				parseAmmo(&elements[index]);
//				index++;
//			}
//		}
//		else if (ft_strcmp(elements[index], "@pickup") == 0) {
//			index++;
//			while (elements[index] && ft_strcmp(elements[index], "@end") == 0) {
//				parsePickups(&elements[index]);
//				index++;
//			}
//		}
//		else if (ft_strcmp(elements[index], "@enemy") == 0) {
//			index++;
//			while (elements[index] && ft_strcmp(elements[index], "@end") == 0) {
//				parseEnemies(&elements[index]);
//				index++;
//			}
//		}
//		else if (ft_strcmp(elements[index], "@object") == 0) {
//			index++;
//			while (elements[index] && ft_strcmp(elements[index], "@end") == 0) {
//				parseObjects(&elements[index]);
//				index++;
//			}
//		}
//		else if (ft_strcmp(elements[index], "@door") == 0) {
//			index++;
//			while (elements[index] && ft_strcmp(elements[index], "@end") == 0) {
//				parseDoors(&elements[index]);
//				index++;
//			}
//		}
//		else if (ft_strcmp(elements[index], "@tex") == 0) {
//			index++;
//			while (elements[index] && ft_strcmp(elements[index], "@end") == 0) {
//				parseBackground(&elements[index]);
//				index++;
//			}
//		}
//		else if (ft_strcmp(elements[index], "@player") == 0) {
//			index++;
//			while (elements[index] && ft_strcmp(elements[index], "@end") == 0) {
//				parsePlayer(&elements[index]);
//				index++;
//			}
//		}
//		else if (ft_strcmp(elements[index], "@map") == 0) {
//			index++;
//			while (elements[index] && ft_strcmp(elements[index], "@end") == 0) {
//				parseMap(&elements[index]);
//				index++;
//			}
//		}
		else if (elements[index][0] != '\n') {
			ERROR("Unknown element!\n");
		}
		if (elements[index] == NULL) {
			break;
		}
		index++;
	}
	ft_free_array(elements);
}

void	parseFile(int fd, t_level *level) {
	char *data = ft_strdup("");
	if (!data) {
		ERROR("Malloc fail!\n");
		return;
	}
	int res = 1;
	char *line;
	while (res > 0) {
		res = get_next_line(fd, &line);
		if (res < 0) {
			ERROR("Failed to read file!\n");
			// TODO proper cleanup
		}
		if (ft_strlen(line) == 0)
		{
			line = ft_strjoin(line, "\n");  // TODO memleak
			//ft_free(line);
			if (!line) {
				ERROR("Malloc fail!\n");
				return; // TODO proper cleanup
			}
		}
		line = ft_strjoin(line, "\n");  // TODO memleak
		if (!line) {
			ERROR("Malloc fail!\n");
			return; // TODO proper cleanup
		}
//		ft_free(line);
		data = ft_strjoin(data, line);  // TODO memleak
	}
	parseSettings(data, level);
}

void parser(t_raycaster *rc) {
	for (int i = 0; i < NUMBER_OF_LEVELS; i++) {
		char *current_level = ft_strjoin("/level_", ft_itoa(i + 1));
		char *path = ft_strjoin(PATH_LEVEL, current_level);
		if (current_level == NULL || path == NULL) {
			ERROR("Level [%d], couldn't be created!\n", i + 1);
			return; //TODO add proper cleanup exit
		}
		int fd = open(path, O_RDONLY);
		ft_bzero(&rc->level[i], sizeof(t_level));
		parseFile(fd, &rc->level[i]);
		close(fd);
		ft_free(path);
		ft_free(current_level);
//		setSprites();
//		if ((rc->level[i].zBuffer = (double *)ft_calloc(rc->screenHeight, sizeof(double))) == NULL) {
//			ERROR("Zbuffer for sprites couldn't be created!\n", i + 1);
//			return; //TODO add proper cleanup exit
//		}
	}
}