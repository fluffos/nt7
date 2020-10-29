// boardd.c
// Created by jjgod. 2002/01/29.
// Updated by jjgod. 2002/06/16.
// Finishd by jjgod. 2002/06/28.

// databased.c 提供的函数：(* 为尚未完成)
//
// 版面管理：
//   int    query_forum_id()       - 查询版面 ID
//   mixed  query_forum_info()     - 查询版面信息
//   string query_mud_name()       - 查询用户名('阿福-jjgod' 形式)
//   string query_user_name()      - 查询用户 ID('jjgod' 形式)
//   int    query_user_id()        - 查询用户编号
//   int    query_post_id()        - 查询文章编号
//   int    query_topic_id()       - 查询主题编号

// 文章管理：
//   mixed *query_all_topics()     - 返回所有主题(不包括回复) -+
//   mixed *query_all_posts()      - 返回所有文章(包括回复)   -+- 二者格式不同
//   mixed *query_post_info()      - 返回文章内容(根据 POST_ID)
//   mixed *query_topic_info()     - 返回主题内容(根据 TOPIC_ID)
//   mixed *query_new_post()       - 返回未读文章(根据不同浏览模式返回主题或者所有文章)
//   mixed *query_post()           - 根据用户指定的编号找到应读的文章
//   int    query_topic_number()   - 返回主题的编号
//   int   *query_number_post()    - 根据序号找到文章的 POST_ID
//   int   *query_number_topic()   - 根据序号找到主题的 TOPIC_ID / POST_ID
//   mixed *query_post_data()      - 返回指定文章数据

// 文章发表、回复与删除：
//   int   delete_topic()          - 删除指定编号的主题
//   int   delete_post()           - 删除指定编号的文章
//   int   reply_topic()           - 回复主题
//   int   add_topic_view()        - 增加主题的浏览次数
//   int   post_new_topic()        - 发表新主题

// #pragma optimize
// #pragma save_binary

// #ifdef DB_SAVE
// 暂时关闭
#ifdef DB_SAVE_A

#include <ansi.h>
#include <board.h>
#include <mudlib.h>

#include "/adm/etc/database.h"
#define DEBUG

#ifdef STATIC_LINK
protected int db_handle = 0;
#endif

int    query_forum_id(object board);
int    query_post_id(int forum_id, int post_time);
int    query_topic_id(int forum_id, string title);
int    query_topic_number(object board, int topic_id);
int   *query_number_topic(object board, int num, int mode);
int   *query_number_post(object board, int num);
string query_user_name(int user_id);
string query_mud_name(int user_id);
mixed  query_forum_info(object board, string key);
mixed *query_all_replies(int topic_id, int first_post_id);
mixed *query_post_data(int post_id);

varargs mixed *query_post_info(int post_id, int raw);
varargs mixed *query_all_topics(object board, int raw);
varargs mixed *query_topic_info(int topic_id, int raw);
varargs int    add_topic_view(int topic_id, int count);

protected void log_error(string func, mixed err)
{
        log_file("boardd", sprintf("%s ERROR ** %s\n%O\n", func, ctime(time()), err));
}

int query_db_status()
{
        mixed *ret;

#ifdef STATIC_LINK
        ret = DATABASE_D->db_fetch_row("SHOW DATABASES");
        if (db_handle && arrayp(ret) && sizeof(ret) > 0)
                return 1;
#endif
        return 0;
}

#ifdef STATIC_LINK
protected void connect_to_database()
#else
protected int connect_to_database()
#endif
{
        mixed n;

        n = db_connect(DB_HOST, DATABASE, DB_USER);

        if (intp(n) && (n > 0))  // 连接成功
#ifdef STATIC_LINK
        {
                db_handle = n;
                return;
        }
#else
                return n;
#endif

        else
        {
                log_error("db_connect", n);
#ifdef STATIC_LINK
                call_out("connect_to_database", 30);
                return;
#endif
                return 0;
        }
}

protected void close_database(int db)
{
        mixed ret;

        if (! intp(db) || (db < 1))
                return 0;

        ret = db_close(db);

        if (intp(ret) && (ret == 1))
                return;

        else
                log_error("db_close", ret);
}

protected void create()
{
        seteuid(ROOT_UID);
#ifdef STATIC_LINK
        // connect_to_database();
        db_handle = DATABASE_D->query_db_handle();
#endif
}

