--
-- PostgreSQL database dump
--

-- Dumped from database version 9.5.19
-- Dumped by pg_dump version 9.5.19

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: inctf2020; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.inctf2020 (
    username character varying(20),
    go_to character varying(40)
);


ALTER TABLE public.inctf2020 OWNER TO postgres;

--
-- Data for Name: inctf2020; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.inctf2020 (username, go_to) FROM stdin;
aaaaaa	./you_are_not_admin.php
admin	./feel_the_gosql_series.php
zamin	./you_are_not_admin.php
\.


--
-- Name: SCHEMA public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- Name: TABLE inctf2020; Type: ACL; Schema: public; Owner: postgres
--

REVOKE ALL ON TABLE public.inctf2020 FROM PUBLIC;
REVOKE ALL ON TABLE public.inctf2020 FROM postgres;
GRANT ALL ON TABLE public.inctf2020 TO postgres;
GRANT SELECT ON TABLE public.inctf2020 TO test;


--
-- PostgreSQL database dump complete
--

