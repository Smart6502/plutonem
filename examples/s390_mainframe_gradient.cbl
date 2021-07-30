       IDENTIFICATION DIVISION.
       PROGRAM-ID. PLUTO-GRADIENT.

       DATA DIVISION.
       WORKING-STORAGE SECTION.
       01 WS-END PIC X(1).
       01 X PIC 9(3).
       01 Y PIC 9(3).

       01 R PIC 9(3).
       01 G PIC 9(3).
       01 B PIC 9(3).

       01 LINE_WIDTH PIC 9(3) VALUE 8.
       01 ANGLE PIC 9(8)V9(3).

       PROCEDURE DIVISION.
           CALL "pl_init".

           MOVE 'N' TO WS-END.
           PERFORM UNTIL WS-END = 'Y'
              MOVE 0 TO Y
              PERFORM UNTIL Y = 150
                 MOVE 0 TO X
                 PERFORM UNTIL X = 200
                    MOVE X TO R
                    MOVE Y TO G
                    MOVE 255 TO B
                    ADD ANGLE TO B
                    CALL "pl_cpix" USING X Y R G B
                    ADD 1 TO X
                 END-PERFORM
                 ADD 1 TO Y
              END-PERFORM

              ADD 8 TO ANGLE

              CALL "pl_render"
           END-PERFORM.
           CALL "pl_deinit".
           STOP RUN.
