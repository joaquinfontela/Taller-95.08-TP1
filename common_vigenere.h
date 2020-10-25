typedef struct vigenereEncoder {
  unsigned char* key;
  unsigned int currentKeyPosition;
} vigenereEncoder_t;

/*  Pre:          key = la llave con la cual cifrar/descifrar el mensaje.
 *
 *  Pos:          Se guarda la llave, ademas inicializa la posicion actual de la
 *                llave en 0.
 *
 *  RETURN VALUE: -1 en caso de error, 0 en caso de exito.
 *
 */
int vigenereEncoder_t_initialize(vigenereEncoder_t* self, unsigned char key[]);

/*  Pre:          string = el mensaje a ser cifrado en Vigenere.
 *
 *  Pos:          Deja en 'string' el mensaje recibido pero ya cifrado.
 *
 */
void vigenereEncoder_t_encode(void* selfVoid, unsigned char string[]);

/*  Pre:          string = el mensaje a ser descifrado en Vigenere.
 *                bytesToDecode = la cantidad de bytes a ser descifrados (el
 *                largo del mensaje).
 *
 *  Pos:          Deja en 'string' el mensaje recibido pero ya descifrado.
 *
 */
void vigenereEncoder_t_decode(void* selfVoid, unsigned char string[],
                              unsigned int bytesToDecode);
