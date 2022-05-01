gamemanager = {
	transform = {
        position = " 0 ,0 ,0 ",
        rotation = " 0 ,0 ,0 ",
        scale = " 0 ,0 ,0 ",
    },

    gamemanager = {      
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
    },

    audioListener = {

    },
}

player = {
    transform = {
        position = " -50, 40, 0 ",
        rotation = " 0 ,0 ,0 ",
        scale = " 10,10,10 ",
    },

    mesh = {
        name = "pipo",
    },

    rigidbody = {
        mass = "2",
        isTrigger = "0",
        isKinematic = "0",
        colShape = "0",
    },

    audioComponent = {

    },

    playerController = {
        speed = "1500",
        maxForce = "200",
    },

    playerInteract = {

    },

    animatorController = {
        Idle = "walk",
		walk = "Idle",
		Idle_with_product = "walk_with_product",
		walk_with_product = "Idle_with_product",
		Idle_with_cart = "walk_with_cart",
		walk_with_cart = "Idle_with_cart",
		AnyState = "Idle",
		AnyState = "Idle_with_product",
		AnyState = "Idle_with_cart",
    },
}

object = {
    transform = {
        position = " 0, -15, 0 ",
        rotation = " 0 ,0 ,0 ",
        scale = " 15, 0.1, 15 ",
    },

    mesh = {
        name = "cube",
    },

    rigidbody = {
        mass = "0",
        isTrigger = "0",
        isKinematic = "0",
        colShape = "0",
    },
}

cart = {
    transfom = {
        position = " 0, 0, 2.5 ",
        rotation = " 0 ,0 ,0 ",
        scale = " 0.02, 0.02, 0.02 ",
    },

    mesh = {
        name = "cube",
    },

    rigidbody = {
        mass = "2",
        isTrigger = "1",
        isKinematic = "1",
        colShape = "0",
    },

    parent = "player",
}

cartTrigger = {

}

entities = {"gamemanager", "light", "camera", "player", "object"}