(define (domain vampire)
    (:requirements :conditional-effects)
    (:predicates
        (light-on ?r)
        (slayer-is-alive)
        (slayer-is-in ?r)
        (vampire-is-alive)
        (vampire-is-in ?r)
        (fighting)
        ;
        ; static predicates
        (NEXT-ROOM ?r ?rn)
        (CONTAINS-GARLIC ?r)
    )

    (:action toggle-light
        :parameters (?anti-clockwise-neighbor ?room ?clockwise-neighbor)
        :precondition (and
            (NEXT-ROOM ?anti-clockwise-neighbor ?room)
            (NEXT-ROOM ?room ?clockwise-neighbor)
            (not (fighting))
        )
        :effect (and
;; Add your solution here.
            ;; Luz
            (when (light-on ?room)
                    (not (light-on ?room))) ;; Apaga a luz, se estiver acesa.
            (when (not (light-on ?room)) 
                    (light-on ?room))       ;; Acende a luz, se estiver apagada.

            ;; Movimentacao vampiro
            (when (and (vampire-is-in ?room) (light-on ?room)) ;; Vampiro no quarto ligado
                    (or
                        ;; Se antihorario desligado, mover
                        (and
                            (not (light-on ?anti-clockwise-neighbor))
                            (vampire-is-in ?anti-clockwise-neighbor)

                            (when (slayer-is-in ?anti-clockwise-neighbor) ;; Se encontrou cacador, lutar
                                (fighting)
                            )
                        )
                        ;; Se ambas ligadas, mover horario
                        (and
                            (light-on ?anti-clockwise-neighbor)
                            (light-on ?clockwise-neighbor)
                            (vampire-is-in ?clockwise-neighbor)

                            (when (slayer-is-in ?clockwise-neighbor) ;; Se encontrou cacador, lutar
                                (fighting)
                            )
                        )
                    )
            )

            ;; Movimentacao cacador
            (when (and (slayer-is-in ?room) (not (light-on ?room))) ;; Cacador no quarto desligado 
                (or
                    ;; Se horario ligada, mover
                    (and
                        (light-on ?clockwise-neighbor)
                        (slayer-is-in ?clockwise-neighbor)

                        (when (vampire-is-in ?clockwise-neighbor) ;; Se encontrou vampiro, lutar
                            (fighting)
                        )
                    )

                    ;; Se horario desligada, mover antihorario
                    (and
                        (not (light-on ?clockwise-neighbor))
                        (slayer-is-in ?anti-clockwise-neighbor)

                        (when (vampire-is-in ?anti-clockwise-neighbor) ;; Se encontrou vampiro, lutar
                            (fighting)
                        )
                    )
                )
            )
        )
    )

    (:action watch-fight
        :parameters (?room)
        :precondition (and
            (slayer-is-in ?room)
            (slayer-is-alive)
            (vampire-is-in ?room)
            (vampire-is-alive)
            (fighting)
        )
        :effect (and
;; Add your solution here.
            ;; Desligada SEM alho, vampiro mata cacador
            (when
                (and (not (light-on ?room)) (not (CONTAINS-GARLIC ?room)))
                (and (not (slayer-is-alive)) (not (fighting)))
            )

            ;; Desligada COM algo, cacador mata vampiro
            (when
                (and (not (light-on ?room)) (CONTAINS-GARLIC ?room))
                (and (not (vampire-is-alive)) (not (fighting)))
            )

            ;; Ligada, cacador mata vampiro
            (when
                (light-on ?room)
                (and (not (vampire-is-alive)) (not (fighting)))
            )
        )
    )
)
