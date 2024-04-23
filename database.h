#include <format>
#include <sqlite3.h>
#include <string>
#include <vector>


struct Text
{
    int id;
    std::string title;
    std::string text;
    std::string summary;
    int resourceId;
    std::string resourcePath;
};


class Database
{
public:
    Database(const std::string& path = "example.db")
    {
        exit = sqlite3_open(path.c_str(), &DB);
    }
    ~Database() { sqlite3_close(DB); }

    void createTables()
    {
        char* messaggeError;
        std::string query_text = "CREATE TABLE IF NOT EXISTS text("
                                 "ID INTEGER PRIMARY KEY  AUTOINCREMENT,"
                                 "title TEXT,"
                                 "text TEXT,"
                                 "summary TEXT,"
                                 "resourceId INT,"
                                 "resourcePath TEXT);";
        exit = sqlite3_exec(DB, query_text.c_str(), NULL, NULL, &messaggeError);
        // TODO: Error message output

        std::string query_resouce = "CREATE TABLE IF NOT EXISTS resource("
                                    "ID INTEGER PRIMARY KEY  AUTOINCREMENT,"
                                    "type TEXT  NOT NULL,"
                                    "description TEXT);";
        exit = sqlite3_exec(DB, query_resouce.c_str(), NULL, NULL, &messaggeError);
        // TODO: Error message output
    }

    void addText(std::string title, std::string text, std::string summary,
                 int resourceId = 1, std::string resourcePath = "")
    {
        char* messaggeError;

        std::string query =
                std::format("INSERT INTO text (title, text, summary, resourceId, "
                            "resourcePath) VALUES ('{}', '{}', '{}', {}, '{}')",
                            title, text, summary, resourceId, resourcePath);
        exit = sqlite3_exec(DB, query.c_str(), NULL, NULL, &messaggeError);
    }

    std::vector<Text> getAllTexts()
    {
        char* messaggeError;

        std::string query = "SELECT * FROM text;";
        std::vector<Text> data;
        exit = sqlite3_exec(DB, query.c_str(), textCallback, &data, &messaggeError);

        return data;
    }

private:
    sqlite3* DB;
    int exit;

    static int textCallback(void* data, int numOfColumns, char** row, char** columnsNames)
    {
        std::vector<Text>* _data = static_cast<std::vector<Text>*>(data);
        _data->push_back({std::stoi(row[0]), row[1], row[2], row[3], std::stoi(row[4]), row[5]});

        return 0;
    }
};
