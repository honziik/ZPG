#include "SceneFactory.h"
#include "Tree.h"
#include "Bushes.h"
#include "Square.h"
#include "Sphere.h"
#include "PointLight.h"
#include "Firefly.h"
#include "Spotlight.h"
#include "DynamicRotate.cpp"
#include "LinearMove.cpp"
#include "BezierMove.cpp"


//todo bezirova krivka + zmenit glsl soubory + vyjebat veci z aplikace
Scene* SceneFactory::createFirstScene()
{
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    Scene* scene = new Scene(camera);

    ShaderProgram* shader = new ShaderProgram(
        "shaders/greenVertex.glsl",
        "shaders/greenFragment.glsl",
        camera
    );

    scene->addShader(shader);

    const float triangle[] = {
     0.0f,  0.5f, 0.0f,  0.0f,  0.0f,  1.0f,
     -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  1.0f
    };

    scene->addObject(ModelFactory::createModel(triangle, 3, shader,{}));
    scene->init();

    return scene;
}

Scene* SceneFactory::createSecondScene()
{
    Camera* camera = new Camera(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    std::vector<std::string> faces = {
    "cubemap\\right.png", "cubemap\\left.png",
    "cubemap\\top.png", "cubemap\\bottom.png",
    "cubemap\\front.png", "cubemap\\back.png"
    };

    Skybox* skybox = new Skybox(camera);
    skybox->init();
    skybox->loadCubemap(faces);
    camera->addObserver(skybox);

    ShaderProgram* skyboxs = new ShaderProgram(
        "shaders/skyboxV.glsl",
        "shaders/skyboxF.glsl",
        camera
    );
    skybox->setShader(skyboxs);

    Scene* scene = new Scene(camera);
    scene->addSkybox(skybox);

    ShaderProgram* grey = new ShaderProgram(
        "shaders/greyVertex.glsl",
        "shaders/greyFragmentNew.glsl",
        camera
    );

    ShaderProgram* green = new ShaderProgram(
        "shaders/greenVertex.glsl",
        "shaders/greenFragment.glsl",
        camera
    );

    ShaderProgram* brown = new ShaderProgram(
        "shaders/brownVertex.glsl",
        "shaders/brownFragment.glsl",
        camera
    );

    ShaderProgram* firefly = new ShaderProgram(
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\greyVertex.glsl",
        "C:\\Users\\User\\source\\repos\\zpg\\zpg\\shaders\\fireflyFragment.glsl",
        camera
    );
    ShaderProgram* newShader = new ShaderProgram("PhongVertexShader.glsl", "PhongFragmentShader.glsl", camera);


    scene->addObject(ModelFactory::createModelFromObject("objects/house.obj", "textures/house.png", brown, {}));

    std::vector<Transform*> transforms;
    transforms.push_back(new Scale(glm::vec3(30.0f, 30.0f, 30.0f)));
    scene->addObject(ModelFactory::createModelFromObject("objects/logo.obj", "textures/grass2.png", brown, transforms));

    scene->addShader(grey);
    scene->addShader(brown);
    scene->addShader(firefly);
    scene->addShader(green);
    scene->addShader(skyboxs);

   for (int i = 0; i <6; i++) {
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
        float x = static_cast<float>(rand() % 80 - 40);
        float z = static_cast<float>(rand() % 80 - 40);
        
        std::vector<Transform*> transforms;
        transforms.push_back(new Translate(glm::vec3(x, 0.0f, z)));
        float size = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.0f)));
        transforms.push_back(new Scale(glm::vec3(size, size, size)));
        transforms.push_back(new DynamicRotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
     
        scene->addObject(ModelFactory::createModel(tree, 92814, grey, transforms));
    }

    for (int i = 0; i < 50; ++i) {
        std::vector<Transform*> transforms;
        float x = static_cast<float>(rand() % 100 - 50);
        float z = static_cast<float>(rand() % 100 - 50);
        transforms.push_back(new Translate(glm::vec3(x, 0.0f, z)));

        float size = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (3.0f)));
        transforms.push_back(new Scale(glm::vec3(size, size, size)));

        scene->addObject(ModelFactory::createModel(bushes, 8730, green, transforms));
    }
    
    scene->addObject(ModelFactory::createModelWithTexture(square, 6, brown, {}, "textures/grass2.png"));
    scene->init();

    return scene;
}

