#include <iostream>
#include "HCNetSDK.h"

using namespace std;

int main() {
    NET_DVR_Init();

    NET_DVR_DEVICEINFO_V30 deviceInfo = {0};
    LONG userID = NET_DVR_Login_V30("Ip_address", 80, "admin", "Password", &deviceInfo);

    if (userID < 0) {
        cerr << "Error connexion to the camera : " << NET_DVR_GetLastError() << endl;
        NET_DVR_Cleanup();
        return 1;
    }

    NET_DVR_COMPRESSIONCFG_V30 compressionCfg = {0};
    if (NET_DVR_GetDVRConfig(userID, NET_DVR_GET_COMPRESSCFG_V30, 1, &compressionCfg, sizeof(compressionCfg), NULL)) {

        compressionCfg.struNormHighRecordPara.dwVideoBitrate = 1024;

        if (NET_DVR_SetDVRConfig(userID, NET_DVR_SET_COMPRESSCFG_V30, 1, &compressionCfg, sizeof(compressionCfg))) {
            cout << "Paramètres du flux principal modifiés avec succès." << endl;
        } else {
            cerr << "Error, cannot set the configuration: " << NET_DVR_GetLastError() << endl;
        }
    } else {
        cerr << "Cannot get access to the configuration of the camera : " << NET_DVR_GetLastError() << endl;
    }

    // Deconnexion and clear
    NET_DVR_Logout(userID);
    NET_DVR_Cleanup();

    return 0;
}
