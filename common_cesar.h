typedef struct cesarEncoder {
  unsigned int offset;
} cesarEncoder_t;

/*  Pre:          offset = el offset con el cual cifrar el mensaje.
 *
 *  Pos:          Convierte el offset a entero y se lo guarda como atributo.
 *
 *
 *  RETURN VALUE: -1 en caso de error, 0 en caso de exito.
 *
 */
int cesarEncoder_t_initialize(cesarEncoder_t* self, unsigned char offset[]);

/*  Pre:          string = el mensaje a ser cifrado en Cesar.
 *
 *  Pos:          Deja en 'string' el mensaje recibido pero ya cifrado.
 *
 */
void cesarEncoder_t_encode(void* selfVoid, unsigned char string[]);

/*  Pre:          string = el mensaje a ser descifrado en Cesar.
 *                bytesToDecode = la cantidad de bytes a ser descifrados (el
 *                largo del mensaje).
 *
 *  Pos:          Deja en 'string' el mensaje recibido pero ya descifrado.
 *
 */
void cesarEncoder_t_decode(void* selfVoid, unsigned char string[],
                           unsigned int bytesToDecode);
