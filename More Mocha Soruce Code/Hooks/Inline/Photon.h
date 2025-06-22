#pragma once


struct RoomOptions : Il2CppObject { // IMODLKDLEHD



};



typedef bool (*JoinOrCreateRoom_t)(Il2CppString*, RoomOptions*, void*, Il2CppArray*, void*);
JoinOrCreateRoom_t JoinOrCreateRoom_o = nullptr;
bool __fastcall JoinOrCreateRoom_Ihook(Il2CppString* roomName, RoomOptions* roomOptions, void* typedLobby, Il2CppArray* expectedUsers, void* methodInfo) {
    if (!globals::Ihooks::joinOrCreateRoom)
        return JoinOrCreateRoom_o(roomName, roomOptions, typedLobby, expectedUsers, methodInfo);

    Log::debug("Enter RoomJoin!");


    Hashtable* CustomRoomProperties = GetField<Hashtable*>(roomOptions, 32);

    if (CustomRoomProperties != nullptr) {

        Log::debug("properties good");

Il2CppString* htString = CustomRoomProperties->ToString();

if (htString != nullptr) {
    Log::debug("Custom Properties String: " + std::string(ReadIl2CppString(htString)));
}

    }



    return JoinOrCreateRoom_o(roomName, roomOptions, typedLobby, expectedUsers, methodInfo);

    /*

    if (!initialDone)
    {
        roomOptionsSaved = roomOptions;
        typedLobbySaved = typedLobby;
        initialDone = true;
    }
    Log::debug(ReadIl2CppString(roomName));

    Il2CppString* newRoom = WriteIl2CppString(globals::roomIdBuffer);
    globals::Ihooks::joinOrCreateRoom = false;
    if (initialDone)
    {
        Log::debug("Initial Done.");
        return JoinOrCreateRoom_o(newRoom, roomOptionsSaved, typedLobbySaved, expectedUsers);
    }
    else
    {
        return JoinOrCreateRoom_o(newRoom, roomOptions, typedLobby, expectedUsers);
    }
    */
}

typedef void (*OnJoinRoomFailed_t)(int16_t, Il2CppString*, void*);
OnJoinRoomFailed_t OnJoinRoomFailed_o = nullptr;
void __fastcall OnJoinRoomFailed_Ihook(int16_t returnCode, Il2CppString* message, void* methodInfo) {
    if (!globals::Ihooks::onJoinRoomFailed)
        return OnJoinRoomFailed_o(returnCode, message, methodInfo);

    Log::debug("Return Code: " + std::to_string(returnCode));
    Log::debug("Message: " + std::string(ReadIl2CppString(message)));

    return OnJoinRoomFailed_o(returnCode, message, methodInfo);
}


/*typedef bool (*ToString_t)(Hashtable* hashTable);
bool ToString() {
    ToStringconst auto func = (ToString_t)(GameAssembly + 0x636D160);
    return func(this);
}*/

