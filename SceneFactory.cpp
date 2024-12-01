#include "SceneFactory.h"
#include "Tree.h"
#include "Bushes.h"
#include "Square.h"
#include "Sphere.h"
#include "PointLight.h"
#include "Firefly.h"
#include "Spotlight.h"

Scene* SceneFactory::createFirstScene()
{
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    Scene* scene = new Scene(camera);

    ShaderProgram* triangleShader = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greenVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greenFragment.glsl",
        camera
    );

    scene->addShader(triangleShader);


    Models* triangleModel = new Models(square, 6, false, false);
    triangleModel->setShaderProgram(triangleShader);
    scene->addObject(triangleModel);
    scene->init();

    return scene;
}

Scene* SceneFactory::createSecondScene()
{
    std::vector<std::string> faces = {
    "cubemap\\right.png", "cubemap\\left.png",
    "cubemap\\top.png", "cubemap\\bottom.png",
    "cubemap\\front.png", "cubemap\\back.png"
    };

    Skybox* skybox = new Skybox();
    skybox->init();
    skybox->loadCubemap(faces);
    Camera* camera = new Camera(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    ShaderProgram* skyboxs = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\skyboxV.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\skyboxF.glsl",
        camera
    );
    skybox->setShader(skyboxs);

    Scene* scene = new Scene(camera);
    scene->addSkybox(skybox);
    scene->addShader(skyboxs);

    ShaderProgram* grey = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyFragmentNew.glsl",
        camera
    );

    ShaderProgram* green = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greenVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greenFragment.glsl",
        camera
    );

    ShaderProgram* brown = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\brownVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\brownFragment.glsl",
        camera
    );

    ShaderProgram* firefly = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\fireflyFragment.glsl",
        camera
    );


    ShaderProgram* newShader = new ShaderProgram("PhongVertexShader.glsl", "PhongFragmentShader.glsl", camera);
    Models* house = new Models("objects/house.obj", "textures/house.png");
    house->setShaderProgram(brown);
    CompositeTransform* ct = new CompositeTransform();
    house->transform = ct;
    scene->addObject(house);

    Models* login = new Models("objects/logo.obj", "textures/grass2.png");
    login->setShaderProgram(brown);
    CompositeTransform* ct2 = new CompositeTransform();
    house->transform = ct2;
    scene->addObject(login);


    scene->addShader(firefly);
    scene->addShader(grey);
    scene->addShader(green);
    scene->addShader(brown);
    for(int i = 0; i <6 ; i++){
        Firefly* light = new Firefly(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f));
        light->setShaderProgram(firefly);
        light->addObserver(grey);
    
        grey->addLight(light);
        scene->addObject(light);
    }
    GLint idModelTransform = grey->getUniformLocation("modelMatrix");
    if (idModelTransform == -1) {
        std::cerr << "Warning: uniform 'modelMatrix' not found in shader." << std::endl;
    }

    for (int i = 0; i < 30; ++i) {
        Models* treeModel = new Models(tree, 92814, true, false);
        treeModel->setShaderProgram(grey);

        CompositeTransform* treeTransform = new CompositeTransform();

        float x = static_cast<float>(rand() % 80 - 40);
        float z = static_cast<float>(rand() % 80 - 40);
        treeTransform->addTransform(new Translate(glm::vec3(x, 0.0f, z)));

        float size = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.0f)));

        treeTransform->addTransform(new Scale(glm::vec3(size, size, size)));

        treeModel->transform = treeTransform;
        scene->addObject(treeModel);
    }

    for (int i = 0; i < 50; ++i) {
        Models* bushModel = new Models(bushes, 8730, true, false);
        bushModel->setShaderProgram(green);

        CompositeTransform* bushTransform = new CompositeTransform();

        float x = static_cast<float>(rand() % 100 - 50);
        float z = static_cast<float>(rand() % 100 - 50);
        bushTransform->addTransform(new Translate(glm::vec3(x, 0.0f, z)));

        float size = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (3.0f)));

        bushTransform->addTransform(new Scale(glm::vec3(size, size, size)));

        bushModel->transform = bushTransform;
        scene->addObject(bushModel);
    }

    Models* grass = new Models(square, 6, true, true);
    grass->setShaderProgram(brown);
    Texture* texture = new Texture();
    texture->loadFromFile("textures/grass2.png");
    grass->setTexture(texture);
    scene->addObject(grass);
    scene->init();

    return scene;
}

