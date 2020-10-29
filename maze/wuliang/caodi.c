// Room: caodi.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "万劫谷谷口");
        set("long", @LONG
眼前大片草地，尽头处又全是一株株松树。走过草地，只见一株大松上削
下了丈许长、尺许宽的一片，漆上白漆，写着九个大字：“姓段者入此谷杀无
赦”。八字黑色，那“杀”字却作殷红之色。 
LONG
        );
        set("exits", ([
            "out" : __DIR__"hslin",
            "south" : __DIR__"xiaojing",
        ])); 
        set("outdoors", "大理");

        setup();
}