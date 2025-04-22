#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <thread>
#include <chrono>
#include <random>
#include <sstream>
#include <fstream>
#include <iomanip>

// Singleton Logger
class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& msg) {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[LOG] " << msg << std::endl;
    }

private:
    std::mutex mtx;
    Logger() {}
};

// Fake Blog Post
struct BlogPost {
    int id;
    std::string title;
    std::string content;
    std::string author;
    std::string timestamp;
};

// Blog Database (fake multithreaded nonsense)
class BlogDatabase {
public:
    void addPost(const BlogPost& post) {
        std::lock_guard<std::mutex> lock(dbMutex);
        posts[post.id] = post;
        Logger::getInstance().log("Added post with ID: " + std::to_string(post.id));
    }

    BlogPost getPost(int id) {
        std::lock_guard<std::mutex> lock(dbMutex);
        return posts[id];
    }

    std::vector<BlogPost> getAllPosts() {
        std::lock_guard<std::mutex> lock(dbMutex);
        std::vector<BlogPost> all;
        for (auto& [_, post] : posts) all.push_back(post);
        return all;
    }

private:
    std::map<int, BlogPost> posts;
    std::mutex dbMutex;
};

// Utils
std::string currentTime() {
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%F %T");
    return ss.str();
}

std::string randomContent(int length) {
    static const std::string charset = "abcdefghijklmnopqrstuvwxyz ";
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<> dist(0, charset.size() - 1);
    std::string result;
    for (int i = 0; i < length; ++i) result += charset[dist(rng)];
    return result;
}

// Main
int main() {
    BlogDatabase db;
    std::vector<std::thread> workers;

    for (int i = 1; i <= 10; ++i) {
        workers.emplace_back([&, i]() {
            BlogPost post = {
                .id = i,
                .title = "Post " + std::to_string(i),
                .content = randomContent(300),
                .author = "Author" + std::to_string(i),
                .timestamp = currentTime()
            };
            db.addPost(post);
        });
    }

    for (auto& t : workers) t.join();

    auto posts = db.getAllPosts();
    for (const auto& post : posts) {
        std::cout << "\n---\nID: " << post.id <<
                     "\nTitle: " << post.title <<
                     "\nAuthor: " << post.author <<
                     "\nTime: " << post.timestamp <<
                     "\nContent: " << post.content.substr(0, 100) << "..." << std::endl;
    }

    return 0;
}
