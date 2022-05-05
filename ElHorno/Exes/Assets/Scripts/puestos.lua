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
        scale = "0.35;0.35;0.35"
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
        scale = "0.35;0.8;0.35",
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
        scale = "0.35;0.75;0.35",
        
    },
    mesh = {
        name = "BaldaPlatano.mesh",
    }
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
    mesh = {
        name = "TriggerCarniceria.mesh",
    }
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
        colShape = "0"scale = "8.0; 8.0; 8.0",
        
    },
    parent = {
        name = "Peso",
        
    },
    mesh = {
        name = "TriggerPeso.mesh",
    }
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
    mesh = {
        name = "TriggerTicketDispenser.mesh",
    }
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
    mesh = {
        name = "TriggerPescaderia.mesh",
    }
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
         id = "Platano"
    },
    rigidbody = {
         mass = "0.0",
          isTrigger = "1",
        isKinematic = "0",
        colShape = "0"scale = "8.0; 8.0; 8.0",
        
    },
    parent = {
        name = "BaldaPlatano",
        
    },
    mesh = {
        name = "TriggerBaldaPlatano.mesh",
    }
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
         id = "Cocacola"
    },
    mesh = {
        name = "TriggerBaldaDobleCola.mesh",
    }
}

entities = {"Peso", "TicketDispenser", "Pescaderia", "Carniceria", "Floor", "BaldaDobleCola", "BaldaPlatano", "TriggerCarniceria", "TriggerPeso", "TriggerTicketDispenser", "TriggerPescaderia", "TriggerBaldaPlatano", "TriggerBaldaDobleCola" }
