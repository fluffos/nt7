inherit ROOM;

void create()
{
        set("short", "书房内厅");
        set("long", @LONG
这里是书房内厅，靠墙放着一排书架，窗前的小几上一个小
书童正在其间抄写着什么。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
        "out": __DIR__"shufang",
        ]));

        set("objects", ([
                __DIR__"npc/sn" : 1,
        ]));
        setup();

}

int valid_leave(object me,string dir)
{
        if(!me)
                return 0;

        if(dir == "out")
        {
                if(sizeof(filter_array(deep_inventory(me),(: $1->is_yaowang_book() :))))
                        return notify_fail("书奴悄悄地对你说，这些书别拿出去呀!\n");
        }

        return ::valid_leave(me,dir);
}