Scene* SceneFactory::createThirdScene()
{
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    Scene* scene = new Scene(camera);

    ShaderProgram* grey = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyFragmentNew.glsl",
        camera
    );
    scene->addShader(grey);

    GLint idModelTransform = grey->getUniformLocation("modelMatrix");
    if (idModelTransform == -1) {
        std::cerr << "Warning: uniform 'modelMatrix' not found in shader." << std::endl;
    }

    PointLight* light = new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), 1.0f, 0.09f, 0.032f);
    light->addObserver(grey);
    grey->addLight(light);

    for (int i = 0; i < 4; ++i) {
        Models* treeModel = new Models(sphere, 2880, true, false);
        treeModel->setShaderProgram(grey);

        CompositeTransform* treeTransform = new CompositeTransform();

        float x = (i % 2 == 0 ? -1.5f : 1.5f);
        float z = (i / 2 == 0 ? -1.5f : 1.5f);
        treeTransform->addTransform(new Translate(glm::vec3(x, 0.0f, z)));

        treeModel->transform= treeTransform;
        scene->addObject(treeModel);
    }
    scene->init();

    return scene;
}

Scene* SceneFactory::createFourthScene()
{
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    Scene* scene = new Scene(camera);

    ShaderProgram* constantShader = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\colorVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\colorFragment.glsl",
        camera
    );
    scene->addShader(constantShader);

    ShaderProgram* phongShader = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyFragmentNew.glsl",
        camera
    );
    scene->addShader(phongShader);

    ShaderProgram* lambertShader = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\lambertFragment.glsl",
        camera
    );
    scene->addShader(lambertShader);

    ShaderProgram* blinnShader = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\blinnFragment.glsl",
        camera
    );
    scene->addShader(blinnShader);

    PointLight* light = new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), 1.0f, 0.09f, 0.032f);
    light->addObserver(lambertShader);
    light->addObserver(phongShader);
    light->addObserver(blinnShader);

    lambertShader->addLight(light);
    phongShader->addLight(light);
    blinnShader->addLight(light);

    for (int i = 0; i < 4; ++i) {
        Models* model = new Models(sphere, 2880, true, false);

        CompositeTransform* transform = new CompositeTransform();
        float x = (i % 2 == 0 ? -2.5f : 2.5f);
        float z = (i / 2 == 0 ? -2.5f : 2.5f);
        transform->addTransform(new Translate(glm::vec3(x, 0.0f, z)));
        model->transform=transform;

        switch (i) {
        case 0:
            model->setShaderProgram(constantShader);
            break;
        case 2:
            model->setShaderProgram(lambertShader);
            break;
        case 1:
            model->setShaderProgram(phongShader);
            break;
        case 3:
            model->setShaderProgram(blinnShader);
            break;
        }

        scene->addObject(model);
    }

    scene->init();
    return scene;
}

Scene* SceneFactory::createFifthScene()
{
    Camera* camera = new Camera(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    Spotlight* light = new Spotlight(camera->position, camera->front, glm::vec3(1.0f, 1.0f, 1.0f),12.5f, 30.0f);
    light->attachToCamera(camera);
    camera->addObserver(light);
    Scene* scene = new Scene(camera);

    ShaderProgram* grey = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyFragmentNew.glsl",
        camera
    );
    light->addObserver(grey);

    grey->addLight(light);
    scene->addShader(grey);

    GLint idModelTransform = grey->getUniformLocation("modelMatrix");
    if (idModelTransform == -1) {
        std::cerr << "Warning: uniform 'modelMatrix' not found in shader." << std::endl;
    }
    for (int i = 0; i < 30; ++i) {
        Models* treeModel = new Models(tree, 92814, true, false);
        treeModel->setShaderProgram(grey);

        CompositeTransform* treeTransform = new CompositeTransform();

        float x = static_cast<float>(rand() % 80 - 40);
        float z = static_cast<float>(rand() % 80 - 40);
        treeTransform->addTransform(new Translate(glm::vec3(x, 0.0f, z)));

        float size = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.0f)));

        treeTransform->addTransform(new Scale(glm::vec3(size, size, size)));

        treeModel->transform = treeTransform;
        scene->addObject(treeModel);
    }

    for (int i = 0; i < 50; ++i) {
        Models* bushModel = new Models(bushes, 8730, true, false);
        bushModel->setShaderProgram(grey);

        CompositeTransform* bushTransform = new CompositeTransform();

        float x = static_cast<float>(rand() % 100 - 50);
        float z = static_cast<float>(rand() % 100 - 50);
        bushTransform->addTransform(new Translate(glm::vec3(x, 0.0f, z)));

        float size = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (3.0f)));

        bushTransform->addTransform(new Scale(glm::vec3(size, size, size)));

        bushModel->transform = bushTransform;
        scene->addObject(bushModel);
    }

    Models* grass = new Models(square, 6, true, true);

    grass->setShaderProgram(grey);
    scene->addObject(grass);
    scene->init();

    return scene;
}

