// database.h

// 是否采用永久连接
#define STATIC_LINK
//#define USE_SQLITE
// 是否调试状态
// #define DEBUG
// 是否允许分站新玩家注册
// #define REFUSE_NEW_PLAYER

protected mapping all_others_db = ([
        // "61.184.100.7" : "lonely",     // db_host : db_user
]);

protected mapping stations = ([
        "127.0.0.1" : "《泥潭·王者归来》",
]);

#ifndef DATABASE
nosave string DATABASE               = "nitan";
#endif
#ifndef DB_USER
nosave string DB_USER                = "lonely";
#endif
nosave string USER_TABLE             = "users";
nosave string IP_TABLE               = "ip";
nosave string NEWS_TABLE             = "news";
nosave string ITEM_TABLE             = "items";
nosave string MEMBER_TABLE           = "members";
nosave string CARD_TABLE             = "cards";

// 采用的加密算法
nosave string DB_CRYPT               = "PASSWORD";
