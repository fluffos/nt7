//Cracked by Kafei
// yideng quest room 12

inherit ROOM;
void create()
{
        set("short", "庙后石室");
        set("long", @LONG
竹林深处的石室清雅幽静，窗外满眼是幽幽碧竹，正是禅宗参禅
之妙所。室中小几上点着一炉檀香，几旁一位老僧端坐在蒲团上。
LONG );

        set("exits", ([
                "south" : __DIR__"yideng11",
        ]));

        set("objects", ([
                CLASS_D("duan") + "/yideng" : 1,
                ]) );

        set("invalid_startroom", 1);
        set("coor/x", -38000);
        set("coor/y", -79990);
        set("coor/z", 500);
        setup();
}