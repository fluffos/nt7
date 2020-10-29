#include <ansi.h>
inherit ROOM;

int do_move(string arg);

void create()
{
        set("short", "墓门");
        set("long", @LONG
你走过了草地，眼前突然了一片开阔地，突兀地耸立着一座大墓，
墓上砌的石头已经班驳了，看的出来这是座古墓。墓前没有立碑，也
没有任何的标记，不知道这是前朝哪位王公大臣的墓穴。墓门口被一
块的大石头(shi)封闭得丝毫不透。
LONG );
        set("outdoors", "gumu");
        set("exits", ([
                "east"  : __DIR__"xuanya",
                "west"  : __DIR__"huangshalin",
                "north" : __DIR__"caodi",
        ]));

        set("objects", ([
               __DIR__"npc/yufeng" : 1+random(3),
               __DIR__"npc/sun" :  1,
        ]));

        set("item_desc", ([
               "shi": HIC "这是块巨石，怕不有万斤上下，好象锩着「" NOR + YEL"降龙石" HIC
                      "」几个字。\n" NOR,
        ]) );
        set("coor/x", -3220);
        set("coor/y", 30);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_move", "move");
        add_action("do_move", "luo");
        add_action("do_move", "tui");
}

int do_move(string arg)
{
        object me=this_player();

        if( !arg || arg != "shi" ) {
                return notify_fail("你要移动什么？\n");
        }

        if( (int)me->query_str() > 33 ) {
                message_vision(HIC "$N" HIC "站在石前，双掌发力推动巨石，只听得巨石"
                       "吱吱连声，缓\n缓向后移去，现出一道门户来。\n" NOR,
                       this_player());
                set("exits/south", __DIR__"mudao01");
                remove_call_out("close");
                call_out("close", 5, this_object());
        } else
                message_vision("$N试着推了推巨石，巨石纹丝不动，只得罢了。\n", this_player());
        return 1;
}

void close(object room)
{
        message("vision", HIW "\n只见巨石又吱吱地回到原地。\n" NOR, room);
        delete("exits/south", room);
}

int valid_leave(object me, string dir)
{
        object guard;

        if (dir != "south"
           || ! objectp(guard = present("sun popo", this_object()))
            || !query("family", me) )
                return ::valid_leave(me, dir);

        return guard->permit_pass(me, dir);
}