gamemanager = {
    gamemanager = {      
        state = "3",
        productNum = "6",
        list = "Tomate,3,Zanahoria,2,Pizza,1",
        maxTime = "180",
    },
}

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

player = {
    transform = {
        position = " -50, 20, 0 ",
        rotation = " 0 ,0 ,0 ",
        scale = " 10,10,10 ",
    },

    mesh = {
        name = "pipo.mesh",
    },

    rigidbody = {
        mass = "2",
        isTrigger = "0",
        isKinematic = "0",
        colShape = "0",
        scale = "0.5, 0.7, 1.3",
        angFactor = "0.0",
    },

    audiocomponent = {

    },

    playercontroller = {
        speed = "1500",
        maxForce = "200",
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

camera = {
    transform = {
        position = " 0 ,0 ,0 ",
        rotation = " 0 ,0 ,0 ",
        scale = " 0 ,0 ,0 ",
    },

    camera = {
        position = " 0, 100, 450 ",
        lookAt = " 0, 0, 0 ",
        color = " 0, 0.3, 0.5, 1 ",
        nearClDis = "5",
        farClDis = "10000",
        target = "player,0.2 ,0 ,600, 300",
    },

    audiolistener = {

    },
}

object = {
    transform = {
        position = " 0, -7, 0 ",
        rotation = " 0 ,0 ,0 ",
        scale = " 15, 0.1, 15 ",
    },

    mesh = {
        name = "cube.mesh",
    },

    rigidbody = {
        mass = "0",
        isTrigger = "0",
        isKinematic = "0",
        colShape = "0",
    },
}

cart = {
    transform = {
        position = " 0, 0, 2.5 ",
        rotation = " 0 ,0 ,0 ",
        scale = " 0.02, 0.02, 0.02 ",
    },

    mesh = {
        name = "cube.mesh",
    },

    rigidbody = {
        mass = "2",
        isTrigger = "1",
        isKinematic = "1",
        colShape = "0",
    },

    parent = {
        name = "player",
    },
}

cartTrigger = {
    transform = {
        position = " 0, 0, 0 ",
        rotation = " 0 ,0 ,0 ",
        scale = " 4, 4, 4 ",
    },

    rigidbody = {
        mass = "1",
        isTrigger = "1",
        isKinematic = "1",
        colShape = "0",
    },

    entityid = {
        type = "2";
        productType = "0";
        id = "";
    },
    parent = {
        name = "cart",
    },
}

moneco = {
    transform = {
        position = " -150, 10, 0 ",
        rotation = " 0 ,0 ,0 ",
        scale = " 0.5, 0.5, 0.5 ",
    },

    mesh = {
        name = "penguin.mesh",
    },

    rigidbody = {
        mass = "3",
        isTrigger = "0",
        isKinematic = "0",
        colShape = "0",
    },

    patrol = {
        speed = "50",
        positions = "-150, 10, 0, 1, -250, 10, 0, 1, -250, 10, -100, 1, -150, 10, -100, 1",
    }
}
--[[ CajaPagar = {
--     transform = {
--         position = "  0.476969 ,0.071519 ,250.477413 " ,
--         rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
--         scale = "  20.000000 ,20.000000 ,20.000000 " ,
--     },
--     rigidbody = {
--         mass = "0.0",
--         isTrigger = "0",
--          isKinematic = "0",
--          colShape = "0",
--          scale = "0.35, 0.35, 0.35",
--     },
--     mesh = {
--         name = "CajaPagar.mesh",
--     }
-- }
-- Se ve pochangano: papelera, charco, imagenes carteles, BaldaFrigorifica, baldacolision --]]
BaldaPlatanos = {
    transform = {
        position = "  40.834900 ,0.000000 ,-23.514296 " ,
        rotation = "   0.000000, 0.000000, 0.000000, 0.000000 " ,
        scale = "  20.000000 ,20.000000 ,20.000000 " ,
    },
    rigidbody = {
        mass = "0.0",
        isTrigger = "0",
         isKinematic = "0",
         colShape = "0",
         scale = "0.35, 0.75, 0.35",
    },
    mesh = {
        name = "BaldaPlatano.mesh",
    }
}

entities = {"gamemanager", "light", "player", "camera", "object", "cart", "cartTrigger", "moneco", "BaldaPlatanos"}