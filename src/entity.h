/* src/entity.h
 * entity header
 * by: thomas bruce
 * date: 26/04/2025
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
typedef enum {
	ET_PLAYER,
	ET_ENEMY,
	ET_BOSS,
	ET_BULLET,
	ET_TOKEN
} EntityType;

typedef struct Entity {
	EntityType	type;
	void		*ptr;
} Entity;

#endif