protected int valid_caller()
{
        // ! 注意，正式站点一定要把下面的语句删除 !
#ifdef DEBUG
        return 1;
#else
        // ! 注意，正式站点一定要把上面的语句删除 !

        if (! previous_object() ||
           (previous_object() != find_object(SIMUL_EFUN_OB)) &&
           (! inherits(DATABASE_BOARD, previous_object())))
                return 0;

        else
                return 1;
#endif
}

/*
#ifdef STATIC_LINK
void remove(string id)
{
        if (! valid_caller())
                return;

        close_database(db_handle);
}
#endif
*/

int query_forum_id(object board)
{
        string forum_name;
        int forum_id;
        int db;
        mixed ret, *res;
        string sql;

        if (! valid_caller())
                return 0;

        if (! objectp(board))
                return 0;

        if( !stringp(forum_name=query("forum_name", board)) )
        {
                log_error("query_forum_id",query("board_id", board)+
                          " have no forum name.");
                return 0;
        }

        if( intp(forum_id=query("forum_id", board)) && forum_id != 0 )
                return forum_id;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT forum_id FROM %s WHERE forum_name = \"%s\"",
                      FORUMS_TABLE, forum_name);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_forum_id.db_exec", ret);

        if (sizeof(res = db_fetch(db, 1)) && intp(res[0]))
                forum_id = res[0];

#ifndef STATIC_LINK
                close_database(db);
#endif

        set("forum_id", forum_id, board);
        return forum_id;
}

// 查询版面信息
mixed query_forum_info(object board, string key)
{
        int forum_id;
        int db;
        mixed ret, *res;
        string sql;

        if (! valid_caller())
                return 0;

        if (! objectp(board))
                return 0;
#ifndef DEBUG
        if( !undefinedp(ret=query(key, board)) )
                return ret;
#endif
        if (! forum_id = query_forum_id(board))
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT %s FROM %s WHERE forum_id = %d",
                      key, FORUMS_TABLE, forum_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_forum_info.db_exec", ret);

        if (sizeof(res = db_fetch(db, 1)) && ! undefinedp(res[0]))
                ret = res[0];

#ifndef STATIC_LINK
                close_database(db);
#endif

#ifndef DEBUG
        set(key, ret, board);
#endif
        return ret;
}

// 若没有作用数据库保存用户数据的工作，就要修改 NAME_D 以提供类似的
// 把 id 转换为 name 的功能
string query_mud_name(int user_id)
{
        string user_name;

        if (! user_id)
                return "nitan3";

        user_name = query_user_name(user_id);

        if (! user_name)
                return "nitan3";

        return sprintf("%s-%s", DATABASE_D->db_query_user(user_name, "name"),
                       user_name);
}

// 把 Web 数据库保存的用户 id(类似 1、2 这样的)转换为 mud 中的 id，
// 即 Web 论坛上的用户名
string query_user_name(int user_id)
{
        int db;
        mixed ret, *res;
        string sql;
        string user_name;

        if (! valid_caller())
                return 0;

        if (! intp(user_id) || ! user_id)
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT username FROM %s WHERE user_id = %d",
                      USERS_TABLE, user_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_user_name.db_exec", ret);

        if (sizeof(res = db_fetch(db, 1)) && stringp(res[0]))
                ret = res[0];

#ifndef STATIC_LINK
                close_database(db);
#endif
        return ret;
}

// 返回所有的主题(回复从属于主题，另置)
varargs mixed *query_all_topics(object board, int raw)
{
        int forum_id;
        int db, i;
        mixed ret, *res;
        string sql;

        if (! valid_caller())
                return 0;

        if (! objectp(board))
                return 0;

        if (! forum_id = query_forum_id(board))
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT topic_title, topic_id, topic_poster,"
                      " topic_time%s"
                      " FROM %s WHERE forum_id = %d ORDER BY topic_time",
                      raw ? "" : ", topic_views, topic_replies, topic_first_post_id",
                      TOPICS_TABLE, forum_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_all_topics.db_exec", ret);

        res = ({ });
        i = 1;
        while (sizeof(ret = db_fetch(db, i)))
        {
                res += ({ ret });
                i++;
        }
#ifndef STATIC_LINK
                close_database(db);
#endif
        return res;
}

