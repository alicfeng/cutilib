/*
| Author   :    AlicFeng
| Email    :    a@samego.com
| Github   :    https://github.com/alicfeng
|--------------------------------------------------------------------------
| Simple as well as Easy Tool Library
|--------------------------------------------------------------------------
|
| 所见即所得！没错，这就是一款非常简单且易用的工具类库，由 C/C++ 纯语言标准类库编写的，您只要
| 引入 cutilib/utilib.hpp 头文件即可享受其带来的快感，同时函数的调用姿势也非常舒适。为了避免
| 污染项目或者与标准库的函数冲突，特意使用 samego::utilib 二层命名空间作隔离。详细的说明文档
| 请查阅 https://github.com/alicfeng/cutilib/README.md 文档。
|
*/

#ifndef SAMEGO_UTIL_LIBRARY_HPP_
#define SAMEGO_UTIL_LIBRARY_HPP_


#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <cassert>


namespace samego {
    /**
     * @namespace samego::utilib
     * @details 由此即将进入一个开箱即用的工具类库的编码世界
     */
    namespace utilib {

        /**
         * @defgroup file
         * @class samego::utilib::file
         * @details 集成文件体系的系列函数
         */
        class file {
        public:
            /**
             * 根据文件路径判断文件是否存在
             * @param filepath 文件路径
             * @return bool
             */
            static bool exists(const std::string &filepath) {
                return 0 == access(filepath.c_str(), F_OK);
            }
        };


        /**
         * @defgroup string
         * @class samego::utilib::string
         * @details 集成字符串体系的系列函数
         */
        class string {
        public:
            /**
             * 将字符串内容作URL解码
             * @param content 字符串内容
             * @return std::string
             */
            static std::string url_decode(const std::string &content) {
                std::string data;
                size_t length = content.length();
                for (size_t i = 0; i < length; i++) {
                    if (content[i] == '+') {
                        data += ' ';
                    } else if (content[i] == '%') {
                        assert(i + 2 < length);
                        unsigned char high = from_hex((unsigned char) content[++i]);
                        unsigned char low = from_hex((unsigned char) content[++i]);
                        data += high * 16 + low;
                    } else {
                        data += content[i];
                    }
                }
                return data;
            }

        private:
            /**
             * 非负字符内容反转十六进制
             * @param content 非负字符内容
             * @return unsigned char
             */
            static unsigned char from_hex(unsigned char x) {
                unsigned char y;
                if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
                else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
                else if (x >= '0' && x <= '9') y = x - '0';
                else
                    assert(0);
                return y;
            }
        };
    }
}


#endif //SAMEGO_UTIL_LIBRARY_HPP_