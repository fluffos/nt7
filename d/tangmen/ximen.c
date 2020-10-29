// ximen.c
 

inherit ROOM;
#include <ansi.h>;

string look_gaoshi();
string get_killer();

void create()
{
        set("short", "西门");
        set("long",
"这是唐家镇的西门，说是西门，其实就是一个岗哨，所有来往的行个\n"
"都要受到检查。这是蜀中唐门为了安全，在这儿设了一个哨位。过往的人\n"
"不准携带兵器。城墙上贴着几张通缉告示(gaoshi)。一条笔直的青石板大\n"
"道向东西两边延伸。再往西边就是蜀中唐门了，东边是镇里。\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 1);
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));

        set("exits", ([
                "east"  : __DIR__"xdajie",
                "northwest"  : __DIR__"ximenroad",
        ]));
        set("objects", ([
                CLASS_D("tangmen") + "/tangrou" : 1,
        ]));
        setup();
}

string look_gaoshi()
{
        return HIR"\n                              唐门通缉榜                    \n\n\n"NOR+get_killer() +HIC"\n\n                                               蜀中唐门             \n                                               唐君伤     \n"NOR;
}

string get_killer()
{
        int i;
        string msg;
        object *ob = users();

        msg = "";
        for (i = 0; i < sizeof(ob); i++)
                if( ob[i]->query_condition("killer") && query("family/family_name", ob[i]) == "唐门世家" )
                        msg += (ob[i]->short() + "\n");
        if (msg == "")
                return "没有违规者。\n";
        else
                return "现在正在缉拿以下违规弟子：\n\n" + msg;
}