// 查询一个 board 所有的文章(包括回复)
// ({ 文章编号, 所属主题编号, 作者号, 发表时间 })
mixed *query_all_posts(object board)
{
        int forum_id;
        int db, i;
        mixed ret, *res;
        string sql;

        if (! valid_caller())
                return 0;

        if (! objectp(board))
                return 0;

        if (! forum_id = query_forum_id(board))
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT post_id, topic_id, poster_id, post_time"
                      " FROM %s WHERE forum_id = %d ORDER BY post_time",
                      POSTS_TABLE, forum_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_all_posts.db_exec", ret);

        res = ({ });
        i = 1;
        while (sizeof(ret = db_fetch(db, i)))
        {
                res += ({ ret });
                i++;
        }
#ifndef STATIC_LINK
                close_database(db);
#endif
        return res;
}

// 查询一篇文章的详细信息
// ({ 标题, BBCODE 鉴定号, 内容 })
varargs mixed *query_post_info(int post_id, int raw)
{
        int db;
        mixed ret, *res;
        string sql;

        if (! valid_caller())
                return 0;

        if (! intp(post_id) || ! post_id)
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT post_subject, bbcode_uid%s"
                      " FROM %s WHERE post_id = %d",
                      raw ? "" : ", post_text", TEXTS_TABLE,
                      post_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_post_info.db_exec", ret);

        if (sizeof(res = db_fetch(db, 1)))
                ret = res;
#ifndef STATIC_LINK
                close_database(db);
#endif
        return ret;
}

// 查询一篇主题的详细信息
// ({ 标题, 编号, 发表者编号, 发表时间, 浏览次数, 回复数, 首贴编号 })
varargs mixed *query_topic_info(int topic_id, int raw)
{
        int db;
        mixed ret, *res;
        string sql;

        if (! valid_caller())
                return 0;

        if (! intp(topic_id) || ! topic_id)
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT topic_title, topic_id, topic_poster,"
                      " topic_time%s"
                      " FROM %s WHERE topic_id = %d",
                      raw ? "" : ", topic_views, topic_replies, topic_first_post_id",
                      TOPICS_TABLE, topic_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_topic_info.db_exec", ret);

        if (sizeof(res = db_fetch(db, 1)))
                ret = res;
#ifndef STATIC_LINK
                close_database(db);
#endif
        return ret;
}

// 查询一个主题所有的回复(不包括首贴)
// ({ 文章编号, 所属主题编号, 作者号, 发表时间 })
mixed *query_all_replies(int topic_id, int first_post_id)
{
        int db, i;
        mixed ret, *res;
        string sql;

        if (! valid_caller())
                return 0;

        if (! intp(topic_id) || ! topic_id)
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT post_id, topic_id, poster_id, post_time"
                      " FROM %s WHERE topic_id = %d AND post_id != %d"
                      " ORDER BY post_time",
                      POSTS_TABLE, topic_id, first_post_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_all_replies.db_exec", ret);

        res = ({ });
        i = 1;
        while (sizeof(ret = db_fetch(db, i)))
        {
                res += ({ ret });
                i++;
        }
#ifndef STATIC_LINK
                close_database(db);
#endif
        return res;
}

// 返回一篇主题的编号
int query_topic_number(object board, int topic_id)
{
        int num, i, max;
        mixed *posts;

        posts = query_all_posts(board);
        max = sizeof(posts);

        for (i = 0; i < max; i++)
        {
                if (posts[i][TOPIC_ID] == topic_id)
                        return (i + 1);
        }
}

// 根据用户名查找用户 id
int query_user_id(string user_name)
{
        int db;
        mixed ret, *res;
        string sql;

        if (! valid_caller())
                return 0;

        if (! stringp(user_name))
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT user_id FROM %s WHERE username = \"%s\"",
                      USERS_TABLE, user_name);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_user_id.db_exec", ret);

        if (sizeof(res = db_fetch(db, 1)))
                ret = res[0];

#ifndef STATIC_LINK
                close_database(db);
#endif
        return ret;
}

