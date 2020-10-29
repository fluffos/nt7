// board.h

// 表名前缀
#define TABLE_PREFIX    "phpbb_"

#define TOPICS_TABLE    TABLE_PREFIX "topics"
#define FORUMS_TABLE    TABLE_PREFIX "forums"

#define POSTS_TABLE     TABLE_PREFIX "posts"
#define TEXTS_TABLE     TABLE_PREFIX "posts_text"

#define USERS_TABLE     TABLE_PREFIX "users"

#define DEBUG_MSG(x)    tell_object(find_player("lonely"), HIR + x + NOR);

#define POST_ID         0       // 文章编号
#define TOPIC_ID        1       // 主题编号
#define POSTER_ID       2       // 文章作者
#define POST_TIME       3       // 发表时间

#define POST_SUBJECT    0       // 文章标题
#define BBCODE_UID      1       // bbcode 的鉴定号
#define POST_TEXT       2       // 文章内容

#define TOPIC_TITLE     0       // 主题标题
#define TOPIC_POSTER    2       // 主题作者
#define TOPIC_TIME      3       // 发表时间
#define TOPIC_VIEWS     4       // 主题浏览次数
#define TOPIC_REPLIES   5       // 主题回复
#define TOPIC_FIRST_ID  6       // 主题首贴编号

// BBS 模式(显示所有的文章，包括回复)
int is_bbs_mode(object me) { return (me->query("env/board_mode") == 0); }
// Web 论坛模式(只显示主题，回复在察看主题时再显示)
// int is_web_mode(object me) { return (me->query("env/board_mode") == 1); }
int is_web_mode(object me) { return me->query("env/board_mode"); }

// 显示回复的方式
#define SHOW_NONE       0       // 不显示
#define SHOW_LAST       1       // 显示最后一篇
#define SHOW_ALL        2       // 显示所有

// Web 论坛地址
#define WEB_URL         "http://www.mudbuilder.com/phpbb/"
#define FORUM_URL       WEB_URL "viewforum.php?f=%d"    // 版面页面地址
#define TOPIC_URL       WEB_URL "viewtopic.php?t=%d"    // 主题页面地址

