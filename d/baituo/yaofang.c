//room: /d/btshan/restroom.c
inherit ROOM;

void create()
{
        set("short","药房");
        set("long", @LONG
这里是间药房，靠墙放着一只大药柜。屋子里有张桌子，上边摆
满了炼药用的瓶瓶罐罐。其中一个药瓶(bottle)里只装了清水。炼药
师是位小姑娘，正在那里发呆，不知在想什么。北面是气派的长廊。
LONG );

        set("exits",([
                "north" : __DIR__"changlang",
        ]));

        set("item_desc",([
                "bottle" : "药罐上贴着标签：『蛇胆膏』，乃珍"
                           "贵补品，生精补气，效果奇佳。\n",
        ]));

        set("objects",([
                __DIR__"npc/xiaoqing" : 1,
        ]));

        set("coor/x", -49980);
        set("coor/y", 20020);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}