inherit ROOM;
/*
string go_enter(object me)
{
        if( me && (query("family/family_name", me) == "药王谷") )
                return __DIR__"dmq";

        else
                return __DIR__"shulin/entry";
}
*/
void create()
{
        set("short", "石子小路");
        set("long", @LONG
这是一条石子小路蜿蜒在青青的绿草地中，可能是经常有人
走动，路上的石子被磨得非常光亮，仔细看上面还有用彩色的石
子拼出的一个“药”字。路边竖着一块小石碑(bei)。
LONG
        );

        set("exits", ([
  "north" : __DIR__"dmq",
  "south" : __DIR__"xiaoyuan",
]));

        set("outdoors", "yaowang");
        setup();
}
