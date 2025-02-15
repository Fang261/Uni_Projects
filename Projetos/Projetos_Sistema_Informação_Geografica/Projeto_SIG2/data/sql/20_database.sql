create table locations
(
    id      serial primary key,
    geom    geography(point, 4326),
    address text
);

create table universities
(
    id          serial primary key,
    name        text,
    location_id integer references locations (id)
);

create table schools
(
    id            serial primary key,
    short_name    text,
    full_name     text,
    university_id integer references universities (id),
    location_id   integer references locations (id)
);

insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.1935177881667 38.7600972664144)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.15778207461115 38.75294719201223)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.160189910940508 38.73404965816873)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.15241124583974 38.7072835498519)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.1935177881667 38.7600972664144)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-8.65113488856252 41.2760886860589)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.18357608977054 38.7649333234353)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.13865135933251 38.7370200226105)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.15538040350804 38.7566507689603)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.19481765933359 38.7130104604756)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.20534354584189 38.6612865141465)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.15041286913231 38.7406591135067)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.32577454612342 38.6786319421252)', 4326), '');
insert into locations (geom, address)
values (ST_GeomFromText('POINT(-9.10199837976008 38.7823673995688)', 4326), '');

insert into universities (name, location_id)
values ('Universidade Europeia', 1);
insert into universities (name, location_id)
values ('Universidade de Lisboa', 2);
insert into universities (name, location_id)
values ('Universidade NOVA', 3);

insert into schools (short_name, full_name, university_id, location_id)
values ('IADE', 'Faculdade de Design, Tecnologia e Comunicação', 1, 4);
insert into schools (short_name, full_name, university_id, location_id)
values ('IPAML', 'Instituto Português de Administração de Marketing - Lisboa', 1, 5);
insert into schools (short_name, full_name, university_id, location_id)
values ('IPAMP', 'Instituto Português de Administração de Marketing - Porto', 1, 6);
insert into schools (short_name, full_name, university_id, location_id)
values ('FCST', 'Faculdade de Ciências Sociais e Tecnologia', 1, 7);
insert into schools (short_name, full_name, university_id, location_id)
values ('IST', 'Instituto Superior Técnico', 2, 8);
insert into schools (short_name, full_name, university_id, location_id)
values ('FCUL', 'Faculdade de Ciências', 2, 9);
insert into schools (short_name, full_name, university_id, location_id)
values ('FA', 'Faculda de Arquitetura', 2, 10);
insert into schools (short_name, full_name, university_id, location_id)
values ('FCT', 'Faculdade de Ciências e Tecnologia', 3, 11);
insert into schools (short_name, full_name, university_id, location_id)
values ('FCSH', 'Faculdade de Ciências Sociais e Humanas', 3, 12);
insert into schools (short_name, full_name, university_id, location_id)
values ('SBE', 'School of Business and Economics', 3, 13);
insert into schools (short_name, full_name, university_id, location_id)
values ('OGC', 'Oriente Green Campus', 1, 14);