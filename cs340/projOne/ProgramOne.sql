--Jackson E. Rollins
--932932878
--Program #1
--5/11/2021

--Question #1

CREATE TABLE DEPT_STATS(
Dnumber int(2) NOT NULL,
Emp_count int(11) NOT NULL,
Avg_salary decimal(10.2) NOT NULL,
PRIMARY KEY (Dnumber));


--Question #2

DELIMITER $$
CREATE DEFINER=`cs340_rollijac`@`%` PROCEDURE `InitDeptStats`()
BEGIN
	INSERT INTO DEPT_STATS
    SELECT dno, COUNT(ssn), AVG(salary)
    FROM EMPLOYEE
    GROUP BY dno;
END$$
DELIMITER ;


--Question #3
--Part 1

CREATE TRIGGER `DELETEDeptStats` AFTER DELETE ON `EMPLOYEE`
 FOR EACH ROW BEGIN
	DELETE FROM DEPT_STATS;
    CALL InitDeptStats();
END

--Part 2

CREATE TRIGGER `INSERTDeptStats` AFTER INSERT ON `EMPLOYEE`
 FOR EACH ROW BEGIN
	DELETE FROM DEPT_STATS;
    CALL InitDeptStats();
END

--Part 3

CREATE TRIGGER `UPDATEDDeptStats` AFTER UPDATE ON `EMPLOYEE`
 FOR EACH ROW BEGIN
	DELETE FROM DEPT_STATS;
    CALL InitDeptStats();
END


--Question #4

CREATE TRIGGER `MaxTotalHours` BEFORE INSERT ON `WORKS_ON`
 FOR EACH ROW BEGIN
	DECLARE num integer;
	DECLARE customMessage VARCHAR(100);
    SELECT SUM(WORKS_ON.Hours) INTO num
    	FROM WORKS_ON
        WHERE Essn=New.Essn;
	IF((num + New.Hours) > 40) THEN
    	SET customMessage = concat('You entered ', New.Hours,'. You currently work ', num,'. You are over 40 hours.');
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = customMessage;
    END IF;
END


--Question #5

DELIMITER $$
CREATE DEFINER=`cs340_rollijac`@`%` FUNCTION `PayLevel`(`empSSN` CHAR(9)) RETURNS varchar(20) CHARSET utf8
BEGIN
    DECLARE paylevel varchar(100);
    DECLARE avgsal decimal(10, 2);
        
    SELECT d.Avg_salary INTO avgsal FROM DEPT_STATS d WHERE (SELECT Dno FROM EMPLOYEE e WHERE e.Ssn = empSSN) = d.Dnumber;
    
    IF ((SELECT e.Salary FROM EMPLOYEE e WHERE e.Ssn = empSSN) > avgsal) THEN
        RETURN 'Above Average';
    END IF;
    IF ((SELECT e.Salary FROM EMPLOYEE e WHERE e.Ssn = empSSN) < avgsal) THEN
        RETURN 'Below Average';
    END IF;
    RETURN 'Average';
END$$
DELIMITER ;