// Room: /d/mingjiao/mishi.c
// Date: Java 97/04/9

inherit ROOM;

#include <room.h>

void create()
{
        set("short", "石室");
        set("long", @LONG
这间石室极大，顶上垂下钟乳，显是天然的石洞。走了几步，突
见地下倒着两具骷髅。骷髅身上衣服尚未烂尽，着得出是一男一女。
走近两具骷髅，只见那女子右手抓着一柄晶光闪亮的匕首，插在她自
己胸口。
LONG );
        set("exits", ([
                "south" : __DIR__"midao0",
                "up"    : __DIR__"neishi",
        ]));
        set("objects", ([
                __DIR__"obj/yangdt" : 1,
                __DIR__"obj/yangfr" : 1,
        ]));
        set("no_clean_up", 0);
        set("xin_count", 1);
        setup();
        create_door("south", "石门", "north", !DOOR_CLOSED);
}

void init()
{
        add_action("do_ketou", "ketou");
}

int do_ketou()
{
        object me;

        me = this_player();
        message_vision("$N虔诚地跪下来，在阳教主遗骨前恭恭敬敬地磕了个头。\n", me);
        if (query("xin_count") > 0 )
        {
                addn("xin_count", -1);
                new(__DIR__"obj/yixin")->move(this_object());
                new("/clone/book/qiankun_book")->move(this_object());
                tell_object(me, "突然你抬眼看到遗骨下面，有一些东西，你"
                            "看了看，原来是一封信和一张羊皮。\n");
        }
        return 1;
}
void reset()
{
        ::reset();
        set("xin_count",1);
}