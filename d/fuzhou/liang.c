// room: liang.c

#include <ansi.h>
#include <room.h>

#define JIASHA    "/clone/lonely/book/kuihua3"

inherit ROOM;

void create()
{
        object item;
        set("short","密室房梁");
        set("long", @LONG
你现在在密室的房梁上四下观瞧，周围都是些烂木头破砖瓦。突然
你瞟见犄角旮旯处有一件袈裟。
LONG );
        set("exits", ([
                "down" : __DIR__"mishi",
        ]));
        set("objects", ([
                //__DIR__"obj/jiasha" : 1,
                "/d/xingxiu/npc/snake" :1,
        ]));
        set("coor/x", 1820);
        set("coor/y", -6312);
        set("coor/z", 10);
        setup();
        item = find_object(JIASHA);
        if( !objectp(item) || !environment(item) ) {
                item = get_object(JIASHA);
                item->move(this_object());
                item->start_borrowing();
        }
}


void init()
{
        object me = this_player(), ob;
        int exp, pot, sc;

        exp = 10000 + random(3000);
        pot = 1000 + random(300);
        sc = random(50);

        ob = find_object(JIASHA);
        if (! ob) ob = load_object(JIASHA);

        if (! objectp(ob))
                return 0;

        if (! objectp(present("jia sha", this_object())))
                return 0;

        if( !query("skybook/xiaoao/baodian", me) )
        {
                addn("combat_exp", exp, me);
                addn("potential", pot, me);
                addn("score", sc, me);
                tell_object(me, HIY "\n你刚跃上房梁，顿时发现一件袈裟摆放其中。\n\n"
                                NOR + HIW "你成功的找到了葵花宝典！\n" NOR + HIC
                                "通过这次的历练，你获得了" + chinese_number(exp) +
                                "点经验、" + chinese_number(pot) + "点潜\n能以及"
                                + chinese_number(sc) + "点江湖阅历。\n\n" NOR);
                set("skybook/xiaoao/baodian", 1, me);
        } else
                tell_object(me, HIY "\n你刚跃上房梁，顿时发现一件袈裟摆放其中。\n\n" NOR);
}

void reset()
{
        object item;
        ::reset();
        item = find_object(JIASHA);
        if( !objectp(item) || !environment(item) ) {
                item = get_object(JIASHA);
                item->move(this_object());
                item->start_borrowing();
        }
}
