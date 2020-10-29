inherit ROOM;  
#include <ansi.h> 
void create() 
{ 
        set("short", "精灵界");
        set("long",
HIG "这里紫霓朦胧，瑞气缭绕，虚空中有一幅诗卷：\n" NOR
HIW "第一个封印放树巅，风精灵从此不再飞翔。\n"
    "第二个封印落水间，涟漪和浪花便敛起了锋芒。\n"
    "第三个封印封锁山岩，大地的歌声转为呜咽。\n"
    "第四个封印驱逐雷电，世间只剩下冰冷的火焰。\n"
    "第五个封印啊天空知道，太阳的光芒远离了绝顶上神奇的琼草。\n"
    "第六个封印也很清晰，月光在墓园里不安地嬉戏。\n" 
    "可是第七个封印啊，我怎么想也想不起。第七个封印啊我一生\n"
    "的灵契，我究竟把它忘在哪里？\n" NOR
HIG "一个清灵美丽的女孩站在诗卷下，仿佛等待着什么。\n" NOR
);
        set("exits", ([ 
   "south" : __DIR__"spirit1",
 ]));
        set("objects", ([ 
           "/quest/tulong/npc/leader" : 1,
]));
        set("no_clean_up", 0);

        set("no_magic", 1);
        setup();
        replace_program(ROOM);
}