// 返回主题的编号
int query_topic_id(int forum_id, string title)
{
        int db;
        mixed ret, *res;
        string sql;

        if (! valid_caller())
                return 0;

        if (! stringp(title))
                return 0;

        if (! intp(forum_id) || ! forum_id)
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT topic_id FROM %s WHERE forum_id = %d"
                      " AND topic_title = \"%s\"",
                      TOPICS_TABLE, forum_id, title);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_topic_id.db_exec", ret);

        if (sizeof(res = db_fetch(db, 1)))
                ret = res[0];

#ifndef STATIC_LINK
                close_database(db);
#endif
        return ret;
}

// 返回文章的编号
int query_post_id(int forum_id, int post_time)
{
        int db;
        mixed ret, *res;
        string sql;

        if (! valid_caller())
                return 0;

        if (! intp(post_time) || ! post_time)
                return 0;

        if (! intp(forum_id) || ! forum_id)
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT post_id FROM %s WHERE forum_id = %d"
                      " AND post_time = %d",
                      POSTS_TABLE, forum_id, post_time);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_post_id.db_exec", ret);

        if (sizeof(res = db_fetch(db, 1)))
                ret = res[0];

#ifndef STATIC_LINK
                close_database(db);
#endif
        return ret;
}

// 把 "127.0.0.1" 转换为 7F000001 这样的 16 进制地址
string convert_to_ip(string ip)
{
        array ips;
        string hex_ip;

        ips = explode(ip, ".");
        hex_ip = "";

        foreach (ip in ips)
                hex_ip += sprintf("%2'0'X", atoi(ip));

        return hex_ip;
}

