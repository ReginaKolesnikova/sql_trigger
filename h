Create database trigerTARgv24;
use trigerTARgv24;
--INSERT TRIGER- jälgib andmete sisestamine tabelis
--ja teeb vastava kirje tabelis logi
CREATE TRIGGER linnaLisamine
ON linnad --tabelinimi, mis on vaja jälgida
FOR INSERT
AS
INSERT INTO logi(aeg, toiming, andmed)
SELECT
GETDATE(),
'on tehtud INSERT käsk',
inserted.linnanimi
FROM inserted;

--trigeri tegevuse kontroll
INSERT INTO linnad(linnanimi, rahvaarv)
VALUES ('Tallinn', 600000);
SELECT * FROM linnad;
SELECT * FROM logi;

INSERT INTO linnad(linnanimi, rahvaarv)
VALUES ('Tartu', 50000);
SELECT * FROM linnad;
SELECT * FROM logi;

INSERT INTO linnad(linnanimi, rahvaarv)
VALUES ('Tapa', 5000);
SELECT * FROM linnad;
SELECT * FROM logi;


----


  use [trigerTARgv24]
GO
/********** Object: Trigger [dbo].[linnaLisamine] *****/

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER TRIGGER [dbo].[linnaLisamine]
on [dbo].[linnad] --tabelinimi, mis on vaja jälgida
FOR INSERT
AS
INSERT INTO logi(kasutaja, aeg, toiming, andemed)
SELECT
SUSER_NAME(), --USER
GETDATE(),
'on tehtud INSERT käsk'
CONCAT('linn: ', inserted.linnanimi, ', elanike arv: ', inserted.rahvaarv)
FROM inserted;



-----

  CREATE TRIGGER linnaKustutamine
on linnad --tabelinimi, mis on vaja jälgida
FOR DELETE
AS
INSERT INTO logi(kasutaja, aeg, toiming, andemed)
SELECT
SUSER_NAME(), --USER
GETDATE(),
'on tehtud DELETE käsk'
CONCAT('linn: ', deleted.linnanimi, ', elanike arv: ', deleted.rahvaarv)
FROM deleted

--kontroll
DELETE FROM linnad
WHERE linnID=1;
SELECT * FROM linnad;
SELECT * FROM logi;



CREATE TRIGGER linnaUUendamine
on linnad --tabelinimi, mis on vaja jälgida
FOR UPDATE
AS
INSERT INTO logi(kasutaja, aeg, toiming, andemed)
SELECT
SUSER_NAME(), --USER
GETDATE(),
'on tehtud UPDATE käsk'
CONCAT('vanad andmed -linn: ', deleted.linnanimi, ', elanike arv: ', deleted.rahvaarv, '\n uued andmed -linn: ', inserted.linnanimi, ', elanike arv: ', inserted.rahvaarv)
FROM deleted
INNER JOIN inserted
ON deleted.linnID=inserted.linnID;

--kontroll
UPDATE linnad SET rahvaarv=2500
WHERE linnID=3;
SELECT * FROM linnad;
SELECT * FROM logi;


