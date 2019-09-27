#include <CLI/CLI.hpp>
#include <nuwe_cimiss/client.h>

int main(int argc, char** argv) {
    std::string user;
    std::string password;
    std::string config_file;

    CLI::App app{ "example_grid_array_2d" };
    app.add_option("--user", user, "user name")->required();
    app.add_option("--password", password, "user password")->required();
    app.add_option("--client-config", config_file, "config file");

    CLI11_PARSE(app, argc, argv);

    const std::string interface_id = "getNafpEleGridByTimeAndLevelAndValidtime";
    const std::string server_id = "NMIC_MUSIC_CMADAAS";

    nuwe_cimiss::ApiParams params = {
        {"dataCode", "NAFP_FOR_FTM_KWBC_GLB"},
        {"time", "20190921000000"},
        {"fcstEle", "TEM"},
        {"levelType", "1"},
        {"fcstLevel", "0"},
        {"validTime", "0"},
    };

    nuwe_cimiss::CimissClientConfig config;
    config.server_id = server_id;

    nuwe_cimiss::CimissClient client{config, config_file};
    client.Connect(user, password);
    auto grid_array_2d = client.callAPI_to_gridArray2D(interface_id, params, server_id);

    return 0;
}