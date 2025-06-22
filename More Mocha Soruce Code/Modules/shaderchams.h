#pragma once

bool assetsLoaded = false;
std::unordered_map<std::string, Shader*> customShaders;

void LoadAssets()
{
    {
        auto& internalCustomShaders = customShaders;

        AssetBundle* bundle = AssetBundle::LoadFromFile(WriteIl2CppString("Mocha/assets.bin"));

        if (bundle != nullptr)
        {
            AssetBundleRequest* request = bundle->LoadAllAssetsAsync();

            if (request != nullptr)
            {
                Il2CppArray* assets = request->get_allAssets();

                for (int i = 0; i < assets->max_length; i++)
                {
                    UObject* object = il2cpp_array_get(assets, UObject*, i);

                    auto objtype = static_cast<Type*>(Type::GetType(object));

                    auto typestr = std::string(ReadIl2CppString(objtype->ToString()));

                    if (typestr.find("Type: Shader") != std::string::npos)
                    {
                        std::string objectName = ReadIl2CppString(object->GetName());

                        internalCustomShaders[objectName] = static_cast<Shader*>(object);
                    }
                }
            }
        }
    }

    Log::debug("loading test mocha");
    {
        auto& internalCustomShaders = customShaders;

        AssetBundle* bundle = AssetBundle::LoadFromFile(WriteIl2CppString("Mocha/mocha.bin"));

        if (bundle != nullptr)
        {
            AssetBundleRequest* request = bundle->LoadAllAssetsAsync();

            if (request != nullptr)
            {
                Il2CppArray* assets = request->get_allAssets();

                for (int i = 0; i < assets->max_length; i++)
                {
                    UObject* object = il2cpp_array_get(assets, UObject*, i);

                    auto objtype = static_cast<Type*>(Type::GetType(object));

                    auto typestr = std::string(ReadIl2CppString(objtype->ToString()));

                    if (typestr.find("Type: Shader") != std::string::npos)
                    {
                        std::string objectName = ReadIl2CppString(object->GetName());

                        internalCustomShaders[objectName] = static_cast<Shader*>(object);
                    }
                }
            }
        }
    }
    
}

