DROP TABLE IF EXISTS blacklisted_tokens CASCADE;
DROP TABLE IF EXISTS employee CASCADE;
DROP TABLE IF EXISTS application CASCADE;
DROP TABLE IF EXISTS direction CASCADE;
DROP TABLE IF EXISTS transport_way CASCADE;
DROP TABLE IF EXISTS warehouse_type CASCADE;
DROP TABLE IF EXISTS application_status CASCADE;
DROP TABLE IF EXISTS job_title CASCADE;
DROP TABLE IF EXISTS vessel_type CASCADE;
DROP TABLE IF EXISTS mar_ship CASCADE;
DROP TABLE IF EXISTS vessel_status CASCADE;
DROP TABLE IF EXISTS equipment_category CASCADE;
DROP TABLE IF EXISTS external_dimensions CASCADE;
DROP TABLE IF EXISTS container_type CASCADE;
DROP TABLE IF EXISTS container_status CASCADE;
DROP TABLE IF EXISTS container CASCADE;

CREATE TABLE blacklisted_tokens (
  id SERIAL,
  token VARCHAR(160) NOT NULL,
  expires_at TIMESTAMP NOT NULL
);

CREATE TABLE job_title (
  id_job_title SERIAL,
  name VARCHAR(60) NOT NULL,
  PRIMARY KEY (id_job_title)
);

CREATE TABLE direction (
  id_direction SERIAL,
  name VARCHAR(60) NOT NULL,
  PRIMARY KEY (id_direction)
);

CREATE TABLE transport_way (
  id_transport_way SERIAL,
  name VARCHAR(60) NOT NULL,
  PRIMARY KEY (id_transport_way)
);

CREATE TABLE warehouse_type (
  id_warehouse_type SERIAL,
  name VARCHAR(60) NOT NULL,
  PRIMARY KEY (id_warehouse_type)
);

CREATE TABLE application_status (
  id_application_status SERIAL,
  name VARCHAR(60) NOT NULL,
  PRIMARY KEY (id_application_status)
);

CREATE TABLE vessel_type (
  id_vessel_type SERIAL,
  name VARCHAR(60) NOT NULL,
  PRIMARY KEY (id_vessel_type)
);

CREATE TABLE vessel_status (
  id_vessel_status SERIAL,
  name VARCHAR(60) NOT NULL,
  PRIMARY KEY (id_vessel_status)
);

CREATE TABLE equipment_category (
  id_equipment_category SERIAL,
  name VARCHAR(60) NOT NULL,
  PRIMARY KEY (id_equipment_category)
);

CREATE TABLE external_dimensions (
  id_external_dimensions SERIAL,
  external_dimensions_code VARCHAR(60) NOT NULL,
  PRIMARY KEY (id_external_dimensions)
);

CREATE TABLE container_status (
  id_container_status SERIAL,
  name VARCHAR(60) NOT NULL,
  PRIMARY KEY (id_container_status)
);

CREATE TABLE employee (
  id_employee SERIAL,
  surname VARCHAR(60) NOT NULL,
  name VARCHAR(60) NOT NULL,
  patronymic VARCHAR(60),
  login VARCHAR(60) NOT NULL UNIQUE,
  password VARCHAR(60) NOT NULL,
  id_job_title INT NOT NULL,
  PRIMARY KEY (id_employee),
  FOREIGN KEY (id_job_title) REFERENCES job_title(id_job_title)
);

CREATE TABLE container_type (
  id_container_type SERIAL,
  code VARCHAR(60) NOT NULL,
  id_external_dimensions INT NOT NULL,
  PRIMARY KEY (id_container_type)
);

CREATE TABLE mar_ship (
  id_mar_ship SERIAL,
  imo_number VARCHAR(60) NOT NULL,
  name VARCHAR(100) NOT NULL,
  call_sign VARCHAR(60) NOT NULL,
  id_vessel_type INT NOT NULL,
  id_vessel_status INT,
  PRIMARY KEY (id_mar_ship),
  FOREIGN KEY (id_vessel_type) REFERENCES vessel_type(id_vessel_type),
  FOREIGN KEY (id_vessel_status) REFERENCES vessel_status(id_vessel_status)
);


CREATE TABLE application (
  id_application SERIAL,
  number VARCHAR(60) NOT NULL,
  name_organization VARCHAR(60) NOT NULL,
  inn_organization VARCHAR(60) NOT NULL,
  contact_phone VARCHAR(60) NOT NULL,
  email VARCHAR(100) NOT NULL,
  cargo_name VARCHAR(100) NOT NULL,
  tn_code VARCHAR(60),
  id_direction INT NOT NULL,
  unit_length DECIMAL(10,2),
  unit_width DECIMAL(10,2),
  unit_height DECIMAL(10,2),
  unit_mass DECIMAL(10,2),
  cargo_packaging TEXT,
  dangerous_cargo BOOLEAN DEFAULT FALSE,
  structural_characteristics TEXT,
  id_transport_way_in INT NOT NULL,
  id_transport_way_out INT NOT NULL,
  pickup_date DATE,
  import_date DATE,
  removal_date DATE,
  id_warehouse_type INT,
  shelf_life DATE,
  packaging_requirements TEXT,
  manufacturer VARCHAR(100),
  shipper VARCHAR(100),
  departure_port VARCHAR(100),
  departure_country VARCHAR(100),
  destination_port VARCHAR(100),
  destination_country VARCHAR(100),
  receiver VARCHAR(100),
  instructions_info TEXT,
  comment TEXT,
  id_application_status INT NOT NULL,
  id_employee INT NOT NULL,
  PRIMARY KEY (id_application),
  FOREIGN KEY (id_direction) REFERENCES direction(id_direction),
  FOREIGN KEY (id_transport_way_in) REFERENCES transport_way(id_transport_way),
  FOREIGN KEY (id_transport_way_out) REFERENCES transport_way(id_transport_way),
  FOREIGN KEY (id_warehouse_type) REFERENCES warehouse_type(id_warehouse_type),
  FOREIGN KEY (id_application_status) REFERENCES application_status(id_application_status),
  FOREIGN KEY (id_employee) REFERENCES employee(id_employee)
);

CREATE TABLE container (
  id_container SERIAL,
  code_owner VARCHAR(60) NOT NULL,
  country_code VARCHAR(60) NOT NULL,
  id_external_dimensions INT NOT NULL,
  serial_number VARCHAR(60) NOT NULL,
  check_digit VARCHAR(60) NOT NULL,
  id_equipment_category INT NOT NULL,
  id_container_type INT NOT NULL,
  id_container_status INT NOT NULL,
  service_number VARCHAR(20),
  tare_mass DECIMAL(10,2),
  gross_weight DECIMAL(10,2),
  payload DECIMAL(10,2),
  capacity DECIMAL(10,2),
  position VARCHAR(60) NOT NULL,
  id_mar_ship INT,
  id_application INT,
  id_employee INT,
  PRIMARY KEY (id_container),
  FOREIGN KEY (id_mar_ship) REFERENCES mar_ship(id_mar_ship),
  FOREIGN KEY (id_equipment_category) REFERENCES equipment_category(id_equipment_category),
  FOREIGN KEY (id_container_type) REFERENCES container_type(id_container_type),
  FOREIGN KEY (id_container_status) REFERENCES container_status(id_container_status),
  FOREIGN KEY (id_external_dimensions) REFERENCES external_dimensions(id_external_dimensions),
  FOREIGN KEY (id_application) REFERENCES application(id_application),
  FOREIGN KEY (id_employee) REFERENCES employee(id_employee)

);