Scene* SceneFactory::createThirdScene()
{
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    Scene* scene = new Scene(camera);

    ShaderProgram* grey = new ShaderProgram(
        "shaders/greyVertex.glsl",
        "shaders/greyFragmentNew.glsl",
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
        std::vector<Transform*> transforms;
        float x = (i % 2 == 0 ? -1.5f : 1.5f);
        float z = (i / 2 == 0 ? -1.5f : 1.5f);
        transforms.push_back(new Translate(glm::vec3(x, 0.0f, z)));

        scene->addObject(ModelFactory::createModel(sphere, 2880, grey, transforms));
    }
    scene->init();

    return scene;
}

Scene* SceneFactory::createFourthScene()
{
    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    Scene* scene = new Scene(camera);

    ShaderProgram* constantShader = new ShaderProgram(
        "shaders/colorVertex.glsl",
        "shaders/colorFragment.glsl",
        camera
    );
    scene->addShader(constantShader);

    ShaderProgram* phongShader = new ShaderProgram(
        "shaders/greyVertex.glsl",
        "shaders/greyFragmentNew.glsl",
        camera
    );
    scene->addShader(phongShader);

    ShaderProgram* lambertShader = new ShaderProgram(
        "shaders/greyVertex.glsl",
        "shaders/lambertFragment.glsl",
        camera
    );
    scene->addShader(lambertShader);

    ShaderProgram* blinnShader = new ShaderProgram(
        "shaders/greyVertex.glsl",
        "shaders/blinnFragment.glsl",
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
        "shaders/greyVertex.glsl",
        "shaders/greyFragmentNew.glsl",
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
        float x = static_cast<float>(rand() % 80 - 40);
        float z = static_cast<float>(rand() % 80 - 40);

        std::vector<Transform*> transforms;
        transforms.push_back(new Translate(glm::vec3(x, 0.0f, z)));
        float size = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.0f)));
        transforms.push_back(new Scale(glm::vec3(size, size, size)));
        transforms.push_back(new DynamicRotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)));

        scene->addObject(ModelFactory::createModel(tree, 92814, grey, transforms));
    }

    for (int i = 0; i < 50; ++i) {
        std::vector<Transform*> transforms;
        float x = static_cast<float>(rand() % 100 - 50);
        float z = static_cast<float>(rand() % 100 - 50);
        transforms.push_back(new Translate(glm::vec3(x, 0.0f, z)));

        float size = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (3.0f)));
        transforms.push_back(new Scale(glm::vec3(size, size, size)));

        scene->addObject(ModelFactory::createModel(bushes, 8730, grey, transforms));
    }

    const float square2[] = {
        -50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
         50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
        -50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,
        -50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,
         50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
         50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f
    };

    std::vector<Transform*> transforms;
    transforms.push_back(new LinearMove(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 0.0f, 0.0f), 0.3f));
    transforms.push_back(new Scale(glm::vec3(3.0f, 3.0f, 3.0f)));

    ShaderProgram* brown = new ShaderProgram(
        "shaders/brownVertex.glsl",
        "shaders/brownFragment.glsl",
        camera
    );
    scene->addShader(brown);
    scene->addObject(ModelFactory::createModelFromObject("objects/zombie.obj", "textures/zombie.png", brown, transforms));

    std::vector<Transform*> transforms2;
    std::vector<glm::vec3> controlPoints = {
        {-2, 0, 0}, {0, 0, 2}, {2, 0, 4}, {4, 0, 0}, {2, 0, 4}, {0, 0, 2}, {-2, 0, 0}
    };
    transforms2.push_back(new BezierMove(controlPoints, 0.5f));
    transforms2.push_back(new Scale(glm::vec3(3.0f, 3.0f, 3.0f)));
    scene->addObject(ModelFactory::createModelFromObject("objects/zombie.obj", "textures/zombie.png", brown, transforms2));


    scene->addObject(ModelFactory::createModel(square2, 6, grey, {}));
    scene->init();

    return scene;
}