typedef void (*OpJoinRoom_t)(void*, void*, void*); // LDBAOCBHDEH*, AGHFKKKCGMD*, MethodInfo
OpJoinRoom_t OpJoinRoom_o = nullptr;
void __fastcall OpJoinRoom_Ihook(void* loadBalancingClient, void* EnterRoomOptions, void* methodInfo) {
    if (!globals::Ihooks::OpJoinRoom)
        return OpJoinRoom_o(loadBalancingClient, EnterRoomOptions, methodInfo);


    Log::debug("Enter OpRoomJoin!");


    if (EnterRoomOptions != nullptr) {

        RoomOptions* roomOptions = GetField<RoomOptions*>(EnterRoomOptions, 24); // IMODLKDLEHD < EnterRoomOptions

        if (roomOptions != nullptr) {

            Hashtable* CustomRoomProperties = GetField<Hashtable*>(roomOptions, 32);

            if (CustomRoomProperties != nullptr) {

                Log::debug("properties good");

                Il2CppString* htString = CustomRoomProperties->ToString();

                std::string htcppString = ReadIl2CppString(htString);

                if (htString != nullptr) {
                    Log::debug("Custom Properties String: " + htcppString);

                    PhotonPlayer* localPlayer = GetField<PhotonPlayer*>(loadBalancingClient, 264);

                    Log::debug("1");

                    if (localPlayer != nullptr) {

                        /// playerid test also did nothing. we cant get playerid before actually joining the room???

                        //Log::debug("12");
                        //int LocalPlayerId = localPlayer->getActorNumber();
                        //Log::debug("13");


                        /// this shit did now work at all, doesn't crash tho lol

                        bool falseBool = false;
                        Il2CppObject* falseBoolObj = il2cpp_value_box_spoof(FindClass("System.Boolean"), &falseBool);
                        
                        
                        //Il2CppObject* playerIdObject = il2cpp_value_box_spoof(findClass("System.Int32"), &LocalPlayerId);
                        Log::debug("14");

                        if (htcppString.find("(System.Byte)250") != std::string::npos) {
                            CustomRoomProperties->set_Item(250, (UObject*)falseBoolObj);
                        }
                        else {
                            CustomRoomProperties->Add(250, (UObject*)falseBoolObj);
                        }
                        Log::debug("15");
                        Log::debug(std::string(ReadIl2CppString(CustomRoomProperties->ToString())));
                    }
                }

            }

            Il2CppArray* propsforlobby = GetField<Il2CppArray*>(roomOptions, 40);

            if (propsforlobby != nullptr) {

                Log::debug("p: ===================");

                for (int i = 0; i < propsforlobby->max_length; i++) {
                    Il2CppString* thing = il2cpp_array_get(propsforlobby, Il2CppString*, i);

                    if (thing != nullptr) {

                        Log::debug(ReadIl2CppString(thing));

                    }

                }
                Log::debug("p: ===================");

            }
            {
                Il2CppArray* propsforlobby = GetField<Il2CppArray*>(roomOptions, 48);

                if (propsforlobby != nullptr) {

                    Log::debug("pl: ===================");

                    for (int i = 0; i < propsforlobby->max_length; i++) {
                        Il2CppString* thing = il2cpp_array_get(propsforlobby, Il2CppString*, i);

                        if (thing != nullptr) {

                            Log::debug(ReadIl2CppString(thing));

                        }

                    }
                    Log::debug("pl: ===================");

                }
            }

        }
    }


    return OpJoinRoom_o(loadBalancingClient, EnterRoomOptions, methodInfo);
}




///  this shit gives some wack ass gameProperties, idk what else to do with them tbh
typedef void (*OpSetPropertiesOfRoom_t)(void*, Hashtable*, Hashtable*, void*, void*);
OpSetPropertiesOfRoom_t OpSetPropertiesOfRoom_o = nullptr;
void __fastcall OpSetPropertiesOfRoom_Ihook(void* loadBalancingClient, Hashtable* gameProperties, Hashtable* expectedProperties, void* webFlags, void* methodInfo) {
    if (!globals::Ihooks::OpSetPropertiesOfRoom)
        return OpSetPropertiesOfRoom_o(loadBalancingClient, gameProperties, expectedProperties, webFlags, methodInfo);


    Log::debug("set props hook hit!");

    if (gameProperties != nullptr) {

        Log::debug("gameProperties good");

        Il2CppString* htString = gameProperties->ToString();

        std::string htcppstring;

        if (htString != nullptr) {
            htcppstring = ReadIl2CppString(htString);
            Log::debug("gameProperties String: " + htcppstring);
        }

        bool falseBool = false;
        Il2CppObject* falseBoolObj = il2cpp_value_box_spoof(FindClass("System.Boolean"), &falseBool);


        //Il2CppObject* playerIdObject = il2cpp_value_box_spoof(findClass("System.Int32"), &LocalPlayerId);
        Log::debug("14");

        if (htcppstring.find("(System.Byte)250") != std::string::npos) {
            gameProperties->set_Item(250, (UObject*)falseBoolObj);
        }
        else {
            gameProperties->Add(250, (UObject*)falseBoolObj);
        }
        Log::debug("15");
        Log::debug(std::string(ReadIl2CppString(gameProperties->ToString())));

    }

    if (expectedProperties != nullptr) {

        Log::debug("expectedProperties good");

        Il2CppString* htString = expectedProperties->ToString();

        if (htString != nullptr) {
            Log::debug("expectedProperties String: " + std::string(ReadIl2CppString(htString)));
        }

    }


    return OpSetPropertiesOfRoom_o(loadBalancingClient, gameProperties, expectedProperties, webFlags, methodInfo);
}