void ShaderChamsLogic()
{
    /// we are in OnEvent (Ihook) so internals must be used here for globals

    bool& internalToggle = globals::shaderChams::toggle;

    if (internalToggle)
    {
        std::timed_mutex& internalMutex = playerlistMutex;
        int& internalTimeout = globals::playerlistMutexTimeout;
        auto& internalPlayerlist = photonPlayerlist;
        auto& internalCachedPlayerlist = cachedPlayerlist;
        bool& internalAssetsLoaded = assetsLoaded;
        auto& internalChamsMode = globals::shaderChams::chamsMode;
        auto& internalCustomShaders = customShaders;
        PlayerInfo& internalLocalPlayer = localPlayer;
        bool& internalLocalPlayerExists = localPlayerExists;
        bool& internalSelf = globals::shaderChams::self;

        ImVec4& internal_Color1 = globals::shaderChams::_Color1;
        ImVec4& internal_Color2 = globals::shaderChams::_Color2;

        float& internal_Rainbow1 = globals::shaderChams::_Rainbow1;
        float& internal_Rainbow2 = globals::shaderChams::_Rainbow2;
        float& internal_GlowIntensity = globals::shaderChams::_GlowIntensity;
        float& internal_Speed = globals::shaderChams::_Speed;
        float& internal_Wireframe = globals::shaderChams::_Wireframe;
        float& internal_LineWidth  = globals::shaderChams::_LineWidth ;
        
        ImVec4& internal_Emissioncolour = globals::shaderChams::_Emissioncolour;
        ImVec4& internal_WireColor = globals::shaderChams::_WireColor;

        if (internalLocalPlayerExists && internalLocalPlayer.loadingStage >= LoadingStage::LOADED)
        {
            RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(internalLocalPlayer.photonActorID);

            if (localPlayerPlayer != nullptr && localPlayerPlayer->get_IsInitialized() && localPlayerPlayer->
                get_IsInitialLoadFinished())
            {
                if (!internalAssetsLoaded)
                {
                    LoadAssets();
                }

                std::unique_lock<std::timed_mutex> lock(internalMutex, std::defer_lock);

                if (lock.try_lock_for(std::chrono::milliseconds(internalTimeout)))
                {
                    for (int i = 0; i < internalPlayerlist.size(); ++i)
                    {
                        if ((internalPlayerlist[i] != internalLocalPlayer.photonPlayer) || internalSelf)
                        {
                            if (internalCachedPlayerlist[internalPlayerlist[i]].loadingStage >= LoadingStage::LOADED)
                            {
                                PlayerInfo& targetPlayer = internalCachedPlayerlist[internalPlayerlist[i]];

                                RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(
                                    targetPlayer.photonActorID);

                                if (playerPlayer == nullptr) return;

                                if (playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished())
                                {
                                    Transform* playerTransform = playerPlayer->get_transform();

                                    if (playerTransform == nullptr) continue;

                                    int32_t childCount = playerTransform->get_ChildCount();

                                    if (childCount < 4)
                                        continue;

                                    Transform* playerMeshContainerTransform = nullptr;
                                    bool isNewBodyType = false;
                                    bool found = false;
                                    for (int j = 0; j < childCount; j++)
                                    {
                                        Transform* childTransform = playerTransform->GetChild(j);
                                        if (childTransform != nullptr)
                                        {
                                            GameObject* childGO = childTransform->get_gameObject();
                                            if (childGO != nullptr)
                                            {
                                                if (!childGO->get_active()) continue;

                                                std::string objectNameString = "";

                                                Il2CppString* objectName = childGO->GetName();

                                                if (objectName != nullptr && objectName->length > 0)
                                                {
                                                    objectNameString = ReadIl2CppString(objectName);
                                                }
                                                if (objectNameString.find(std::string("(PlayerMeshes)")) !=
                                                    std::string::npos)
                                                {
                                                    found = true;
                                                    playerMeshContainerTransform = childGO->get_transform();
                                                    break;
                                                }
                                                if (objectNameString.find(std::string("BAvatar_")) != std::string::npos)
                                                {
                                                    found = true;
                                                    playerMeshContainerTransform = childGO->get_transform();
                                                    isNewBodyType = true;
                                                    break;
                                                }
                                            }
                                        }
                                    }

                                    if (!found) continue;


                                    std::vector<SkinnedMeshRenderer*> skinnedMeshRenderers;
                                    std::vector<GameObject*> targetGOs;
                                    if (isNewBodyType)
                                    {
                                        /// full body or bean body 2.0

                                        if (playerMeshContainerTransform == nullptr) continue;
                                        if (playerMeshContainerTransform->get_ChildCount() < 1) continue;
                                        Transform* differenceBase = playerMeshContainerTransform->GetChild(1);

                                        if (differenceBase == nullptr) continue;
                                        if (differenceBase->get_ChildCount() < 1) continue;

                                        {
                                            Transform* childZero = differenceBase->GetChild(0);
                                            if (childZero != nullptr && childZero->get_ChildCount() >= 1)
                                            {
                                                Transform* childZeroZero = childZero->GetChild(0);
                                                if (childZeroZero != nullptr)
                                                {
                                                    GameObject* firstPersonMeshesGO = childZeroZero->get_gameObject();
                                                    if (firstPersonMeshesGO != nullptr)
                                                    {
                                                        targetGOs.push_back(firstPersonMeshesGO);
                                                    }
                                                }
                                            }
                                        }
                                        {
                                            Transform* childOne = differenceBase->GetChild(1);
                                            if (childOne != nullptr && childOne->get_ChildCount() >= 1)
                                            {
                                                Transform* childOneZero = childOne->GetChild(0);
                                                if (childOneZero != nullptr)
                                                {
                                                    GameObject* thirdPersonMeshesGO = childOneZero->get_gameObject();
                                                    if (thirdPersonMeshesGO != nullptr)
                                                    {
                                                        targetGOs.push_back(thirdPersonMeshesGO);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        /// Legacy bean body
                                        if (playerMeshContainerTransform != nullptr && playerMeshContainerTransform->
                                            get_ChildCount() >= 1)
                                        {
                                            {
                                                Transform* childZero = playerMeshContainerTransform->GetChild(0);
                                                if (childZero != nullptr && childZero->get_ChildCount() >= 1)
                                                {
                                                    Transform* childZeroZero = childZero->GetChild(0);
                                                    if (childZeroZero != nullptr)
                                                    {
                                                        GameObject* firstPersonMeshesGO = childZeroZero->
                                                            get_gameObject();
                                                        if (firstPersonMeshesGO != nullptr)
                                                        {
                                                            targetGOs.push_back(firstPersonMeshesGO);
                                                        }
                                                    }
                                                }
                                            }
                                            {
                                                Transform* childOne = playerMeshContainerTransform->GetChild(1);
                                                if (childOne != nullptr && childOne->get_ChildCount() >= 1)
                                                {
                                                    Transform* childOneZero = childOne->GetChild(0);
                                                    if (childOneZero != nullptr)
                                                    {
                                                        GameObject* thirdPersonMeshesGO = childOneZero->
                                                            get_gameObject();
                                                        if (thirdPersonMeshesGO != nullptr)
                                                        {
                                                            targetGOs.push_back(thirdPersonMeshesGO);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    for (auto& gameObject : targetGOs)
                                    {
                                        Il2CppArray* comps = gameObject->GetComponents("UnityEngine.Component");

                                        if (comps->max_length >= 2)
                                        {
                                            /// these game objects always have SkinnedMeshRenderer* as the second component

                                            SkinnedMeshRenderer* object = il2cpp_array_get(
                                                comps, SkinnedMeshRenderer*, 1);
                                            skinnedMeshRenderers.push_back(object);
                                        }
                                    }

                                    std::string currentSelectedShaderString =
                                        globals::shaderChams::GetCurrentModeString();

                                    for (auto& skinnedMeshRender : skinnedMeshRenderers)
                                    {
                                        if (skinnedMeshRender != nullptr)
                                        {
                                            Material* skinnedMeshRendererMaterial = skinnedMeshRender->getMaterial();

                                            if (skinnedMeshRendererMaterial != nullptr)
                                            {
                                                Shader* appliedShader = skinnedMeshRendererMaterial->get_shader();

                                                if (appliedShader != nullptr)
                                                {
                                                    std::string shaderNameString = "";

                                                    Il2CppString* shaderName = appliedShader->GetName();

                                                    if (shaderName != nullptr && shaderName->length > 0)
                                                    {
                                                        shaderNameString = ReadIl2CppString(shaderName);
                                                    }

                                                    if (shaderNameString.find(currentSelectedShaderString) == std::string::npos)
                                                    {
                                                        Material* material = nullptr;

                                                        switch (internalChamsMode)
                                                        {
                                                        //! ctor & setShader both want the class and not a pointer/object of the class!!!

                                                        case globals::shaderChams::Mode::Chams:
                                                            {
                                                                Shader*& shader = internalCustomShaders["Mocha/ChamsShader"];

                                                                material = Material::ctor(shader);
                                                                material->setShader(shader);
                                                                break;
                                                            }
                                                        case globals::shaderChams::Mode::ColorChams:
                                                            {
                                                                Shader*& shader = internalCustomShaders["ColorChams"];
                                                                material = Material::ctor(shader);
                                                                material->setShader(shader);
                                                                break;
                                                            }
                                                        case globals::shaderChams::Mode::Pulsing:
                                                            {
                                                                Shader*& shader = internalCustomShaders["Pulsing"];
                                                                material = Material::ctor(shader);
                                                                material->setShader(shader);
                                                                break;
                                                            }
                                                        case globals::shaderChams::Mode::Wireframe:
                                                            {
                                                                Shader*& shader = internalCustomShaders["Wireframe"];
                                                                material = Material::ctor(shader);
                                                                material->setShader(shader);
                                                                break;
                                                            }
                                                        case globals::shaderChams::Mode::Rainbow:
                                                            {
                                                                Shader*& shader = internalCustomShaders["Rainbow"];
                                                                material = Material::ctor(shader);
                                                                material->setShader(shader);
                                                                break;
                                                            }
                                                        default:
                                                            Shader*& shader = internalCustomShaders["Rainbow"];

                                                            material = Material::ctor(shader);
                                                            material->setShader(shader);
                                                            break;
                                                        }

                                                        if (material != nullptr)
                                                        {
                                                            switch (internalChamsMode)
                                                            {
                                                            case globals::shaderChams::Mode::Chams:
                                                                {
                                                                    material->SetColor(WriteIl2CppString("_Color1"), internal_Color1);
                                                                    material->SetColor(WriteIl2CppString("_Color2"), internal_Color2);

                                                                    material->SetFloat(WriteIl2CppString("_Rainbow1"), internal_Rainbow1);
                                                                    material->SetFloat(WriteIl2CppString("_Rainbow2"), internal_Rainbow2);
                                                                    material->SetFloat(WriteIl2CppString("_GlowIntensity"), internal_GlowIntensity);
                                                                    material->SetFloat(WriteIl2CppString("_Speed"), internal_Speed);
                                                                    material->SetFloat(WriteIl2CppString("_Wireframe"), internal_Wireframe);
                                                                    material->SetFloat(WriteIl2CppString("_LineWidth"), internal_LineWidth);
                                                                    break;
                                                                }
                                                            case globals::shaderChams::Mode::ColorChams:
                                                                {
                                                                    material->SetColor(
                                                                        WriteIl2CppString("_Color1"),
                                                                        internal_Color1);
                                                                    material->SetColor(
                                                                        WriteIl2CppString("_Color2"),
                                                                        internal_Color2);
                                                                    break;
                                                                }
                                                            case globals::shaderChams::Mode::Pulsing:
                                                                {
                                                                    material->SetColor(
                                                                        WriteIl2CppString("_Emissioncolour"),
                                                                        internal_Emissioncolour);
                                                                    break;
                                                                }
                                                            case globals::shaderChams::Mode::Wireframe:
                                                                {
                                                                    material->SetColor(
                                                                        WriteIl2CppString("_WireColor"),
                                                                        internal_WireColor);
                                                                    break;
                                                                }
                                                            default:
                                                                break;
                                                            }

                                                            skinnedMeshRender->setMaterial(material);

                                                            int32_t materialCount = skinnedMeshRender->
                                                                GetMaterialCount();

                                                            auto* materialType = static_cast<Type*>(Type::getType(
                                                                il2cpp_string_new_spoof("UnityEngine.Material")));
                                                            Il2CppArray* materialArray = Array::createInstance(
                                                                materialType, materialCount);

                                                            for (int k = 0; k < materialCount; k++)
                                                            {
                                                                il2cpp_array_set(materialArray, Material*, k, material);
                                                            }
                                                            skinnedMeshRender->set_materials(materialArray);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        else
                                        {
                                            Log::debug("mesh not found");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    Log::error("playerlistMutex timed out in SpawnAssetAll (callback)!");
                }
            }
            else
            {
                internalAssetsLoaded = false;
            }
        }
        else
        {
            internalAssetsLoaded = false;
        }
    }
}
