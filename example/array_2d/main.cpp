#include <CLI/CLI.hpp>
#include <nuwe_cimiss/client.h>
#include <map>

int main(int argc, char** argv) {
    std::string user;
    std::string password;
    std::string config_file;

    CLI::App app{ "example_array_2d" };
    app.add_option("--user", user, "user name")->required();
    app.add_option("--password", password, "user password")->required();
    app.add_option("--client-config", config_file, "config file");

    CLI11_PARSE(app, argc, argv);

    const std::string interface_id = "getSurfEleByTimeRange";
    const std::string server_id = "NMIC_MUSIC_CMADAAS";

    nuwe_cimiss::ApiParams params = {
        {"dataCode", "SURF_CHN_MUL_HOR"},
        {"elements", "Station_Id_d,Lat,Lon,Alti,Day,Hour,PRS_Sea,TEM,DPT,WIN_D_INST,WIN_S_INST,PRE_1h,PRE_6h,PRE_24h,PRS"},
        {"timeRange", "[20190817000000,20190817020000)"},
        {"orderby", "Station_ID_d:ASC"},
        {"limitCnt", "10"},
    };

    nuwe_cimiss::CimissClientConfig config;
    config.server_id = server_id;

    nuwe_cimiss::CimissClient client{config, config_file};
    client.connect(user, password);
    auto result = client.callAPI_to_array2D(interface_id, params, server_id);

    return 0;
}