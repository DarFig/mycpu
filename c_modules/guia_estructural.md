# Guía Para Construir Procesadores Compatibles

## Sobre las etapas

  La simulación se basa en *pipeline* segmentados, para simular trabajo secuencial
  en un ciclo considerar una sola etapa.

#### Instrucciones

- Definir las diferentes etapas en ficheros cabecera independientes.
- Los bancos de registros utilizados entre las diferentes etapas para separarlas
se encuentran duplicados en banco de entrada y banco de salida, para evitar
condiciones de carrera. Al finalizar cada ciclo se copian los datos dejados en por
la etapa anterior en el banco de salida en el corespondiente banco de entrada, el
cual será utilizado por la siguiente etapa.
- Se deben definir las correspondientes funciones para mostrar el contenido de la
memoria y el banco de registros:
'''c
  print_contenido_mem_detalle(dir_inicio, dir_fin, posicion_pc);

  print_contenido_mem_detalle(dir_ini, dir_fin);

  print_contenido_BR_detalle(registro_ini,registro_fin);
'''
- Cada etapa debe tener un método de ejecución que será llamada al finalizar la
etapa anterior, excepto la primera etapa que es llamada desde el main() mediante su
método por ejemplo:
'''c
  etapa_fetch_run();
'''
