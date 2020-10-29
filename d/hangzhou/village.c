// This program is a part of NT MudLIB

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "牛家村");
        set("long", @LONG
钱塘江浩浩江水，日日夜夜无穷无休的从临安牛家村边绕过，东
流入海。江畔一排数十株乌柏树，叶子似火烧般红。村前村后的野草
刚起始变黄，更增了几分萧索。两株大松树下围着一堆村民，男男女
女和十几个小孩，正自聚精会神的听着一个瘦削的老者说话。村东头
挑出一个破酒帘，似是酒店模样。
LONG );

        set("exits", ([ /* sizeof() == 2 */
                "east" : __DIR__"jiudian",
                "west" : __DIR__"qiantang",
        ]));

        set("objects", ([
                __DIR__"npc/yang" : 1,
                __DIR__"npc/guo" : 1,
         ]));

         set("outdoors", "xihu");

         set("coor/x", 3900);
        set("coor/y", -1800);
        set("coor/z", 0);
        setup();

         replace_program(ROOM);
}