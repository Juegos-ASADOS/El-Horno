function changeNextScene()
    local manager = SceneManager.getSceneManager();
    manager:changeScene();
end 

function loadNextScene()
    local manager = SceneManager.getSceneManager();
    manager:nextScene("prueba");
end 