// 发表新主题
int post_new_topic(object board, string title, string name, string text, string ip)
{
        int db;
        mixed ret;
        string sql;
        int forum_id;
        int poster_id;
        int topic_id;
        int post_id;
        int t;

        if (! valid_caller())
                return 0;

        if (! objectp(board))
                return 0;

        if (! forum_id = query_forum_id(board))
                return 0;

        if (! poster_id = query_user_id(name))
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        // 插入主题
        t = time();
        sql = sprintf("INSERT INTO %s (topic_title, topic_poster, topic_time, forum_id)"
                      " VALUES (\"%s\", %d, %d, %d)",
                      TOPICS_TABLE, title, poster_id, t, forum_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("post_new_topic.db_exec", ret);

        // 插入帖子
        topic_id = query_topic_id(forum_id, title);
        sql = sprintf("INSERT INTO %s (topic_id, forum_id, poster_id, post_time, poster_ip)"
                      " VALUES (%d, %d, %d, %d, \"%s\")",
                      POSTS_TABLE, topic_id, forum_id, poster_id, t, convert_to_ip(ip));
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("post_new_topic.db_exec", ret);

        // 插入帖子内容
        post_id = query_post_id(forum_id, t);
        sql = sprintf("INSERT INTO %s (post_id, post_subject, bbcode_uid, post_text)"
                      " VALUES (%d, \"%s\", \"\", \"%s\")",
                      TEXTS_TABLE, post_id, title, text);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("post_new_topic.db_exec", ret);

        // 设定首贴 id
        sql = sprintf("UPDATE %s SET topic_first_post_id = %d, topic_last_post_id ="
                      " %d WHERE topic_id = %d", TOPICS_TABLE, post_id, post_id, topic_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("post_new_topic.db_exec", ret);

        // 增加用户发帖数
        sql = sprintf("UPDATE %s SET user_posts = user_posts + 1 WHERE user_id ="
                      " %d", USERS_TABLE, poster_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("post_new_topic.db_exec", ret);

        // 增加版面主题、文章数
        sql = sprintf("UPDATE %s SET forum_posts = forum_posts + 1, "
                      "forum_topics = forum_topics + 1, forum_last_post_id = "
                      "%d WHERE forum_id = %d",
                      FORUMS_TABLE, post_id, forum_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("post_new_topic.db_exec", ret);

#ifndef STATIC_LINK
                close_database(db);
#endif
        return 1;
}

// 增加主题的浏览次数
varargs int add_topic_view(int topic_id, int count)
{
        int db;
        mixed ret;
        string sql;

        if (! valid_caller())
                return 0;

        if (! intp(topic_id) || ! topic_id)
                return 0;

        // 默认增加一次
        if (! count) count = 1;

        if (count <= 0)
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("UPDATE %s SET topic_views = topic_views + %d"
                      " WHERE topic_id = %d",
                      TOPICS_TABLE, count, topic_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("add_topic_view.db_exec", ret);

#ifndef STATIC_LINK
                close_database(db);
#endif
        return ret;
}

// 查询指定 post_id 的文章数据
mixed *query_post_data(int post_id)
{
        int db;
        mixed ret, *res;
        string sql;

        if (! valid_caller())
                return 0;

        if (! post_id)
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = sprintf("SELECT post_id, topic_id, poster_id, post_time"
                      " FROM %s WHERE post_id = %d",
                      POSTS_TABLE, post_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("query_post_data.db_exec", ret);

        if (sizeof(res = db_fetch(db, 1)))
                ret = res;

#ifndef STATIC_LINK
                close_database(db);
#endif
        return ret;
}

// 根据用户指定的编号找到主题的 id
int *query_number_topic(object board, int num, int mode)
{
        mixed *posts;
        int max;

        if (! valid_caller())
                return 0;

        posts = mode ? query_all_posts(board)
                     : query_all_topics(board);

        if (! arrayp(posts) ||
            ! (max = sizeof(posts)) ||
            num > 0 && num > max - 1 ||
            num < 0 && -num > max)
                return 0;

        // 若 num < 0，则返回倒数的主题 id
        if (num < 0) return posts[max + num][TOPIC_ID];

        return posts[num][TOPIC_ID];
}

// 根据用户指定的编号找到文章的 id
int *query_number_post(object board, int num)
{
        mixed *posts;
        int max;

        if (! valid_caller())
                return 0;

        posts = query_all_posts(board);

        if (! arrayp(posts) ||
            ! (max = sizeof(posts)) ||
            num > 0 && num > max - 1 ||
            num < 0 && -num > max - 1)
                return 0;

        // 若 num < 0，则返回倒数的主题 id
        if (num < 0) return posts[max + num][TOPIC_ID];

        return posts[num][POST_ID];
}

// 回复主题
int reply_topic(object board, int topic_id, string name, string text, string ip)
{
        int db;
        mixed ret;
        string sql;
        int forum_id;
        int poster_id;
        int post_id;
        int t;

        if (! valid_caller())
                return 0;

        if (! objectp(board))
                return 0;

        if (! forum_id = query_forum_id(board))
                return 0;

        if (! poster_id = query_user_id(name))
                return 0;

        if (! topic_id)
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif
        t = time();

        // 插入帖子
        sql = sprintf("INSERT INTO %s (topic_id, forum_id, poster_id, post_time, poster_ip)"
                      " VALUES (%d, %d, %d, %d, \"%s\")",
                      POSTS_TABLE, topic_id, forum_id, poster_id, t, convert_to_ip(ip));
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("reply_topic.db_exec", ret);

        // 插入帖子内容
        post_id = query_post_id(forum_id, t);
        sql = sprintf("INSERT INTO %s (post_id, post_subject, bbcode_uid, post_text)"
                      " VALUES (%d, \"%s\", \"\", \"%s\")",
                      TEXTS_TABLE, post_id, "", text);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("reply_topic.db_exec", ret);

        // 设定尾贴 id，回复加一，时间更新
        sql = sprintf("UPDATE %s SET topic_replies = topic_replies + 1, "
                      "topic_last_post_id = %d, topic_time = %d WHERE topic_id = %d",
                      TOPICS_TABLE, post_id, t, topic_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("reply_topic.db_exec", ret);

        // 增加用户发帖数
        sql = sprintf("UPDATE %s SET user_posts = user_posts + 1 WHERE user_id ="
                      " %d", USERS_TABLE, poster_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("reply_topic.db_exec", ret);

        // 增加版面文章数
        sql = sprintf("UPDATE %s SET forum_posts = forum_posts + 1, "
                      "forum_last_post_id = %d WHERE forum_id = %d",
                      FORUMS_TABLE, post_id, forum_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("reply_topic.db_exec", ret);

#ifndef STATIC_LINK
                close_database(db);
#endif
        return 1;
}

// 删除主题
int delete_topic(object board, int topic_id)
{
        int db;
        int forum_id;
        mixed ret;
        mixed *posts, *post;
        string sql;

        if (! valid_caller())
                return 0;

        if (! topic_id)
                return 0;

        if (! forum_id = query_forum_id(board))
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        // 删除主题
        sql = sprintf("DELETE FROM %s WHERE topic_id = %d",
                      TOPICS_TABLE, topic_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("delete_topic.db_exec", ret);

        // 删除所有本主题下文章内容
        posts = query_all_posts(board);
        foreach (post in posts)
        {
                if (post[TOPIC_ID] == topic_id)
                {
                        sql = sprintf("DELETE FROM %s WHERE post_id = %d",
                                      TEXTS_TABLE, post[POST_ID]);
                        db_exec(db, sql);
                }
        }

        // 删除所有本主题下文章
        sql = sprintf("DELETE FROM %s WHERE topic_id = %d",
                      POSTS_TABLE, topic_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("delete_topic.db_exec", ret);

        // 减少版面主题、文章数
        sql = sprintf("UPDATE %s SET forum_posts = forum_posts - %d, "
                      "forum_topics = forum_topics - 1 WHERE forum_id = %d",
                      FORUMS_TABLE, sizeof(posts), forum_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("reply_topic.db_exec", ret);

#ifndef STATIC_LINK
                close_database(db);
#endif
        return 1;
}

// 删除文章
int delete_post(object board, int post_id)
{
        int db;
        int forum_id;
        mixed ret;
        string sql;
        mixed *pdata, *tinfo;

        if (! valid_caller())
                return 0;

        if (! post_id)
                return 0;

        if (! forum_id = query_forum_id(board))
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        pdata = query_post_data(post_id);
        tinfo = query_topic_info(pdata[TOPIC_ID]);

        // 若为首贴，则删除整个主题的所有文章
        if (tinfo[TOPIC_FIRST_ID] == post_id)
                return delete_topic(board, pdata[TOPIC_ID]);

        // 删除文章内容
        sql = sprintf("DELETE FROM %s WHERE post_id = %d",
                      TEXTS_TABLE, post_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("delete_post.db_exec", ret);

        // 删除所有本主题下文章
        sql = sprintf("DELETE FROM %s WHERE post_id = %d",
                      POSTS_TABLE, post_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("delete_post.db_exec", ret);

        // 减少版面主题、文章数
        sql = sprintf("UPDATE %s SET forum_posts = forum_posts - 1"
                      " WHERE forum_id = %d",
                      FORUMS_TABLE, forum_id);
        ret = db_exec(db, sql);

        if (! intp(ret))
                log_error("reply_topic.db_exec", ret);

#ifndef STATIC_LINK
                close_database(db);
#endif
        return 1;
}

int db_count_user()
{
        int db;
        mixed ret, *res;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        // ret = db_exec(db, sprintf("SELECT COUNT(*) AS NUM FROM %s", USERS_TABLE));
        ret = db_exec(db, sprintf("SELECT MAX(user_id) FROM %s", USERS_TABLE));
        if (! intp(ret) || (ret < 1))
        {
                log_error("count_reg_user", ret);
                return 0;
        }

        res = db_fetch(db, 1);

#ifndef STATIC_LINK
        close_database(db);
#endif
        return res[0];
}

int db_create_user(object user)
{
        int db, user_id;
        mixed ret;
        string sql;

        if (! objectp(user))
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
                return 0;
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif
        user_id = db_count_user() + 1;
        sql = "insert into phpbb_users set user_id = " + DB_STR(user_id) +
              ",username=query("id", "+DB_STR(user))+",user_password="+
              DB_STR(query("ad_password", user))+",user_email="+
              DB_STR(query("email", user));

        ret = db_exec(db, sql);

#ifndef STATIC_LINK
                close_database(db);
#endif
        if (! intp(ret))
        {
                log_error("db_create_user.db_exec", ret);
                return 0;
        }

        return ret;
}

int db_remove_player(string id)
{
        int db;
        string sql;
        mixed ret;

        if (! stringp(id) || id == "")
                return 0;

#ifdef STATIC_LINK
        if (! db_handle)
        {
                return 0;
        }
        db = db_handle;
#else
        if (! (db = connect_to_database()))
                return 0;
#endif

        sql = "delete from phpbb_users where username='" + id + "'";
        ret = db_exec(db, sql);
        if (! intp(ret))
        {
                log_error("db_delete.db_exec", ret + "\n" + sql);
                return 0;
        }
        if (ret < 1) return 0;
#ifndef STATIC_LINK
        close_database(db);
#endif
        return ret;
}

#endif
