-- SIG 2023 2024 - Laboratório 2
-- Número: 20220589
-- Nome: Tomás Salgueiro

-- 1. Adicionar moradas textuais às três primeiras localizações, correspondentes às reitorias das universidades.
UPDATE locations SET address = 'Avenida Dom Carlos I, 4 1200-649 Lisboa' WHERE id = 1;
UPDATE locations SET address = 'Alameda da Universidade, 1649-004 Lisboa' WHERE id = 2;
UPDATE locations SET address = 'Campus de, 1099-085 Lisboa' WHERE id = 3;

-- 2. Listar todas as escolas, indicando nome curto, nome completo, nome da universidade e morada da reitoria correspondente.
SELECT
    s.short_name,
    s.full_name,
    u.name AS university_name,
    rectory_l.address AS rectory_address
FROM
    schools s
JOIN
    universities u ON s.university_id = u.id
JOIN
    locations s_loc ON s.location_id = s_loc.id
JOIN
    locations rectory_l ON u.location_id = rectory_l.id;

-- 3. Listas todas as escolas, indicando nome curto, e distâncias em metros à sua reitoria.
SELECT
    s.short_name,
    ST_Distance(s_loc.geom::geography, rectory_l.geom::geography) AS distance_to_rectory_meters
FROM
    schools s
JOIN
    universities u ON s.university_id = u.id
JOIN
    locations s_loc ON s.location_id = s_loc.id
JOIN
    locations rectory_l ON u.location_id = rectory_l.id;

-- 5. Listar todas as universidades, indicando nome e coordenadas geográficas da reitoria em texto, ordenadas por ordem crescente de distância à sua escola mais distante.
WITH max_distance AS (
    SELECT
        u.id,
        MAX(ST_Distance(s_loc.geom::geography, rectory_l.geom::geography)) AS max_distance_to_rectory_meters
    FROM
        schools s
    JOIN
        universities u ON s.university_id = u.id
    JOIN
        locations s_loc ON s.location_id = s_loc.id
    JOIN
        locations rectory_l ON u.location_id = rectory_l.id
    GROUP BY
        u.id
)
SELECT
    u.name AS university_name,
    rectory_l.address AS rectory_address,
    max_distance.max_distance_to_rectory_meters
FROM
    universities u
JOIN
    locations rectory_l ON u.location_id = rectory_l.id
JOIN
    max_distance ON u.id = max_distance.id
ORDER BY
    max_distance.max_distance_to_rectory_meters ASC;
    
-- 7. Indicar as coordenadas do polígono convexo mais pequeno que contém todas as escolas de todas as universidades.
WITH schools_geom AS (
    SELECT
        ST_Collect(s_loc.geom::geometry) AS geom
    FROM
        schools s
    JOIN
        locations s_loc ON s.location_id = s_loc.id
)
SELECT
    ST_AsText(ST_ConvexHull(schools_geom.geom)) AS convex_hull_text
FROM
    schools_geom;


-- 8. Listar todas as universidade, indicando nome e coordendas em GeoJSON do polígono convexo mais pequeno que contém todas as suas escolas.
WITH schools_geom AS (
    SELECT
        u.id AS university_id,
        ST_Collect(s_loc.geom::geometry) AS geom
    FROM
        schools s
    JOIN
        universities u ON s.university_id = u.id
    JOIN
        locations s_loc ON s.location_id = s_loc.id
    GROUP BY
        u.id
)
SELECT
    u.name AS university_name,
    ST_AsGeoJSON(ST_ConvexHull(schools_geom.geom)) AS convex_hull_geojson
FROM
    universities u
JOIN
    schools_geom ON u.id = schools_geom.university_id;


-- 9. Indicar o polígono que resulta da sobreposição de todos os polígonos listados em 8.
WITH schools_geom AS (
    SELECT
        u.id AS university_id,
        ST_Collect(s_loc.geom::geometry) AS geom
    FROM
        schools s
    JOIN
        universities u ON s.university_id = u.id
    JOIN
        locations s_loc ON s.location_id = s_loc.id
    GROUP BY
        u.id
)
SELECT
    ST_AsGeoJSON(ST_ConvexHull(schools_geom.geom)) AS convex_hull_geojson
FROM
    schools_geom;


-- 10. Listar todas as escolas, indicando nome da universidade, morada da reitoria, nome curto da escola, e distância em metros da escola para o IADE. Ordenar por ordem crescente de distância. O único identificados desta pesquisa é o termo 'IADE'. O IADE não deve aparecer na lista.
WITH iade_location AS (
    SELECT
        s.id,
        s_loc.geom
    FROM
        schools s
    JOIN
        locations s_loc ON s.location_id = s_loc.id
    WHERE
        s.short_name = 'IADE'
)
SELECT
    u.name AS university_name,
    rectory_l.address AS rectory_address,
    s.short_name,
    ST_Distance(s_loc.geom::geography, iade_location.geom::geography) AS distance_to_iade_meters
FROM
    schools s
JOIN
    universities u ON s.university_id = u.id
JOIN
    locations s_loc ON s.location_id = s_loc.id
JOIN
    locations rectory_l ON u.location_id = rectory_l.id
CROSS JOIN
    iade_location
WHERE
    s.short_name != 'IADE'
ORDER BY
    distance_to_iade_meters ASC;