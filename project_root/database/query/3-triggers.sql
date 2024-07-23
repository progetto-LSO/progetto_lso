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

CREATE TRIGGER check_book_availability_trigger
BEFORE INSERT ON loan
FOR EACH ROW
EXECUTE FUNCTION check_book_availability();

/* -------------------------------------------- */

CREATE OR REPLACE FUNCTION set_loan_dates() 
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.loan_start is null THEN
        NEW.loan_start := current_timestamp;
    END IF;

    IF NEW.loan_end is null THEN
        NEW.loan_end := current_timestamp + interval '30 day';
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER set_loan_dates_trigger
BEFORE INSERT ON loan
FOR EACH ROW
EXECUTE FUNCTION set_loan_dates();