CREATE TABLE "user" (
    username TEXT NOT NULL, 
    passw TEXT NOT NULL,

    CONSTRAINT user_pk PRIMARY KEY (username)
);

CREATE TABLE book (
    isbn TEXT PRIMARY KEY, 
    title TEXT UNIQUE NOT NULL, 
    authors TEXT[] NOT NULL, 
    genre TEXT[] NOT NULL, 
    quantity INTEGER NOT NULL,

    CONSTRAINT check_quantity_validity CHECK (quantity >= 0)
);

CREATE TABLE loan (
    id SERIAL,

    loan_start TIMESTAMP WITH TIME ZONE  NOT NULL  DEFAULT CURRENT_TIMESTAMP,
    loan_end TIMESTAMP WITH TIME ZONE  NOT NULL,
    returned TIMESTAMP WITH TIME ZONE,

    username TEXT, 
    isbn TEXT,

    CONSTRAINT loan_pk PRIMARY KEY id,
    CONSTRAINT loan_user_fk FOREIGN KEY (username) REFERENCES public."user" ON DELETE CASCADE,
    CONSTRAINT loan_book_fk FOREIGN KEY (isbn) REFERENCES book ON DELETE CASCADE,
    
    CONSTRAINT check_loan_validity CHECK (loan_end > loan_start)
);