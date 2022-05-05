light = {
    transform = {
        position = " 0 ,200 ,200 ",
        rotation = " 0 ,0 ,0 ",
        scale = " 0 ,0 ,0 ",
    },

    light = {
        type = "0",
        dirLight = " 0 ,0 ,0 ",
    },
}

Peso = {
    transform = {
        position = "  -37.421616 ,-0.597879 ,-123.489502 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    rigidbody = {
        mass = "0.0",
        isTrigger = "0",
         isKinematic = "0",
         colShape = "0",
        scale = "0.35; 0.35; 0.35"
    },
    mesh = {
        name = "Peso.mesh",
    }
}
TicketDispenser = {
    transform = {
        position = "  -60.322956 ,-0.597879 ,-122.307426 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    rigidbody = {
        mass = "0.0",
        isTrigger = "0",
         isKinematic = "0",
         colShape = "0",
        scale = "0.35; 0.8; 0.35",
        
    },
    mesh = {
        name = "TicketDispenser.mesh",
    }
}
Pescaderia = {
    transform = {
        position = "  253.359894 ,-0.500147 ,223.288452 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    rigidbody = {
        mass = "0.0",
        isTrigger = "0",
         isKinematic = "0",
         colShape = "0",
        scale = "0.6;0.6;0.6",
        
    },
    mesh = {
        name = "Pescaderia.mesh",
    }
}
Carniceria = {
    transform = {
        position = "  253.359894 ,-0.500147 ,97.648293 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    rigidbody = {
        mass = "0.0",
        isTrigger = "0",
         isKinematic = "0",
         colShape = "0",
        scale = "0.6;0.6;0.6",
        
    },
    mesh = {
        name = "Carniceria.mesh",
    }
}
Floor = {
    transform = {
        position = "  34.506065 ,-2.830084 ,-11.012547 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    rigidbody = {
         mass = "0",
         isTrigger = "0",
         isKinematic = "0",
         colShape = "0",
        
    },
    mesh = {
        name = "Floor.mesh",
    }
}
BaldaDobleManzana = {
    transform = {
        position = "  92.436668 ,-0.597879 ,178.181107 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    rigidbody = {
        mass = "0.0",
        isTrigger = "0",
         isKinematic = "0",
         colShape = "0",
        scale = "0.35; 0.25; 0.65",
        
    },
    mesh = {
        name = "BaldaDobleManzana.mesh",
    }
}
BaldaDobleCola = {
    transform = {
        position = "  -220.367859 ,-0.597879 ,77.404541 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    rigidbody = {
        mass = "0.0",
        isTrigger = "0",
         isKinematic = "0",
         colShape = "0",
        scale = "0.6;0.6;0.6",
        
    },
    mesh = {
        name = "BaldaDobleCola.mesh",
    }
}
BaldaDoblePezAzul = {
    transform = {
        position = "  -220.367859 ,-0.597879 ,157.404510 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    rigidbody = {
        mass = "0.0",
        isTrigger = "0",
         isKinematic = "0",
         colShape = "0",
        scale = "0.35; 0.35; 0.65",
        
    },
    mesh = {
        name = "BaldaDoblePezAzul.mesh",
    }
}
BaldaPlatano = {
    transform = {
        position = "  79.922325 ,-0.597879 ,224.342438 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    rigidbody = {
        mass = "0.0",
        isTrigger = "0",
         isKinematic = "0",
         colShape = "0",
        scale = "0.35; 0.75; 0.35",
        
    },
    mesh = {
        name = "BaldaPlatano.mesh",
    }
}
cart = {
    transform = {
        position = "  0.000000 ,0.000000 ,2.500000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    parent = {
        name = "player",
        
    },
    rigidbody = {
        mass = "2",
        isTrigger = "1",
         isKinematic = "1",
         colShape = "0",
        
    },
    mesh = {
        name = "cart.mesh",
    }
}
camera = {
    transform = {
        position = "  0.000000 ,0.000000 ,-0.000000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  20.000000 ,20.000000 ,20.000000 " ,
    },
    camera = {
        position = " 0,100,450",
        lookAt = "   0,0,0 ",
        color = "0 ,0.3 ,0.5,1 ",
        nearClDis = "5",
        farClDis = "10000",
        target = "player,0.2,0,600,300"
    },
    audiolistener = {
        
    },
}
gamemanager = {
    transform = {
        position = "  -390.363617 ,-0.597879 ,-592.355591 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    gamemanager = {
        state = "0",
        productNum = "6",
        list = "Tomate,3,Zanahoria,2,Pizza,1",
        maxTime = "20",
    },
}
player = {
    transform = {
        position = "  -50.000000 ,20.000000 ,-0.000000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  8.000000 ,8.000000 ,8.000000 " ,
    },
    mesh = {
        name = "pipo.mesh"
    },
    rigidbody = {
        mass = "2.0",
        isTrigger = "0",
         isKinematic = "0",
         colShape = "0",
         scale = "0.5; 0.7; 1.3",
        angFactor = "0.0",
    },
    playercontroller = {
        speed = "1500.0",
         maxForce = "200"
    },
    audiocomponent = {
        
    },
    playerinteract = {
        
    },
    animatorcontroller = {
        Idle = "walk",
         walk = "Idle",
         Idle_with_product = "walk_with_product",
         walk_with_product = "Idle_with_product",
         Idle_with_cart = "walk_with_cart",
         walk_with_cart = "Idle_with_cart",
         AnyState = "Idle_with_cart,Idle_with_product,Idle",
    
    },
}
TriggerCarniceria = {
    transform = {
        position = "  -26.869394 ,0.000000 ,-0.000000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    entityid = {
        type = "5",
        
    },
    rigidbody = {
         mass = "0.0",
          isTrigger = "1",
        isKinematic = "0",
        colShape = "0",
        scale = "13.0; 10.0; 10.0"
    },
    parent = {
        name = "Carniceria",
        
    },
}
TriggerPeso = {
    transform = {
        position = "  0.000000 ,0.000000 ,-0.000000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    entityid = {
        type = "7",
        
    },
    rigidbody = {
         mass = "0.0",
          isTrigger = "1",
        isKinematic = "0",
        colShape = "0",
         scale = "8.0; 8.0; 8.0",
        
    },
    parent = {
        name = "Peso",
        
    },
}
TriggerTicketDispenser = {
    transform = {
        position = "  0.000000 ,0.000000 ,-0.000000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    entityid = {
        type = "4",
        
    },
    rigidbody = {
         mass = "0.0",
          isTrigger = "1",
        isKinematic = "0",
        colShape = "0",
        scale = "8.0; 8.0; 8.0",
        
    },
    parent = {
        name = "TicketDispenser",
        
    },
}
TriggerPescaderia = {
    transform = {
        position = "  -26.869394 ,0.000000 ,-0.000000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    entityid = {
        type = "6",
        
    },
    rigidbody = {
         mass = "0.0",
          isTrigger = "1",
        isKinematic = "0",
        colShape = "0",
        scale = "13.0; 10.0; 10.0"
    },
    parent = {
        name = "Pescaderia",
        
    },
}
cartTrigger = {
    transform = {
        position = "  0.000000 ,0.000000 ,-0.000000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  4.000000 ,4.000000 ,4.000000 " ,
    },
    parent = {
        name = "cart",
        
    },
    rigidbody = {
        mass = "1",
          isTrigger = "1",
         isKinematic = "1",
         colShape = "0",
        
    },
    entityid = {
        type = "2",
         productType = "0",
         id = "",
        
    },
}
TriggerBaldaPlatano = {
    transform = {
        position = "  0.000000 ,0.000000 ,-0.000000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    entityid = {
        type = "1",
        prodtype = "2",
         id = "Platano",
    },
    rigidbody = {
         mass = "0.0",
          isTrigger = "1",
        isKinematic = "0",
        colShape = "0",
        scale = "8.0; 8.0; 8.0",
        
    },
    parent = {
        name = "BaldaPlatano",
        
    },
}
TriggerBaldaDobleCola = {
    transform = {
        position = "  0.000000 ,11.054862 ,-0.000000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    parent = {
        name = "BaldaDobleCola",
        
    },
    rigidbody = {
         mass = "0.0",
          isTrigger = "1",
        isKinematic = "0",
        colShape = "0",
        scale = "8.0; 5.0; 5.0",
        
    },
    entityid = {
        type = "1",
        prodtype = "1",
         id = "Cocacola",
    },
}
TriggerBaldaDoblePezAzul = {
    transform = {
        position = "  0.000000 ,11.054862 ,-0.000000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    parent = {
        name = "BaldaDoblePezAzul",
        
    },
    rigidbody = {
         mass = "0.0",
          isTrigger = "1",
        isKinematic = "0",
        colShape = "0",
        scale = "8.0; 5.0; 5.0",
        
    },
    entityid = {
        type = "1",
        prodtype = "3",
         id = "PezAzul"
    },
}
TriggerBaldaDobleManzana = {
    transform = {
        position = "  0.000000 ,11.054862 ,-0.000000 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  1.000000 ,1.000000 ,1.000000 " ,
    },
    parent = {
        name = "BaldaDobleManzana",
        
    },
    rigidbody = {
         mass = "0.0",
          isTrigger = "1",
        isKinematic = "0",
        colShape = "0",
        scale = "8.0; 5.0; 5.0",
        
    },
    entityid = {
        type = "1",
        prodtype = "2",
         id = "Manzana"
    },
}

entities = {"light","player","Peso", "TicketDispenser", "Pescaderia", "Carniceria", "Floor", "BaldaDobleManzana", "BaldaDobleCola", "BaldaDoblePezAzul", "BaldaPlatano", "cart", "camera", "GameManager",  "TriggerCarniceria", "TriggerPeso", "TriggerTicketDispenser", "TriggerPescaderia", "cartTrigger", "TriggerBaldaPlatano", "TriggerBaldaDobleCola", "TriggerBaldaDoblePezAzul", "TriggerBaldaDobleManzana" }
