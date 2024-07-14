-- Creazione del trigger
CREATE OR REPLACE FUNCTION check_book_availability() 
RETURNS TRIGGER AS $$
DECLARE
    available_quantity INTEGER;
BEGIN
    -- Ottieni la quantità disponibile del libro
    SELECT ab.available_quantity 
    INTO available_quantity 
    FROM available_books as ab
    WHERE ab.isbn = NEW.isbn;

    -- Controlla se ci sono abbastanza copie disponibili per il prestito
    IF available_quantity > 0 THEN
        RETURN NEW;
    ELSE
        RAISE EXCEPTION 'Il libro con ISBN % non è disponibile per il prestito.', NEW.isbn;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Creazione del trigger sulla tabella loan
CREATE TRIGGER check_book_availability_trigger
BEFORE INSERT ON loan
FOR EACH ROW
EXECUTE FUNCTION check_book_availability();
