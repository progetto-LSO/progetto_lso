CREATE OR REPLACE VIEW available_books AS 
    SELECT b.*, b.quantity - COALESCE(l.borrowed_quantity, 0) AS available_quantity 
    FROM book b 
    LEFT JOIN ( 
        SELECT isbn, COUNT(*) AS borrowed_quantity 
        FROM loan 
        WHERE returned IS NULL 
        GROUP BY isbn 
    ) l ON b.isbn = l.isbn
;
