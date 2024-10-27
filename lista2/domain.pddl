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
            (when (light-on ?room) (not (light-on ?room))) ;; Apaga a luz, se estiver acesa.
            (when (not (light-on ?room)) (light-on ?room)) ;; Acende a luz, se estiver apagada.

            ;; Movimentacao vampiro
            (when (and (vampire-is-in ?room) (not (light-on ?room))) ;; Vampiro no quarto com luz ligada ;; HERE

                (and 
                    (not (vampire-is-in ?room)) ;; Remover o vampiro do quarto atual
                    
                    ;; Se o anti-horario estiver acesso e o horario apagado, mover para horario
                    (when (and (light-on ?anti-clockwise-neighbor) (not (light-on ?clockwise-neighbor)))
                        (and
                            (vampire-is-in ?clockwise-neighbor)

                            (when (slayer-is-in ?anti-clockwise-neighbor)
                                (fighting)
                            )
                        )
                    )

                    ;; Se o vizinho anti-horario estiver escuro, mover para la
                    (when (not (light-on ?anti-clockwise-neighbor))
                        (and
                            (vampire-is-in ?anti-clockwise-neighbor)

                            (when (slayer-is-in ?anti-clockwise-neighbor)
                                (fighting)
                            )
                        )
                    )

                    ;; Se ambos os vizinhos estão acesos, mover para o sentido horario
                    (when (and (light-on ?anti-clockwise-neighbor) (light-on ?clockwise-neighbor))
                        (and
                            (vampire-is-in ?clockwise-neighbor)

                            (when (slayer-is-in ?clockwise-neighbor)
                                (fighting)
                            )
                        )
                    )
                )
            )

            ;; Movimentacao do caçador
            (when (and (slayer-is-in ?room) (light-on ?room)) ;; Caçador no quarto com luz apagada ;; HERE
                
                (and (not (slayer-is-in ?room)) ;; Remover caçador do quarto atual

                    ;; Se o quarto horário estiver com a luz acesa, mover para lá
                    (when (light-on ?clockwise-neighbor)
                        (and
                            (slayer-is-in ?clockwise-neighbor)

                            (when (vampire-is-in ?clockwise-neighbor)
                                (fighting)
                            )
                        )
                    )

                    ;; Se o quarto horário estiver com a luz apagada, mover para o anti-horário
                    (when (not (light-on ?clockwise-neighbor))
                        (and
                            (slayer-is-in ?anti-clockwise-neighbor)

                            (when (vampire-is-in ?anti-clockwise-neighbor)
                                (fighting)
                            )
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
