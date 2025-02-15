[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/AA4A8GmB)
# IADE - Universidade Europeia

## SIG 2023 2024

### Laboratório 2

#### Parte 1

Responda às seguintes questões sobre o dataset em `data/20_database.sql`, que inclui dados sobre faculdades na zona de lisboa.

1. Adicionar moradas textuais às três primeiras localizações, correspondentes às reitorias das universidades.
2. Listar todas as escolas, indicando nome curto, nome completo, nome da universidade e morada da reitoria correspondente.
3. Listas todas as escolas, indicando nome curto, e distâncias em metros à sua reitoria.
5. Listar todas as universidades, indicando nome e coordenadas geográficas da reitoria em texto, ordenadas por ordem crescente de distância à sua escola mais distante.
7. Indicar as coordenadas do polígono convexo mais pequeno que contém todas as escolas de todas as universidades.
8. Listar todas as universidade, indicando nome e coordendas em GeoJSON do polígono convexo mais pequeno que contém todas as suas escolas.
9. Indicar o polígono que resulta da sobreposição de todos os polígonos listados em 8.
10. Listar todas as escolas, indicando nome da universidade, morada da reitoria, nome curto da escola, e distância em metros da escola para o IADE. Ordenar por ordem crescente de distância. O único identificados desta pesquisa é o termo 'IADE'. O IADE não deve aparecer na lista.

As respostas devem ser dadas sob a forma de queries SQL no ficheiro `queries.sql`. No mesmo ficheiro, indique o seu nome e número de estudante.

Está incluído um ficheiro `docker-compose.yml` que permite correr um servidor PostgreSQL+PostGIS com o dataset.

#### Parte 2 (Opcional)

Construa uma aplicação web, com vistas HTML que permitam:

1. Listar as escolas, indicando nome curto, e nome da universidade.
2. Obter mais detalhe de uma escola.
3. Visualizar a localização de cada escola num mapa.
4. Adicionar uma nova escola, com localização geográfica, à base de dados.