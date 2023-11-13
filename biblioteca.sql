-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 06-11-2023 a las 15:38:40
-- Versión del servidor: 10.4.28-MariaDB
-- Versión de PHP: 8.2.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `biblioteca`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `alquiler`
--

CREATE TABLE `alquiler` (
  `ID_alquiler` int(11) NOT NULL,
  `ID_libro` int(11) NOT NULL,
  `ID_socio` int(11) NOT NULL,
  `Fecha_adquirido` date NOT NULL,
  `Fecha_entregado` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `alquiler`
--

INSERT INTO `alquiler` (`ID_alquiler`, `ID_libro`, `ID_socio`, `Fecha_adquirido`, `Fecha_entregado`) VALUES
(1, 9, 3, '2023-11-15', '2023-11-30'),
(2, 1, 1, '2017-09-05', '2017-12-29'),
(3, 2, 2, '2004-01-31', '2003-11-12'),
(4, 3, 4, '2023-11-06', '2023-12-31'),
(5, 4, 5, '2015-11-11', '2011-12-31'),
(6, 5, 6, '2007-07-07', '2007-11-30'),
(7, 6, 7, '2003-11-01', '2004-02-28');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `autor`
--

CREATE TABLE `autor` (
  `ID_autor` int(11) NOT NULL,
  `Nombre` varchar(35) NOT NULL,
  `Apellido` varchar(35) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `autor`
--

INSERT INTO `autor` (`ID_autor`, `Nombre`, `Apellido`) VALUES
(1, 'Gabriel', 'García Márquez'),
(2, 'Julio', 'Cortázar'),
(3, 'Robert', 'Kiyosaki'),
(4, 'Charles', 'Dickens'),
(5, 'Julio', 'Verne'),
(6, 'Jorge Luis', 'Borges'),
(7, 'Pablo', 'Neduda'),
(8, 'Mario', 'Benedeti');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `editorial`
--

CREATE TABLE `editorial` (
  `ID_editorial` int(11) NOT NULL,
  `Nombre` varchar(35) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `editorial`
--

INSERT INTO `editorial` (`ID_editorial`, `Nombre`) VALUES
(1, 'Sudamericana'),
(2, 'Planeta'),
(3, 'Minotauro'),
(4, 'Nouger Ediciones'),
(5, 'Ediciones Oniro'),
(6, 'BlackList'),
(7, 'Emcé Editores'),
(8, 'El Aleph Editores');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `genero`
--

CREATE TABLE `genero` (
  `ID_genero` int(11) NOT NULL,
  `Tipo` varchar(35) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `genero`
--

INSERT INTO `genero` (`ID_genero`, `Tipo`) VALUES
(1, 'Novela'),
(2, 'Ficcion'),
(3, 'Cuento'),
(4, 'Finanzas Personales'),
(5, 'Drama'),
(6, 'Novela'),
(7, 'Historia'),
(8, 'Aventura'),
(9, 'Cientifica'),
(10, 'Terror'),
(11, 'Poesia');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `libro`
--

CREATE TABLE `libro` (
  `ID_libro` int(11) NOT NULL,
  `ISBN` varchar(15) NOT NULL,
  `Titulo` varchar(35) NOT NULL,
  `ID_autor` int(11) NOT NULL,
  `ID_genero` int(11) NOT NULL,
  `ID_editorial` int(11) NOT NULL,
  `Stock` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `libro`
--

INSERT INTO `libro` (`ID_libro`, `ISBN`, `Titulo`, `ID_autor`, `ID_genero`, `ID_editorial`, `Stock`) VALUES
(1, '9789500767170', 'Cien años de soledad', 1, 1, 1, 1),
(2, '9788420421315', 'Bestiario', 2, 1, 5, 14),
(3, '9783862486342', 'El cuadrante del flujo de dinero', 3, 7, 1, 3),
(4, '9781016306058', 'The Frozen Deep', 4, 6, 4, 54),
(5, '9780758311986', 'Viaje al centro de la Tierra', 5, 5, 2, 2),
(6, '9781567921236', 'La biblioteca de Babel', 6, 4, 3, 11),
(7, '9780828825290', 'Veinte poemas de amor y una canción', 7, 3, 5, 25),
(8, '9788497933056', 'Poemas de amor', 8, 2, 8, 6),
(9, '9786071122360', 'El negocio del siglo 21', 3, 1, 7, 78);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `socio`
--

CREATE TABLE `socio` (
  `ID_socio` int(11) NOT NULL,
  `Nombre` varchar(35) NOT NULL,
  `Apellido` varchar(35) NOT NULL,
  `DNI` int(11) NOT NULL,
  `Telefono` int(20) NOT NULL,
  `Direccion` varchar(50) DEFAULT NULL,
  `mail` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `socio`
--

INSERT INTO `socio` (`ID_socio`, `Nombre`, `Apellido`, `DNI`, `Telefono`, `Direccion`, `mail`) VALUES
(1, 'Genaro', 'Scarpato', 45580753, 445221385, 'DEL Tridente 1678', 'genaro.scarpato@alu.inspt.utn.edu.ar'),
(2, 'Lucas', 'Smilary', 43600521, 78542123, 'Besares 4043', 'lucas.smilari@hotmail.com'),
(3, 'Matias', 'Seba Mallo', 45545291, 8955621, 'Paz Soldan 5188', 'mathiasSM98@gmail.com'),
(4, 'Pocho', 'Messi', 123654, 13165400, 'MiamiFlorida 221', 'laterceraencasapapa@hotmail.com'),
(5, 'Eduardo', 'Lavezzi', 20135489, 5459215, 'Florentini 9518', 'armandini.espocito@alu.isnpt.utn.edu.ar'),
(6, 'Lautaro', 'Rodriguez', 43987456, 85113889, 'Mendoza 5049', 'doctoramor@alu.inspt.utn.edu.ar'),
(7, 'Tomas', 'Couso', 46902512, 563288465, 'Islandia 5552', 'tupapuchotecnico@alu.isnpt.utn.edu.ar');

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `alquiler`
--
ALTER TABLE `alquiler`
  ADD PRIMARY KEY (`ID_alquiler`),
  ADD KEY `Alquiler_ibfk_1` (`ID_libro`),
  ADD KEY `Alquiler_ibfk_2` (`ID_socio`);

--
-- Indices de la tabla `autor`
--
ALTER TABLE `autor`
  ADD PRIMARY KEY (`ID_autor`);

--
-- Indices de la tabla `editorial`
--
ALTER TABLE `editorial`
  ADD PRIMARY KEY (`ID_editorial`);

--
-- Indices de la tabla `genero`
--
ALTER TABLE `genero`
  ADD PRIMARY KEY (`ID_genero`);

--
-- Indices de la tabla `libro`
--
ALTER TABLE `libro`
  ADD PRIMARY KEY (`ID_libro`),
  ADD KEY `ID_genero` (`ID_genero`),
  ADD KEY `ID_autor` (`ID_autor`),
  ADD KEY `ID_editorial` (`ID_editorial`);

--
-- Indices de la tabla `socio`
--
ALTER TABLE `socio`
  ADD PRIMARY KEY (`ID_socio`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `alquiler`
--
ALTER TABLE `alquiler`
  MODIFY `ID_alquiler` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT de la tabla `autor`
--
ALTER TABLE `autor`
  MODIFY `ID_autor` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT de la tabla `editorial`
--
ALTER TABLE `editorial`
  MODIFY `ID_editorial` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT de la tabla `genero`
--
ALTER TABLE `genero`
  MODIFY `ID_genero` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- AUTO_INCREMENT de la tabla `libro`
--
ALTER TABLE `libro`
  MODIFY `ID_libro` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT de la tabla `socio`
--
ALTER TABLE `socio`
  MODIFY `ID_socio` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `alquiler`
--
ALTER TABLE `alquiler`
  ADD CONSTRAINT `Alquiler_ibfk_1` FOREIGN KEY (`ID_libro`) REFERENCES `libro` (`ID_libro`),
  ADD CONSTRAINT `Alquiler_ibfk_2` FOREIGN KEY (`ID_socio`) REFERENCES `socio` (`ID_socio`);

--
-- Filtros para la tabla `libro`
--
ALTER TABLE `libro`
  ADD CONSTRAINT `Libro_ibfk_1` FOREIGN KEY (`ID_genero`) REFERENCES `genero` (`ID_genero`),
  ADD CONSTRAINT `Libro_ibfk_2` FOREIGN KEY (`ID_autor`) REFERENCES `autor` (`ID_autor`),
  ADD CONSTRAINT `Libro_ibfk_3` FOREIGN KEY (`ID_editorial`) REFERENCES `editorial` (`ID_editorial`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
