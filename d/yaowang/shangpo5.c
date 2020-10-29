inherit ROOM;

void create()
{
        set("short", "上山小路");
        set("long", @LONG
这是一条陡峭的上山小路，两旁都是带刺的荆棘，地上是稀
松的黄土和小石子，一不小心准摔跟斗。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "northup" : __DIR__"feng",
  "southdown" : __DIR__"shangpo4",
]));

        set("outdoors", "yaowang");
        setup();
}

int valid_leave(object me, string dir)
{
        int sk;

        if(!userp(me) || (dir != "northup"))
                return ::valid_leave(me, dir);

        sk = me->query_skill("dodge", 1);

        if(random(40) > sk)
        {
                me->receive_damage("qi", 25);
                return notify_fail("你一个不留神，摔了个大马爬。\n");
        }

        return ::valid_leave(me, dir);
}
